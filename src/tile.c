#include "tile.h"
#include "constants.h"

void LoadTile(Tile* tile, int type, int row, int col){
	tile->type = type;
	tile->pos = (Rectangle){(col * TILE_SIZE), (row * TILE_SIZE), TILE_SIZE, TILE_SIZE};
	switch(tile->type){
		case DIRT:
			tile->isSolid = false;
			break;
		case COBBLE:
			tile->isSolid = true;
			break;
		case GRASS:
			tile->isSolid = false;
			break;
	}
}

Rectangle getTileRect(tileType tile){
	switch(tile){
		case DIRT:
			return (Rectangle){0, 0, TILE_SIZE, TILE_SIZE};
		case COBBLE:
			return (Rectangle){TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
		case GRASS:
			return (Rectangle){TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE};
	}
	return (Rectangle){0, 0, TILE_SIZE, TILE_SIZE};
}
