#pragma once
#include "Mesh.h"
#include "Zorlock/Core/Timestep.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"



namespace Zorlock
{
	class MeshRenderer;

	enum class AssimpTextureStorageType
	{
		Invalid,
		None,
		EmbeddedIndexCompressed,
		EmbeddedIndexNonCompressed,
		EmbeddedCompressed,
		EmbeddedNonCompressed,
		Disk
	};



	class Model
	{
	public:
		virtual ~Model() {};
		Model(const std::string& name,const std::string& modelfile);
		Model(const std::string& name, const std::string& modelfile, Ref<MeshRenderer> renderer);
		virtual void Update(Timestep ts);
		virtual void Draw();
		virtual void Destroy();
		void SetMeshRenderer(Ref<MeshRenderer> m);

		Ref<Mesh> CreateMesh();
		void AddMesh(Ref<Mesh> mesh);
		void RemoveMesh(Ref<Mesh> mesh);
		Ref<Mesh> GetMesh(uint32_t index);
		std::string name;
	protected:
		Ref<MeshRenderer> meshRenderer;
		std::vector<Ref<Mesh>> m_meshes;
		void ProcessNode(aiNode* node, const aiScene* scene, const MATRIX4& parentTransformMatrix);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, const MATRIX4& transformMatrix);
		void LoadMaterialTextures(Ref<Material> material, aiMaterial* pMaterial, aiTextureType textype, const aiScene* pscene);
		AssimpTextureStorageType DetermineTextureStorageType(const aiScene* pscene, aiMaterial* pmaterial, unsigned int index, aiTextureType textype);
		int GetTextureIndex(aiString* pStr);
		friend class MeshRenderer;
	};

}

#define ZLMODEL Zorlock::Model