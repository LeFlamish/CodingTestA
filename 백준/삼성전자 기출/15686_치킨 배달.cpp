#include <bits/stdc++.h>
using namespace std;
#define SIZE 51
typedef pair<int, int> CD;
#define X first
#define Y second

int N, M, ans = INT_MAX;
int board[SIZE][SIZE];
int tmp[SIZE][SIZE];
int visited[SIZE][SIZE];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
vector<CD> chicken;
CD selected[13];

void init() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			if (board[y][x] == 2) chicken.push_back({ x, y });
		}
	}
}

void copyBoard() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (board[y][x] == 2) tmp[y][x] = 0;
			else tmp[y][x] = board[y][x];
		}
	}
}

int getScore() {
	int ret = 0;
	queue<CD> Q;
	for (int i = 0; i < M; i++) {
		visited[selected[i].Y][selected[i].X] = 0;
		Q.push({ selected[i].X, selected[i].Y });
	}
	while (!Q.empty()) {
		CD cur = Q.front(); Q.pop();
		if (tmp[cur.Y][cur.X] == 1) ret += visited[cur.Y][cur.X];
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (visited[ny][nx] != -1) continue;
			visited[ny][nx] = visited[cur.Y][cur.X] + 1;
			Q.push({ nx, ny });
		}
	}
	return ret;
}

void solve(int cnt, int k) {
	if (cnt == M) {
		copyBoard();
		for (int i = 0; i < M; i++) {
			tmp[selected[i].Y][selected[i].X] = 2;
		}
		memset(visited, -1, sizeof(visited));
		ans = min(ans, getScore());
	}

	for (int i = k; i < chicken.size(); i++) {
		selected[cnt] = chicken[i];
		solve(cnt + 1, i + 1);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve(0, 0);
	cout << ans;
	return 0;
}
