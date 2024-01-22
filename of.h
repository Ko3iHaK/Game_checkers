#pragma once

#undef min
#undef max
#include <iostream>
#include "GamePl.h"

int SIZEZ = 30;
int MARK{ 0 };
int count = 4;
int countReal = 0;
int MIN = -1000;
int MAX = 1000;
bool tmp = false;
int tmp1 = 1000;

struct Positions {
	int xIndexMove;
	int yIndexMove;
	int direction;
};

struct Tree {
	int mark;
	Field value;
	int colorQueue;
	Positions pos;
	Positions* posChilds{};
	Tree** child;
	int sizeChild;
	Tree() : child(new Tree* [SIZEZ]) { for (int i = 0; i < SIZEZ; i++) child[i] = 0; }
	//~Tree() { for (int i = 0; i < SIZE; i++) { delete child[i]; } delete[] child; }

};

class NTree {
private:
	void freeTree(Tree* T);
	void add(Tree*& T, Field F, bool c);
	void printing(Tree* T, int sh);
	void posCheck(Tree* T);
	void countCheck(Tree* T);
	bool movesCount(Tree* T, bool color);
	void eatCheck(Tree* T, int c);
	void moving(Tree* T, int c, bool flag);
	void movNotChange(Tree* T, int c);
	void eating(Tree* T, int c);
	void findIndex(Tree* T, bool color);
	void findIndexEating(Tree* T, bool color);
	bool findSecondIndexEat(Tree* T, int x, int y);
	void moveCheck(Tree* T, int c);
	int checkMark(Tree* T, int color);
	int minMax(Tree* T, int alpha, int beta);
	void stateSelection(Tree* T);
	void treeUpdate(Tree* T, Field F, bool c, int countRealUpdate);
public:
	int moves;
	Tree* root;
	NTree();
	~NTree();
	void stateSel();
	void addElement(Field F, int c);
	void MM();
	void TU(Field F, bool c, int countRealUpdate);
	void moveC(Tree* T);
	void eatC();
	void mov(int c);
	void eat(int c);
	void print();
};


NTree::NTree() {
	root = nullptr;
}

NTree::~NTree() {
	delete root;
}

void NTree::freeTree(Tree* T) {

}

void NTree::stateSel() {
	stateSelection(root);
}

void NTree::print() {
	printing(root, 5);
}

void NTree::addElement(Field F, int c) {
	add(root, F, c);
}

void NTree::MM() {
	moveC(root);
}

void NTree::TU(Field F, bool c, int countRealUpdate) {
	treeUpdate(root, F, c, countRealUpdate);
}

void NTree::moveC(Tree* T) {
	T->mark = minMax(T, MIN, MAX);
	for (int i = 0; i < T->sizeChild; i++) {
		moveC(T->child[i]);
	}
}

void NTree::eatC() {
	eatCheck(root, 1);
}

void NTree::printing(Tree* T, int sh) {
	if (!T) return;
	for (int j = 0; j < sh; j++)
		std::cout << ' ';
	std::cout << T->mark << std::endl;
	for (int i = 0; i < T->sizeChild; i++)
		printing(T->child[i], sh + 5);
}




void NTree::treeUpdate(Tree* T, Field F, bool c, int countRealUpdate) {
	countReal++;
	if (countReal == count) { return; }
	c = !c;
	if (countRealUpdate == 1) { T->value = F; }
	countRealUpdate = 0;
	delete[] T->posChilds;
	bool flag = movesCount(T, c);
	T->sizeChild = moves;
	T->posChilds = new Positions[T->sizeChild];
	if (flag) {
		findIndex(T, c);
	}
	else {
		findIndexEating(T, c);
	}
	//std::cout << countReal << "++++++++++++++++++++++++++++++++++++++++++++\n";
	for (int i = 0; i < T->sizeChild; i++) {
		if (!T->child[i]) T->child[i] = new Tree();
		T->child[i]->value = T->value;
		T->child[i]->pos = T->posChilds[i];
		if (c) { T->child[i]->colorQueue = 1; }
		else { T->child[i]->colorQueue = 2; }
		moving(T->child[i], T->child[i]->colorQueue, flag);
	}
	for (int i = 0; i < T->sizeChild; i++) {
		treeUpdate(T->child[i], T->value, c, countRealUpdate);
		countReal--;
	}
}



