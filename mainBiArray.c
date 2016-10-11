#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "keyboard.h"
#include "mathFunctions.h"

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4


//Create a biArray[size][size] array with 0
unsigned **initZerosBiArray(unsigned size){
	unsigned **biArray = (unsigned **) malloc(sizeof(unsigned *) * size);
	for(unsigned i = 0; i < size; i++){
		biArray[i] = (unsigned *) malloc(sizeof(unsigned *) * size);
		for(unsigned j = 0; j < size; j++){
			biArray[i][j] = 0;
		}
	}
	return biArray;
}


//Free all the allocated memory for the **biArray
unsigned **freeBiArray(unsigned **biArray, unsigned size){
	for(unsigned i = 0; i < size; i++){
		free(biArray[i]);
	}
	free(biArray);
	return biArray;
}

/* Print maps on screen
   Returns 0 if ok
   Errors:
*/
int printBiMap(unsigned **map, unsigned size){
	for(unsigned i = 0; i < size; i++){
		printf("\n|");
		for(unsigned j = 0; j < size; j++){
			printf("\t%u |", map[i][j]);
		}
	}
	printf("\n");
	return 0;
}

/* Returns 0 if number added, 1 if there's no space to add a number */
int addNumberToBiMap(unsigned **map, unsigned size){
	unsigned posX, posY;
	unsigned number = getARandomNumber(size);

	//Will have an 1 if the pos have a number or not
	unsigned **reviewedPos;
	reviewedPos = initZerosBiArray(size);

	while(1){
		posX = getRandomPos(size);
		posY = getRandomPos(size);
		if(map[posX][posY] == 0){
			map[posX][posY] = number;
			break;
		}
		else{
			reviewedPos[posX][posY] = 1;
			if(sumBiArray(reviewedPos, size) == size*size){
				return 1;
			}
		}
	}
	free(reviewedPos);
	return 0;
}

/* Move (UP, LEFT, DOWN or RIGHT) and sum a number next to it to the pos i0, j0 */
void sumToThePos(unsigned **map, unsigned i0, unsigned j0, int direction){
	int dirX = 0;
	int dirY = 0;

	if(direction == UP){
		dirX = -1;
	}
	else if(direction == LEFT){
		dirY = -1;
	}
	else if(direction == DOWN){
		dirX = 1;
	}
	else if(direction == RIGHT){
		dirY = 1;
	}
	else{
		return;
	}

	map[i0 + dirX][j0 + dirY] += map[i0][j0];
	map[i0][j0] = 0;
}

/* Iterate only the row or column of the array searching for all of the zeros in the row/column and returns the last position where a zero
was founded */
int getZeroPos(unsigned **map, unsigned size, unsigned i, unsigned j, int direction){
	int zeroPos = 0, aux = 0;

	if(direction == UP || direction == LEFT){
		aux = - 1;
	}
	else if(direction == DOWN || direction == RIGHT){
		aux = 1;
	}

	if(direction == UP || direction == DOWN){
		zeroPos = i + aux;
	}
	else if(direction == LEFT || direction == RIGHT){
		zeroPos = j + aux;
	}

	while((zeroPos + aux >= 0) && (zeroPos + aux < size)){
		if(direction == UP || direction == DOWN){
			if((map[zeroPos +aux][j] == 0)){
				zeroPos += aux;
			}
			else{
				break;
			}
		}
		else if(direction == LEFT || direction == RIGHT){
			if(map[i][zeroPos + aux] == 0){
				zeroPos += aux;
			}
			else{
				break;
			}
		}
	}
	
	return zeroPos;
}

/* Move everything to the selected direction direction */

