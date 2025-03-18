#include <stdio.h>

// 배열 회전은 반드시 여분의 배열이 필요하다.
// 배열 회전에서는 인덱스만 잘 계산해도 단순 2중 for문으로 해결 가능하다.

int board[4][4];
int tmp[4][4];

void init() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			board[y][x] = y * 4 + x + 1;
		}
	}
}

void copyBoard() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			board[y][x] = tmp[y][x];
		}
	}
}

void rotateRight() {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			tmp[x][y] = board[3 - y][x];
		}
	}
	copyBoard();
}

void rotateLeft() {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			tmp[x][y] = board[y][3 - x];
		}
	}
	copyBoard();
}

void printBoard() {
	printf("====================\n");
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			printf("%d ", board[y][x]);
		}
		printf("\n");
	}
	printf("====================\n");
}

int main() {
	init();
	printBoard();
	rotateRight();
	printBoard();
	rotateLeft();
	printBoard();
	return 0;
}
