#include <GL/glut.h>
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glutMainLoop();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}
