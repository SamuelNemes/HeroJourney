#pragma once

#include "raylib.h"
#include "hero.h"
#include "room.h"
#include "map.h"
#include "tile.h"
#include "enemy.h"
#include "sword.h"

void DrawHero(Hero* hero, Texture2D heroSheet, Texture2D swordSheet);
void DrawSword(Sword* sword, Texture2D swordSheet);
void DrawEnemy(Enemy* enemy);
void DrawRoom(Room* room, Texture2D tileSheet);
void DrawMap(Map* map, Texture2D tileSheet);

void DrawHeroTransition(Hero* hero, Texture2D heroSheet, int offset, Direction direction);
void DrawMapTransition(Map* map, Texture2D tileSheet);
void DrawRoomTransition(Room* currentRoom, Room* nextRoom, Direction direction, int offset, Texture2D tileSheet);

void DrawMenu(int health, int maxHealth, Texture2D menu, Texture2D hearts, Texture2D heroCloseup);
