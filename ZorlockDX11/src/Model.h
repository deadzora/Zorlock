#pragma once
#include "BaseModel.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <Importer.hpp>
#include <postprocess.h>
#include <scene.h>

using namespace DirectX;




class Model : public BaseModel
{
public:
	bool init(DeviceContext* device_context) override;
	bool init(const std::string & filename,DeviceContext* device_context) override;
	void SetTexture(ID3D11ShaderResourceView* tex) override;
	void SetTexture(Texture * tex) override;
	void ApplyShaders() override;

	//Make a light management class or something.
	void SetLightColor(int lightnum, float r, float g, float b);
	void SetLightBrightness(int lightnum, float b);
	void SetLightPosition(int lightnum, const XMFLOAT3 & pos);
	void SetLightAttenuation(int lightnum, float a, float b, float c);
	void SetLightRadius(int lightnum, float r);
	//end light stuff

	bool LoadModel(const std::string & filename) override;
	void Draw(DirectX::XMMATRIX viewmatrix) override;
	void Release();
	Model();
	~Model();

	

private:
	void SetAllMeshTextures(std::vector<Texture>& tex);
	void SetMeshTextures(std::vector<Texture> & tex, unsigned int index);
	int GetTextureIndex(aiString * pStr);
	void ProcessNode(aiNode * node, const aiScene * scene, const XMMATRIX & parentTransformMatrix);
	Mesh ProcessMesh(aiMesh * mesh, const aiScene * scene, const XMMATRIX & transformMatrix);
	TextureStorageType DetermineTextureStorageType(const aiScene * pscene, aiMaterial * pmaterial, unsigned int index, aiTextureType textype);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textype, const aiScene* pscene);
	
	//eventually create a transform class



};

