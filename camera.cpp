#include "loader.h"

Vector3 translate(Vector3 point, Vector3 pos) {
    point.x += obj.pos.x;
    point.y += obj.pos.y;
    point.z += obj.pos.z;
    return point;
}

Vector3 scale(Vector3 point, double scale) {
    point.x *= obj.scale;
    point.y *= obj.scale;
    point.z *= obj.scale;
    return point;
}

Vector3 rotate(Vector3 point, Vector3 angle) {
    glTranslated(0, 0, 0);
    glTranslated(obj.pos.x, obj.pos.y, obj.pos.z);
    
    double values[3][3][3] = {
        {
            {1, 0, 0},
            {0, cos(angle.x), -sin(angle.x)},
            {0, sin(angle.x),  cos(angle.x)}
        },
        {
            {cos(angle.y), 0, sin(angle.y)},
            {0, 1, 0},
            {-sin(angle.y), 0, cos(angle.y)}
        },
        {
            {cos(angle.z), -sin(angle.z), 0},
            {sin(angle.z),  cos(angle.z), 0},
            {0, 0, 1}
        },
    };

    for (int i = 0; i < 3; i++) {
        Vector3 oldPoint = Vector3(point.x, point.y, point.z);

        point.x = (oldPoint.x * values[i][0][0]) + (oldPoint.y * values[i][0][1]) + (oldPoint.z * values[i][0][2]);
        point.y = (oldPoint.x * values[i][1][0]) + (oldPoint.y * values[i][1][1]) + (oldPoint.z * values[i][1][2]);
        point.z = (oldPoint.x * values[i][2][0]) + (oldPoint.y * values[i][2][1]) + (oldPoint.z * values[i][2][2]);
    }

    return point;
}


void keyboard(int key, int, int) {   
    switch (key) {
        case GLUT_KEY_RIGHT: // →
            obj.angle.y -= 0.1;
            break;
        case GLUT_KEY_LEFT: // ←
            obj.angle.y += 0.1;
            break;
        case GLUT_KEY_UP: // ↑
            obj.angle.x -= 0.1;
            break;
        case GLUT_KEY_DOWN: // ↓
            obj.angle.x -= 0.1;
            break;
    }
}

void keyboard(unsigned char key, int, int) {
    key = towlower(key);
    
    switch (key) {
        case 'w':
            obj.pos.y += 0.5;
            break;
        case 's':
            obj.pos.y -= 0.5;
            break;
        case 'a':
            obj.pos.x -= 0.5;
            break;
        case 'd':
            obj.pos.x += 0.5;

        case 'z':
            obj.angle.z -= 0.5;
            break;
        case 'x':
            obj.angle.z += 0.5;
            break;
        
        case '+': 
            obj.pos.z += 1;
            break;
        case '-':
            obj.pos.z -= 1;
            break;

        case 'o':
            obj.scale -= 0.5;
            break;
        case 'p':
            obj.scale += 0.5;
            break;

        case 't':
            glEnable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
            break;
        case 'y':
            glEnable(GL_LIGHT1);
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT2);
            break;
        case 'u':
            glEnable(GL_LIGHT2);
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            break;
        case 27: // esc
            exit(0);
            break;
    }
}
