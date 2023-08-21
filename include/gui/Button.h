#ifndef BUTTON_H
#define BUTTON_H
#include <cmath>
#pragma once
#include <cstdlib>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"


namespace sg {

    class Button : public sf::Drawable, public sf::Transform
    {


        private:
            std::string m_content = "NULL";
            sf::Color m_bckgColor = sf::Color::White;
            sf::Color m_textColor = sf::Color::Black;
            sf::Font* m_ptrFont = nullptr;
            int m_charSize = 20;

            int m_outlineThickness = 0;
            sf::Color m_outlineColor = sf::Color::White;

            sf::Vector2f m_position = {100,100};
            sf::Vector2f m_textPos = {100,100};
            sf::Vector2f m_bckgSize = {200,100};

            sf::Vector2f m_bckgOrigin = {0,0};
            sf::Vector2f m_origin = {0,0};

            bool m_isMouseHeld = false;

            // HOVER
            sf::Color m_hoverBckgColor = sf::Color::Black;
            sf::Color m_hoverTextColor = sf::Color::White;
            sf::Color m_hoverOutlineColor = sf::Color::White;

            // CLICK
            sf::Color m_clickBckgColor = sf::Color::Black;
            sf::Color m_clickTextColor = sf::Color::White;
            sf::Color m_clickOutlineColor = sf::Color::White;



            // DEBUG REMOVE LATER
            /*
            sf::RectangleShape DEBUG_SHAPE;
            sf::RectangleShape DEBUG_B_SHAPE;
            */


        private:
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
            {
                if(m_ptrFont != nullptr)
                {
                    target.draw(bckgShape);
                    target.draw(text);
                    //target.draw(DEBUG_SHAPE);
                    //target.draw(DEBUG_B_SHAPE);
                }
            }

            void changeToHover()
            {
                bckgShape.setFillColor(m_hoverBckgColor);
                text.setFillColor(m_hoverTextColor);
                bckgShape.setOutlineColor(m_hoverOutlineColor);
            }

            void changeToClick()
            {
                bckgShape.setFillColor(m_clickBckgColor);
                text.setFillColor(m_clickTextColor);
                bckgShape.setOutlineColor(m_clickOutlineColor);
            }

            void defaultColors()
            {
                bckgShape.setFillColor(m_bckgColor);
                text.setFillColor(m_textColor);
                bckgShape.setOutlineColor(m_outlineColor);
                
            }


        public:
            sf::RectangleShape bckgShape;
            sf::Text text;

        public:
            Button(std::string& content, sf::Vector2f& startPos, sf::Font& font)
            {
                setContent(content);
                setPosition(startPos);
                setFont(font);

                initSelf();
                Button::s_buttons.push_back(this);

            }

