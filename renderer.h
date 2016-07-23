#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"

#define WIDTH  770
#define HEIGHT 585
GLuint ventana;

void render(void);
void reshape(int width, int height);
void drawGameText();
void drawHelpText();
void drawBackground(void);
void drawEnemySet(LEVEL level);
void drawDefenses(LEVEL level);
void drawObject(OBJECT *object);
void drawExplosion(OBJECT *object);
void drawObjectHere(OBJECT *object, COORDINATE x, COORDINATE y);
void drawShotObject(SHOT *object);
void drawShip(OBJECT *ship);
void drawShots(LEVEL level);

void update_graphicstate();

void drawstr(GLuint x, GLuint y, GLdouble scale, char* format, ...);

#endif
