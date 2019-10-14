#include "pch.h"
#include "Header.h"
#include <windows.h>

int main()
{
	//ховаємо вікно консолі
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);

	int score = 0;
	//створення вікна гри
	RenderWindow window(VideoMode(WW, WH), "SpaceOOP2019");
	//меню
	menu(window);
	if (!isClose)	//перевірка чи не треба закривати вікно
	{
		//гра
		score = game(window);
		//заставка
		caption(window, score);
		//закриваємо вікно
	}
	window.close();
	return 0;
}