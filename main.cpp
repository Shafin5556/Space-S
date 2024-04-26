#include <windows.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;


float starYPos = 100.0f; // Initial y-position of stars
int numStarsDrawn = 0; // Number of stars drawn
int numSegments = 1000; // Number of segments to divide the window width


GLfloat xPosition = 0;
GLfloat yPosition = 0;
GLfloat bulletY = 0.0f;
bool shooting = false;
std::vector<std::pair<GLfloat, GLfloat>> bullets;


int numGroups = 5; // Number of groups of stars
int numStarsPerGroup = 10; // Number of stars per group
//float starYPos = 100.0f; // Initial y-position of stars
//int numStarsDrawn = 0; // Number of stars drawn in current group
int currentGroup = 0; // Index of current group

struct Star {
    float x;
    float y;
    float size;
    float r;
    float g;
    float b;
};

Star stars[50]; // Array to store stars



class Bullet {
public:
    GLfloat x;
    GLfloat y;
    Bullet(GLfloat x, GLfloat y) : x(x), y(y) {}
};

//std::vector<Bullet> bullets;


void renderBitmapString(float x, float y, float z, void *font, char *string) {
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}



struct Point {
    float x, y;
};

struct Laser {
    Point position;
    float speed;
    bool active;
};

struct Enemy {
    Point position;
    bool active;
};




void spaceShip();
void drawBullets();

void star(float x, float y, float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glPointSize(size);
    glBegin(GL_POINTS);
    /*
    glVertex2f(x + 1.5, y + 2.5);
    glVertex2f(x + 5.0, y + 2.5);
    glVertex2f(x + 2.0, y);
    glVertex2f(x + 3.5, y - 4.0);
    glVertex2f(x, y - 2.0);
    glVertex2f(x - 3.5, y - 4.0);
    glVertex2f(x - 2.0, y);
    glVertex2f(x - 5.0, y + 2.5);
    glVertex2f(x - 1.5, y + 2.5);
    glVertex2f(x, y + 6.0);


    */
    /*

    glVertex2f(x + 0.125, y + 0.625);
    glVertex2f(x + 1.25, y + 0.625);
    glVertex2f(x + 0.5, y);
    glVertex2f(x + 0.875, y - 1.0);
    glVertex2f(x, y - 0.5);
    glVertex2f(x - 0.875, y - 1.0);
    glVertex2f(x - 0.5, y);
    glVertex2f(x - 1.25, y + 0.625);
    glVertex2f(x - 0.125, y + 0.625);
    glVertex2f(x, y + 1.5);

    */



}
/*
void drawStars(int numStars) {
    srand(time(NULL));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < numStars; ++i) {
        float x = rand() % 200 - 100; // Random x-coordinate within window bounds
        float y = rand() % 200 - 100; // Random y-coordinate within window bounds
        float size = (rand() % 100) / 100.0f; // Random size between 1 and 10
        float r = (rand() % 256) / 255.0f; // Random red component
        float g = (rand() % 256) / 255.0f; // Random green component
        float b = (rand() % 256) / 255.0f; // Random blue component

        star(x, y, size, r, g, b);
    }
}
*/

void drawStars(int numStars) {
    srand(time(NULL));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < numStars; ++i) {
        float x = rand() % 200 - 100; // Random x-coordinate within window bounds
        float y = starYPos - rand() % 10; // Decrease y-coordinate based on starYPos
        float size = (rand() % 100) / 100.0f; // Random size between 0 and 1
        float r = (rand() % 256) / 255.0f; // Random red component
        float g = (rand() % 256) / 255.0f; // Random green component
        float b = (rand() % 256) / 255.0f; // Random blue component

        star(x, y, size, r, g, b);
        numStarsDrawn ++;
    }
}


