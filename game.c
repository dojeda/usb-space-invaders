#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "resources.h"

extern OBJECTTYPE **objectTypes;
extern unsigned int objectTypeNumber;

extern ANIMATION **shotDefAnimations;
extern unsigned int shotDefNumber;

extern DRAWING *defenseDrawing;

void init_game() {
  score  = 0;
  lives  = 3;
  paused = 0;
  gameover = 0;
  leftbound  = 0.0;
  rightbound =  240.0;
  upperbound =  0.0;
  lowerbound =  185.0;
  level.speed = 0;
  last_delay = -1;
  begin_level(&level);
}

void init_help(LEVEL *helplevel) {
  unsigned int i;

  helplevel->enemyNumber = 12;
  helplevel->enemyset = (OBJECT *) malloc(sizeof(OBJECT)*helplevel->enemyNumber);
  
  for (i=0;i<4;i++) {
    create_object((helplevel->enemyset+i), 16.5+(15*i), 50, 0.5, 0, *(objectTypes+ENEMYTYPE1), 8.0, 10.0, 1, 10);
    create_object((helplevel->enemyset+i+4), 15+(15*i), 62.5, 0.5, 0, *(objectTypes+ENEMYTYPE2), 8.0, 10.0, 1, 10);
    create_object((helplevel->enemyset+i+8), 15+(15*i), 75, 0.5, 0, *(objectTypes+ENEMYTYPE3), 8.0, 10.0, 1, 10);
  }

  helpship = (OBJECT *) malloc(sizeof(OBJECT));
  create_object(helpship, 40, 175, 0, 0, *(objectTypes+SHIP), 14.0, 10.0, 1, 10);
  helpship->type->currentState = 0;
  helpship->visible = 1;

  helplevel->shipShotNumber = 1;
  helplevel->ship_shots = (SHOT *) malloc(sizeof(SHOT)*helplevel->shipShotNumber );

  for (i=0;i<helplevel->shipShotNumber;i++) {
    (helplevel->ship_shots+i)->position.x = 47;
    (helplevel->ship_shots+i)->position.y = 160+5*i;
    (helplevel->ship_shots+i)->velocity.x = 0;
    (helplevel->ship_shots+i)->velocity.y = -2;
    (helplevel->ship_shots+i)->animation = *(shotDefAnimations+SHIPSHOT);
    (helplevel->ship_shots+i)->visible = 1;
  }

  helplevel->enemyShotNumber = 4;
  helplevel->enemy_shots = (SHOT *) malloc(sizeof(SHOT)*helplevel->enemyShotNumber);

  for (i=0;i<(helplevel->enemyShotNumber)/2;i++) {
    (helplevel->enemy_shots+i)->position.x = 60 + 5*i;
    (helplevel->enemy_shots+i)->position.y = 90 + 35*i;
    (helplevel->enemy_shots+i)->velocity.x = 0;
    (helplevel->enemy_shots+i)->velocity.y = 0;
    (helplevel->enemy_shots+i)->animation = *(shotDefAnimations+ENEMYSHOT1);
    (helplevel->enemy_shots+i)->visible = 1;
  }
  for (i=(helplevel->enemyShotNumber)/2;i<helplevel->enemyShotNumber;i++) {
    (helplevel->enemy_shots+i)->position.x = 20 + 5*i;
    (helplevel->enemy_shots+i)->position.y = 90 + 12*i;
    (helplevel->enemy_shots+i)->velocity.x = 0;
    (helplevel->enemy_shots+i)->velocity.y = 0;
    (helplevel->enemy_shots+i)->animation = *(shotDefAnimations+ENEMYSHOT2);
    (helplevel->enemy_shots+i)->visible = 1;
  }

  helplevel->defenseNumber = 1;
  helplevel->defenseset = (DEFENSE **)malloc(sizeof(DEFENSE *));
  for (i=0; i<3;i++) {
    *(helplevel->defenseset+i) = create_defense(20*(i+1)-8,140);
  }

  for (i=0;i<objectTypeNumber;i++) {
    OBJECTTYPE *objtype = *(objectTypes+i);
    ANIMATION *animation = *((objtype->states));
    animation->delay = 5;
  }

  helplevel->speed = 0;
}

DEFENSE *create_defense(COORDINATE x, COORDINATE y) {
  DEFENSE *defense;
  
  defense = (DEFENSE *)malloc(sizeof(DEFENSE));
  
  defense->defenseDrawing = defenseDrawing;
  defense->position.x = x;
  defense->position.y = y;
  defense->width =  ((*defenseDrawing->polygons)->points+2)->x;
  defense->height = ((*defenseDrawing->polygons)->points+2)->y;

  reset_defense(defense);

  return defense;
}

