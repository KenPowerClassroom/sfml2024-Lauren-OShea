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

    Sprite block[1000];

    int count=0;
    for (int xRow=1;xRow<=10;xRow++)
    for (int yRow=1;yRow<=10;yRow++)
      {
         block[count].setTexture(blockTexture);
         block[count].setPosition(xRow*43,yRow*20);
         count++;
      }

    float dx=6, dy=5;
    float x=300, y=300;

    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
       }

    x+=dx;
    for (int i=0;i<count;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dx=-dx;}

    y+=dy;
    for (int i=0;i<count;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dy=-dy;}

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
