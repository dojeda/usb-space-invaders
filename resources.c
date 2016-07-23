/*******************************************************************************
 * SPACE INVADERS 2004
 *
 * resources.c
 *
 * Debido a restricciones de tiempo, se implementas estas funciones para la
 * creacion de los recursos graficos del juego. Todos los datos de los dibujos
 * de los enemigos y las naves estan contenidos aqui.
 *
 * Programacion: Ciro Duran  #00-32749
 *               David Ojeda #00-33151
 *
 * Fecha: 4-X-2004 11.47pm
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "game.h"
#include "resources.h"

OBJECTTYPE **objectTypes = NULL;
unsigned int objectTypeNumber = 4;

ANIMATION **shotDefAnimations = NULL;
unsigned int shotDefNumber = 4;

DRAWING *defenseDrawing = NULL;
DRAWING *explosionDrawing = NULL;

/**
 * Como convencion adoptada para identificar que cosa pertenece a cada
 * recurso, las variables van a tener la forma eWaXdYpZ donde:
 *
 * e == enemy
 * a == animation
 * d == drawing
 * p == polygon
 *
 * y las variables W, X, Y, Z indican el numero de recurso correspondiente.
 */

/**
 * Los datos para el enemigo tipo 2
 *
 * ..X.....X..
 * X..X...X..X
 * X.XXXXXXX.X
 * XXX.XXX.XXX
 * .XXXXXXXXX.
 * ..X.....X..
 * .X.......X.
 */
static float        bodyColor[] = {0.38, 1.0, 0};
static float        eyesColor[] = {   0,   0, 0};

static unsigned int e2a0d0p0sides = 4;
static COORDINATE   e2a0d0p0points[] =  {0,1,  1,1,  1,5,  0,5};
static COORDINATE   e2a0d0p1points[] =  {10,1, 11,1, 11,5, 10,5};
static COORDINATE   e2a0d0p2points[] =  {2,2,  9,2,  9,3,  2,3};
static COORDINATE   e2a0d0p3points[] =  {1,3,  10,3, 10,6, 1,6};
static COORDINATE   e2a0d0p4points[] =  {2,0,  3,0,  3,1,  2,1};
static COORDINATE   e2a0d0p5points[] =  {3,1,  4,1,  4,2,  3,2};
static COORDINATE   e2a0d0p6points[] =  {8,0,  9,0,  9,1,  8,1};
static COORDINATE   e2a0d0p7points[] =  {7,1,  8,1,  8,2,  7,2};
static COORDINATE   e2a0d0p8points[] =  {2,6,  3,6,  3,7,  2,7};
static COORDINATE   e2a0d0p9points[] =  {1,7,  2,7,  2,8,  1,8};
static COORDINATE   e2a0d0p10points[] = {8,6,  9,6,  9,7,  8,7};
static COORDINATE   e2a0d0p11points[] = {9,7,  10,7, 10,8, 9,8};

static COORDINATE   e2a0d0p12points[] = {3,3,  4,3,  4,4,  3,4};
static COORDINATE   e2a0d0p13points[] = {7,3,  8,3,  8,4,  7,4};

//Drawing 1
//Drawing 1
//Drawing 1

static unsigned int e2a0d1p0sides = 4;
static COORDINATE e2a0d1p0points[] =  {0,4,  1,4,  1,7,  0,7};
static COORDINATE e2a0d1p1points[] =  {10,4, 11,4, 11,7, 10,4};
static COORDINATE e2a0d1p2points[] =  {2,2,  9,2,  9,3,  2,3};
static COORDINATE e2a0d1p3points[] =  {1,3,  10,3, 10,5, 1,5};
static COORDINATE e2a0d1p4points[] =  {2,5,  9,5,  9,6,  2,6};
static COORDINATE e2a0d1p5points[] =  {2,0,  3,0,  3,1,  2,1};
static COORDINATE e2a0d1p6points[] =  {3,1,  4,1,  4,2,  3,2};
static COORDINATE e2a0d1p7points[] =  {8,0,  9,0,  9,1,  8,1};
static COORDINATE e2a0d1p8points[] =  {7,1,  8,1,  8,2,  7,2};
static COORDINATE e2a0d1p9points[] =  {2,6,  3,6,  3,7,  2,7};
static COORDINATE e2a0d1p10points[] = {3,7,  5,7,  5,8,  3,8};
static COORDINATE e2a0d1p11points[] = {8,6,  9,6,  9,7,  8,7};
static COORDINATE e2a0d1p12points[] = {6,7,  8,7,  8,8,  6,8};

static COORDINATE e2a0d1p13points[] = {3,3,  4,3,  4,4,  3,4};
static COORDINATE e2a0d1p14points[] = {7,3,  8,3,  8,4,  7,4};

/**
 * Los datos para el enemigo tipo 1
 *
 * ...XX...
 * ..XXXX..
 * .XXXXXX.
 * XX.XX.XX
 * XXXXXXXX
 * .X.XX.X.
 * X......X
 * .X....X.
 */
//Comun
static COORDINATE e1a0headp0points[] = {3,0,  5,0,  5,1,  3,1};
static COORDINATE e1a0headp1points[] = {2,1,  6,1,  6,2,  2,2};
static COORDINATE e1a0headp2points[] = {1,2,  7,2,  7,3,  1,3};
static COORDINATE e1a0headp3points[] = {0,3,  8,3,  8,5,  0,5};
static COORDINATE e1a0headp4points[] = {2,3,  3,3,  3,4,  2,4};
static COORDINATE e1a0headp5points[] = {5,3,  6,3,  6,4,  5,4};

//Drawing 0
static COORDINATE e1a0d0p0points[] = {1,5,  2,5,  2,6,  1,6};
static COORDINATE e1a0d0p1points[] = {0,6,  1,6,  1,7,  0,7};
static COORDINATE e1a0d0p2points[] = {1,7,  2,7,  2,8,  1,8};
static COORDINATE e1a0d0p3points[] = {3,5,  5,5,  5,6,  3,6};
static COORDINATE e1a0d0p4points[] = {6,5,  7,5,  7,6,  6,6};
static COORDINATE e1a0d0p5points[] = {7,6,  8,6,  8,7,  7,7};
static COORDINATE e1a0d0p6points[] = {6,7,  7,7,  7,8,  6,8};

//Drawing 1
static COORDINATE e1a0d1p0points[] = {2,5,  3,5,  3,6,  2,6};
static COORDINATE e1a0d1p1points[] = {5,5,  6,5,  6,6,  5,6};
static COORDINATE e1a0d1p2points[] = {1,6,  2,6,  2,7,  1,7};
static COORDINATE e1a0d1p3points[] = {3,6,  5,6,  5,7,  3,7};
static COORDINATE e1a0d1p4points[] = {6,6,  7,6,  7,7,  6,7};
static COORDINATE e1a0d1p5points[] = {0,7,  1,7,  1,8,  0,8};
static COORDINATE e1a0d1p6points[] = {2,7,  3,7,  3,8,  2,8};
static COORDINATE e1a0d1p7points[] = {5,7,  6,7,  6,8,  5,8};
static COORDINATE e1a0d1p8points[] = {7,7,  8,7,  8,8,  7,8};

