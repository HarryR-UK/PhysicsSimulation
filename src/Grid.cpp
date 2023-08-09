#include "../include/Grid.h"
#include <cstddef>
#include <iostream>
#include <vector>


const void Grid::deleteGridMap()
{
    delete m_gridMap;
}

void Grid::initGrid(float gridSize, sf::RenderWindow& window)
{
    m_gridMap = new std::array<std::array<Cell, WIDTH>, HEIGHT>;

    m_gridSize = gridSize;
    m_width = window.getSize().x / gridSize;
    m_height = window.getSize().y / gridSize;
    
    std::cout << m_height << '\n';

    
}
const float Grid::getWidth() const
{
    return m_width;
}
const float Grid::getHeight() const
{
    return m_width;
}

const float Grid::getGridSize() const
{
    return m_gridSize;
}

std::array<std::array<Cell, Grid::WIDTH>, Grid::HEIGHT>& Grid::getGridMap()
{
    return (*m_gridMap);
}
const void Grid::setIndexAtPos(uint8_t x, uint8_t y, uint8_t index)
{
    (*m_gridMap)[x][y].indexes.push_back(index);
}
std::vector<int>& Grid::getIndexesAtPos(uint8_t x, uint8_t y)
{
    return (*m_gridMap)[x][y].indexes;
}

const void Grid::clearGrid()
{
    for(int x = 0; x < m_width; ++x)
    for(int y = 0; y < m_height; ++y)
    {
        if((*m_gridMap)[x][y].indexes.size() > 0)
            (*m_gridMap)[x][y].indexes.clear();
    }
}
