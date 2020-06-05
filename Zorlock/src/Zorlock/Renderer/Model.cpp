#include "ZLpch.h"
#include "Model.h"
#include "Renderer.h"
#include "Zorlock/Components/MeshRenderer.h"
#include "RendererAPI.h"
#include "Skeleton.h"
#include "Bone.h"
#include "Animation.h"

namespace Zorlock
{
	ZModel::~ZModel()
	{
	}
	ZModel::ZModel() : m_skeleton(nullptr), loadscale(1.0f), current_animation(0)
	{
	}
	ZModel::ZModel(ZorlockPrimitiveType primitive, Ref<MeshRenderer> renderer, uint32_t segments) : loadscale(1.0f), m_skeleton(nullptr), current_animation(0)
	{
		meshRenderer = renderer;
		switch (primitive)
		{
		case ZorlockPrimitiveType::None:
		{
			break;
		}
		case ZorlockPrimitiveType::Quad:
		{
			CreateQuad();
			break;
		}
		case ZorlockPrimitiveType::Cube:
		{
			CreateCube();
			break;
		}
		case ZorlockPrimitiveType::Sphere:
		{
			CreateSphere(segments);
			break;
		}
		case ZorlockPrimitiveType::Cylinder:
		{
			CreateCylinder(segments);
			break;
		}
		case ZorlockPrimitiveType::Cone:
		{
			CreateCone(segments);
			break;
		}
		}
	}
	ZModel::ZModel(const std::string& name,const std::string& modelfile) : name(name), loadscale(1.0f), m_skeleton(nullptr), current_animation(0)
	{
		UINT flags = (RendererAPI::GetAPI() == RendererAPI::API::OpenGL) ? aiProcess_Triangulate : aiProcess_Triangulate | aiProcess_ConvertToLeftHanded;

		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(modelfile, flags);

		m_skeleton = CreateRef<Skeleton>("Skeleton", nullptr);

		if (pScene != NULL)
		{
			MATRIX4 rootMatrix = MATRIX4(
				(float)pScene->mRootNode->mTransformation.a1, (float)pScene->mRootNode->mTransformation.a2, (float)pScene->mRootNode->mTransformation.a3, (float)pScene->mRootNode->mTransformation.a4,
				(float)pScene->mRootNode->mTransformation.b1, (float)pScene->mRootNode->mTransformation.b2, (float)pScene->mRootNode->mTransformation.b3, (float)pScene->mRootNode->mTransformation.b4,
				(float)pScene->mRootNode->mTransformation.c1, (float)pScene->mRootNode->mTransformation.c2, (float)pScene->mRootNode->mTransformation.c3, (float)pScene->mRootNode->mTransformation.c4,
				(float)pScene->mRootNode->mTransformation.d1, (float)pScene->mRootNode->mTransformation.d2, (float)pScene->mRootNode->mTransformation.d3, (float)pScene->mRootNode->mTransformation.d4
			);			
			
			this->ProcessNode(pScene->mRootNode, pScene, rootMatrix);
			this->ProcessMeshes(pScene->mRootNode, pScene);
			this->m_skeleton->SetGlobalInverse(rootMatrix.inverse());
			this->ProcessAnimations(pScene);
		}

	}
	ZModel::ZModel(const std::string& name, const std::string& modelfile, Ref<MeshRenderer> renderer, float scale) : name(name), loadscale(scale), current_animation(0)
	{
		meshRenderer = renderer;
		UINT flags = (RendererAPI::GetAPI() == RendererAPI::API::OpenGL) ? aiProcess_Triangulate : aiProcess_Triangulate | aiProcess_ConvertToLeftHanded;

		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(modelfile, flags); // | aiProcess_ConvertToLeftHanded

		m_skeleton = CreateRef<Skeleton>("Skeleton", renderer->parent->transform);

		if (pScene != NULL)
		{
			MATRIX4 rootMatrix = MATRIX4(
				(float)pScene->mRootNode->mTransformation.a1, (float)pScene->mRootNode->mTransformation.a2, (float)pScene->mRootNode->mTransformation.a3, (float)pScene->mRootNode->mTransformation.a4,
				(float)pScene->mRootNode->mTransformation.b1, (float)pScene->mRootNode->mTransformation.b2, (float)pScene->mRootNode->mTransformation.b3, (float)pScene->mRootNode->mTransformation.b4,
				(float)pScene->mRootNode->mTransformation.c1, (float)pScene->mRootNode->mTransformation.c2, (float)pScene->mRootNode->mTransformation.c3, (float)pScene->mRootNode->mTransformation.c4,
				(float)pScene->mRootNode->mTransformation.d1, (float)pScene->mRootNode->mTransformation.d2, (float)pScene->mRootNode->mTransformation.d3, (float)pScene->mRootNode->mTransformation.d4
			);
			
			renderer->parent->transform->UpdateTransformationMatrix();
			this->ProcessNode(pScene->mRootNode, pScene, rootMatrix);
			this->ProcessMeshes(pScene->mRootNode, pScene);
			this->m_skeleton->SetGlobalInverse(rootMatrix.inverse());
			this->ProcessAnimations(pScene);
		}

	}
	void ZModel::Update(Timestep ts)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			if (meshRenderer != nullptr)
			{
				m_meshes[i]->SetDrawMatrix(m_meshes[i]->GetMatrix() * meshRenderer->parent->transform->GetDrawMatrix());
			}
		}
		if (m_skeleton != nullptr)
		{
			if (current_animation < m_animations.size())
			{
				m_skeleton->SetCurrentAnimation(m_animations[current_animation]);
				m_skeleton->Update(ts);
			}
		}
	}

	void ZModel::Draw()
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			Ref<Material> mat = m_meshes[i]->GetMaterial();
			if (mat != nullptr)
			{
				mat->GetShader()->Bind();
				switch(RendererAPI::GetAPI())
				{ 
				case RendererAPI::API::DX11:
				{
					mat->GetShader()->SetBuffer("u_Bones", m_skeleton->GetBoneMatrices(i), sizeof(Matrix4) * m_skeleton->GetBonesSize(), m_skeleton->GetBonesSize());
					break;
				}
				case RendererAPI::API::OpenGL:
				{
					Matrix4* matx = m_skeleton->GetBoneMatrices(i);
					for (size_t i = 0; i < m_skeleton->GetBonesSize(); i++)
					{
						mat->GetShader()->SetMat4("u_Bones[" + std::to_string(i) + "]", matx[i]);						
					}
					break;
				}
				}
				
				m_meshes[i]->Draw();
			}
		}
	}

	ZL_DEPRECATED("Please add mem release commands to vertexarray, vertexbuffer and indexbuffer")
	void ZModel::Destroy()
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->Destroy();
		}
	}

	void ZModel::AppendAnimation(const std::string& modelfile)
	{
		UINT flags = (RendererAPI::GetAPI() == RendererAPI::API::OpenGL) ? aiProcess_Triangulate : aiProcess_Triangulate | aiProcess_ConvertToLeftHanded;

		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(modelfile, flags); // | aiProcess_ConvertToLeftHanded
		if (pScene != NULL)
		{
			this->ProcessAnimations(pScene);
		}
	}

	void ZModel::SetMeshRenderer(Ref<MeshRenderer> m)
	{
		Ref<MeshRenderer> mrenderer = m;
		meshRenderer = mrenderer;
	}

	void ZModel::CreateCube()
	{

		std::vector<Vertex> vertices;

		vertices.push_back(Vertex(
			//position
			-1.0, -1.0, -1.0, 1.0,
			//normal
			0.0, 0.0, -1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 1.0
		));
		vertices.push_back(Vertex(
			//position
			-1.0, 1.0, -1.0, 1.0,
			//normal
			0.0, 0.0, -1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, 1.0, -1.0, 1.0,
			//normal
			0.0, 0.0, -1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, -1.0, -1.0, 1.0,
			//normal
			0.0, 0.0, -1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 1.0
		));

		//new side

		vertices.push_back(Vertex(
			//position
			-1.0, -1.0, 1.0, 1.0,
			//normal
			0.0, 0.0, 1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 1.0
		));
		vertices.push_back(Vertex(
			//position
			-1.0, 1.0, 1.0, 1.0,
			//normal
			0.0, 0.0, 1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, 1.0, 1.0, 1.0,
			//normal
			0.0, 0.0, 1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, -1.0, 1.0, 1.0,
			//normal
			0.0, 0.0, 1.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 1.0
		));
		//new side

		vertices.push_back(Vertex(
			//position
			-1.0, -1.0, 1.0, 1.0,
			//normal
			0.0, -1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 1.0
		));
		vertices.push_back(Vertex(
			//position
			-1.0, 1.0, 1.0, 1.0,
			//normal
			0.0, 1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, 1.0, 1.0, 1.0,
			//normal
			0.0, 1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			-1.0, -1.0, -1.0, 1.0,
			//normal
			0.0, -1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 1.0
		));
		//new side

		vertices.push_back(Vertex(
			//position
			-1.0, -1.0, -1.0, 1.0,
			//normal
			0.0, -1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			-1.0, 1.0, -1.0, 1.0,
			//normal
			0.0, 1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 1.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, 1.0, -1.0, 1.0,
			//normal
			0.0, 1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 1.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, -1.0, -1.0, 1.0,
			//normal
			0.0, -1.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 0.0
		));
		//new side


		vertices.push_back(Vertex(
			//position
			-1.0, -1.0, 1.0, 1.0,
			//normal
			-1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 1.0
		));
		vertices.push_back(Vertex(
			//position
			-1.0, 1.0, 1.0, 1.0,
			//normal
			-1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, 1.0, 1.0, 1.0,
			//normal
			1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, -1.0, 1.0, 1.0,
			//normal
			1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 1.0
		));
		//new side


		vertices.push_back(Vertex(
			//position
			-1.0, -1.0, -1.0, 1.0,
			//normal
			-1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 1.0
		));
		vertices.push_back(Vertex(
			//position
			-1.0, 1.0, -1.0, 1.0,
			//normal
			-1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			1.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, 1.0, -1.0, 1.0,
			//normal
			1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 0.0
		));
		vertices.push_back(Vertex(
			//position
			1.0, -1.0, -1.0, 1.0,
			//normal
			1.0, 0.0, 0.0,
			//color
			1.0, 1.0, 1.0,
			//uv
			0.0, 1.0
		));
		std::vector<uint32_t> indices;
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		indices.push_back(0); indices.push_back(2); indices.push_back(3);
		indices.push_back(6); indices.push_back(5); indices.push_back(4);
		indices.push_back(7); indices.push_back(6); indices.push_back(4);
		indices.push_back(6 + 8); indices.push_back(5 + 8); indices.push_back(1 + 8);
		indices.push_back(2 + 8); indices.push_back(6 + 8); indices.push_back(1 + 8);
		indices.push_back(0 + 8); indices.push_back(4 + 8); indices.push_back(7 + 8);
		indices.push_back(0 + 8); indices.push_back(7 + 8); indices.push_back(3 + 8);
		indices.push_back(6 + 16); indices.push_back(2 + 16); indices.push_back(3 + 16);
		indices.push_back(7 + 16); indices.push_back(6 + 16); indices.push_back(3 + 16);
		indices.push_back(0 + 16); indices.push_back(1 + 16); indices.push_back(5 + 16);
		indices.push_back(0 + 16); indices.push_back(5 + 16); indices.push_back(4 + 16);


		Ref<Material> zmaterial = MaterialLibrary::GetInstance()->CreateMaterial(ShaderLibrary::GetInstance()->GetStandard());

		if (meshRenderer != nullptr)
		{
			meshRenderer->AddMaterial(zmaterial);

		}
		zmaterial->GetShader()->Bind();
		Ref<Mesh> quadmesh = CreateMesh();
		quadmesh->SetMaterial(zmaterial);
		Ref<VertexArray> varray = quadmesh->CreateVertexArray();
		quadmesh->SetMatrix(MATRIX4::TRS(VECTOR3(0.0f, 0.0f, 0.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.0f, 1.0f, 1.0f)));
		quadmesh->vcount = (uint32_t)indices.size();
		//printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)sizeof(vertices.data()));
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)(sizeof(Vertex)*vertices.size()));
		vbuffer->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial->GetShader().get());
		varray->AddVertexBuffer(vbuffer);
		Ref<IndexBuffer> ibuffer = quadmesh->CreateIndexBuffer(indices.data(), (uint32_t)indices.size());
		varray->SetIndexBuffer(ibuffer);



	}

	void ZModel::CreateQuad()
	{
		Ref<Material> zmaterial = MaterialLibrary::GetInstance()->CreateMaterial(ShaderLibrary::GetInstance()->GetStandard());

		if (meshRenderer != nullptr)
		{
			meshRenderer->AddMaterial(zmaterial);

		}
		zmaterial->GetShader()->Bind();
		Ref<Mesh> quadmesh = CreateMesh();
		quadmesh->SetMaterial(zmaterial);
		Ref<VertexArray> varray = quadmesh->CreateVertexArray();

		float squareVertices[12 * 4] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
			};		
		quadmesh->SetMatrix(MATRIX4::TRS(VECTOR3(0.0f, 0.0f, 0.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.0f, 1.0f, 1.0f)));
		quadmesh->vcount = 6;
		//printf("Setting Mesh Data vertices: %u indices %d \n", 24, 6);		
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(squareVertices, sizeof(squareVertices));
		vbuffer->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial->GetShader().get());
		varray->AddVertexBuffer(vbuffer);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> ibuffer = quadmesh->CreateIndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		varray->SetIndexBuffer(ibuffer);



	}

	void ZModel::CreateSphere(uint32_t segments)
	{

		if (segments < 3 || segments>100) return;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		uint32_t h_segs = segments * 2, v_segs = segments;
		Vertex v;
		Point t;
		v.position = Vector4(0, 1, 0, 1);
		v.normal = Vector3(0, 1, 0);
		uint32_t k;
		for (k = 0; k < h_segs; ++k) {
			v.uvw.x = (k + .5f) / h_segs;
			v.uvw.y = 0;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		for (k = 1; k < v_segs; ++k) {
			float pitch = k * M_PI / v_segs - HALFPI;
			for (uint32_t j = 0; j <= h_segs; ++j) {
				float yaw = (j % h_segs) * TWOPI / h_segs;
				v.normal = MathF::rotationMatrix(pitch, yaw, 0).k;
				v.position = Vector4(v.normal, 1.0f);
				v.uvw.x = float(j) / float(h_segs);
				v.uvw.y = float(k) / float(v_segs);
				vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
			}
		}
		v.normal = Vector3(0, -1, 0);
		v.position = Vector4(v.normal, 1.0f);
		for (k = 0; k < h_segs; ++k) {
			v.uvw.x = (k + .5f) / h_segs;
			v.uvw.y = 1;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		for (k = 0; k < h_segs; ++k) {
			t.x = k;
			t.y = t.x + h_segs + 1;
			t.z = t.y - 1;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
		}
		for (k = 1; k < v_segs - 1; ++k) {
			for (uint32_t j = 0; j < h_segs; ++j) {
				t.x = k * (h_segs + 1) + j - 1;
				t.y = t.x + 1;
				t.z = t.y + h_segs + 1;
				indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
				t.y = t.z;
				t.z = t.y - 1;
				indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
			}
		}
		for (k = 0; k < h_segs; ++k) {
			t.x = (h_segs + 1) * (v_segs - 1) + k - 1;
			t.y = t.x + 1;
			t.z = t.y + h_segs;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
		}

		Ref<Material> zmaterial = MaterialLibrary::GetInstance()->CreateMaterial(ShaderLibrary::GetInstance()->GetStandard());

		if (meshRenderer != nullptr)
		{
			meshRenderer->AddMaterial(zmaterial);

		}
		zmaterial->GetShader()->Bind();
		Ref<Mesh> quadmesh = CreateMesh();
		quadmesh->SetMaterial(zmaterial);
		Ref<VertexArray> varray = quadmesh->CreateVertexArray();
		quadmesh->SetMatrix(MATRIX4::TRS(VECTOR3(0.0f, 0.0f, 0.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.0f, 1.0f, 1.0f)));
		quadmesh->vcount = (uint32_t)indices.size();
		//printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)vertices.size());
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)(sizeof(Vertex) * vertices.size()));
		vbuffer->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial->GetShader().get());
		varray->AddVertexBuffer(vbuffer);
		Ref<IndexBuffer> ibuffer = quadmesh->CreateIndexBuffer(indices.data(), (uint32_t)indices.size());
		varray->SetIndexBuffer(ibuffer);

	}

	void ZModel::CreateCylinder(uint32_t segments)
	{

		if (segments < 3 || segments>100) return;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		Vertex v;
		Point t;

		uint32_t k;
		for (k = 0; k <= segments; ++k) {
			float yaw = (k % segments) * TWOPI / segments;
			v.position = Vector4(MathF::rotationMatrix(0, yaw, 0).k, 1.0f);
			v.position.y = 1;
			v.normal = Vector3(v.position.x, 0, v.position.z);
			v.uvw.x = v.uvw.x = float(k) / segments;
			v.uvw.y = v.uvw.y = 0;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
			v.position.y = -1;
			v.uvw.x = v.uvw.x = float(k) / segments;
			v.uvw.y = v.uvw.y = 1;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		for (k = 0; k < segments; ++k) {
			t.x = k * 2;
			t.y = t.x + 2;
			t.z = t.y + 1;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
			t.y = t.z;
			t.z = t.y - 2;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
		}

		for (k = 0; k < segments; ++k) {
			float yaw = k * TWOPI / segments;
			v.position = Vector4(MathF::rotationMatrix(0, yaw, 0).k,1.0f);
			v.position.y = 1; v.normal = Vector3(0, 1, 0);
			v.uvw.x = v.uvw.x = v.position.x * .5f + .5f;
			v.uvw.y = v.uvw.y = v.position.z * .5f + .5f;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
			v.position.y = -1; v.normal = Vector3(0, -1, 0);
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		for (k = 2; k < segments; ++k) {
			t.x = 0;
			t.y = k * 2;
			t.z = (k - 1) * 2;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
			t.x = 1;
			t.y = (k - 1) * 2 + 1;
			t.z = k * 2 + 1;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
		}
		Ref<Material> zmaterial = MaterialLibrary::GetInstance()->CreateMaterial(ShaderLibrary::GetInstance()->GetStandard());

		if (meshRenderer != nullptr)
		{
			meshRenderer->AddMaterial(zmaterial);

		}
		zmaterial->GetShader()->Bind();
		Ref<Mesh> quadmesh = CreateMesh();
		quadmesh->SetMaterial(zmaterial);
		Ref<VertexArray> varray = quadmesh->CreateVertexArray();
		quadmesh->SetMatrix(MATRIX4::TRS(VECTOR3(0.0f, 0.0f, 0.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.0f, 1.0f, 1.0f)));
		quadmesh->vcount = (uint32_t)indices.size();
		//printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)vertices.size());
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)(sizeof(Vertex) * vertices.size()));
		vbuffer->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial->GetShader().get());
		varray->AddVertexBuffer(vbuffer);
		Ref<IndexBuffer> ibuffer = quadmesh->CreateIndexBuffer(indices.data(), (uint32_t)indices.size());
		varray->SetIndexBuffer(ibuffer);
	}

	void ZModel::CreateCone(uint32_t segments)
	{
		if (segments < 3 || segments>100) return;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		Vertex v;
		Point t;
		uint32_t k;

		v.normal = Vector3(0, 1, 0);
		v.position = Vector4(v.normal, 1.0f);
		for (k = 0; k < segments; ++k) {
			v.uvw.x = v.uvw.x = (k + .5f) / segments;
			v.uvw.y = v.uvw.y = 0;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		for (k = 0; k <= segments; ++k) {
			float yaw = (k % segments) * TWOPI / segments;
			v.position = Vector4(MathF::yawMatrix(yaw).k,1.0f); v.position.y = -1;
			v.normal = Vector3(v.position.x, 0, v.position.z);
			v.uvw.x = v.uvw.x = float(k) / segments;
			v.uvw.y = v.uvw.y = 1;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		for (k = 0; k < segments; ++k) {
			t.x = k;
			t.y = k + segments + 1;
			t.z = k + segments;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
		}

		for (k = 0; k < segments; ++k) {
			float yaw = k * TWOPI / segments;
			v.position = Vector4(MathF::yawMatrix(yaw).k,1.0f); v.position.y = -1;
			v.normal = Vector3(v.position.x, 0, v.position.z);
			v.uvw.x = v.uvw.x = v.position.x * .5f + .5f;
			v.uvw.y = v.uvw.y = v.position.z * .5f + .5f;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		t.x = 0;
		for (k = 2; k < segments; ++k) {
			t.y = k - 1;
			t.z = k;
			indices.push_back(t.x); indices.push_back(t.y); indices.push_back(t.z);
		}
		Ref<Material> zmaterial = MaterialLibrary::GetInstance()->CreateMaterial(ShaderLibrary::GetInstance()->GetStandard());

		if (meshRenderer != nullptr)
		{
			meshRenderer->AddMaterial(zmaterial);

		}
		zmaterial->GetShader()->Bind();
		Ref<Mesh> quadmesh = CreateMesh();
		quadmesh->SetMaterial(zmaterial);
		Ref<VertexArray> varray = quadmesh->CreateVertexArray();
		quadmesh->SetMatrix(MATRIX4::TRS(VECTOR3(0.0f, 0.0f, 0.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.0f, 1.0f, 1.0f)));
		quadmesh->vcount = (uint32_t)indices.size();
		//printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)vertices.size());
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)(sizeof(Vertex) * vertices.size()));
		vbuffer->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial->GetShader().get());
		varray->AddVertexBuffer(vbuffer);
		Ref<IndexBuffer> ibuffer = quadmesh->CreateIndexBuffer(indices.data(), (uint32_t)indices.size());
		varray->SetIndexBuffer(ibuffer);

	}

	Ref<Mesh> ZModel::CreateMesh(std::string name)
	{		
		Ref<Mesh> mesh = Ref<Mesh>(new Mesh(name));
		if (mesh != nullptr)
		{
			printf("Created Mesh \n");
			m_meshes.push_back(mesh);
			mesh->SetMeshID(m_meshes.size() - 1);
			return mesh;
		}
		return nullptr;
	}

	void ZModel::AddMesh(Ref<Mesh> mesh)
	{
		if (mesh != nullptr)
		{
			m_meshes.push_back(mesh);
			mesh->SetMeshID(m_meshes.size() - 1);
		}
	}

	void ZModel::RemoveMesh(Ref<Mesh> mesh)
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

	Ref<Mesh> ZModel::GetMesh(uint32_t index)
	{
		if (index < m_meshes.size())
		{
			return m_meshes[index];
		}
		return nullptr;
	}

	Ref<Animation> ZModel::CreateAnimation(std::string name)
	{
		Ref<Animation> animation = Ref<Animation>(new Animation(name));
		if (animation != nullptr)
		{
			printf("Created Animation \n");
			m_animations.push_back(animation);
			animation->SetAnimationID(m_animations.size() - 1);
			current_animation = m_animations.size() - 1;
			return animation;
		}
		return nullptr;
	}

	Ref<Animation> ZModel::GetAnimation(uint32_t i)
	{
		return m_animations[i];
	}

	Ref<Animation> ZModel::GetAnimation(std::string name)
	{
		for (size_t i = 0; i < m_animations.size(); i++)
		{
			if (m_animations[i]->name.compare(name) == 0)
				return m_animations[i];
		}
		return nullptr;
	}

	Ref<Bone> ZModel::AddBone(std::string name, Ref<Transform> parent)
	{
		if (m_skeleton != nullptr)
		{
			return m_skeleton->AddBone(name,parent);
		}
		return nullptr;
	}

	Ref<Bone> ZModel::GetBone(uint32_t i)
	{
		if (m_skeleton != nullptr)
		{
			return m_skeleton->GetBone(i);
		}
		return nullptr;
	}

	Ref<Bone> ZModel::GetBone(std::string name)
	{
		if (m_skeleton != nullptr)
		{
			return m_skeleton->GetBone(name);
		}
		return nullptr;
	}

	size_t ZModel::GetSkeletonSize()
	{
		return m_skeleton->GetBonesSize();
	}

	void ZModel::ProcessAnimations(const aiScene* scene)
	{
		for (size_t i = 0; i < scene->mNumAnimations; i++)
		{
			aiAnimation* anim = scene->mAnimations[i];
			Ref<Animation> animation = CreateAnimation(anim->mName.data);
			//printf("animation: %s duration: %f \n", anim->mName.C_Str(), (float)anim->mDuration);

			animation->SetDuration((float)anim->mDuration);
			
			for (size_t c = 0; c < anim->mNumChannels; c++)
			{
				aiNodeAnim* achannel = anim->mChannels[c];
				Ref<AnimationChannel> animchannel = animation->CreateChannel(achannel->mNodeName.data);
				animchannel->m_boneID = m_skeleton->GetBone(achannel->mNodeName.data)->GetBoneID();

				for (size_t p = 0; p < achannel->mNumPositionKeys; p++)
				{
					aiVectorKey vkey = achannel->mPositionKeys[p];
					animchannel->AddPositionKey((float)vkey.mTime, Vector3((float)vkey.mValue.x, (float)vkey.mValue.y, (float)vkey.mValue.z));
				}

				for (size_t q = 0; q < achannel->mNumRotationKeys; q++)
				{
					aiQuatKey qkey = achannel->mRotationKeys[q];
					animchannel->AddRotationKey((float)qkey.mTime, Quaternion((float)qkey.mValue.x, (float)qkey.mValue.y, (float)qkey.mValue.z, (float)qkey.mValue.w));
				}

				for (size_t s = 0; s < achannel->mNumScalingKeys; s++)
				{
					aiVectorKey vkey = achannel->mScalingKeys[s];
					animchannel->AddScalingKey((float)vkey.mTime, Vector3((float)vkey.mValue.x, (float)vkey.mValue.y, (float)vkey.mValue.z));
				}
			}
		}
	}

	void ZModel::ProcessMeshes(aiNode* node, const aiScene* scene)
	{
		uint32_t meshoffset = 0;
		//printf("Parsing Mesh: %s \n", node->mName.C_Str());
		MATRIX4 mat = m_skeleton->GetBone(node->mName.data)->GetBaseMat();
		for (UINT i = 0; i < node->mNumMeshes; i++)
		{
			
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Ref<Mesh> zmesh = this->ProcessMesh(mesh, scene, meshoffset, mat);
		}

		for (UINT i = 0; i < node->mNumChildren; i++)
		{
			this->NodeChild(node->mChildren[i], meshoffset, scene);
		}

	}

	void ZModel::NodeChild(aiNode* node, uint32_t& meshoffset, const aiScene* scene)
	{
		//printf("Parsing Mesh: %s \n", node->mName.C_Str());
		for (UINT i = 0; i < node->mNumMeshes; i++)
		{
			
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Ref<Mesh> zmesh = this->ProcessMesh(mesh, scene, meshoffset);
		}

		for (UINT i = 0; i < node->mNumChildren; i++)
		{
			this->NodeChild(node->mChildren[i], meshoffset, scene);
		}
	}

	void ZModel::ProcessNode(aiNode* node, const aiScene* scene, const MATRIX4& parentTransformMatrix, Ref<Bone> parent)
	{
		MATRIX4 nodeMatrix = MATRIX4(
			(float)node->mTransformation.a1, (float)node->mTransformation.a2, (float)node->mTransformation.a3, (float)node->mTransformation.a4,
			(float)node->mTransformation.b1, (float)node->mTransformation.b2, (float)node->mTransformation.b3, (float)node->mTransformation.b4,
			(float)node->mTransformation.c1, (float)node->mTransformation.c2, (float)node->mTransformation.c3, (float)node->mTransformation.c4,
			(float)node->mTransformation.d1, (float)node->mTransformation.d2, (float)node->mTransformation.d3, (float)node->mTransformation.d4
			);
		MATRIX4 nodeTransformMatrix = parentTransformMatrix * nodeMatrix;
		Ref<Bone> bone = nullptr;
		if (parent == nullptr)
		{
			bone = AddBone(node->mName.data, m_skeleton->transform);
			bone->SetParent(parent);
			bone->SetBaseMat(nodeMatrix);
			bone->SetParentMat(parentTransformMatrix);
		}
		else {
			bone = AddBone(node->mName.data, parent->transform);
			bone->SetParent(parent);
			bone->SetBaseMat(nodeMatrix);
			bone->SetParentMat(parentTransformMatrix);
			parent->AddChildBone(bone);
		}
		
		

		for (UINT i = 0; i < node->mNumChildren; i++)
		{
			//printf("Parsing Node %s! \n",node->mName.C_Str());
			this->ProcessNode(node->mChildren[i], scene, nodeTransformMatrix,bone);
			
		}



	}

	Ref<Mesh> ZModel::ProcessMesh(aiMesh* mesh, const aiScene* scene, uint32_t& meshoffset, const MATRIX4& nodetransform)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		UINT nv = 0;
		Ref<Mesh> quadmesh = CreateMesh(mesh->mName.C_Str());
		

		for (UINT i = 0; i < mesh->mNumVertices; i++)
		{

			

			Vertex vertex;
			vertex.position.x = (float)mesh->mVertices[i].x * loadscale;
			vertex.position.y = (float)mesh->mVertices[i].y * loadscale;
			vertex.position.z = (float)mesh->mVertices[i].z * loadscale;
			vertex.position.w = 1.0f;

			vertex.position = nodetransform * vertex.position;

			vertex.color.x = 1.0f;
			vertex.color.y = 1.0f;
			vertex.color.z = 1.0f;
			vertex.normal.x = (float)mesh->mNormals[i].x;
			vertex.normal.y = (float)mesh->mNormals[i].y;
			vertex.normal.z = (float)mesh->mNormals[i].z;

			vertex.normal = nodetransform * vertex.normal;

			if (mesh->mTextureCoords[0])
			{
				vertex.uvw.x = (float)mesh->mTextureCoords[0][i].x;
				vertex.uvw.y = (float)mesh->mTextureCoords[0][i].y;
			}


			vertices.push_back(vertex);
			/*
			*/

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

		if (mesh->HasBones())
		{
			quadmesh->hasbones = true;
			//printf("Mesh has %u bones ", mesh->mNumBones);
			if (mesh->HasBones() && m_skeleton != nullptr)
			{
				for (size_t b = 0; b < mesh->mNumBones; b++)
				{
					Ref<Bone> bone = m_skeleton->GetBone(mesh->mBones[b]->mName.data);
					MATRIX4 nodeMatrix = MATRIX4(
						(float)mesh->mBones[b]->mOffsetMatrix.a1, (float)mesh->mBones[b]->mOffsetMatrix.a2, (float)mesh->mBones[b]->mOffsetMatrix.a3, (float)mesh->mBones[b]->mOffsetMatrix.a4,
						(float)mesh->mBones[b]->mOffsetMatrix.b1, (float)mesh->mBones[b]->mOffsetMatrix.b2, (float)mesh->mBones[b]->mOffsetMatrix.b3, (float)mesh->mBones[b]->mOffsetMatrix.b4,
						(float)mesh->mBones[b]->mOffsetMatrix.c1, (float)mesh->mBones[b]->mOffsetMatrix.c2, (float)mesh->mBones[b]->mOffsetMatrix.c3, (float)mesh->mBones[b]->mOffsetMatrix.c4,
						(float)mesh->mBones[b]->mOffsetMatrix.d1, (float)mesh->mBones[b]->mOffsetMatrix.d2, (float)mesh->mBones[b]->mOffsetMatrix.d3, (float)mesh->mBones[b]->mOffsetMatrix.d4
					);
					//printf(" Setting bone offset for %u", quadmesh->GetMeshID());
					bone->SetOffset(nodeMatrix, quadmesh->GetMeshID());
					//printf("Submesh: %u %s Bone ID: %u %s  \n", quadmesh->GetMeshID(),quadmesh->name.c_str(), bone->GetBoneID(), mesh->mBones[b]->mName.C_Str());
					/*
					Vector3 pos;
					Quaternion rot;
					Vector3 scale;
					nodeMatrix.decomposition(pos, rot, scale);
					printf(" Bone ID: %u %s pos: x %f y %f z %f \n",bone->GetBoneID(), mesh->mBones[b]->mName.C_Str(), pos.x, pos.y, pos.z);
					bone->transform->position = pos;
					bone->transform->rotation = rot;
					bone->transform->scale = scale;
					bone->transform->UpdateTransformationMatrix();
					*/
					for (size_t w = 0; w < mesh->mBones[b]->mNumWeights; w++)
					{
						bone->SetBoneWeight(quadmesh->GetMeshID(), mesh->mBones[b]->mWeights[w].mWeight, mesh->mBones[b]->mWeights[w].mVertexId);
						if (vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.x > 0.0f)
						{
							if (vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.y > 0.0f)
							{
								if (vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.z > 0.0f)
								{
									if (vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.w > 0.0f)
									{

									}
									else {
										//printf("WeightW: %f Vertex ID: %u BoneID: %s %u \n", mesh->mBones[b]->mWeights[w].mWeight, mesh->mBones[b]->mWeights[w].mVertexId, mesh->mBones[b]->mName.data, bone->GetBoneID());
										vertices[mesh->mBones[b]->mWeights[w].mVertexId].boneids.w = bone->GetBoneID();
										vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.w = mesh->mBones[b]->mWeights[w].mWeight;
									}
								}
								else {
									//printf("WeightZ: %f Vertex ID: %u BoneID: %s %u \n", mesh->mBones[b]->mWeights[w].mWeight, mesh->mBones[b]->mWeights[w].mVertexId, mesh->mBones[b]->mName.data, bone->GetBoneID());
									vertices[mesh->mBones[b]->mWeights[w].mVertexId].boneids.z = bone->GetBoneID();
									vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.z = mesh->mBones[b]->mWeights[w].mWeight;
								}
							}
							else {
								//printf("WeightY: %f Vertex ID: %u BoneID: %s %u \n", mesh->mBones[b]->mWeights[w].mWeight, mesh->mBones[b]->mWeights[w].mVertexId, mesh->mBones[b]->mName.data, bone->GetBoneID());
								vertices[mesh->mBones[b]->mWeights[w].mVertexId].boneids.y = bone->GetBoneID();
								vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.y = mesh->mBones[b]->mWeights[w].mWeight;
							}

						}
						else {
							//printf("WeighXt: %f Vertex ID: %u BoneID: %s %u \n", mesh->mBones[b]->mWeights[w].mWeight, mesh->mBones[b]->mWeights[w].mVertexId, mesh->mBones[b]->mName.data, bone->GetBoneID());
							vertices[mesh->mBones[b]->mWeights[w].mVertexId].boneids.x = bone->GetBoneID();
							vertices[mesh->mBones[b]->mWeights[w].mVertexId].weights.x = mesh->mBones[b]->mWeights[w].mWeight;
						}
					}

				}

			}

		}
		meshoffset += nv;
		aiString mname;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		mname = material->mProperties[AI_MATKEY_NAME]->mData;

		Ref<Material> zmaterial = MaterialLibrary::GetInstance()->CreateMaterial(ShaderLibrary::GetInstance()->GetStandard());

		if (meshRenderer != nullptr)
		{
			meshRenderer->AddMaterial(zmaterial);

		}
		zmaterial->GetShader()->Bind();
		
		quadmesh->SetMaterial(zmaterial);
		Ref<VertexArray> varray = quadmesh->CreateVertexArray();
		quadmesh->SetMatrix(MATRIX4::TRS(VECTOR3(0.0f, 0.0f, 0.0f), QUATERNION::EulerAngles(VECTOR3(0, 0, 0)), VECTOR3(1.0f, 1.0f, 1.0f)));
		quadmesh->vcount = (uint32_t)indices.size();
		//printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)nv, (uint32_t)((sizeof(float)*12)*nv));
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)sizeof(Vertex)*nv);
		vbuffer->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial->GetShader().get());
		varray->AddVertexBuffer(vbuffer);
		Ref<IndexBuffer> ibuffer = quadmesh->CreateIndexBuffer(indices.data(), (uint32_t)indices.size());
		varray->SetIndexBuffer(ibuffer);

		return quadmesh;
	}

	void ZModel::LoadMaterialTextures(Ref<Material> material, aiMaterial* pMaterial, aiTextureType textype, const aiScene* pscene)
	{

		AssimpTextureStorageType storetype = AssimpTextureStorageType::Invalid;
		unsigned int textureCount = pMaterial->GetTextureCount(textype);
		//printf("Texture Count: %u \n", textureCount);
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
					//printf("Creating black color texture \n");
					return;
				}
				//material->LoadTexture(1, 1, COLOR4(aiColor.r, aiColor.g, aiColor.b).ToColor());
				//printf("Creating rgb color texture \n");
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
					//printf("Embedded Indexed Compressed Texture \n");
					//int index = GetTextureIndex(&path);
					//Texture embeddedIndexTexture(reinterpret_cast<uint8_t*>(pscene->mTextures[index]->pcData), pscene->mTextures[index]->mWidth, textype);
					//materialTextures.push_back(embeddedIndexTexture);
					break;
				}
				case AssimpTextureStorageType::EmbeddedCompressed:
				{
					//printf("Embedded Texture \n");
					//const aiTexture* pTexture = pscene->GetEmbeddedTexture(path.C_Str());
					//Texture embeddedTexture(reinterpret_cast<uint8_t*>(pTexture->pcData), pTexture->mWidth, textype);
					//materialTextures.push_back(embeddedTexture);
					break;
				}
				case AssimpTextureStorageType::Disk:
				{
					std::string filename = "assets/textures/" + std::string(path.C_Str());
					//printf(" Texture file: %s \n", filename.c_str());
					material->LoadTexture(filename);
					break;
				}
				}
			}
		}
		return;
	}

	AssimpTextureStorageType ZModel::DetermineTextureStorageType(const aiScene* pscene, aiMaterial* pmaterial, unsigned int index, aiTextureType textype)
	{
		if (pmaterial->GetTextureCount(textype) == 0)
		{
			printf("No Textures \n");
			return AssimpTextureStorageType::None;
		}
		aiString path;
		
		pmaterial->GetTexture(textype, index, &path);
		//printf("Texture Path: %s \n", path.C_Str());
		std::string texpath = path.C_Str();

		if (texpath[0] == '*')
		{
			if (pscene->mTextures[0]->mHeight == 0)
			{
				printf("Embedded Indexed Compressed Texture\n");
				return AssimpTextureStorageType::EmbeddedIndexCompressed;
			}
			else
			{
				ZL_ASSERT(0,"NO SUPPORT FOR INDEX NON COMPRESSED TEXTURES!\n");
				//printf("Embedded Indexed Texture\n");
				return AssimpTextureStorageType::EmbeddedIndexNonCompressed;
			}
		}
		if (auto pTex = pscene->GetEmbeddedTexture(texpath.c_str()))
		{
			if (pTex->mHeight == 0)
			{
				//printf("Embedded Compressed Texture\n");
				return AssimpTextureStorageType::EmbeddedCompressed;
			}
			else
			{
				//printf("Embedded Texture\n");
				ZL_ASSERT(0, "NO SUPPORT FOR EMBEDDED NON COMPRESSED TEXTURES!");
				return AssimpTextureStorageType::EmbeddedNonCompressed;
			}
		}

		if (texpath.find('.') != std::string::npos)
		{
			//printf("Disk %s \n",texpath.c_str());
			return AssimpTextureStorageType::Disk;
		}
		//printf("No Texture\n");
		return AssimpTextureStorageType::None;
	}

	int ZModel::GetTextureIndex(aiString* pStr)
	{
		assert(pStr->length >= 2);
		return atoi(&pStr->C_Str()[1]);
	}


}