/**
 * Los datos para el enemigo tipo 3
 *
 * ....XXXX....
 * .XXXXXXXXXX.
 * XXXXXXXXXXXX
 * XXX..XX..XXX
 * XXXXXXXXXXXX
 * ...XX..XX...
 * ..XX.XX.XX..
 * XX........XX
 */
//Comun
static COORDINATE e3a0headp0points[] = {4,0,  8,0,  8,1,  4,1};
static COORDINATE e3a0headp1points[] = {1,1,  11,1, 11,2, 1,2};
static COORDINATE e3a0headp2points[] = {0,2,  12,2, 12,5, 0,5};
static COORDINATE e3a0headp3points[] = {3,3,  5,3,  5,4,  3,4};
static COORDINATE e3a0headp4points[] = {7,3,  9,3,  9,4,  7,4};

//Drawing 0
static COORDINATE e3a0d0p0points[] = {3,5,  5,5,  5,6,  3,6};
static COORDINATE e3a0d0p1points[] = {7,5,  9,5,  9,6,  7,6};
static COORDINATE e3a0d0p2points[] = {2,6,  4,6,  4,7,  2,7};
static COORDINATE e3a0d0p3points[] = {5,6,  7,6,  7,7,  5,7};
static COORDINATE e3a0d0p4points[] = {8,6,  10,6, 10,7, 8,7};
static COORDINATE e3a0d0p5points[] = {0,7,  2,7,  2,8,  0,8};
static COORDINATE e3a0d0p6points[] = {10,7, 12,7, 12,8, 10,8};

//Drawing 1
static COORDINATE e3a0d1p0points[] = {2,5, 5,5,  5,6,  2,6};
static COORDINATE e3a0d1p1points[] = {7,5, 10,5, 10,6, 7,6};
static COORDINATE e3a0d1p2points[] = {1,6, 3,6,  3,7,  1,7};
static COORDINATE e3a0d1p3points[] = {5,6, 7,6,  7,7,  5,7};
static COORDINATE e3a0d1p4points[] = {9,6, 11,6, 11,7, 9,7};
static COORDINATE e3a0d1p5points[] = {2,7, 4,7,  4,8,  2,8};
static COORDINATE e3a0d1p6points[] = {8,7, 10,7, 10,8, 8,8};

/**
 * Los datos para el disparo 1
 *
 * .X.
 * .X.
 * .X.
 * XXX
 * .X.
 */
static float shotColor[] = {1,1,1};
static unsigned int shotSides = 4;
static COORDINATE shot1p0points[] = {1,0,  2,0,  2,5,  1,5};
static COORDINATE shot1p1points[] = {0,3,  3,3,  3,4,  0,4};

/**
 * Los datos para el disparo 2
 *
 * .X.
 * X..
 * .X.
 * ..X
 * .X.
 */
static COORDINATE shot2p0points[] = {1,0, 2,0, 2,1, 1,1};
static COORDINATE shot2p1points[] = {0,1, 1,1, 1,2, 0,2};
static COORDINATE shot2p2points[] = {1,2, 2,2, 2,3, 1,3};
static COORDINATE shot2p3points[] = {2,3, 3,3, 3,4, 2,4};
static COORDINATE shot2p4points[] = {1,4, 2,4, 2,5, 1,5};

/**
 * Los datos para el disparo de la nave
 *
 * X
 * X
 * X
 * X
 * X
 */
static COORDINATE shot3p0points[] = {0,0, 1,0, 1,5, 0,5};

/**
 * Los datos para la nave
 *
 * .......X.......
 * ......XXX......
 * ......XXX......
 * ......XXX......
 * .XXXXXXXXXXXXX.
 * XXXXXXXXXXXXXXX
 * XXXXXXXXXXXXXXX
 * XXXXXXXXXXXXXXX
 * XXXXXXXXXXXXXXX
 */
static unsigned int shipBodySides = 4;
static unsigned int shipTipSides = 5;
static float shipColor[] = {0.75, 0.1, 0};
static COORDINATE shipa0d0p0points[] = {0,5,  15,5,  15,9, 0,9};
static COORDINATE shipa0d0p1points[] = {1,4,  14,4,  14,5, 1,5};
static COORDINATE shipa0d0p2points[] = {6,4,  7,1,  7.5,1, 8,1, 9,4};

/**
 * Los datos para la explosion de la nave
 *
 * Dibujo 1
 * ....X..........
 * ..X.....X....X.
 * ....X..X..X....
 * ..X......X.X...
 * X....X.XX...X..
 * ...XXXXXXXXX...
 * ..XXXXXXXXXXX..
 * .XXXXXXXXXXXXX.
 * 
 * Dibujo 2
 * .X.....X....X..
 * ....X..........
 * ..X....X....X..
 * ......X...X....
 * .X...XX.X.....X
 * ....XXXXXX..X..
 * ...XXXXXXXX....
 * .XXXXXXXXXXXX..
 */
static unsigned int explosionSides=4;
static float explosionColor1[]={1,0,0};
static float explosionColor2[]={1,0.6,0.2};
static float explosionColor3[]={0.8,0.8,0.8};
static COORDINATE shipa1d0p0points[]  = {4,0,  5,0,  5,1,  4,1};
static COORDINATE shipa1d0p1points[]  = {2,1,  3,1,  3,2,  2,2};
static COORDINATE shipa1d0p2points[]  = {8,1,  9,1,  9,2,  8,2};
static COORDINATE shipa1d0p3points[]  = {13,1, 14,1, 14,2, 13,2};
static COORDINATE shipa1d0p4points[]  = {4,2,  5,2,  5,3,  4,3};
static COORDINATE shipa1d0p5points[]  = {7,2,  8,2,  8,3,  7,3};
static COORDINATE shipa1d0p6points[]  = {10,2, 11,2, 11,3, 10,3};
static COORDINATE shipa1d0p7points[]  = {2,3,  3,3,  3,4,  2,4};
static COORDINATE shipa1d0p8points[]  = {9,3,  10,3, 10,4, 9,4};
static COORDINATE shipa1d0p9points[]  = {11,3, 12,3, 12,4, 11,4};
static COORDINATE shipa1d0p10points[] = {0,4,  1,4,  1,5,  0,5};
static COORDINATE shipa1d0p11points[] = {5,4,  6,4,  6,5,  5,5};
static COORDINATE shipa1d0p12points[] = {7,4,  9,4,  9,5,  7,5};
static COORDINATE shipa1d0p13points[] = {12,4, 13,4, 13,5, 12,5};
static COORDINATE shipa1d0p14points[] = {3,5,  11,5, 11,6, 3,6};
static COORDINATE shipa1d0p15points[] = {2,6,  5,6,  5,7,  2,7};
static COORDINATE shipa1d0p16points[] = {5,6,  9,6,  9,7,  5,7};
static COORDINATE shipa1d0p17points[] = {9,6,  12,6, 12,7, 9,7};
static COORDINATE shipa1d0p18points[] = {1,7,  4,7,  4,8,  1,8};
static COORDINATE shipa1d0p19points[] = {4,7,  10,7, 10,8, 4,8};
static COORDINATE shipa1d0p20points[] = {10,7, 13,7, 13,8, 10,8};

