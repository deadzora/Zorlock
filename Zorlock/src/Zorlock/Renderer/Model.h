#pragma once
#include "Mesh.h"
#include "Zorlock/Core/Timestep.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"



namespace Zorlock
{
	class MeshRenderer;
	class Skeleton;

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


	enum class ZorlockPrimitiveType
	{
		None,
		Quad,
		Cube,
		Cylinder,
		Sphere,
		Cone
	};

	class ZModel
	{
	public:
		~ZModel();
		ZModel();
		ZModel(ZorlockPrimitiveType primitive,Ref<MeshRenderer> renderer, uint32_t segments = 12);
		ZModel(const std::string& name,const std::string& modelfile);
		ZModel(const std::string& name, const std::string& modelfile, Ref<MeshRenderer> renderer, float scale = 1.0f);
		virtual void Update(Timestep ts);
		virtual void Draw();
		virtual void Destroy();
		void SetMeshRenderer(Ref<MeshRenderer> m);
		void CreateCube();
		void CreateQuad();
		void CreateSphere(uint32_t segments);
		void CreateCylinder(uint32_t segments);
		void CreateCone(uint32_t segments);
		Ref<Mesh> CreateMesh();
		void AddMesh(Ref<Mesh> mesh);
		void RemoveMesh(Ref<Mesh> mesh);
		Ref<Mesh> GetMesh(uint32_t index);
		std::string name;
	protected:
		float loadscale;
		Ref<MeshRenderer> meshRenderer;
		std::vector<Ref<Mesh>> m_meshes;
		Ref<Skeleton> m_skeleton;



		void ProcessNode(aiNode* node, const aiScene* scene, const MATRIX4& parentTransformMatrix);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, const MATRIX4& transformMatrix);
		void LoadMaterialTextures(Ref<Material> material, aiMaterial* pMaterial, aiTextureType textype, const aiScene* pscene);
		AssimpTextureStorageType DetermineTextureStorageType(const aiScene* pscene, aiMaterial* pmaterial, unsigned int index, aiTextureType textype);
		int GetTextureIndex(aiString* pStr);
		friend class MeshRenderer;
	};

}

#define ZLMODEL Zorlock::ZModel