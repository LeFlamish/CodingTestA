#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int computer[3];
bool selected[10];

int main() {
	printf("Start Game!\n");
	int cnt = 0;
	while (cnt < 3) {
		srand((int)time(NULL));
		int num = rand() % 10;
		if (selected[num]) continue;
		selected[num] = true;
		computer[cnt++] = num;
	}
	int t = 0;
	while (1) {
		t++;
		int strike = 0, ball = 0;
		printf("3개의 숫자 선택 : ");
		int player[3];
		for (int i = 0; i < 3; i++) {
			scanf_s("%d", &player[i]);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == j && player[i] == computer[j]) strike++;
				else if (player[i] == computer[j]) ball++;
			}
		}
		printf("%d번째 도전 결과 : %d strike, %d ball!!\n", t, strike, ball);
		if (strike == 3) break;
	}
	printf("Game Over");
	return 0;
}
