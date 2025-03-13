/*
왼쪽 아래를 0, 0으로 보는 것은 프로그래밍에서 불편하다.
따라서 오른쪽으로 90도를 돌려서 보면, 전혀 문제가 되지 않음을 생각해볼 수 있다.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct State {
	int x, y;
};

int M, N, K;
bool board[101][101];
bool visited[101][101];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
vector<int> ret;

void init() {
	cin >> M >> N >> K;
	for (int k = 0; k < K; k++) {
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		for (int y = y1; y < y2; y++) {
			for (int x = x1; x < x2; x++) {
				board[y][x] = true; // 겹치더라도 그냥 그 위치에 직사각형이 있다는 것이 중요함. 얼마나 겹치는지는 중요하지 않음.
			}
		}
	}
}

inline bool OOB(int x, int y) {
	return x < 0 || x >= M || y < 0 || y >= N;
}

int BFS(int x, int y) {
	int cnt = 0;
	queue<State> Q;
	visited[y][x] = true;
	Q.push({ x, y });
	while (!Q.empty()) {
		State cur = Q.front(); Q.pop();
		cnt++;
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || board[ny][nx]) continue;
			visited[ny][nx] = true;
			Q.push({ nx, ny });
		}
	}
	return cnt;
}

void solve() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (!visited[y][x] && !board[y][x]) {
				ret.push_back(BFS(x, y));
			}
		}
	}
	sort(ret.begin(), ret.end());
	cout << ret.size() << '\n';
	for (int i : ret) cout << i << ' ';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
