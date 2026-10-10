#include <iostream>
#include <queue>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

// 격자 내 좌표 (x: 행, y: 열)
struct Point {
    int x, y;
};

// 포탑 정보
struct Turret {
    int x, y; // operator < 에서 좌표 비교를 위해 저장
    int power;
    int lastAttack;

    // 포탑의 공격자 선정 우선순위를 비교하는 연산자
    // 반환값이 true라면 현재 포탑이 비교 대상보다 공격자 선정에서 우선
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

int N, M, K;                 // 격자 크기 N x M, 최대 턴 수 K
int aliveCount;              // 부서지지 않은 포탑의 개수

Turret turrets[11][11];     // 각 위치의 포탑 정보

bool attacked[11][11];      // 이번 턴 공격과 관련된 포탑 여부
bool visited[11][11];       // 레이저 공격 BFS 방문 여부

Point prevPoint[11][11];    // BFS에서 이전 좌표 저장 (최단 경로 역추적)

// 우 / 하 / 좌 / 상
// 레이저 공격의 최단 경로 우선순위
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

// 포탄 공격 8방향
// 공격 대상의 대각선을 포함한 주변 8칸
int bx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int by[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// 두 좌표가 동일한지 확인
bool IsSame(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

// 특정 위치의 포탑에 피해 적용
void Damage(Point point, int damage) {
    // 참조를 사용하여 원본 포탑의 정보를 직접 수정
    Turret& turret = turrets[point.x][point.y];

    // 이미 부서진 포탑
    if (turret.power <= 0)
        return;

    // 공격력 감소 및 이번 턴 공격 관련 여부 기록
    turret.power -= damage;
    attacked[point.x][point.y] = true;

    // 이번 공격으로 부서진 경우
    if (turret.power <= 0)
        aliveCount--;
}

// 공격자 선정: 살아 있는 포탑 중 가장 약한 포탑 선택
Point SelectAttacker() {
    Point attacker = { -1, -1 };

    // 모든 포탑을 순회하며 공격자 선정
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            // 부서진 포탑은 공격자가 될 수 없음
            if (turrets[x][y].power <= 0)
                continue;

            // 첫 번째 후보이거나 기존 공격자보다 우선순위가 높은 경우 갱신
            // operator < 에 정의된 4가지 우선순위 적용
            if (attacker.x == -1 ||
                turrets[x][y] < turrets[attacker.x][attacker.y]) {
                attacker = { x, y };
            }
        }
    }

    return attacker;
}

// 공격 대상 선정: 공격자를 제외한 살아 있는 포탑 중 가장 강한 포탑 선택
Point SelectTarget(Point attacker) {
    Point target = { -1, -1 };

    // 모든 포탑을 순회하며 공격 대상 선정
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            // 부서진 포탑 제외
            if (turrets[x][y].power <= 0)
                continue;

            // 공격자 자신은 공격 대상에서 제외
            if (x == attacker.x && y == attacker.y)
                continue;

            // 현재 포탑이 기존 target보다 강하면 갱신
            // 공격자 선정과 반대 우선순위 적용
            if (target.x == -1 ||
                turrets[target.x][target.y] < turrets[x][y]) {
                target = { x, y };
            }
        }
    }

    return target;
}

// 레이저 공격
// BFS로 공격자에서 공격 대상까지 최단 경로 탐색
// 공격 가능한 경로가 있으면 true, 없으면 false 반환
bool LaserAttack(Point attacker, Point target) {
    // 매 턴 BFS 방문 정보 초기화
    memset(visited, false, sizeof(visited));

    queue<Point> q;

    // 공격자의 위치에서 BFS 시작
    q.push(attacker);
    visited[attacker.x][attacker.y] = true;

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        // 공격 대상에 도달하면 탐색 종료
        if (IsSame(cur, target))
            break;

        // 우 → 하 → 좌 → 상 순서로 탐색
        // BFS 특성상 최단 경로가 여러 개라면 해당 방향 우선순위 반영
        for (int dir = 0; dir < 4; dir++) {
            // 격자 경계를 넘어가면 반대편으로 연결 (원형 격자)
            int nx = (cur.x + dx[dir] + N) % N;
            int ny = (cur.y + dy[dir] + M) % M;

            // 이미 방문한 위치는 제외
            if (visited[nx][ny])
                continue;

            // 부서진 포탑은 지나갈 수 없음
            if (turrets[nx][ny].power <= 0)
                continue;

            // 방문 처리 및 이전 좌표 기록
            visited[nx][ny] = true;
            prevPoint[nx][ny] = cur;

            q.push({ nx, ny });
        }
    }

    // 공격 대상까지 가는 경로가 없음
    if (!visited[target.x][target.y])
        return false;

    // 공격자의 현재 공격력을 피해량으로 설정
    int damage = turrets[attacker.x][attacker.y].power;

    // 공격 대상
    // 공격 대상은 공격력 전체만큼 피해
    Damage(target, damage);

    // 공격 대상과 공격자 사이의 경로
    // prevPoint를 이용해 공격 대상에서 공격자 방향으로 역추적
    Point cur = prevPoint[target.x][target.y];

    while (!IsSame(cur, attacker)) {
        // 경로상의 포탑은 공격력의 절반만큼 피해
        Damage(cur, damage / 2);

        // 이전 좌표로 이동하여 최단 경로 역추적
        cur = prevPoint[cur.x][cur.y];
    }

    return true;
}

