#include "ZLpch.h"
#include "Assets.h"
#include <rpc.h>

namespace Zorlock
{
	void Asset::GetUUID()
	{
#ifdef ZL_PLATFORM_WINDOWS
		UUID uuid;
		RPC_STATUS s = UuidCreate(&uuid);
		HRESULT hr = HRESULT_FROM_WIN32(s);
		if (SUCCEEDED(hr))
		{
			RPC_STATUS ss = UuidToStringA(&uuid, (RPC_CSTR*)&m_uuid);
			HRESULT hrr = HRESULT_FROM_WIN32(ss);
			if (SUCCEEDED(hrr))
			{

			}
		}
#endif		

	}
	void Asset::SetUUID(std::string u)
	{
#ifdef ZL_PLATFORM_WINDOWS
		UUID uuid;
		RPC_STATUS s = UuidFromStringA((RPC_CSTR)u.c_str(), &uuid);
		HRESULT hr = HRESULT_FROM_WIN32(s);
		if (SUCCEEDED(hr))
		{

		}
#endif
	}
	bool Asset::Deserialize(const rapidjson::Value& obj)
	{
		Name(obj["name"].GetString());
		FilePath(obj["filepath"].GetString());
		AssetUUID(obj["uuid"].GetString());
		AssetType(obj["type"].GetString());
		return true;
	}
	bool Asset::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		writer->String("name");
		writer->String(_name.c_str());
		writer->String("filepath");
		writer->String(_filepath.c_str());
		writer->String("uuid");
		writer->String(m_uuid.c_str());
		writer->String("type");
		writer->String(m_asset_type.c_str());
		writer->EndObject();
		return true;
	}
	AssetLibrary::AssetLibrary()
	{
		
	}
	AssetLibrary::~AssetLibrary()
	{
	}

	bool AssetLibrary::Deserialize(const std::string& s)
	{
		rapidjson::Document doc;
		if (!InitDocument(s, doc))
			return false;

		if (!doc.IsArray())
			return false;

		for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
		{
			Asset a;
			a.Deserialize(*itr);
			m_assets.push_back(a);
		}

		return true;
	}

	bool AssetLibrary::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartArray();

		for (size_t i = 0; i < m_assets.size(); i++)
		{
			m_assets[i].Serialize(writer);
		}
		writer->EndArray();

		return true;
	}

}