static COORDINATE shipa1d1p0points[]  = {1,0,  0,0,  2,1,  0,0};
static COORDINATE shipa1d1p1points[]  = {7,0,  0,0,  8,1,  0,0};
static COORDINATE shipa1d1p2points[]  = {12,0, 0,0,  13,1, 0,0};
static COORDINATE shipa1d1p3points[]  = {4,1,  0,0,  5,2,  0,0};
static COORDINATE shipa1d1p4points[]  = {2,2,  0,0,  3,3,  0,0};
static COORDINATE shipa1d1p5points[]  = {7,2,  0,0,  8,3,  0,0};
static COORDINATE shipa1d1p6points[]  = {12,2, 0,0,  13,3, 0,0};
static COORDINATE shipa1d1p7points[]  = {6,3,  0,0,  7,4,  0,0};
static COORDINATE shipa1d1p8points[]  = {10,3, 0,0,  11,4, 0,0};
static COORDINATE shipa1d1p9points[]  = {1,4,  0,0,  2,5,  0,0};
static COORDINATE shipa1d1p10points[] = {5,4,  0,0,  7,5,  0,0};
static COORDINATE shipa1d1p11points[] = {8,4,  0,0,  9,5,  0,0};
static COORDINATE shipa1d1p12points[] = {14,4, 0,0,  15,5, 0,0};
static COORDINATE shipa1d1p13points[] = {4,5,  0,0,  10,6, 0,0};
static COORDINATE shipa1d1p14points[] = {12,5, 0,0,  13,6, 0,0};
static COORDINATE shipa1d1p15points[] = {3,6,  0,0,  6,7,  0,0};
static COORDINATE shipa1d1p16points[] = {6,6,  0,0,  8,7,  0,0};
static COORDINATE shipa1d1p17points[] = {8,6,  0,0,  11,7, 0,0};
static COORDINATE shipa1d1p18points[] = {1,7,  0,0,  4,8,  0,0};
static COORDINATE shipa1d1p19points[] = {4,7,  0,0,  10,8, 0,0};
static COORDINATE shipa1d1p20points[] = {10,7, 0,0,  13,8, 0,0};

/**
 * Los datos para explosion de un alien
 *
 * .....X..X...
 * ..X..X..X..X
 * ...X...X..X.
 * XXX.........
 * ....X.....XX
 * ..XX....X...
 * .X....X..X..
 * ......X...X.
 */
static float explosionColor[] = {1,0.8,0.8};
static COORDINATE explosionp0points[] =  {2,1, 0,0, 3,2, 0,0};
static COORDINATE explosionp1points[] =  {5,0, 0,0, 6,2, 0,0};
static COORDINATE explosionp2points[] =  {8,0, 0,0, 9,2, 0,0};
static COORDINATE explosionp3points[] =  {11,1, 0,0, 12,2, 0,0};
static COORDINATE explosionp4points[] =  {3,2, 0,0, 4,3, 0,0};
static COORDINATE explosionp5points[] =  {7,2, 0,0, 8,3, 0,0};
static COORDINATE explosionp6points[] =  {10,2, 0,0, 11,3, 0,0};
static COORDINATE explosionp7points[] =  {0,3, 0,0, 3,4, 0,0};
static COORDINATE explosionp8points[] =  {4,4, 0,0, 5,5, 0,0};
static COORDINATE explosionp9points[] =  {10,4, 0,0, 12,5, 0,0};
static COORDINATE explosionp10points[] = {2,5, 0,0, 4,6, 0,0};
static COORDINATE explosionp11points[] = {8,5, 0,0, 9,6, 0,0};
static COORDINATE explosionp12points[] = {1,6, 0,0, 2,7, 0,0};
static COORDINATE explosionp13points[] = {6,6, 0,0, 7,8, 0,0};
static COORDINATE explosionp14points[] = {9,6, 0,0, 10,7, 0,0};
static COORDINATE explosionp15points[] = {10,7, 0,0, 11,8, 0,0};

/**
 * Los datos para la defensa
 */
static unsigned int defenseSides = 4;
static COORDINATE defensep0points[] = {0,0, 0,0, 30,4, 0,0};

void init_resources() {
  objectTypes = (OBJECTTYPE **)malloc(sizeof(OBJECTTYPE *)*4);
  
  *objectTypes = build_ship();
  *(objectTypes+1) = build_enemytype1();
  *(objectTypes+2) = build_enemytype2();
  *(objectTypes+3) = build_enemytype3();

  shotDefAnimations = (ANIMATION **)malloc(sizeof(ANIMATION *)*4);
  
  *shotDefAnimations = build_shipshot();
  *(shotDefAnimations+1) = build_enemyshot1();
  *(shotDefAnimations+2) = build_enemyshot2();

  defenseDrawing = build_defense();
  explosionDrawing = build_explosion();
  //alienship = build_alienship();
}

