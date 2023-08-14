#include "../include/Simulation.h"


Simulation::~Simulation()
{
}

Simulation::Simulation()
{


    m_objects.reserve(MAXBALLS);
    initText();
    m_mouseColShape.setRadius(m_mouseColRad);
    m_mouseColShape.setPointCount(20);
    m_mouseColShape.setFillColor(sf::Color::Transparent);
    m_mouseColShape.setOutlineThickness(1);
    m_mouseColShape.setOutlineColor(sf::Color::Red);

    /*
    for(int i = 0; i < 122; ++i)
    {
        Object& obj = addNewObject({-100,-100}, 1);
    }
     * REMOVE LATER 
     * Weird annoying gltch that makes the balls float until there are 122 balls 
    */
    
}

const void Simulation::setWindow( sf::RenderWindow& window )
{
    m_window = &window;
}
const void Simulation::setSubSteps( int substeps )
{
    m_subStepNumber = substeps;
}
const float Simulation::getSubDeltaTime( ) const
{
    return m_deltaTime / static_cast<float>(m_subStepNumber);
}
const int Simulation::getSubSteps( ) const
{
    return m_subStepNumber;
}

const float Simulation::getTime() const
{
    return m_time;
}

Object& Simulation::addNewObject( sf::Vector2f startPos, float r, bool pinned )
{
    return m_objects.emplaceBack(startPos, r, pinned); 
}

Stick& Simulation::addNewStick(int id1, int id2, float length)
{
    return m_sticks.emplaceBack(id1, id2, length);
}

void Simulation::initText()
{
    if(!m_font.loadFromFile("./res/fonts/open-sans/OpenSans-Semibold.ttf"))
    {
        std::cout << "ERROR LOADING FILE IN SIMULATION CLASS" << '\n';
    }

    m_debugText.setFillColor(sf::Color::White);
    m_debugText.setFont(m_font);
    m_debugText.setCharacterSize(20);
    m_debugText.setPosition(10,10);
    m_debugText.setString("NULL");
}


void Simulation::setDeltaTime()
{
     m_deltaTime = m_deltaTimeClock.restart().asSeconds() * MULT;
}
// UPDATING
void Simulation::updateText()
{
    std::stringstream ss;
    ss 
        << "SIM TIME: " << m_simUpdateClock.restart().asMilliseconds() << "ms" << '\n'
        << "BALLS: " << m_objects.size() << '\n'
        << "GRAVITY: " << m_gravityActive << '\n'
        << "BUILD: " << m_buildModeActive << '\n';
        ;
    m_debugText.setString(ss.str());


}

void Simulation::nonBuildModeMouseControls()
{

    if(InputHandler::isLeftMouseClicked())
    {
        if(mouseHoveringBall())
            m_grabbingBall = true;

    }
    else {
        if(m_grabbingBall)
        {
            for(auto &obj : m_objects)
            {
                if(obj.isGrabbed)
                {
                    obj.isGrabbed = false;
                    obj.outlineThic = 0;
                    // this prevents the velocity shooting the ball when paused and grabbing a ball
                    if(!m_paused)
                        obj.addVelocity(m_mouseVelocity, getSubDeltaTime());
                    else
                        obj.setVelocity(sf::Vector2f(0,0), getSubDeltaTime());

                }

            }

        }
        m_grabbingBall = false;
    }

    if(InputHandler::isRightMouseClicked())
        m_mouseColActive = true;
    else
        m_mouseColActive = false;

}

void Simulation::buildModeMouseControls()
{
    if(InputHandler::isLeftMouseClicked())
    {
            if(m_spawnClock.getElapsedTime().asSeconds() > m_spawnNewBallDelay)
            {
                Object& obj = addNewObject(m_mousePosView, m_mouseColRad, m_newBallPin);
                obj.color = getRainbowColors(getTime());
                m_spawnClock.restart();
            }
    }

    if(InputHandler::isRightMouseClicked())
    {
        if(!m_isMouseHeld)
        {
            m_isMouseHeld = true;
            int delId;
            if(mouseHoveringBall(delId))
            {
                deleteBall(delId);
            }

        }
    }
    else{
        m_isMouseHeld = false;
    }

}

void Simulation::deleteBall( int& delID )
{
    for(std::size_t i = 0; i < m_sticks.size(); ++i)
    {
        if(m_sticks[i].obj1ID == delID || m_sticks[i].obj2ID == delID)
        {
            m_sticks.deleteElementById(m_sticks[i].ID);
            i = 0;
        }
        if(m_sticks[i].obj2ID == delID || m_sticks[i].obj1ID == delID)
        {
            m_sticks.deleteElementById(m_sticks[i].ID);
            i = 0;
        }
    }

    m_objects.deleteElementById(delID);
}