void drawStar() {
    srand(time(NULL));
    float segmentWidth = 200.0f / numSegments; // Width of each segment
    float x = (rand() % numSegments) * segmentWidth - 100 + segmentWidth / 2; // Random x-coordinate within each segment
    float y = starYPos - rand() % 10; // Decrease y-coordinate based on starYPos
    float size = (rand() % 100) / 100.0f; // Random size between 0 and 1
    float r = (rand() % 256) / 255.0f; // Random red component
    float g = (rand() % 256) / 255.0f; // Random green component
    float b = (rand() % 256) / 255.0f; // Random blue component

    star(x, y, size, r, g, b);
    numStarsDrawn++;
}

void drawStars1(float x, float y, float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glPointSize(size);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.3, y + 0.0);
    glVertex2f(x  +0.0, y - 0.3);
    glVertex2f(x - 0.3, y  +0.0);
    glVertex2f(x  +0.0, y + 0.3);
    glEnd();
}

void generateStars() {
    srand(time(NULL));
    float segmentWidth = 200.0f / numGroups; // Width of each segment
    float x = (rand() % numStarsPerGroup) * (segmentWidth / numStarsPerGroup) + currentGroup * segmentWidth - 100 + (segmentWidth / (2 * numStarsPerGroup)); // Random x-coordinate within each segment
    float y = starYPos - rand() % 10; // Decrease y-coordinate based on starYPos
    float size = (rand() % 100) / 100.0f; // Random size between 0 and 1
    float r = (rand() % 256) / 255.0f; // Random red component
    float g = (rand() % 256) / 255.0f; // Random green component
    float b = (rand() % 256) / 255.0f; // Random blue component

    stars[numStarsDrawn].x = x;
    stars[numStarsDrawn].y = y;
    stars[numStarsDrawn].size = size;
    stars[numStarsDrawn].r = r;
    stars[numStarsDrawn].g = g;
    stars[numStarsDrawn].b = b;
    numStarsDrawn++;
}
/*
void spaceShip()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0, -5.0);
    glVertex2f(-1.5, -5.0);
    glVertex2f(-1.5, -4.5);
    glVertex2f(-2.0, -4.5);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(2.0, -5.0);
    glVertex2f(1.5, -5.0);
    glVertex2f(1.5, -4.5);
    glVertex2f(2.0, -4.5);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(1.5, -5.0);
    glVertex2f(1.0, -5.0);
    glVertex2f(1.0, -4.5);
    glVertex2f(1.5, -4.5);
    glEnd();
}
*/

