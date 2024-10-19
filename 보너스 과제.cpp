#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

static int Day = 0, Time = 0;

void InitLighting() {
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 }; // ���� ��ġ
    glEnable(GL_LIGHTING); // ���� Ȱ��ȭ
    glEnable(GL_LIGHT0);   // �⺻ ����
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� ���� �ʱ�ȭ
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ī�޶� ����: ������ �����ٺ��� ���� (Y�� �󿡼� X-Z ����� �����ٺ�)
    gluLookAt(0.0, 4.0, 0.0,  // ī�޶� ��ġ�� �� �ָ� ����
        0.0, 0.0, 0.0,  // ����(�¾�)�� �ٶ�
        0.0, 0.0, 1.0); // ��� ������ Z���� ����

    // �¾� �׸��� (�߽ɿ� ����)
    glDisable(GL_LIGHTING); // �¾� ��ü�� �߱�ü��, ���� ������ ���� �ʵ��� ����
    glColor3f(1.0, 0.8, 0.0);  // ����� �¾�
    glutSolidSphere(0.3, 20, 16); // �¾� ��ü ũ�� �ణ ����
    glEnable(GL_LIGHTING); // �ٽ� ���� Ȱ��ȭ

    // ������ ���� ���� (X-Z ��鿡��)
    glPushMatrix();
    glRotatef((GLfloat)Day, 0.0, 1.0, 0.0); // Y���� �������� ���� ����
    glTranslatef(1.5, 0.0, 0.0);           // �¾翡�� ������ �Ÿ� ����
    glColor3f(0.2, 0.6, 1.0);              // �Ķ� ���� ����
    glutSolidSphere(0.15, 10, 8);          // ���� ��ü ũ�� ����

    // ���� ���� ���� (���� ������ ����)
    glPushMatrix();
    glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // ���� ������ ����
    glTranslatef(0.4, 0.0, 0.0);           // �������� ������ �Ÿ� ����
    glColor3f(0.8, 0.8, 0.8);              // ȸ�� ��
    glutSolidSphere(0.06, 10, 8);          // �� ��ü ũ�� ����
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'd':
        Day = (Day + 5) % 360;  // ���� ���� �ӵ�
        glutPostRedisplay();
        break;
    case 't':
        Time = (Time + 10) % 360;  // �� ���� �ӵ�
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ���� ���� ���
    glutInitWindowSize(800, 800);  // â ũ�� Ȯ��
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System: Enlarged Background");

    glEnable(GL_DEPTH_TEST); // ���� �׽�Ʈ Ȱ��ȭ
    glClearColor(0.0, 0.0, 0.0, 1.0); // ����� ���������� ����

    InitLighting(); // ���� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 10.0); // �þ߰� Ȯ��: 60��

    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}