OBJECTTYPE *build_enemytype1() {
  OBJECTTYPE *enemytype = NULL;
  DRAWINGTEMPLATE **drawing_list = NULL;
  ANIMATION **states_list = NULL;
  
  DRAWINGTEMPLATE drawing0;
  DRAWINGTEMPLATE drawing1;

  //DRAWING 0
  drawing0.polygonNumber = 13;

  drawing0.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing0.polygonNumber);
  *(drawing0.sides_list)   = &e2a0d0p0sides;
  *((drawing0.sides_list)+1) = &e2a0d0p0sides;
  *((drawing0.sides_list)+2) = &e2a0d0p0sides;
  *((drawing0.sides_list)+3) = &e2a0d0p0sides;
  *((drawing0.sides_list)+4) = &e2a0d0p0sides;
  *((drawing0.sides_list)+5) = &e2a0d0p0sides;
  *((drawing0.sides_list)+6) = &e2a0d0p0sides;
  *((drawing0.sides_list)+7) = &e2a0d0p0sides;
  *((drawing0.sides_list)+8) = &e2a0d0p0sides;
  *((drawing0.sides_list)+9) = &e2a0d0p0sides;
  *((drawing0.sides_list)+10) = &e2a0d0p0sides;
  *((drawing0.sides_list)+11) = &e2a0d0p0sides;
  *((drawing0.sides_list)+12) = &e2a0d0p0sides;

  drawing0.color_list = (float **)malloc(sizeof(float *)*drawing0.polygonNumber);
  *(drawing0.color_list) = bodyColor;
  *((drawing0.color_list)+1) = bodyColor;
  *((drawing0.color_list)+2) = bodyColor;
  *((drawing0.color_list)+3) = bodyColor;
  *((drawing0.color_list)+4) = eyesColor;
  *((drawing0.color_list)+5) = eyesColor;
  *((drawing0.color_list)+6) = bodyColor;
  *((drawing0.color_list)+7) = bodyColor;
  *((drawing0.color_list)+8) = bodyColor;
  *((drawing0.color_list)+9) = bodyColor;
  *((drawing0.color_list)+10) = bodyColor;
  *((drawing0.color_list)+11) = bodyColor;
  *((drawing0.color_list)+12) = bodyColor;

  drawing0.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing0.polygonNumber);
  *(drawing0.points_list) = e1a0headp0points;
  *((drawing0.points_list)+1) = e1a0headp1points;
  *((drawing0.points_list)+2) = e1a0headp2points;
  *((drawing0.points_list)+3) = e1a0headp3points;
  *((drawing0.points_list)+4) = e1a0headp4points;
  *((drawing0.points_list)+5) = e1a0headp5points;
  *((drawing0.points_list)+6) = e1a0d0p0points;
  *((drawing0.points_list)+7) = e1a0d0p1points;
  *((drawing0.points_list)+8) = e1a0d0p2points;
  *((drawing0.points_list)+9) = e1a0d0p3points;
  *((drawing0.points_list)+10) = e1a0d0p4points;
  *((drawing0.points_list)+11) = e1a0d0p5points;
  *((drawing0.points_list)+12) = e1a0d0p6points;
  
  //DRAWING 1
  drawing1.polygonNumber = 15;

  drawing1.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing1.polygonNumber);
  *(drawing1.sides_list)   = &e2a0d1p0sides;
  *((drawing1.sides_list)+1) = &e2a0d1p0sides;
  *((drawing1.sides_list)+2) = &e2a0d1p0sides;
  *((drawing1.sides_list)+3) = &e2a0d1p0sides;
  *((drawing1.sides_list)+4) = &e2a0d1p0sides;
  *((drawing1.sides_list)+5) = &e2a0d1p0sides;
  *((drawing1.sides_list)+6) = &e2a0d1p0sides;
  *((drawing1.sides_list)+7) = &e2a0d1p0sides;
  *((drawing1.sides_list)+8) = &e2a0d1p0sides;
  *((drawing1.sides_list)+9) = &e2a0d1p0sides;
  *((drawing1.sides_list)+10) = &e2a0d1p0sides;
  *((drawing1.sides_list)+11) = &e2a0d1p0sides;
  *((drawing1.sides_list)+12) = &e2a0d1p0sides;
  *((drawing1.sides_list)+13) = &e2a0d1p0sides;
  *((drawing1.sides_list)+14) = &e2a0d1p0sides;

  drawing1.color_list = (float **)malloc(sizeof(float *)*drawing1.polygonNumber);
  *(drawing1.color_list) = bodyColor;
  *((drawing1.color_list)+1) = bodyColor;
  *((drawing1.color_list)+2) = bodyColor;
  *((drawing1.color_list)+3) = bodyColor;
  *((drawing1.color_list)+4) = eyesColor;
  *((drawing1.color_list)+5) = eyesColor;
  *((drawing1.color_list)+6) = bodyColor;
  *((drawing1.color_list)+7) = bodyColor;
  *((drawing1.color_list)+8) = bodyColor;
  *((drawing1.color_list)+9) = bodyColor;
  *((drawing1.color_list)+10) = bodyColor;
  *((drawing1.color_list)+11) = bodyColor;
  *((drawing1.color_list)+12) = bodyColor;
  *((drawing1.color_list)+13) = bodyColor;
  *((drawing1.color_list)+14) = bodyColor;

  drawing1.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing1.polygonNumber);
  *(drawing1.points_list) = e1a0headp0points;
  *((drawing1.points_list)+1) = e1a0headp1points;
  *((drawing1.points_list)+2) = e1a0headp2points;
  *((drawing1.points_list)+3) = e1a0headp3points;
  *((drawing1.points_list)+4) = e1a0headp4points;
  *((drawing1.points_list)+5) = e1a0headp5points;
  *((drawing1.points_list)+6) = e1a0d1p0points;
  *((drawing1.points_list)+7) = e1a0d1p1points;
  *((drawing1.points_list)+8) = e1a0d1p2points;
  *((drawing1.points_list)+9) = e1a0d1p3points;
  *((drawing1.points_list)+10) = e1a0d1p4points;
  *((drawing1.points_list)+11) = e1a0d1p5points;
  *((drawing1.points_list)+12) = e1a0d1p6points;
  *((drawing1.points_list)+13) = e1a0d1p7points;
  *((drawing1.points_list)+14) = e1a0d1p8points;
 

  //DRAWING LIST
  drawing_list = (DRAWINGTEMPLATE **)malloc(sizeof(DRAWINGTEMPLATE *)*2);
  *(drawing_list) = &drawing0;
  *(drawing_list+1) = &drawing1;

  states_list = (ANIMATION **)malloc(sizeof(ANIMATION *));
  *(states_list) = build_animation(2, 5, drawing_list);

  free(drawing_list);
  free(drawing0.sides_list);
  free(drawing0.color_list);
  free(drawing0.points_list);
  free(drawing1.sides_list);
  free(drawing1.color_list);
  free(drawing1.points_list);

  enemytype = create_objecttype(1, states_list);

  return enemytype;
}

