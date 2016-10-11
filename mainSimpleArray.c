#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "keyboard.h"
#include "mathFunctions.h"


/* Print maps on screen
   Returns 0 if ok
   Errors:
       1 - Wrong size (must have sqrt)
*/
int printMap(unsigned *map, unsigned size){
	if(isNotPerfectSqrt(size)){
		return 1;
	}
	//printf("%s\n", );

	unsigned root = sqrt(size);

	for(unsigned i = 0; i < size; i++){
		if(i % root == 0){
			printf("\n|");

		}
		printf("\t%u |", map[i]);
	}
	printf("\n");
	return 0;
}

//Fill all the array only with 0
void initZerosArray(unsigned *map, unsigned size){
	for(unsigned i = 0; i < size; i++){
		map[i] = 0;
	}
}

/* Returns 0 if number added, 1 if there's no space to add a number */
int addNumberToMap(unsigned *map, unsigned size){
	unsigned pos;
	unsigned number = getARandomNumber(size);

	//Will have an 1 if the pos have a number or not
	unsigned reviewedPos[size];
	initZerosArray(reviewedPos, size);

	while(1){
		pos = getRandomPos(size);
		if(!map[pos]){
			map[pos] = number;
			break;
		}
		else{
			reviewedPos[pos] = 1;
			if(sumArray(reviewedPos, size) == size){
				return 1;
			}
		}
	}
	return 0;
}

// TODO: If nothings is moved, not add a number
/* Move everything up */
unsigned moveMapUP(unsigned *map, unsigned size){
	unsigned root = sqrt(size);
	int zeroPos;

	//Iterate rows and then columns from up to down
	for(unsigned i = root; i < size && i >= 0; i++){ //iterate the map from the second row
		if(map[i] == map[i - root]){ //The number and the number up this are the same
			map[i - root] *= 2;
			map[i] = 0;
		}
		else if(map[i - root] == 0){ //The number up this is 0
			zeroPos = i - root;
			while((zeroPos - root) >= 0 && (zeroPos - root < size)){ //View if all of the numbers over this are zero or not, and get the pos of the "more up" zero of the column
				if((zeroPos - root >= 0) && (zeroPos - root < size) && (map[zeroPos - root] == 0)){
					zeroPos -= root;
				}
				else{
					break;
				}
			}
			
			//Move the number to the "more up" zero in the column
			map[zeroPos] = map[i];
			map[i] = 0;

			if((zeroPos - root >= 0) && (map[zeroPos] == map[zeroPos - root])){ //If the number and the number up this are the same
				map[zeroPos - root] *= 2;
				map[zeroPos] = 0;
			}
		}
		
	}
	return 0;
}

unsigned moveMapLEFT(unsigned *map, unsigned size){
	unsigned root = sqrt(size);
	int zeroPos;

	//Iterate columns and then rows from left to right
	for(unsigned i = size/size; i < size && i >= 0 && i != root; i += root){
		if(map[i] == map[i - 1]){ //The number and the number left this are the same
			map[i - 1] *= 2;
			map[i] = 0;
		}
		else if(map[i - 1] == 0){ //The number left this is 0
			zeroPos = i - 1;
			while((zeroPos - 1) >= 0){ //View if all of the numbers left this are zero or not, and get the pos of the "more left" zero of the row
				if((zeroPos - 1 >= 0) && (map[zeroPos - 1] == 0) && (zeroPos % root != 0)){
					zeroPos -= 1;
				}
				else{
					break;
				}
			}
			
			//Move the number to the "more left" zero in the row
			map[zeroPos] = map[i];
			map[i] = 0;
			
			if((zeroPos - 1 >= 0)  && (map[zeroPos] == map[zeroPos - 1])){ //If the number and the number left this are the same
				map[zeroPos - 1] *= 2;
				map[zeroPos] = 0;
			}
		}
		
		//To get back to the first element of the next column
		if(i + root > size){
			i = i - (root * root) + 1;
		}

	}
	return 0;
}

