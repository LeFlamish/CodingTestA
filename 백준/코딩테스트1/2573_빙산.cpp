#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> CD;
#define X first
#define Y second

int N, M;
int board[300][300];
bool visited[300][300];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
vector<pair<CD, int>> melted;

void init() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> board[y][x];
		}
	}
}

void meltIceberg() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (board[y][x] > 0) {
				int cnt = 0;
				for (int dir = 0; dir < 4; dir++) {
					int nx = x + dx[dir];
					int ny = y + dy[dir];
					if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
					if (board[ny][nx] == 0) cnt++;
				}
				melted.push_back(make_pair(make_pair(x, y), cnt));
			}
		}
	}
	for (auto i : melted) {
		CD target = i.first;
		int amount = i.second;
		board[target.Y][target.X] = max(0, board[target.Y][target.X] - amount);
	}
	melted.clear();
}

void BFS(int x, int y) {
	visited[y][x] = true;
	queue<CD> Q;
	Q.push(make_pair(x, y));
	while (!Q.empty()) {
		CD cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
			if (visited[ny][nx] || board[ny][nx] == 0) continue;
			visited[ny][nx] = true;
			Q.push(make_pair(nx, ny));
		}
	}
}

int checkIceberg() {
	memset(visited, false, sizeof(visited));
	int cnt = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (board[y][x] && !visited[y][x]) {
				cnt++;
				BFS(x, y);
			}
		}
	}
	return cnt;
}

int solve() {
	int flag = 0;
	int t = 0;
	while (1) {
		t++;
		meltIceberg();
		flag = checkIceberg();
		if (flag == 0) return 0;
		else if (flag > 1) return t;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	cout << solve();
	return 0;
}
