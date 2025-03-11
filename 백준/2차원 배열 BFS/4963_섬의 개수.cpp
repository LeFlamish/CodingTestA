#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
struct State {
	int x, y;
};

const int SIZE = 51;
int W, H, board[SIZE][SIZE], cnt;
bool visited[SIZE][SIZE];
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

// 초기화 함수. 입력을 받을 때, W와 H가 모두 0이면 false를 반환하며 종료. 이외에는 정상 입력이므로 true 반환.
bool init() {
	cnt = 0;
	memset(board, 0, sizeof(board));
	memset(visited, false, sizeof(visited));
	cin >> W >> H;
	if (W == 0 && H == 0) return false;
	for (int h = 0; h < H; h++) {
		for (int w = 0; w < W; w++) {
			cin >> board[h][w];
		}
	}
	return true;
}

// Out Of Bounds
inline bool OOB(int x, int y) {
	return x < 0 || x >= W || y < 0 || y >= H;
}

void BFS(int x, int y) {
	visited[y][x] = true;
	queue<State> Q;
	Q.push({ x, y });
	while (!Q.empty()) {
		State cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 8; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || !board[ny][nx]) continue;
			visited[ny][nx] = true;
			Q.push({ nx, ny });
		}
	}
}

void solve() {
	for (int h = 0; h < H; h++) {
		for (int w = 0; w < W; w++) {
			if (!visited[h][w] && board[h][w] == 1) {
				BFS(w, h);
				cnt++;
			}
		}
	}
	cout << cnt << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	while (init()) {
		solve();
	}
	return 0;
}
