void recursiveProcess(aiNode* node, const aiScene* scene)
{
	//process
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}


	//recursion
	for (int i = 0; i < node->mNumChildren; i++)
	{
		recursiveProcess(node->mChildren[i], scene);
	}
}
void meshLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<vertexData>data;
	std::vector<unsigned int> indices;
	std:: vector<textureData> textures;

	for (int i = 0; i < mNumVerticies; i++)
	{
		vertexData tmp;
		vector3d tmpVec;

		//position
		tmpVec.x = mesh->mVertices[i].x;
		tmpVec.y = mesh->mVertices[i].y;
		tmpVec.z = mesh->mVertices[i].z;
		tmp.position = tmpVec;

		//normals
		tmpVec.x = mesh->mNormals[i].x;
		tmpVec.y = mesh->mNormals[i].y;
		tmpVec.z = mesh->mNormals[i].z;
		tmp.normal = tmpVec;

		//tangent
		if (mesh->mTangetns)
		{
			tmpVec.x = mesh->mTangents[i].x;
			tmpVec.y = mesh->mVertices[i].y;
			tmpVec.z = mesh->mVertices[i].z;
		}
		else
		{
			tmpVec.x = 0;
			tmpVec.y = tempVec.z = 0;
		}
		tmp.tangent = tmpVec;

		//color
		if (mesh->mColors[0])
		{
			tmpVec.x = mesh->mColors[i].x;
			tmpVec.y = mesh->mColors[i].y;
			tmpVec.z = mesh->mColors[i].z;
		}
		else
		{
			tmpVec.x = tmpVec.y = tmpVec.z = 0.7;
		}
		tmp.color = tmpVec;

		//color
		if (mesh->MTextureCoords[0])
		{
			tmpVec.x = mesh->MTextureCoords[i].x;
			tmpVec.y = mesh->MTextureCoords[i].y;
			tmpVec.z = mesh->MTextureCoords[i].z;
		}
		else
		{
			tmpVec.x = tmpVec.y = tmpVec.z = 0.0;
		}
		tmp.U = tmpVec.x;
		tmp.V = tmpVec.y;
		data.push_back(tmp);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) //0..2
		{
			indicies.push_back(face.mIndices[j]);

		}
	}

	aiMaterial* mat = scene - mMaterial[mesh->mMaterialIndex];
	for (int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE, i, &str);
		textureData tmp;
		tmp.id = loadTexture(str.C_Str());
		tmp.type = 0;
		textures.push_back(tmp);
	}
	meshes.push_back(new mesh(data, &indices, &textures));
}
unsigned int meshLoader::loadTexture(const char* filename);


meshLoader::meshLoader(const char* filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, 
		aiProcess_GenSmoothNormals | aiProcess_Triangulate |
		aiProcess_ClalcTangentSpace | aiProcess_FlipUVs);
	if (!scene->mFlags || !scene->mRootNode)
	{
		std::cout << "The file wasnt' successfully opened " << filename << std::endl;
		return;
	}

	recursiveProcess(scene->mRootNode, scene);
	if (mRootNode = null)
};


~meshLoader()
{
	for (int i = 0; i < meshes.size(); i++)
		delete meshes[i];

}
void draw(unsigned int programId)
{
	for (int int = 0; i < meshes.size();i++)
	meshes[i]->draw(programId);
}
std::vector<mesh>*& getMeshes()
{
	return meshes;
}