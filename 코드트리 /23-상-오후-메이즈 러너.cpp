#include <iostream>
using namespace std;

struct Human {
	int x;
	int y;
	int total;
	bool isOut;
};

struct Square {
	int x;
	int y;
	int side;
};

int N, M, K, ret;
int exitX, exitY;
int board[11][11];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int isHuman[11][11];
bool visited[11];
Human man[11];
Square S;
int tmpMap[11][11];
int exitCnt;

void check() {
	cout << "====================\n";
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (isHuman[y][x]) cout << "H ";
			else cout << board[y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (isHuman[y][x]) cout << "1 ";
			else cout << "0 ";
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	cout << "******************** : " << "출구 : " << exitX << ", " << exitY << '\n';
	cout << "--------------------\n";
	for (int m = 1; m <= M; m++) {
		cout << m << "번 사람 : " << man[m].x << ", " << man[m].y << ' ' << man[m].total << '\n';
		if (man[m].isOut) cout << m << "번 사람 탈출\n";
	}
	cout << "====================\n";
}

bool isArea(int nx, int ny) {
	return !(nx < 1 || nx > N || ny < 1 || ny > N);
}

void init() {
	cin >> N >> M >> K;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> board[y][x];
		}
	}
	for (int m = 1; m <= M; m++) {
		cin >> man[m].y >> man[m].x;
		isHuman[man[m].y][man[m].x]++;
	}
	cin >> exitY >> exitX;
	board[exitY][exitX] = -1;
}

void findSquare() {
	int size = 2;
	while (1) {
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				bool findRunner = false, findExit = false;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						if (x + size - 1 > N || y + size - 1 > N) continue;
						if (exitX == x + j && exitY == y + i) findExit = true;
						if (isHuman[y + i][x + j]) findRunner = true;
					}
				}
				if (findRunner && findExit) {
					S.x = x;
					S.y = y;
					S.side = size;
					//cout << "회전 대상 정사각형\n";
					//cout << "******************** : " << S.x << ' ' << S.y << ' ' << S.side << '\n';
					return;
				}
			}
		}
		size++;
	}
}

void setIsHuman() {
	memset(isHuman, false, sizeof(isHuman));
	for (int m = 1; m <= M; m++) {
		if (man[m].isOut) continue;
		isHuman[man[m].y][man[m].x]++;
	}
}

void rotation() {
	memset(visited, false, sizeof(visited));
	for (int x = 0; x < S.side; x++) {
		for (int y = 0; y < S.side; y++) {
			if (board[S.y + S.side - 1 - y][S.x + x] == -1) tmpMap[x][y] = -1;
			else tmpMap[x][y] = max(board[S.y + S.side - 1 - y][S.x + x] - 1, 0);
			if (isHuman[S.y + S.side - 1 - y][S.x + x]) {
				for (int m = 1; m <= M; m++) {
					if (man[m].x == S.x + x && man[m].y == S.y + S.side - 1 - y && !visited[m]) {
						visited[m] = true;
						isHuman[S.y + S.side - 1 - y][S.x + x]--;
						man[m].x = S.x + y;
						man[m].y = S.y + x;
					}
				}
			}
		}
	}
	for (int y = 0; y < S.side; y++) {
		for (int x = 0; x < S.side; x++) {
			board[S.y + y][S.x + x] = tmpMap[y][x];
			if (board[S.y + y][S.x + x] == -1) {
				exitX = S.x + x;
				exitY = S.y + y;
			}
		}
	}
	setIsHuman();
}

void moveHuman() {
	for (int m = 1; m <= M; m++) {
		if (man[m].isOut) continue;
		int dist = abs(man[m].x - exitX) + abs(man[m].y - exitY);
		int tmpDir = -1;
		for (int dir : {0, 2}) {
			int nx = man[m].x + dx[dir];
			int ny = man[m].y + dy[dir];
			if (!isArea(nx, ny)) continue;
			if (board[ny][nx] > 0) continue;
			if (board[ny][nx] == -1) {
				man[m].total++;
				man[m].isOut = true;
				exitCnt++;
				break;
			}
			int tmp = abs(nx - exitX) + abs(ny - exitY);
			if (dist >= tmp) {
				tmpDir = dir;
				dist = tmp;
			}
		}
		if (tmpDir == -1) {
			for (int dir : {1, 3}) {
				int nx = man[m].x + dx[dir];
				int ny = man[m].y + dy[dir];
				if (!isArea(nx, ny)) continue;
				if (board[ny][nx] > 0) continue;
				if (board[ny][nx] == -1) {
					man[m].total++;
					man[m].isOut = true;
					exitCnt++;
					break;
				}
				int tmp = abs(nx - exitX) + abs(ny - exitY);
				if (dist >= tmp) {
					tmpDir = dir;
					dist = tmp;
				}
			}
		}
		if (tmpDir != -1) {
			man[m].x += dx[tmpDir];
			man[m].y += dy[tmpDir];
			man[m].total++;
		}
	}
	setIsHuman();
}


void solve(int T) {
	for (int t = 1; t <= T; t++) {
		moveHuman();
		//cout << t << "초 사람 이동 후\n";
		//check();
		if (exitCnt == M) break;
		findSquare();
		rotation();
		//cout << t << "초 회전 후\n";
		//check();
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	//cout << "시작 전\n";
	//check();
	solve(K);
	for (int m = 1; m <= M; m++) {
		ret += man[m].total;
	}
	cout << ret << '\n' << exitY << ' ' << exitX;
	return 0;
}
