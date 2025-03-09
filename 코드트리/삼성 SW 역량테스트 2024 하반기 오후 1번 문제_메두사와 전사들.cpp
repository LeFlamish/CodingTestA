#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>
#include <iomanip>
using namespace std;
typedef pair<int, int> PI;
#define X first
#define Y second
struct Path {
	int x, y;
	bool isVisit;
};
struct Medusa {
	int x, y, dir;
	bool isArrived;
};
struct Sight {
	int x, y, dx, dy;
};
struct Warrior {
	int x, y, d;
	bool isDie, isStone;
};

int N, M, stone, attacker, totalD;
int board[50][50];
int cnt[4][50][50];
Path path[50][50];
PI S, E;
Medusa MDS;
Warrior W[300];
int dx[] = { 0, 0, -1, 1 }; // 우선 순위는
int dy[] = { -1, 1, 0, 0 }; // 상, 하, 좌, 우
stack<PI> Road;

void check(int dir) {
	cout << "====================\n";
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			bool flag = false;
			if (MDS.x == x && MDS.y == y) {
				cout << " M ";
				flag = true;
				continue;
			}
			for (int m = 0; m < M; m++) {
				if (W[m].x == x && W[m].y == y && !W[m].isDie) {
					cout << " W ";
					flag = true;
					break;
				}
			}
			if (!flag) cout << setw(2) << cnt[dir][y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	cout << totalD << ' ' << stone << ' ' << attacker << '\n';
	cout << "====================\n";
}

// 초기화 함수
void init() {
	cin >> N >> M;
	cin >> S.Y >> S.X >> E.Y >> E.X;
	MDS.x = S.X; MDS.y = S.Y;
	for (int m = 0; m < M; m++) {
		cin >> W[m].y >> W[m].x;
	}
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
		}
	}
}

// OutOfBounds
inline bool OOB(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= N;
}

// 메두사가 공원으로 가는 최단 경로를 찾아낸다. 공원에 도착할 수 없다면 false를 반환한다.
bool findMedusaRoad() {
	queue<Path> Q;
	path[S.Y][S.X] = { S.X, S.Y, true };
	Q.push(path[S.Y][S.X]);
	while (!Q.empty()) {
		Path cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (path[ny][nx].isVisit || board[ny][nx]) continue;
			path[ny][nx] = { cur.x, cur.y, true };
			if (E.X == nx && E.Y == ny) return true;
			Q.push({ nx, ny });
		}
	}
	return false;
}

void makeMedusaRoad() {
	queue<PI> Q;
	Q.push(E);
	while (!Q.empty()) {
		PI cur = Q.front(); Q.pop();
		Road.push(cur);
		if (path[cur.Y][cur.X].x == S.X && path[cur.Y][cur.X].y == S.Y) break;
		Q.push({ path[cur.Y][cur.X].x, path[cur.Y][cur.X].y });
	}
}

inline void dieWarrior() {
	for (int m = 0; m < M; m++) {
		if (MDS.x == W[m].x && MDS.y == W[m].y) W[m].isDie = true;
	}
}

void moveMedusa() {
	PI next = Road.top(); Road.pop();
	MDS.x = next.X; MDS.y = next.Y;
	dieWarrior();
}

void shadow(Sight sight, int dir) {
	queue<PI> Q;
	if (sight.dx != 0 && sight.dy != 0) {
		int nx = sight.x, ny = sight.y;
		while (1) {
			nx += sight.dx, ny += sight.dy;
			if (OOB(nx, ny)) break;
			Q.push({ nx, ny });
		}
	}
	while (!Q.empty()) {
		PI cur = Q.front(); Q.pop();
		cnt[dir][cur.Y][cur.X] = -1;
	}
}

