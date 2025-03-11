#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct State {
	int x, y;
};

int T, M, N, K, ret;
int	board[50][50];
bool visited[50][50];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

// 테스트 케이스를 한 번 실행하는 동안 모두 돌리므로 2차원 배열과 변수 초기화 필수.
void init() {
    ret = 0;
    memset(visited, false, sizeof(visited));
    memset(board, 0, sizeof(board));
	cin >> M >> N >> K;
	for (int k = 0; k < K; k++) {
		int x, y;
		cin >> x >> y;
		board[y][x] = 1;
	}
}

// Out Of Bounds
inline bool OOB(int x, int y) {
    return x < 0 || x >= M || y < 0 || y >= N;
}

void BFS(int x, int y) {
    queue<State> Q;
    visited[y][x] = true;
    Q.push({ x, y });
    while (!Q.empty()) {
        State cur = Q.front(); Q.pop();
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            if (OOB(nx, ny)) continue;
            if (visited[ny][nx] || board[ny][nx] == 0) continue;
            visited[ny][nx] = true;
            Q.push({ nx, ny });
        }
    }
}

void solve() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (board[y][x] && !visited[y][x]) { // BFS를 하면 한 덩어리씩 방문 처리가 되므로 끝날 때 마다 한 덩어리가 있는 것으로 판단.
                BFS(x, y);
                ret++;
            }
        }
    }
    cout << ret << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        init();
        solve();
    }
	return 0;
}
