
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Main.h"



void    HandleInput(sf::View& view)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        view.move(0, -5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        view.move(0, 5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        view.move(-5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        view.move(5, 0);
    }
}


int main()
{
    static std::vector<std::vector<int>> intMatrix = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}
    };
    static std::vector<std::vector<int>> intMatrix2 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));

    Grid* grid = new Grid(intMatrix2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space)
                    grid->NewPathFind(sf::Vector2i(0, 0), sf::Vector2i(9, 9));
                if (event.key.code == sf::Keyboard::Enter)
                    grid->NextStepPathFind();
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    view.zoom(0.9f);
                }
                else if (event.mouseWheelScroll.delta < 0)
                {
                    view.zoom(1.1f);
                }
                window.setView(view);
            }
            else if (event.type == sf::Event::Closed)
                window.close();

        }

        HandleInput(view);

        //Update
        grid->Update(0.f);

        //Render
        window.setView(view);
        window.clear();
        grid->Draw(window);
        // window.draw(shape);
        window.display();
    }

    delete grid;

    return 0;
}

