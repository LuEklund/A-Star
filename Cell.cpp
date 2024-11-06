#include "Cell.h"
#include <iostream>

Cell::Cell()
{
	m_shape.setFillColor(sf::Color::White);
	m_shape.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Black);
}

void Cell::SetPosition(int x, int y)
{
	m_cord.x = x;
	m_cord.y = y;
	m_position.x = static_cast<float>(x) * Global::CellSize;
	m_position.y = static_cast<float>(y) * Global::CellSize;
	m_shape.setPosition(m_position);
	std::cout << "X: " << m_position.x << "  Y:" << m_position.y << std::endl;
}

void Cell::InitText(sf::Font &font)
{
	m_textG.setFont(font);  
	m_textG.setCharacterSize(12);  
	m_textG.setFillColor(sf::Color::Black); 
	m_textG.setPosition(m_position.x + 10, m_position.y + 10); 
	m_textG.setString("G: " + std::to_string(m_G));

	m_textH = m_textG;
	m_textH.setString("H: " + std::to_string(m_H));
	m_textH.setPosition(m_position.x + 10, m_position.y + m_textH.getLocalBounds().height + 15);


	m_textF = m_textG;
	m_textF.setCharacterSize(22);
	m_textF.setPosition(m_position.x + Global::CellSize/2 - m_textF.getGlobalBounds().width/2, m_position.y + Global::CellSize / 2 - m_textF.getGlobalBounds().height/2);
	m_textF.setString("F: " + std::to_string(m_F));
}

float Cell::DistanceToCord(sf::Vector2i Cord)
{
	sf::Vector2f diff = sf::Vector2f(m_cord - Cord); 
    return std::sqrt(diff.x * diff.x + diff.y * diff.y); 
}

void Cell::SetState(int State)
{
	m_textG.setPosition(m_position.x + 10, m_position.y + 10); 
	m_textG.setString("G: " + std::to_string(m_G));

	m_textH.setString("H: " + std::to_string(m_H));
	m_textH.setPosition(m_position.x + 10, m_position.y + m_textH.getLocalBounds().height + 15);

	m_textF.setPosition(m_position.x + Global::CellSize/2 - m_textF.getGlobalBounds().width/2, m_position.y + Global::CellSize / 2 - m_textF.getGlobalBounds().height/2);
	m_textF.setString("F: " + std::to_string(m_F));
	
	switch (State)
	{
		case 0:
			m_state = CellState::Empty;
			m_shape.setFillColor(sf::Color::White);
			break;
		case 1:
			m_state = CellState::Wall;
			m_shape.setFillColor(sf::Color(125, 125, 125));
			break;
		case 2:
			m_state = CellState::Pathfinding;
			m_shape.setFillColor(sf::Color::Yellow);
			break;
		case 3:
			m_state = CellState::Goal;
			m_shape.setFillColor(sf::Color::Green);
			break;
		case 4:
			m_state = CellState::Pathfinding;
			m_shape.setFillColor(sf::Color::Red);
			break;
		default:
			m_state = CellState::Empty;
			m_shape.setFillColor(sf::Color::White);
			break;
	}
}

void Cell::SetState(CellState State)
{
	switch (State)
	{
	case CellState::Empty:
		SetState(0);
		break;
	case CellState::Wall:
		SetState(1);
		break;
	case CellState::Pathfinding:	
		SetState(2);
		break;
	case CellState::Goal:
		SetState(3);
		break;
	case CellState::PathfindingActive:
		SetState(4);
		break;
	default:
		SetState(0);
		break;
	}
}

void Cell::Draw(sf::RenderWindow &window)
{
	window.draw(m_shape);
	window.draw(m_textG);
	window.draw(m_textH);
	window.draw(m_textF);
}