void Simulation::getInput()
{
        if(!m_buildModeActive)
            nonBuildModeMouseControls();
        else if(m_objects.size() < MAXBALLS)
            buildModeMouseControls();

    if(InputHandler::isCClicked())
    {
        if(!m_isKeyHeld)
        {
            m_isKeyHeld = true;
            m_objects.clear();
        }

    }
    else if(InputHandler::isSpaceClicked())
    {
        if(!m_isKeyHeld)
        {
            m_isKeyHeld = true;
            for(auto& obj : m_objects)
                obj.setVelocity({0,0}, getSubDeltaTime());
            m_paused = !m_paused;
        }
    }
    else if(InputHandler::isGClicked())
    {
        if(!m_isKeyHeld)
        {
            m_isKeyHeld = true;
            m_gravityActive = !m_gravityActive;
        }
    }
    else if(InputHandler::isQClicked())
    {
        if(!m_isKeyHeld)
        {
            m_isKeyHeld = true;
            if(m_grabbingBall)
            {
                for(auto &obj : m_objects)
                {
                    if(obj.isGrabbed)
                        obj.togglePinned();

                }
            }
            else if(m_buildModeActive){
                m_newBallPin = !m_newBallPin;
            }

        }
    }
    else if(InputHandler::isEClicked())
    {
        if(!m_isKeyHeld)
        {
            m_isKeyHeld = true;
            m_buildModeActive = !m_buildModeActive;

        }
    }
    else{
        m_isKeyHeld = false;
    }

}

void Simulation::changeMouseRadius( float change )
{
    if(m_buildModeActive || m_mouseColActive)
    {
        m_mouseColRad += change;
        if(m_mouseColRad < m_mouseColMinRad)
            m_mouseColRad = m_mouseColMinRad;

        if(m_mouseColRad > m_mouseColMaxRad)
            m_mouseColRad = m_mouseColMaxRad;

    }
    else if(m_grabbingBall){
        for(auto &obj : m_objects)
        {
            if(obj.isGrabbed)
            {
                obj.radius += change;
                if(obj.radius < m_mouseColMinRad)
                    obj.radius = m_mouseColMinRad;

                if(obj.radius > m_mouseColMaxRad)
                    obj.radius = m_mouseColMaxRad;
            }
        }
    }

}


void Simulation::updateMousePos()
{
    m_mousePosView = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
}

void Simulation::calcMouseVelocity()
{
    // useful so that when grabbing a ball, then letting go, depending on how you throw the mouse, depends on how the ball is thrown
    m_mouseVelocity = m_mousePosView - m_mouseOldPos;
    m_mouseOldPos = m_mousePosView;
}

void Simulation::startSim( )
{
    m_updateThread = std::thread(&Simulation::simulate, this);
}

void Simulation::simulate( )
{
    /*
    while(m_window->isOpen())
    {
    */
            m_time+= m_deltaTime;
            updateText();
            setDeltaTime();
            float subStepDT = getSubDeltaTime();

            for(int i{getSubSteps()}; i > 0; --i)
            {
                if(m_window->hasFocus() && !m_paused)
                {
                    if(m_gravityActive)
                        applyGravityToObjects();
                    updateObjects( getSubDeltaTime() );
                    demoSpawner();

                }
                updateSticks();
                ballGrabbedMovement();
                checkConstraints();
                checkCollisions();
            }


    /*
    }
    */


}

void Simulation::initSticks()
{
    /*
    Object& ob = addNewObject(sf::Vector2f(100,100), 8);
    Object& ob1 = addNewObject(sf::Vector2f(150,100), 8);
    Object& ob2 = addNewObject(sf::Vector2f(150,150), 8);
    Object& ob3 = addNewObject(sf::Vector2f(100,150), 8);
    ob.color = sf::Color::Red;
    ob1.color = sf::Color::Magenta;


    Stick& s = addNewStick(ob.ID, ob1.ID, 50);
    Stick& s1 = addNewStick(ob1.ID, ob2.ID, 50);
    Stick& s2 = addNewStick(ob2.ID, ob3.ID, 50);
    Stick& s3 = addNewStick(ob3.ID, ob.ID, 50);
    sf::Vector2f axis = ob3.currentPos - ob1.currentPos;
    float dist = sqrt(axis.x * axis.x + axis.y * axis.y);
    Stick& s4 = addNewStick(ob3.ID, ob1.ID, dist);

*/

    int tempMax = m_objects.size();
    for(int i = 0; i < 51; ++i)
    {
        Object& ob = addNewObject(sf::Vector2f(200 + (i * 20), 400), 8);
        if(i == 0 || i == 50)
        {
            ob.isPinned = true;
            ob.color = sf::Color::Red;
        }
        if(i == 0)
        {
            continue;
        }

        Stick& s = addNewStick(m_objects[tempMax + (i-1)].ID, m_objects[tempMax + i].ID, 20);

    }

}

