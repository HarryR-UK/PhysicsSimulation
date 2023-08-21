#include "../include/GuiHandler.h"
#include <iterator>
using namespace handler;

GuiHandler::GuiHandler( pe::Simulation& sim )
{
    m_sim = &sim;
    initButtons();
}

GuiHandler::~GuiHandler()
{
    delete m_font;
}

void GuiHandler::initButtons()
{
    m_font = new sf::Font;
    if(!m_font->loadFromFile("../res/fonts/open-sans/OpenSans-Semibold.ttf")) std::cout << "ERROR LOADING FONT!" << '\n';
    m_clearButton.setFont(*m_font);
    m_clearButton.setCharacterSize(15);
    m_clearButton.setContent("Clear");
    m_clearButton.setTextColor(sf::Color::White);
    m_clearButton.setBackgroundColor(sf::Color::Black);
    m_clearButton.setOutlineThickness(1);
    m_clearButton.setOutlineColor(sf::Color::White);
    m_clearButton.setPosition(sf::Vector2f(400,100));
    m_clearButton.setBackgroundSize(sf::Vector2f(75,40));
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

}

void GuiHandler::render(sf::RenderTarget &target)
{
    target.draw(m_clearButton);
}
