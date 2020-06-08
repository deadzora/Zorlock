#include "ZLpch.h"
#include "Projects.h"


namespace Zorlock
{


	Project::Project() : _name("project")
	{

	}

	Zorlock::Project::~Project()
	{
	}

	bool Project::Deserialize(const rapidjson::Value& obj)
	{
		Name(obj["name"].GetString());
		Directory(obj["directory"].GetString());
		return true;
	}

	bool Project::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		writer->String("name");
		writer->String(_name.c_str());
		writer->String("directory");
		writer->String(_directory.c_str());

		writer->EndObject();
		return true;
	}

	bool Projects::Deserialize(const std::string& s)
	{
		rapidjson::Document doc;
		if (!InitDocument(s, doc))
			return false;

		if (!doc.IsArray())
			return false;

		for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
		{
			Project p;
			p.Deserialize(*itr);
			_projects.push_back(p);
		}

		return true;
	}

	Project* Projects::GetProject(size_t i)
	{
		if (i < _projects.size())
		{
			return &_projects[i];
		}
		return nullptr;
	}

	bool Projects::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartArray();

		for (size_t i = 0; i < _projects.size(); i++)
		{
			_projects[i].Serialize(writer);
		}
		writer->EndArray();

		return true;
	}
	

	ProjectInfo::ProjectInfo() : _name("projectinfo"), _assetsdir("")
	{
	}

	ProjectInfo::ProjectInfo(std::string name, std::string dir) : _name(name), _assetsdir(dir)
	{
	}

	ProjectInfo::~ProjectInfo()
	{
	}

	bool ProjectInfo::Deserialize(const rapidjson::Value& obj)
	{
		Name(obj["name"].GetString());
		AssetDirectory(obj["assetdirectory"].GetString());
		return true;
	}

	bool ProjectInfo::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		writer->String("name");
		writer->String(_name.c_str());
		writer->String("assetdirectory");
		writer->String(_assetsdir.c_str());

		writer->EndObject();
		return true;
	}

}