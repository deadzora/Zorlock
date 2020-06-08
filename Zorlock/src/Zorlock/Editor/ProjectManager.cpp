#include "ZLpch.h"
#include "ProjectManager.h"
#include "Projects.h"

namespace Zorlock
{

	namespace fs = std::filesystem;

	static ProjectManager* pmanager = nullptr;

	ProjectManager::ProjectManager() : m_projects(nullptr), enginedir(""), newproject(true), m_projectinfo(nullptr), projectloaded(false)
	{
		Project* p = new Project();
		p->Name("My Project");
		std::string appdir = std::getenv("HOMEPATH");
		appdir += "\\Documents\\ZorlockEngine";
		p->Directory(appdir);
		m_new_project = p;
		m_current_project = p;
		
	}

	ProjectManager::~ProjectManager()
	{
	}

	ProjectManager* ProjectManager::Get()
	{
		if (pmanager == nullptr)
		{
			pmanager = new ProjectManager();
		}
		return pmanager;
	}

	Projects* ProjectManager::GetProjects()
	{
		if (m_projects != nullptr)
			return m_projects.get();

		Projects* p = new Projects();
		m_projects = Ref<Projects>(p);

		//check if application appdata dir exists
		std::string appdir = std::getenv("APPDATA");
		appdir += "\\ZorlockEngine";
		printf("App data dir %s \n", appdir.c_str());
		if(!fs::exists(appdir))
		{
			if (fs::create_directory(appdir))
			{
				enginedir = appdir;
			}
			else {
				printf("Could not create engine dir \n");
			}

			return m_projects.get();
		}
		else {


			projectsfile = appdir + "\\Projects.json";
			if (fs::exists(projectsfile))
			{
				m_projects->DeserializeFromFile(projectsfile);
				
			}
		}
		return m_projects.get();
	}

	void ProjectManager::SetNewProject()
	{
		m_current_project = m_new_project;
		newproject = true;
	}

	void ProjectManager::SetProject(size_t i)
	{
		Project* p = m_projects->GetProject(i);
		if (p == nullptr)
		{
			m_current_project = m_new_project;
			newproject = true;
		}
		else {
			m_current_project = p;
			newproject = false;
		}
	}

	bool ProjectManager::CreateProject()
	{
		if(!newproject)
			return false;

		m_projectinfo = new ProjectInfo(m_current_project->Name(), m_current_project->Directory() + "\\" + m_current_project->Name() + "\\assets");

		if (!fs::exists(m_current_project->Directory()))
		{
			if (!fs::create_directory(m_current_project->Directory()))
			{
				return false;
			}
		}
		if (!fs::exists(m_current_project->Directory() + "\\" + m_current_project->Name()))
		{
			if (fs::create_directory(m_current_project->Directory() + "\\" + m_current_project->Name()))
			{
				if (fs::create_directory(m_current_project->Directory() + "\\" + m_current_project->Name() + "\\assets"))
				{
					m_projectinfo->SerializeToFile(m_current_project->Directory() + "\\" + m_current_project->Name() + "\\project_info.json");
				}
				else {
					printf("Could not create assets dir \n");
				}
			}
			else {
				printf("Could not create project dir \n");
			}
		}
		
		m_projects->AddProject(m_current_project);
		m_projects->SerializeToFile(projectsfile);
		projectloaded = true;
		return true;
	}

	bool ProjectManager::LoadProject()
	{
		if (newproject)
			return false;

		if (fs::exists(m_current_project->Directory() + "\\" + m_current_project->Name() + "\\project_info.json"))
		{
			m_projectinfo = new ProjectInfo(m_current_project->Name(), m_current_project->Directory() + "\\" + m_current_project->Name() + "\\assets");
			m_projectinfo->DeserializeFromFile(m_current_project->Directory() + "\\" + m_current_project->Name() + "\\project_info.json");
			projectloaded = true;
			return true;
		}
		return false;
	}

	std::string ProjectManager::GetCurrentProjectName()
	{
		return m_current_project->Name();
	}

}