void reset_defense(DEFENSE *defense) {
  defense->parts[0] = 1;
  defense->parts[1] = 1;
  defense->parts[2] = 1;
  defense->health = 3;
}

void create_object(OBJECT *object,
		   COORDINATE posx, 
		   COORDINATE posy,
		   COORDINATE velx,
		   COORDINATE vely,
		   OBJECTTYPE *type,
		   float width,
		   float height,
		   unsigned short visible,
		   short explosion_delay) {
  object->position.x = posx;
  object->position.y = posy;
  object->velocity.x = velx;
  object->velocity.y = vely;
  object->type = type;
  object->width = width;
  object->height = height;
  object->visible = visible;
  object->explosion_delay = explosion_delay;
}

void begin_level(LEVEL *level) {
  unsigned int i;

  level->enemyNumber = 55;
  level->enemyset = (OBJECT *) malloc(sizeof(OBJECT)*level->enemyNumber);
  
  for (i=0;i<11;i++) {
    create_object((level->enemyset+i), 1.5+(15*i), 10, 0.5, 0, *(objectTypes+ENEMYTYPE1), 8.0, 10.0, 1, 10);
    create_object((level->enemyset+i+11), (15*i), 22.5, 0.5, 0, *(objectTypes+ENEMYTYPE2), 10.0, 10.0, 1, 10);
    create_object((level->enemyset+i+22), (15*i), 35, 0.5, 0, *(objectTypes+ENEMYTYPE2), 10.0, 10.0, 1, 10);
    create_object((level->enemyset+i+33), (15*i), 47.5, 0.5, 0, *(objectTypes+ENEMYTYPE3), 10.0, 10.0, 1, 10);
    create_object((level->enemyset+i+44), (15*i), 60, 0.5, 0, *(objectTypes+ENEMYTYPE3), 10.0, 10.0, 1, 10);
  }

  ship = (OBJECT *) malloc(sizeof(OBJECT));
  create_object(ship, 120, 175, 0, 0, *(objectTypes+SHIP), 14.0, 10.0, 1, 10);
  ship->type->currentState = 0;

  level->shipShotNumber = 1;
  level->ship_shots = (SHOT *) malloc(sizeof(SHOT)*level->shipShotNumber );

  for (i=0;i<level->shipShotNumber;i++) {
    (level->ship_shots+i)->position.x = 200+10*i;
    (level->ship_shots+i)->position.y = 100+20*i;
    (level->ship_shots+i)->velocity.x = 0;
    (level->ship_shots+i)->velocity.y = -2;
    (level->ship_shots+i)->animation = *(shotDefAnimations+SHIPSHOT);
    (level->ship_shots+i)->visible = 0;
  }

  level->enemyShotNumber = 1 + level->speed;
  level->enemy_shots = (SHOT *) malloc(sizeof(SHOT)*level->enemyShotNumber);

  for (i=0;i<(level->enemyShotNumber)/2;i++) {
    (level->enemy_shots+i)->position.x = 0;
    (level->enemy_shots+i)->position.y = 0;
    (level->enemy_shots+i)->velocity.x = 0;
    (level->enemy_shots+i)->velocity.y = 0;
    (level->enemy_shots+i)->animation = *(shotDefAnimations+ENEMYSHOT1);
    (level->enemy_shots+i)->visible = 0;
  }
  for (i=(level->enemyShotNumber)/2;i<level->enemyShotNumber;i++) {
    (level->enemy_shots+i)->position.x = 0;
    (level->enemy_shots+i)->position.y = 0;
    (level->enemy_shots+i)->velocity.x = 0;
    (level->enemy_shots+i)->velocity.y = 0;
    (level->enemy_shots+i)->animation = *(shotDefAnimations+ENEMYSHOT2);
    (level->enemy_shots+i)->visible = 0;
  }

  level->defenseNumber = 3;
  level->defenseset = (DEFENSE **)malloc(sizeof(DEFENSE *));
  for (i=0; i<3;i++) {

    *(level->defenseset+i) = create_defense(60*(i+1)-8,140);
  }

  for (i=0;i<objectTypeNumber;i++) {
    OBJECTTYPE *objtype = *(objectTypes+i);
    ANIMATION *animation = *((objtype->states));
    animation->delay = 5;
  }

  shot_delay = 25;
  dead_delay = -1;
  enemy_kills = 0;

}

/**
 * actualiza el nivel... documentare mejor
 */
