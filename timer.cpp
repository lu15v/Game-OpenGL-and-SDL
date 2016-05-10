#include <iostream>
#include <Windows.h>
#include "functions.h"

int timeLaps(int laps){
	int seconds = 0;
	int milliseconds = 0;

		while(seconds != laps){
		if(milliseconds == 10){
			++seconds;
			milliseconds = 0;
		}
		std::cout << seconds << ":" << milliseconds;
		++milliseconds;
		Sleep(100);
	}

	return seconds;
}
