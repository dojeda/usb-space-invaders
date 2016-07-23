#ifndef RESOURCES_H
#define RESOURCES_H

#include "data.h"

#define SHIP       0
#define ENEMYTYPE1 1
#define ENEMYTYPE2 2
#define ENEMYTYPE3 3

#define SHIPSHOT   0
#define ENEMYSHOT1 1
#define ENEMYSHOT2 2

/* PROTOTIPOS */
void init_resources();
OBJECTTYPE *build_enemytype1();
OBJECTTYPE *build_enemytype2();
OBJECTTYPE *build_enemytype3();
OBJECTTYPE *build_ship();
ANIMATION *build_shipshot();
ANIMATION *build_enemyshot1();
ANIMATION *build_enemyshot2();
DRAWING *build_defense();
DRAWING *build_explosion();

#endif