unsigned moveMapDOWN(unsigned *map, unsigned size){
	unsigned root = sqrt(size);
	int zeroPos;

	//Iterate rows and then columns from up to down
	for(unsigned i = size - root; i >= 0 && i < size; i--){ //iterate the map penultimate row

		if(map[i] == map[i + root]){ //The number and the number down this are the same
			map[i + root] *= 2;
			map[i] = 0;
		}
		else if(map[i + root] == 0){ //The number down this is 0
			zeroPos = i + root;
			while((zeroPos + root) < size && (zeroPos + root < size)){ //View if all of the numbers down this are zero or not, and get the pos of the "more down" zero of the column
				if((zeroPos + root < size) && (zeroPos + root < size) && (map[zeroPos + root] == 0)){
					zeroPos += root;
				}
				else{
					break;
				}
			}
			
			//Move the number to the "more down" zero in the column
			map[zeroPos] = map[i];
			map[i] = 0;

			if((zeroPos + root < size) && (map[zeroPos] == map[zeroPos + root])){ //If the number and the number up this are the same
				map[zeroPos + root] *= 2;
				map[zeroPos] = 0;
			}
		}
		
	}
	return 0;
}

unsigned moveMapRIGHT(unsigned *map, unsigned size){
	unsigned root = sqrt(size);
	int zeroPos;

	//Iterate columns and then rows from right to left
	for(unsigned i = size - 2; i < size && i >= 0; i -= root){
		printf("%u\n", i);
		if(map[i] == map[i + 1]){ //The number and the number right this are the same
			map[i + 1] *= 2;
			map[i] = 0;
		}
		else if(map[i + 1] == 0){ //The number right this is 0
			zeroPos = i + 1;
			while((zeroPos + 1) < size){ //View if all of the numbers right this are zero or not, and get the pos of the "more right" zero of the row
				if((zeroPos + 1 < size) && (map[zeroPos + 1] == 0) && ((zeroPos + 1) % root != 0)){
					zeroPos += 1;
				}
				else{
					break;
				}
			}
			
			//Move the number to the "more right" zero in the row
			map[zeroPos] = map[i];
			map[i] = 0;
			
			if((zeroPos + 1 < size)  && (map[zeroPos] == map[zeroPos + 1])){ //If the number and the number right this are the same
				map[zeroPos + 1] *= 2;
				map[zeroPos] = 0;
			}

		}


		//To get back to the first element of the next column
		if(((i - root > size) && (i != 0)) || (i - root < 0)){
			i = i + (root * root) - 1;
			printf("\n");
		}

	}

	return 0;
}


/*Returns 1 if gameOver, else 0 */
unsigned isGameOver(unsigned *map, unsigned size){
	return 0;
}

int main(){
	//Init variables
	unsigned size = 16;
	unsigned map[size];
	int gameOn = 1;
	int pressedKey = 0;
	unsigned dontAdd = 0;

	//Init random seed
	srand(time(NULL));

	//Init the map array
	initZerosArray(map, size);

	//Prints the map
	printMap(map, size);

	while(gameOn){

		if(addNumberToMap(map, size)){
			gameOn = 0;
			break;
		}
		
		printMap(map, size);

		//User input
		pressedKey = 0;
		while(pressedKey == 0 || pressedKey >= 5){
			pressedKey = getKeyboardPress();

			if(pressedKey == 7){ //ESC
				gameOn = 0;
				break;
			}

			if(pressedKey == 1){ // UP
				dontAdd = moveMapUP(map, size);
			}
			else if(pressedKey == 2){ // LEFT
				dontAdd = moveMapLEFT(map, size);
			}
			else if(pressedKey == 3){ // DOWN
				dontAdd = moveMapDOWN(map, size);
			}
			else if(pressedKey == 4){ // RIGHT
				dontAdd = moveMapRIGHT(map, size);
			}

			if(dontAdd == 1){
				pressedKey = 0;
				continue;
			}

		}

		if(isGameOver(map, size)){
			gameOn = 0;
			break;
		}
	}

	printf("\n\n --- Game Over --- \n\n");

	return 0;
}
