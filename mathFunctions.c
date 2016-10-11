#include "mathFunctions.h"

/* Returns 0 if number has perfect sqrt (4, 9, 16, 25, etc), else 1 */
int isNotPerfectSqrt(float number){
	float a = sqrt(number);
	unsigned b = a;
	return a != b;
}
void testIsNotPerfectSqrt(){
	printf("%d\n", isNotPerfectSqrt(26));
	printf("%d\n", isNotPerfectSqrt(25));
}

/* Returns a number between 0 and limit-1 */
unsigned getRandomPos(unsigned limit){
	return rand() % limit;
}

/* Returns 2 or 4 randomly */
unsigned getARandomNumber(unsigned limit){
	if(getRandomPos(limit) > limit/2){
		return 4;
	}
	return 2;
}

//Return the sum of all elements of the array
unsigned sumArray(unsigned *array, unsigned size){
	unsigned sum = 0;
	for(unsigned i = 0; i < size; i++){
		sum += array[i];
	}
	return sum;
}

//Return the sum of all elements of a biArray
unsigned sumBiArray(unsigned **biArray, unsigned size){
	unsigned sum = 0;
	for(unsigned i = 0; i < size; i++){
		for(unsigned j = 0; j < size; j++){
			sum += biArray[i][j];
		}
	}
	return sum;
}
