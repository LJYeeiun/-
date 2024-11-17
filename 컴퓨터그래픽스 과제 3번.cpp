#include <GL/glut.h>
#include <cmath>

float posX = 0.0f, posY = 10.0f, velocity = 0.0f, gravity = -9.8f; // ��ġ, �ӵ�, �߷�
float radius = 1.0f; // ���� ������
float groundY = -5.0f; // �ٴ��� y ��ġ
bool wireframe = false; // ���̾������� ���
float bounce = 0.8f; // ź�� ��� (0.8�̸� 80%�� �������� ƨ��)

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

    // ī�޶� ��ġ ����
    gluLookAt(0.0, 15.0, 30.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0); // ī�޶� ���� �ٴ��� �� ���̵��� ����

    drawBall();

    glutSwapBuffers();
}

void update(int value) {
    // �߷¿� ���� �ӵ� ��ȭ
    velocity += gravity * 0.1f;

    // ���� ��ġ ��ȭ
    posY += velocity * 0.1f;

    // �ٴڿ� ���� �� �ݻ�
    if (posY - radius <= groundY) {
        posY = groundY + radius; // �ٴڿ� �´���� ��
        velocity = -velocity * bounce; // �ݻ�� �ӵ� (ź�� ��� ����)

        // ���� ���� �۾����ų� ���������
        if (velocity < 0.1f) radius = 1.0f; // ź�� �������� ������ ũ�� ����
    }

    // �ִϸ��̼��� ������ ����
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // ���̾������� ���
        wireframe = true;
        break;
    case 's': // �ָ��� ���
        wireframe = false;
        break;
    case 27: // ESC Ű�� ����
        exit(0);
        break;
    }
}

void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.5, 0.1, 100.0); // ȭ�� ������ 1.5�� �����Ͽ� ���� ȭ���� �����
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); // ������ ũ�⸦ ��� ����
    glutCreateWindow("Bouncing Ball Animation");

    initOpenGL();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
