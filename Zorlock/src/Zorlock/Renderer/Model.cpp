#include "ZLpch.h"
#include "Model.h"
#include "Zorlock/Renderer/Renderer.h"
#include "Zorlock/Components/MeshRenderer.h"


namespace Zorlock
{
	Model::Model(const std::string& name,const std::string& modelfile) : name(name)
	{
		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(modelfile, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

		if (pScene != NULL)
		{
			this->ProcessNode(pScene->mRootNode, pScene, MATRIX4::IDENTITY());
		}

	}
	Model::Model(const std::string& name, const std::string& modelfile, Ref<MeshRenderer> renderer) : name(name)
	{
		meshRenderer = renderer;

		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(modelfile, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

		if (pScene != NULL)
		{
			this->ProcessNode(pScene->mRootNode, pScene, MATRIX4::IDENTITY());
		}

	}
	void Model::Update(Timestep ts)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			if (meshRenderer != nullptr)
			{
				m_meshes[i]->SetDrawMatrix(m_meshes[i]->GetMatrix() * meshRenderer->parent->transform->GetTransformationMatrix());
				//m_meshes[i]->SetDrawMatrix(MATRIX4::TRS(VECTOR3(0.0f, 0.0f, -10.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(0.0001f, 0.0001f, 0.0001f))); //m_meshes[i]->GetMatrix());// * meshRenderer->parent->transform->GetTransformationMatrix());
			}
		}
	}

