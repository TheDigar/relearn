#pragma once
#include <Mesh.h>
#include <assimp/scene.h>

class Model
{
public:
	Model(const char* path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);
private:
	// model data
    // model data 
	vector<TextureId> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;

	void loadModel(const string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<TextureId> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);
};

