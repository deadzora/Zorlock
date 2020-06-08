#pragma once


namespace Zorlock
{
	class Projects;
	class Project;
	class ProjectInfo;

	class ProjectManager
	{
	public:
		ProjectManager();
		~ProjectManager();
		static ProjectManager* Get();
		Projects* GetProjects();
		void SetNewProject();
		void SetProject(size_t i);
		bool IsNewProject()
		{
			return newproject;
		}
		bool IsProjectLoaded()
		{
			return projectloaded;
		}
		Project* GetCurrentProject()
		{
			return m_current_project;
		}
		bool CreateProject();
		bool LoadProject();
		std::string GetCurrentProjectName();
	protected:
		bool newproject;
		bool projectloaded;
		Project* m_new_project;
		Project* m_current_project;
		ProjectInfo* m_projectinfo;
		Ref<Projects> m_projects;
		std::string enginedir;
		std::string projectsfile;
	};
}

#define ZLPROJECTMANAGER Zorlock::ProjectManager