void NTree::add(Tree*& T, Field F, bool c) {
	if (!T) {
		T = new Tree();
		countReal++;
		if (countReal == count) { return; }
		T->value = F;
		if (c) T->colorQueue = 1;
		else T->colorQueue = 2;
		bool flag = movesCount(T, T->colorQueue);
		T->sizeChild = moves;
		T->posChilds = new Positions[T->sizeChild];
		if (flag) {
			findIndex(T, T->colorQueue);
		}
		else {
			findIndexEating(T, T->colorQueue);
		}
		for (int i = 0; i < SIZEZ; i++) { T->child[i] = new Tree(); T->child[i]->value = F; }
		for (int i = 0; i < T->sizeChild; i++) {
			T->child[i]->value = T->value;
			T->child[i]->pos = T->posChilds[i];
			if (c) T->child[i]->colorQueue = 1;
			else T->child[i]->colorQueue = 2;
			moving(T->child[i], T->colorQueue, flag);
		}
		for (int i = 0; i < T->sizeChild; i++) {
			add(T->child[i], T->value, c);
			countReal--;
		}
	}
	else {
		countReal++;
		if (countReal == count) { return; }
		c = !c;
		bool flag = movesCount(T, c);
		T->sizeChild = moves;
		T->posChilds = new Positions[T->sizeChild];
		if (flag) {
			findIndex(T, c);
		}
		else {
			findIndexEating(T, c);
		}
		for (int i = 0; i < SIZEZ; i++) { T->child[i] = new Tree(); T->child[i]->value = F; }
		for (int i = 0; i < T->sizeChild; i++) {
			T->child[i]->value = T->value;
			T->child[i]->pos = T->posChilds[i];
			if (c) { T->child[i]->colorQueue = 1; }
			else { T->child[i]->colorQueue = 2; }
			moving(T->child[i], T->child[i]->colorQueue, flag);

		}
		for (int i = 0; i < T->sizeChild; i++) {
			add(T->child[i], T->value, c);
			countReal--;
		}
	}
}

int NTree::checkMark(Tree* T, int color) {
	int c;
	if (color == 1) c = 2;
	else c = 1;
	int _mark;
	posCheck(T);
	countCheck(T);
	moveCheck(T, c);
	eatCheck(T, c);
	_mark = MARK;
	MARK = 0;
	return _mark;
}

void NTree::posCheck(Tree* T) {
	for (int y = 3; y < 7; y++) {
		for (int x = 0; x < 10; x++) {
			if (T->value.vals[y][x] == 1) {
				MARK++;
			}
			else if (T->value.vals[y][x] == 2) {
				MARK--;
			}
		}
	}
}

void NTree::countCheck(Tree* T) {
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (T->value.vals[y][x] == 1) {
				MARK = MARK + 2;
				if (T->value.king[y][x] == 1) {
					MARK = MARK + 2;
				}
			}
			if (T->value.vals[y][x] == 2) {
				MARK = MARK - 2;
				if (T->value.king[y][x] == 2) {
					MARK = MARK - 2;
				}
			}
		}
	}
}

void NTree::moveCheck(Tree* T, int c) {
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (c == 1) {
				if (T->value.vals[y][x] == c) {
					if ((x - 1 >= 0) and (y + 1 < 10)) {
						if (T->value.vals[y + 1][x - 1] == 0) {
							MARK++;
						}
					}
					if ((x - 1 > 0) and (y - 1 > 0)) {
						if (T->value.vals[y + 1][x + 1] == 0) {
							MARK++;
						}
					}
				}
			}
			if (c == 2) {
				if (T->value.vals[y][x] == c) {
					if ((x - 1 >= 0) and (y - 1 >= 0)) {
						if (T->value.vals[y - 1][x - 1] == 0) {
							MARK--;
						}
					}
					if ((x + 1 < 10) and (y - 1 >= 0)) {
						if (T->value.vals[y - 1][x + 1] == 0) {
							MARK--;
						}
					}
				}
			}
		}
	}
}

void NTree::eatCheck(Tree* T, int c) {
	bool flag = T->value.checkEat(c);
	if (c == 1) MARK = MARK + T->value.eat;
	else MARK = MARK - T->value.eat;
}


bool NTree::movesCount(Tree* T, bool color) {
	int c;
	if (color) c = 1;
	else c = 2;
	moves = 0;
	if (T->value.checkEat(c)) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				if (c == 1) {
					if (T->value.vals[y][x] == c) {
						if ((x - 1 >= 0) and (y + 1 < 10)) {
							if (T->value.vals[y + 1][x - 1] == 0) {

								moves++;
							}
						}
						if ((x + 1 < 10) and (y + 1 < 10)) {
							if (T->value.vals[y + 1][x + 1] == 0) {

								moves++;
							}
						}
					}
				}
				else if (c == 2) {
					if (T->value.vals[y][x] == c) {
						if ((x - 1 >= 0) and (y - 1 > 0)) {
							if (T->value.vals[y - 1][x - 1] == 0) {

								moves++;
							}
						}
						if ((x + 1 < 10) and (y - 1 >= 0)) {
							if (T->value.vals[y - 1][x + 1] == 0) {

								moves++;
							}
						}
					}
				}
			}
		}
		return true;
	}
	else if (!T->value.checkEat(c)) {
		moves = T->value.eat;
		return false;
	}
	return true;
}



