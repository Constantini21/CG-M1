#pragma once
#ifndef LOADER_H
#define LOADER_H

#define EDITING_VERTEX 0
#define EDITING_TEXTURE 1
#define EDITING_NORMAL 2

using namespace std;

#include <string>
#include <fstream>
#include <iostream>
#include<GL/glut.h>

#include "classes.h"

void onInitGL();
void display();
void redraw(int);
void reshape(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);
void keyboard(int, int, int);

Vector3 translate(Vector3, Vector3);
Vector3 scale(Vector3, double);
Vector3 rotate(Vector3, Vector3);

void counterOBJTypes(string, ObjData&);
int counterByType(string, string);
void getVertexFace(string, ObjData&);
void getVertexByType(string, ObjData&, string);
void getFace(string, ObjData&);
int mtlCounter(string);
void loadOBJ(ObjData&, string);
#endif