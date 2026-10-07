#include <iostream>
#include <queue>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

struct Turret {
    int x, y; // Turret 구조체 자체를 2차원 배열로 쓰기 때문에 중복된 데이터이긴 하지만, operator 함수 사용을 위해 추가
    int power;
    int lastAttack;

    bool operator < (const Turret& _turret) const {
        // 1. 공격력이 낮은 포탑
        if (power != _turret.power)
            return power < _turret.power;

        // 2. 가장 최근에 공격한 포탑
        if (lastAttack != _turret.lastAttack)
            return lastAttack > _turret.lastAttack;

        // 3. 행 + 열의 합이 큰 포탑
        if (x + y != _turret.x + _turret.y)
            return x + y > _turret.x + _turret.y;

        // 4. 열 값이 큰 포탑
        return y > _turret.y;
    }
};

int N, M, K;

Turret turrets[11][11]; // 모든 위치에 포탑이 존재한다면, 굳이 int board와 Turret turrets를 따로 둘 필요가 있을까?

bool attacked[11][11];
bool visited[11][11];

Point prevPoint[11][11];

// 우 / 하 / 좌 / 상
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

// 포탄 공격 8방향
int bx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int by[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool IsSame(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

int CountAlive() {
    int cnt = 0;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (turrets[x][y].power > 0)
                cnt++;
        }
    }

    return cnt;
}

Point SelectAttacker() {
    Point attacker = { -1, -1 };

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (turrets[x][y].power <= 0)
                continue;

            if (attacker.x == -1 ||
                turrets[x][y] < turrets[attacker.x][attacker.y]) {
                attacker = { x, y };
            }
        }
    }

    return attacker;
}

Point SelectTarget(Point attacker) {
    Point target = { -1, -1 };

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (turrets[x][y].power <= 0)
                continue;

            if (x == attacker.x && y == attacker.y)
                continue;

            // 현재 포탑이 기존 target보다 강하면 갱신
            if (target.x == -1 ||
                turrets[target.x][target.y] < turrets[x][y]) {
                target = { x, y };
            }
        }
    }

    return target;
}

bool LaserAttack(Point attacker, Point target) {
    memset(visited, false, sizeof(visited));

    queue<Point> q;

    q.push(attacker);
    visited[attacker.x][attacker.y] = true;

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (IsSame(cur, target))
            break;

        for (int dir = 0; dir < 4; dir++) {
            int nx = (cur.x + dx[dir] + N) % N;
            int ny = (cur.y + dy[dir] + M) % M;

            if (visited[nx][ny])
                continue;

            if (turrets[nx][ny].power <= 0)
                continue;

            visited[nx][ny] = true;
            prevPoint[nx][ny] = cur;

            q.push({ nx, ny });
        }
    }

    // 공격 대상까지 가는 경로가 없음
    if (!visited[target.x][target.y])
        return false;

    int damage = turrets[attacker.x][attacker.y].power;

    // 공격 대상
    turrets[target.x][target.y].power -= damage;
    attacked[target.x][target.y] = true;

    // 공격 대상과 공격자 사이의 경로
    Point cur = prevPoint[target.x][target.y];

    while (!IsSame(cur, attacker)) {
        turrets[cur.x][cur.y].power -= damage / 2;
        attacked[cur.x][cur.y] = true;

        cur = prevPoint[cur.x][cur.y];
    }

    return true;
}

void BombAttack(Point attacker, Point target) {
    int damage = turrets[attacker.x][attacker.y].power;

    // 공격 대상
    turrets[target.x][target.y].power -= damage;
    attacked[target.x][target.y] = true;

    // 공격 대상 주변 8방향
    for (int dir = 0; dir < 8; dir++) {
        int nx = (target.x + bx[dir] + N) % N;
        int ny = (target.y + by[dir] + M) % M;

        // 공격자는 피해를 받지 않음
        if (nx == attacker.x && ny == attacker.y)
            continue;

        // 부서진 포탑은 피해 없음
        if (turrets[nx][ny].power <= 0)
            continue;

        turrets[nx][ny].power -= damage / 2;
        attacked[nx][ny] = true;
    }
}

void Repair() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            // 부서진 포탑
            if (turrets[x][y].power <= 0)
                continue;

            // 이번 턴 공격과 관련된 포탑
            if (attacked[x][y])
                continue;

            turrets[x][y].power++;
        }
    }
}

void Debug() {
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            cout << setw(4) << turrets[y][x] << ' ';
        }
        cout << '\n';
    }
}

void Init() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            cin >> turrets[x][y].power;

            turrets[x][y].x = x;
            turrets[x][y].y = y;
            turrets[x][y].lastAttack = 0;
        }
    }
}

void Solve() {
    for (int turn = 1; turn <= K; turn++) {
        if (CountAlive() <= 1)
            break;

        memset(attacked, false, sizeof(attacked));

        // 1. 공격자 선정
        Point attacker = SelectAttacker();

        turrets[attacker.x][attacker.y].power += N + M;
        turrets[attacker.x][attacker.y].lastAttack = turn;

        attacked[attacker.x][attacker.y] = true;

        // 2. 공격 대상 선정
        Point target = SelectTarget(attacker);

        // 레이저 공격을 우선 시도
        if (!LaserAttack(attacker, target))
            BombAttack(attacker, target);

        // 3. 포탑 부서짐
        // power <= 0인 포탑을 부서진 것으로 판단하므로 별도 처리 없음

        // 4. 포탑 정비
        Repair();
    }

    int answer = 0;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            answer = max(answer, turrets[x][y].power);
        }
    }

    cout << answer << '\n';
}

int main() {
    Init();
    Solve();
}
