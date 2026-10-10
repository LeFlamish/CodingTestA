#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

// 좌표 정보
struct Point {
    int r, c;
};

// 아기 고래의 현재 위치 및 방향
struct Whale {
    int r, c, d;
};

int N, r, c, d, visitedCnt;

int board[51][51];              // 바다 지도 (0: 이동 가능, 1: 이동 불가)
bool visited[51][51];           // 아기 고래가 방문한 위치
int visitedForNearest[51][51];  // BFS 탐색 시 방문 여부 및 거리 저장

Whale whale;

// 방향 인덱스: 상(0), 좌(1), 하(2), 우(3)
int dc[] = { 0, -1, 0, 1 };
int dr[] = { -1, 0, 1, 0 };

// 디버깅: 바다 지도 및 아기 고래의 방문 상태 출력
void Debug() {
    cout << "====================\n";
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            cout << board[r][c] << ' ';
        }
        cout << '\n';
    }
    cout << "--------------------\n";
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            if (whale.r == r && whale.c == c) {
                switch(whale.d) {
                    case 0:
                        cout << "↑ ";
                        break;
                    case 1:
                        cout << "← ";
                        break;
                    case 2:
                        cout << "↓ ";
                        break;
                    case 3:
                        cout << "→ ";
                        break;
                }
                continue;
            }
            cout << visited[r][c] << ' ';
        }
        cout << '\n';
    }
    cout << "--------------------\n";
    cout << "====================\n";
}

// 입력 및 초기 상태 설정
void Init() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> r >> c >> d;

    // 시작 위치는 방문한 것으로 처리
    visited[r][c] = true;

    // 아기 고래의 초기 위치 설정
    whale.r = r;
    whale.c = c;

    // 입력 방향을 내부 방향 인덱스로 변환
    // 입력: 1(상), 2(하), 3(좌), 4(우)
    // 내부: 0(상), 1(좌), 2(하), 3(우)
    switch(d) {
        case 1:
            whale.d = 0;
            break;
        case 2:
            whale.d = 2;
            break;
        case 3:
            whale.d = 1;
            break;
        case 4:
            whale.d = 3;
            break;
    }

    // 바다 지도 입력
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            cin >> board[r][c];
        }
    }
}

// 좌표가 격자 범위를 벗어나는지 확인
inline bool OOB(int r, int c) {
    return r < 1 || r > N || c < 1 || c > N;
}

// 인접한 미방문 칸으로 이동 시도
// 이동 성공 시 true, 이동할 수 없으면 false 반환
bool AdjMoveWhale() {
    bool flag = false;

    // 최대 4번의 방향 탐색
    for (int dir = 1; dir <= 4; dir++) {
        // 현재 바라보는 방향의 다음 위치
        int nr = whale.r + dr[whale.d];
        int nc = whale.c + dc[whale.d];

        // 격자 밖이거나 이미 방문했거나 이동 불가능한 칸인 경우
        if (OOB(nr, nc) || visited[nr][nc] || board[nr][nc]) {
            // 방향을 변경하고 다음 이동 시도
            whale.d = (whale.d + dir) % 4;
            continue;
        }

        // 이동한 위치를 방문 처리
        visited[nr][nc] = true;

        // 아기 고래의 위치 갱신
        whale.r = nr;
        whale.c = nc;

        flag = true;
        break;
    }

    return flag;
}

