#include "ZLpch.h"
#include "JSONIncludes.h"
#include <string>
#include "ZJSONBase.h"
#include <fstream>
#include <sstream>

namespace Zorlock
{

	std::string ZJSONBase::Serialize() const
	{
		rapidjson::StringBuffer ss;
		rapidjson::Writer<rapidjson::StringBuffer> writer(ss);		// Can also use Writer for condensed formatting
		if (Serialize(&writer))
			return ss.GetString();
		return "";
	}

	bool ZJSONBase::Deserialize(const std::string& s)
	{
		rapidjson::Document doc;
		if (!InitDocument(s, doc))
			return false;

		Deserialize(doc);

		return true;
	}

	bool ZJSONBase::DeserializeFromFile(const std::string& filePath)
	{
		std::ifstream f(filePath);
		std::stringstream buffer;
		buffer << f.rdbuf();
		f.close();

		return Deserialize(buffer.str());
	}

	bool ZJSONBase::SerializeToFile(const std::string& filePath)
	{
		std::ofstream f(filePath);
		std::string s = Serialize();
		f << s;
		f.flush();
		f.close();

		return true;
	}

	bool ZJSONBase::InitDocument(const std::string& s, rapidjson::Document& doc)
	{
		if (s.empty())
			return false;

		std::string validJson(s);

		return !doc.Parse(validJson.c_str()).HasParseError() ? true : false;
	}

}