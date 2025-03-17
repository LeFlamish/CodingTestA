#include <bits/stdc++.h>
using namespace std;
#define SIZE 51

// robotX, robotY, robotDir을 변수로 만드는 것이 아니라, 로봇 객체가 하나뿐이라도 Robot 구조체를 만드는 것을 추천.
int N, M, robotX, robotY, robotDir;
int board[SIZE][SIZE];
bool cleaned[SIZE][SIZE];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

void init() {
	cin >> N >> M >> robotY >> robotX >> robotDir;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> board[y][x];
		}
	}
	cleaned[robotY][robotX] = true;
}

bool cleanCheck() {
	for (int dir = 0; dir < 4; dir++) {
		int nx = robotX + dx[dir];
		int ny = robotY + dy[dir];
		if (board[ny][nx] || cleaned[ny][nx]) continue;
		return true;
	}
	return false;
}

void doClean() {
	for (int dir = 0; dir < 4; dir++) {
		robotDir = (robotDir + 3) % 4;
		int nx = robotX + dx[robotDir];
		int ny = robotY + dy[robotDir];
		if (board[ny][nx] == 0 && !cleaned[ny][nx]) {
			cleaned[ny][nx] = true;
			robotX = nx;
			robotY = ny;
			return;
		}
	}
}

bool stopRobot() {
	int backward = (robotDir + 2) % 4;
	if (board[robotY + dy[backward]][robotX + dx[backward]] == 1) return true;
	else {
		robotX += dx[backward];
		robotY += dy[backward];
		return false;
	}
}

int solve() {
	int ret = 1;
	while(1) {
		if (cleanCheck()) {
			doClean();
			ret++;
		}
		else {
			if (stopRobot()) break;
		}
	}
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	cout << solve();
	return 0;
}
