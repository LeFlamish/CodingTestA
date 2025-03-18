#define _CRT_SECURE_NO_WARNINGS // 안쓰려면 scanf_s 사용
#include <stdio.h>
#include <stdbool.h>

// 여러가지 방법이 있을 수 있지만 이 방법을 외워야 한다.
// dx/dy 테크니션으로 해결 가능.

// 출제 가능 포인트
// 왼쪽으로 달팽이 배열.
// 지그재그, S자 등등.
// 출발점이 다른 달팽이 배열.
// 아주 다양하다.

int N;
int board[100][100];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void init() {
	scanf("%d", &N);
}

bool OOB(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= N;
}

// dx/dy 테크니션이 빛을 발하는 순간.
void makeBoard() {
	int cx, cy, curD;
	cx = cy = curD = 0;
	for (int i = 1; i <= N * N; i++) {
		board[cy][cx] = i;
		int nx = cx + dx[curD];
		int ny = cy + dy[curD];
		if (OOB(nx, ny) || board[ny][nx] > 0) curD = (curD + 1) % 4;
		cx += dx[curD];
		cy += dy[curD];
	}
}

void printBoard() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			printf("%2d ", board[y][x]);
		}
		printf("\n");
	}
}

int main() {
	init();
	makeBoard();
	printBoard();
	return 0;
}
