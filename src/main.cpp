#include <SFML/Graphics.hpp>

#include "Board.h"

bool drawBoard(sf::RenderWindow &window, Board const& board)
{
    window.clear();

    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(3, 3));
    cell.setFillColor(sf::Color::White);

    for (int i = 0; i < board.Width(); i++)
    {
        for (int j = 0; j < board.Height(); j++)
        {
            if (board.Alive(i, j))
            {
                cell.setPosition(i * 3, j * 3);

                window.draw(cell);
            }
        }
    }
    window.display();

    return true;
}

int main()
{
    auto window = sf::RenderWindow{ { 900u, 900u }, "CMake SFML Project" };
    window.setFramerateLimit(60);

    constexpr uint16_t width = 300;
    constexpr uint16_t height = 300;
    constexpr uint16_t maxage = 1000;

    Board board;
    board.Reserve(width * height);
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


