#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int SIZE = 27;
typedef pair<int, int> CD;
#define X first
#define Y second

int N, cnt;
string board[SIZE];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
bool visited[SIZE][SIZE];
vector<int> BFSanswer;

void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> board[i];
	}
}

int BFS(CD start) {
	cnt = 1;
	visited[start.X][start.Y] = true;
	queue<CD> Q;
	Q.push(start);
	while (!Q.empty()) {
		int cx = Q.front().X;
		int cy = Q.front().Y;
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (visited[nx][ny] || board[nx][ny] == '0') continue;
			visited[nx][ny] = true;
			Q.push({ nx, ny });
			cnt++;
		}
	}
	return cnt;
}

void solve() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] || board[i][j] == '0') continue;
			BFSanswer.push_back(BFS({ i, j }));
		}
	}
	sort(BFSanswer.begin(), BFSanswer.end());
	cout << BFSanswer.size() << '\n';
	for (int i = 0; i < BFSanswer.size(); i++) {
		cout << BFSanswer[i] << '\n';
	}
}

int main(void) {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
