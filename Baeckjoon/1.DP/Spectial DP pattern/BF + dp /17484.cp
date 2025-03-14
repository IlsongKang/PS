#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
// 방향: 왼쪽 대각선 아래, 바로 아래, 오른쪽 대각선 아래
int dy[] = { -1, 0, 1 };

vector<vector<int>> board;

// dp[i][j][k]: i행 j열에 도착했을 때, 직전에 k 방향으로 이동했을 때의 최소 연료
vector<vector<vector<int>>> dp;

int main() {
    cin >> n >> m;
    board.resize(n, vector<int>(m));

    // dp 배열 초기화 (매우 큰 값으로)
    dp.resize(n, vector<vector<int>>(m, vector<int>(3, 1e9)));

    // 입력 받기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    // 첫 번째 행 초기화 (시작점)
    for (int j = 0; j < m; j++) {
        for (int dir = 0; dir < 3; dir++) {
            dp[0][j][dir] = board[0][j];
        }
    }

    // DP로 모든 위치 계산
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int dir = 0; dir < 3; dir++) {
                // 이전 위치 계산
                int prev_y = j - dy[dir];

                // 범위를 벗어나면 계속
                if (prev_y < 0 || prev_y >= m) continue;

                // 같은 방향으로 연속 이동 불가능
                for (int prev_dir = 0; prev_dir < 3; prev_dir++) {
                    if (prev_dir != dir) {
                        dp[i][j][dir] = min(dp[i][j][dir], dp[i - 1][prev_y][prev_dir] + board[i][j]);
                    }
                }
            }
        }
    }

    // 마지막 행에서 최소값 찾기
    int result = 1e9;
    for (int j = 0; j < m; j++) {
        for (int dir = 0; dir < 3; dir++) {
            result = min(result, dp[n - 1][j][dir]);
        }
    }

    cout << result << '\n';

    return 0;
}