	void Model::Draw()
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->Draw();
		}
	}

	ZL_DEPRECATED("Please add mem release commands to vertexarray, vertexbuffer and indexbuffer")
	void Model::Destroy()
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->Destroy();
		}
	}

	void Model::SetMeshRenderer(Ref<MeshRenderer> m)
	{
		Ref<MeshRenderer> mrenderer = m;
		meshRenderer = mrenderer;
	}

	Ref<Mesh> Model::CreateMesh()
	{		
		Ref<Mesh> mesh = Ref<Mesh>(new Mesh());
		if (mesh != nullptr)
		{
			printf("Created Mesh \n");
			m_meshes.push_back(mesh);
			return mesh;
		}
		return nullptr;
	}

	void Model::AddMesh(Ref<Mesh> mesh)
	{
		if (mesh != nullptr)
		{
			m_meshes.push_back(mesh);
		}
	}

	void Model::RemoveMesh(Ref<Mesh> mesh)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			if (m_meshes[i] == mesh)
			{
				m_meshes.erase(m_meshes.begin() + i);
				m_meshes.shrink_to_fit();
				return;
			}
		}
	}

	Ref<Mesh> Model::GetMesh(uint32_t index)
	{
		if (index < m_meshes.size())
		{
			return m_meshes[index];
		}
		return nullptr;
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, const MATRIX4& parentTransformMatrix)
	{
		MATRIX4 nodeMatrix = *reinterpret_cast<MATRIX4*>(&node->mTransformation.a1);
		MATRIX4 nodeTransformMatrix = nodeMatrix * parentTransformMatrix;

		for (UINT i = 0; i < node->mNumMeshes; i++)
		{
			printf("Parsing Mesh! \n");
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->ProcessMesh(mesh, scene, nodeTransformMatrix);
		}

		for (UINT i = 0; i < node->mNumChildren; i++)
		{
			printf("Parsing Node! \n");
			this->ProcessNode(node->mChildren[i], scene, nodeTransformMatrix);

		}
	}

	Ref<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const MATRIX4& transformMatrix)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		UINT nv = 0;
		for (UINT i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;
			vertex.position.w = 1.0f;
			vertex.color.x = 1.0f;
			vertex.color.y = 1.0f;
			vertex.color.z = 1.0f;
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;

			if (mesh->mTextureCoords[0])
			{
				vertex.uvw.x = (float)mesh->mTextureCoords[0][i].x;
				vertex.uvw.y = (float)mesh->mTextureCoords[0][i].y;
			}

			vertices.push_back(vertex);
			nv++;
		}

		for (UINT i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (UINT j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}


		aiString mname;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		mname = material->mProperties[AI_MATKEY_NAME]->mData;

		//create with default shader
		Ref<Material> zmaterial = MaterialLibrary::GetInstance()->CreateMaterial(ShaderLibrary::GetInstance()->GetStandard());

		if (meshRenderer != nullptr)
		{
			meshRenderer->AddMaterial(zmaterial);
			
		}

		zmaterial->GetShader()->Bind();
		LoadMaterialTextures(zmaterial, material, aiTextureType::aiTextureType_DIFFUSE, scene);

		Ref<Mesh> zmesh = CreateMesh();
		zmesh->SetMatrix(transformMatrix);
		zmesh->vcount = nv;
		printf("Setting Mesh Data vertices: %u indices %d \n", nv, (uint32_t)indices.size());
		zmesh->CreateVertexArray();
		zmesh->CreateVertexBuffer(vertices.data(), (uint32_t)(sizeof(vertices.data())));
		zmesh->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial);
		zmesh->CreateIndexBuffer(indices.data(), indices.size());
		zmesh->Bind();


		return zmesh;
	}

	void Model::LoadMaterialTextures(Ref<Material> material, aiMaterial* pMaterial, aiTextureType textype, const aiScene* pscene)
	{

		AssimpTextureStorageType storetype = AssimpTextureStorageType::Invalid;
		unsigned int textureCount = pMaterial->GetTextureCount(textype);
		printf("Texture Count: %u ", textureCount);
		if (textureCount == 0)
		{
			storetype = AssimpTextureStorageType::None;
			aiColor3D aiColor(0.0f, 0.0f, 0.0f);
			switch (textype)
			{
			case aiTextureType::aiTextureType_DIFFUSE:
				pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
				if (aiColor.IsBlack())
				{
					//material->LoadTexture(1, 1, COLOR4(1, 0, 1).ToColor());
					printf("Creating black color texture");
					return;
				}
				//material->LoadTexture(1, 1, COLOR4(aiColor.r, aiColor.g, aiColor.b).ToColor());
				printf("Creating rgb color texture");
				return;


			}
		}
		else
		{
			for (UINT i = 0; i < textureCount; i++)
			{
				aiString path;
				pMaterial->GetTexture(textype, i, &path);
				AssimpTextureStorageType storetype = DetermineTextureStorageType(pscene, pMaterial, i, textype);
				switch (storetype)
				{
				case AssimpTextureStorageType::EmbeddedIndexCompressed:
				{
					printf("Embedded Indexed Compressed Texture");
					//int index = GetTextureIndex(&path);
					//Texture embeddedIndexTexture(reinterpret_cast<uint8_t*>(pscene->mTextures[index]->pcData), pscene->mTextures[index]->mWidth, textype);
					//materialTextures.push_back(embeddedIndexTexture);
					break;
				}
				case AssimpTextureStorageType::EmbeddedCompressed:
				{
					printf("Embedded Texture");
					//const aiTexture* pTexture = pscene->GetEmbeddedTexture(path.C_Str());
					//Texture embeddedTexture(reinterpret_cast<uint8_t*>(pTexture->pcData), pTexture->mWidth, textype);
					//materialTextures.push_back(embeddedTexture);
					break;
				}
				case AssimpTextureStorageType::Disk:
				{
					std::string filename = "assets/textures/" + std::string(path.C_Str());
					printf(" Texture file: %s \n", filename.c_str());
					material->LoadTexture(filename);
					break;
				}
				}
			}
		}
		return;
	}

	AssimpTextureStorageType Model::DetermineTextureStorageType(const aiScene* pscene, aiMaterial* pmaterial, unsigned int index, aiTextureType textype)
	{
		if (pmaterial->GetTextureCount(textype) == 0)
		{
			return AssimpTextureStorageType::None;
		}
		aiString path;
		
		pmaterial->GetTexture(textype, index, &path);
		printf("Texture Path: %s \n", path.C_Str());
		std::string texpath = path.C_Str();

		if (texpath[0] == '*')
		{
			if (pscene->mTextures[0]->mHeight == 0)
			{
				return AssimpTextureStorageType::EmbeddedIndexCompressed;
			}
			else
			{
				ZL_ASSERT(0,"NO SUPPORT FOR INDEX NON COMPRESSED TEXTURES!\n");
				printf("Embedded Indexed Texture\n");
				return AssimpTextureStorageType::EmbeddedIndexNonCompressed;
			}
		}
		if (auto pTex = pscene->GetEmbeddedTexture(texpath.c_str()))
		{
			if (pTex->mHeight == 0)
			{
				printf("Embedded Compressed Texture\n");
				return AssimpTextureStorageType::EmbeddedCompressed;
			}
			else
			{
				printf("Embedded Texture\n");
				ZL_ASSERT(0, "NO SUPPORT FOR EMBEDDED NON COMPRESSED TEXTURES!");
				return AssimpTextureStorageType::EmbeddedNonCompressed;
			}
		}

		if (texpath.find('.') != std::string::npos)
		{
			printf("Disk %s \n",texpath.c_str());
			return AssimpTextureStorageType::Disk;
		}
		printf("No Texture\n");
		return AssimpTextureStorageType::None;
	}

	int Model::GetTextureIndex(aiString* pStr)
	{
		assert(pStr->length >= 2);
		return atoi(&pStr->C_Str()[1]);
	}


}