void update_gamestate() {
  unsigned int i;

  if (paused | gameover) return;

  // delay por matar al ultimo enemigo
  if (last_delay > 0) {
    last_delay--;
    return;
  } if (last_delay == 0) {
    last_delay--;
    level.speed++;
    begin_level(&level);
    for (i=0;i<objectTypeNumber;i++) {
      OBJECTTYPE *objtype = *(objectTypes+i);
      ANIMATION *animation = *((objtype->states));
      animation->delay = 5;
    }
  }


  // delay por muerte de la nave
  if (dead_delay > 0) {
    dead_delay--;
    return;
  } else if (dead_delay == 0) {
    dead_delay--;
    lives--;
    if (lives > 0) {
      ship->type->currentState = 0;
      // borro todos los disparos... para ser mas amigables
      for (i=0;i<level.enemyShotNumber;i++) {
	(level.enemy_shots+i)->visible = 0;
      }
      for (i=0;i<level.shipShotNumber;i++) {
	(level.ship_shots+i)->visible = 0;
      }
    } else {
      gameover = 1;
    }
    return;
  }
  
  // MOVIMIENTO DE OBJETOS:
  // movimiento de enemigos
  for (i=0;i<level.enemyNumber;i++) {
    if ((level.enemyset+i)->visible) {
      (level.enemyset+i)->position.x += (level.enemyset+i)->velocity.x;
      (level.enemyset+i)->position.y += (level.enemyset+i)->velocity.y;
      // este alien tiene la posibilidad de disparar
      if (rand()%(abs((level.enemyset+i)->position.x - ship->position.x) + 1) == 0) {
	if (shot_delay == 0) {
	  enemy_shoot(level.enemyset+i);
	  shot_delay = 25 - 5 * level.speed;
	  // por si acaso esta muy adelantada la velocidad MUAJAJA
	  if ( shot_delay < 0 ) {
	    shot_delay = 0;
	  }
	} else {
	  shot_delay = (shot_delay <= 0) ? 0 : shot_delay-1;
	}
      }
    }
  }
  
  // movimiento de nave
  ship->position.x += ship->velocity.x;
  ship->position.y += ship->velocity.y; // esto deberia ser innecesario

  // movimiento de disparos
  for (i=0;i<level.shipShotNumber;i++) {
    if ((level.ship_shots+i)->visible) {
      (level.ship_shots+i)->position.x += (level.ship_shots+i)->velocity.x;
      (level.ship_shots+i)->position.y += (level.ship_shots+i)->velocity.y;
    }
  }
  for (i=0;i<level.enemyShotNumber;i++) {
    if ((level.enemy_shots+i)->visible) {
      (level.enemy_shots+i)->position.x += (level.enemy_shots+i)->velocity.x;
      (level.enemy_shots+i)->position.y += (level.enemy_shots+i)->velocity.y;
    }
  }

  // todo: deteccion de colision de objectos/disparos
  detectShotCollision();
  
  // deteccion de colision de enemigos/borde
  detectEnemyCollision();

  // deteccion de colision de nave/borde
  detectShipCollision();
 
  // deteccion de disparos perdidos
  detectMissedShots();
}

/**
 * deteccion de colisiones entre:
 * disparos-enemigos / nave
 * disparos-nave / aliens
 * disparos-* / defensas
 */
