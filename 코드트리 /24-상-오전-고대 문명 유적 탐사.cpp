#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> CD;
#define X first
#define Y second

int K, M, ret;
int board[5][5];
int tmp[5][5];
int candidate[5][5];
bool visited[5][5];
int item[300];
int curItem;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int rotationDx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int rotationDy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
vector<CD> V;

void check() {
	cout << "====================\n";
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			cout << board[y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "====================\n";
}

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.X == b.X) {
		return a.Y > b.Y;
	}
	return a.X < b.X;
}

void init() {
	cin >> K >> M;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			cin >> board[y][x];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> item[i];
	}
}

bool isArea(int x, int y) {
	if (x < 0 || x >= 5 || y < 0 || y >= 5) return false;
	return true;
}

void copyBoard() {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			tmp[y][x] = board[y][x];
		}
	}
}

void rotateTmp(int x, int y) {
	int temp[3][3];
	temp[1][1] = tmp[y][x];
	for (int dir = 0; dir < 8; dir++) {
		int fromX = x + rotationDx[dir];
		int fromY = y + rotationDy[dir];
		int toX = 1 + rotationDx[(dir + 2) % 8];
		int toY = 1 + rotationDy[(dir + 2) % 8];
		temp[toY][toX] = tmp[fromY][fromX];
	}
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			tmp[y + i][x + j] = temp[i + 1][j + 1];
		}
	}
}

void rotateBoard(int x, int y, int angle) {
	int temp[3][3];
	for (int i = 0; i < angle; i++) {
		temp[1][1] = board[y][x];
		for (int dir = 0; dir < 8; dir++) {
			int fromX = x + rotationDx[dir];
			int fromY = y + rotationDy[dir];
			int toX = 1 + rotationDx[(dir + 2) % 8];
			int toY = 1 + rotationDy[(dir + 2) % 8];
			temp[toY][toX] = board[fromY][fromX];
		}
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				board[y + i][x + j] = temp[i + 1][j + 1];
			}
		}
	}
}

int getTmpScore() {
	int score = 0;
	memset(visited, false, sizeof(visited));
	queue<CD> Q;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			int cnt = 0;
			visited[y][x] = true;
			Q.push({ x, y });
			while (!Q.empty()) {
				CD cur = Q.front(); Q.pop();
				cnt++;
				for (int dir = 0; dir < 4; dir++) {
					int nx = cur.X + dx[dir];
					int ny = cur.Y + dy[dir];
					if (!isArea(nx, ny)) continue;
					if (visited[ny][nx] || tmp[ny][nx] != tmp[y][x]) continue;
					visited[ny][nx] = true;
					Q.push({ nx, ny });
				}
			}
			if (cnt >= 3) score += cnt;
		}
	}
	return score;
}

int getBoardScore() {
	int score = 0;
	memset(visited, false, sizeof(visited));
	V.clear();
	queue<CD> Q;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (visited[y][x]) continue;
			int cnt = 0;
			visited[y][x] = true;
			Q.push({ x, y });
			while (!Q.empty()) {
				CD cur = Q.front(); Q.pop();
				cnt++;
				V.push_back({ cur.X, cur.Y });
				for (int dir = 0; dir < 4; dir++) {
					int nx = cur.X + dx[dir];
					int ny = cur.Y + dy[dir];
					if (!isArea(nx, ny)) continue;
					if (visited[ny][nx] || board[ny][nx] != board[y][x]) continue;
					visited[ny][nx] = true;
					Q.push({ nx, ny });
				}
			}
			if (cnt >= 3) score += cnt;
			else {
				for (int i = 0; i < cnt; i++) {
					V.pop_back();
				}
			}
		}
	}
	sort(V.begin(), V.end(), compare);
	for (int i = 0; i < V.size(); i++) {
		board[V[i].Y][V[i].X] = item[curItem];
		curItem = (curItem + 1) % M;
	}
	return score;
}

pair<int, pair<int, int>> findCenter() {
	CD center = { 5, 5 };
	int Max = 0;
	int MaxAngle = 0;

	for (int y = 1; y < 4; y++) {
		for (int x = 1; x < 4; x++) {
			copyBoard();
			for (int angle = 1; angle <= 3; angle++) {
				rotateTmp(x, y);
				int score = getTmpScore();
				if (Max < score) {
					Max = score;
					center = { x, y };
					MaxAngle = angle;
				}
				else if (Max == score) {
					if (MaxAngle > angle) {
						Max = score;
						center = { x, y };
						MaxAngle = angle;
					}
					else if (MaxAngle == angle) {
						if (center.X > x) {
							Max = score;
							center = { x, y };
							MaxAngle = angle;
						}
						else if (center.X == x) {
							if (center.Y > y) {
								Max = score;
								center = { x, y };
								MaxAngle = angle;
							}
						}
					}
				}
			}
		}
	}
	if (Max == 0) {
		return { -1, {-1, -1} };
	}
	return { MaxAngle, center };
}

void solve(int k) {
	for (int i = 0; i < k; i++) {
		ret = 0;
		pair<int, pair<int, int>> info = findCenter();
		int angle = info.first;
		if (angle == -1) break;
		CD center = info.second;
		rotateBoard(center.X, center.Y, angle);
		//check();
		while (1) {
			int score = getBoardScore();
			//check();
			if (score == 0) break;
			ret += score;
		}
		cout << ret << ' ';
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve(K);
	return 0;
}
