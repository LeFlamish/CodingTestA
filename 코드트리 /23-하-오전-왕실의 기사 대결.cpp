#include <iostream>
#include <iomanip> // setw
#include <queue>
using namespace std;

struct Knight {
	int x;
	int y;
	int h;
	int w;
	int k;
};

int L, N, Q, ret;
int board[2][41][41];
int origin[31];
Knight knight[31];
int order[100][2];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
queue<pair<int, int>> seq;
bool isMove;
bool visited[31];

void check(int q) {
	cout << "====================\n";
	cout << q + 1 << "번 째 명령 : " << order[q][0] << "번 째 기사를 ";
	if (order[q][1] == 0) cout << "위쪽";
	else if (order[q][1] == 1) cout << "오른쪽";
	else if (order[q][1] == 2) cout << "아래쪽";
	else cout << "왼쪽";
	cout << "으로 이동시킨 후\n";
	cout << "--------------------\n";
	for (int y = 1; y <= L; y++) {
		for (int x = 1; x <= L; x++) {
			if (board[0][y][x] == 2) {
				cout << " 벽";
				continue;
			}
			cout << setw(2) << board[1][y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	cout << "기사들 체력\n";
	for (int n = 1; n <= N; n++) {
		cout << n << "번 째 기사 남은 체력 : " << knight[n].k << '\n';
	}
	cout << "====================\n";
}

void init() {
	cin >> L >> N >> Q;
	for (int y = 1; y <= L; y++) {
		for (int x = 1; x <= L; x++) {
			cin >> board[0][y][x];
		}
	}
	for (int n = 1; n <= N; n++) {
		cin >> knight[n].y >> knight[n].x >> knight[n].h >> knight[n].w >> knight[n].k;
		origin[n] = knight[n].k;
		for (int y = 0; y < knight[n].h; y++) {
			for (int x = 0; x < knight[n].w; x++) {
				board[1][knight[n].y + y][knight[n].x + x] = n;
			}
		}
	}
	for (int q = 0; q < Q; q++) {
		cin >> order[q][0] >> order[q][1];
	}
}

bool canMove(int nx, int ny) {
	if (nx < 1 || nx > L || ny < 1 || ny > L) return false;
	if (board[0][ny][nx] == 2) return false;
	return true;
}

bool interaction(int nx, int ny, int dir) {
	bool flag = false;
	int knightNum = board[1][ny][nx];
	Knight tmp = knight[knightNum];
	for (int y = 0; y < tmp.h; y++) {
		for (int x = 0; x < tmp.w; x++) {
			int nx = tmp.x + x + dx[dir];
			int ny = tmp.y + y + dy[dir];
			if (!canMove(nx, ny)) {
				isMove = false;
				return false;
			}
			if (board[1][ny][nx] > 0 && board[1][ny][nx] != knightNum) {
				if (!interaction(nx, ny, dir)) flag = true;
			}
		}
	}
	if (flag) {
		isMove = false;
		return false;
	}
	if (!visited[knightNum]) {
		visited[knightNum] = true;
		seq.push({ knightNum, dir });
	}
	return true;
}

void move(int k) {
	bool flag = false;
	int knightNum = order[k][0];
	int knightDir = order[k][1];
	Knight tmp = knight[knightNum];
	for (int y = 0; y < tmp.h; y++) {
		for (int x = 0; x < tmp.w; x++) {
			int nx = tmp.x + x + dx[knightDir];
			int ny = tmp.y + y + dy[knightDir];
			if (!canMove(nx, ny)) {
				isMove = false;
				return;
			}
			if (board[1][ny][nx] > 0 && board[1][ny][nx] != knightNum) {
				if (!interaction(nx, ny, knightDir)) flag = true;
			}
		}
	}
	if (flag) {
		isMove = false;
		return;
	}
	if (!visited[knightNum]) {
		visited[knightNum] = true;
		seq.push({ knightNum, knightDir });
	}
}

void solve() {
	//check(-1);
	for (int q = 0; q < Q; q++) {
		memset(visited, false, sizeof(visited));
		if (knight[order[q][0]].k <= 0) continue;
		isMove = true;
		move(q);
		if (isMove) {
			while (!seq.empty()) {
				int knightNum = seq.front().first;
				int dir = seq.front().second;
				seq.pop();
				for (int y = 0; y < knight[knightNum].h; y++) {
					for (int x = 0; x < knight[knightNum].w; x++) {
						board[1][knight[knightNum].y + y][knight[knightNum].x + x] = 0;
					}
				}
				knight[knightNum].x += dx[dir];
				knight[knightNum].y += dy[dir];
				int damage = 0;
				for (int y = 0; y < knight[knightNum].h; y++) {
					for (int x = 0; x < knight[knightNum].w; x++) {
						board[1][knight[knightNum].y + y][knight[knightNum].x + x] = knightNum;
						if (board[0][knight[knightNum].y + y][knight[knightNum].x + x] == 1) damage++;
					}
				}
				if (knightNum == order[q][0]) continue;
				knight[knightNum].k -= damage;
				if (knight[knightNum].k <= 0) {
					for (int y = 0; y < knight[knightNum].h; y++) {
						for (int x = 0; x < knight[knightNum].w; x++) {
							board[1][knight[knightNum].y + y][knight[knightNum].x + x] = 0;
						}
					}
				}
			}
		}
		while (!seq.empty()) {
			seq.pop();
		}
		//check(q);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	for (int n = 1; n <= N; n++) {
		if (knight[n].k > 0) ret += origin[n] - knight[n].k;
	}
	cout << ret;
	return 0;
}
