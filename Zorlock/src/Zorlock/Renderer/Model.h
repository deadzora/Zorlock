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
	class Bone;

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
		Ref<Bone> AddBone(std::string name = "Bone", Ref<Transform> parent = nullptr);
		Ref<Bone> GetBone(uint32_t i);
		Ref<Bone> GetBone(std::string name);
		size_t GetSkeletonSize();
		std::string name;
	protected:
		float loadscale;
		Ref<MeshRenderer> meshRenderer;
		std::vector<Ref<Mesh>> m_meshes;
		Ref<Skeleton> m_skeleton;


		void ProcessMeshes(aiNode* node, const aiScene* scene);
		void NodeChild(aiNode* node, const aiScene* scene);
		void ProcessNode(aiNode* node, const aiScene* scene, const MATRIX4& parentTransformMatrix, Ref<Bone> parent = nullptr);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, const MATRIX4& nodetransform = MATRIX4::IDENTITY());
		void LoadMaterialTextures(Ref<Material> material, aiMaterial* pMaterial, aiTextureType textype, const aiScene* pscene);
		AssimpTextureStorageType DetermineTextureStorageType(const aiScene* pscene, aiMaterial* pmaterial, unsigned int index, aiTextureType textype);
		int GetTextureIndex(aiString* pStr);
		friend class MeshRenderer;
	};

}

#define ZLMODEL Zorlock::ZModel