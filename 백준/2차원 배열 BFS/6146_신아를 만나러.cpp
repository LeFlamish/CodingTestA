#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> PI; // 구조체 추천
#define X first
#define Y second
#define FOR(i, N) for (int i = 0; i < N; i++) // for문 축약형

PI T;
int N;
int board[1001][1001]; // -500 ~ 500이므로 500을 0으로 설정하는 것이 자명함.
int visited[1001][1001];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

// 초기화 함수
void init() {
	cin >> T.X >> T.Y >> N;
	T.X += 500; T.Y += 500;
	FOR(i, N) {
		int x, y;
		cin >> x >> y;
		board[500 + y][500 + x] = 1;
	}
}

// Out Of Bounds
inline bool area(int x, int y) {
	return (x < 0 || x >= 1001 || y < 0 || y >= 1001);
}

int BFS() { // 시작 지점이 정해져있기 때문에 매개변수 필요없음.
	queue<PI> Q;
	visited[500][500] = 1;
	Q.push({ 500, 500 });
	while (!Q.empty()) {
		PI cur = Q.front(); Q.pop();
		if (cur == T) return visited[cur.Y][cur.X] - 1;

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (area(nx, ny)) continue;
			if (visited[ny][nx] || board[ny][nx]) continue;
			visited[ny][nx] = visited[cur.Y][cur.X] + 1;
			Q.push({ nx, ny });
		}
	}
	return -1;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	cout << BFS();
	return 0;
}
