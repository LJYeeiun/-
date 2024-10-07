#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int FlatShaded = 0;
int Wireframed = 0;
int ViewX = 0, ViewY = 0;

void InitLight() {
    GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 15.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyMouseMove(GLint X, GLint Y) {
    // 마우스 움직임에 따라 ViewX, ViewY 값 변경
    ViewX = X;
    ViewY = Y;

    glutPostRedisplay();  // 화면 다시 그리기
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': case '\033':
        exit(0);
        break;
    case 's':
        if (FlatShaded) {
            FlatShaded = 0;
            glShadeModel(GL_SMOOTH);
        }
        else {
            FlatShaded = 1;
            glShadeModel(GL_FLAT);
        }
        glutPostRedisplay();
        break;
    case 'w':
        if (Wireframed) {
            Wireframed = 0;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else {
            Wireframed = 1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        glutPostRedisplay();
        break;
    }
}

void DrawTable() {
    // 바닥 그리기
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, 1.0);
    glEnd();

    // 탁자 상판 그리기
    glPushMatrix();
    glTranslatef(0.0, 0.2, 0.0); // 상판을 위로 이동
    glScalef(0.6, 0.05, 0.6);
    glutSolidCube(1.0); // 상판
    glPopMatrix();

    // 탁자 다리 그리기
    glPushMatrix();
    glTranslatef(-0.25, 0.1, -0.25); // 첫 번째 다리
    glScalef(0.05, 0.2, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25, 0.1, -0.25); // 두 번째 다리
    glScalef(0.05, 0.2, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, 0.1, 0.25); // 세 번째 다리
    glScalef(0.05, 0.2, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25, 0.1, 0.25); // 네 번째 다리
    glScalef(0.05, 0.2, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 카메라 시점 조정 (마우스 X, Y 값 사용)
    gluLookAt(0.0 + ViewX * 0.01, 0.5 + ViewY * 0.01, 2.0,  // 카메라 위치
        0.0, 0.0, 0.0,                                // 카메라가 보는 지점
        0.0, 1.0, 0.0);                               // 위쪽 방향

    // 바닥과 탁자 그리기
    DrawTable();

    // 탁자 위에 다양한 물체 그리기
    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0); // 탁자 위로 물체 이동
    glutSolidTeapot(0.1); // 찻주전자
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15, 0.25, 0.15); // 다른 위치에 구 추가
    glutSolidSphere(0.07, 20, 20); // 구
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.15, 0.25, -0.15); // 다른 위치에 정육면체 추가
    glutSolidCube(0.1); // 정육면체
    glPopMatrix();

    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 10.0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Table with Objects");
    glClearColor(0.4, 0.4, 0.4, 0.0);
    InitLight();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutPassiveMotionFunc(MyMouseMove);  // 마우스가 움직일 때 카메라 시점 변경
    glutReshapeFunc(MyReshape);
    glutMainLoop();
}
