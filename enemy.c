/*******************************************************************************
 * SPACE INVADERS 2004
 *
 * enemy.c
 *
 * Implementacion de las rutinas de creacion, destruccion y manipulacion de
 * estructuras de datos del juego. Aqui se manejan solamente puntos de
 * poligonos y cosas por el estilo, no se interactua directamente con GLUT.
 *
 * Programacion: Ciro Duran  #00-32749
 *               David Ojeda #00-33151
 *
 * Fecha: 3-X-2004 11.24pm
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

/**
 * create_point
 * Tomando una coordenada x, y una y, devuelve una estructura POINT.
 */
POINT *create_point(COORDINATE x, COORDINATE y) {
  POINT *point = (POINT *)malloc(sizeof(POINT));
  
  point->x = x;
  point->y = y;
  
  return point;
}

/**
 * destroy_point
 * Saca de memoria el punto que ha sido creado con create_point
 */
void destroy_point(POINT *point) {
  if (point == NULL)
  {
    perror("destroy_point: destruyendo un apuntador a NULL.");
    exit(-1);
  }

  free(point);
}

/**
 * create_polygon
 * Tomando el color, el numero de lados, y los puntos que tiene, crea un 
 * poligono.
 */
POLYGON *create_polygon(float *color, unsigned int sides, POINT *points) {
  POLYGON *polygon = (POLYGON *)malloc(sizeof(POLYGON));

  polygon->color = color;
  polygon->sides = sides;
  polygon->points = points;
  
  return polygon;
}

/**
 * destroy_polygon
 * Destruye el apuntador al poligono que se le pase.
 * NOTA: NO destruye los apuntadores a los puntos que contiene, estos deben ser
 *       destruidos explicitamente por el programador.
 */
void destroy_polygon(POLYGON *polygon) {
  
  if (polygon == NULL)
  {
    perror("destroy_polygon: destruyendo un apuntador a NULL");
    exit(-1);
  }

  free(polygon);
}

/**
 * create_drawing
 * Dado el numero de poligonos que tiene, y la lista de poligonos, crea un 
 * dibujo. Note que el orden en el que esten los poligonos en la lista 
 * determina el orden en el que son dibujados.
 */
DRAWING *create_drawing(unsigned int polygonNumber, POLYGON **polygons) {
  DRAWING *drawing = (DRAWING *)malloc(sizeof(DRAWING));
  
  drawing->polygonNumber = polygonNumber;
  drawing->polygons = polygons;

  return drawing;
}

/**
 * destroy_drawing
 * Destruye el dibujo que indica el apuntador que se le pase.
 * NOTA: La funcion NO destruye los poligonos que contiene, estos deben ser
 *       destruidos explicitamente por el programador.
 */
void destroy_drawing(DRAWING *drawing) {
  if (drawing == NULL)
  {
    perror("destroy_drawing: destruyendo un apuntador a NULL");
    exit(-1);
  }
  
  free(drawing);
}

/**
 * create_animation
 * Dado el numero de frames, el retardo entre frame y frame, y la lista de dibujos,
 * se crea una animacion.
 */
ANIMATION *create_animation(unsigned int framesNumber, unsigned int delay, DRAWING **frames) {
  ANIMATION *animation = (ANIMATION *)malloc(sizeof(ANIMATION));

  animation->framesNumber = framesNumber;
  animation->delay = delay;
  animation->currentDelay = 0;
  animation->currentFrame = 0;
  animation->frames = frames;

  return animation;
}

/**
 * destroy_animation
 * Destruye la animacion a la que el apuntador este indicando.
 * NOTA: La funcion NO destruye los dibujos que contiene, estos deben ser
 *       destruidos explicitamente por el programador.
 */
void destroy_animation(ANIMATION *animation) {
  if (animation == NULL)
  {
    perror("destroy_animation: destruyendo un apuntador a NULL");
    exit(-1);
  }

  free(animation);
}

/**
 * create_objecttype
 * Dado los datos requeridos se crea un enemigo.
 * NOTA: Estos datos para la version 0.1 todavia no estan completos y continuan
 *       en crecimiento. Espere mas pronto!
 */
OBJECTTYPE *create_objecttype(unsigned int statesNumber, ANIMATION **states) {
  OBJECTTYPE *objecttype =(OBJECTTYPE *)malloc(sizeof(OBJECTTYPE));

  objecttype->statesNumber = statesNumber;
  objecttype->states = states;
  objecttype->currentState = 0;

  return objecttype;
}

/**
 * destroy_objecttype
 * Destruye el enemigo que indique el apuntador que se le pase
 * NOTA: No destruye el 
 */
void destroy_objecttype(OBJECTTYPE *objecttype) {
  if (objecttype == NULL)
  {
    perror("destroy_objecttype: destruyendo un apuntador a NULL");
    exit(-1);
  }
  
  free(objecttype);
}

ANIMATION *build_animation(unsigned int framesNumber, unsigned int delay, DRAWINGTEMPLATE **drawingtemplate_list) {
  ANIMATION *animation = NULL;
  DRAWING **frames = (DRAWING **)malloc(sizeof(DRAWING *)*framesNumber);
  unsigned int i = 0;

  for (i = 0; i < framesNumber; i++) {
    *(frames+i) = build_drawing((*(drawingtemplate_list+i))->polygonNumber,
				(*(drawingtemplate_list+i))->sides_list,
				(*(drawingtemplate_list+i))->points_list, 
				(*(drawingtemplate_list+i))->color_list
				);
  }
  
  animation = create_animation(framesNumber, delay, frames);
  
  return animation;
}

DRAWING *build_drawing(unsigned int polygonNumber, unsigned int **sidesList, COORDINATE **pointsList, float **colors) {
  DRAWING *drawing = NULL;
  POLYGON **polygon_list = (POLYGON **)malloc(sizeof(POLYGON *)*polygonNumber);
  unsigned int i = 0;

  for (i = 0; i < polygonNumber; i++) {
    *(polygon_list+i) = build_polygon((*(sidesList+i)), 
				      *(pointsList+i), 
				      **(colors+i), 
				      *(*(colors+i)+1), 
				      *(*(colors+i)+2)
				      );
  }
  
  drawing = create_drawing(polygonNumber, polygon_list);

  return drawing;
}

POLYGON *build_polygon(unsigned int *pointNumber, COORDINATE *points, float r, float g, float b) {
  POLYGON *polygon = NULL;
  POINT *point_list = NULL;
  float *color = NULL;
  unsigned int sides = 0;
  unsigned int i = 0;
  
  //Construyendo los puntos
  sides = (*pointNumber)  ;
  point_list = (POINT *)malloc(sizeof(POINT)*sides);
  
  for (i = 0; i < sides; i++) {
    (point_list+i)->x = *(points+2*i);
    (point_list+i)->y = *(points+1+2*i);
  }
  
  //Construyendo colores
  color = (float *)malloc(sizeof(float)*3);
  *(color) = r;
  *(color+1) = g;
  *(color+2) = b;
  
  polygon = create_polygon(color, sides, point_list);

  return polygon;
}