void NTree::findIndex(Tree* T, bool color) {
	int c;
	if (color) c = 1;
	else c = 2;
	int i = 0;
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (c == 1) {
				if (T->value.vals[y][x] == c) {
					if ((x - 1 >= 0) and (y + 1 < 10)) {
						if (T->value.vals[y + 1][x - 1] == 0) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 0;
							i++;
						}
					}
					if ((x + 1 < 10) and (y + 1 < 10)) {
						if (T->value.vals[y + 1][x + 1] == 0) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 1;
							i++;
						}
					}
				}
			}
			else if (c == 2) {
				if (T->value.vals[y][x] == c) {
					if ((x - 1 >= 0) and (y - 1 >= 0)) {
						if (T->value.vals[y - 1][x - 1] == 0) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 0;
							i++;
						}
					}
					if ((x + 1 < 10) and (y - 1 >= 0)) {
						if (T->value.vals[y - 1][x + 1] == 0) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 1;
							i++;
						}
					}
				}
			}
		}
	}

}


void NTree::findIndexEating(Tree* T, bool color) {
	int c;
	if (color) c = 1;
	else c = 2;
	int i = 0;
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (c == 1) {
				if (T->value.eater[y][x] == 1) {
					if ((x + 2 < 10) and (y + 2 < 10)) {
						if ((T->value.vals[y + 2][x + 2] == 0) and (T->value.vals[y + 1][x + 1] == 2)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 4;
							i++;
						}
					}
					if ((x + 2 < 10) and (y - 2 >= 0)) {
						if ((T->value.vals[y - 2][x + 2] == 0) and (T->value.vals[y - 1][x + 1] == 2)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 2;
							i++;
						}
					}
					if ((x - 2 >= 0) and (y + 2 < 10)) {
						if ((T->value.vals[y + 2][x - 2] == 0) and (T->value.vals[y + 1][x - 1] == 2)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 3;
							i++;
						}
					}
					if ((x - 2 >= 0) and (y - 2 >= 0)) {
						if ((T->value.vals[y - 2][x - 2] == 0) and (T->value.vals[y - 1][x - 1] == 2)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 1;
							i++;
						}
					}
				}
			}
			else {
				if (T->value.eater[y][x] == 1) {
					if ((x + 2 < 10) and (y + 2 < 10)) {
						if ((T->value.vals[y + 2][x + 2] == 0) and (T->value.vals[y + 1][x + 1] == 1)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 4;
							i++;
						}
					}
					if ((x + 2 < 10) and (y - 2 >= 0)) {
						if ((T->value.vals[y - 2][x + 2] == 0) and (T->value.vals[y - 1][x + 1] == 1)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 2;
							i++;
						}
					}
					if ((x - 2 >= 0) and (y + 2 < 10)) {
						if ((T->value.vals[y + 2][x - 2] == 0) and (T->value.vals[y + 1][x - 1] == 1)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 3;
							i++;
						}
					}
					if ((x - 2 >= 0) and (y - 2 >= 0)) {
						if ((T->value.vals[y - 2][x - 2] == 0) and (T->value.vals[y - 1][x - 1] == 1)) {
							T->posChilds[i].xIndexMove = x;
							T->posChilds[i].yIndexMove = y;
							T->posChilds[i].direction = 1;
							i++;
						}
					}
				}
			}
		}
	}

}


void NTree::moving(Tree* T, int c, bool flag) {
	if (flag) {
		if (c == 1) {
			//std::cout << "+++++++++++++++++++++++++++++++\n";
			T->value.simpleMoveBlack(T->pos.xIndexMove, T->pos.yIndexMove, T->pos.direction);
		}
		else {
			T->value.simpleMoveWhite(T->pos.xIndexMove, T->pos.yIndexMove, T->pos.direction);
		}
	}
	else {
		int secondEat;
		if (c == 1) {
			T->value.eatCheckerBlack(T->pos.xIndexMove, T->pos.yIndexMove, T->pos.direction);
		}
		else {
			T->value.eatCheckerWhite(T->pos.xIndexMove, T->pos.yIndexMove, T->pos.direction);
		}
	}
}


int NTree::minMax(Tree* T, int alpha, int beta) {
	int best = MIN;
	if (T->sizeChild == 0) {
		return checkMark(T, T->colorQueue);
	}
	else {
		for (int i = 0; i < T->sizeChild; i++) {
			best = std::max(best, -minMax(T->child[i], -beta, -alpha));
			alpha = std::max(alpha, best);
			if (alpha > beta) break;
		}
	}
	return best;
}


void NTree::stateSelection(Tree* T) {
	int best = MAX;
	for (int i = 0; i < T->sizeChild; i++) {
		if (T->child[i]->mark < best) best = T->child[i]->mark;
	}
	for (int i = 0; i < T->sizeChild; i++) {
		if (T->child[i]->mark == best) {
			T->value = T->child[i]->value;
			break;
		}
	}
}