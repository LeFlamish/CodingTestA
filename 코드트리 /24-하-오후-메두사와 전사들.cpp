#include <iostream>
#include <queue>
#include <stack>
#include <cmath> // abs
#include <cstring> // memset
#include <iomanip> // setw
using namespace std;

// 2차원 좌표에 대한 기본 정의
typedef pair<int, int> PI;
#define X first
#define Y second

// 메두사의 이동 경로를 추적하기 위해 필요한 구조체
struct Path {
	int x, y;
	bool isVisit;
};

// 객체로써의 메두사 구조체
struct Medusa {
	int x, y, dir;
	bool isArrived;
};

// 메두사의 시야에 대한 구조체
struct Sight {
	int x, y, dx, dy;
};

// 객체로써의 전사 구조체
struct Warrior {
	int x, y, d;
	bool isDie, isStone;
};

int N, M, totalD, stone, attacker; // N, M, 모든 전사가 이동한 거리의 합, 메두사로 인해 돌이 된 전사의 수, 메두사를 공격한 전사의 수
int board[50][50]; // board
int cnt[4][50][50]; // 메두사가 바라보는 네 방향에 대해서 보이는 전사, 메두사의 시야 영역, 전사에 의해 가려지는 영역을 저장
Path path[50][50]; // 메두사의 최단 이동 경로를 얻기 위해 Path 구조체의 2차원 배열
PI S, E; // 메두사의 집, 공원
Medusa MDS; // 메두사 객체
Warrior W[300]; // 전사 객체들
int dx[] = { 0, 0, -1, 1 }; // 우선 순위는
int dy[] = { -1, 1, 0, 0 }; // 상, 하, 좌, 우
stack<PI> Road; // 도착 지점에서 출발 지점까지 돌아오면서 최단 경로 각각의 좌표를 역순으로 담기 위해서

// 매 턴마다 보드 등의 상태를 출력해보며 디버깅
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
// 단순 BFS. 다음 좌표가 목적지라면 true를 반환한다.
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

// 최단 경로가 존재한다면, 도착 지점(E)에서부터 저장된 좌표(현재 좌표에 도달하기 직전, 어디서 왔는지)를 Stack에 Push.
// Stack의 특성 상, 도착 지점에서부터 좌표를 Push하면 마지막에 Pop되는 순서는 결국 출발 지점부터 시작하게 된다.
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

// 메두사가 이동한 칸에 전사가 있는 경우를 처리한다.
inline void dieWarrior() {
	for (int m = 0; m < M; m++) {
		if (MDS.x == W[m].x && MDS.y == W[m].y) W[m].isDie = true;
	}
}

// 메두사의 이동을 처리한다.
// 단순히 Stack에서 Pop한 좌표가 메두사의 다음 이동 칸이다.
void moveMedusa() {
	PI next = Road.top(); Road.pop();
	MDS.x = next.X; MDS.y = next.Y;
	dieWarrior();
}

// 메두사의 시선에 따라 가려지는 영역의 경계를 표시(처리)한다.
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

// 메두사의 시선을 처리한다.
// 4방향을 보는 경우를 모두 따져보고 counting(돌이 되는 전사의 수)가 가장 많은 dir(방향)을 Medusa 객체에 저장한다.
// 또한 방향이 다르면 돌이 되는 전사, 가려지는 시야 영역이 모두 다르기 때문에 cnt배열 4개를 만들어둔다.
// 전사가 돌이 되는 것과 시야가 가려지는 것은 단순히 2차원 배열 위에 전사가 있는지 없는지가 중요하기 때문에 cnt의 각 위치에 몇 명이 있는지로 기록.
// 즉, 돌이 되는 건 따로 처리하는 것이 편하다.
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

// 돌이 되는 전사를 처리한다.
void makeStone() {
	for (int m = 0; m < M; m++) {
		if (cnt[MDS.dir][W[m].y][W[m].x] == -2) W[m].isStone = true;
	}
}

// 좌표를 입력 받아 메두사와의 맨해튼 거리를 반환한다.
inline int distance(int x, int y) {
	return abs(MDS.x - x) + abs(MDS.y - y);
}

// 전사가 메두사를 공격하고 사라지는 것을 처리한다.
void attackMedusa(int m) {
	attacker++;
	W[m].isDie = true;
}

// 전사의 이동을 처리한다.
// 주의할 점은 첫 번째 이동과 두 번째 이동의 우선 순위가 다르다. 방향 회전과 마찬가지로 % 연산을 통해서 수행한다.
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

// 돌이 된 전사들은 다음 턴이 되면 돌에서 풀려나는 것을 처리한다.
inline void resetStone() {
	for (int m = 0; m < M; m++) {
		W[m].isStone = false;
	}
}

// 전체적으로 한 턴 씩 수행한다.
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
