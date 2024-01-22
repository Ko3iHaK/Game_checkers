#pragma once
#include <iostream>


class Field {
private:
	//Matrix *Mat;
public:
	//Matrix *Mat;
	int vals[10][10];
	int eater[10][10];
	int king[10][10];
	int moves[10][10];
	int eat;
	int direction;
	Field();
	//~Field();
	void moveChecker(int c);
	bool simpleMoveBlack(int x, int y, int k);
	bool simpleMoveWhite(int x, int y, int k);
	void eatCheckerWhite(int x, int y, int dir);
	void eatCheckerBlack(int x, int y, int dir);
	void eatKing();
	void checkKing();
	void checkEatKing();
	bool checkEat(int c);
	void set_element();
	void print();
};



Field::Field() {
}

void Field::set_element() {
	bool flag = true;
	int tmp = 1;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			eater[i][j] = 0;
			king[i][j] = 0;
			moves[i][j] = 0;
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
	int k;

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

void Field::print() {
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

bool Field::simpleMoveBlack(int x, int y, int k) {
	if ((vals[y][x] == 0) or (vals[y][x] == 5) or (vals[y][x] == 2)) { return false; }
	else {
		if ((vals[y + 1][x + 1] == 0) and ((x - 1 < 0) or (vals[y + 1][x - 1] == 2))) {
			vals[y][x] = 0;
			vals[y + 1][x + 1] = 1;
			return true;
		}
		else if ((vals[y + 1][x + 1] == 0) and (vals[y + 1][x - 1] == 1)) {
			vals[y][x] = 0;
			vals[y + 1][x + 1] = 1;
			return true;
		}
		else if ((vals[y + 1][x - 1] == 0) and ((x + 1 > 9) or (vals[y + 1][x + 1] == 2))) {
			vals[y][x] = 0;
			vals[y + 1][x - 1] = 1;
			return true;
		}
		else if ((vals[y + 1][x - 1] == 0) and (vals[y + 1][x + 1] == 1)) {
			vals[y][x] = 0;
			vals[y + 1][x - 1] = 1;
			return true;
		}
		else if ((vals[y + 1][x - 1] == 0) and (vals[y + 1][x + 1] == 0)) {
			if (k == 0) {
				vals[y][x] = 0;
				vals[y + 1][x - 1] = 1;
				return true;
			}
			else if (k == 1) {
				vals[y][x] = 0;
				vals[y + 1][x + 1] = 1;
				return true;
			}
		}
		else { return false; }

	}
	return false;

}


bool Field::simpleMoveWhite(int x, int y, int k) {
	if ((vals[y][x] == 0) or (vals[y][x] == 5) or (vals[y][x] == 1)) { return false; }
	else {
		if ((vals[y - 1][x + 1] == 0) and ((x - 1 < 0) or (vals[y - 1][x - 1] == 1))) {
			vals[y][x] = 0;
			vals[y - 1][x + 1] = 2;
			return true;
		}
		else if ((vals[y - 1][x + 1] == 0) and (vals[y - 1][x - 1] == 2)) {
			vals[y][x] = 0;
			vals[y - 1][x + 1] = 2;
			return true;
		}
		else if ((vals[y - 1][x - 1] == 0) and ((x + 1 > 9) or (vals[y - 1][x + 1] == 1))) {
			vals[y][x] = 0;
			vals[y - 1][x - 1] = 2;
			return true;
		}
		else if ((vals[y - 1][x - 1] == 0) and (vals[y - 1][x + 1] == 2)) {
			vals[y][x] = 0;
			vals[y - 1][x - 1] = 2;
			return true;
		}
		else if ((vals[y - 1][x - 1] == 0) and (vals[y - 1][x + 1] == 0)) {
			if (k == 0) {
				vals[y][x] = 0;
				vals[y - 1][x - 1] = 2;
				return true;
			}
			else if (k == 1) {
				vals[y][x] = 0;
				vals[y - 1][x + 1] = 2;
				return true;
			}
		}
		else { return false; }

	}
	return false;
	//print();
}

bool Field::checkEat(int c) {

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

void Field::eatCheckerWhite(int x, int y, int dir) {
	int xOneCheck{}, yOneCheck{};
	switch (dir) {
	case 1:
		//std::cout << "MOVE1\n";
		vals[y][x] = 0;
		vals[y - 1][x - 1] = 0;
		vals[y - 2][x - 2] = 2;
		xOneCheck = x - 2;
		yOneCheck = y - 2;
		break;
	case 2:
		//std::cout << "MOVE2\n";
		vals[y][x] = 0;
		vals[y - 1][x + 1] = 0;
		vals[y - 2][x + 2] = 2;
		xOneCheck = x + 2;
		yOneCheck = y - 2;
		break;
	case 3:
		//std::cout << "MOVE3\n";
		vals[y][x] = 0;
		vals[y + 1][x - 1] = 0;
		vals[y + 2][x - 2] = 2;
		xOneCheck = x - 2;
		yOneCheck = y + 2;
		break;
	case 4:
		//std::cout << "MOVE4\n";
		vals[y][x] = 0;
		vals[y + 1][x + 1] = 0;
		vals[y + 2][x + 2] = 2;
		xOneCheck = x + 2;
		yOneCheck = y + 2;
		break;
	}
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			eater[y][x] = 0;
		}
	}
	//	print();
	bool flag = false;
	flag = checkEat(2);
	if ((!flag) and (eater[yOneCheck][xOneCheck] == 1)) {
		eatCheckerWhite(xOneCheck, yOneCheck, direction);
	}
}

void Field::eatCheckerBlack(int x, int y, int dir) {
	int xOneCheck{}, yOneCheck{};
	//std::cout << "DIRECT: " << direction << std::endl;
	//std::cout << "CHECKER: " << "black" << std::endl;
	switch (dir) {
	case 1:
		//std::cout << "MOVE1\n";
		vals[y][x] = 0;
		vals[y - 1][x - 1] = 0;
		vals[y - 2][x - 2] = 1;
		xOneCheck = x - 2;
		yOneCheck = y - 2;
		break;
	case 2:
		//std::cout << "MOVE2\n";
		vals[y][x] = 0;
		vals[y - 1][x + 1] = 0;
		vals[y - 2][x + 2] = 1;
		xOneCheck = x + 2;
		yOneCheck = y - 2;
		break;
	case 3:
		//std::cout << "MOVE3\n";
		vals[y][x] = 0;
		vals[y + 1][x - 1] = 0;
		vals[y + 2][x - 2] = 1;
		xOneCheck = x - 2;
		yOneCheck = y + 2;
		break;
	case 4:
		//std::cout << "MOVE4\n";
		vals[y][x] = 0;
		vals[y + 1][x + 1] = 0;
		vals[y + 2][x + 2] = 1;
		xOneCheck = x + 2;
		yOneCheck = y + 2;
		break;
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
		eatCheckerBlack(xOneCheck, yOneCheck, direction);
	}

}

void Field::checkKing() {
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




