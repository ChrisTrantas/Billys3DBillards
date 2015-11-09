#ifndef SCENELOADER_H
#define SCENELOADER_H
#include <vector>
#include <assimp/Importer.h>
#include <assimp/scene.h>
#include <assimp/postProcess.h>
#include "mesh.h"

class sceneLoader
{
	std::vector<mesh*> meshes;
	void recursiveProcess(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* mesh, const aiScene* scene);
	unsigned int loadTexture(const char* filename);
public:
	meshLoader(const char* filename);
	~meshLoader();
	void draw(unsigned int programId);
	std::vector<mesh>*& getMeshes();
};

#endif