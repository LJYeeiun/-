#include <GL/glut.h>
#include <cmath>

float posX = 0.0f, posY = 10.0f, velocity = 0.0f, gravity = -9.8f; // 위치, 속도, 중력
float radius = 1.0f; // 공의 반지름
float groundY = -5.0f; // 바닥의 y 위치
bool wireframe = false; // 와이어프레임 모드
float bounce = 0.8f; // 탄성 계수 (0.8이면 80%의 에너지로 튕김)

void drawBall() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    if (wireframe) {
        glutWireSphere(radius, 16, 16);
    }
    else {
        glutSolidSphere(radius, 16, 16);
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 카메라 위치 조정
    gluLookAt(0.0, 15.0, 30.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0); // 카메라를 공과 바닥이 잘 보이도록 설정

    drawBall();

    glutSwapBuffers();
}

void update(int value) {
    // 중력에 의한 속도 변화
    velocity += gravity * 0.1f;

    // 공의 위치 변화
    posY += velocity * 0.1f;

    // 바닥에 닿을 때 반사
    if (posY - radius <= groundY) {
        posY = groundY + radius; // 바닥에 맞닿았을 때
        velocity = -velocity * bounce; // 반사된 속도 (탄성 계수 적용)

        // 점점 공이 작아지거나 길어지도록
        if (velocity < 0.1f) radius = 1.0f; // 탄성 에너지가 적으면 크기 복원
    }

    // 애니메이션의 연속적 갱신
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // 와이어프레임 모드
        wireframe = true;
        break;
    case 's': // 솔리드 모드
        wireframe = false;
        break;
    case 27: // ESC 키로 종료
        exit(0);
        break;
    }
}

void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.5, 0.1, 100.0); // 화면 비율을 1.5로 설정하여 넓은 화면을 만들기
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); // 윈도우 크기를 길게 설정
    glutCreateWindow("Bouncing Ball Animation");

    initOpenGL();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
