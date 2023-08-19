#include "../include/Application.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"

const bool Application::isRunning() const
{
    return m_window->isOpen();
}

Application::~Application()
{
    delete m_window;
}


Application::Application()
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


void Application::initVariables()
{
    m_window = nullptr;
    

    m_screenWidth = sf::VideoMode::getDesktopMode().width;
    m_screenHeight = sf::VideoMode::getDesktopMode().height;


}

void Application::initWindow()
{
    m_videoMode.height = WINDOW_HEIGHT;
    m_videoMode.width = WINDOW_WIDTH;
    
    m_contextSettings.antialiasingLevel = 3;

    m_window = new sf::RenderWindow(m_videoMode, "PHYSICS!",  sf::Style::Close, m_contextSettings);
    m_window->setFramerateLimit(244);
}

void Application::initFont()
{
    if(!m_mainFont.loadFromFile("../res/fonts/open-sans/OpenSans-Regular.ttf"))
    {
        std::cerr << "ERROR::GAME::INITFONT::Failed to load main font" << '\n';
    }
}

void Application::initText()
{

}


void Application::pollEvents()
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


void Application::toggleFullscreen( )
{
    // FULLSCREEN CONTROLS

    if(m_window->hasFocus())
    {
        if(handler::InputHandler::isFClicked())
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


void Application::getInput()
{


    toggleFullscreen();
}

void Application::updateMousePos()
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    
    

}

void Application::update()
{
    pollEvents();
    getInput();
    updateMousePos();
    m_sim.simulate();

}


void Application::render()
{
    m_window->clear();

    m_sim.render(*m_window);
    m_sim.renderUI(*m_window);

    m_window->display();
}

void Application::run()
{
    m_sim.initSticks();
    while(this->isRunning())
    {
        Time::initDeltaTime();
        Time::updateFPS();

        this->update();

        this->render();

    }
}

// TODO: change to set variables for the window width and height so that the thread which runns the simulation
// no longer uses the window at all times, this means i can allow the user to change in and out of fullscreen 
// and then trigger a function in the simulation class which re-assigns the window width and heihgt
