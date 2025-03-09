#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int, int> CD;
#define X first
#define Y second
struct Human {
	int x, y;
	bool isTimeWall;
};
struct Anomaly {
	int x, y;
	int d;
	int v;
};

int N, M, F;
int board[20][20];
int startTWx, startTWy;
int timewall[30][30];
bool visitedB[20][20];
bool visitedT[20][20];
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
Anomaly anomalys[10];
Human H;
queue<Human> Q;

void check(int turn) {
	cout << "====================\n";
	cout << turn << '\n';
	cout << "====================\n";
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cout << board[y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "====================\n";
	for (int y = 0; y < 3 * M; y++) {
		for (int x = 0; x < 3 * M; x++) {
			cout << timewall[y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "====================\n";
}

void init() {
	memset(timewall, -1, sizeof(timewall));
	cin >> N >> M >> F;

	// 미지의 공간 입력
	bool flag = false;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			if (!flag && board[y][x] == 3) {
				startTWx = x;
				startTWy = y;
				flag = true;
			}
		}
	}

	// 시간의 벽 동쪽
	for (int x = 2 * M; x < 3 * M; x++) {
		for (int y = 2 * M - 1; y >= M; y--) {
			cin >> timewall[y][x];
		}
	}

	// 시간의 벽 서쪽
	for (int x = M - 1; x >= 0; x--) {
		for (int y = M; y < 2*M; y++) {
			cin >> timewall[y][x];
		}
	}
	
	// 시간의 벽 남쪽
	for (int y = 2 * M; y < 3 * M; y++) {
		for (int x = M; x < 2 * M; x++) {
			cin >> timewall[y][x];
		}
	}

	// 시간의 벽 북쪽
	for (int y = M - 1; y >= 0; y--) {
		for (int x = 2 * M - 1; x >= M; x--) {
			cin >> timewall[y][x];
		}
	}

	// 시간의 벽 윗면
	for (int y = M; y < 2 * M; y++) {
		for (int x = M; x < 2 * M; x++) {
			cin >> timewall[y][x];
			if (timewall[y][x] == 2) {
				H.x = x;
				H.y = y;
				H.isTimeWall = true;
				Q.push(H);
			}
		}
	}

	// 시간 이상 현상
	for (int f = 0; f < F; f++) {
		cin >> anomalys[f].y >> anomalys[f].x >> anomalys[f].d >> anomalys[f].v;
		board[anomalys[f].y][anomalys[f].x] = 5;
	}
}

bool exitTimeWall(int x, int y) {
	return (x < 0 || x >= 3 * M || y < 0 || y >= 3 * M);
}

bool area(int x, int y) {
	return (x < 0 || x >= N || y < 0 || y >= N);
}

void moveAnomaly(int turn) {
	for (int f = 0; f < F; f++) {
		if (turn % anomalys[f].v == 0) {
			int nx = anomalys[f].x + dx[anomalys[f].d];
			int ny = anomalys[f].y + dy[anomalys[f].d];
			if (board[ny][nx] == 1 || board[ny][nx] == 3 || board[ny][nx] == 4) continue;
			board[ny][nx] = 5;
			anomalys[f].x = nx;
			anomalys[f].y = ny;
		}
	}
}

bool moveHuman() {
	int size = Q.size();
	for (int i = 0; i < size; i++) {
		Human cur = Q.front(); Q.pop();
		if (!cur.isTimeWall && board[cur.y][cur.x] == 4) return true;
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (cur.isTimeWall) { // 아직 시간의 벽에 존재할 때
				if (exitTimeWall(nx, ny)) { // 다음 턴에 시간의 벽을 탈출할 때
					if (nx == -1) { // 시간의 벽의 서쪽으로 탈출했다면
						nx = startTWx - 1;
						ny = startTWy + (ny % M);
					}
					else if (nx == 3 * M) { // 시간의 벽의 동쪽으로 탈출했다면
						nx = startTWx + M;
						ny = startTWy + (ny % M);
					}
					else if (ny == -1) { // 시간의 벽의 북쪽으로 탈출했다면
						nx = startTWx + (nx % M);
						ny = startTWy - 1;
					}
					else { // 시간의 벽의 남쪽으로 탈출했다면
						nx = startTWx + (nx % M);
						ny = startTWy + M;
					}
					if (area(nx, ny)) continue;
					if (visitedB[ny][nx] || board[ny][nx] == 1 || board[ny][nx] == 3 || board[ny][nx] == 5) continue;
					visitedB[ny][nx] = true;
					Human tmp = { nx, ny, false };
					Q.push(tmp);
				}
				else { // 다음 턴에도 시간의 벽에 있을 때
					if (timewall[ny][nx] == -1) { // 시간의 벽을 옆으로 이동할 때
						if (dir == 0) { // 시간의 벽을 옆으로 이동할 때, 전개도에서 동쪽으로 이동했다면
							if (ny < M) { // 오른쪽 위에 해당
								nx = 3 * M - 1 - ny;
								ny = M;
							}
							else { // 오른쪽 아래에 해당
								int tmp = nx;
								nx = ny;
								ny = tmp - 1;
							}
						}
						else if (dir == 1) { // 시간의 벽을 옆으로 이동할 때, 전개도에서 서쪽으로 이동했다면
							if (ny < M) { // 왼쪽 위에 해당
								int tmp = nx;
								nx = ny;
								ny = tmp + 1;
							}
							else { // 왼쪽 아래에 해당
								nx = 3 * M - 1 - ny;
								ny = 2 * M - 1;
							}
						}
						else if (dir == 2) { // 시간의 벽을 옆으로 이동할 때, 전개도에서 남쪽으로 이동했다면
							if (nx < M) { // 왼쪽 아래에 해당
								ny = 3 * M - 1 - nx;
								nx = M;
							}
							else { // 오른쪽 아래에 해당
								int tmp = nx;
								nx = ny - 1;
								ny = tmp;
							}
						}
						else { // 시간의 벽을 옆으로 이동할 때, 전개도에서 북쪽으로 이동했다면
							if (nx < M) { // 왼쪽 위에 해당
								int tmp = nx;
								nx = ny + 1;
								ny = tmp;
							}
							else { // 오른쪽 위에 해당
								ny = 3 * M - 1 - nx;
								nx = 2 * M - 1;
							}
						}
					}
					else { // 그냥 전개도 따라 정상적으로 이동할 때

					}
					if (visitedT[ny][nx] || timewall[ny][nx] == 1) continue;
					visitedT[ny][nx] = true;
					Human tmp = { nx, ny, true };
					Q.push(tmp);
				}

			}
			else { // 시간의 벽에서 탈출해서 미지의 공간에 있을 때
				if (area(nx, ny)) continue;
				if (visitedB[ny][nx] || board[ny][nx] == 1 || board[ny][nx] == 3 || board[ny][nx] == 5) continue;
				visitedB[ny][nx] = true;
				Human tmp = { nx, ny, false };
				Q.push(tmp);
			}
		}
	}
	return false;
}

void solve() {
	int turn = 1;
	while (!Q.empty()) {
		moveAnomaly(turn);
		if (moveHuman()) {
			cout << turn - 1;
			return;
		}
		// check(turn);
		turn++;
	}
	cout << -1;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
