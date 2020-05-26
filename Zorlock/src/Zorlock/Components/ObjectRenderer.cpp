#include "ZLpch.h"
#include "ObjectRenderer.h"
#include "Zorlock/Game/SceneManager.h"

namespace Zorlock
{

	ObjectRenderer::ObjectRenderer()
	{
	}

	ObjectRenderer::ObjectRenderer(std::string name)
	{
		this->name = name;
	}

	ObjectRenderer::~ObjectRenderer()
	{
	}

	void ObjectRenderer::Awake()
	{
	}

	void ObjectRenderer::Start()
	{
	}

	void ObjectRenderer::Update(Timestep ts)
	{
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			//m_materials[i]->SetViewMatrix(ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetViewMatrix() * ZLSCENEMANAGER::GetInstance()->GetActiveScene()->MainCamera()->GetProjectionMatrix());

		}
	}

	void ObjectRenderer::Render()
	{
	}

	void ObjectRenderer::Destroy()
	{
	}

	void ObjectRenderer::AddMaterial(Ref<Material> material)
	{
		m_materials.push_back(material);
	}

	void ObjectRenderer::AddMaterial(Ref<Material> material, size_t index)
	{
		if (index > m_materials.size() - 1)
		{
			if (m_materials.size() > 0)
			{

				m_materials.resize((size_t)index + 1, m_materials[m_materials.size() - 1]);
				m_materials[index].swap(material);
			}
			else {
				m_materials.resize((size_t)index + 1, material);
				m_materials[index].swap(material);
			}
		}
		else {
			m_materials[index].swap(material);
		}
	}

	void ObjectRenderer::RemoveMaterial(size_t index)
	{
		if (index < m_materials.size())
		{
			m_materials.erase(m_materials.begin() + index);
			m_materials.shrink_to_fit();
		}
	}

	void ObjectRenderer::RemoveMaterial(Ref<Material> material)
	{
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			if (m_materials[i] == material)
			{
				m_materials.erase(m_materials.begin() + i);
				m_materials.shrink_to_fit();
			}
		}
	}

	Ref<Material> ObjectRenderer::GetMaterial(size_t index)
	{
		if (index < m_materials.size())
		{
			return m_materials[index];
		}
		return nullptr;
	}

	Ref<Material> ObjectRenderer::GetMaterial(std::string matname)
	{
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			if (m_materials[i]->name.compare(matname) == 0)
			{
				return m_materials[i];
			}
		}
		return nullptr;
	}
}