#define _CRT_SECURE_NO_WARNIGNS // 안쓰려면 scanf_s 사용
#include <stdio.h> 

// 배열 회전은 반드시 여분의 배열이 필요하다.
// 배열 회전에서는 인덱스만 잘 계산해도 단순 2중 for문으로 해결 가능하다.
// 삼성전자 코딩테스트에 제일 자주 나오는 부분.

// 출제 가능 포인트
// 2차원 배열의 크기를 입력 받아서 회전. (4로 고정 X).
// 2차원 배열을 왼쪽으로 90도 회전.
// 회전 방향과 각도를 매개 변수로 받아서 회전.

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
