#pragma once
#include <iostream>
/*
struct Matrix{
	int** vals{};
	int** eater{};
	int** king{};
};
*/

class FieldPl {
private:
	//Matrix *Mat;
public:
	int vals[10][10];
	int eater[10][10];
	int king[10][10];
	int moves[10][10];
	int eat;
	int direction;
	FieldPl();
	//~FieldPl();
	void simpleMoveBlack();
	void simpleMoveWhite();
	void eatCheckerWhite();
	void eatCheckerBlack();
	void eatKing();
	void checkKing();
	void checkEatKing();
	bool checkEat(int c);
	void set_element();
	void print();
};


FieldPl::FieldPl() {

}

void FieldPl::set_element() {
	bool flag = true;
	int tmp = 1;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			eater[i][j] = 0;
			king[i][j] = 0;
			if ((i % 2 == 1) and (j % 2 == 1)) {
				vals[i][j] = 5;
			}
			else if ((i % 2 == 0) and (j % 2 == 0)) {
				vals[i][j] = 5;
			}
			else vals[i][j] = 0;
		}
	}
	int count;
	int tmp1;
	int tmp2;
	int k;/*
	while (true){
		std::cout << "Введите позицию по x\n";
		std::cin >> tmp1;
		std::cout << "Введите позицию по y\n";
		std::cin >> tmp2;
		std::cout << "Введите шашку\n";
		std::cin >> count;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				if ((tmp1-1 == i) and (tmp2-1 == j)){
					vals[j][i] = count;
				}
			}
		}
		std::cout << "0 - выход. 1 - продолжить ввод\n";
		std::cin >> k;
		if (k == 0) break;
		else continue;
	}*/

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			if ((((x % 2 == 1) and (y % 2 == 0)) or ((x % 2 == 0) and (y % 2 == 1)))) {
				vals[y][x] = 1;
			}
		}
	}
	for (int y = 6; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if ((((x % 2 == 1) and (y % 2 == 0)) or ((x % 2 == 0) and (y % 2 == 1)))) {
				vals[y][x] = 2;
			}
		}
	}

}

void FieldPl::print() {
	for (int i = 0; i < 10; i++) {
		for (int j = -2; j < 10; j++) {
			if (j > -1) {
				if ((((i + 1) % 2 != 0) and ((j + 1) % 2 != 0)) or (((i + 1) % 2 == 0) and ((j + 1) % 2 == 0))) {
					std::cout << "   ";
				}
				else std::cout << vals[i][j] << " ";
			}
			else if (j == -2) {
				std::cout << i;
			}
			else std::cout << "|";
		}
		std::cout << std::endl;
	}
	std::cout << "_____________________________\n";
	std::cout << "  0  1 2  3 4  5 6  7 8  9\n";
	std::cout << "_____________________________________\n";
}

void FieldPl::simpleMoveBlack() {
	int x, y, k;
	while (true) {
		while (true) {
			std::cout << "Выберите координаты черной шашки которой надо сходить\n";
			std::cout << "X: ";
			std::cin >> x;
			std::cout << "Y: ";
			std::cin >> y;
			std::cout << std::endl;
			if ((std::cin.fail()) or (x < 0) or (x > 9) or (y < 0) or (y > 9)) {
				std::cout << "Введите целове число от 0 до 9\n";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				continue;
			}
			break;
		}
		if ((vals[y][x] == 0) or (vals[y][x] == 5) or (vals[y][x] == 2)) { std::cout << "Шашек на этой клетке нет\n"; continue; }
		else {
			if ((vals[y + 1][x + 1] == 0) and ((x - 1 < 0) or (vals[y + 1][x - 1] == 2))) {
				vals[y][x] = 0;
				vals[y + 1][x + 1] = 1;
				break;
			}
			else if ((vals[y + 1][x + 1] == 0) and (vals[y + 1][x - 1] == 1)) {
				vals[y][x] = 0;
				vals[y + 1][x + 1] = 1;
				break;
			}
			else if ((vals[y + 1][x - 1] == 0) and ((x + 1 > 9) or (vals[y + 1][x + 1] == 2))) {
				vals[y][x] = 0;
				vals[y + 1][x - 1] = 1;
				break;
			}
			else if ((vals[y + 1][x - 1] == 0) and (vals[y + 1][x + 1] == 1)) {
				vals[y][x] = 0;
				vals[y + 1][x - 1] = 1;
				break;
			}
			else if ((vals[y + 1][x - 1] == 0) and (vals[y + 1][x + 1] == 0)) {
				while (true) {
					std::cout << "0 - left, 1 - right\n";
					std::cin >> k;
					if ((std::cin.fail())) {
						std::cout << "Введите число\n";
						std::cin.clear();
						std::cin.ignore(32767, '\n');
						continue;
					}
					break;
				}
				if (k == 0) {
					vals[y][x] = 0;
					vals[y + 1][x - 1] = 1;
					break;
				}
				else if (k == 1) {
					vals[y][x] = 0;
					vals[y + 1][x + 1] = 1;
					break;
				}
				else std::cout << "Нет такой кнопки\n";
			}
			else { std::cout << "нет ходов\n"; continue; }

		}

	}
	//print();

};

