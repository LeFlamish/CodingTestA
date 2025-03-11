#include <iostream>
using namespace std;
// 결국 각 칸에 로봇이 있고 없고가 중요하고 각 칸마다 내구성이 존재하므로 칸을 객체로 생각하기 위하여 구조체 선언.
struct Belt {
	int dur;
	bool onRobot;
};

int N, K;
Belt belt[2][101]; // 2차원 배열로 풀지 않고 1차원 배열로 풀어도 됨. 1차원 배열 풀이가 더 편할지도.
Belt tmp[2][101]; // belt 회전을 위한 여분 배열.

// belt의 상황을 확인하기 위한 디버깅 함수.
void debug() {
	cout << "====================\n";
	for (int y = 0; y < 2; y++) {
		for (int x = 1; x <= N; x++) {
			cout << belt[y][x].dur << ' ';
		}
		cout << '\n';
	}
	cout << "====================\n";
}

// 초기화 함수.
void init() {
	cin >> N >> K;
	for (int x = 1; x <= N; x++) cin >> belt[0][x].dur;
	for (int x = N; x >= 1; x--) cin >> belt[1][x].dur; // 아래 컨베이어 벨트는 순서를 반대로 받아야 함.
}

// 회전한 컨베이어 벨트는 tmp에 있는데 tmp를 그대로 belt로 복사해서 belt에 회전한 것 저장.
void copyToBelt() {
	for (int y = 0; y < 2; y++) {
		for (int x = 1; x <= N; x++) {
			belt[y][x] = tmp[y][x];
		}
	}
}

// 배열 회전 수행 후, copyToBelt 함수 호출하여 회전 수행. 
void rotate() {
	for (int x = 1; x < N; x++) {
		tmp[0][x + 1] = belt[0][x];
		tmp[1][x] = belt[1][x + 1];
	}
	tmp[1][N] = belt[0][N];
	tmp[0][1] = belt[1][1];
	copyToBelt();
}

// 컨베이어 벨트 위에서의 로봇 움직임.
void moveRobot() {
	belt[0][N].onRobot = false;
	for (int x = N - 1; x > 0; x--) { // 반드시 역순으로 해야 먼저 올라간 로봇부터 움직임.
		if (belt[0][x].onRobot && !belt[0][x + 1].onRobot && belt[0][x + 1].dur) { // 현재 로봇이 있고 다음 칸에 로봇이 없으며 다음 칸의 내구성이 남아있는 경우에만 이동
			belt[0][x].onRobot = false;
			belt[0][x + 1].onRobot = true;
			belt[0][x + 1].dur--;
		}
	}
	belt[0][N].onRobot = false;
}

// 로봇을 컨베이어 벨트에 올리는 과정.
void putRobot() {
	if (belt[0][1].dur) {
		belt[0][1].onRobot = true;
		belt[0][1].dur--;
	}
}

// dur == 0이 될 때마다 cnt--하는 방식도 있지만, 귀찮아서 매번 확인하는 방식.
bool checkEnd() {
	int cnt = 0;
	for (int y = 0; y < 2; y++) {
		for (int x = 1; x <= N; x++) {
			if (!belt[y][x].dur) cnt++;
		}
	}
	if (cnt >= K) return true;
	return false;
}

void solve() {
	int t = 0;
	while (1) { // 문제에서 준 순서대로 동작별 함수를 실행.
		t++;
		rotate();
		moveRobot();
		putRobot();
		//debug();
		if (checkEnd()) break;
	}
	cout << t;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
