#include "../include/Game.h"
#include <vector>

const bool Game::isRunning() const
{
    return m_window->isOpen();
}

Game::~Game()
{
    delete m_window;
}


Game::Game()
    : WINDOW_WIDTH(sf::VideoMode::getDesktopMode().width / 1.2), 
    WINDOW_HEIGHT(sf::VideoMode::getDesktopMode().height / 1.2)
{
    initVariables();
    initWindow();
    initFont();
    initText();


}


void Game::initVariables()
{
    m_window = nullptr;
    

    m_screenWidth = sf::VideoMode::getDesktopMode().width;
    m_screenHeight = sf::VideoMode::getDesktopMode().height;


}

void Game::initWindow()
{
    m_videoMode.height = WINDOW_HEIGHT;
    m_videoMode.width = WINDOW_WIDTH;
    
    m_contextSettings.antialiasingLevel = 3;

    m_window = new sf::RenderWindow(m_videoMode, "SORTING!", sf::Style::Close | sf::Style::None, m_contextSettings);
}

void Game::initFont()
{
    if(!m_mainFont.loadFromFile("../res/fonts/open-sans/OpenSans-Regular.ttf"))
    {
        std::cerr << "ERROR::GAME::INITFONT::Failed to load main font" << '\n';
    }
}

void Game::initText()
{

}


void Game::pollEvents()
{
    while(m_window->pollEvent(m_event))
    {
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
            default:
                break;
        }
    }
}


void Game::getInput()
{

}

void Game::updateMousePos()
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    
    

}

void Game::update()
{
    pollEvents();
    getInput();
    updateMousePos();
}


void Game::render()
{
    m_window->clear();


    m_window->display();
}

void Game::startGLoop()
{
    while(this->isRunning())
    {
        Time::initDeltaTime();
        Time::updateFPS();

        this->update();

        this->render();

    }
}