void Simulation::updateSticks()
{
    for(auto& stick : m_sticks)
    {
        stick.update(m_objects.getById(stick.obj1ID), m_objects.getById(stick.obj2ID));
    }
}

void Simulation::updateUI()
{
    if(m_window->hasFocus())
    {
        getInput();
    }
    updateMousePos();
    calcMouseVelocity();
    
}

void Simulation::joinUpdateThread()
{
    m_updateThread.join();
}

bool Simulation::mouseHoveringBall()
{
    for(auto &obj: m_objects)
    {
        sf::Vector2f axis = m_mousePosView - obj.currentPos;
        float dist = sqrt(axis.x * axis.x + axis.y * axis.y);
        
        if(dist < obj.radius && !m_grabbingBall)
        {
            obj.isGrabbed = true;
            obj.outlineThic = 1;
            return true;
        }
    }

    return false;
}
bool Simulation::mouseHoveringBall( int& delteID )
{
    for(auto &obj: m_objects)
    {
        sf::Vector2f axis = m_mousePosView - obj.currentPos;
        float dist = sqrt(axis.x * axis.x + axis.y * axis.y);
        
        if(dist < obj.radius && !m_grabbingBall)
        {
            delteID = obj.ID;
            return true;
        }
    }

    return false;
}

void Simulation::ballGrabbedMovement()
{
    for(auto &obj : m_objects)
    {
        if(obj.isGrabbed)
        {
            if(obj.isPinned)
                obj.outlineColor = sf::Color::Green;
            else
                obj.outlineColor = sf::Color::White;
            obj.outlineThic = 1;
            obj.currentPos = m_mousePosView;
        }
    }
}

sf::Color Simulation::getRainbowColors( float time )
{
    float red = sin(time);
    float green = sin(time + 0.3f * 2);
    float blue = sin(time + 0.6f * 2.0);


    return sf::Color( 
        static_cast<unsigned>(red * red * 255),
        static_cast<unsigned>(green * green * 255),
        static_cast<unsigned>(blue * blue * 255)
            );
}

void Simulation::demoSpawner()
{
    sf::Vector2f spawnPos = {m_window->getSize().x * 0.5f, m_window->getSize().y * 0.25f};
    int maxBalls = 300;
    float spawnDelay = 0.05f;
    float spawnSpeed = 40;
    int minRad = 6;
    int maxRad = 16;

    if(m_objects.size() < maxBalls && m_clock.getElapsedTime().asSeconds() >= spawnDelay)
    {
        m_clock.restart().asSeconds();
        Object& ob = addNewObject(spawnPos, (rand() % maxRad) + minRad);

        float time = getTime();
        
        float angle =  time * 3.1415936 * 0.05;

        ob.addVelocity( spawnSpeed * sf::Vector2f(cos(angle), sin(angle)), getSubDeltaTime());
        ob.color = getRainbowColors(time);

    }


}

void Simulation::checkConstraints()
{
    for(auto &obj : m_objects)
    {
        float winWidth = m_window->getSize().x;
        float winHeight = m_window->getSize().y;
        sf::Vector2f veloc = obj.currentPos - obj.oldPos;
        if(obj.currentPos.x > winWidth - obj.radius)
        {
            obj.currentPos.x = winWidth - obj.radius;
            //obj.oldPos.x = obj.currentPos.x + veloc.x * obj.friction;
        }
        if(obj.currentPos.x < obj.radius)
        {
            obj.currentPos.x = obj.radius;
            // obj.oldPos.x = obj.currentPos.x + veloc.x * obj.friction;
        }
        if(obj.currentPos.y < obj.radius)
        {
            obj.currentPos.y = obj.radius;
            // obj.oldPos.y = obj.currentPos.y + veloc.y * obj.friction;
        }
        if(obj.currentPos.y > winHeight - obj.radius)
        {
            obj.currentPos.y = winHeight - obj.radius;
            // obj.oldPos.y = obj.currentPos.y + veloc.y * obj.friction;
        }
    }
}

