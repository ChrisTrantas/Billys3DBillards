#ifndef MESH_H
#define MESH_H
#include <iostream>
#include "GLee.h"
#include <GL/GL.h>
#include <GL/GLU.h>
#include <vector>
#include <string>

class meshClass{
	std::vector<vertexData> data;
	std::vector<textureData> textures;
	std::vector<unsigned int> indicies;
	unsigned int VBO;
	unsigned int IND;
public:
	mesh(std::vector<vertexData>* vd, std::vector<unsigned int>* id, std::vector<textureData>* td = NULL);
	~mesh();
	void draw(unsigned int programId);
};
#endif