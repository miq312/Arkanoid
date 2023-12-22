#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ball.h"
#include "paddle.h"
#include "blok.h"

using namespace sf;
using namespace std;

template <class T1, class T2> bool isIntersecting(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right()
        && A.bottom() >= B.top() && A.top() <= B.bottom();
}

bool collisionTest(Paddle& paddle, Ball& ball)
{
    if (isIntersecting(paddle, ball))
    {
        ball.moveUp();

        if (ball.getPosition().x < paddle.getPosition().x)
        {
            ball.moveLeft();
        }
        else if (ball.getPosition().x > paddle.getPosition().x)
        {
            ball.moveRight();
        }

        return true;
    }

    return false;
}

bool collisionTest(Block& block, Ball& ball)
{
    if(isIntersecting(block, ball))
    {
        block.destroy();

        float overlapleft { ball.right() - block.left()};
        float overlapright { ball.right() - block.left()};
        float overlaptop { ball.bottom() - block.top()};
        float overlapbottom { ball.bottom() - block.top()};


        bool ballFromLeft {abs(overlapleft) < abs(overlapright)};
        bool ballFromTop {abs(overlaptop) < abs(overlapbottom)};

        float minoverlapx {ballFromLeft ? overlapleft : overlapright};
        float minoverlapy {ballFromTop ? overlaptop : overlapbottom};

        if(abs(minoverlapx) < abs(minoverlapy))
        {
            ballFromLeft ? ball.moveLeft() : ball.moveRight();
        }

        else
        {
            ballFromTop ? ball.moveUp() : ball.moveDown();
        }
    }

    return false;
}

int main()
{
    Ball ball(400, 300);
    Paddle paddle(400, 550);
    RenderWindow window{VideoMode{800, 600}, "Arcanoid"};
    window.setFramerateLimit(60);
    Event event;
    unsigned blocksX {10}, blocksY {4}, blockWidth {60}, blockHeight {20};

    vector<Block> blocks;

    for(int i = 0; i < blocksY; i++)
    {
        for(int j = 0; j < blocksX; j++)
        {
            blocks.emplace_back((j + 1) * (blockWidth+12), (i + 2) * (blockHeight + 5), blockWidth, blockHeight);
        }
    }

    while (window.isOpen())
    {
        window.clear(Color::Black);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        collisionTest(paddle, ball);
        ball.update();
        paddle.update();


        for(auto& block : blocks) if(collisionTest(block, ball)) break;

        auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block ) {return block.isDestroyed();});
        blocks.erase(iterator, end(blocks));

        window.draw(ball);
        window.draw(paddle);

        for(auto& block : blocks)
            window.draw(block);

        window.display();
    }

    return 0;
}
