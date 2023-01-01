#include<iostream>

#include"AssetManager.h"

AssetManager::~AssetManager()
{
	for (const auto& asset : m_asset_map)
		SDL_DestroyTexture(asset.second);
}

AssetManager& AssetManager::GetInstance()
{
	static AssetManager* instance = new AssetManager;

	return *instance;
}

void AssetManager::Load(SDL_Renderer* renderer, const std::string& key, const std::string& filePath)
{
	SDL_Texture* tex = NULL;

	tex = IMG_LoadTexture(renderer, filePath.c_str());
	if (tex == NULL)
		std::cout << "Texture not Loaded!" << SDL_GetError() << std::endl;

	m_asset_map[key] = tex;
}

SDL_Texture* AssetManager::Get(const std::string& key) const
{
	SDL_Texture* tex = NULL;

	if (m_asset_map.find(key) != m_asset_map.end())
		tex = m_asset_map.at(key);

	return tex;
}

SDL_Texture* AssetManager::LoadTexture(SDL_Renderer* renderer, const std::string& key, const std::string& filePath)
{
	SDL_Texture* tex = NULL;
	if (m_asset_map.find(key) != m_asset_map.end())
	{
		return m_asset_map.at(key);
	}
	else
	{
		tex = IMG_LoadTexture(renderer, filePath.c_str());
		if (tex == NULL)
			std::cout << "Texture not Loaded!" << SDL_GetError() << std::endl;

		m_asset_map[key] = tex;
		return tex;
	}
}