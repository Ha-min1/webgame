#include "game_core.h"
#include <vector>  // 벽돌 배열에 std::vector를 사용한다면 필요 (현재는 고정 배열이지만 나중에 바뀔 수도!)
#include <cmath>   // 수학 함수 (M_PI, sin, cos 등) 필요할 때 대비해서 (나중에 공 움직임 등에)


// --- game.h에서 extern으로 선언했던 전역 변수들 정의 ---
// 여기에 실제로 메모리를 할당하고 초기값을 지정해주는 거야!
double g_ballX;
double g_ballY;
double g_dx;
double g_dy;

double g_paddleX;

bool g_rightPressed;
bool g_leftPressed;

int g_score;
int g_lives;

// 벽돌 배열 정의
Brick g_bricks[BRICK_COLUMN_COUNT][BRICK_ROW_COUNT]; // game.h에 상수로 정의된 크기 사용

// --- 게임 초기화 함수 구현 ---
void initializeGame(double canvasWidth, double canvasHeight) { // 캔버스 크기를 받아서 초기화
    // 공 초기 위치
    g_ballX = canvasWidth / 2;
    g_ballY = canvasHeight - 30;
    g_dx = 2; // 공 속도 (오른쪽 위로 시작)
    g_dy = -2;

    // 패들 초기 위치
    g_paddleX = (canvasWidth - PADDLE_WIDTH) / 2;

    // 키 눌림 상태 초기화
    g_rightPressed = false;
    g_leftPressed = false;

    // 점수와 생명 초기화
    g_score = 0;
    g_lives = 3;

    // 벽돌 배열 초기화 (모든 벽돌을 살아있는 상태로)
    for (int c = 0; c < BRICK_COLUMN_COUNT; c++) {
        for (int r = 0; r < BRICK_ROW_COUNT; r++) {
            g_bricks[c][r].status = 1; // 1은 살아있는 상태
            // 벽돌의 x, y 좌표도 미리 계산해서 저장해두자
            g_bricks[c][r].x = (c * (BRICK_WIDTH + BRICK_PADDING)) + BRICK_OFFSET_LEFT;
            g_bricks[c][r].y = (r * (BRICK_HEIGHT + BRICK_PADDING)) + BRICK_OFFSET_TOP;
        }
    }
}


// --- 나머지 함수들은 여기에 차차 구현해나가면 돼! ---

// JS에서 호출할 WebAssembly export 함수들 (game.h에 선언된 것들)도 여기에 정의하면 돼!
// 이 함수들은 game.h에 선언만 되어 있었잖아. 실제 내용은 여기에 작성하는 거야.

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
// emscripten_run_script 같은 거 쓸 땐 #include <emscripten/emscripten.h>
// emscripten.h는 일반 C++ 파일에 포함시켜도 문제가 없어.

extern "C" { // C++이름 맹글링 피하고 C 호출 규약을 따르도록

EMSCRIPTEN_KEEPALIVE void setKeyPressed(int key_code, bool is_pressed) {
    // 키 코드 (예: 1 for Right, 2 for Left)는 나중에 정의해야 해.
    // 일단 임시로 숫자 1을 오른쪽, 2를 왼쪽으로 가정해볼게!
    if (key_code == 1) { // 오른쪽 키
        g_rightPressed = is_pressed;
    } else if (key_code == 2) { // 왼쪽 키
        g_leftPressed = is_pressed;
    }
}

EMSCRIPTEN_KEEPALIVE double getBallX() { return g_ballX; }
EMSCRIPTEN_KEEPALIVE double getBallY() { return g_ballY; }
EMSCRIPTEN_KEEPALIVE double getPaddleX() { return g_paddleX; }
EMSCRIPTEN_KEEPALIVE int getScore() { return g_score; }
EMSCRIPTEN_KEEPALIVE int getLives() { return g_lives; }

EMSCRIPTEN_KEEPALIVE int getBrickStatus(int col, int row) {
    if (col >= 0 && col < BRICK_COLUMN_COUNT && row >= 0 && row < BRICK_ROW_COUNT) {
        return g_bricks[col][row].status;
    }
    return -1; // 에러 처리
}

} // extern "C"
#endif
