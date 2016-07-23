#include <GL/glut.h>
#include "resources.h"
#include "game.h"
#include "renderer.h"


int main(int argc, char **argv) {
  
  init_game();

  init_resources();
  update_gamestate(); //solo para probar

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowSize(640, 480);
  glutInitWindowPosition(50, 50);

  glutCreateWindow("Display test");
  glutDisplayFunc(render);
  glutMainLoop();
  return 0;
}