void detectShotCollision() {
  unsigned int i,j,k;
  // disparos-nave / aliens
  for (i=0;i<level.shipShotNumber;i++) {
    SHOT *nextshot = (level.ship_shots+i);
    if (nextshot->visible) {

      for (j=0;j<level.enemyNumber;j++) {
	OBJECT *nextalien = (level.enemyset+j);
	if ( 
	    nextalien->visible                                               &&  // es visible el alien
	    nextshot->visible                                                &&  // es visible el disparo
	    nextalien->position.x < nextshot->position.x                     &&  // borde izquierdo
	    nextshot->position.x  < nextalien->position.x + nextalien->width &&  // borde derecho
	    nextalien->position.y < nextshot->position.y                     &&  // borde superior
	    nextshot->position.y  < nextalien->position.y + nextalien->height     // borde inferior
	    ) {
	  // hay colision
	  nextalien->visible = 0;
	  nextshot->visible = 0;

	  // nuevo: vida cada 1000 puntos
	  unsigned int oldscore = score; 

	  // calculo el score
	  if (nextalien->type == *(objectTypes+ENEMYTYPE1))
	    score += 40;
	  else if (nextalien->type == *(objectTypes+ENEMYTYPE2))
	    score += 20;
	  else if (nextalien->type == *(objectTypes+ENEMYTYPE3))
	    score += 10;
	
	  enemy_kills++;
	  

	  if (oldscore%1000 > score%1000)
	    lives++;
	  
	  
	  if (enemy_kills == level.enemyNumber) {
	    last_delay = 50;
	    return;
	  } else {
	    // aumento de la velocidad (testing)
	    if ((enemy_kills%11) == 0 && enemy_kills < 55) {
	      for (k=0;k<objectTypeNumber;k++) {
		OBJECTTYPE *objtype = *(objectTypes+k);
		ANIMATION *animation = *((objtype->states));
		animation->delay -= 1;
	      }
	      for (k=0;k<level.enemyNumber;k++) {
		if ((level.enemyset+k)->visible)
		  (level.enemyset+k)->velocity.x *= 4.0/3.0;
	      }
	    }
	  }
	  // destruyo los objetos
	  // todo: destroynave
	}
      }

    }
  }

  // disparos-enemigos / nave
  for (i=0;i<level.enemyShotNumber;i++) {
    SHOT *nextshot = (level.enemy_shots+i);
    if ( 
	nextshot->visible                                     &&  // es visible el disparo
	ship->position.x     < nextshot->position.x           &&  // borde izquierdo
	nextshot->position.x < ship->position.x + ship->width &&  // borde derecho
	ship->position.y     < nextshot->position.y           &&  // borde superior
	nextshot->position.y < ship->position.y + ship->height    // borde inferior
	 ) {
      // hay colision
      //printf("BOOM-NAVE %d\n",i);
      //printf("state before %d\n",ship->type->currentState);
      ship->type->currentState = 1;
      //Printf("state  after %d\n",ship->type->currentState);
      nextshot->visible = 0;
      dead_delay = 50;
    }
  }
  
  // disparos-enemigo / defensas
  detectDefenseCollision(level.enemy_shots, level.enemyShotNumber, 1);
  // disparos-nave / defensas
  detectDefenseCollision(level.ship_shots, level.shipShotNumber, 0);
}

void detectDefenseCollision(SHOT *shotList, unsigned int shotNumber, int isComingDown) {
  unsigned int i = 0;
  for (i=0;i<shotNumber;i++) {
    SHOT *nextshot = (shotList+i);
    COORDINATE minheight = ((*level.defenseset)->position.y);
    COORDINATE maxheight = minheight+((*level.defenseset)->height*3);
    unsigned int j = 0;

    //Si el tiro no está a la altura de las defensas, no vale la pena seguir calculando
    if (!nextshot->visible) continue;
    if (nextshot->position.y < minheight || nextshot->position.y > maxheight) {
      continue;
    }
    
    for (j=0; j<level.defenseNumber; j++) {
      DEFENSE *nextdef = *(level.defenseset+j);

      //Si el tiro está dentro del area de la defensa, hay que
      //chequear si el tiro colisiona con alguna parte visible
      //de la defensa.
      if (nextshot->position.x >= nextdef->position.x &&
	  nextshot->position.x <  nextdef->position.x+nextdef->width) {
	int k = 0;
	if (!isComingDown) {
	  for (k = 2; k >= 0; k--) {
	    if (nextdef->parts[k] == 1) {
	      nextdef->parts[k] = 0;
	      nextdef->health--;
	      nextshot->visible = 0;
	      goto continue_nextshot;
	    }
	  }
	} else {
	  for (k = 0; k < 3; k++) {
	    if (nextdef->parts[k] == 1) {
	      nextdef->parts[k] = 0;
	      nextdef->health--;
	      nextshot->visible = 0;
	      goto continue_nextshot;
	    }
	  }
	}
      }
    }
    
  continue_nextshot:;
  }
}



/**
 * deteccion de disparos que hay que eliminar porque ya se salieron
 * del borde pintable y no haran mas da'no
 */
void detectMissedShots() {
  unsigned int i;
  // los disparos de la nave vs el limite superior
  for (i=0;i<level.shipShotNumber;i++) {
    if ( (level.ship_shots+i)->visible &&
	 (level.ship_shots+i)->position.y < upperbound) {
      //printf("bound shipshots - borde superior\n");
      (level.ship_shots+i)->visible = 0;
    }
  }
  // los disparos de los enemigos vs el limite inferior
  for (i=0;i<level.enemyShotNumber;i++) {
    if ( (level.enemy_shots+i)->visible &&
	 (level.enemy_shots+i)->position.y > lowerbound) {
      //printf("bound enemyshots - borde inferior\n");
      (level.enemy_shots+i)->visible = 0;
    }
  }    
}

/**
 * deteccion de enemigos que se salen de los limites de su audaz
 * movimiento de ataque hacia la tierra
 */
