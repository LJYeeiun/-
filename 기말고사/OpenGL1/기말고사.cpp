#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include <vector>

// M_PI가 정의되지 않은 경우 정의하기
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 전역 변수
float angle = 0.0f;  // 회전 각도
bool showHelp = false;  // 도움말 표시 여부

// 광원 속성 (아침 햇빛과 석양)
GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // 초기 광원 위치 (아침 햇빛)
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // 환경광
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 확산광

// 물체의 재질 속성
GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat mat_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };

// 텍스처 변수
GLuint textureID;

// 텍스처 이미지 로딩
void LoadTexture() {
    glGenTextures(1, &textureID);  // 텍스처 ID 생성
    glBindTexture(GL_TEXTURE_2D, textureID);  // 텍스처 바인딩

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // 텍스처 축소 필터링 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 텍스처 확대 필터링 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // 텍스처 래핑 방식 설정 (수평 방향)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);  // 텍스처 래핑 방식 설정 (수직 방향)

    // 텍스처 이미지 로딩: 예시로 흰색 텍스처를 사용
    unsigned char texture_data[64 * 64 * 3];
    std::fill(texture_data, texture_data + sizeof(texture_data), 255);  // 모든 값을 255 (흰색)으로 채움

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
}

// 도움말 메시지 표시
void DisplayHelp() {
    if (showHelp) {
        std::cout << "H - 도움말 표시/숨기기" << std::endl;
        std::cout << "ESC - 프로그램 종료" << std::endl;
        std::cout << "화살표 키: 물체 회전 제어" << std::endl;
    }
}

// 광원 설정 (아침 햇빛과 석양)
void SetupLighting() {
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 활성화
}

// 원통 그리기 (GLU 없이)
void DrawCylinder(float radius, float height, int slices) {
    float angleStep = 2 * M_PI / slices;

    // 원통의 측면 그리기
    for (int i = 0; i < slices; ++i) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        float x1 = radius * cos(angle1);
        float y1 = radius * sin(angle1);

        float x2 = radius * cos(angle2);
        float y2 = radius * sin(angle2);

        // 원통 측면 삼각형
        glBegin(GL_TRIANGLES);
        glVertex3f(x1, y1, 0.0f);
        glVertex3f(x2, y2, 0.0f);
        glVertex3f(x2, y2, height);

        glVertex3f(x1, y1, 0.0f);
        glVertex3f(x2, y2, height);
        glVertex3f(x1, y1, height);
        glEnd();
    }

    // 원통의 위/아래 원 그리기
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // 원의 중심 (바닥)
    for (int i = 0; i <= slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height); // 원의 중심 (위)
    for (int i = 0; i <= slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, height);
    }
    glEnd();
}

// 원뿔 그리기 (GLU 없이)
void DrawCone(float radius, float height, int slices) {
    float angleStep = 2 * M_PI / slices;

    // 원뿔의 원형 바닥 그리기 (원)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);  // 원의 중심
    for (int i = 0; i <= slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    // 원뿔의 측면 그리기
    for (int i = 0; i < slices; ++i) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        float x1 = radius * cos(angle1);
        float y1 = radius * sin(angle1);

        float x2 = radius * cos(angle2);
        float y2 = radius * sin(angle2);

        // 측면 삼각형
        glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 0.0f, height);  // 원뿔의 꼭대기
        glVertex3f(x1, y1, 0.0f);  // 첫 번째 점
        glVertex3f(x2, y2, 0.0f);  // 두 번째 점
        glEnd();
    }
}

// 나무 그리기 (원통 + 원뿔)
void DrawTree(float x, float z) {
    glPushMatrix(); // 변환 시작
    glTranslatef(x, 0.0f, z); // 나무 위치 설정

    // 나무 줄기 (원통)
    glColor3f(0.8f, 0.5f, 0.2f); // 갈색
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // 위치 조정
    DrawCylinder(0.1f, 1.0f, 32); // 원통
    glPopMatrix();

    // 나무 가지 (원뿔)
    glColor3f(0.0f, 1.0f, 0.0f); // 초록색
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f); // 위치 조정
    DrawCone(0.3f, 1.0f, 32); // 원뿔
    glPopMatrix();

    glPopMatrix(); // 변환 끝
}

// 공원 길 그리기
void DrawPath() {
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.1f); // 갈색

    glBegin(GL_QUADS);
    glVertex3f(-5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, 5.0f);
    glVertex3f(-5.0f, 0.0f, 5.0f);
    glEnd();

    glPopMatrix();
}

// 입간판 그리기 (텍스처 매핑 사용)
void DrawSign() {
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f); // 입간판 위치

    glBindTexture(GL_TEXTURE_2D, textureID); // 텍스처 적용
    glBegin(GL_QUADS);
    // 텍스처 매핑된 사각형
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.0f);
    glEnd();

    glPopMatrix();
}

// 화면 그리기
void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 화면 초기화

    glLoadIdentity(); // 기본 좌표계로 리셋

    gluLookAt(0.0f, -5.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); // 카메라 설정

    SetupLighting(); // 조명 설정

    DrawPath();  // 공원 길 그리기
    DrawTree(-2.0f, 0.0f);  // 나무 1
    DrawTree(2.0f, 2.0f);   // 나무 2
    DrawSign(); // 입간판 그리기

    DisplayHelp(); // 도움말 표시

    glutSwapBuffers(); // 더블 버퍼링
}

// 키보드 입력 처리
void Keyboard(unsigned char key, int x, int y) {
    if (key == 27) {  // ESC 키로 종료
        exit(0);
    }
    else if (key == 'h' || key == 'H') {
        showHelp = !showHelp;  // H 키로 도움말 표시/숨기기
    }
}

// 화면 크기 조정
void Reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 200.0f); // 원근 투영
    glMatrixMode(GL_MODELVIEW);
}

// 타이머 함수 (회전)
void Timer(int value) {
    angle += 1.0f;  // 각도 증가
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    glutPostRedisplay(); // 화면 갱신
    glutTimerFunc(16, Timer, 0); // 16ms마다 호출
}

// 프로그램 초기화
void Init() {
    glEnable(GL_TEXTURE_2D); // 텍스처 사용
    LoadTexture();  // 텍스처 로딩
    glEnable(GL_LIGHTING);  // 조명 활성화
    glEnable(GL_LIGHT0);  // 첫 번째 광원 활성화
    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 활성화
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 배경 색상을 흰색으로 설정
}

// main 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 더블 버퍼링, RGB, 깊이 버퍼
    glutInitWindowSize(800, 600); // 창 크기
    glutCreateWindow("공원 장면"); // 창 생성

    Init();  // 초기화

    glutDisplayFunc(Display);  // 화면 그리기 함수 등록
    glutReshapeFunc(Reshape);  // 화면 크기 조정 함수 등록
    glutKeyboardFunc(Keyboard);  // 키보드 입력 처리 함수 등록
    glutTimerFunc(16, Timer, 0);  // 타이머 함수 등록

    glutMainLoop();  // GLUT 메인 루프 시작
    return 0;
}
