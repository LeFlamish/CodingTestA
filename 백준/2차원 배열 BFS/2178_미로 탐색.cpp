#include <iostream>
#include <queue>
using namespace std;
struct State {
	int x, y;
};

int N, M;
string board[100];
int visited[100][100];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0 ,-1 };

void init() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		cin >> board[y];
	}
}

inline bool OOB(int x, int y) {
	return x < 0 || x >= M || y < 0 || y >= N;
}

int BFS() {
	queue<State> Q;
	visited[0][0] = 1;
	Q.push({ 0, 0 });
	while (!Q.empty()) {
		State cur = Q.front(); Q.pop();
		if (cur.x == M - 1 && cur.y == N - 1) return visited[cur.y][cur.x];
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || board[ny][nx] == '0') continue;
			visited[ny][nx] = visited[cur.y][cur.x] + 1;
			Q.push({ nx, ny });
		}
	}
	return -1;
}

int main(void) {
	cin.tie(0)->sync_with_stdio(0);
	init();
	cout << BFS();
	return 0;
}
