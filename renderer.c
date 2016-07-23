/*******************************************************************************
 * SPACE INVADERS 2004
 *
 * renderer.c
 *
 * Aqui estan implementadas las funciones necesarias para hacer render de una
 * escena sobre una ventana.
 *
 * Programacion: Ciro Duran  #00-32749
 *               David Ojeda #00-33151
 *
 * Fecha: 6-X-2004 12.09pm
 ******************************************************************************/
#include <GL/glut.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include "data.h"
#include "game.h"
#include "resources.h"
#include "renderer.h"

extern LEVEL level;
extern OBJECT *ship;

extern OBJECTTYPE **objectTypes;
extern unsigned int objectTypeNumber;

extern DRAWING *explosionDrawing;

static float defenseColors[3][3] = {{1, 0.3, 0.2},
				    {0.8, 0.8, 0.2},
				    {0.2, 1, 0.2}}; 

//GLvoid *font_style = GLUT_BITMAP_9_BY_15;
//GLvoid *font_style = GLUT_STROKE_MONO_ROMAN;
GLvoid *font_style = GLUT_STROKE_ROMAN;

void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  //glViewport(0, 0, 640, 480);
/*   glMatrixMode(GL_PROJECTION); */
/*   glLoadIdentity(); */
/*   gluOrtho2D(0, 320, 240, 0); */

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScalef(1.25,1.25,1.25);


  drawBackground();
  if (help) {
    drawEnemySet(helplevel);
    drawDefenses(helplevel);
    drawShip(helpship);
    drawShots(helplevel);
    drawHelpText();
  } else {
    drawEnemySet(level);
    drawDefenses(level);
    drawShip(ship);
    drawShots(level);
    drawGameText();
  }

  glFlush();
  glutSwapBuffers();
}

void reshape(int width, int height) {
  double ratio = (double) WIDTH / (double) HEIGHT;
  double aspect = (double) width / (double) height;

  GLsizei w,h;

  if (aspect < ratio) {
    w = width;
    h = width / ratio;
  } else {
    h = height;
    w = height * ratio;
  }
  
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 320, 240, 0.0);
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
}

void drawBackground() {
  if (gameover)
    glColor3f(0.38, 0, 0);
  else
    glColor3f(0, 0, 0.38);
    
  glRectf(0, 0, 320, 240);

  // el piso
  glColor3f(0,1,0);
  glRectf(leftbound, lowerbound + 3, rightbound + 20, lowerbound+5);
}

void drawHelpText() {
  glColor3f(1.0,1.0,1.0);
  COORDINATE vertcenter = lowerbound/2;
  COORDINATE horzcenter = rightbound/2;
  drawstr(horzcenter/3, 15, 0.15, "Space Invaders FX");
  drawstr(horzcenter/3, 30, 0.06,"Ojeda & Duran Games");
  drawstr(horzcenter,   45, 0.06, "Help:");
  drawstr(horzcenter,   55, 0.05, "Maneja el lanzamisiles para proteger");
  drawstr(horzcenter,   65, 0.05, "al planeta de la invasion extraterrestre");
  drawstr(horzcenter,   75, 0.05, "Tienes 3 vidas para salvar el mundo");

  drawstr(horzcenter,   90, 0.05, "Como jugar :");
  drawstr(horzcenter,  100, 0.05, "Flechas o Mouse : mover lanzamisiles");
  drawstr(horzcenter,  110, 0.05, "Spacebar o LeftClick : disparar misil");
  drawstr(horzcenter,  120, 0.05, "p : pausa        f : fullscreen");
  drawstr(horzcenter,  130, 0.05, "h : help         N : proximo nivel");
  drawstr(horzcenter,  140, 0.05, "U : enable volar    q : salir");
  drawstr(horzcenter,  150, 0.05, "ENTER : reiniciar juego si perdiste");
  drawstr(horzcenter,  160, 0.05, "1000 puntos = vida extra");

  drawstr(horzcenter,  180, 0.05, "Presiona ENTER o h para continuar");


  drawstr(75,  55  , 0.035, "40 puntos");
  drawstr(75,  67.5, 0.035, "20 puntos");
  drawstr(75,  80  , 0.035, "10 puntos");

  drawstr(45,  140  , 0.035, "Las defensas te pueden");
  drawstr(45,  145, 0.035,   "proteger solamente tres");
  drawstr(45,  150, 0.035,   "ocasiones de bombas");
  drawstr(45,  155, 0.035,   "enemigas o cohete terrestres");

  drawstr(60,  105, 0.035,   "evita las bombas,");
  drawstr(60,  110, 0.035,   "las naves te apuntan");
  drawstr(60,  115, 0.035,   "y disparan dos tipos");
  drawstr(60,  120, 0.035,   "de bombas");

  drawstr(5,  90, 0.035,     "las naves aumentan");
  drawstr(5,  95, 0.035,     "su velocidad a medida");
  drawstr(5,  100, 0.035,    "que son destruidas");

  drawstr(57,  170, 0.035,   "solamente puedes disparar");
  drawstr(57,  175, 0.035,   "un cohete a la vez, usalo");
  drawstr(57,  180, 0.035,   "con cuidado");
  
}

