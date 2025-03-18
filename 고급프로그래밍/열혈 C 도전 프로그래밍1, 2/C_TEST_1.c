#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 1번 문제의 함수
double recursive(int n) {
	if (n == 0) return 1;
	if (n > 0) return recursive(n - 1) * 2;
	else return recursive(n + 1) / 2;
}

// 3번 문제의 함수
bool isPalindrome(char* str, int len) {
	bool flag = true;
	for (int i = 0; i < len; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') str[i] += 'A' - 'a';
	}
	for (int i = 0; i < len / 2; i++) {
		if (str[i] != str[len - 1 - i]) {
			flag = false;
			break;
		}
	}
	return flag;
}

int main() {
	// 1번.
	int num1;
	printf("양수 n을 입력해주세요. : ");
	scanf("%d", &num1);
	printf("2의 %d승은 %g입니다.\n\n", num1, recursive(num1));

	

	// 2번.
	int num2, cnt = 0;
	int arr[100];
	printf("10진수 형태 정수를 입력해주세요 : ");
	scanf("%d", &num2);
	while (num2 > 0) {
		arr[cnt++] = num2 % 2;
		num2 /= 2;
	}
	printf("%d의 2진수는 ", num2);
	for (int i = --cnt; i >= 0; i--) {
		printf("%d", arr[i]);
	}
	printf("입니다.\n\n");
	


	// 3번.
	char str[100];
	int len;
	printf("단어를 입력해주세요 : ");
	scanf("%s", str);
	len = strlen(str);
	if (isPalindrome(str, len)) printf("회문입니다.\n");
	else printf("회문이 아닙니다.\n");
	


	return 0;
}
