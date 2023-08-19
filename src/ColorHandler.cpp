#include "../include/ColorHandler.h"

using namespace handler;
const sf::Color ColorHandler::getRainbowColors( float time )
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
