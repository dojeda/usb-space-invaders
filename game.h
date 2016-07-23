#ifndef GAME_H
#define GAME_H

#include "data.h"

typedef struct _OBJECT {
  OBJECTTYPE *type;
  POINT position;
  POINT velocity;
  float width;
  float height;
  unsigned short visible;
  short explosion_delay;
} OBJECT;

typedef struct _SHOT {
  ANIMATION *animation;
  POINT position;
  POINT velocity;
  unsigned short visible;
} SHOT;

typedef struct _DEFENSE {
  DRAWING *defenseDrawing;
  POINT position;
  short parts[3];
  unsigned int health;
  float width;
  float height;
} DEFENSE;

typedef struct _LEVEL {
  OBJECT *enemyset;
  DEFENSE **defenseset;
  SHOT *ship_shots;
  SHOT *enemy_shots;
  unsigned int enemyNumber;
  unsigned int defenseNumber;
  unsigned int enemyShotNumber;
  unsigned int shipShotNumber;
  unsigned int speed;
} LEVEL;

OBJECT *ship;
OBJECT *helpship;
LEVEL level;
LEVEL helplevel;
unsigned int score;
unsigned int lives;
unsigned short help;
unsigned short paused;
unsigned short gameover;
unsigned int enemy_kills;
COORDINATE  leftbound;
COORDINATE rightbound;
COORDINATE upperbound;
COORDINATE lowerbound;

int shot_delay;
int dead_delay;
int last_delay;

void init_game();
void init_help();

DEFENSE *create_defense(COORDINATE x, COORDINATE y);
void reset_defense(DEFENSE *defense);
void create_object(OBJECT *object,
		   COORDINATE posx, 
		   COORDINATE posy,
		   COORDINATE velx,
		   COORDINATE vely,
		   OBJECTTYPE *type,
		   float width,
		   float height,
		   unsigned short visible,
		   short explosion_delay);

void begin_level(LEVEL *level);

void update_gamestate();
void detectDefenseCollision(SHOT *shotList, unsigned int shotNumber, int isComingDown);
void detectShotCollision();
void detectShipCollision();
void detectEnemyCollision();
void detectMissedShots();
void detectDefenseDestruction();
void ship_shoot();
void enemy_shoot(OBJECT *enemy);

#endif
