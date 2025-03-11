#include <iostream>
#include <vector>
using namespace std;

int K;
int isMove[5];
string gear[5];
vector<pair<int, int>> oper;

void check() {
	cout << "====================\n";
	for (int i = 1; i < 5; i++) {
		cout << gear[i] << '\n';
	}
	cout << "====================\n";
}

void init() {
	for (int i = 1; i < 5; i++) {
		cin >> gear[i];
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		oper.push_back({ x, y });
	}
}

void checkMove(pair<int, int> O) {
	memset(isMove, 0, sizeof(isMove));
	if (O.first == 1) {
		isMove[1] = O.second;
		if (gear[1][2] != gear[2][6]) isMove[2] = -1 * isMove[1];
		if (gear[2][2] != gear[3][6]) isMove[3] = -1 * isMove[2];
		if (gear[3][2] != gear[4][6]) isMove[4] = -1 * isMove[3];
	}
	else if (O.first == 2) {
		isMove[2] = O.second;
		if (gear[1][2] != gear[2][6]) isMove[1] = -1 * isMove[2];
		if (gear[2][2] != gear[3][6]) isMove[3] = -1 * isMove[2];
		if (gear[3][2] != gear[4][6]) isMove[4] = -1 * isMove[3];
	}
	else if (O.first == 3) {
		isMove[3] = O.second;
		if (gear[2][2] != gear[3][6]) isMove[2] = -1 * isMove[3];
		if (gear[3][2] != gear[4][6]) isMove[4] = -1 * isMove[3];
		if (gear[1][2] != gear[2][6]) isMove[1] = -1 * isMove[2];
	}
	else {
		isMove[4] = O.second;
		if (gear[3][2] != gear[4][6]) isMove[3] = -1 * isMove[4];
		if (gear[2][2] != gear[3][6]) isMove[2] = -1 * isMove[3];
		if (gear[1][2] != gear[2][6]) isMove[1] = -1 * isMove[2];
	}
}

void moveGear(int G, int D) {
	if (D == 0) return;
	if (D == 1) {
		char tmp = gear[G][7];
		for (int i = 0; i < 8; i++) {
			char temp = gear[G][i];
			gear[G][i] = tmp;
			tmp = temp;
		}
	}
	else {
		char tmp = gear[G][0];
		for (int i = 7; i >= 0; i--) {
			char temp = gear[G][i];
			gear[G][i] = tmp;
			tmp = temp;
		}
	}
}

void solve() {
	for (int i = 0; i < K; i++) {
		checkMove(oper[i]);
		for (int j = 1; j < 5; j++) {
			moveGear(j, isMove[j]);
		}
	}
}

int getScore() {
	int ret = 0;
	for (int i = 1; i < 5; i++) {
		if (gear[i][0] == '1') ret += pow(2, i - 1);
	}
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	//check();
	cout << getScore();
	return 0;
}