OBJECTTYPE *build_enemytype2() {
  OBJECTTYPE *enemytype = NULL;
  DRAWINGTEMPLATE **drawing_list = NULL;
  ANIMATION **states_list = NULL;

  DRAWINGTEMPLATE drawing0;
  DRAWINGTEMPLATE drawing1;

  //DRAWING 0
  drawing0.polygonNumber = 14;

  drawing0.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing0.polygonNumber);
  *(drawing0.sides_list)   = &e2a0d0p0sides;
  *((drawing0.sides_list)+1) = &e2a0d0p0sides;
  *((drawing0.sides_list)+2) = &e2a0d0p0sides;
  *((drawing0.sides_list)+3) = &e2a0d0p0sides;
  *((drawing0.sides_list)+4) = &e2a0d0p0sides;
  *((drawing0.sides_list)+5) = &e2a0d0p0sides;
  *((drawing0.sides_list)+6) = &e2a0d0p0sides;
  *((drawing0.sides_list)+7) = &e2a0d0p0sides;
  *((drawing0.sides_list)+8) = &e2a0d0p0sides;
  *((drawing0.sides_list)+9) = &e2a0d0p0sides;
  *((drawing0.sides_list)+10) = &e2a0d0p0sides;
  *((drawing0.sides_list)+11) = &e2a0d0p0sides;
  *((drawing0.sides_list)+12) = &e2a0d0p0sides;
  *((drawing0.sides_list)+13) = &e2a0d0p0sides;

  drawing0.color_list = (float **)malloc(sizeof(float *)*drawing0.polygonNumber);
  *(drawing0.color_list) = bodyColor;
  *((drawing0.color_list)+1) = bodyColor;
  *((drawing0.color_list)+2) = bodyColor;
  *((drawing0.color_list)+3) = bodyColor;
  *((drawing0.color_list)+4) = bodyColor;
  *((drawing0.color_list)+5) = bodyColor;
  *((drawing0.color_list)+6) = bodyColor;
  *((drawing0.color_list)+7) = bodyColor;
  *((drawing0.color_list)+8) = bodyColor;
  *((drawing0.color_list)+9) = bodyColor;
  *((drawing0.color_list)+10) = bodyColor;
  *((drawing0.color_list)+11) = bodyColor;
  *((drawing0.color_list)+12) = eyesColor;
  *((drawing0.color_list)+13) = eyesColor;

  drawing0.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing0.polygonNumber);
  *(drawing0.points_list) = e2a0d0p0points;
  *((drawing0.points_list)+1) = e2a0d0p1points;
  *((drawing0.points_list)+2) = e2a0d0p2points;
  *((drawing0.points_list)+3) = e2a0d0p3points;
  *((drawing0.points_list)+4) = e2a0d0p4points;
  *((drawing0.points_list)+5) = e2a0d0p5points;
  *((drawing0.points_list)+6) = e2a0d0p6points;
  *((drawing0.points_list)+7) = e2a0d0p7points;
  *((drawing0.points_list)+8) = e2a0d0p8points;
  *((drawing0.points_list)+9) = e2a0d0p9points;
  *((drawing0.points_list)+10) = e2a0d0p10points;
  *((drawing0.points_list)+11) = e2a0d0p11points;
  *((drawing0.points_list)+12) = e2a0d0p12points;
  *((drawing0.points_list)+13) = e2a0d0p13points;
  
  //DRAWING 1
  drawing1.polygonNumber = 15;

  drawing1.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing1.polygonNumber);
  *(drawing1.sides_list)   = &e2a0d1p0sides;
  *((drawing1.sides_list)+1) = &e2a0d1p0sides;
  *((drawing1.sides_list)+2) = &e2a0d1p0sides;
  *((drawing1.sides_list)+3) = &e2a0d1p0sides;
  *((drawing1.sides_list)+4) = &e2a0d1p0sides;
  *((drawing1.sides_list)+5) = &e2a0d1p0sides;
  *((drawing1.sides_list)+6) = &e2a0d1p0sides;
  *((drawing1.sides_list)+7) = &e2a0d1p0sides;
  *((drawing1.sides_list)+8) = &e2a0d1p0sides;
  *((drawing1.sides_list)+9) = &e2a0d1p0sides;
  *((drawing1.sides_list)+10) = &e2a0d1p0sides;
  *((drawing1.sides_list)+11) = &e2a0d1p0sides;
  *((drawing1.sides_list)+12) = &e2a0d1p0sides;
  *((drawing1.sides_list)+13) = &e2a0d1p0sides;
  *((drawing1.sides_list)+14) = &e2a0d1p0sides;

  drawing1.color_list = (float **)malloc(sizeof(float *)*drawing1.polygonNumber);
  *(drawing1.color_list) = bodyColor;
  *((drawing1.color_list)+1) = bodyColor;
  *((drawing1.color_list)+2) = bodyColor;
  *((drawing1.color_list)+3) = bodyColor;
  *((drawing1.color_list)+4) = bodyColor;
  *((drawing1.color_list)+5) = bodyColor;
  *((drawing1.color_list)+6) = bodyColor;
  *((drawing1.color_list)+7) = bodyColor;
  *((drawing1.color_list)+8) = bodyColor;
  *((drawing1.color_list)+9) = bodyColor;
  *((drawing1.color_list)+10) = bodyColor;
  *((drawing1.color_list)+11) = bodyColor;
  *((drawing1.color_list)+12) = bodyColor;
  *((drawing1.color_list)+13) = eyesColor;
  *((drawing1.color_list)+14) = eyesColor;


  drawing1.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing1.polygonNumber);
  *(drawing1.points_list) = e2a0d1p0points;
  *((drawing1.points_list)+1) = e2a0d1p1points;
  *((drawing1.points_list)+2) = e2a0d1p2points;
  *((drawing1.points_list)+3) = e2a0d1p3points;
  *((drawing1.points_list)+4) = e2a0d1p4points;
  *((drawing1.points_list)+5) = e2a0d1p5points;
  *((drawing1.points_list)+6) = e2a0d1p6points;
  *((drawing1.points_list)+7) = e2a0d1p7points;
  *((drawing1.points_list)+8) = e2a0d1p8points;
  *((drawing1.points_list)+9) = e2a0d1p9points;
  *((drawing1.points_list)+10) = e2a0d1p10points;
  *((drawing1.points_list)+11) = e2a0d1p11points;
  *((drawing1.points_list)+12) = e2a0d1p12points;
  *((drawing1.points_list)+13) = e2a0d1p13points;
  *((drawing1.points_list)+14) = e2a0d1p14points;

  //DRAWING LIST
  drawing_list = (DRAWINGTEMPLATE **)malloc(sizeof(DRAWINGTEMPLATE *)*2);
  *(drawing_list) = &drawing0;
  *(drawing_list+1) = &drawing1;

  states_list = (ANIMATION **)malloc(sizeof(ANIMATION *));
  *(states_list) = build_animation(2, 5, drawing_list);

  free(drawing_list);
  free(drawing0.sides_list);
  free(drawing0.color_list);
  free(drawing0.points_list);
  free(drawing1.sides_list);
  free(drawing1.color_list);
  free(drawing1.points_list);

  enemytype = create_objecttype(1, states_list);

  return enemytype;
}

