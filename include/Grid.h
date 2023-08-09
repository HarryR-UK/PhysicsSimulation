#ifndef GRID_H
#define GRID_H
#include "Global.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <_types/_uint8_t.h>
#include <array>
#include <sys/types.h>
#include <vector>

#pragma once

struct Cell
{
    std::vector<int> indexes = {};
};


class Grid
{
    private:
        static const int WIDTH = 1500 / BALL_RADIUS;
        static const int HEIGHT = 1050 / BALL_RADIUS ;
        std::array<std::array<Cell,WIDTH >, HEIGHT>* m_gridMap;
        float m_gridSize = 0;
        float m_width = 0;
        float m_height = 0;
    private:


    public:

    public:
        void initGrid(float gridSize, sf::RenderWindow& window);
        const float getWidth() const;
        const float getHeight() const;
        const float getGridSize() const;
        std::array<std::array<Cell, WIDTH>,HEIGHT>& getGridMap();
        const void setIndexAtPos(uint8_t x, uint8_t y, uint8_t index);
        std::vector<int>& getIndexesAtPos(uint8_t x, uint8_t y);
        const void clearGrid();
        const void deleteGridMap();


};



#endif // !GRID_H
