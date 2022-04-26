#include <iostream>
#include <vector>

#include "loader.h"

ObjData obj = ObjData();

int main(int argc, char** argv) {
    loadOBJ(obj, "cubo.obj");

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("OBJ Loader");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000 / 60, redraw, 0);
    glEnable(GL_DEPTH_TEST);
    onInitGL();
    glutMainLoop();
    return 0;
}