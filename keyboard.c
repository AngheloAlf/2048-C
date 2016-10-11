#include "keyboard.h"

int getKeyboardPress(){
	int input = getch(); //Get keyboard press

	if(input == 224){ //Arrows keys
		int input2 = getch(); // In the case of the arrows keys, a second getch is needed
		if(input2 == 72){ // UP
			return 1;
		}
		else if(input2 == 75){ // LEFT
			return 2;
		}
		else if(input2 == 80){ // DOWN
			return 3;
		}
		else if(input2 == 77){ // RIGHT
			return 4;
		}
	}

	else if(input == 13){ //Enter
		return 5;
	}
	else if(input == 32){ //Space
		return 6;
	}
	else if(input == 27){ //Esc
		return 7;
	}

	return 0;
}
void testGetKeyboardPress(){
	int test;
	do{
		test = getKeyboardPress();
		if(test != 0){
			printf("You pressed %d\n", test);
		}
	}while(test != 7);

	printf("Exiting...\n");
}