OBJECTTYPE *build_enemytype3() {
  OBJECTTYPE *enemytype = NULL;
  DRAWINGTEMPLATE **drawing_list = NULL;
  ANIMATION **states_list = NULL;
  
  DRAWINGTEMPLATE drawing0;
  DRAWINGTEMPLATE drawing1;

  //DRAWING 0
  drawing0.polygonNumber = 12;

  drawing0.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing0.polygonNumber);
  *(drawing0.sides_list)   = &e2a0d0p0sides;
  *((drawing0.sides_list)+1) = &e2a0d0p0sides;
  *((drawing0.sides_list)+2) = &e2a0d0p0sides;
  *((drawing0.sides_list)+3) = &e2a0d0p0sides;
  *((drawing0.sides_list)+4) = &e2a0d0p0sides;
  *((drawing0.sides_list)+5) = &e2a0d0p0sides;
  *((drawing0.sides_list)+6) = &e2a0d0p0sides;
  *((drawing0.sides_list)+7) = &e2a0d0p0sides;
  *((drawing0.sides_list)+8) = &e2a0d0p0sides;
  *((drawing0.sides_list)+9) = &e2a0d0p0sides;
  *((drawing0.sides_list)+10) = &e2a0d0p0sides;
  *((drawing0.sides_list)+11) = &e2a0d0p0sides;
  
  drawing0.color_list = (float **)malloc(sizeof(float *)*drawing0.polygonNumber);
  *(drawing0.color_list) = bodyColor;
  *((drawing0.color_list)+1) = bodyColor;
  *((drawing0.color_list)+2) = bodyColor;
  *((drawing0.color_list)+3) = eyesColor;
  *((drawing0.color_list)+4) = eyesColor;
  *((drawing0.color_list)+5) = bodyColor;
  *((drawing0.color_list)+6) = bodyColor;
  *((drawing0.color_list)+7) = bodyColor;
  *((drawing0.color_list)+8) = bodyColor;
  *((drawing0.color_list)+9) = bodyColor;
  *((drawing0.color_list)+10) = bodyColor;
  *((drawing0.color_list)+11) = bodyColor;

  drawing0.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing0.polygonNumber);
  *(drawing0.points_list) = e3a0headp0points;
  *((drawing0.points_list)+1) = e3a0headp1points;
  *((drawing0.points_list)+2) = e3a0headp2points;
  *((drawing0.points_list)+3) = e3a0headp3points;
  *((drawing0.points_list)+4) = e3a0headp4points;
  *((drawing0.points_list)+5) = e3a0d0p0points;
  *((drawing0.points_list)+6) = e3a0d0p1points;
  *((drawing0.points_list)+7) = e3a0d0p2points;
  *((drawing0.points_list)+8) = e3a0d0p3points;
  *((drawing0.points_list)+9) = e3a0d0p4points;
  *((drawing0.points_list)+10) = e3a0d0p5points;
  *((drawing0.points_list)+11) = e3a0d0p6points;
  
  //DRAWING 1
  drawing1.polygonNumber = 12;

  drawing1.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing1.polygonNumber);
  *(drawing1.sides_list)   = &e2a0d1p0sides;
  *((drawing1.sides_list)+1) = &e2a0d1p0sides;
  *((drawing1.sides_list)+2) = &e2a0d1p0sides;
  *((drawing1.sides_list)+3) = &e2a0d1p0sides;
  *((drawing1.sides_list)+4) = &e2a0d1p0sides;
  *((drawing1.sides_list)+5) = &e2a0d1p0sides;
  *((drawing1.sides_list)+6) = &e2a0d1p0sides;
  *((drawing1.sides_list)+7) = &e2a0d1p0sides;
  *((drawing1.sides_list)+8) = &e2a0d1p0sides;
  *((drawing1.sides_list)+9) = &e2a0d1p0sides;
  *((drawing1.sides_list)+10) = &e2a0d1p0sides;
  *((drawing1.sides_list)+11) = &e2a0d1p0sides;

  drawing1.color_list = (float **)malloc(sizeof(float *)*drawing1.polygonNumber);
  *(drawing1.color_list) = bodyColor;
  *((drawing1.color_list)+1) = bodyColor;
  *((drawing1.color_list)+2) = bodyColor;
  *((drawing1.color_list)+3) = eyesColor;
  *((drawing1.color_list)+4) = eyesColor;
  *((drawing1.color_list)+5) = bodyColor;
  *((drawing1.color_list)+6) = bodyColor;
  *((drawing1.color_list)+7) = bodyColor;
  *((drawing1.color_list)+8) = bodyColor;
  *((drawing1.color_list)+9) = bodyColor;
  *((drawing1.color_list)+10) = bodyColor;
  *((drawing1.color_list)+11) = bodyColor;

  drawing1.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing1.polygonNumber);
  *(drawing1.points_list) = e3a0headp0points;
  *((drawing1.points_list)+1) = e3a0headp1points;
  *((drawing1.points_list)+2) = e3a0headp2points;
  *((drawing1.points_list)+3) = e3a0headp3points;
  *((drawing1.points_list)+4) = e3a0headp4points;
  *((drawing1.points_list)+5) = e3a0d1p0points;
  *((drawing1.points_list)+6) = e3a0d1p1points;
  *((drawing1.points_list)+7) = e3a0d1p2points;
  *((drawing1.points_list)+8) = e3a0d1p3points;
  *((drawing1.points_list)+9) = e3a0d1p4points;
  *((drawing1.points_list)+10) = e3a0d1p5points;
  *((drawing1.points_list)+11) = e3a0d1p6points;
 

  //DRAWING LIST
  drawing_list = (DRAWINGTEMPLATE **)malloc(sizeof(DRAWINGTEMPLATE *)*2);
  *(drawing_list) = &drawing0;
  *(drawing_list+1) = &drawing1;

  states_list = (ANIMATION **)malloc(sizeof(ANIMATION *));
  *(states_list) = build_animation(2, 5, drawing_list);

  free(drawing_list);
  free(drawing0.sides_list);
  free(drawing0.color_list);
  free(drawing0.points_list);
  free(drawing1.sides_list);
  free(drawing1.color_list);
  free(drawing1.points_list);

  enemytype = create_objecttype(1, states_list);

  return enemytype;
}

