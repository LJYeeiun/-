#include <GL/glut.h> // OpenGL과 GLUT 라이브러리

// 회전 각도 및 스케일 변수
GLfloat rtri = 0.0f; // 피라미드 회전 각도
GLfloat rquad = 0.0f; // 큐브 회전 각도
GLfloat scale = 1.0f; // 크기 조절 변수

// 화면 크기
int width = 800;
int height = 600;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 화면 및 깊이 버퍼 초기화
    glLoadIdentity(); // 모델 뷰 행렬 초기화

    // 카메라 위치 및 방향 설정
    gluLookAt(0.0f, 0.0f, 5.0f, // 카메라 위치
        0.0f, 0.0f, 0.0f, // 바라보는 방향 (원점)
        0.0f, 1.0f, 0.0f); // 업 벡터

    // 피라미드 그리기
    glLoadIdentity(); // 모델 뷰 행렬 초기화
    glTranslatef(-1.5f, 0.0f, -6.0f); // 피라미드 위치로 이동
    glRotatef(rtri, 0.0f, 1.0f, 0.0f); // 피라미드 회전
    glScalef(scale, scale, scale); // 피라미드 크기 조정

    glBegin(GL_TRIANGLES); // 삼각형 시작
    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f); // 피라미드 꼭대기
    glColor3f(0.0f, 1.0f, 0.0f); // 초록색
    glVertex3f(-1.0f, -1.0f, 1.0f); // 피라미드 왼쪽
    glColor3f(0.0f, 0.0f, 1.0f); // 파란색
    glVertex3f(1.0f, -1.0f, 1.0f); // 피라미드 오른쪽
    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f); // 피라미드 꼭대기
    glColor3f(0.0f, 0.0f, 1.0f); // 파란색
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // 초록색
    glVertex3f(1.0f, -1.0f, -1.0f); // 피라미드 뒷면

    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f); // 피라미드 꼭대기
    glColor3f(0.0f, 1.0f, 0.0f); // 초록색
    glVertex3f(1.0f, -1.0f, -1.0f); // 피라미드 뒷면
    glColor3f(0.0f, 0.0f, 1.0f); // 파란색
    glVertex3f(-1.0f, -1.0f, -1.0f); // 피라미드 왼쪽면

    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f); // 피라미드 꼭대기
    glColor3f(0.0f, 1.0f, 0.0f); // 초록색
    glVertex3f(-1.0f, -1.0f, -1.0f); // 피라미드 왼쪽면
    glColor3f(0.0f, 0.0f, 1.0f); // 파란색
    glVertex3f(-1.0f, -1.0f, 1.0f); // 피라미드 오른쪽면
    glEnd();

    // 큐브 그리기
    glLoadIdentity(); // 모델 뷰 행렬 초기화
    glTranslatef(1.5f, 0.0f, -7.0f); // 큐브 위치로 이동
    glRotatef(rquad, 1.0f, 1.0f, 1.0f); // 큐브 회전
    glScalef(scale, scale, scale); // 큐브 크기 조정

    glBegin(GL_QUADS); // 정사각형 시작
    glColor3f(1.0f, 0.0f, 0.0f); // 앞쪽 색상
    glVertex3f(1.0f, 1.0f, -1.0f); // 앞쪽 정점
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glColor3f(0.0f, 1.0f, 0.0f); // 뒷면 색상
    glVertex3f(1.0f, 1.0f, 1.0f); // 뒷면
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 1.0f); // 왼쪽 색상
    glVertex3f(-1.0f, 1.0f, 1.0f); // 왼쪽
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 0.0f); // 오른쪽 색상
    glVertex3f(1.0f, 1.0f, 1.0f); // 오른쪽
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    glColor3f(1.0f, 0.0f, 1.0f); // 위쪽 색상
    glVertex3f(1.0f, 1.0f, 1.0f); // 위쪽
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 1.0f); // 아래쪽 색상
    glVertex3f(1.0f, -1.0f, 1.0f); // 아래쪽
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glutSwapBuffers(); // 버퍼 교환
}

void timer(int value) {
    rtri += 2.0f; // 피라미드 회전 속도
    rquad -= 2.0f; // 큐브 회전 속도
    glutPostRedisplay(); // 화면 새로 고침
    glutTimerFunc(16, timer, 0); // 약 60fps
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h); // 뷰포트 설정
    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드
    glLoadIdentity(); // 초기화
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f); // 원근 투영
    glMatrixMode(GL_MODELVIEW); // 모델 뷰 행렬 모드로 복귀
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 디스플레이 모드 설정
    glutInitWindowSize(width, height); // 윈도우 크기 설정
    glutCreateWindow("3D Shapes with Transformations"); // 윈도우 생성

    glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
    glutDisplayFunc(display); // 디스플레이 함수 설정
    glutReshapeFunc(reshape); // 리사이즈 함수 설정
    glutTimerFunc(0, timer, 0); // 타이머 함수 설정

    glutMainLoop(); // GLUT 메인 루프 실행
    return 0;
}