void spaceShip()
{


    glPushMatrix();
    glTranslatef(xPosition,yPosition,0.0);

    //white background

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -22.0);
    glVertex2f(1.0, -22.0);
    glVertex2f(1.0, -45.0);
    glVertex2f(-1.0, -45.0);

    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0, -26.0);
    glVertex2f(2.0, -26.0);
    glVertex2f(2.0, -45.0);
    glVertex2f(-2.0, -45.0);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-3.0, -30.0);
    glVertex2f(3.0, -30.0);
    glVertex2f(3.0, -45.0);
    glVertex2f(-3.0, -45.0);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0, -34.0);
    glVertex2f(4.0, -34.0);
    glVertex2f(4.0, -45.0);
    glVertex2f(-4.0, -45.0);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-5.0, -38.0);
    glVertex2f(5.0, -38.0);
    glVertex2f(5.0, -45.0);
    glVertex2f(-5.0, -45.0);

    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0, -42.0);
    glVertex2f(6.0, -42.0);
    glVertex2f(6.0, -45.0);
    glVertex2f(-6.0, -45.0);

    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-7.0, -44.0);
    glVertex2f(7.0, -44.0);
    glVertex2f(7.0, -45.0);
    glVertex2f(-7.0, -45.0);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-8.0, -46.0);
    glVertex2f(8.0, -46.0);
    glVertex2f(8.0, -45.0);
    glVertex2f(-8.0, -45.0);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-9.0, -47.0);
    glVertex2f(-4.0, -47.0);
    glVertex2f(-4.0, -46.0);
    glVertex2f(-9.0, -46.0);

    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-10.0, -48.0);
    glVertex2f(-6.0, -48.0);
    glVertex2f(-6.0, -47.0);
    glVertex2f(-10.0, -47.0);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-11.0, -49.0);
    glVertex2f(-8.0, -49.0);
    glVertex2f(-8.0, -48.0);
    glVertex2f(-11.0, -48.0);

    glEnd();



    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(9.0, -47.0);
    glVertex2f(4.0, -47.0);
    glVertex2f(4.0, -46.0);
    glVertex2f(9.0, -46.0);

    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(10.0, -48.0);
    glVertex2f(6.0, -48.0);
    glVertex2f(6.0, -47.0);
    glVertex2f(10.0, -47.0);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(11.0, -49.0);
    glVertex2f(8.0, -49.0);
    glVertex2f(8.0, -48.0);
    glVertex2f(11.0, -48.0);

    glEnd();







    //side borders, all will be black

    //lower half of the spaceship

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-12.0, -50.0);
    glVertex2f(-8.0, -50.0);
    glVertex2f(-8.0, -49.0);
    glVertex2f(-12.0, -49.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(12.0, -50.0);
    glVertex2f(8.0, -50.0);
    glVertex2f(8.0, -49.0);
    glVertex2f(12.0, -49.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-8.0, -49.0);
    glVertex2f(-6.0, -49.0);
    glVertex2f(-6.0, -48.0);
    glVertex2f(-8.0, -48.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0, -48.0);
    glVertex2f(-4.0, -48.0);
    glVertex2f(-4.0, -47.0);
    glVertex2f(-6.0, -47.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0, -47.0);
    glVertex2f(-2.0, -47.0);
    glVertex2f(-2.0, -46.0);
    glVertex2f(-4.0, -46.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0, -46.0);
    glVertex2f(2.0, -46.0);
    glVertex2f(2.0, -45.0);
    glVertex2f(-2.0, -45.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(8.0, -49.0);
    glVertex2f(6.0, -49.0);
    glVertex2f(6.0, -48.0);
    glVertex2f(8.0, -48.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(6.0, -48.0);
    glVertex2f(4.0, -48.0);
    glVertex2f(4.0, -47.0);
    glVertex2f(6.0, -47.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.0, -47.0);
    glVertex2f(2.0, -47.0);
    glVertex2f(2.0, -46.0);
    glVertex2f(4.0, -46.0);

    glEnd();

    //upper half of the body on both side


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-12.0, -49.0);
    glVertex2f(-11.0, -49.0);
    glVertex2f(-11.0, -48.0);
    glVertex2f(-12.0, -48.0);

    glEnd();



    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-11.0, -48.0);
    glVertex2f(-10.0, -48.0);
    glVertex2f(-10.0, -47.0);
    glVertex2f(-11.0, -47.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-10.0, -47.0);
    glVertex2f(-9.0, -47.0);
    glVertex2f(-9.0, -46.0);
    glVertex2f(-10.0, -46.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-9.0, -46.0);
    glVertex2f(-8.0, -46.0);
    glVertex2f(-8.0, -45.0);
    glVertex2f(-9.0, -45.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-8.0, -45.0);
    glVertex2f(-7.0, -45.0);
    glVertex2f(-7.0, -44.0);
    glVertex2f(-8.0, -44.0);

    glEnd();





    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(12.0, -49.0);
    glVertex2f(11.0, -49.0);
    glVertex2f(11.0, -48.0);
    glVertex2f(12.0, -48.0);
    glEnd();



    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(11.0, -48.0);
    glVertex2f(10.0, -48.0);
    glVertex2f(10.0, -47.0);
    glVertex2f(11.0, -47.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(10.0, -47.0);
    glVertex2f(9.0, -47.0);
    glVertex2f(9.0, -46.0);
    glVertex2f(10.0, -46.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(9.0, -46.0);
    glVertex2f(8.0, -46.0);
    glVertex2f(8.0, -45.0);
    glVertex2f(9.0, -45.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(8.0, -45.0);
    glVertex2f(7.0, -45.0);
    glVertex2f(7.0, -44.0);
    glVertex2f(8.0, -44.0);

    glEnd();


    //upper half of the body

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-7.0, -44.0);
    glVertex2f(-6.0, -44.0);
    glVertex2f(-6.0, -42.0);
    glVertex2f(-7.0, -42.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0, -42.0);
    glVertex2f(-5.0, -42.0);
    glVertex2f(-5.0, -38.0);
    glVertex2f(-6.0, -38.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-5.0, -38.0);
    glVertex2f(-4.0, -38.0);
    glVertex2f(-4.0, -34.0);
    glVertex2f(-5.0, -34.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0, -34.0);
    glVertex2f(-3.0, -34.0);
    glVertex2f(-3.0, -30.0);
    glVertex2f(-4.0, -30.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-3.0, -30.0);
    glVertex2f(-2.0, -30.0);
    glVertex2f(-2.0, -26.0);
    glVertex2f(-3.0, -26.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0, -26.0);
    glVertex2f(-1.0, -26.0);
    glVertex2f(-1.0, -22.0);
    glVertex2f(-2.0, -22.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -22.0);
    glVertex2f(1.0, -22.0);
    glVertex2f(1.0, -18.0);
    glVertex2f(-1.0, -18.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(7.0, -44.0);
    glVertex2f(6.0, -44.0);
    glVertex2f(6.0, -42.0);
    glVertex2f(7.0, -42.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(6.0, -42.0);
    glVertex2f(5.0, -42.0);
    glVertex2f(5.0, -38.0);
    glVertex2f(6.0, -38.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(5.0, -38.0);
    glVertex2f(4.0, -38.0);
    glVertex2f(4.0, -34.0);
    glVertex2f(5.0, -34.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.0, -34.0);
    glVertex2f(3.0, -34.0);
    glVertex2f(3.0, -30.0);
    glVertex2f(4.0, -30.0);

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(3.0, -30.0);
    glVertex2f(2.0, -30.0);
    glVertex2f(2.0, -26.0);
    glVertex2f(3.0, -26.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(2.0, -26.0);
    glVertex2f(1.0, -26.0);
    glVertex2f(1.0, -22.0);
    glVertex2f(2.0, -22.0);

    glEnd();




    //blue core

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -34.0);
    glVertex2f(1.0, -34.0);
    glVertex2f(1.0, -32.0);
    glVertex2f(-1.0, -32.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0, -38.0);
    glVertex2f(2.0, -38.0);
    glVertex2f(2.0, -34.0);
    glVertex2f(-2.0, -34.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-3.0, -38.0);
    glVertex2f(3.0, -38.0);
    glVertex2f(3.0, -43.0);
    glVertex2f(-3.0, -43.0);

    glEnd();


    // red texture, lower half


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-8.0, -48.0);
    glVertex2f(-7.0, -48.0);
    glVertex2f(-7.0, -47.0);
    glVertex2f(-8.0, -47.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-7.0, -47.0);
    glVertex2f(-5.0, -47.0);
    glVertex2f(-5.0, -46.0);
    glVertex2f(-7.0, -46.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0, -46.0);
    glVertex2f(-4.0, -46.0);
    glVertex2f(-4.0, -45.0);
    glVertex2f(-6.0, -45.0);

    glEnd();



    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(8.0, -48.0);
    glVertex2f(7.0, -48.0);
    glVertex2f(7.0, -47.0);
    glVertex2f(8.0, -47.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(7.0, -47.0);
    glVertex2f(5.0, -47.0);
    glVertex2f(5.0, -46.0);
    glVertex2f(7.0, -46.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(6.0, -46.0);
    glVertex2f(4.0, -46.0);
    glVertex2f(4.0, -45.0);
    glVertex2f(6.0, -45.0);

    glEnd();



    //red texture upper half

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-3.0, -44.0);
    glVertex2f(3.0, -44.0);
    glVertex2f(3.0, -43.0);
    glVertex2f(-3.0, -43.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -30.0);
    glVertex2f(1.0, -30.0);
    glVertex2f(1.0, -27.0);
    glVertex2f(-1.0, -27.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -32.0);
    glVertex2f(1.0, -32.0);
    glVertex2f(1.0, -31.0);
    glVertex2f(-1.0, -31.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0, -43.0);
    glVertex2f(-3.0, -43.0);
    glVertex2f(-3.0, -38.0);
    glVertex2f(-4.0, -38.0);

    glEnd();



    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-3.0, -38.0);
    glVertex2f(-2.0, -38.0);
    glVertex2f(-2.0, -34.0);
    glVertex2f(-3.0, -34.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0, -34.0);
    glVertex2f(-1.0, -34.0);
    glVertex2f(-1.0, -32.0);
    glVertex2f(-2.0, -32.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.0, -43.0);
    glVertex2f(3.0, -43.0);
    glVertex2f(3.0, -38.0);
    glVertex2f(4.0, -38.0);

    glEnd();



    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(3.0, -38.0);
    glVertex2f(2.0, -38.0);
    glVertex2f(2.0, -34.0);
    glVertex2f(3.0, -34.0);

    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(2.0, -34.0);
    glVertex2f(1.0, -34.0);
    glVertex2f(1.0, -32.0);
    glVertex2f(2.0, -32.0);

    glEnd();
    glPopMatrix();


    /*

    // Draw bullets
    glColor3f(1.0f, 0.0f, 0.0f); // Blue color for bullets
    for (const auto& bullet : bullets) {
        glBegin(GL_QUADS);
        glVertex2f(bullet.x - 10.2f, bullet.y); // Adjust size and position as needed
        glVertex2f(bullet.x + 10.2f, bullet.y);
        glVertex2f(bullet.x + 10.2f, bullet.y + 10.2f);
        glVertex2f(bullet.x - 10.02f, bullet.y + 10.2f);
        glEnd();
    }

    // Move bullets upward
    for (auto& bullet : bullets) {
        bullet.y += 0.05f;
    }

    // Remove bullets that are out of bounds
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),[](const Bullet& bullet) { return bullet.y > 1.0f; }), bullets.end());

*/








}



void drawBullets() {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for bullets
    for (const auto& bullet : bullets) {
        glPushMatrix(); // Save current matrix
        glTranslatef(bullet.first, bullet.second, 0.0f);

        // Draw bullet rectangle
        /*
        glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.0f);
        glVertex2f(0.02f, 0.0f);
        glVertex2f(0.02f, 0.2f);
        glVertex2f(-0.02f, 0.2f);
        glEnd();
        */

        //glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(-0.5, -24.0);
        glVertex2f(0.5, -24.0);
        glVertex2f(0.5, -22.0);
        glVertex2f(-0.5, -22.0);

        glEnd();

        glPopMatrix(); // Restore previous matrix
    }
}




void display() {
    glClearColor(0.85f, 0.85f, 0.9f, 1.0f);
    glClearColor(0.1294f, 0.1294f, 0.1294f, 1.0f);
 // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
    glLoadIdentity();


    for (int i = 0; i < numStarsDrawn; ++i) {
        drawStars1(stars[i].x, stars[i].y, stars[i].size, stars[i].r, stars[i].g, stars[i].b);
    }

    //drawStars(1000); // Draw 100 stars
    //drawStar();
    spaceShip();
    drawBullets();


    glFlush(); // Render now
    glutSwapBuffers();

}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            yPosition += 0.1f; // Move up
            break;
        case GLUT_KEY_DOWN:
            yPosition -= 0.1f; // Move down
            break;
        case GLUT_KEY_LEFT:
            xPosition -= 0.1f; // Move left
            break;
        case GLUT_KEY_RIGHT:
            xPosition += 0.1f; // Move right
            break;
    }

    glutPostRedisplay(); // Redraw the scene
}
/*
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 13: // ASCII code for Enter key
            // Start shooting when Enter key is pressed
            shooting = true;
            cout<<"shooting Started"<<endl;
            break;
    }
}
*/

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 13: // ASCII code for Enter key
            // Start shooting when Enter key is pressed
            shooting = true;
            // Calculate the position of the tip of the spaceship
            GLfloat tipX = xPosition;
            GLfloat tipY = yPosition + 5.0f; // Assuming the spaceship height is 32.0f
            bullets.push_back(std::make_pair(tipX, tipY)); // Create bullet at the tip position
            break;
    }
}

