/* figure: 	Kursach									   */
/*******************************************************/
/* Filename: GAME.cpp                         		   */
/* Abstract: This is a sample c++ -program         	   */
/* Description:                                 	   */
/* Create date: 2022 / 12 / 18                		   */
/* Author: Alekseev Maxim                              */
/* Notes/Platform/Copyright: NGTU/OS Windows(Ubuntu)   */
/*******************************************************/

#include <windows.h>
#include <iostream>
#include <iomanip>
#include "of.h"
//#include "GamePl.h"
#include "GamePlvsPl.h"


#define clear_screen()      std::cout << "\x1B[0;0f" << "\x1B[2J" << "\x1B[3J";


int main() {
	FieldPl test;
	test.set_element();
	bool flag;
	int k;
	int MIN;
	std::cout << "Выберите режим работы: \n";
	std::cout << "1 - игрок против компьютера, 2 - игрок против игрока\n";
	std::cin >> k;

	clear_screen();

	if (k == 1) {

		Field f1;
		NTree tree;
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				f1.vals[y][x] = test.vals[y][x];
			}
		}
		tree.addElement(f1, true);
		while (true) {
			test.print();
			MIN = -1000;
			flag = test.checkEat(2);
			if (flag) {
				test.simpleMoveWhite();
				clear_screen();
				test.print();
				Sleep(3);
			}
			else {
				test.eatCheckerWhite();
				clear_screen();
				test.print();
				Sleep(3);
			}
			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {
					f1.vals[y][x] = test.vals[y][x];
				}
			}
			countReal = 0;
			tree.TU(f1, false, 1);
			tree.MM();
			tree.stateSel();
			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {
					test.vals[y][x] = tree.root->value.vals[y][x];
				}
			}
			clear_screen();
			test.print();
			std::cout << "0 - выход, 1 - продолжить\n";
			std::cin >> k;
			Sleep(2);
			clear_screen();
			flag = false;
			if (k == 0) break;
			else continue;
		}
	}
	else if (k == 2) {
		while (true) {
			test.print();
			flag = test.checkEat(2);
			if (flag) {
				test.simpleMoveWhite();
				clear_screen();
				test.print();
			}
			else {
				test.eatCheckerWhite();
				clear_screen();
				test.print();
			}
			Sleep(2);
			flag = test.checkEat(1);
			//test.print();
			if (flag) {
				test.simpleMoveBlack();
				clear_screen();
				test.print();
			}
			else {
				test.eatCheckerBlack();
				clear_screen();
				test.print();
			}
			std::cout << "0 - выход, 1 - продолжить\n";
			std::cin >> k;
			Sleep(2);
			clear_screen();
			flag = false;
			if (k == 0) break;
			else continue;
		}
	}
	else {
		std::cout << "Нет такого кода\n";
	}

	return 0;



}