void FieldPl::simpleMoveWhite() {
	int x, y, k;
	while (true) {
		while (true) {
			std::cout << "Выберите координаты белой шашки которой надо сходить\n";
			std::cout << "X: ";
			std::cin >> x;
			std::cout << "Y: ";
			std::cin >> y;
			std::cout << std::endl;
			if ((std::cin.fail()) or (x < 0) or (x > 9) or (y < 0) or (y > 9)) {
				std::cout << "Введите целове число от 0 до 9\n";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				continue;
			}
			break;
		}
		if ((vals[y][x] == 0) or (vals[y][x] == 5) or (vals[y][x] == 1)) { std::cout << "Шашек на этой клетке нет\n"; continue; }
		if (vals[y][x] == 2) {
			if ((vals[y - 1][x + 1] == 0) and ((x - 1 < 0) or (vals[y - 1][x - 1] == 1))) {
				vals[y][x] = 0;
				vals[y - 1][x + 1] = 2;
				break;
			}
			else if ((vals[y - 1][x + 1] == 0) and (vals[y - 1][x - 1] == 2)) {
				vals[y][x] = 0;
				vals[y - 1][x + 1] = 2;
				break;
			}
			else if ((vals[y - 1][x - 1] == 0) and ((x + 1 > 9) or (vals[y - 1][x + 1] == 1))) {
				vals[y][x] = 0;
				vals[y - 1][x - 1] = 2;
				break;
			}
			else if ((vals[y - 1][x - 1] == 0) and (vals[y - 1][x + 1] == 2)) {
				vals[y][x] = 0;
				vals[y - 1][x - 1] = 2;
				break;
			}
			else if ((vals[y - 1][x - 1] == 0) and (vals[y - 1][x + 1] == 0)) {
				while (true) {
					std::cout << "0 - left, 1 - right\n";
					std::cin >> k;
					if ((std::cin.fail())) {
						std::cout << "Введите число\n";
						std::cin.clear();
						std::cin.ignore(32767, '\n');
						continue;
					}
					break;
				}
				if (k == 0) {
					vals[y][x] = 0;
					vals[y - 1][x - 1] = 2;
					break;
				}
				else if (k == 1) {
					vals[y][x] = 0;
					vals[y - 1][x + 1] = 2;
					break;
				}
				else std::cout << "Нет такой кнопки\n";
			}

			else { std::cout << "нет ходов\n"; continue; }

		}
	}
	//print();
}