int moveBiMapDir(unsigned **map, unsigned size, int direction){
	//Init variables
	int zeroPos; // Aux to know how many spaces move the number
	unsigned numbersMoved = 0; // How many numbers has been moved
	unsigned **movedNumbersArray = initZerosBiArray(size); //An array containing if a number has moved to that pos

	int iterI = 0, iterJ = 0;

	if(direction == UP){
		iterI = 1;
		iterJ = 1;
	}
	else if(direction == LEFT){
		iterI = 1;
		iterJ = 1;
	}
	else if(direction == DOWN){
		iterI = -1;
		iterJ = 1;
	}
	else if(direction == RIGHT){
		iterI = 1;
		iterJ = -1;
	}


	for(unsigned i = 1; i < size; i++){
		for(unsigned j = 0; j < size; j++){
			if(map[i][j] != 0){
				if((map[i - 1][j] == map[i][j])){
					sumToThePos(map, i, j, UP);

					numbersMoved += 1;
					movedNumbersArray[i - 1][j] = 1;
				}
				else if(map[i - 1][j] == 0){
					zeroPos = getZeroPos(map, size, i, j, UP);
	
					map[zeroPos][j] = map[i][j];
					map[i][j] = 0;
	
					if((zeroPos - 1 >= 0) && (zeroPos - 1 < size) && (map[zeroPos - 1][j] == map[zeroPos][j])){
						if((zeroPos - 2 >= 0 && movedNumbersArray[zeroPos - 2][j] == 1) || (movedNumbersArray[zeroPos - 1][j] == 0)){
							sumToThePos(map, zeroPos, j, UP);
						}
					}

					numbersMoved += 1;
					movedNumbersArray[zeroPos][j] = 1;
				}
			}
		}
	}

	freeBiArray(movedNumbersArray, size);

	return numbersMoved;
}

int moveBiMapUP(unsigned **map, unsigned size){
	//Init variables
	int zeroPos; // Aux to know how many spaces move the number
	unsigned numbersMoved = 0; // How many numbers has been moved
	unsigned **movedNumbersArray = initZerosBiArray(size); //An array containing if a number has moved to that pos

	for(unsigned i = 1; i < size; i++){
		for(unsigned j = 0; j < size; j++){
			if(map[i][j] != 0){
				if((map[i - 1][j] == map[i][j])){
					sumToThePos(map, i, j, UP);

					numbersMoved += 1;
					movedNumbersArray[i - 1][j] = 1;
				}
				else if(map[i - 1][j] == 0){
					zeroPos = getZeroPos(map, size, i, j, UP);
	
					map[zeroPos][j] = map[i][j];
					map[i][j] = 0;
	
					if((zeroPos - 1 >= 0) && (zeroPos - 1 < size) && (map[zeroPos - 1][j] == map[zeroPos][j])){
						if((zeroPos - 2 >= 0 && movedNumbersArray[zeroPos - 2][j] == 1) || (movedNumbersArray[zeroPos - 1][j] == 0)){
							sumToThePos(map, zeroPos, j, UP);
						}
					}

					numbersMoved += 1;
					movedNumbersArray[zeroPos][j] = 1;
				}
			}
		}
	}

	freeBiArray(movedNumbersArray, size);

	return numbersMoved;
}

int moveBiMapLEFT(unsigned **map, unsigned size){
	int zeroPos;
	unsigned numbersMoved = 0;

	for(unsigned i = 0; i < size; i++){
		for(unsigned j = 1; j < size; j++){
			if(map[i][j] != 0){
				if(map[i][j - 1] == map[i][j]){
					sumToThePos(map, i, j, LEFT);
					numbersMoved += 1;
				}
				else if(map[i][j - 1] == 0){
					zeroPos = getZeroPos(map, size, i, j, LEFT);

					map[i][zeroPos] = map[i][j];
					map[i][j] = 0;

					if((zeroPos - 1 >= 0) && (zeroPos - 1 < size)){				
						if(map[i][zeroPos - 1] == map[i][zeroPos]){
							sumToThePos(map, i, zeroPos, LEFT);
						}
					}

					numbersMoved += 1;
				}
			}
		}
	}

	return numbersMoved;
}

