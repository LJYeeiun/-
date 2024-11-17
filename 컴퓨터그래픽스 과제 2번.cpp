#include <GL/glut.h> // OpenGL�� GLUT ���̺귯��

// ȸ�� ���� �� ������ ����
GLfloat rtri = 0.0f; // �Ƕ�̵� ȸ�� ����
GLfloat rquad = 0.0f; // ť�� ȸ�� ����
GLfloat scale = 1.0f; // ũ�� ���� ����

// ȭ�� ũ��
int width = 800;
int height = 600;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ȭ�� �� ���� ���� �ʱ�ȭ
    glLoadIdentity(); // �� �� ��� �ʱ�ȭ

    // ī�޶� ��ġ �� ���� ����
    gluLookAt(0.0f, 0.0f, 5.0f, // ī�޶� ��ġ
        0.0f, 0.0f, 0.0f, // �ٶ󺸴� ���� (����)
        0.0f, 1.0f, 0.0f); // �� ����

    // �Ƕ�̵� �׸���
    glLoadIdentity(); // �� �� ��� �ʱ�ȭ
    glTranslatef(-1.5f, 0.0f, -6.0f); // �Ƕ�̵� ��ġ�� �̵�
    glRotatef(rtri, 0.0f, 1.0f, 0.0f); // �Ƕ�̵� ȸ��
    glScalef(scale, scale, scale); // �Ƕ�̵� ũ�� ����

    glBegin(GL_TRIANGLES); // �ﰢ�� ����
    glColor3f(1.0f, 0.0f, 0.0f); // ������
    glVertex3f(0.0f, 1.0f, 0.0f); // �Ƕ�̵� �����
    glColor3f(0.0f, 1.0f, 0.0f); // �ʷϻ�
    glVertex3f(-1.0f, -1.0f, 1.0f); // �Ƕ�̵� ����
    glColor3f(0.0f, 0.0f, 1.0f); // �Ķ���
    glVertex3f(1.0f, -1.0f, 1.0f); // �Ƕ�̵� ������
    glColor3f(1.0f, 0.0f, 0.0f); // ������
    glVertex3f(0.0f, 1.0f, 0.0f); // �Ƕ�̵� �����
    glColor3f(0.0f, 0.0f, 1.0f); // �Ķ���
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // �ʷϻ�
    glVertex3f(1.0f, -1.0f, -1.0f); // �Ƕ�̵� �޸�

    glColor3f(1.0f, 0.0f, 0.0f); // ������
    glVertex3f(0.0f, 1.0f, 0.0f); // �Ƕ�̵� �����
    glColor3f(0.0f, 1.0f, 0.0f); // �ʷϻ�
    glVertex3f(1.0f, -1.0f, -1.0f); // �Ƕ�̵� �޸�
    glColor3f(0.0f, 0.0f, 1.0f); // �Ķ���
    glVertex3f(-1.0f, -1.0f, -1.0f); // �Ƕ�̵� ���ʸ�

    glColor3f(1.0f, 0.0f, 0.0f); // ������
    glVertex3f(0.0f, 1.0f, 0.0f); // �Ƕ�̵� �����
    glColor3f(0.0f, 1.0f, 0.0f); // �ʷϻ�
    glVertex3f(-1.0f, -1.0f, -1.0f); // �Ƕ�̵� ���ʸ�
    glColor3f(0.0f, 0.0f, 1.0f); // �Ķ���
    glVertex3f(-1.0f, -1.0f, 1.0f); // �Ƕ�̵� �����ʸ�
    glEnd();

    // ť�� �׸���
    glLoadIdentity(); // �� �� ��� �ʱ�ȭ
    glTranslatef(1.5f, 0.0f, -7.0f); // ť�� ��ġ�� �̵�
    glRotatef(rquad, 1.0f, 1.0f, 1.0f); // ť�� ȸ��
    glScalef(scale, scale, scale); // ť�� ũ�� ����

    glBegin(GL_QUADS); // ���簢�� ����
    glColor3f(1.0f, 0.0f, 0.0f); // ���� ����
    glVertex3f(1.0f, 1.0f, -1.0f); // ���� ����
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glColor3f(0.0f, 1.0f, 0.0f); // �޸� ����
    glVertex3f(1.0f, 1.0f, 1.0f); // �޸�
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 1.0f); // ���� ����
    glVertex3f(-1.0f, 1.0f, 1.0f); // ����
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 0.0f); // ������ ����
    glVertex3f(1.0f, 1.0f, 1.0f); // ������
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    glColor3f(1.0f, 0.0f, 1.0f); // ���� ����
    glVertex3f(1.0f, 1.0f, 1.0f); // ����
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 1.0f); // �Ʒ��� ����
    glVertex3f(1.0f, -1.0f, 1.0f); // �Ʒ���
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glutSwapBuffers(); // ���� ��ȯ
}

void timer(int value) {
    rtri += 2.0f; // �Ƕ�̵� ȸ�� �ӵ�
    rquad -= 2.0f; // ť�� ȸ�� �ӵ�
    glutPostRedisplay(); // ȭ�� ���� ��ħ
    glutTimerFunc(16, timer, 0); // �� 60fps
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h); // ����Ʈ ����
    glMatrixMode(GL_PROJECTION); // ���� ��� ���
    glLoadIdentity(); // �ʱ�ȭ
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f); // ���� ����
    glMatrixMode(GL_MODELVIEW); // �� �� ��� ���� ����
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT �ʱ�ȭ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ���÷��� ��� ����
    glutInitWindowSize(width, height); // ������ ũ�� ����
    glutCreateWindow("3D Shapes with Transformations"); // ������ ����

    glEnable(GL_DEPTH_TEST); // ���� �׽�Ʈ Ȱ��ȭ
    glutDisplayFunc(display); // ���÷��� �Լ� ����
    glutReshapeFunc(reshape); // �������� �Լ� ����
    glutTimerFunc(0, timer, 0); // Ÿ�̸� �Լ� ����

    glutMainLoop(); // GLUT ���� ���� ����
    return 0;
}
