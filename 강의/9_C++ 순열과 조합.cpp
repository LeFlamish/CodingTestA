#include <iostream>
using namespace std;

int N, M;
int answer[10];
bool selected[10];

// 뽑는 숫자의 수가 3개 이하로 고정되어 있으면 for문 돌리는 것이 편함.
// 뽑는 숫자의 수가 3개 이상이거나 변동되면 반드시 재귀 함수.

// 중복 순열
void select1(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << answer[i] << ' ';
		}
		cout << '\n';
		return;
	}
	for (int i = 1; i <= N; i++) {
		answer[cnt] = i;
		select1(cnt + 1);
	}
}

// 순열
void select2(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << answer[i] << ' ';
		}
		cout << '\n';
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (!selected[i]) {
			selected[i] = true;
			answer[cnt] = i;
			select2(cnt + 1);
			selected[i] = false;
		}
	}
}

// 조합
void select3(int cnt, int k) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			cout << answer[i] << ' ';
		}
		cout << '\n';
		return;
	}
	for (int i = k; i <= N; i++) {
		answer[cnt] = i;
		select3(cnt + 1, i + 1);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout << "N개 중에 M개 뽑기\n";
	cout << "N : ";
	cin >> N;
	cout << "M : ";
	cin >> M;

	cout << "중복 순열\n";
	select1(0);

	cout << "순열\n";
	select2(0);

	cout << "조합\n";
	select3(0, 1);

	return 0;
}
