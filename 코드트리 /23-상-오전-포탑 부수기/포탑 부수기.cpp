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
    int x, y; // operator < 에서 좌표 비교를 위해 저장
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
int aliveCount;

Turret turrets[11][11];

bool attacked[11][11];
bool visited[11][11];

Point prevPoint[11][11];

// 우 / 하 / 좌 / 상
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

// 포탄 공격 8방향
int bx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int by[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

inline bool IsSame(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void Damage(Point point, int damage) {
    Turret& turret = turrets[point.x][point.y];

    // 이미 부서진 포탑
    if (turret.power <= 0)
        return;

    turret.power -= damage;
    attacked[point.x][point.y] = true;

    // 이번 공격으로 부서진 경우
    if (turret.power <= 0)
        aliveCount--;
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

            // 부서진 포탑은 지나갈 수 없음
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
    Damage(target, damage);

    // 공격 대상과 공격자 사이의 경로
    Point cur = prevPoint[target.x][target.y];

    while (!IsSame(cur, attacker)) {
        Damage(cur, damage / 2);

        cur = prevPoint[cur.x][cur.y];
    }

    return true;
}

void BombAttack(Point attacker, Point target) {
    int damage = turrets[attacker.x][attacker.y].power;

    // 공격 대상
    Damage(target, damage);

    // 공격 대상 주변 8방향
    for (int dir = 0; dir < 8; dir++) {
        int nx = (target.x + bx[dir] + N) % N;
        int ny = (target.y + by[dir] + M) % M;

        // 공격자는 피해를 받지 않음
        if (nx == attacker.x && ny == attacker.y)
            continue;

        // 이미 이번 공격에 피해를 받은 위치
        if (attacked[nx][ny])
            continue;

        // 이미 부서진 포탑
        if (turrets[nx][ny].power <= 0)
            continue;

        Damage({ nx, ny }, damage / 2);
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
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            cout << setw(4) << turrets[x][y].power << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void Init() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;

    aliveCount = 0;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            cin >> turrets[x][y].power;

            turrets[x][y].x = x;
            turrets[x][y].y = y;
            turrets[x][y].lastAttack = 0;

            if (turrets[x][y].power > 0)
                aliveCount++;
        }
    }
}

void Solve() {
    for (int turn = 1; turn <= K; turn++) {
        if (aliveCount <= 1)
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
        // Damage()에서 power <= 0이 되는 순간 aliveCount 감소

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