            Button()
            {
                initSelf();
                Button::s_buttons.push_back(this);
            }
            ~Button()
            {

            }
            bool onClick( )
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHover())
                {
                    if(!m_isMouseHeld)
                    {
                        m_isMouseHeld = true;
                        return true;
                    }
                }
                else{
                    m_isMouseHeld = false;
                }
                return false;
            }

            void setContent( const std::string& content ) {this->m_content = content; text.setString(content);}
            void setBackgroundColor( const sf::Color& color) {this->m_bckgColor = color; bckgShape.setFillColor(color);}
            void setTextColor( const sf::Color& color ) {this->m_textColor = color; text.setFillColor(color);}
            void setFont( sf::Font& font ) {this->m_ptrFont = &font; text.setFont(font);} 
            void setOutlineThickness( const int& thic ){this->m_outlineThickness = thic; bckgShape.setOutlineThickness(thic);}
            void setOutlineColor( const sf::Color& color ){this->m_outlineColor = color; bckgShape.setOutlineColor(color);}

            void setPosition( const sf::Vector2f& pos ){this->m_position = pos; bckgShape.setPosition(pos);}
            void setTextPosition( const sf::Vector2f& pos ){this->m_textPos = pos; text.setPosition(pos);}

            void setTextOrigin( const sf::Vector2f& o) {this->m_origin = o; text.setOrigin(o);}
            void setBackgroundOrigin( const sf::Vector2f& o ){this->m_bckgOrigin = o; bckgShape.setOrigin(o);}
            

            void setBackgroundSize( const sf::Vector2f& size ){this->m_bckgSize = size; bckgShape.setSize(size);}
            void setCharacterSize( const int& size ){this->m_charSize = size; text.setCharacterSize(size);}

            void setHoverColors( const sf::Color& backgroundColor, const sf::Color& textColor, const sf::Color& outlineColor)
            {
                m_hoverBckgColor = backgroundColor;
                m_hoverTextColor = textColor;
                m_hoverOutlineColor = outlineColor;
            }

            void setClickColors( const sf::Color& backgroundColor, const sf::Color& textColor, const sf::Color& outlineColor)
            {
                m_clickBckgColor = backgroundColor;
                m_clickTextColor = textColor;
                m_clickOutlineColor = outlineColor;
            }




            void setTextCENTER()
            {
                //https://learnsfml.com/how-to-center-text/
                setBackgroundOrigin(sf::Vector2f(bckgShape.getSize().x * 0.5f, bckgShape.getSize().y * 0.5f));

                sf::Vector2f center = text.getGlobalBounds().getSize() * 0.5f;
                sf::Vector2f localBounds =  center + text.getLocalBounds().getPosition();
                sf::Vector2f rounded = sf::Vector2f(std::round(localBounds.x), std::round(localBounds.y));

                text.setOrigin(rounded);
                text.setPosition(bckgShape.getPosition());
                
                //DEBUG_SHAPE.setPosition(text.getPosition());
                //DEBUG_B_SHAPE.setPosition(bckgShape.getPosition());

            }

            void initSelf()
            {
                bckgShape.setPosition(m_position);
                bckgShape.setOutlineColor(m_outlineColor);
                bckgShape.setOutlineThickness(m_outlineThickness);
                bckgShape.setSize(sf::Vector2f(m_bckgSize.x - m_outlineThickness, m_bckgSize.y - m_outlineThickness));
                bckgShape.setFillColor(m_bckgColor);
                bckgShape.setOrigin(sf::Vector2f(m_bckgSize.x * 0.5f, m_bckgSize.y * 0.5f));

                text.setFillColor(m_textColor);
                text.setCharacterSize(m_charSize);
                if(m_ptrFont != nullptr) text.setFont(*m_ptrFont);
                text.setString(m_content);
                setTextCENTER();

                /*
                DEBUG_SHAPE.setFillColor(sf::Color::Red);
                DEBUG_SHAPE.setSize(sf::Vector2f(6,6));
                DEBUG_SHAPE.setOrigin(3,3);
                DEBUG_SHAPE.setPosition(text.getPosition());

                DEBUG_B_SHAPE.setFillColor(sf::Color::Blue);
                DEBUG_B_SHAPE.setSize(sf::Vector2f(6,6));
                DEBUG_B_SHAPE.setOrigin(3,3);
                DEBUG_B_SHAPE.setPosition(bckgShape.getPosition());
                */

            }

            bool isHover()
            {
                if(bckgShape.getGlobalBounds().contains(Button::s_mousePosView))
                {
                    return true;
                }
                return false;
            }

            const sf::Text& getText( ) {return text;}
            const sf::RectangleShape getBackgroundShape( ) {return bckgShape;}

        public:
            inline static sf::RenderWindow* s_window;
            inline static std::vector<Button*> s_buttons;
            inline static sf::Vector2f s_mousePosView;

        public:
            inline static void setWindow( sf::RenderWindow& window )
            {
                Button::s_window = &window;
            }
            inline static void update( )
            {
                Button::s_mousePosView = Button::s_window->mapPixelToCoords(sf::Mouse::getPosition(*Button::s_window));

                for(auto& button : Button::s_buttons)
                {
                    if(button->isHover() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) { button->changeToClick(); }
                    else if(button->isHover()) { button->changeToHover(); }
                    else{ button-> defaultColors(); }
                }
            }


    };
}



#endif // !BUTTON_H
