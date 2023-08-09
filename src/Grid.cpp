#include "../include/Grid.h"
#include <cstddef>
#include <iostream>
#include <vector>

void Grid::initGrid(float gridSize, sf::RenderWindow& window)
{
    m_gridSize = gridSize;
    m_width = window.getSize().x / gridSize + 1;
    m_height = window.getSize().y / gridSize + 1;
    
    std::cout << m_height << '\n';

    m_gridMap.resize(m_width, std::vector<Cell>());
    for(std::size_t x = 0; x < m_width; ++x)
        m_gridMap[x].resize(m_height, Cell());
    
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

const std::vector<std::vector<Cell>>& Grid::getGridMap()
{
    return m_gridMap;
}
const void Grid::setIndexAtPos(uint8_t x, uint8_t y, uint8_t index)
{
    m_gridMap[x][y].indexes.push_back(index);
}
std::vector<int>& Grid::getIndexesAtPos(uint8_t x, uint8_t y)
{
    return m_gridMap[x][y].indexes;
}

const void Grid::clearGrid()
{
    for(int x = 0; x < m_width; ++x)
    for(int y = 0; y < m_height; ++y)
        m_gridMap[x][y].indexes.clear();
}
