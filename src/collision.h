#include "hero.h"
#include "room.h"
#include "enemy.h"

bool CheckHeroTileCollision(Hero* hero, Tile tiles[ROOM_ROWS][ROOM_COLS], float dt);

bool CheckHeroEnemyCollision(Hero* hero, Enemy enemy[MAX_ENEMIES], Enemy** attacker);

bool CheckSwordEnemyCollision(Vector2 swordPos, Vector2 swordPivot, Enemy* enemy);
