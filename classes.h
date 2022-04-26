#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>

using namespace std;

class Vector2 {
	public:
		double x;
		double y;

		Vector2() {
			this->x = 0;
			this->y = 0;
		}

		Vector2(double x, double y) {
			this->x = x;
			this->y = y;
		}
};

class Vector3 {
	public:
		double x;
		double y;
		double z;

		Vector3() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		Vector3(double x, double y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
};

struct Face {
	unsigned short int vertexPerFace;
	unsigned short int* vertex;
	unsigned short int* texture;
	unsigned short int* normal;
};

struct Texture {
	Vector2 coord;
	string material;
};

struct ObjData {
	double scale;
	Vector3 angle;
	Vector3 pos;

	int vertexLength;
	int normalsLength;
	int facesLength;
	int textsLength;
	int numMtl;
	unsigned int* textureID;
	Vector3 size;
	Vector3 offset;
	Vector3* vertex;
	Vector3* normals;
	Texture* textures;
	Face* faces;

	ObjData() {
		this->scale = 1;
    this->pos = { 0, 0, -5 };
	}
};

extern ObjData obj;
#endif