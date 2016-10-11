all: mainSimpleArray mainBiArray

mainBiArray: mainBiArray.o keyboard.o mathFunctions.o
	gcc mainBiArray.o keyboard.o mathFunctions.o -o 2048Bi -Wall

mainBiArray.o: mainBiArray.c keyboard.h mathFunctions.h
	gcc mainBiArray.c -c -Wall



mainSimpleArray: mainSimpleArray.o keyboard.o mathFunctions.o
	gcc mainSimpleArray.o keyboard.o mathFunctions.o -o 2048Simple -Wall

mainSimpleArray.o: mainSimpleArray.c keyboard.h mathFunctions.h
	gcc mainSimpleArray.c -c -Wall



keyboard.o: keyboard.c
	gcc keyboard.c -c -Wall

mathFunctions.o: mathFunctions.c
	gcc mathFunctions.c -c -Wall

clean:
	rm mainSimpleArray.o keyboard.o mathFunctions.o