bool FieldPl::checkEat(int c) {
	eat = 0;
	int tmp = 0;
	direction = 0;
	if (c == 1) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				tmp = 0;
				if ((vals[y][x] != 0) and (vals[y][x] != 5) and (vals[y][x] != 2)) {
					if ((x + 2 < 10) and (y + 2 < 10)) {
						if ((vals[y + 2][x + 2] == 0) and (vals[y + 1][x + 1] == 2)) {
							eat++;
							tmp++;
							direction = 4;
						}
					}
					if ((x + 2 < 10) and (y - 2 > -1)) {
						if ((vals[y - 2][x + 2] == 0) and (vals[y - 1][x + 1] == 2)) {
							eat++;
							tmp++;
							direction = 2;

						}
					}
					if ((x - 2 > -1) and (y + 2 < 10)) {
						if ((vals[y + 2][x - 2] == 0) and (vals[y + 1][x - 1] == 2)) {
							eat++;
							tmp++;
							direction = 3;
						}
					}
					if ((x - 2 > -1) and (y - 2 > -1)) {
						if ((vals[y - 2][x - 2] == 0) and (vals[y - 1][x - 1] == 2)) {
							eat++;
							tmp++;
							direction = 1;
						}
					}
				}
				if (tmp != 0) { eater[y][x] = 1; }
			}
		}

		if (eat != 0) {
			return false;
		}
		else { return true; }
	}
	else {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				tmp = 0;
				if ((vals[y][x] != 0) and (vals[y][x] != 5) and (vals[y][x] != 1)) {
					if ((x + 2 < 10) and (y + 2 < 10)) {
						if ((vals[y + 2][x + 2] == 0) and (vals[y + 1][x + 1] == 1)) {
							eat++;
							tmp++;
							direction = 4;
						}
					}
					if ((x + 2 < 10) and (y - 2 > -1)) {
						if ((vals[y - 2][x + 2] == 0) and (vals[y - 1][x + 1] == 1)) {
							eat++;
							tmp++;
							direction = 2;

						}
					}
					if ((x - 2 > -1) and (y + 2 < 10)) {
						if ((vals[y + 2][x - 2] == 0) and (vals[y + 1][x - 1] == 1)) {
							eat++;
							tmp++;
							direction = 3;
						}
					}
					if ((x - 2 > -1) and (y - 2 > -1)) {
						if ((vals[y - 2][x - 2] == 0) and (vals[y - 1][x - 1] == 1)) {
							eat++;
							tmp++;
							direction = 1;
						}
					}
				}
				if (tmp != 0) { eater[y][x] = 1; }
			}
		}
		//std::cout << "EAT: " << eat << std::endl;
		if (eat != 0) {
			return false;
		}
		else { return true; }
	}
}

