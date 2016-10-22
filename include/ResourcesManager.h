#ifndef DEF_RESSOURCESMANAGER
#define DEF_RESSOURCESMANAGER

#include <iostream>
#include <map>

/** \brief template for the destructor of ResourcesManager. Done nothing (destructor empty) */
template <typename T>
struct clean
{
	/** \brief the release function. This function do nothing (it like a null release)
	 * \param v the ResourcesManager value to 'release' */
	static void release(T const& v)
	{

	}
};

/** \brief template for the destructor of ResourcesManager. Delete pointer if not NULL.*/
template <typename T>
struct clean<T*>
{
	/** \brief if v is not null, delete it from the memory
	 * \param v the ResourcesManager value to release*/
	static void release(T * v)
	{
		if(v)
			delete v;
		v = NULL;
	}
};

/** \brief template for the destructor of ResourcesManager. Delete dynamic array.*/
template <typename T>
struct clean_array
{
	/** \brief release the dynamic array
	 * \param v the ResourcesManager dynamic array to release */
	static void release(T * v)
	{
		delete[] v;
	}
};

/** \brief Manage an array of resources. If you use pointer and don't want to an auto deallocation, set CT.
 * */
template <typename T, typename CT = clean<T> >
class ResourcesManager
{
	typedef std::string keyType;
	typedef CT cleanning_traits;
	typedef typename std::map<std::string, T>::iterator iterator;
public:
	/** \brief Create an empty array */
	ResourcesManager();

	/** \brief ResourcesManager destructor. Call CT::release() for each resources.*/
	~ResourcesManager();

	/** \brief add on the array the object type associated with the string name
	 * \param name The object key type 
	 * \param type The object*/
	void add(const std::string &name, const T &type);

	/** \brief remove the object from its key
	 * \param name The object key */
	bool remove(const std::string &name);

	/** \brief remove the object from itself. It use the object equality
	 * \param resource The object to remove (a pointer for example) */
	bool remove(const T &resource);

	/** \brief get the object from its key
	 * \param name the object key 
	 * \return The object reference */
	T &get(const std::string &name);

	/** \brief get the key object from its resource 
	 * \param resource the object resource
	 * \return the key*/
	const std::string &get(const T &resource) const;

	/** \brief tell if the key exist on the array
	 * \param name the object key 
	 * \return Tell if it exist */
	bool exist(const std::string &name) const;

	/** \brief tell if the object exist on the array
	 * \param resource the object 
	 * \return Tell if it exists */
	bool exist(const T &resource) const;
	
	void clean();

	int getSize() const;
	iterator begin()
	{
		return m_resources.begin();
	}

	iterator end()
	{
		return m_resources.end();
	}
protected:
	std::map <std::string, T> m_resources;
};

template <typename T, typename CT>
 ResourcesManager<T, CT>::ResourcesManager()
{

}

template <typename T, typename CT>
 ResourcesManager<T, CT>::~ResourcesManager()
{
	for(auto & p : m_resources)
		CT::release(p.second);
}

template <typename T, typename CT>
 void ResourcesManager<T, CT>::add(const std::string &name, const T &type)
{
	if(m_resources.find(name) == m_resources.end())
		m_resources.insert(std::make_pair(name, type));
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::remove(const std::string &name)
{
	if(exist(name))
	{
		CT::release(m_resources[name]);
		m_resources.erase(name);
		return true;
	}
	return false;
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::remove(const T& resource)
{
	for(typename std::map<std::string, T>::iterator it = m_resources.begin(); it != m_resources.end(); ++it)
		if(it->second == resource)
		{
			cleanning_traits::release(it->second);
			m_resources.erase(it);
			return true;
		}

	return false;
}

template <typename T, typename CT>
 T &ResourcesManager<T, CT>::get(const std::string &name)
{
	return m_resources.find(name)->second;
}

template <typename T, typename CT>
 void ResourcesManager<T, CT>::clean()
{
	for(auto & p : m_resources)
		CT::release(p.second);
	m_resources.clear();
}

template <typename T, typename CT>
 const std::string  &ResourcesManager<T, CT>::get(const T &resource) const
{
	for(typename std::map<std::string, T>::const_iterator it=m_resources.begin(); it != m_resources.end(); ++it)
		if(it->second == resource)
			return it->first;
	
	std::cout << "The resource isn't in this ResourceManager. This function return the first key std::string" << std::endl;
	return m_resources.begin()->first;
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::exist(const std::string &name) const
{
	if(m_resources.find(name) == m_resources.end())
		return false;
	return true;
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::exist(const T &resource) const
{
	for(typename std::map<std::string, T>::iterator it = m_resources.begin(); it != m_resources.end(); ++it)
		if(it == &resource)
			return true;
	return false;
}

template <typename T, typename CT>
 int ResourcesManager<T, CT>::getSize() const
{
	return m_resources.size();
}

#endif