OBJECTTYPE *build_ship() {
  OBJECTTYPE *shiptype = NULL;
  DRAWINGTEMPLATE **drawing_list = NULL;
  ANIMATION **states_list = NULL;
  
  //Animation 0
  DRAWINGTEMPLATE drawing0;
  
  //Animation 1 - Destroyed ship
  DRAWINGTEMPLATE drawing1;
  DRAWINGTEMPLATE drawing2;

  unsigned int i = 0;

  //DRAWING 0
  drawing0.polygonNumber = 3;

  drawing0.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing0.polygonNumber);
  *(drawing0.sides_list)   = &shipBodySides;
  *((drawing0.sides_list)+1) = &shipBodySides;
  *((drawing0.sides_list)+2) = &shipTipSides;
  
  drawing0.color_list = (float **)malloc(sizeof(float *)*drawing0.polygonNumber);
  *(drawing0.color_list) = shipColor;
  *((drawing0.color_list)+1) = shipColor;
  *((drawing0.color_list)+2) = shipColor;

  drawing0.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing0.polygonNumber);
  *(drawing0.points_list) = shipa0d0p0points;
  *((drawing0.points_list)+1) = shipa0d0p1points;
  *((drawing0.points_list)+2) = shipa0d0p2points;
 
  //DRAWING 1
  drawing1.polygonNumber = 21;
  drawing2.polygonNumber = 21;

  drawing1.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing1.polygonNumber);
  drawing2.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing1.polygonNumber);
  for (i = 0; i != drawing1.polygonNumber; i++) {
    *(drawing1.sides_list+i) = &explosionSides;
    *(drawing2.sides_list+i) = &explosionSides;
  }

  drawing1.color_list = (float **)malloc(sizeof(float *)*drawing1.polygonNumber);
  *(drawing1.color_list+0) = explosionColor3;
  *(drawing1.color_list+1) = explosionColor3;
  *(drawing1.color_list+2) = explosionColor3;
  *(drawing1.color_list+3) = explosionColor3;
  *(drawing1.color_list+4) = explosionColor3;
  *(drawing1.color_list+5) = explosionColor3;
  *(drawing1.color_list+6) = explosionColor3;
  *(drawing1.color_list+7) = explosionColor3;
  *(drawing1.color_list+8) = explosionColor3;
  *(drawing1.color_list+9) = explosionColor3;
  *(drawing1.color_list+10) = explosionColor3;
  *(drawing1.color_list+11) = explosionColor1;
  *(drawing1.color_list+12) = explosionColor1;
  *(drawing1.color_list+13) = explosionColor3;
  *(drawing1.color_list+14) = explosionColor1;
  *(drawing1.color_list+15) = explosionColor1;
  *(drawing1.color_list+16) = explosionColor2;
  *(drawing1.color_list+17) = explosionColor1;
  *(drawing1.color_list+18) = explosionColor1;
  *(drawing1.color_list+19) = explosionColor2;
  *(drawing1.color_list+20) = explosionColor1;

drawing1.points_list = (float **)malloc(sizeof(float *)*drawing1.polygonNumber);
  *(drawing1.points_list+0) = shipa1d0p0points;
  *(drawing1.points_list+1) = shipa1d0p1points;
  *(drawing1.points_list+2) = shipa1d0p2points;
  *(drawing1.points_list+3) = shipa1d0p3points;
  *(drawing1.points_list+4) = shipa1d0p4points;
  *(drawing1.points_list+5) = shipa1d0p5points;
  *(drawing1.points_list+6) = shipa1d0p6points;
  *(drawing1.points_list+7) = shipa1d0p7points;
  *(drawing1.points_list+8) = shipa1d0p8points;
  *(drawing1.points_list+9) = shipa1d0p9points;
  *(drawing1.points_list+10) = shipa1d0p10points;
  *(drawing1.points_list+11) = shipa1d0p11points;
  *(drawing1.points_list+12) = shipa1d0p12points;
  *(drawing1.points_list+13) = shipa1d0p13points;
  *(drawing1.points_list+14) = shipa1d0p14points;
  *(drawing1.points_list+15) = shipa1d0p15points;
  *(drawing1.points_list+16) = shipa1d0p16points;
  *(drawing1.points_list+17) = shipa1d0p17points;
  *(drawing1.points_list+18) = shipa1d0p18points;
  *(drawing1.points_list+19) = shipa1d0p19points;
  *(drawing1.points_list+20) = shipa1d0p20points;

  //DRAWING 2

  drawing2.color_list = (float **)malloc(sizeof(float *)*drawing2.polygonNumber);
  *(drawing2.color_list+0) = explosionColor3;
  *(drawing2.color_list+1) = explosionColor3;
  *(drawing2.color_list+2) = explosionColor3;
  *(drawing2.color_list+3) = explosionColor3;
  *(drawing2.color_list+4) = explosionColor3;
  *(drawing2.color_list+5) = explosionColor3;
  *(drawing2.color_list+6) = explosionColor3;
  *(drawing2.color_list+7) = explosionColor3;
  *(drawing2.color_list+8) = explosionColor3;
  *(drawing2.color_list+9) = explosionColor3;
  *(drawing2.color_list+10) = explosionColor1;
  *(drawing2.color_list+11) = explosionColor1;
  *(drawing2.color_list+12) = explosionColor3;
  *(drawing2.color_list+13) = explosionColor1;
  *(drawing2.color_list+14) = explosionColor3;
  *(drawing2.color_list+15) = explosionColor1;
  *(drawing2.color_list+16) = explosionColor2;
  *(drawing2.color_list+17) = explosionColor1;
  *(drawing2.color_list+18) = explosionColor1;
  *(drawing2.color_list+19) = explosionColor2;
  *(drawing2.color_list+20) = explosionColor1;

drawing2.points_list = (float **)malloc(sizeof(float *)*drawing2.polygonNumber);
  *(drawing2.points_list+0) = shipa1d1p0points;
  *(drawing2.points_list+1) = shipa1d1p1points;
  *(drawing2.points_list+2) = shipa1d1p2points;
  *(drawing2.points_list+3) = shipa1d1p3points;
  *(drawing2.points_list+4) = shipa1d1p4points;
  *(drawing2.points_list+5) = shipa1d1p5points;
  *(drawing2.points_list+6) = shipa1d1p6points;
  *(drawing2.points_list+7) = shipa1d1p7points;
  *(drawing2.points_list+8) = shipa1d1p8points;
  *(drawing2.points_list+9) = shipa1d1p9points;
  *(drawing2.points_list+10) = shipa1d1p10points;
  *(drawing2.points_list+11) = shipa1d1p11points;
  *(drawing2.points_list+12) = shipa1d1p12points;
  *(drawing2.points_list+13) = shipa1d1p13points;
  *(drawing2.points_list+14) = shipa1d1p14points;
  *(drawing2.points_list+15) = shipa1d1p15points;
  *(drawing2.points_list+16) = shipa1d1p16points;
  *(drawing2.points_list+17) = shipa1d1p17points;
  *(drawing2.points_list+18) = shipa1d1p18points;
  *(drawing2.points_list+19) = shipa1d1p19points;
  *(drawing2.points_list+20) = shipa1d1p20points;
  
  //DRAWING LIST
  drawing_list = (DRAWINGTEMPLATE **)malloc(sizeof(DRAWINGTEMPLATE *)*2);
  *(drawing_list) = &drawing0;

  states_list = (ANIMATION **)malloc(sizeof(ANIMATION *)*2);
  *(states_list) = build_animation(1, 100, drawing_list);

  *(drawing_list) = &drawing1;
  *(drawing_list+1) = &drawing2;
  
  *(states_list+1) = build_animation(2, 4, drawing_list);

  free(drawing_list);
  free(drawing0.sides_list);
  free(drawing0.color_list);
  free(drawing0.points_list);

  free(drawing1.sides_list);
  free(drawing1.color_list);
  free(drawing1.points_list);
  
  free(drawing2.sides_list);
  free(drawing2.color_list);
  free(drawing2.points_list);

  shiptype = create_objecttype(1, states_list);

  return shiptype;
}

