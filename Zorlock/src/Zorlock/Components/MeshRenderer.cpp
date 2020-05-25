#include "ZLpch.h"
#include "MeshRenderer.h"
#include "Zorlock/Renderer/RendererAPI.h"
#include "Zorlock/Renderer/Model.h"
#include "Zorlock/Game/SceneManager.h"
namespace Zorlock
{

	MeshRenderer::MeshRenderer()
	{
	}

	MeshRenderer::MeshRenderer(std::string name)
	{
		this->name = name;
	}

	MeshRenderer::~MeshRenderer()
	{
	}



	void MeshRenderer::Awake() 
	{
	}

	void MeshRenderer::Start() 
	{

	}

	Ref<Model> MeshRenderer::GetModel(uint32_t index)
	{
		if (index < m_models.size())
		{
			return m_models[index];
		}
		return nullptr;
	}


	void MeshRenderer::Update(Timestep ts) 
	{
		
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			m_materials[i]->SetViewMatrix(ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetViewMatrix() * ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetProjectionMatrix());
			
		}

		for (size_t i = 0; i < m_models.size(); i++)
		{
			m_models[i]->Update(ts);
		}
	}

	void MeshRenderer::Render()
	{
		for (size_t i = 0; i < m_models.size(); i++)
		{
			m_models[i]->Draw();
		}
	}

	void MeshRenderer::Destroy() 
	{
		for (size_t i = 0; i < m_models.size(); i++)
		{
			m_models[i]->Destroy();
		}
	}

	bool MeshRenderer::AddModel(const std::string& name, const std::string& filename)
	{
		Ref<Model> model = Ref<Model>(new Model("model", filename, Ref<MeshRenderer>(this)));
		m_models.push_back(model);
		return true;

	}

	void MeshRenderer::RemoveModel(std::string name)
	{
		for (size_t i = 0; i < m_models.size(); i++)
		{
			if (m_models[i]->name.compare(name) == 0)
			{
				m_models.erase(m_models.begin() + i);
				m_models.shrink_to_fit();
			}
		}
	}
	void MeshRenderer::RemoveModel(Ref<Model> model)
	{
		for (size_t i = 0; i < m_models.size(); i++)
		{
			if (m_models[i]==model)
			{
				m_models.erase(m_models.begin() + i);
				m_models.shrink_to_fit();
			}
		}
	}
}