void drawGameText() {
  glColor3f(1.0,1.0,1.0);
  drawstr((rightbound - leftbound) * 1.0/4.0, 5.0, 0.05, "SCORE %d",   score);
  drawstr((rightbound - leftbound) * 2.0/4.0, 5.0, 0.05, "LEVEL %d",   level.speed+1);
  drawstr((rightbound - leftbound) * 3.0/4.0, 5.0, 0.05, "LIVES x %d", lives);

  if (paused | gameover) {
    COORDINATE vertcenter = lowerbound/2;
    COORDINATE horzcenter = rightbound/2;

    glColor3f(0,0,0);
    glRectf(horzcenter-30, vertcenter-5, horzcenter+30, vertcenter+5);
    glColor3f(1,1,1);
    if (paused)
      drawstr(horzcenter-10, vertcenter+1, 0.05, "PAUSE");
    else if (gameover)
      drawstr(horzcenter-20, vertcenter+1, 0.05, "GAME OVER");
  }
}

void drawEnemySet(LEVEL level) {
  unsigned int i = 0;

  for (i = 0; i < level.enemyNumber; i++) {
    if ((level.enemyset+i)->visible) {
      drawObject(level.enemyset+i);
    } else if ((level.enemyset+i)->explosion_delay) {
      drawExplosion(level.enemyset+i);
    }
  }
}

void drawDefenses(LEVEL level) {
  unsigned int i = 0;
  
  for (i = 0; i < level.defenseNumber; i++) {
    DEFENSE *nextdef = *(level.defenseset+i);
    POLYGON *poly = *(nextdef->defenseDrawing->polygons);
    unsigned int j = 0;

    if (nextdef->health)
        glColor3f(defenseColors[nextdef->health-1][0],
                  defenseColors[nextdef->health-1][1],
                  defenseColors[nextdef->health-1][2]);

    for (j = 0; j < 3; j++) {
      if (nextdef->parts[j] == 0) {
	continue;
      }
      glRectf((poly->points)->x + nextdef->position.x,
	      (poly->points)->y+nextdef->height*j + nextdef->position.y,
	      (poly->points+2)->x + nextdef->position.x,
	      (poly->points+2)->y+nextdef->height*j + nextdef->position.y);
    }
  }
}
void drawShip(OBJECT *ship) {
  drawObject(ship);
}

void drawShots(LEVEL level) {
  unsigned int i = 0;

  for (i = 0; i < level.shipShotNumber; i++) {
    if ((level.ship_shots+i)->visible) {
      drawShotObject(level.ship_shots+i);
    }
  }

  for (i = 0; i < level.enemyShotNumber; i++) {
    if ((level.enemy_shots+i)->visible) {
      drawShotObject(level.enemy_shots+i);
    }
  }
}

void drawObject(OBJECT *object) {
  
  ANIMATION *animation = (*(object->type->states+object->type->currentState));
  DRAWING * draw2render = *(animation->frames+(animation->currentFrame));
  COORDINATE objectX = object->position.x;
  COORDINATE objectY = object->position.y;

  unsigned int i = 0;
  
  for (i = 0; i < draw2render->polygonNumber; i++) {
    POLYGON * poly = *((draw2render->polygons)+i);
    float *color = poly->color;
    unsigned int j = 0;

    glColor3f(*color, *(color+1), *(color+2));
    if (poly->sides == 4) {
      glRectf((*(poly->points)).x + objectX, 
	      (*(poly->points)).y + objectY,
	      (*(poly->points+2)).x + objectX, 
	      (*(poly->points+2)).y + objectY);
    } else {
      glBegin(GL_POLYGON);
      
      for (j = 0; j < poly->sides; j++) {
	glVertex2f((*(poly->points+j)).x + objectX,
		   (*(poly->points+j)).y + objectY);
      }
      
      glEnd();
    }
    //glFlush();
  }
}

