#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// 1번.
int board[10][10];
int dir;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

// 2번.
bool selected[10];

int main() {



	// 1번.
	srand((int)time(NULL));
	int n = (rand() % 10) + 1;
	int cx = 0, cy = 0;
	int cnt;
	printf("n : %d\n", n);
	if (n & 1) { // 홀수일 때
		cnt = n * n;
		dir = 0;
		while (cnt >= 1) {
			board[cy][cx] = cnt--;
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || board[ny][nx]) {
				dir = (dir + 1) % 4;
			}
			cx += dx[dir];
			cy += dy[dir];
		}
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				printf("%2d ", board[y][x]);
			}
			printf("\n");
		}
	}
	else { // 짝수일 때
		cnt = 1;
		dir = 1;
		while (cnt <= n * n) {
			board[cy][cx] = cnt++;
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || board[ny][nx]) {
				dir = (dir + 3) % 4;
			}
			cx += dx[dir];
			cy += dy[dir];
		}
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				printf("%2d ", board[y][x]);
			}
			printf("\n");
		}
	}
	


	// 2번.
	int computer[2];
	int player[2];
	int Cnt = 0;
	while (Cnt < 2) {
		int num = rand() % 10;
		if (selected[num]) continue;
		selected[num] = true;
		computer[Cnt++] = num;
	}
	while (1) {
		int strike = 0, ball = 0;
		while (1) {
			printf("서로 다른 숫자 2 개를 입력해주세요.(0 ~ 9) : ");
			scanf_s("%d %d", &player[0], &player[1]);
			if (player[0] > 9 || player[1] > 9) {
				printf("0 ~ 9의 숫자만 입력해주세요.\n");
				continue;
			}
			if (player[0] != player[1]) break;
			else printf("중복된 숫자를 입력하였습니다.\n");
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (player[i] == computer[j]) {
					if (i == j) {
						strike++;
						break;
					}
					else {
						ball++;
						break;
					}
				}
			}
		}
		if (strike) printf("%d strike\n", strike);
		else if (ball) printf("%d ball\n", ball);
		else printf("0 strike, 0 ball\n");
		if (strike == 2) break;
	}
	printf("정답입니다!\n게임 종료.");



	return 0;
}
