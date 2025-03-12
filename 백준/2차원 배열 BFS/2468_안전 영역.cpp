/*
안전 영역의 최대 개수를 구하라고 했기 때문에 알 수 있는 사실이 하나 있다.
변수(variable)가 존재한다는 것. 왜냐하면 최대 개수를 구하라는 것 자체가 여러 개의 개수 중에서 그 중에 최대를 구하라는 것이기 때문.
즉, 이 문제에서 변수가 무엇인지 찾아야한다.
2차원 배열에서 각 좌표의 높이는 변수가 아니므로 잘 생각해보면 물의 높이(비의 양)가 변수임을 알 수 있다.
따라서 물의 높이를 0부터 최대 높이까지 바꿔가면서 각각 진행해보고 최댓값을 구해야함을 알 수 있다.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
struct State {
	int x, y;
};

int N, Max, ret;
int board[100][100];
bool visited[100][100];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void init() {
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			Max = max(Max, board[y][x]); // 물의 높이를 0부터 100까지 돌리는 것이 아니라 실제 2차원 배열에 들어있는 최댓값까지만 돌리기 위해.
		}
	}
}

inline bool OOB(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= N;
}

void BFS(int x, int y, int h) {
	queue<State> Q;
	visited[y][x] = true;
	Q.push({ x, y });
	while (!Q.empty()) {
		State cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || board[ny][nx] <= h) continue;
			visited[ny][nx] = true;
			Q.push({ nx, ny });
		}
	}
}

void solve() {
	for (int h = 0; h <= Max; h++) {
		int cnt = 0;
		memset(visited, false, sizeof(visited));
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (!visited[y][x] && board[y][x] > h) {
					BFS(x, y, h);
					cnt++;
				}
			}
		}
		ret = max(ret, cnt);
	}
	cout << ret;
}

int main(void) {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
