#define VERTEX 0
#define TEXTURE 1
#define NORMAL 2

#include <string>
#include <fstream>
#include <iostream>

#include "classes.h"

void counterOBJTypes(string objFileName, ObjData& objData) {
	objData.facesLength = 0; objData.vertexLength = 0; objData.normalsLength = 0; objData.textsLength = 0;
	ifstream file(objFileName);
	

		if (file.is_open()) {
			string type;
			
			while (file >> type) {
				if (type == "v") {
					objData.vertexLength += 1;
				} else if (type == "vn") {
					objData.normalsLength += 1;
				} else if (type == "f") {
					objData.facesLength += 1;
				} else if (type == "vt") {
					objData.textsLength += 1;
				}
			}

		file.close();
	}
}

int counterByType(string objFileName, string target) {
	ifstream file(objFileName);
	string type = "", line;
	int counter = 0;
	
	while (type != target) {
		file >> type;
		getline(file, line);
	}

	for (int i = 0; line[i + 1] != 0; i++) {
		if (line[i] == ' ' && line[i + 1] != ' ') {
			counter++;
		}
	}

	file.close();
	
	return counter;
}

void getVertexFace(string objFileName, ObjData& objData) {
	ifstream file(objFileName);
	string line;
	string type = "";
	int currentFace = 0;

	while (file >> type) {
		getline(file, line);
		
		if (type == "f") {
			int counter = 0;
			
			for (int i = 0; line[i + 1] != 0; i++) {
				if (line[i] == ' ' && line[i + 1] != ' ') {
					counter++;
				}
			}

			objData.faces[currentFace].vertexPerFace = counter;
			objData.faces[currentFace].vertex = new unsigned short int[counter];
			objData.faces[currentFace].texture = new unsigned short int[counter];
			objData.faces[currentFace].normal = new unsigned short int[counter];
			currentFace++;
		}
	}

	file.close();
}

void getVertexByType(string objFileName, ObjData& objData, string target) {
	if (obj.normalsLength == 0 && target == "vn") return;
	int numElements = counterByType(objFileName, target);
	
	double maxX = -10000, minX = 10000;
	double maxY = -10000, minY = 10000;
	double maxZ = -10000, minZ = 10000;
	
	string type, x, y, z, w, currentMaterial;
	int current = 0;
	ifstream file(objFileName);
	
	while (file >> type) {
		if (type == target) {
			if (target == "usemtl") {
				file >> x;
			} else if (numElements == 2) {
				file >> x >> y;
			} else if (numElements == 3) {
				file >> x >> y >> z;
			} else if (numElements == 4) {
				file >> x >> y >> z >> w;
			}

			if (target == "v") {
				// x
				objData.vertex[current].x = stod(x);
				if (stod(x) > maxX) maxX = stod(x);
				if (stod(x) < minX) minX = stod(x);
				// y
				objData.vertex[current].y = stod(y);
				if (stod(y) > maxY) maxY = stod(y);
				if (stod(y) < minY) minY = stod(y);
				
				// z
				objData.vertex[current].z = stod(z);
				if (stod(z) > maxZ) maxZ = stod(z);
				if (stod(z) < minZ) minZ = stod(z);
			} else if (target == "vn") {
				objData.normals[current].x = stod(x);
				objData.normals[current].y = stod(y);
				objData.normals[current].z = stod(z);
			} else if (target == "usemtl") {
				currentMaterial = x;
			} else if (target == "vt") {
				objData.textures[current].coord.x = stod(x);
				objData.textures[current].coord.y = stod(y);
				objData.textures[current].material = currentMaterial;
			}

			current++;
		}
	}

	if (target == "v") {
		objData.offset.x = minX + ((maxX - minX) / 2);
		objData.offset.y = minY + ((maxY - minY) / 2);
		objData.offset.z = minZ + ((maxZ - minZ) / 2);
		objData.size.x = maxX - minX;
		objData.size.y = maxY - minY;
		objData.size.z = maxZ - minZ;
	}

	file.close();
}

void getFace(string objFileName, ObjData& objData) {
	ifstream file(objFileName);
	
	int currentVertex = -1, vertexLengthPassed = 0,  currentFace = 0, normalsLengthPassed = 0, textsLengthPassed = 0;
	string line, temp, type = "";
	
	while (file >> type) {
		getline(file, line);
		int editing = NORMAL;

		if (type == "v") vertexLengthPassed++;
		if (type == "vn") normalsLengthPassed++;
		if (type == "vt") textsLengthPassed++;
		
		if (type == "f") {
			for (int i = 1; line[i] != 0; i++) {
				if (currentVertex == obj.faces[currentFace].vertexPerFace) {
					currentFace++;
					currentVertex = 0;
				}

				if (line[i - 1] == ' ' && line[i] != ' ') {
					editing = VERTEX;
					temp = "";
					currentVertex++;
				} else if (editing == VERTEX && line[i - 1] == '/') {
					editing = TEXTURE;
					temp = "";
				} else if (editing == TEXTURE && line[i - 1] == '/') {
					editing = NORMAL;
					temp = "";
				}

				if (!(line[i] == '/' || line[i] == ' ')) {
					temp += line[i];
				} else if (temp != "") {
					if (editing == VERTEX) {
						objData.faces[currentFace].vertex[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : vertexLengthPassed - abs(stoi(temp));
					} else if (editing == TEXTURE) {
						objData.faces[currentFace].texture[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : textsLengthPassed - abs(stoi(temp));
					} else if (editing == NORMAL) {
						objData.faces[currentFace].normal[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : normalsLengthPassed - abs(stoi(temp));
					}
				}
			}

			objData.faces[currentFace].normal[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : normalsLengthPassed - abs(stoi(temp));
		}
	}
}

int mtlCounter(string objFileName) {
	ifstream file(objFileName);

	string type = "", line;
	int count = 0;
	
	while (file >> type) {
		if (type == "newmtl") {
			count++;
		}
	}

	return count;
}

void loadOBJ(ObjData& obj, string objFileName) {
	counterOBJTypes(objFileName, obj);
	
	if (obj.vertexLength) {
		obj.vertex = new Vector3[obj.vertexLength];
		obj.normals = new Vector3[obj.normalsLength];
		obj.faces = new Face[obj.facesLength];
		obj.textures = new Texture[obj.textsLength];

		getVertexByType(objFileName, obj, "v");
		getVertexByType(objFileName, obj, "vn");

		getVertexFace(objFileName, obj);
		getFace(objFileName, obj);
	}
}