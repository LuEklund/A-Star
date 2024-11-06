#include "Grid.h"
#include "Cell.h"
#include <iostream>


Grid::Grid(int height, int width)
{
    for (int x = 0; x < width; x++)
    {
        Cells.push_back(std::vector<Cell>());
        for (int y = 0; y < height; y++)
        {
            Cells[x].push_back(Cell());
            (Cells[x].end()-1)->SetPosition(x, y);
       }
    }

}

Grid::Grid(std::vector<std::vector<int>>& Matrix)
{
    if (!m_font.loadFromFile("Assets/Bangers-Regular.ttf"))
		std::cerr << "Failed to load font!" << std::endl;
        
    for (int width = 0; width < Matrix.size(); width++)
    {
        Cells.push_back(std::vector<Cell>());
        for (int heigth = 0; heigth < Matrix[width].size(); heigth++)
        {
            Cells[width].push_back(Cell());
            (Cells[width].end()-1)->SetState(Matrix[width][heigth]);
            (Cells[width].end()-1)->SetPosition(width, heigth);
            (Cells[width].end()-1)->InitText(m_font);
        }
    }
}

void Grid::Update(float dt)
{
    for (std::vector<Cell> &Width : Cells)
    {
        for (Cell& cell : Width)
        {

        }
    }
}

void Grid::Draw(sf::RenderWindow &window)
{
    for (std::vector<Cell>& Width : Cells)
    {
        for (Cell& cell : Width)
        {
            cell.Draw(window);
        }
    }
}

void Grid::NextStepPathFind()
{
    if (m_StartCell && m_EndCell)
    {
        if (m_ToSearchCells.size() > 0)
        {
            Cell *LowestFCell = m_ToSearchCells[0];
            for (Cell *cell : m_ToSearchCells)
            {
                if (cell->GetF() < LowestFCell->GetF())
                {
                    LowestFCell = cell;
                }
                else if (cell->GetF() == LowestFCell->GetF())
                {
                    if (cell->GetH() < LowestFCell->GetH())
                    {
                        LowestFCell = cell;
                    }
                }
            }
            m_ToSearchCells.erase(std::find(m_ToSearchCells.begin(), m_ToSearchCells.end(), LowestFCell));
            m_SearchedCells.push_back(LowestFCell);
            LowestFCell->SetState(CellState::PathfindingActive);
            if (LowestFCell == m_EndCell)
            {
                std::cout << "Path Found" << std::endl;
                while (LowestFCell)
                {
                    LowestFCell->SetState(CellState::Goal);
                    LowestFCell = LowestFCell->Parent;
                }
                return;
            }
            for (Cell *neighborCell : GetNeighborCells(LowestFCell))
            {
                if (std::find(m_SearchedCells.begin(), m_SearchedCells.end(), neighborCell) != m_SearchedCells.end() || neighborCell->GetState() == CellState::Wall)
                {
                    continue;
                }
                int NewG = LowestFCell->GetG() + static_cast<int>(LowestFCell->DistanceToCord(neighborCell->GetCord()) * 10.f);
                if (NewG < neighborCell->GetG() || std::find(m_ToSearchCells.begin(), m_ToSearchCells.end(), neighborCell) == m_ToSearchCells.end())
                {
                    neighborCell->SetG(NewG);
                    neighborCell->SetH(static_cast<int>(neighborCell->DistanceToCord(m_EndCell->GetCord()) * 10.f));
                    neighborCell->SetF(neighborCell->GetG() + neighborCell->GetH());
                    neighborCell->SetState(CellState::Pathfinding);
                    neighborCell->Parent = LowestFCell;
                    if (std::find(m_ToSearchCells.begin(), m_ToSearchCells.end(), neighborCell) == m_ToSearchCells.end())
                        m_ToSearchCells.push_back(neighborCell);
                }
            }
 
        }
    }
}

std::vector<Cell *> Grid::GetNeighborCells(Cell *cell)
{
    std::vector<Cell *> Neighbors;
    if (cell)
    {
        for (int x = -1; x < 2; x++)
        {
            for (int y = -1; y < 2; y++)
            {
                if (cell->GetCord().x + x >= 0 && cell->GetCord().x + x < Cells.size() && cell->GetCord().y + y >= 0 && cell->GetCord().y + y < Cells[cell->GetCord().x].size())
                {
                    Neighbors.push_back(&Cells[cell->GetCord().x + x][cell->GetCord().y + y]);
                }
            }
            
        }
    }
    return Neighbors;
    
}

void Grid::NewPathFind(sf::Vector2i Start, sf::Vector2i End)
{
    if ((Start.x >= 0 && Start.x < Cells.size()) && (Start.y >= 0 && Start.y < Cells[Start.x].size())
        && (End.x >= 0 && End.x < Cells.size()) && (End.y >= 0 && End.y < Cells[End.x].size()))
    {
        m_StartCell = &Cells[Start.x][Start.y];
        m_EndCell = &Cells[End.x][End.y];
        m_StartCell->SetState(2);
        m_EndCell->SetState(3);
        m_ToSearchCells.push_back(m_StartCell);
    }
    else
    {
        std::cout << "Start or End is out of bounds" << std::endl;
    }
}

Grid::~Grid()
{
    for (int x = 0; x < Cells.size(); x++)
    {
        Cells[x].clear();
    }
    Cells.clear();
}
