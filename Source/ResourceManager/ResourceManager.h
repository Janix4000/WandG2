#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template<typename Resource>

class ResourceManager
{
public:
	ResourceManager(const std::string& folder, const std::string& extention)
		:
		folderName("Resources/" + folder + "/"),
		extention("." + extention)
	{
		auto pFail = std::make_shared<Resource>();
		const std::string fullName = getFullFileName("_fail_");

		pFail->loadFromFile(fullName);
		resourcePtrs.insert({ "_fail_",pFail });
	}

public:

	std::shared_ptr<Resource> acquire(const std::string& name)
	{
		const auto i = resourcePtrs.find(name);
		if (i != resourcePtrs.end())
		{
			return i->second;
		}
		else
		{
			auto pRes = std::make_shared<Resource>();
			const std::string fullName = getFullFileName(name);

			if (pRes->loadFromFile(fullName))
			{
				resourcePtrs.insert({ name,pRes });
				return pRes;
			}
			else
			{
				std::cout << "Failed to load from " << folderName << "\n";
				return resourcePtrs.find("_fail_")->second;
			}
		}

	}
	void deleteAditional()
	{
		for (auto i = resourcePtrs.begin(); i != resourcePtrs.end(); )
		{
			if (i->second.unique())
			{
				i = resourcePtrs.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Resource>> resourcePtrs;
	std::string folderName;
	std::string extention;

private:
	std::string getFullFileName(const std::string name) const
	{
		return folderName + name + extention;
	}

};

using TextureManager = ResourceManager<sf::Texture>;
using FontManager = ResourceManager<sf::Font>;
using SoundBufferManager = ResourceManager<sf::SoundBuffer>;