/*
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 13: // ASCII code for Enter key
            // Start shooting bullets
            shooting = true;
            // Calculate the position of the tip of the spaceship
            GLfloat tipX = xPosition;
            GLfloat tipY = yPosition + 32.0f; // Assuming the spaceship height is 32.0f
            bullets.push_back(std::make_pair(tipX, tipY)); // Create bullet at the tip position
            break;
    }
}
*/


void update(int value) {
    if (shooting) {
        // Create new bullets when shooting is active
        for (auto& bullet : bullets) {
            // Move bullets upward
            bullet.second += 0.1f; // Adjust the value as needed
        }
    }

    glutPostRedisplay();
    // Move stars down by decrementing starYPos
    starYPos -= 1.0f;
    glutPostRedisplay();
    //glutTimerFunc(25, update, 0); // Update every 25 milliseconds
    glutTimerFunc(16, update, 0);
    // Draw next star if not all stars are drawn
    /*
    if (numStarsDrawn < 100) {
        drawStar();
    }
    */

    // Draw next star if not all stars are drawn
    if (numStarsDrawn < numStarsPerGroup * numGroups) {
        generateStars();
    } else {
        // Reset for next group of stars
        starYPos = 100.0f;
        numStarsDrawn = 0;
        currentGroup = (currentGroup + 1) % numGroups;
    }
}


