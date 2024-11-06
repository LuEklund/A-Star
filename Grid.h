#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


class Cell;
class Grid
{
private:
    std::vector<std::vector<Cell>>  Cells;

    std::vector<Cell*>   m_ToSearchCells;
    std::vector<Cell*>   m_SearchedCells;
    Cell*               m_StartCell;
    Cell*               m_EndCell;

	sf::Font            m_font;



public:
    Grid(int width, int height);
    Grid(std::vector<std::vector<int>> &Matrix);
    void Update(float dt);
    void Draw(sf::RenderWindow &window);
    void    NewPathFind(sf::Vector2i Start, sf::Vector2i End);
    void    NextStepPathFind();
    std::vector<Cell*> GetNeighborCells(Cell *cell);

    ~Grid();

};

