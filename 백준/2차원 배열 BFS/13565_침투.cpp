#include <iostream>
#include <queue>
#include <string>
using namespace std;
typedef pair<int, int> CD;
#define X first
#define Y second

int M, N;
string board[1000];
bool visited[1000][1000];
queue<CD> Q;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

// 초기화 함수
void init() {
	cin >> M >> N;
	for (int i = 0; i < M; i++) {
		cin >> board[i];
	}
	for (int i = 0; i < N; i++) {
		if (board[0][i] == '0') {
			visited[0][i] = true;
			Q.push(make_pair(i, 0));
		}
	}
}

// BFS함수를 bool형으로 선언하여서 도착하면 true를 반환하고, 도착하지 못하면 false 반환.
bool BFS() {
	while (!Q.empty()) {
		CD cur = Q.front(); Q.pop();
		if (cur.Y == M - 1) {
			return true;
		}
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (visited[ny][nx] || board[ny][nx] == '1') continue;
			visited[ny][nx] = true;
			Q.push(make_pair(nx, ny));
		}
	}
	return false;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	if (BFS()) cout << "YES";
	else cout << "NO";
	return 0;
}
