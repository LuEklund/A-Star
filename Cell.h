#pragma once
#include <SFML/Graphics.hpp>
#include "Global.hpp"

enum class CellState
{
    Empty,
    Wall,
    Pathfinding,
    Goal,
    PathfindingActive
};

class Cell
{
private:
    //sf::Vector2f        m_size;
    sf::Vector2f        m_position;
    sf::Vector2i	        m_cord;
    sf::RectangleShape  m_shape = sf::RectangleShape(sf::Vector2f(Global::CellSize, Global::CellSize));;
	CellState           m_state = CellState::Empty;

	int				 m_G = 0;
	int				 m_H = 0;
	int				 m_F = 0;

	sf::Text            m_textG;
	sf::Text            m_textH;
	sf::Text            m_textF;


public:

	Cell* Parent = nullptr;

    Cell();
    void SetPosition(int x, int y);

	int GetG() { return m_G; };
	int GetH() { return m_H; };
	int GetF() { return m_F; };

	void			 SetG(int G) { m_G = G; };
	void			 SetH(int H) { m_H = H; };
	void			 SetF(int F) { m_F = F; };

	void			 InitText(sf::Font &font);

	float DistanceToCord(sf::Vector2i Cord);

	sf::Vector2f GetPosition() { return m_position; };
	sf::Vector2i GetCord() { return m_cord; };

    //void                    SetShape(sf::RectangleShape *shape) { m_shape = shape; };
    void                   		SetState(int State);
	void					   SetState(CellState State);
	CellState			   GetState() { return m_state; };
    sf::RectangleShape      GetShape() { return (m_shape); };


	void Draw(sf::RenderWindow &window);

};

