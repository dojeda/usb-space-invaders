#ifndef DATA_H
#define DATA_H

typedef float COORDINATE;

typedef struct _POINT {
  COORDINATE x;
  COORDINATE y;
  //  float *color;
} POINT;

typedef struct _POLYGON {
  //  char isUnicolor;
  float *color;
  unsigned int sides;
  POINT *points;
} POLYGON;

typedef struct _DRAWING {
  unsigned int polygonNumber;
  POLYGON **polygons;
} DRAWING;

typedef struct _ANIMATION {
  unsigned int framesNumber;
  unsigned int delay;
  unsigned int currentDelay;
  unsigned int currentFrame;
  DRAWING **frames;
} ANIMATION;

typedef struct _OBJECTTYPE {
  unsigned int statesNumber;
  unsigned int currentState;
  ANIMATION **states;
} OBJECTTYPE;

typedef struct _DRAWINGTEMPLATE {
  unsigned int polygonNumber;
  unsigned int **sides_list;
  float **color_list;
  COORDINATE **points_list;
} DRAWINGTEMPLATE;

DRAWING *build_drawing(unsigned int polygonNumber, 
		       unsigned int **sidesList, 
		       COORDINATE **pointsList, 
		       float **colors);

POLYGON *build_polygon(unsigned int *pointNumber, 
		       COORDINATE *points, 
		       float r, 
		       float g, 
		       float b);

ANIMATION *build_animation(unsigned int framesNumber, 
			   unsigned int delay, 
			   DRAWINGTEMPLATE **drawingtemplate_list);

POINT *create_point(COORDINATE x, 
		    COORDINATE y);
void destroy_point(POINT *point);

POLYGON *create_polygon(float *color, 
			unsigned int sides, 
			POINT *points);
void destroy_polygon(POLYGON *polygon);

DRAWING *create_drawing(unsigned int polygonNumber, 
			POLYGON **polygons);
void destroy_drawing(DRAWING *drawing);

ANIMATION *create_animation(unsigned int framesNumber, 
			    unsigned int delay, 
			    DRAWING **frames);
void destroy_animation(ANIMATION *animation);

OBJECTTYPE *create_objecttype(unsigned int statesNumber, ANIMATION **states);
void destroy_objecttype(OBJECTTYPE *objecttype);

void nextFrame(OBJECTTYPE *object);
#endif
