#include <iostream>
#include <queue>
using namespace std;
#define SIZE 74
typedef pair<int, int> CD;
#define X first
#define Y second
struct Golem {
	int centerX;
	int centerY = 1;
	int out;
};

int R, C, K, ret;
int board[SIZE][SIZE];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
bool visited[SIZE][SIZE];
Golem golems[1001];

void check() {
	cout << "====================\n";
	for (int r = 0; r <= R; r++) {
		if (r == 3) cout << "--------------------\n";
		for (int c = 1; c <= C; c++) {
			cout << board[r][c] << ' ';
		}
		cout << '\n';
	}
	cout << "====================\n";
}

void init() {
	cin >> R >> C >> K;
	for (int k = 1; k <= K; k++) {
		cin >> golems[k].centerX >> golems[k].out;
	}
	R += 2;
}

bool canDown(Golem& G) {
	if (G.centerY + 2 > R) return false;
	if (board[G.centerY + 1][G.centerX - 1] || board[G.centerY + 1][G.centerX + 1] || board[G.centerY + 2][G.centerX]) return false;
	return true;
}

void moveDown(Golem& G) {
	for (int dir = 0; dir < 4; dir++) {
		int nx = G.centerX + dx[dir];
		int ny = G.centerY + dy[dir];
		if (nx < 1 || nx > C || ny < 0 || ny > R) continue;
		board[ny][nx] = 0;
	}
	G.centerY++;
	board[G.centerY][G.centerX] = 3;
	for (int dir = 0; dir < 4; dir++) {
		int nx = G.centerX + dx[dir];
		int ny = G.centerY + dy[dir];
		if (nx < 1 || nx > C || ny < 1 || ny > R) continue;
		board[ny][nx] = 1;
	}
	board[G.centerY + dy[G.out]][G.centerX + dx[G.out]] = 2;
}

bool canLeft(Golem& G) {
	if (G.centerY + 2 > R || G.centerX <= 2) return false;
	if (board[G.centerY][G.centerX - 2] || board[G.centerY - 1][G.centerX - 1] || board[G.centerY + 1][G.centerX - 1] || board[G.centerY + 1][G.centerX - 2] || board[G.centerY + 2][G.centerX - 1]) return false;
	return true;
}

void moveLeft(Golem& G) {
	board[G.centerY][G.centerX] = 0;
	for (int dir = 0; dir < 4; dir++) {
		int nx = G.centerX + dx[dir];
		int ny = G.centerY + dy[dir];
		if (nx < 1 || nx > C || ny < 0 || ny > R) continue;
		board[ny][nx] = 0;
	}
	G.centerY++;
	G.centerX--;
	board[G.centerY][G.centerX] = 3;
	for (int dir = 0; dir < 4; dir++) {
		int nx = G.centerX + dx[dir];
		int ny = G.centerY + dy[dir];
		if (nx < 1 || nx > C || ny < 1 || ny > R) continue;
		board[ny][nx] = 1;
	}
	G.out = (G.out + 3) % 4;
	board[G.centerY + dy[G.out]][G.centerX + dx[G.out]] = 2;
}

bool canRight(Golem& G) {
	if (G.centerY + 2 > R || G.centerX + 1 >= C) return false;
	if (board[G.centerY][G.centerX + 2] || board[G.centerY - 1][G.centerX + 1] || board[G.centerY + 1][G.centerX + 1] || board[G.centerY + 1][G.centerX + 2] || board[G.centerY + 2][G.centerX + 1]) return false;
	return true;
}

void moveRight(Golem& G) {
	board[G.centerY][G.centerX] = 0;
	for (int dir = 0; dir < 4; dir++) {
		int nx = G.centerX + dx[dir];
		int ny = G.centerY + dy[dir];
		if (nx < 1 || nx > C || ny < 0 || ny > R) continue;
		board[ny][nx] = 0;
	}
	G.centerY++;
	G.centerX++;
	board[G.centerY][G.centerX] = 3;
	for (int dir = 0; dir < 4; dir++) {
		int nx = G.centerX + dx[dir];
		int ny = G.centerY + dy[dir];
		if (nx < 1 || nx > C || ny < 1 || ny > R) continue;
		board[ny][nx] = 1;
	}
	G.out = (G.out + 1) % 4;
	board[G.centerY + dy[G.out]][G.centerX + dx[G.out]] = 2;
}

bool clearBoard() {
	for (int r = 0; r < 4; r++) {
		for (int c = 1; c <= C; c++) {
			if (board[r][c] == 3) {
				memset(board, 0, sizeof(board));
				return true;
			}
		}
	}
	return false;
}

int getScore(Golem G) {
	memset(visited, false, sizeof(visited));
	queue<CD> Q;
	visited[G.centerY][G.centerX] = true;
	Q.push({ G.centerX, G.centerY });
	while (!Q.empty()) {
		CD cur = Q.front(); Q.pop();
		int value = board[cur.Y][cur.X];
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 1 || nx > C || ny < 1 || ny > R) continue;
			if (board[ny][nx] == 0 || visited[ny][nx]) continue;
			if (value == 1 && board[ny][nx] != 3) continue;
			visited[ny][nx] = true;
			Q.push({ nx, ny });
		}
	}
	for (int r = R; r >= 1; r--) {
		for (int c = 1; c <= C; c++) {
			if (visited[r][c]) return r - 2;
		}
	}
}

void solve(int k) {
	board[golems[k].centerY][golems[k].centerX] = 3;
	for (int dir = 0; dir < 4; dir++) {
		int nx = golems[k].centerX + dx[dir];
		int ny = golems[k].centerY + dy[dir];
		if (nx < 1 || nx > C || ny < 0 || ny > R) continue;
		board[ny][nx] = 1;
	}
	board[golems[k].centerY + dy[golems[k].out]][golems[k].centerX + dx[golems[k].out]] = 2;
	//check();
	while (1) {
		if (canDown(golems[k])) {
			moveDown(golems[k]);
		}
		else {
			if (canLeft(golems[k])) {
				moveLeft(golems[k]);
			}
			else {
				if (canRight(golems[k])) {
					moveRight(golems[k]);
				}
				else {
					break;
				}
			}
		}
		//check();
	}
	if (!clearBoard()) {
		ret += getScore(golems[k]);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	for (int k = 1; k <= K; k++) {
		solve(k);
	}
	cout << ret;
	return 0;
}