void Simulation::checkCollisions()
{

    for(std::size_t i = 0; i < m_objects.size(); ++i)
    {
        Object& obj1 = m_objects[i];
        for(std::size_t j = i + 1; j < m_objects.size(); ++j)
        {
            Object& obj2 = m_objects[j];
            sf::Vector2f axis = obj1.currentPos - obj2.currentPos;
            float distanceBtw = sqrt(axis.x * axis.x + axis.y * axis.y);
            float minAllowedDist = obj1.radius + obj2.radius;
            if(distanceBtw < minAllowedDist)
            {
                float moveAmount = minAllowedDist - distanceBtw;
                float percentage = (moveAmount / distanceBtw) * 0.5;
                sf::Vector2f offsetAmount = axis * percentage;

                if(!obj1.isPinned)
                    obj1.currentPos += offsetAmount;
                if(!obj2.isPinned)
                    obj2.currentPos -= offsetAmount;
            }
        }
    }

    mouseCollisionsBall();
}

void Simulation::mouseCollisionsBall()
{
    if(m_mouseColActive)
    {
        for(auto &obj : m_objects)
        {
            sf::Vector2f axis = m_mousePosView - obj.currentPos;
            float dist = sqrt(axis.x * axis.x + axis.y * axis.y);
            float minDist = m_mouseColRad + obj.radius;
            if(dist < minDist)
            {
                if(!obj.isPinned)
                {
                    float moveAmount = minDist - dist;
                    float perc = (moveAmount / dist) * 0.5;
                    sf::Vector2f off = axis * perc;
                    obj.currentPos -= off;
                }
            }

        }
    }
}

void Simulation::updateObjects( float subDeltaTime )
{
    for( auto &obj : m_objects)
    {
        if(!obj.isPinned)
            obj.update(subDeltaTime);
    }
}

void Simulation::applyGravityToObjects( )
{
   
    
    if(m_gravityActive)
    {
        for(auto &obj : m_objects)
        {
            obj.accelerate( obj.mass * GRAVITY);
        }

    }
}


// RENDERING
void Simulation::render( sf::RenderTarget &target )
{

    renderSticks(target);

    sf::CircleShape circleS;
    circleS.setPointCount(30);
    sf::CircleShape pinShape;
    for(auto &obj : m_objects)
    {
        circleS.setRadius(obj.radius);
        circleS.setOrigin(obj.radius, obj.radius);
        circleS.setFillColor(obj.color);
        circleS.setPosition(obj.currentPos);
        circleS.setOutlineColor(obj.outlineColor);
        circleS.setOutlineThickness(obj.outlineThic);
        target.draw(circleS);
        
        if(obj.isPinned)
        {
            pinShape.setFillColor(sf::Color::Red);
            pinShape.setOutlineThickness(1);
            pinShape.setOutlineColor(sf::Color::Black);
            pinShape.setRadius((circleS.getRadius() * 0.2) - pinShape.getOutlineThickness());
            pinShape.setOrigin(pinShape.getRadius(), pinShape.getRadius());
            pinShape.setPosition(circleS.getPosition());

            target.draw(pinShape);
        }

    }

    if(m_buildModeActive || m_mouseColActive)
    {
        float newRad = m_mouseColRad - m_mouseColShape.getOutlineThickness();
        m_mouseColShape.setRadius(newRad);
        m_mouseColShape.setOrigin(newRad, newRad);
        m_mouseColShape.setPosition(m_mousePosView);

        if(m_mouseColActive)
            m_mouseColShape.setOutlineColor(sf::Color::Red);
        else if(m_buildModeActive)
        {
            if(m_newBallPin)
                m_mouseColShape.setOutlineColor(sf::Color::Green);
            else
                m_mouseColShape.setOutlineColor(sf::Color(0, 128, 255));
        }


        target.draw(m_mouseColShape);
    }
}

void Simulation::renderSticks(sf::RenderTarget &target)
{
    for(auto &stick : m_sticks)
    {
        sf::Vertex lines[2];
        lines[0].position = m_objects.getById(stick.obj1ID).currentPos;
        lines[0].color = m_objects.getById(stick.obj1ID).color;
        lines[1].position = m_objects.getById(stick.obj2ID).currentPos;
        lines[1].color = m_objects.getById(stick.obj2ID).color;

        target.draw(lines, 2, sf::LineStrip);

    }
}

void Simulation::renderUI( sf::RenderTarget &target )
{
    target.draw(m_debugText);
}
