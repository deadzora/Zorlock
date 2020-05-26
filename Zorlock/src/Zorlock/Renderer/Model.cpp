#include "ZLpch.h"
#include "Model.h"
#include "Zorlock/Renderer/Renderer.h"
#include "Zorlock/Components/MeshRenderer.h"


namespace Zorlock
{
	ZModel::~ZModel()
	{
	}
	ZModel::ZModel()
	{
	}
	ZModel::ZModel(ZorlockPrimitiveType primitive, Ref<MeshRenderer> renderer, uint32_t segments)
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
	ZModel::ZModel(const std::string& name,const std::string& modelfile) : name(name)
	{
		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(modelfile, aiProcess_Triangulate | aiProcess_PreTransformVertices);

		if (pScene != NULL)
		{
			this->ProcessNode(pScene->mRootNode, pScene, MATRIX4::IDENTITY());
		}

	}
	ZModel::ZModel(const std::string& name, const std::string& modelfile, Ref<MeshRenderer> renderer) : name(name)
	{
		meshRenderer = renderer;

		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(modelfile, aiProcess_Triangulate | aiProcess_PreTransformVertices); // | aiProcess_ConvertToLeftHanded

		if (pScene != NULL)
		{
			this->ProcessNode(pScene->mRootNode, pScene, MATRIX4::IDENTITY());
		}

	}
	void ZModel::Update(Timestep ts)
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

