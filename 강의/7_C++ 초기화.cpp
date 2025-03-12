#include <iostream>
#include <cstring> // memset을 사용하기 위한 라이브러리
#include <algorithm> // fill을 사용하기 위한 라이브러리
using namespace std;

int board[10][10];

int main() {
	cin.tie(0)->sync_with_stdio(0);

	// -1, 0을 제외하고 나머지 값으로 초기화를 하기 위해서는 fill 사용. -1, 0도 가능하지만 memset이 더 편리.
	// 2차원 배열에서 사용하기 위해서는 for문 사용 필수.
	for (int i = 0; i < 10; i++) {
		fill(board[i], board[i] + 10, 7); // fill(배열 시작 주소, 배열 끝주소, 초기화 값);
	}

	// memset은 byte 단위로 초기화 진행. 따라서 -1, 0을 제외하고는 오류가 발생할 가능성이 높음.
	// -1, 0로 초기화를 하기 위해서는 memset이 훨씬 더 편리.
	memset(board, 0, sizeof(board)); // memset(배열 이름, 초기화 값, sizeof(배열 이름));
	return 0;
}
