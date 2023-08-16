#include "../include/Game.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"

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
    WINDOW_HEIGHT(sf::VideoMode::getDesktopMode().height / 1.05)
    /*
    : WINDOW_WIDTH(sf::VideoMode::getDesktopMode().width / 1.2), 
    WINDOW_HEIGHT(sf::VideoMode::getDesktopMode().height / 1.05)
      , m_sim{}
    */
{
    initVariables();
    initWindow();
    initFont();
    initText();

    m_sim.setWindow(*m_window);
    m_sim.setSubSteps(12);

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

    m_window = new sf::RenderWindow(m_videoMode, "PHYSICS!",  sf::Style::Close, m_contextSettings);
    m_window->setFramerateLimit(244);
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
            case sf::Event::MouseWheelMoved:
                m_sim.changeMouseRadius(m_event.mouseWheel.delta);
            default:
                break;
        }
    }
}


void Game::getInput()
{
    if(m_window->hasFocus())
    {
        if(InputHandler::isFClicked())
        {
            if(!m_isKeyHeld)
            {
                m_isKeyHeld = true;

                m_videoMode.width = sf::VideoMode::getDesktopMode().width / 1.2;
                m_videoMode.height = sf::VideoMode::getDesktopMode().height / 1.05;
            
                if(m_isFullScreen)
                {
                    m_window->create(m_videoMode, "PHYSICS", sf::Style::Close, m_contextSettings);
                }
                else
                    m_window->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "PHYSICS", sf::Style::None, m_contextSettings);

                m_isFullScreen = !m_isFullScreen;
            }

        }
        else{
            m_isKeyHeld = false;
        }
    }
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
    m_sim.simulate();

}


void Game::render()
{
    m_window->clear();

    m_sim.render(*m_window);
    m_sim.renderUI(*m_window);

    m_window->display();
}

void Game::startGLoop()
{
    // m_sim.startSim();
    m_sim.initSticks();
    while(this->isRunning())
    {
        Time::initDeltaTime();
        Time::updateFPS();

        this->update();

        this->render();

    }
    // m_sim.joinUpdateThread();
}

// TODO: change to set variables for the window width and height so that the thread which runns the simulation
// no longer uses the window at all times, this means i can allow the user to change in and out of fullscreen 
// and then trigger a function in the simulation class which re-assigns the window width and heihgt
