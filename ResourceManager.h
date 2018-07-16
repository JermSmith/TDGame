#pragma once

#include <unordered_map>
#include <string>

/* Holds all the resources of the game in an unordered map */

template<typename Resource>
class ResourceManager
{
public:
	ResourceManager(const std::string& folder, const std::string& extension)
		: m_folder("res/" + folder + "/"), m_extension("." + extension) { }

	Resource& get(const std::string& name)
	{
		if (!exists(name))
		{
			add(name);
		}

		return m_resources.at(name);
	}

	bool exists(const std::string& name) const
	{
		return m_resources.find(name) != m_resources.end();

		// .find(name) returns an iterator to the element if the element exists, but
		// .find(name) returns an iterator to .end() if the element doesn't exist.
	}

	void add(const std::string& name)
	{
		Resource r;

		//if the resource fails to load, then it adds a default "fail" resource
		if (!r.loadFromFile(getFullFilename(name)))
		{
			Resource fail;
			fail.loadFromFile(m_folder + "_fail_" + m_extension);
			m_resources.insert(std::make_pair(name, fail));
		}
		else
		{
			m_resources.insert(std::make_pair(name, r));
		}
	}

private:
	std::string getFullFilename(const std::string& name)
	{
		return m_folder + name + m_extension;
	}

	const std::string m_folder;
	const std::string m_extension;

	std::unordered_map<std::string, Resource> m_resources;
};