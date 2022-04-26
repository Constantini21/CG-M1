#include "loader.h"

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < obj.facesLength; i++) {
        glBegin(GL_POLYGON);

        for (int vertex = 0; vertex < obj.faces[i].vertexPerFace; vertex++) {
            Vector3 point = obj.vertex[obj.faces[i].vertex[vertex]];
            Vector3 normal = obj.normals[obj.faces[i].normal[vertex]];

            point = scale(point, obj.scale);
            point = rotate(point, obj.angle);
            point = translate(point, obj.pos);

            glNormal3d(normal.x, normal.y, normal.z);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
    }

    glutSwapBuffers();
}

void onInitGL() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffusedLight[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };

    glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusedLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    GLfloat lightPos[] = { 0.0, 0.0, -5.0, 1.0 };
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void redraw(int value) {
  glutPostRedisplay();
  glutTimerFunc(1000 / 60, redraw, 0);
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, GLfloat((GLfloat)width / (GLfloat)height), 0.1f, 100.0f);
}