void FieldPl::eatCheckerWhite() {
	int xOneCheck{}, yOneCheck{};
	if (eat == 1) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				if (eater[y][x] == 1) {
					switch (direction) {
					case 1:
						std::cout << "MOVE1\n";
						vals[y][x] = 0;
						vals[y - 1][x - 1] = 0;
						vals[y - 2][x - 2] = 2;
						xOneCheck = x - 2;
						yOneCheck = y - 2;
						break;
					case 2:
						std::cout << "MOVE2\n";
						vals[y][x] = 0;
						vals[y - 1][x + 1] = 0;
						vals[y - 2][x + 2] = 2;
						xOneCheck = x + 2;
						yOneCheck = y - 2;
						break;
					case 3:
						std::cout << "MOVE3\n";
						vals[y][x] = 0;
						vals[y + 1][x - 1] = 0;
						vals[y + 2][x - 2] = 2;
						xOneCheck = x - 2;
						yOneCheck = y + 2;
						break;
					case 4:
						std::cout << "MOVE4\n";
						vals[y][x] = 0;
						vals[y + 1][x + 1] = 0;
						vals[y + 2][x + 2] = 2;
						xOneCheck = x + 2;
						yOneCheck = y + 2;
						break;
					}
				}
			}
		}
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				eater[y][x] = 0;
			}
		}
		//print();
		bool flag = false;
		flag = checkEat(2);
		if ((!flag) and (eater[yOneCheck][xOneCheck] == 1)) {
			eatCheckerWhite();
		}
	}
	else {
		int xUser, yUser, direc;
		while (true) {
			while (true) {
				std::cout << "Введите какой шашкой съесть\n";
				std::cout << "X: ";
				std::cin >> xUser;
				std::cout << "Y: ";
				std::cin >> yUser;
				std::cout << std::endl;
				if ((std::cin.fail()) or (xUser < 0) or (xUser > 9) or (yUser < 0) or (yUser > 9)) {
					std::cout << "Введите целове число от 0 до 9\n";
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					continue;
				}
				break;
			}
			if (eater[yUser][xUser] == 0) { std::cout << "Эта шашка не может съесть\n"; continue; }
			else {
				while (true) {
					while (true) {
						std::cout << "1 - upleft, 2 - upright, 3 - downleft, 4 - downright\n";
						std::cin >> direc;
						if ((std::cin.fail())) {
							std::cout << "Введите целое число\n";
							std::cin.clear();
							std::cin.ignore(32767, '\n');
							continue;
						}
						break;
					}
					if (direc == 1) {
						if ((yUser - 2 > -1) and (xUser - 2 > -1)) {
							if ((vals[yUser - 2][xUser - 2] == 0) and (vals[yUser - 1][xUser - 1] == 1)) {
								vals[yUser][xUser] = 0;
								vals[yUser - 1][xUser - 1] = 0;
								vals[yUser - 2][xUser - 2] = 2;
								xOneCheck = xUser - 2;
								yOneCheck = yUser - 2;
								break;
							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else if (direc == 2) {
						if ((yUser - 2 > -1) and (xUser + 2 < 10)) {
							if ((vals[yUser - 2][xUser + 2] == 0) and (vals[yUser - 1][xUser + 1] == 1)) {
								vals[yUser][xUser] = 0;
								vals[yUser - 1][xUser + 1] = 0;
								vals[yUser - 2][xUser + 2] = 2;
								xOneCheck = xUser + 2;
								yOneCheck = yUser - 2;
								break;

							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else if (direc == 3) {
						if ((yUser + 2 < 10) and (xUser - 2 > -1)) {
							if ((vals[yUser + 2][xUser - 2] == 0) and (vals[yUser + 1][xUser - 1] == 1)) {
								vals[yUser][xUser] = 0;
								vals[yUser + 1][xUser - 1] = 0;
								vals[yUser + 2][xUser - 2] = 2;
								xOneCheck = xUser - 2;
								yOneCheck = yUser + 2;
								break;
							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else if (direc == 4) {
						if ((yUser + 2 < 10) and (xUser + 2 < 10)) {
							if ((vals[yUser + 2][xUser + 2] == 0) and (vals[yUser + 1][xUser + 1] == 1)) {
								vals[yUser][xUser] = 0;
								vals[yUser + 1][xUser + 1] = 0;
								vals[yUser + 2][xUser + 2] = 2;
								xOneCheck = xUser + 2;
								yOneCheck = yUser + 2;
								break;
							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else { std::cout << "нет такой кнопки\n"; continue; }
				}
			}
			//print();
			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {
					eater[y][x] = 0;
				}
			}
			bool flag = false;
			flag = checkEat(2);
			if ((!flag) and (eater[yOneCheck][xOneCheck] == 1)) {
				eatCheckerWhite();
			}
			break;
		}
	}
}

void FieldPl::eatCheckerBlack() {
	int xOneCheck{}, yOneCheck{};
	if (eat == 1) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				//std::cout << x << " " << y << " " << eater[y][x] << "\n";
				if (eater[y][x] == 1) {
					//std::cout << "DIRECT: " << direction << std::endl;
					//std::cout << "CHECKER: " << "black" << std::endl;
					switch (direction) {
					case 1:
						std::cout << "MOVE1\n";
						vals[y][x] = 0;
						vals[y - 1][x - 1] = 0;
						vals[y - 2][x - 2] = 1;
						xOneCheck = x - 2;
						yOneCheck = y - 2;
						break;
					case 2:
						std::cout << "MOVE2\n";
						vals[y][x] = 0;
						vals[y - 1][x + 1] = 0;
						vals[y - 2][x + 2] = 1;
						xOneCheck = x + 2;
						yOneCheck = y - 2;
						break;
					case 3:
						std::cout << "MOVE3\n";
						vals[y][x] = 0;
						vals[y + 1][x - 1] = 0;
						vals[y + 2][x - 2] = 1;
						xOneCheck = x - 2;
						yOneCheck = y + 2;
						break;
					case 4:
						std::cout << "MOVE4\n";
						vals[y][x] = 0;
						vals[y + 1][x + 1] = 0;
						vals[y + 2][x + 2] = 1;
						xOneCheck = x + 2;
						yOneCheck = y + 2;
						break;
					}
				}
			}
		}
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				eater[y][x] = 0;
			}
		}
		//print();
		bool flag = false;
		flag = checkEat(1);
		if ((!flag) and (eater[yOneCheck][xOneCheck] == 1)) {
			eatCheckerBlack();
		}
	}
	else {
		int xUser, yUser, direc;
		while (true) {
			while (true) {
				std::cout << "Введите какой шашкой съесть\n";
				std::cout << "X: ";
				std::cin >> xUser;
				std::cout << "Y: ";
				std::cin >> yUser;
				std::cout << std::endl;
				if ((std::cin.fail()) or (xUser < 0) or (xUser > 9) or (yUser < 0) or (yUser > 9)) {
					std::cout << "Введите целове число от 0 до 9\n";
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					continue;
				}
				break;
			}
			if (eater[yUser][xUser] == 0) { std::cout << "Эта шашка не может съесть\n"; continue; }
			else {
				while (true) {
					while (true) {
						std::cout << "1 - upleft, 2 - upright, 3 - downleft, 4 - downright\n";
						std::cin >> direc;
						if ((std::cin.fail())) {
							std::cout << "Введите целое число\n";
							std::cin.clear();
							std::cin.ignore(32767, '\n');
							continue;
						}
						break;
					}
					if (direc == 1) {
						if ((yUser - 2 > -1) and (xUser - 2 > -1)) {
							if ((vals[yUser - 2][xUser - 2] == 0) and (vals[yUser - 1][xUser - 1] == 2)) {
								vals[yUser][xUser] = 0;
								vals[yUser - 1][xUser - 1] = 0;
								vals[yUser - 2][xUser - 2] = 1;
								xOneCheck = xUser - 2;
								yOneCheck = yUser - 2;
								break;
							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else if (direc == 2) {
						if ((yUser - 2 > -1) and (xUser + 2 < 10)) {
							if ((vals[yUser - 2][xUser + 2] == 0) and (vals[yUser - 1][xUser + 1] == 2)) {
								vals[yUser][xUser] = 0;
								vals[yUser - 1][xUser + 1] = 0;
								vals[yUser - 2][xUser + 2] = 1;
								xOneCheck = xUser + 2;
								yOneCheck = yUser - 2;
								break;

							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else if (direc == 3) {
						if ((yUser + 2 < 10) and (xUser - 2 > -1)) {
							if ((vals[yUser + 2][xUser - 2] == 0) and (vals[yUser + 1][xUser - 1] == 2)) {
								vals[yUser][xUser] = 0;
								vals[yUser + 1][xUser - 1] = 0;
								vals[yUser + 2][xUser - 2] = 1;
								xOneCheck = xUser - 2;
								yOneCheck = yUser + 2;
								break;
							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else if (direc == 4) {
						if ((yUser + 2 < 10) and (xUser + 2 < 10)) {
							if ((vals[yUser + 2][xUser + 2] == 0) and (vals[yUser + 1][xUser + 1] == 2)) {
								vals[yUser][xUser] = 0;
								vals[yUser + 1][xUser + 1] = 0;
								vals[yUser + 2][xUser + 2] = 1;
								xOneCheck = xUser + 2;
								yOneCheck = yUser + 2;
								break;
							}
							else { std::cout << "так незя\n"; continue; }
						}
						else { std::cout << "так незя\n"; continue; }
					}
					else { std::cout << "нет такой кнопки\n"; continue; }
				}
			}
			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {
					eater[y][x] = 0;
				}
			}
			//print();
			bool flag = false;
			flag = checkEat(1);
			if ((!flag) and (eater[yOneCheck][xOneCheck] == 1)) {
				eatCheckerBlack();
			}
			break;
		}
	}

}

void FieldPl::checkKing() {
	for (int x = 0; x < 10; x++) {
		if (vals[0][x] == 2) {
			king[0][x] == 2;
		}
	}
	for (int x = 0; x < 10; x++) {
		if (vals[9][x] == 1) {
			king[9][x] == 1;
		}
	}
}