	void ZModel::Draw()
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->Draw();
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
		printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)((sizeof(float) * 12) * vertices.size()));
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)sizeof(Vertex) * vertices.size());
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
		printf("Setting Mesh Data vertices: %u indices %d \n", 24, 6);		
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
		int h_segs = segments * 2, v_segs = segments;
		Vertex v;
		Point t;
		v.position = Vector4(0, 1, 0, 1);
		v.normal = Vector3(0, 1, 0);
		int k;
		for (k = 0; k < h_segs; ++k) {
			v.uvw.x = (k + .5f) / h_segs;
			v.uvw.y = 0;
			vertices.push_back(Vertex(v.position.x, v.position.y, v.position.z, v.uvw.x, v.uvw.y));
		}
		for (k = 1; k < v_segs; ++k) {
			float pitch = k * M_PI / v_segs - HALFPI;
			for (int j = 0; j <= h_segs; ++j) {
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
			for (int j = 0; j < h_segs; ++j) {
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
		printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)vertices.size());
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)sizeof(Vertex) * vertices.size());
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

		int k;
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
		printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)vertices.size());
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)sizeof(Vertex) * vertices.size());
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
		int k;

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
		printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)vertices.size(), (uint32_t)vertices.size());
		//Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(verts, (uint32_t)((sizeof(float) * 12) * nv));
		Ref<VertexBuffer> vbuffer = quadmesh->CreateVertexBuffer(vertices.data(), (uint32_t)sizeof(Vertex) * vertices.size());
		vbuffer->SetLayout(zmaterial->GetShader()->GetLayout(), zmaterial->GetShader().get());
		varray->AddVertexBuffer(vbuffer);
		Ref<IndexBuffer> ibuffer = quadmesh->CreateIndexBuffer(indices.data(), (uint32_t)indices.size());
		varray->SetIndexBuffer(ibuffer);

	}

	Ref<Mesh> ZModel::CreateMesh()
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

	void ZModel::AddMesh(Ref<Mesh> mesh)
	{
		if (mesh != nullptr)
		{
			m_meshes.push_back(mesh);
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

	void ZModel::ProcessNode(aiNode* node, const aiScene* scene, const MATRIX4& parentTransformMatrix)
	{
		MATRIX4 nodeMatrix = MATRIX4(
			(float)node->mTransformation.a1, (float)node->mTransformation.a2, (float)node->mTransformation.a3, (float)node->mTransformation.a4,
			(float)node->mTransformation.b1, (float)node->mTransformation.b2, (float)node->mTransformation.b3, (float)node->mTransformation.b4,
			(float)node->mTransformation.c1, (float)node->mTransformation.c2, (float)node->mTransformation.c3, (float)node->mTransformation.c4,
			(float)node->mTransformation.d1, (float)node->mTransformation.d2, (float)node->mTransformation.d3, (float)node->mTransformation.d4
			);
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

	Ref<Mesh> ZModel::ProcessMesh(aiMesh* mesh, const aiScene* scene, const MATRIX4& transformMatrix)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		UINT nv = 0;

		//float* verts = new float[12 * mesh->mNumVertices];
		for (UINT i = 0; i < mesh->mNumVertices; i++)
		{
			/*
			//position
			verts[(i * 12)]	 =	(float)mesh->mVertices[i].x*0.01;
			verts[(i * 12) + 1] = (float)mesh->mVertices[i].y * 0.01;
			verts[(i * 12) + 2] = (float)mesh->mVertices[i].z * 0.01;
			verts[(i * 12) + 3] = 1.0f;
			//normal
			verts[(i * 12) + 4] = (float)mesh->mNormals[i].x;
			verts[(i * 12) + 5] = (float)mesh->mNormals[i].y;
			verts[(i * 12) + 6] = (float)mesh->mNormals[i].z;
			//color
			verts[(i * 12) + 7] = 1.0f;
			verts[(i * 12) + 8] = 1.0f;
			verts[(i * 12) + 9] = 1.0f;
			//uv
			verts[(i * 12) + 10] = (float)mesh->mTextureCoords[0][i].x;
			verts[(i * 12) + 11] = (float)mesh->mTextureCoords[0][i].y;
			
			/*
			*/
			Vertex vertex;

			vertex.position.x = (float)mesh->mVertices[i].x * 0.01;
			vertex.position.y = (float)mesh->mVertices[i].y * 0.01;
			vertex.position.z = (float)mesh->mVertices[i].z * 0.01;
			vertex.position.w = 1.0f;
			vertex.color.x = 1.0f;
			vertex.color.y = 1.0f;
			vertex.color.z = 1.0f;
			vertex.normal.x = (float)mesh->mNormals[i].x;
			vertex.normal.y = (float)mesh->mNormals[i].y;
			vertex.normal.z = (float)mesh->mNormals[i].z;

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


		aiString mname;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		mname = material->mProperties[AI_MATKEY_NAME]->mData;

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
		printf("Setting Mesh Data vertices: %u size %u \n", (uint32_t)nv, (uint32_t)((sizeof(float)*12)*nv));
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
		printf("Texture Count: %u \n", textureCount);
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
					printf("Creating black color texture \n");
					return;
				}
				//material->LoadTexture(1, 1, COLOR4(aiColor.r, aiColor.g, aiColor.b).ToColor());
				printf("Creating rgb color texture \n");
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
					printf("Embedded Indexed Compressed Texture \n");
					//int index = GetTextureIndex(&path);
					//Texture embeddedIndexTexture(reinterpret_cast<uint8_t*>(pscene->mTextures[index]->pcData), pscene->mTextures[index]->mWidth, textype);
					//materialTextures.push_back(embeddedIndexTexture);
					break;
				}
				case AssimpTextureStorageType::EmbeddedCompressed:
				{
					printf("Embedded Texture \n");
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

	AssimpTextureStorageType ZModel::DetermineTextureStorageType(const aiScene* pscene, aiMaterial* pmaterial, unsigned int index, aiTextureType textype)
	{
		if (pmaterial->GetTextureCount(textype) == 0)
		{
			printf("No Textures \n");
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
				printf("Embedded Indexed Compressed Texture\n");
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

	int ZModel::GetTextureIndex(aiString* pStr)
	{
		assert(pStr->length >= 2);
		return atoi(&pStr->C_Str()[1]);
	}


}
