#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define SIZE 11
typedef pair<int, int> CD;
#define X first
#define Y second

int N, M, K;
int board[SIZE][SIZE];
int Prev[SIZE][SIZE];
int attack[SIZE][SIZE];
bool visited[SIZE][SIZE];
bool related[SIZE][SIZE];
int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
int dy[] = { 0, 1, 0, -1, -1, 1, 1, -1 };
vector<pair<int, CD>> candidates;

void check() {
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            cout << setw(4) << board[y][x] << ' ';
        }
        cout << '\n';
    }
}

void init() {
    cin >> N >> M >> K;
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            cin >> board[y][x];
        }
    }
}

CD findMin() {
    candidates.clear();
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            if (board[y][x] != 0) {
                candidates.push_back({ board[y][x], { x, y } });
            }
        }
    }

    sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first < b.first; // 값이 작을수록
        if (attack[a.second.Y][a.second.X] != attack[b.second.Y][b.second.X])
            return attack[a.second.Y][a.second.X] > attack[b.second.Y][b.second.X]; // 공격 횟수 우선
        int sumA = a.second.Y + a.second.X;
        int sumB = b.second.Y + b.second.X;
        if (sumA != sumB) return sumA > sumB; // 행과 열의 합이 큰 것 우선
        return a.second.X > b.second.X; // 열의 값이 큰 것 우선
        });

    CD ret = candidates[0].second;
    board[ret.Y][ret.X] += N + M;
    return ret;
}

CD findMax() {
    candidates.clear();
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            if (board[y][x] != 0) {
                candidates.push_back({ board[y][x], { x, y } });
            }
        }
    }

    sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first > b.first; // 값이 클수록
        if (attack[a.second.Y][a.second.X] != attack[b.second.Y][b.second.X])
            return attack[a.second.Y][a.second.X] < attack[b.second.Y][b.second.X]; // 공격 횟수 우선
        int sumA = a.second.Y + a.second.X;
        int sumB = b.second.Y + b.second.X;
        if (sumA != sumB) return sumA < sumB; // 행과 열의 합이 작은 것 우선
        return a.second.X < b.second.X; // 열의 값이 작은 것 우선
        });

    return candidates[0].second;
}

int countTowers() {
    int count = 0;
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            if (board[y][x] != 0) {
                count++;
            }
        }
    }
    return count;
}

bool canLaser(CD Start, CD End) {
    memset(visited, false, sizeof(visited));
    queue<CD> Q;
    visited[Start.Y][Start.X] = true;
    Q.push(Start);
    while (!Q.empty()) {
        CD cur = Q.front(); Q.pop();
        if (cur == End) return true;
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 1) nx = M; if (nx > M) nx = 1;
            if (ny < 1) ny = N; if (ny > N) ny = 1;
            if (board[ny][nx] == 0 || visited[ny][nx]) continue;
            visited[ny][nx] = true;
            Prev[ny][nx] = dir;
            Q.push({ nx, ny });
        }
    }
    return false;
}

void laserAttack(CD Start, CD End) {
    int x = End.X;
    int y = End.Y;
    board[End.Y][End.X] = max(0, board[End.Y][End.X] - board[Start.Y][Start.X]);
    related[Start.Y][Start.X] = true;
    related[End.Y][End.X] = true;
    while (1) {
        int dir = Prev[y][x];
        int nx = x - dx[dir];
        int ny = y - dy[dir];
        if (nx < 1) nx = M; if (nx > M) nx = 1;
        if (ny < 1) ny = N; if (ny > N) ny = 1;
        if (nx == Start.X && ny == Start.Y) break;
        board[ny][nx] = max(0, board[ny][nx] - board[Start.Y][Start.X] / 2);
        related[ny][nx] = true;
        x = nx; y = ny;
    }
}

void bombAttack(CD Start, CD End) {
    related[Start.Y][Start.X] = true;
    board[End.Y][End.X] = max(0, board[End.Y][End.X] - board[Start.Y][Start.X]);
    related[End.Y][End.X] = true;
    for (int dir = 0; dir < 8; dir++) {
        int nx = End.X + dx[dir];
        int ny = End.Y + dy[dir];
        if (nx < 1) nx = M; if (nx > M) nx = 1;
        if (ny < 1) ny = N; if (ny > N) ny = 1;
        if (board[ny][nx] == 0 || (nx == Start.X && ny == Start.Y)) continue;
        board[ny][nx] = max(0, board[ny][nx] - board[Start.Y][Start.X] / 2);
        related[ny][nx] = true;
    }
}

void prepare() {
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            if (board[y][x] && !related[y][x]) board[y][x]++;
        }
    }
}

void solve(int k) {
    memset(Prev, 0, sizeof(Prev));
    memset(related, false, sizeof(related));
    if (countTowers() <= 1) return;
    //cout << "====================\n<BEFORE>\n";
    //check();
    CD End = findMax();
    CD Start = findMin();
    //cout << "--------------------\n";
    //cout << Start.X << ' ' << Start.Y << " : " << board[Start.Y][Start.X] - N - M << '\n';
    //cout << End.X << ' ' << End.Y << " : " << board[End.Y][End.X] << '\n';
    if (canLaser(Start, End)) {
        //cout << "LASER\n";
        laserAttack(Start, End);
    }
    else {
        bombAttack(Start, End);
        //cout << "BOMB\n";
    }

    //cout << "--------------------\n<AFTER>\n";
    //check();
    //cout << "====================\n\n";
    attack[Start.Y][Start.X] = k;
    prepare();
}

int findAnswer() {
    int ret = INT_MIN;
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            ret = max(ret, board[y][x]);
        }
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init();
    for (int k = 1; k <= K; k++) {
        solve(k);
    }
    cout << findAnswer();
    return 0;
}
