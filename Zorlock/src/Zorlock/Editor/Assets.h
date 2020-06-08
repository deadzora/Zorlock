#pragma once
#include "Zorlock/Json/ZJSONBase.h"
#include <map>
namespace Zorlock
{

	enum class AssetType
	{
		ZL_None = 0,
		ZL_Scene = 1,
		ZL_GameObject = 2,
		ZL_Camera = 3,
		ZL_Camera2D = 4,
		ZL_Light = 5
	};

	class Asset : ZJSONBase
	{
	public:
		Asset() {};
		virtual ~Asset() {};
		void GetUUID();
		void SetUUID(std::string u);
		ZGetSet(std::string, Name, _name)
		ZGetSet(std::string, FilePath, _filepath)
		ZGetSet(std::string, AssetUUID, m_uuid)
		ZGetSet(std::string, AssetType, m_asset_type)

		virtual bool Deserialize(const rapidjson::Value& obj) override;
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const override;
	protected:
		std::string m_asset_type;
		std::string m_uuid;
		std::string _filepath;
		std::string _name;
		
	};


	class AssetLoader
	{

	};

	class AssetLibrary : ZJSONBase
	{
	public:
		AssetLibrary();
		virtual ~AssetLibrary();
	public:
		virtual bool Deserialize(const std::string& s) override;
		virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const override;
		
	protected:
		std::vector<Asset> m_assets;

	};

}