// 포탄 공격
// 레이저 공격이 불가능한 경우 수행
void BombAttack(Point attacker, Point target) {
    // 공격자의 현재 공격력을 피해량으로 설정
    int damage = turrets[attacker.x][attacker.y].power;

    // 공격 대상
    // 공격 대상은 공격력 전체만큼 피해
    Damage(target, damage);

    // 공격 대상 주변 8방향
    for (int dir = 0; dir < 8; dir++) {
        // 격자 경계를 넘어가면 반대편으로 연결 (원형 격자)
        int nx = (target.x + bx[dir] + N) % N;
        int ny = (target.y + by[dir] + M) % M;

        // 공격자는 피해를 받지 않음
        if (nx == attacker.x && ny == attacker.y)
            continue;

        // 이미 이번 공격에 피해를 받은 위치
        // 원형 격자에서 같은 위치가 중복 탐색되는 경우도 방지
        if (attacked[nx][ny])
            continue;

        // 이미 부서진 포탑
        if (turrets[nx][ny].power <= 0)
            continue;

        // 주변 포탑은 공격력의 절반만큼 피해
        Damage({ nx, ny }, damage / 2);
    }
}

// 포탑 정비
// 이번 턴 공격과 관련되지 않은 살아 있는 포탑의 공격력 1 증가
void Repair() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            // 부서진 포탑
            if (turrets[x][y].power <= 0)
                continue;

            // 이번 턴 공격과 관련된 포탑
            if (attacked[x][y])
                continue;

            // 공격과 관련되지 않은 포탑은 공격력 1 증가
            turrets[x][y].power++;
        }
    }
}

// 디버깅: 현재 모든 포탑의 공격력 출력
void Debug() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            cout << setw(4) << turrets[x][y].power << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

// 입력 및 초기 상태 설정
void Init() {
    cin.tie(0)->sync_with_stdio(0);

    // 격자 크기 및 최대 턴 수 입력
    cin >> N >> M >> K;

    aliveCount = 0;

    // 포탑의 초기 공격력 및 좌표 정보 설정
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            cin >> turrets[x][y].power;

            // 각 포탑의 위치 및 마지막 공격 시점 초기화
            turrets[x][y].x = x;
            turrets[x][y].y = y;
            turrets[x][y].lastAttack = 0;

            // 공격력이 0보다 크면 살아 있는 포탑으로 계산
            if (turrets[x][y].power > 0)
                aliveCount++;
        }
    }
}

// 전체 시뮬레이션
void Solve() {
    // 최대 K턴 동안 공격 진행
    for (int turn = 1; turn <= K; turn++) {
        // 살아 있는 포탑이 1개 이하라면 시뮬레이션 종료
        if (aliveCount <= 1)
            break;

        // 매 턴 공격 관련 여부 초기화
        memset(attacked, false, sizeof(attacked));

        // 1. 공격자 선정
        // 살아 있는 포탑 중 가장 약한 포탑 선택
        Point attacker = SelectAttacker();

        // 공격자의 공격력 N + M 증가
        // 마지막 공격 시점을 현재 턴으로 갱신
        turrets[attacker.x][attacker.y].power += N + M;
        turrets[attacker.x][attacker.y].lastAttack = turn;

        // 공격자는 이번 턴 정비 대상에서 제외
        attacked[attacker.x][attacker.y] = true;

        // 2. 공격 대상 선정
        // 공격자를 제외한 살아 있는 포탑 중 가장 강한 포탑 선택
        Point target = SelectTarget(attacker);

        // 레이저 공격을 우선 시도
        // 최단 경로가 존재하지 않으면 포탄 공격 수행
        if (!LaserAttack(attacker, target))
            BombAttack(attacker, target);

        // 3. 포탑 부서짐
        // Damage()에서 power <= 0이 되는 순간 aliveCount 감소

        // 4. 포탑 정비
        // 공격과 관련되지 않은 살아 있는 포탑의 공격력 1 증가
        Repair();
    }

    // 시뮬레이션 종료 후 가장 강한 포탑의 공격력 계산
    int answer = 0;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            answer = max(answer, turrets[x][y].power);
        }
    }

    // 최종 정답 출력
    cout << answer << '\n';
}

int main() {
    Init();
    Solve();
}
