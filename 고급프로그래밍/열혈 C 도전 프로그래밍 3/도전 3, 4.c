#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	printf("난수의 범위 : 0부터 99까지\n");
	srand((int)time(NULL));
	for (int i = 0; i < 5; i++) {
		printf("난수 출력 : %d\n", rand() % 100);
	}
	return 0;
}
