#include "mesh.h"

mesh::mesh(std::vector<vertexData>* vd, std::vector<unsigned int>* id, std::vector<textureData>* td){

	data = *vd;
	indicies = *id;
	if (td)
		textures = *td;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(vertexData),
		&data[0], GL_STATIC_DRAW);


	glGenBuffers(1, &IND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int),
		&indicies[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

mesh::~mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IND);
}

void mesh::draw(unsigned int programId)
{
	// attribue vec3 vertex
	int vertex = glGetAttribLocation(programId, "vertex"); // 0
	int normal = glGetAttribLocation(programId, "normal"); // 1
	int tangent = glGetAttribLocation(programId, "tangent"); // 2
	int color = glGetAttribLocation(programId, "color"); // 3
	int UV = glGetAttribLocation(programId, "UV"); // 4

	// texture0
	//texture1...
	std::string str = "texture";
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBIndTexture(GL_TEXTURE_2D, textures[i].id);
		glUniformli(glGetUniformLocation(programId,str+(char)(i + '0')), i);

	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IND);

	glEnableVertextAttribArray(vertex);
	glVertextAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), 0);

	glEnableVertextAttribArray(normal);
	glVertextAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(3*sizeof(float));

	glEnableVertextAttribArray(tangent);
	glVertextAttribPointer(tangent, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(6 * sizeof(float));

	glEnableVertextAttribArray(color);
	glVertextAttribPointer(color, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(9 * sizeof(float));

	glEnableVertextAttribArray(UV);
	glVertextAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(12 * sizeof(float));

	glDrawElements(GL_TRIANGLE, indicces.size(), LG_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vertex);
	glDisableVertexAttribArray(normal);
	glDisableVertexAttribArray(tangent);
	glDisableVertexAttribArray(color);
	glDisableVertexAttribArray(UV);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}