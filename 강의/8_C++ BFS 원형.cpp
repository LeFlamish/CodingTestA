#include <iostream>
#include <queue>
using namespace std;

// R(행)이 세로축 값이고, C(열)이 가로축 값임을 그냥 머리에 박도록 하자.

// 두 개의 자료형을 묶어주는 pair.
// pair<String, int> 이런 식으로 사용 가능.
// 각 값에 접근하기 위해서는 first, second 키워드 사용.
// ex.
// pair<char, String> tmp;
// tmp.first -> char
// tmp.second -> String
// 하지만 #define으로 first, second의 이름을 설정해줄 수 있음.
// 아래는 2차원 배열(2차원 좌표)의 pair 기본 정의.
typedef pair<int, int> PI;
#define X first
#define Y second

// typedef 또는 구조체로 2차원 좌표를 정의
struct State {
	int x, y;
};

// 기출 문제에서는 구조체를 정의하여 객체로 다루어야하는 경우가 많기 때문에 구조체 공부가 필수적.
// ex.
struct Human {
	int x, y, age;
	bool isAlive;
};

int N;
int board[10][10];
bool visited[10][10]; // 최단 거리를 계산하기 위해서는 visited 배열의 자료형을 int로 설정하면 됨.
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

// board나 visited 등 2차원 배열, 변수, 상태 등을 출력하면서 확인할 수 있는 디버깅 함수.
void debug() {
	cout << "====================\n";
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cout << visited[y][x];
		}
		cout << '\n';
	}
	cout << "====================\n";
}

void init() {
	cin >> N;
	// for문에서 변수도 의미있게 설정하면 보기 편함.
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
		}
	}
}

bool OOB(int x, int y) {
	return x < 0 || x >= N || y < 0 || y >= N;
}

void BFS(int x, int y) {
	queue<PI> Q;
	visited[y][x] = true; // 최단 거리 계산에서는 visited[y][x] = 1;
	Q.push({ x, y });
	while (!Q.empty()) {
		PI cur = Q.front(); Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || board[ny][nx] == 0) continue;
			visited[ny][nx] = true; // 최단 거리 계산에서는 visited[ny][nx] = visited[cur.Y][cur.X] + 1;
			Q.push({ nx, ny });
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	BFS(0, 0);
	// debug();
	return 0;
}