void drawExplosion(OBJECT *object) {
  COORDINATE x = object->position.x;
  COORDINATE y = object->position.y;
  unsigned int j = 0;

  for (j = 0; j < explosionDrawing->polygonNumber; j++) {
    POLYGON *poly = *(explosionDrawing->polygons+j);

    glColor3f(*poly->color, *(poly->color+1), *(poly->color+2));
    glRectf((*(poly->points)).x + x,
	      (*(poly->points)).y + y,
	      (*(poly->points+2)).x + x,
	      (*(poly->points+2)).y + y);
  }
}

void drawObjectHere(OBJECT *object, COORDINATE x, COORDINATE y) {
  
  ANIMATION *animation = (*(object->type->states));
  DRAWING * draw2render = *(animation->frames+(animation->currentFrame));
  COORDINATE objectX = x;
  COORDINATE objectY = y;

  unsigned int i = 0;
  
  for (i = 0; i < draw2render->polygonNumber; i++) {
    POLYGON * poly = *((draw2render->polygons)+i);
    float *color = poly->color;
    unsigned int j = 0;

    glColor3f(*color, *(color+1), *(color+2));
    if (poly->sides == 4) {
      glRectf((*(poly->points)).x + objectX,
	      (*(poly->points)).y + objectY,
	      (*(poly->points+2)).x + objectX,
	      (*(poly->points+2)).y + objectY);
    } else {
      glBegin(GL_POLYGON);
      
      for (j = 0; j < poly->sides; j++) {
	glVertex2f((*(poly->points+j)).x + objectX,
		   (*(poly->points+j)).y + objectY);
      }
      
      glEnd();
    }
    glFlush();
  }
}

void drawShotObject(SHOT *shot) {
  ANIMATION *animation = shot->animation;
  DRAWING * draw2render = *(animation->frames+(animation->currentFrame));
  COORDINATE shotX = shot->position.x;
  COORDINATE shotY = shot->position.y;

  unsigned int i = 0;
  
  for (i = 0; i < draw2render->polygonNumber; i++) {
    POLYGON * poly = *((draw2render->polygons)+i);
    float *color = poly->color;
    unsigned int j = 0;

    glColor3f(*color, *(color+1), *(color+2));
    if (poly->sides == 4) {
      glRectf((*(poly->points)).x + shotX, 
	      (*(poly->points)).y + shotY,
	      (*(poly->points+2)).x + shotX, 
	      (*(poly->points+2)).y + shotY);
    } else {
      glBegin(GL_POLYGON);
      
      for (j = 0; j < poly->sides; j++) {
	glVertex2f((*(poly->points+j)).x + shotX,
		   (*(poly->points+j)).y + shotY);
      }
      
      glEnd();
    }
    glFlush();
  }
}

void update_graphicstate() {
  unsigned int i = 0;

  for (i = 0; i != objectTypeNumber; i++) {
    if (!paused && !gameover)
      nextFrame(*(objectTypes+i));
  }

  for (i = 0; i != level.enemyNumber; i++) {
    OBJECT *obj = (level.enemyset+i);
    if (!obj->visible && obj->explosion_delay > 0) {
      obj->explosion_delay--;
    }
  }
}

void nextFrame(OBJECTTYPE *objecttype) {
  ANIMATION *currentState = *(objecttype->states+(objecttype->currentState));
  
  currentState->currentDelay = (currentState->currentDelay+1)%currentState->delay;

  //printf("currentDelay: %d / Delay: %d\n", currentState->currentDelay, currentState->delay);
  if (currentState->currentDelay == 0) {
    currentState->currentFrame = (currentState->currentFrame+1)%currentState->framesNumber;
    //printf("currentFrame: %d\n", currentState->currentFrame);
  }
}

/**
 * dibuja un string. Tomado de shapes.c
 */
void drawstr(GLuint x, GLuint y, GLdouble scale, char* format, ...)
{
  glPushMatrix();
  glTranslatef(x,y+2,0);
  glScalef(scale,scale,scale);
  glRotatef(180,1,0,0);
  va_list args;
  char buffer[255], *s;
    
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
    
  //glRasterPos2i(x, y);
  //glTranslatef(100,100,0);
  for (s = buffer; *s; s++)
    glutStrokeCharacter(font_style, *s);
  glPopMatrix();
}
