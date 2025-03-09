#include <iostream>
using namespace std;

struct Santa {
	int X;
	int Y;
	int score;
	bool isOut;
	int isStun;
};

struct Rudolph {
	int X;
	int Y;
	int power;
};

int N, M, P, C, D;
int totalSanta;
Rudolph R;
Santa S[31];
int board[51][51];
int rx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int ry[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int sx[] = { 0, 1, 0, -1 };
int sy[] = { -1, 0, 1, 0 };

void check(int k) {
	cout << "====================\n";
	cout << k << "번 째 턴\n--------------------\n";
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cout << board[y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	cout << "루돌프 : " << '(' << R.X << ", " << R.Y << ")\n";
	for (int p = 1; p <= P; p++) {
		cout << p << " : " << S[p].score << '\n';
		if (S[p].isOut) cout << p << " is Out\n";
		else {
			if (S[p].isStun) cout << p << " is Stun\n";
		}
	}
	cout << "====================\n";
}

bool isArea(int nx, int ny) {
	if (nx < 1 || nx > N || ny < 1 || ny > N) return false;
	return true;
}

void init() {
	cin >> N >> M >> P >> C >> D;
	totalSanta = P;
	cin >> R.Y >> R.X;
	board[R.Y][R.X] = -1;
	for (int i = 1; i <= P; i++) {
		int n, x, y;
		cin >> n >> y >> x;
		S[n].X = x;
		S[n].Y = y;
		board[y][x] = n;
	}
}

int distance(int x1, int y1, int x2, int y2) {
	return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

void interactionByR(int santaNum, int dir) {
	int target = board[S[santaNum].Y][S[santaNum].X];
	board[S[target].Y][S[target].X] = santaNum;
	S[target].X += rx[dir];
	S[target].Y += ry[dir];
	if (!isArea(S[target].X, S[target].Y)) {
		S[target].isOut = true;
		totalSanta--;
		return;
	}
	else if (board[S[target].Y][S[target].X] > 0) interactionByR(target, dir);
	board[S[target].Y][S[target].X] = target;
}

void interactionByS(int santaNum, int dir) {
	int target = board[S[santaNum].Y][S[santaNum].X];
	board[S[target].Y][S[target].X] = santaNum;
	S[target].X += sx[dir];
	S[target].Y += sy[dir];
	if (!isArea(S[target].X, S[target].Y)) {
		S[target].isOut = true;
		totalSanta--;
		return;
	}
	else if (board[S[target].Y][S[target].X] > 0) interactionByS(target, dir);
	board[S[target].Y][S[target].X] = target;
}

void crashRudolph(int santaNum, int dir) {
	S[santaNum].score += C;
	S[santaNum].isStun = 2;
	int nx = S[santaNum].X;
	int ny = S[santaNum].Y;
	for (int i = 0; i < C; i++) {
		nx += rx[dir];
		ny += ry[dir];
	}
	if (!isArea(nx, ny)) {
		S[santaNum].isOut = true;
		totalSanta--;
	}
	else {
		S[santaNum].X = nx;
		S[santaNum].Y = ny;
		if (board[ny][nx] > 0) interactionByR(santaNum, dir);
		board[ny][nx] = santaNum;
	}
}

void crashSanta(int santaNum, int dir) {
	S[santaNum].score += D;
	S[santaNum].isStun = 2;
	int nx = S[santaNum].X;
	int ny = S[santaNum].Y;
	for (int i = 0; i < D; i++) {
		nx += sx[dir];
		ny += sy[dir];
	}
	if (!isArea(nx, ny)) {
		S[santaNum].isOut = true;
		totalSanta--;
	}
	else {
		S[santaNum].X = nx;
		S[santaNum].Y = ny;
		if (board[ny][nx] > 0) interactionByS(santaNum, dir);
		board[ny][nx] = santaNum;
	}
}

void moveRudolph() {
	int minD = INT_MAX;
	int toX = -1, toY = -1;
	int target = -1;
	int targetDir = -1;
	for (int p = 1; p <= P; p++) {
		if (S[p].isOut) continue; // 산타가 탈락했는지 여부
		int tmp = distance(R.X, R.Y, S[p].X, S[p].Y);
		if (tmp < minD) {
			toX = S[p].X;
			toY = S[p].Y;
			minD = tmp;
			target = p;
		}
		else if (tmp == minD) {
			if (toY < S[p].Y) {
				toX = S[p].X;
				toY = S[p].Y;
				target = p;
			}
			else if (toY == S[p].Y) {
				if (toX < S[p].X) {
					toX = S[p].X;
					toY = S[p].Y;
					target = p;
				}
			}
		}
	}
	for (int dir = 0; dir < 8; dir++) {
		int tmp = distance(R.X + rx[dir], R.Y + ry[dir], S[target].X, S[target].Y);
		if (minD > tmp) {
			targetDir = dir;
			minD = tmp;
		}
	}
	board[R.Y][R.X] = 0;
	R.X = R.X + rx[targetDir];
	R.Y = R.Y + ry[targetDir];
	int santaNum = board[R.Y][R.X];
	if (santaNum) crashRudolph(santaNum, targetDir);
	board[R.Y][R.X] = -1;
}

void moveSanta() {
	for (int p = 1; p <= P; p++) {
		int targetDir = -1;
		if (S[p].isOut || S[p].isStun) continue;
		int tmp = distance(S[p].X, S[p].Y, R.X, R.Y);
		for (int dir = 0; dir < 4; dir++) {
			int nx = S[p].X + sx[dir];
			int ny = S[p].Y + sy[dir];
			if (!isArea(nx, ny)) continue;
			if (board[ny][nx] > 0) continue;
			int temp = distance(nx, ny, R.X, R.Y);
			if (tmp > temp) {
				targetDir = dir;
				tmp = temp;
			}
		}
		if (targetDir == -1) continue;
		board[S[p].Y][S[p].X] = 0;
		S[p].X += sx[targetDir];
		S[p].Y += sy[targetDir];
		int isRudolph = board[S[p].Y][S[p].X];
		targetDir = (targetDir + 2) % 4;
		if (isRudolph == -1) crashSanta(p, targetDir);
		else board[S[p].Y][S[p].X] = p;
	}
}

void solve() {
	for (int m = 1; m <= M; m++) {
		for (int p = 1; p <= P; p++) {
			if (S[p].isStun > 0) S[p].isStun--;
		}
		//check(m);
		moveRudolph();
		//check(m);
		moveSanta();
		//check(m);
		if (totalSanta == 0) break;
		for (int p = 1; p <= P; p++) {
			if (!S[p].isOut) S[p].score++;
		}
	}
}

void getScore() {
	for (int p = 1; p <= P; p++) {
		cout << S[p].score << ' ';
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	getScore();
	return 0;
}