// BFS를 이용하여 가장 가까운 미방문 칸 탐색
// 우선순위: 1. 최단 거리 2. 행이 작은 칸 3. 열이 작은 칸
Point FindNearestPoint() {
    // BFS 탐색 정보 초기화
    memset(visitedForNearest, 0, sizeof(visitedForNearest));

    queue<Point> Q;

    // 현재 아기 고래의 위치에서 BFS 시작
    Q.push({whale.r, whale.c});
    visitedForNearest[whale.r][whale.c] = 1;

    Point nearest = {-1, -1};
    int minDist = 1e9;

    while (!Q.empty()) {
        Point cur = Q.front(); Q.pop();

        // 시작 위치의 거리 값을 1로 설정했으므로 실제 거리는 -1
        int dist = visitedForNearest[cur.r][cur.c] - 1;

        // 이미 찾은 최단 거리보다 멀면 탐색 종료
        if (dist > minDist) break;

        // 방문하지 않은 칸을 발견한 경우
        if (!visited[cur.r][cur.c]) {
            // 최단 거리가 같다면 행, 열이 작은 칸 선택
            if (nearest.r == -1 || cur.r < nearest.r ||
                (cur.r == nearest.r && cur.c < nearest.c))
                nearest = cur;

            minDist = dist;
            continue;
        }

        // 상 → 좌 → 하 → 우 순서로 인접 칸 탐색
        for (int dir = 0; dir < 4; dir++) {
            int nr = cur.r + dr[dir];
            int nc = cur.c + dc[dir];

            // 격자 밖이면 제외
            if (OOB(nr, nc)) continue;

            // 이동 불가능하거나 BFS에서 이미 탐색한 칸이면 제외
            if (board[nr][nc] || visitedForNearest[nr][nc]) continue;

            // 시작 위치를 1로 설정했으므로 다음 칸의 거리 값은 dist + 2
            visitedForNearest[nr][nc] = dist + 2;
            Q.push({nr, nc});
        }
    }

    // 도달 가능한 미방문 칸이 없다면 {-1, -1} 반환
    return nearest;
}

// 목적지에서 역방향 BFS를 수행하여 최단 거리 정보 계산
void FindNearestPath(Point nearest) {
    memset(visitedForNearest, 0, sizeof(visitedForNearest));

    queue<Point> Q;

    // 목적지를 BFS 시작점으로 설정
    Q.push(nearest);
    visitedForNearest[nearest.r][nearest.c] = 1;

    while (!Q.empty()) {
        Point cur = Q.front(); Q.pop();

        // 현재 위치에서 인접한 4방향 탐색
        for (int dir = 0; dir < 4; dir++) {
            int nr = cur.r + dr[dir];
            int nc = cur.c + dc[dir];

            if (OOB(nr, nc)) continue;
            if (board[nr][nc] || visitedForNearest[nr][nc]) continue;

            // 목적지로부터의 최단 거리 기록
            visitedForNearest[nr][nc] =
                visitedForNearest[cur.r][cur.c] + 1;

            Q.push({nr, nc});
        }
    }
}

// 역방향 BFS 결과를 이용하여 목적지까지 최단 경로 이동
void FollowNearestPath(Point nearest) {
    // 최단 경로가 여러 개라면 좌 → 하 → 우 → 상 우선
    int directions[] = {1, 2, 3, 0};

    // 목적지에 도착할 때까지 이동
    while (whale.r != nearest.r || whale.c != nearest.c) {
        for (int dir : directions) {
            int nr = whale.r + dr[dir];
            int nc = whale.c + dc[dir];

            // 이동할 수 없는 칸 제외
            if (OOB(nr, nc) || board[nr][nc]) continue;

            // 목적지까지의 거리가 1 감소하는 칸만 선택
            // 역방향 BFS의 거리 정보를 이용하여 최단 경로 복원
            if (visitedForNearest[nr][nc] !=
                visitedForNearest[whale.r][whale.c] - 1) continue;

            // 아기 고래의 위치 및 방향 갱신
            whale.r = nr;
            whale.c = nc;
            whale.d = dir;

            break;
        }
    }

    // 최단 경로 이동이 끝난 목적지를 방문 처리
    visited[whale.r][whale.c] = true;
}

// 전체 시뮬레이션
void Solve() {
    // 초기 위치 출력
    cout << whale.r << ' ' << whale.c << '\n';

    // 최대 N * N번의 이동 수행
    for (int i = 0; i < N * N; i++) {

        // 인접한 미방문 칸으로 이동할 수 없는 경우
        if (!AdjMoveWhale()) {

            // BFS를 이용하여 가장 가까운 미방문 칸 탐색
            Point nearest = FindNearestPoint();

            // 도달 가능한 미방문 칸이 없다면 시뮬레이션 종료
            if (nearest.r == -1 && nearest.c == -1) break;

            // 목적지에서 역방향 BFS로 최단 거리 계산
            FindNearestPath(nearest);

            // 최단 경로를 따라 목적지까지 이동
            FollowNearestPath(nearest);
        }

        // 이동 후 아기 고래의 위치 출력
        cout << whale.r << ' ' << whale.c << '\n';

        //Debug();
    }
}

int main() {
    Init();
    Solve();
    return 0;
}
