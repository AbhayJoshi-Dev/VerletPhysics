#include<iostream>

#include"AssetManager.h"

AssetManager::~AssetManager()
{
	for (const auto& asset : m_assetMap)
	{
		SDL_DestroyTexture(asset.second);
	}
}

void AssetManager::Load(SDL_Renderer* renderer, const std::string& key, const std::string& filePath)
{
	SDL_Texture* tex = NULL;
	
	tex = IMG_LoadTexture(renderer, filePath.c_str());

	if (tex == NULL)
		std::cout << "Texture not loaded! " << SDL_GetError() << std::endl;

	m_assetMap[key] = IMG_LoadTexture(renderer, filePath.c_str());
}

SDL_Texture* AssetManager::Get(const std::string& key) const
{
	SDL_Texture* texture = NULL;

	if (m_assetMap.find(key) != m_assetMap.end())
	{
		texture = m_assetMap.at(key);
	}

	return texture;
}