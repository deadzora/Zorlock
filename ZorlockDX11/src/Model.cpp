#include "Model.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "Math.h"
#include "StringConverter.h"
/*
bool Model::Plane()
{
	Vertex list[] =
	{
		//x			y			z			r			g			b			u			v			w
		{-0.5f,		-0.5f,		1.0f,		1.0f,		0.0f,		0.0f,		1.0f,		1.0f,		0.0f},
		{-0.5f,		0.5f,		1.0f,		0.0f,		1.0f,		0.0f,		1.0f,		0.0f,		0.0f},
		{0.5f,		0.5f,		1.0f,		1.0f,		1.0f,		0.0f,		0.0f,		0.0f,		0.0f},
		{0.5f,		-0.5f,		1.0f,		0.0f,		0.0f,		1.0f,		0.0f,		1.0f,		0.0f}
	};


	DWORD indices[] =
	{
		0,1,2,
		0,2,3
	};
	this->m_vb = GraphicsEngine::get()->create_vertexbuffer();
	UINT size_list = ARRAYSIZE(list);

	this->m_ib = GraphicsEngine::get()->create_indexbuffer();
	UINT indexsize_list = ARRAYSIZE(indices);




	this->m_vb->load(list, sizeof(Vertex), size_list, this->m_vs->GetBuffer()->GetBufferPointer(), this->m_vs->GetBuffer()->GetBufferSize());
	this->m_ib->load(indices, sizeof(DWORD), indexsize_list);
	
	return true;
}
*/


bool Model::init(DeviceContext * device_context)
{
	return BaseModel::init(device_context);
}

bool Model::init(const std::string & filename, DeviceContext * device_context)
{

	BaseModel::init(device_context);


	if (!this->LoadModel(filename))
		return false;

	return true;
}

void Model::SetTexture(ID3D11ShaderResourceView * tex)
{
	//this->basetex = tex;
	std::vector<Texture> textures;
	Texture texture = Texture(tex,aiTextureType::aiTextureType_DIFFUSE);
	textures.push_back(texture);
	this->SetAllMeshTextures(textures);
}

void Model::SetTexture(Texture * tex)
{

	std::vector<Texture> textures;
	textures.push_back(Texture(*tex));
	this->SetAllMeshTextures(textures);
}




void Model::ApplyShaders()
{
	for (int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].SetVertexLayout(this->m_vs->GetBuffer(), this->m_vs->GetBuffer()->GetBufferSize());
	}
}



void Model::SetLightColor(int lightnum, float r, float g, float b)
{
	this->l_pcb->setlightcolor(lightnum, r, g, b);
}

void Model::SetLightBrightness(int lightnum, float b)
{
	this->l_pcb->setlightbright(lightnum, b);
}

void Model::SetLightPosition(int lightnum, const DirectX::XMFLOAT3 & pos)
{
	this->l_pcb->setlightpos(lightnum, pos);
}

void Model::SetLightAttenuation(int lightnum, float a, float b, float c)
{
	this->l_pcb->setlightattenuation(lightnum, a, b, c);
}

void Model::SetLightRadius(int lightnum, float r)
{
	this->l_pcb->setlightradius(lightnum, r);
}



void Model::Draw(DirectX::XMMATRIX viewmatrix)
{
	this->m_pcb->applyps();
	this->a_pcb->applyps();
	this->l_pcb->applyps();
	this->m_device_context->setvertexshader(this->m_vs);
	this->m_device_context->setpixelshader(this->m_ps);
	this->m_device_context->setblendstate();
	this->m_pcb->setalpha(1.0f);

	for (int i = 0; i < meshes.size(); i++)
	{
		this->m_cb->setmatrix(meshes[i].GetTransformMatrix() * viewmatrix, meshes[i].GetTransformMatrix());
		this->m_cb->apply();
		this->m_pcb->applyps();
		this->a_pcb->applyps();
		this->l_pcb->applyps();
		meshes[i].Draw();
	}

}

void Model::Release()
{
	BaseModel::Release();
}

Model::Model()
{
}


Model::~Model()
{
}

void Model::SetAllMeshTextures(std::vector<Texture>& tex)
{
	for (UINT i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].SetTextures(tex);
	}
}

void Model::SetMeshTextures(std::vector<Texture>& tex, unsigned int index)
{

	this->meshes[index].SetTextures(tex);

}

int Model::GetTextureIndex(aiString * pStr)
{
	assert(pStr->length >= 2);
	return atoi(&pStr->C_Str()[1]);
}

bool Model::LoadModel(const std::string & filename)
{
	this->directory = StringConverter::GetDirectory(filename);
	Assimp::Importer importer;
	const aiScene * pScene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (pScene == NULL)
		return false;

	this->ProcessNode(pScene->mRootNode, pScene, DirectX::XMMatrixIdentity() );
	return true;
}