/*
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 13: // ASCII code for Enter key
            // Start shooting bullets
            shooting = true;
            bullets.push_back(std::make_pair(xPosition, yPosition));
            break;
    }
}
*/

/*

void update(int value) {
    if (shooting) {
        // Create new bullets when shooting is active
        bullets.push_back(std::make_pair(xPosition, yPosition));
    }

    // Move bullets
    for (auto& bullet : bullets) {
        // Update both x and y coordinates
        bullet.first += 0.0f; // No movement in x-direction
        bullet.second += 0.1f; // Move upward
        cout<<"Bullets moving upward"<<endl;
    }

    // Remove bullets that are out of bounds
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                  [](const std::pair<GLfloat, GLfloat>& bullet) {
                                      return bullet.second > 1.0f;
                                  }), bullets.end());
                                  cout<<"Bullets Removed"<<endl;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

*/

/*
void update(int value) {
    // Move bullets upward
    for (auto& bullet : bullets) {
        bullet.second += 0.05f;
    }

    // Remove bullets that are out of bounds
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                  [](const std::pair<GLfloat, GLfloat>& bullet) {
                                      return bullet.second > 1.0f;
                                  }), bullets.end());

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, update, 0); // Call update function again after 16 milliseconds
}
*/

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-50,50,-50,50);
    gluOrtho2D(-100,100,-100,100);
    glMatrixMode(GL_MODELVIEW);
}
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480); // Set the window's initial width & height
    glutInitWindowPosition(80, 50);  // Set the window's initial position according to the monitor
    glutCreateWindow("Spaceship Game"); // Create a window with the given title
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    //glutReshapeFunc();
    //glutReshapeFunc(reshape);

    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys); // Register special key event handler
    glutKeyboardFunc(keyboard); // Register keyboard event handler
    init();
    glutTimerFunc(0, update, 0);
    glutMainLoop(); // Enter the event-processing loop

    return 0;
}