void detectEnemyCollision() {
  unsigned int i;
  float min =  1000;
  float max = -1000;
  float low =     0;

  for (i=0;i<level.enemyNumber;i++) {
    OBJECT next = *(level.enemyset+i);
    if (next.visible) {
      if (next.position.x < min) {
	min = next.position.x;
      }
      if (next.position.x > max) {
	max = next.position.x;
      }
      if (next.position.y + next.height > low) {
	low = next.position.y + next.height;
      }
    }
  }

  if (low >= lowerbound) {
    gameover = 1;
    return;
  }

  if (min < leftbound) {
    //printf("bound enemigos - borde izquierdo\n");
    for (i=0;i<level.enemyNumber;i++) {
      OBJECT *next = (level.enemyset+i);
      next->velocity.x *= -1;
      next->position.y += 10;
    }
    detectDefenseDestruction();
  }
  if (max > rightbound) {
    //printf("bound enemigos - borde derecho\n");
    for (i=0;i<level.enemyNumber;i++) {
      OBJECT *next = (level.enemyset+i);
      next->velocity.x *= -1;
      next->position.y += 10;
    }
    detectDefenseDestruction();
  }
} 

void detectDefenseDestruction() {
  int i = 0;
  float min = 1000;
  static int defensesDestroyed = 0;
  
  if (defensesDestroyed) return;

  //Buscando la altura del marciano que este mas abajo
  for (i = 4; i >= 0; i--) {
    int j = 0;
    int isEmpty = 1;
    for (j = 0; j != 11; j++) {
      OBJECT *next = (level.enemyset+(i*11)+j);
      if (next->visible) {
	isEmpty = 0;
	break;
      }
    }
    if (!isEmpty) {
      OBJECT *enemy = (level.enemyset+(i*11)+j);
      min = enemy->position.y+enemy->height;
      //printf("min is in monster %d, %d\n", j, i);
      break;
    }
  }
  
  if (min > (*level.defenseset)->position.y) {
    defensesDestroyed = 1;
    
    for (i = 0; i < 3; i++) {
      int j = 0;
      DEFENSE *nextdef = *(level.defenseset+i);
      for (j = 0; j < 3; j++) {
	nextdef->parts[j] = 0;
      }
    }
  }
}

/**
 * deteccion de cuando la nave llega a los bordes permitidos
 */
void detectShipCollision() {
  if (ship->position.x < leftbound) {
    //printf("ship afuera left\n");
    ship->position.x -= ship->velocity.x;
    ship->velocity.x  = 0;
  } else if (ship->position.x > rightbound) {
    //printf("ship afuera right\n");
    ship->position.x -= ship->velocity.x;
    ship->velocity.x = 0;
  }
  // extra para los cheaters
  if (ship->position.y < upperbound) {
    ship->position.y -= ship->velocity.y;
    ship->velocity.y  = 0;
  } else if (ship->position.y > lowerbound) {
    ship->position.y -= ship->velocity.y;
    ship->velocity.y = 0;
  }
} 

void ship_shoot() {
  unsigned int i;
  
  if (paused || gameover || dead_delay > 0 || last_delay > 0) return;

  // buscamos que disparo esta libre
  for (i=0;i<level.shipShotNumber;i++) {
    if (!(level.ship_shots+i)->visible) {
      (level.ship_shots+i)->position.x = ship->position.x + ship->width/2;
      (level.ship_shots+i)->position.y = ship->position.y;
      (level.ship_shots+i)->velocity.x =  0;
      (level.ship_shots+i)->velocity.y = -6;
      (level.ship_shots+i)->visible = 1;
    }
  }
}

void enemy_shoot(OBJECT *enemy) {
  unsigned int i;
  if (paused || gameover || dead_delay > 0 || last_delay > 0) return;

  // buscamos que disparo esta libre
  for (i=0;i<level.enemyShotNumber;i++) {
    if (!(level.enemy_shots+i)->visible) {
      (level.enemy_shots+i)->position.x = enemy->position.x + enemy->width/2;
      (level.enemy_shots+i)->position.y = enemy->position.y + enemy->height/2;
      (level.enemy_shots+i)->velocity.x = 0;
      (level.enemy_shots+i)->visible = 1;
      // tipo de disparo random
      if (rand()%2) {
	(level.enemy_shots+i)->animation = *(shotDefAnimations+ENEMYSHOT1);
	(level.enemy_shots+i)->velocity.y = 2;
      } else {
	(level.enemy_shots+i)->animation = *(shotDefAnimations+ENEMYSHOT2);
	(level.enemy_shots+i)->velocity.y = 4;
      }
      //paused = 1;
      return;
    }
  }
}
