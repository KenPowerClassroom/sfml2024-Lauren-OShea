#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

void setPos(Sprite* block, int const& NUMBER_OF_BLOCKS, float &dx, float &dy,float &x, float &y)
{

    int const SET_POSITION_X = -100;
    int const SET_POSITION_Y = 0;

    x += dx;
    for (int i = 0;i < NUMBER_OF_BLOCKS;i++)
        if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
        {
            block[i].setPosition(SET_POSITION_X, SET_POSITION_Y); dx = -dx;
        }

    y += dy;
    for (int i = 0;i < NUMBER_OF_BLOCKS;i++)
        if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
        {
            block[i].setPosition(SET_POSITION_X, SET_POSITION_Y); dy = -dy;
        }


}

void draw(RenderWindow& app, Sprite& spriteBackground, Sprite& spriteBall, Sprite& spritePaddle, Sprite* block, int const& NUMBER_OF_BLOCKS)
{
    app.clear();
    app.draw(spriteBackground);
    app.draw(spriteBall);
    app.draw(spritePaddle);

    for (int currentBlock = 0;currentBlock < NUMBER_OF_BLOCKS;currentBlock++)
    {
        app.draw(block[currentBlock]);
    }
    app.display();


}
int arkanoid()
{
    srand(time(0));

    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);

    Texture blockTexture, backgroundTexture, ballTexture, paddleTexture;
    blockTexture.loadFromFile("images/arkanoid/block01.png");
    backgroundTexture.loadFromFile("images/arkanoid/background.jpg");
    ballTexture.loadFromFile("images/arkanoid/ball.png");
    paddleTexture.loadFromFile("images/arkanoid/paddle.png");

    Sprite spriteBackground(backgroundTexture), spriteBall(ballTexture), spritePaddle(paddleTexture);
    spritePaddle.setPosition(300, 440);
    int const NUMBER_OF_BLOCKS = 100;
    int const WIDTH_OF_BLOCK = 43;
    int const HEIGHT_OF_BLOCK = 20;
    Sprite block[NUMBER_OF_BLOCKS];

    int count = 0;
    for (int column = 1;column <= 10;column++)
    {
        for (int row = 1;row <= 10;row++)
        {
            block[count].setTexture(blockTexture);
            block[count].setPosition(column * WIDTH_OF_BLOCK, row * HEIGHT_OF_BLOCK);
            count++;
        }
    }
    float dx=6, dy=5;
    float x=300, y=300;
    
    

    while (app.isOpen())
    {
        Event endGame;
        while (app.pollEvent(endGame))
        {
            if (endGame.type == Event::Closed)
                app.close();
        }

        if (x < 0 || x>520)  dx = -dx;
        if (y < 0 || y>450)  dy = -dy;

        if (Keyboard::isKeyPressed(Keyboard::Right)) spritePaddle.move(6, 0);
        if (Keyboard::isKeyPressed(Keyboard::Left)) spritePaddle.move(-6, 0);

        if (FloatRect(x, y, 12, 12).intersects(spritePaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

        setPos(block, NUMBER_OF_BLOCKS, dx, dy, x, y);

        spriteBall.setPosition(x, y);

        draw(app, spriteBackground, spriteBall, spritePaddle, block, NUMBER_OF_BLOCKS);
    }

  return 0;
}
