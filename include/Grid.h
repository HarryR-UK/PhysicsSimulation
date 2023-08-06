#ifndef GRID_H
#define GRID_H

#include "SFML/Graphics/RenderWindow.hpp"
#include <vector>
#pragma once

struct Cell
{
    // cell needs to store all indexes of the VerletObjects that are in that potision
    std::vector<int> indexes;
};

class Grid
{
    private:
        std::vector<std::vector<Cell>> m_gridMap;

        // should be the balls diameter (radius * 2)
        float m_gridSize = 0;


    public:
        Grid();
        ~Grid();

        // windowsize / sizeOfDiameter is the number of blocks (resize the vector)
        const void setGridSize(sf::RenderWindow& window, float sizeOfDiameter);

        // provide the x coord and y coord of current search, and return what indexes the cell holds
        const Cell& getIndexesAtCell(int x, int y) const;

        // will add the objects index to the array
        const void setIndexesAtCell(int x, int y, int index);
    
};


#endif // !GRID_H
