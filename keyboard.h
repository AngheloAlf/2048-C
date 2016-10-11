#ifndef KEYBOARD_H
	#define KEYBOARD_H

	#include <stdio.h>


	/* Gets the keyboard event press and returns a number: 

		1 - UP
		2 - LEFT
		3 - DOWN
		4 - RIGHT

		5 - Enter
		6 - Space
		7 - Esc


	TODO: review if works on linux (tested on windows)
	*/
	int getKeyboardPress();

	//To test the getKeyboardPress()
	void testGetKeyboardPress();

#endif