ANIMATION *build_shipshot() {
  DRAWINGTEMPLATE **drawing_list = NULL;  
  DRAWINGTEMPLATE drawing0;
  ANIMATION *animation;
  
  //DRAWING 0
  drawing0.polygonNumber = 1;

  drawing0.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing0.polygonNumber);
  *(drawing0.sides_list)   = &shotSides;
  
  drawing0.color_list = (float **)malloc(sizeof(float *)*drawing0.polygonNumber);
  *(drawing0.color_list) = shotColor;

  drawing0.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing0.polygonNumber);
  *(drawing0.points_list) = shot3p0points;
 
  //DRAWING LIST
  drawing_list = (DRAWINGTEMPLATE **)malloc(sizeof(DRAWINGTEMPLATE *));
  *(drawing_list) = &drawing0;

  animation = build_animation(1, 100, drawing_list);

  free(drawing_list);
  free(drawing0.sides_list);
  free(drawing0.color_list);
  free(drawing0.points_list);

  return animation;
}

ANIMATION *build_enemyshot1() {
  DRAWINGTEMPLATE **drawing_list = NULL;  
  DRAWINGTEMPLATE drawing0;
  ANIMATION *animation;
  
  //DRAWING 0
  drawing0.polygonNumber = 2;

  drawing0.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing0.polygonNumber);
  *(drawing0.sides_list)   = &shotSides;
  *((drawing0.sides_list)+1) = &shotSides;
  
  drawing0.color_list = (float **)malloc(sizeof(float *)*drawing0.polygonNumber);
  *(drawing0.color_list) = shotColor;
  *((drawing0.color_list)+1) = shotColor;

  drawing0.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing0.polygonNumber);
  *(drawing0.points_list) = shot1p0points;
  *((drawing0.points_list)+1) = shot1p1points;
 
  //DRAWING LIST
  drawing_list = (DRAWINGTEMPLATE **)malloc(sizeof(DRAWINGTEMPLATE *));
  *(drawing_list) = &drawing0;

  animation = build_animation(1, 100, drawing_list);

  free(drawing_list);
  free(drawing0.sides_list);
  free(drawing0.color_list);
  free(drawing0.points_list);

  return animation;
}

ANIMATION *build_enemyshot2() {
  DRAWINGTEMPLATE **drawing_list = NULL;  
  DRAWINGTEMPLATE drawing0;
  ANIMATION *animation;
  
  //DRAWING 0
  drawing0.polygonNumber = 5;

  drawing0.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawing0.polygonNumber);
  *(drawing0.sides_list)   = &shotSides;
  *((drawing0.sides_list)+1) = &shotSides;
  *((drawing0.sides_list)+2) = &shotSides;
  *((drawing0.sides_list)+3) = &shotSides;
  *((drawing0.sides_list)+4) = &shotSides;
  
  drawing0.color_list = (float **)malloc(sizeof(float *)*drawing0.polygonNumber);
  *(drawing0.color_list) = shotColor;
  *((drawing0.color_list)+1) = shotColor;
  *((drawing0.color_list)+2) = shotColor;
  *((drawing0.color_list)+3) = shotColor;
  *((drawing0.color_list)+4) = shotColor;

  drawing0.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawing0.polygonNumber);
  *(drawing0.points_list) = shot2p0points;
  *((drawing0.points_list)+1) = shot2p1points;
  *((drawing0.points_list)+2) = shot2p2points;
  *((drawing0.points_list)+3) = shot2p3points;
  *((drawing0.points_list)+4) = shot2p4points;
 
  //DRAWING LIST
  drawing_list = (DRAWINGTEMPLATE **)malloc(sizeof(DRAWINGTEMPLATE *));
  *(drawing_list) = &drawing0;

  animation = build_animation(1, 100, drawing_list);

  free(drawing_list);
  free(drawing0.sides_list);
  free(drawing0.color_list);
  free(drawing0.points_list);

  return animation;
}

DRAWING *build_defense() {
  /*for (i = 0; i < framesNumber; i++) {
    *(frames+i) = build_drawing((*(drawingtemplate_list+i))->polygonNumber,
				(*(drawingtemplate_list+i))->sides_list,
				(*(drawingtemplate_list+i))->points_list, 
				(*(drawingtemplate_list+i))->color_list
				);
  }*/

  DRAWING *defensedrawing;
  DRAWINGTEMPLATE defense;

  defense.polygonNumber = 1;
  defense.sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*defense.polygonNumber);
  *defense.sides_list = &defenseSides;
  defense.color_list = (float **)malloc(sizeof(float *)*defense.polygonNumber);
  *defense.color_list = bodyColor;
  defense.points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*defense.polygonNumber);
  *defense.points_list = defensep0points;
  
  defensedrawing = build_drawing(defense.polygonNumber,
				 defense.sides_list,
				 defense.points_list, 
				 defense.color_list
				 );

  free(defense.color_list);
  free(defense.points_list);
  free(defense.sides_list);
  return defensedrawing;
}

DRAWING *build_explosion() {
  DRAWING *drawing;
  DRAWINGTEMPLATE *drawtemp;
  unsigned int i = 0;

  drawtemp = (DRAWINGTEMPLATE *)malloc(sizeof(DRAWINGTEMPLATE));
  drawtemp->polygonNumber = 16;

  drawtemp->sides_list = (unsigned int **)malloc(sizeof(unsigned int *)*drawtemp->polygonNumber);
  drawtemp->color_list = (float **)malloc(sizeof(float *)*drawtemp->polygonNumber);
  drawtemp->points_list = (COORDINATE **)malloc(sizeof(COORDINATE *)*drawtemp->polygonNumber);
  for (i = 0; i != drawtemp->polygonNumber; i++) {
    *(drawtemp->sides_list+i) = &explosionSides;
    *(drawtemp->color_list+i) = explosionColor;
  }

  *(drawtemp->points_list+0) = explosionp0points;
  *(drawtemp->points_list+1) = explosionp1points;
  *(drawtemp->points_list+2) = explosionp2points;
  *(drawtemp->points_list+3) = explosionp3points;
  *(drawtemp->points_list+4) = explosionp4points;
  *(drawtemp->points_list+5) = explosionp5points;
  *(drawtemp->points_list+6) = explosionp6points;
  *(drawtemp->points_list+7) = explosionp7points;
  *(drawtemp->points_list+8) = explosionp8points;
  *(drawtemp->points_list+9) = explosionp9points;
  *(drawtemp->points_list+10) = explosionp10points;
  *(drawtemp->points_list+11) = explosionp11points;
  *(drawtemp->points_list+12) = explosionp12points;
  *(drawtemp->points_list+13) = explosionp13points;
  *(drawtemp->points_list+14) = explosionp14points;
  *(drawtemp->points_list+15) = explosionp15points;

  drawing = build_drawing(drawtemp->polygonNumber,
			  drawtemp->sides_list,
			  drawtemp->points_list, 
			  drawtemp->color_list
			  );
  free(drawtemp->sides_list);
  free(drawtemp->color_list);
  free(drawtemp->points_list);
  free(drawtemp);

  return drawing;
}
