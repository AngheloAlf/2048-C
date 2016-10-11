#ifndef MATHFUNCTIONS_H
	#define MATHFUNCTIONS_H
	
	#include <stdio.h>
	#include <math.h>

	/* Returns 0 if number has perfect sqrt (4, 9, 16, 25, etc), else 1 */
	int isNotPerfectSqrt(float number);
	void testIsNotPerfectSqrt();

	/* Returns a number between 0 and limit-1 */
	unsigned getRandomPos(unsigned limit);

	/* Returns 2 or 4 randomly */
	unsigned getARandomNumber(unsigned limit);

	//Return the sum of all elements of the array
	unsigned sumArray(unsigned *array, unsigned size);

	//Return the sum of all elements of a biArray
	unsigned sumBiArray(unsigned **biArray, unsigned size);

#endif
