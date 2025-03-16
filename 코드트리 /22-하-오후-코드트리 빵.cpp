#include <iostream>
#include <queue>
#include <cmath>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

struct State {
	int x, y; // x : 행, y : 열
};

struct Human {
	State cur;
	bool isArrive;
};

// Basecamp와 Store을 따로 구조체로 만들어서 객체로 만드는 풀이도 존재.

int N, M, cntBC;
int board[16][16];
int dist[16][16];
int visited[16][16];
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };
Human human[31];
State store[31];

void debug() {
	cout << "====================\n";
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			cout << board[x][y] << ' ';
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	for (int i = 1; i <= M; i++) cout << human[i].cur.x << ' ' << human[i].cur.y << '\n';
	cout << "====================\n";
}

void init() {
	cin >> N >> M;
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			cin >> board[x][y];
		}
	}
	for (int m = 1; m <= M; m++) {
		int x, y;
		cin >> x >> y;
		store[m] = { x, y };
	}
}

inline bool OOB(int x, int y) {
	return x < 1 || x > N || y < 1 || y > N;
}

int findDirection(int t) {
	memset(dist, 0, sizeof(dist));
	queue<State> Q;
	dist[store[t].x][store[t].y] = 1;
	Q.push(store[t]);
	while (!Q.empty()) {
		State cur = Q.front(); Q.pop();
		if (cur.x == human[t].cur.x && cur.y == human[t].cur.y) break;
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (dist[nx][ny] || board[nx][ny] == 2) continue;
			dist[nx][ny] = dist[cur.x][cur.y] + 1;
			Q.push({ nx, ny });
		}
	}
	int ret, Min = INT_MAX;
	for (int dir = 0; dir < 4; dir++) {
		int nx = human[t].cur.x + dx[dir];
		int ny = human[t].cur.y + dy[dir];
		if (OOB(nx, ny)) continue;
		if (dist[nx][ny] && Min > dist[nx][ny]) {
			ret = dir;
			Min = dist[nx][ny];
		}
	}
	return ret;
}

void moveHuman(int t) {
	for (int i = 1; i < min(t, M + 1); i++) {
		if (human[i].isArrive) continue;
		int dir = findDirection(i);
		human[i].cur.x += dx[dir];
		human[i].cur.y += dy[dir];
		if (human[i].cur.x == store[i].x && human[i].cur.y == store[i].y) human[i].isArrive = true;
	}
}

inline void arriveCheck(int t) {
	for (int i = 1; i < min(t, M + 1); i++) if (human[i].isArrive) board[human[i].cur.x][human[i].cur.y] = 2;
}

void findNearest(int t) {
	memset(visited, false, sizeof(visited));
	int flag = 0;
	queue<State> Q;
	vector<State> candidate;
	visited[store[t].x][store[t].y] = 1;
	Q.push(store[t]);
	while (!Q.empty()) {
		State cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[nx][ny] || board[nx][ny] == 2) continue;
			visited[nx][ny] = visited[cur.x][cur.y] + 1;
			if (board[nx][ny] == 1) {
				if (!flag) {
					candidate.push_back({ nx, ny });
					flag = visited[nx][ny];
				}
				else {
					if (visited[nx][ny] <= flag) candidate.push_back({ nx, ny });
				}
			}
			if (flag) continue;
			Q.push({ nx, ny });
 		}
	}
	int bestX = candidate[0].x, bestY = candidate[0].y;
	for (int i = 1; i < candidate.size(); i++) {
		if (bestX > candidate[i].x) bestX = candidate[i].x, bestY = candidate[i].y;
		else if (bestX == candidate[i].x) {
			if (bestY > candidate[i].y) bestX = candidate[i].x, bestY = candidate[i].y;
		}
	}
	human[t].cur = { bestX, bestY };
}

inline void enterBasecamp(int t) {
	if (t > M) return;
	findNearest(t);
	board[human[t].cur.x][human[t].cur.y] = 2;
}

inline bool isEnd() {
	for (int i = 1; i <= M; i++) if (!human[i].isArrive) return false;
	return true;
}

void solve() {
	int t = 1;
	while (1) {
		moveHuman(t);
		arriveCheck(t);
		enterBasecamp(t);
		//debug();
		if (isEnd()) break;;
		t++;
	}
	cout << t;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
