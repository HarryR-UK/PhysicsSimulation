#include "../include/GuiHandler.h"
#include <iterator>
using namespace handler;


const void GuiHandler::setContraints(int w, int h)
{
    m_constraintWidth = w;
    m_constraintHeight = h;
    m_boundaryPole.setFillColor(sf::Color(80,80,80));
    m_boundaryPole.setSize(sf::Vector2f(5,h));
    //m_boundaryPole.setOrigin(sf::Vector2f(m_boundaryPole.getSize().x * 0.5f, m_boundaryPole.getSize().y * 0.5f));
    m_boundaryPole.setPosition(sf::Vector2f(w - m_boundaryPole.getSize().x, 0));

}

const void GuiHandler::setWindow(sf::RenderWindow& window)
{
    m_window = &window;
}

GuiHandler::GuiHandler( pe::Simulation& sim )
{
    m_sim = &sim;

}

GuiHandler::~GuiHandler()
{
    delete m_font;
}

void GuiHandler::initButtons()
{
    m_font = new sf::Font;
    if(!m_font->loadFromFile("../res/fonts/open-sans/OpenSans-Semibold.ttf")) std::cout << "ERROR LOADING FONT!" << '\n';
    initClearButton();
    initToggleGravityButton();

}

void GuiHandler::initToggleGravityButton()
{
    m_gravityButton.setFont(*m_font);
    m_gravityButton.setCharacterSize(15);
    m_gravityButton.setContent("Gravity");
    m_gravityButton.setTextColor(sf::Color::White);
    m_gravityButton.setBackgroundColor(sf::Color::Black);
    m_gravityButton.setOutlineThickness(1);
    m_gravityButton.setOutlineColor(sf::Color::White);
    m_gravityButton.setBackgroundSize(sf::Vector2f(75,40));
    m_gravityButton.setPosition(sf::Vector2f(m_window->getSize().x - m_gravityButton.bckgShape.getSize().x, m_gravityButton.bckgShape.getSize().y));
    m_gravityButton.setTextCENTER();

    m_gravityButton.setHoverColors(sf::Color(61,61,61), sf::Color::White, sf::Color::White);
    m_gravityButton.setClickColors(sf::Color(77,77,77), sf::Color::White, sf::Color::White);

}


void GuiHandler::initClearButton()
{
    m_clearButton.setFont(*m_font);
    m_clearButton.setCharacterSize(15);
    m_clearButton.setContent("Clear");
    m_clearButton.setTextColor(sf::Color::White);
    m_clearButton.setBackgroundColor(sf::Color::Black);
    m_clearButton.setOutlineThickness(1);
    m_clearButton.setOutlineColor(sf::Color::White);
    m_clearButton.setBackgroundSize(sf::Vector2f(75,40));
    m_clearButton.setPosition(sf::Vector2f(m_constraintWidth + m_clearButton.bckgShape.getSize().x,m_clearButton.bckgShape.getSize().y ));
    m_clearButton.setTextCENTER();

    m_clearButton.setHoverColors(sf::Color(61,61,61), sf::Color::White, sf::Color::White);
    m_clearButton.setClickColors(sf::Color(77,77,77), sf::Color::White, sf::Color::White);

}

void GuiHandler::update()
{
    if(m_clearButton.onClick())
    {
        m_sim->clearEverything();
    }

    if(m_gravityButton.onClick())
    {
        m_sim->toggleGravity();
    }

}

void GuiHandler::render(sf::RenderTarget &target)
{
    target.draw(m_clearButton);
    target.draw(m_gravityButton);

    target.draw(m_boundaryPole);
}
