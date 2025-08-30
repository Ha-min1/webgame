// game_core.h
#pragma once // 헤더 파일 중복 포함 방지

const int BRICK_ROW_COUNT = 3;
const int BRICK_COLUMN_COUNT = 5;
const int BRICK_WIDTH = 75;
const int BRICK_HEIGHT = 20;
const int BRICK_PADDING = 10;
const int BRICK_OFFSET_TOP = 30;
const int BRICK_OFFSET_LEFT = 30;

const int PADDLE_HEIGHT = 10; // 패들 높이 (캔버스에 그릴 때 필요)
const int PADDLE_WIDTH = 75;  // 패들 너비

const int BALL_RADIUS = 10; // 공 반지름

// --- 공, 패들, 벽돌 상태 (C++이 관리할 핵심 변수들) ---
extern double g_ballX; // extern은 다른 파일에서도 이 변수를 사용할 수 있게 해줘
extern double g_ballY;
extern double g_dx;
extern double g_dy;

extern double g_paddleX; // 패들 현재 x 위치

extern bool g_rightPressed; // 키 눌림 상태 (JS에서 값을 받아올 거야)
extern bool g_leftPressed;

extern int g_score; // 점수
extern int g_lives; // 생명

// 벽돌 구조체 정의 (각 벽돌의 정보를 담을 거야)
struct Brick {
    double x; // 벽돌의 x 좌표
    double y; // 벽돌의 y 좌표
    int status; // 벽돌 상태 (1: 살아있음, 0: 깨짐)
};

// 벽돌 배열 (2차원 벡터 사용)
extern Brick g_bricks[BRICK_COLUMN_COUNT][BRICK_ROW_COUNT]; // 고정된 크기 배열로 일단 시작

// --- 함수 선언들 (C++에서 구현할 핵심 게임 로직) ---

// 게임 초기화 함수 (모든 변수들을 초기 상태로 리셋)
void initializeGame(double canvasWidth, double canvasHeight); 

// 공, 패들, 벽돌 등의 위치와 상태를 업데이트하는 메인 게임 로직 함수
// JS의 draw() 함수 안에서 호출될 예정
void updateGameLogic(double canvasWidth, double canvasHeight); // <--- 이제 이 함수 선언은 일반 C++ 스타일!

// 공과 벽돌의 충돌을 감지하고 처리하는 함수 (JS의 collisionDetection 대체)
void detectBrickCollision(double canvasWidth, double canvasHeight);

// 패들의 x 좌표를 업데이트하는 함수 (키 입력에 따라)
// void updatePaddlePosition(double canvasWidth); // <--- 이건 필요하면 다시 넣어주자

// 공이 벽에 부딪혔을 때 튕기는 로직 (JS의 draw() 안의 일부 로직 대체)
void updateBallPosition(double canvasWidth, double canvasHeight);


// --- JavaScript와 통신을 위한 함수 (WebAssembly export) ---
// Emscripten을 통해 JS에서 호출할 수 있도록 아래 extern "C" 블록 안에 선언!

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
extern "C" { // <--- 여기에 extern "C" 시작! (여기 라인 번호는 다를 수 있음)

// JS에서 호출해서 키 상태를 설정하는 함수
EMSCRIPTEN_KEEPALIVE void setKeyPressed(int key_code, bool is_pressed);

// JS에서 C++의 공/패들/스코어/생명 데이터를 가져갈 수 있도록 해주는 함수들
EMSCRIPTEN_KEEPALIVE double getBallX();
EMSCRIPTEN_KEEPALIVE double getBallY();
EMSCRIPTEN_KEEPALIVE double getPaddleX();
EMSCRIPTEN_KEEPALIVE int getScore();
EMSCRIPTEN_KEEPALIVE int getLives();

// JS에서 벽돌 데이터를 통째로 가져갈 수 있도록 (아니면 각 벽돌의 status만)
// 이 부분은 조금 더 복잡해질 수 있는데, 일단 각 벽돌 status만 가져오는 방향으로 고려
EMSCRIPTEN_KEEPALIVE int getBrickStatus(int col, int row);

} // extern "C" <--- 여기에 extern "C" 닫기! (여기 라인 번호도 다를 수 있음)
#endif
