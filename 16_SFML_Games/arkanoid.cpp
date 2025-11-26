#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;


int arkanoid()
{
    srand(time(0));

    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);

    Texture blockTexture,backgroundTexture,ballTexture,paddleTexture;
    blockTexture.loadFromFile("images/arkanoid/block01.png");
    backgroundTexture.loadFromFile("images/arkanoid/background.jpg");
    ballTexture.loadFromFile("images/arkanoid/ball.png");
    paddleTexture.loadFromFile("images/arkanoid/paddle.png");

    Sprite spriteBackground(backgroundTexture), spriteBall(ballTexture), spritePaddle(paddleTexture);
    spritePaddle.setPosition(300,440);
    int const NUMBER_OF_BLOCKS = 100;
    int const WIDTH_OF_BLOCK = 43;
    int const HEIGHT_OF_BLOCK = 20;
    Sprite block[NUMBER_OF_BLOCKS];

    int count=0;
    for (int column=1;column<=10;column++)
    for (int row=1;row<=10;row++)
      {
         block[count].setTexture(blockTexture);
         block[count].setPosition(column*WIDTH_OF_BLOCK,row*HEIGHT_OF_BLOCK);
         count++;
      }

    float dx=6, dy=5;
    float x=300, y=300;
    int const SET_POSITION_X = -100;
    int const   SET_POSITION_Y = 0;


    while (app.isOpen())
    {
       Event endGame;
       while (app.pollEvent(endGame))
       {
         if (endGame.type == Event::Closed)
             app.close();
       }

    x+=dx;
    for (int i=0;i<count;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(setPositionX,setPositionY); dx=-dx;}

    y+=dy;
    for (int i=0;i<count;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(setPositionX,setPositionY); dy=-dy;}

    if (x<0 || x>520)  dx=-dx;
    if (y<0 || y>450)  dy=-dy;

    if (Keyboard::isKeyPressed(Keyboard::Right)) spritePaddle.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) spritePaddle.move(-6,0);

    if ( FloatRect(x,y,12,12).intersects(spritePaddle.getGlobalBounds()) ) dy=-(rand()%5+2);

    spriteBall.setPosition(x,y);

    app.clear();
    app.draw(spriteBackground);
    app.draw(spriteBall);
    app.draw(spritePaddle);

    for (int i=0;i<count;i++)
     app.draw(block[i]);

    app.display();
    }

  return 0;
}
