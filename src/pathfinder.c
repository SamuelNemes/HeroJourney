#include "pathfinder.h"
#include "constants.h"
#include "common.h"
#include "tile.h"
#include <stdlib.h>
#include <stdio.h>

void FindPath(Tile tiles[ROOM_ROWS][ROOM_COLS], TilePos start, TilePos goal, TilePos* path, int* pathLength){
	int state[ROOM_ROWS][ROOM_COLS] = {0}; //0 unmapped, 1 open, 2 closed//
	int gVals[ROOM_ROWS][ROOM_COLS] = {0};
	*pathLength = 0;

	for(int row = 0; row < ROOM_ROWS; row++){
		for(int col = 0; col < ROOM_COLS; col++){
			gVals[row][col] = 999;
		}
	}
	TilePos parents[ROOM_ROWS][ROOM_COLS] = {0};

	TilePos current = start;
	state[start.y][start.x] = 1;
	gVals[start.y][start.x] = 0;

	while(current.x != goal.x || current.y != goal.y){
		state[current.y][current.x] = 2;
		//calculate neighbor gvals

		//NORTH NEIGHBOR
		if(current.y - 1 >= 0){
			if(!tiles[current.y-1][current.x].isSolid){
				int gVal = gVals[current.y][current.x] + 1;
				switch(state[current.y-1][current.x]){
					case 0:
						state[current.y-1][current.x] = 1;
						gVals[current.y-1][current.x] = gVal;
						parents[current.y-1][current.x] = current;
						break;
					case 1:
						if(gVal < gVals[current.y-1][current.x]){
							gVals[current.y-1][current.x] = gVal;
							parents[current.y-1][current.x] = current;
						}
				}
			}
		}

		//EAST NEIGHBOR
		if(current.x+1 < ROOM_COLS){
			if(!tiles[current.y][current.x+1].isSolid){
				int gVal = gVals[current.y][current.x] + 1;
				switch(state[current.y][current.x+1]){
					case 0:
						state[current.y][current.x+1] = 1;
						gVals[current.y][current.x+1] = gVal;
						parents[current.y][current.x+1] = current;
						break;
					case 1:
						if(gVal < gVals[current.y][current.x+1]){
							gVals[current.y][current.x+1] = gVal;
							parents[current.y][current.x+1] = current;
						}
				}
			}
		}

		//SOUTH NEIGHBOR
		if(current.y+1 < ROOM_ROWS){
			if(!tiles[current.y+1][current.x].isSolid){
				int gVal = gVals[current.y][current.x] + 1;
				switch(state[current.y+1][current.x]){
					case 0:
						state[current.y+1][current.x] = 1;
						gVals[current.y+1][current.x] = gVal;
						parents[current.y+1][current.x] = current;
						break;
					case 1:
						if(gVal < gVals[current.y+1][current.x]){
							gVals[current.y+1][current.x] = gVal;
							parents[current.y+1][current.x] = current;
						}
				}

			}
		}

		//WEST NEIGHBOR
		if(current.x-1 >= 0){
			if(!tiles[current.y][current.x-1].isSolid){
				int gVal = gVals[current.y][current.x] + 1;
				switch(state[current.y][current.x-1]){
					case 0:
						state[current.y][current.x-1] = 1;
						gVals[current.y][current.x-1] = gVal;
						parents[current.y][current.x-1] = current;
						break;
					case 1:
						if(gVal < gVals[current.y][current.x-1]){
							gVals[current.y][current.x-1] = gVal;
							parents[current.y][current.x-1] = current;
						}
				}

			}
		}
		int min = 99999;
		for(int row = 0; row < ROOM_ROWS; row++){
			for(int col = 0; col < ROOM_COLS; col++){
				if(state[row][col] != 1){continue;}
				if((gVals[row][col] + abs(goal.x - col) + abs(goal.y - row)) < min){
					min = (gVals[row][col] + abs(goal.x - col) + abs(goal.y - row));
					current.x = col;
					current.y = row;
				}
			}
		}	
		if(min == 99999){
			printf("====FAILED====\n");
			return;
		}
	}
	TilePos tempPath[ROOM_ROWS * ROOM_COLS] = {0};
	while(current.x != start.x || current.y != start.y){
		tempPath[*pathLength] = current;
		current = parents[current.y][current.x];
		(*pathLength)++;
	}

	for(int i=0; i < *pathLength; i++){
		path[i] = tempPath[*pathLength - 1 - i];
	}
}