void Model::ProcessNode(aiNode * node, const aiScene * scene, const XMMATRIX & parentTransformMatrix)
{
	XMMATRIX nodeTransformMatrix = XMMatrixTranspose(XMMATRIX(&node->mTransformation.a1)) * parentTransformMatrix;

	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->ProcessMesh(mesh, scene, nodeTransformMatrix));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene, nodeTransformMatrix);

	}
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene, const XMMATRIX & transformMatrix)
{
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;
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
			vertex.uvw.z = (float)mesh->mTextureCoords[0][i].z;
		}

		vertices.push_back(vertex);

	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	std::vector<Texture> textures;
	aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseTex = LoadMaterialTextures(material, aiTextureType::aiTextureType_DIFFUSE, scene);
	textures.insert(textures.end(), diffuseTex.begin(), diffuseTex.end());
	//textures.push_back(Texture(Colors::UnhandledTextureColor,aiTextureType::aiTextureType_DIFFUSE));

	if (this->m_vs)
	{
		return Mesh(this->m_device_context, vertices, indices, textures, this->m_vs->GetBuffer()->GetBufferPointer(), this->m_vs->GetBuffer()->GetBufferSize(), transformMatrix);
	}
	else
	{
		return Mesh(this->m_device_context, vertices, indices, textures, transformMatrix);

	}
	
}

TextureStorageType Model::DetermineTextureStorageType(const aiScene * pscene, aiMaterial * pmaterial, unsigned int index, aiTextureType textype)
{
	if (pmaterial->GetTextureCount(textype) == 0)
	{
		return TextureStorageType::None;
	}
	aiString path;
	pmaterial->GetTexture(textype, index, &path);

	std::string texpath = path.C_Str();

	if (texpath[0] == '*')
	{
		if (pscene->mTextures[0]->mHeight == 0)
		{
			return TextureStorageType::EmbeddedIndexCompressed;
		}
		else
		{
			assert("NO SUPPORT FOR INDEX NON COMPRESSED TEXTURES!");
			return TextureStorageType::EmbeddedIndexNonCompressed;
		}
	}
	if (auto pTex = pscene->GetEmbeddedTexture(texpath.c_str()))
	{
		if (pTex->mHeight == 0)
		{
			return TextureStorageType::EmbeddedCompressed;
		}
		else
		{
			assert("NO SUPPORT FOR EMBEDDED NON COMPRESSED TEXTURES!");
			return TextureStorageType::EmbeddedNonCompressed;
		}
	}

	if (texpath.find('.') != std::string::npos)
	{
		return TextureStorageType::Disk;
	}

	return TextureStorageType::None;
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial * pMaterial, aiTextureType textype, const aiScene * pscene)
{
	std::vector<Texture> materialTextures;
	TextureStorageType storetype = TextureStorageType::Invalid;
	unsigned int textureCount = pMaterial->GetTextureCount(textype);

	if (textureCount == 0)
	{
		storetype = TextureStorageType::None;
		aiColor3D aiColor(0.0f, 0.0f, 0.0f);
		switch (textype)
		{
		case aiTextureType::aiTextureType_DIFFUSE:
			pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
			if (aiColor.IsBlack())
			{
				materialTextures.push_back(Texture(Colors::UnloadedTextureColor, textype));
				return materialTextures;
			}
			materialTextures.push_back(Texture(Color(aiColor.r*255, aiColor.g*255, aiColor.b*255), textype));
			return materialTextures;
			

		}
	}
	else
	{
		for (UINT i = 0; i < textureCount; i++)
		{
			aiString path;
			pMaterial->GetTexture(textype, i, &path);
			TextureStorageType storetype = DetermineTextureStorageType(pscene, pMaterial, i, textype);
			switch (storetype)
			{
			case TextureStorageType::EmbeddedIndexCompressed:
			{
				int index = GetTextureIndex(&path);
				Texture embeddedIndexTexture(reinterpret_cast<uint8_t*>(pscene->mTextures[index]->pcData), pscene->mTextures[index]->mWidth, textype);
				materialTextures.push_back(embeddedIndexTexture);
				break;
			}
			case TextureStorageType::EmbeddedCompressed:
			{
				const aiTexture * pTexture = pscene->GetEmbeddedTexture(path.C_Str());
				Texture embeddedTexture(reinterpret_cast<uint8_t*>(pTexture->pcData), pTexture->mWidth, textype);
				materialTextures.push_back(embeddedTexture);
				break;
			}
			case TextureStorageType::Disk:
			{
				std::string filename = this->directory + '\\' + path.C_Str();
				Texture diskTexture(StringConverter::StringtoWide(filename).c_str(), textype);
				materialTextures.push_back(diskTexture);
				break;
			}
			}
		}
	}

	if (materialTextures.size() == 0)
	{
		materialTextures.push_back(Texture(Colors::UnhandledTextureColor, textype));
	}
	return materialTextures;
}