int moveBiMapDOWN(unsigned **map, unsigned size){
	int zeroPos;
	unsigned numbersMoved = 0;

	for(unsigned i = size - 2; i < size; i--){
		for(unsigned j = 0; j < size; j++){
			if(map[i][j] != 0){
				if(map[i + 1][j] == map[i][j]){
					sumToThePos(map, i, j, DOWN);
					numbersMoved += 1;
				}
				else if(map[i + 1][j] == 0){
					zeroPos = getZeroPos(map, size, i, j, DOWN);

					map[zeroPos][j] = map[i][j];
					map[i][j] = 0;

					if((zeroPos + 1 >= 0) && (zeroPos + 1 < size)){				
						if(map[zeroPos + 1][j] == map[zeroPos][j]){
							sumToThePos(map, zeroPos, j, DOWN);
						}
					}

					numbersMoved += 1;

				}
			}
		}
	}

	return numbersMoved;
}

int moveBiMapRIGHT(unsigned **map, unsigned size){
	int zeroPos;
	unsigned numbersMoved = 0;

	for(unsigned i = 0; i < size; i++){
		for(unsigned j = size - 2; j < size; j--){
			if(map[i][j] != 0){
				if(map[i][j + 1] == map[i][j]){
					sumToThePos(map, i, j, RIGHT);
					numbersMoved += 1;
				}
				else if(map[i][j + 1] == 0){
					zeroPos = getZeroPos(map, size, i, j, RIGHT);

					map[i][zeroPos] = map[i][j];
					map[i][j] = 0;

					if((zeroPos + 1 >= 0) && (zeroPos + 1 < size)){				
						if(map[i][zeroPos + 1] == map[i][zeroPos]){
							sumToThePos(map, i, zeroPos, RIGHT);
						}
					}
					
					numbersMoved += 1;
				}
			}
		}
	}
	return numbersMoved;
}


/*Returns 1 if gameOver, else 0 */
unsigned isGameOver(unsigned **map, unsigned size){
	return 0;
}

int main(){
	//Init variables
	unsigned size = 4;
	unsigned **map;
	int gameOn = 1;
	int pressedKey = 0;
	int dontAdd = 0;

	//Init random seed
	srand(time(NULL));

	//Init the map array
	map = initZerosBiArray(size);

/*
	map[0][0] = 8; map[0][1] = 8;// map[0][2] = 3; map[0][3] = 4;
	map[1][0] = 8; map[1][1] = 8;// map[1][2] = 7; map[1][3] = 8; 
	map[2][0] = 16; map[2][1] = 8;// map[2][2] = 7; map[2][3] = 6;
	map[3][0] = 32; map[3][1] = 8;// map[3][2] = 3; map[3][3] = 2;
*/

	//Prints the map
	printBiMap(map, size);

	while(gameOn){

		if(addNumberToBiMap(map, size)){
			gameOn = 0;
			break;
		}
		
		printBiMap(map, size);

		//User input
		pressedKey = 0;
		while(pressedKey == 0 || pressedKey >= 5){
			pressedKey = getKeyboardPress();

			if(pressedKey == 7){ //ESC
				gameOn = 0;
				break;
			}

			if(pressedKey == 1){ // UP
				dontAdd = moveBiMapUP(map, size);
			}
			else if(pressedKey == 2){ // LEFT
				dontAdd = moveBiMapLEFT(map, size);
			}
			else if(pressedKey == 3){ // DOWN
				dontAdd = moveBiMapDOWN(map, size);
			}
			else if(pressedKey == 4){ // RIGHT
				dontAdd = moveBiMapRIGHT(map, size);
			}

			if(dontAdd == 0){
				pressedKey = 0;
				continue;
			}
			else if(dontAdd == -1){
				break;
			}

		}

		if(isGameOver(map, size)){
			gameOn = 0;
			break;
		}
	}

	printf("\n\n --- Game Over --- \n\n");

	freeBiArray(map, size);

	return 0;
}
