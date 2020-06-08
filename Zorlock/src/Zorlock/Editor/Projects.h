#pragma once
#include "Zorlock/Json/ZJSONBase.h"

namespace Zorlock
{

	class Project : public ZJSONBase
	{
	public:
		Project();
		virtual ~Project();
		ZGetSet(std::string,Name,_name)
		ZGetSet(std::string, Directory, _directory)
		virtual bool Deserialize(const rapidjson::Value& obj) override;
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const override;

	protected:
		std::string _name;
		std::string _directory;
	};

	class ProjectInfo : public ZJSONBase
	{
	public:
		ProjectInfo();
		ProjectInfo(std::string name, std::string dir);
		virtual ~ProjectInfo();
		ZGetSet(std::string, Name, _name)
		ZGetSet(std::string, AssetDirectory, _assetsdir)
		virtual bool Deserialize(const rapidjson::Value& obj) override;
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const override;
	protected:
		std::string _name;
		std::string _assetsdir;

	};

	class Projects : public ZJSONBase
	{
	public:
		virtual ~Projects() {};
		virtual bool Deserialize(const std::string& s) override;
		Project* GetProject(size_t i);
		void AddProject(Project* p)
		{
			_projects.push_back(*p);
		}
		// Getters/Setters.
		std::vector<Project>& ProjectsList() { return _projects; }
	public:
		virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const override;
	private:
		std::vector<Project> _projects;
	};



}

