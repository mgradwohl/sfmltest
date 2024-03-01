#include <SFML/Graphics.hpp>

#include "Board.h"

bool drawBoard(sf::RenderWindow &window, Board const& board)
{
    window.clear();

    const uint16_t cellWidth = window.getSize().x / board.Width();

    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(cellWidth, cellWidth));
    cell.setFillColor(sf::Color::White);


    for (int i = 0; i < board.Width(); i++)
    {
        for (int j = 0; j < board.Height(); j++)
        {
            if (board.Alive(i, j))
            {
                cell.setPosition(i * cellWidth, j * cellWidth);

                window.draw(cell);
            }
        }
    }
    window.display();

    return true;
}

int main()
{
    constexpr uint16_t width = 400;
    constexpr uint16_t height = 400;
    constexpr uint16_t maxage = 1000;

    auto window = sf::RenderWindow{ { width*3, height*3 }, "CMake SFML Project" };
    window.setFramerateLimit(120);

    Board board;
    board.Resize(width, height, maxage);
    board.RandomizeBoard(0.3f, maxage);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        board.Update(1);
        drawBoard(window, board);

    }
}