void lookMedusa() {
	memset(cnt, 0, sizeof(cnt));
	for (int m = 0; m < M; m++) {
		if (W[m].isDie) continue;
		for (int i = 0; i < 4; i++) {
			cnt[i][W[m].y][W[m].x]++;
		}
	}
	int counting;
	queue<Sight> Q;
	for (int dir = 0; dir < 4; dir++) {
		counting = 0;
		// 메두사의 시야 경계선들을 모두 Q에 추가
		Q.push({ MDS.x, MDS.y, 0, 0 });
		int nx = MDS.x, ny = MDS.y;
		if (dx[dir] == 0) {
			while (1) {
				nx++, ny += dy[dir];
				if (OOB(nx, ny)) break;
				Q.push({ nx, ny, 1, dy[dir] });
			}
			nx = MDS.x, ny = MDS.y;
			while (1) {
				nx--; ny += dy[dir];
				if (OOB(nx, ny)) break;
				Q.push({ nx, ny, -1, dy[dir] });
			}
		}
		else {
			while (1) {
				nx += dx[dir], ny++;
				if (OOB(nx, ny)) break;
				Q.push({ nx, ny, dx[dir], 1 });
			}
			nx = MDS.x, ny = MDS.y;
			while (1) {
				nx += dx[dir], ny--;
				if (OOB(nx, ny)) break;
				Q.push({ nx, ny, dx[dir], -1 });
			}
		}

		// 메두사 시야 처리
		while (!Q.empty()) {
			Sight cur = Q.front(); Q.pop();
			int nx = cur.x, ny = cur.y;
			if (cnt[dir][ny][nx] > 0) {
				counting += cnt[dir][ny][nx];
				shadow({ nx, ny, cur.dx, cur.dy }, dir);
				cnt[dir][ny][nx] = -2;
				continue;
			}
			if (cnt[dir][ny][nx] == -1) continue;
			cnt[dir][ny][nx] = -2;
			while (1) {
				if (OOB(nx, ny)) break;
				if (cnt[dir][ny][nx] > 0) {
					counting += cnt[dir][ny][nx];
					shadow({ nx, ny, cur.dx, cur.dy }, dir);
					cnt[dir][ny][nx] = -2;
					break;
				}
				else if (cnt[dir][ny][nx] == -1) break;
				cnt[dir][ny][nx] = -2;
				nx += dx[dir], ny += dy[dir];
			}
		}
		cnt[dir][MDS.y][MDS.x] = 0;
		if (counting > stone) {
			stone = counting;
			MDS.dir = dir;
		}
	}
}

void makeStone() {
	for (int m = 0; m < M; m++) {
		if (cnt[MDS.dir][W[m].y][W[m].x] == -2) W[m].isStone = true;
	}
}

inline int distance(int x, int y) {
	return abs(MDS.x - x) + abs(MDS.y - y);
}

void attackMedusa(int m) {
	attacker++;
	W[m].isDie = true;
}

void moveWarrior() {
	for (int m = 0; m < M; m++) {
		if (W[m].isStone || W[m].isDie) continue;
		int cx = W[m].x, cy = W[m].y;
		for (int i = 0; i < 2; i++) {
			int bestX = cx, bestY = cy, curD = distance(cx, cy);
			for (int dir = 0; dir < 4; dir++) {
				int nx = cx + dx[dir], ny = cy + dy[dir];
				if (i) {
					nx = cx + dx[(dir + 2) % 4], ny = cy + dy[(dir + 2) % 4];
				}
				if (OOB(nx, ny) || cnt[MDS.dir][ny][nx] == -2) continue;
				if (distance(nx, ny) < curD) {
					curD = distance(nx, ny);
					bestX = nx, bestY = ny;
				}
			}
			if (bestX == cx && bestY == cy) break;
			cx = bestX, cy = bestY;
			totalD++;
			if (cx == MDS.x && cy == MDS.y) {
				attackMedusa(m);
				break;
			}
		}
		W[m].x = cx, W[m].y = cy;
	}
}

inline void resetStone() {
	for (int m = 0; m < M; m++) {
		W[m].isStone = false;
	}
}

void solve() {
	if (findMedusaRoad()) makeMedusaRoad();
	else {
		cout << -1;
		return;
	}
	while (1) {
		totalD = stone = attacker = 0;
		moveMedusa();
		if (Road.empty()) break;
		lookMedusa();
		makeStone();
		moveWarrior();
		resetStone();
		//check(MDS.dir);
		cout << totalD << ' ' << stone << ' ' << attacker << '\n';
	}
	cout << 0;
	return;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
