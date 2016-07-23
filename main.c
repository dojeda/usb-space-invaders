#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h>
#include "game.h"
#include "resources.h"
#include "renderer.h"

int timerDelay = 50;
unsigned short isFullscreen = 0;
unsigned short idclip = 0; // nombre tributo a doom

void idle(void);
void update(int value);
void func_keyboard(unsigned char key, int x, int y);
void func_arrows(unsigned char key, int x, int y);
void func_uparrows(unsigned char key, int x, int y);
void func_mouse(int button, int state, int x, int y);
void func_motion(int x, int y);
void func_passive_motion(int x, int y);

int main(int argc, char **argv) {
  init_resources();
  init_game();
  init_help(&helplevel);
  help = 1;
  paused = 1;
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(50, 50);

  ventana = glutCreateWindow("Space Invaders FX");
  glutTimerFunc(timerDelay, update, 1);
  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(func_keyboard);
  glutSpecialFunc(func_arrows);
  glutSpecialUpFunc(func_uparrows);
  glutMouseFunc(func_mouse);
  glutMotionFunc(func_motion);
  glutPassiveMotionFunc(func_passive_motion);
  glutSetCursor(GLUT_CURSOR_NONE);
  glClearColor(0,0,0.38,0.5);
  glutMainLoop();

  return 0;
}

/* void idle() { */
/*   glutPostRedisplay(); */
/* } */

void update(int value) {
  update_graphicstate();
  update_gamestate();
  //printf("Redisplay\n");
  glutPostRedisplay();
  glutTimerFunc(timerDelay, update, value);
}

void func_keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'f':
  case 'F':
    if (isFullscreen) {
      glutReshapeWindow(WIDTH,HEIGHT);
      isFullscreen = 0;
    } else {
      glutFullScreen();
      isFullscreen = 1;
    }
    break;

  case 'h':
  case 'H':
    if (!help) {
      help = 1;
      paused = 1;
    } else {
      help = 0;
      paused = 0;
    }
    break;

  case 'N':
    if (!paused && !gameover) {
      level.speed++;
      begin_level(&level);
    }
    break;

  case 'p':
  case 'P':
    if (help) return;
    if (!gameover)
      paused = !paused;
    break;

  case 'U':
    if (!paused && !gameover) {
      idclip = idclip==0?1:0;
    }
    break;

  case 32: //space
    ship_shoot();
    break;

  case 'q':
  case 'Q':
  case 27: //escape
    exit(0);
    break;

  case 13: //enter
    if (gameover)
      init_game();
    if (help) {
      help = 0;
      paused = 0;
    }
    break;    
  }
}

void func_arrows(unsigned char key, int x, int y) {
  switch (key) {
  case GLUT_KEY_LEFT:
    ship->velocity.x = -4;
    break;
  case GLUT_KEY_RIGHT:
    ship->velocity.x =  4;
    break;
  case GLUT_KEY_UP  :
    if (idclip)
      ship->velocity.y = -4;
    break;
  case GLUT_KEY_DOWN:
    if (idclip)
      ship->velocity.y =  4;
    break;
  }
}

void func_uparrows(unsigned char key, int x, int y) {
  switch (key) {
  case GLUT_KEY_LEFT:
    ship->velocity.x = 0;
    break;
  case GLUT_KEY_RIGHT:
    ship->velocity.x = 0;
    break;
  case GLUT_KEY_UP  :
    ship->velocity.y = 0;
    break;
  case GLUT_KEY_DOWN:
    ship->velocity.y = 0;
    break;
  }
}

void func_mouse(int button, int state, int x, int y) {
  if (paused || gameover || dead_delay > 0 || last_delay > 0) return;

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    ship_shoot();
  if (x > leftbound && x < rightbound)
    ship->position.x = x;
  if (idclip && y > upperbound && y < lowerbound)
    ship->position.y = y;
}

void func_motion(int x, int y) {
  if (paused || gameover || dead_delay > 0 || last_delay > 0) return;

  if (x > leftbound && x < rightbound)
    ship->position.x = x;
  if (idclip && y > upperbound && y < lowerbound)
    ship->position.y = y;
}

void func_passive_motion(int x, int y) {
  if (paused || gameover || dead_delay > 0 || last_delay > 0) return;

  ship->velocity.x = 0;
  if (x > leftbound && x < rightbound)
    ship->position.x = x;
  if (idclip && y > upperbound && y < lowerbound)
    ship->position.y = y;
}
