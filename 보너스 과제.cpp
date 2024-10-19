#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

static int Day = 0, Time = 0;

void InitLighting() {
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 }; // 빛의 위치
    glEnable(GL_LIGHTING); // 조명 활성화
    glEnable(GL_LIGHT0);   // 기본 조명
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 깊이 버퍼 초기화
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 카메라 설정: 위에서 내려다보는 시점 (Y축 상에서 X-Z 평면을 내려다봄)
    gluLookAt(0.0, 4.0, 0.0,  // 카메라 위치를 더 멀리 설정
        0.0, 0.0, 0.0,  // 원점(태양)을 바라봄
        0.0, 0.0, 1.0); // 상단 방향은 Z축을 향함

    // 태양 그리기 (중심에 고정)
    glDisable(GL_LIGHTING); // 태양 자체는 발광체로, 조명 영향을 받지 않도록 설정
    glColor3f(1.0, 0.8, 0.0);  // 노란색 태양
    glutSolidSphere(0.3, 20, 16); // 태양 구체 크기 약간 증가
    glEnable(GL_LIGHTING); // 다시 조명 활성화

    // 지구의 수평 공전 (X-Z 평면에서)
    glPushMatrix();
    glRotatef((GLfloat)Day, 0.0, 1.0, 0.0); // Y축을 기준으로 지구 공전
    glTranslatef(1.5, 0.0, 0.0);           // 태양에서 떨어진 거리 증가
    glColor3f(0.2, 0.6, 1.0);              // 파란 지구 색상
    glutSolidSphere(0.15, 10, 8);          // 지구 구체 크기 증가

    // 달의 수평 공전 (지구 주위를 돈다)
    glPushMatrix();
    glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // 지구 주위를 공전
    glTranslatef(0.4, 0.0, 0.0);           // 지구에서 떨어진 거리 증가
    glColor3f(0.8, 0.8, 0.8);              // 회색 달
    glutSolidSphere(0.06, 10, 8);          // 달 구체 크기 증가
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'd':
        Day = (Day + 5) % 360;  // 지구 공전 속도
        glutPostRedisplay();
        break;
    case 't':
        Time = (Time + 10) % 360;  // 달 공전 속도
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 깊이 버퍼 사용
    glutInitWindowSize(800, 800);  // 창 크기 확대
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System: Enlarged Background");

    glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
    glClearColor(0.0, 0.0, 0.0, 1.0); // 배경을 검은색으로 설정

    InitLighting(); // 조명 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 10.0); // 시야각 확대: 60도

    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}
