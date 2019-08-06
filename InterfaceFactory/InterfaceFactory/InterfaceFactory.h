#pragma once

#include <map>
#include <memory>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <any>
#include <stdexcept>
#include <string>
#include <iostream>

class InterfaceFactory;

class InterfaceFactoryDestroyer
{
public:
	~InterfaceFactoryDestroyer();
	void initialize(InterfaceFactory* pObj);

private:
	InterfaceFactory* m_pInstance;
};

class InterfaceFactory
{
public:
	template <class TInterface>
	class ScopedUnreg
	{
	public:
		ScopedUnreg(InterfaceFactory &factory) : m_ObjectIndex(std::type_index(typeid(TInterface))), m_Factory(factory)	{}
		ScopedUnreg(ScopedUnreg && other) : m_ObjectIndex(other.m_ObjectIndex), m_Factory(other.m_Factory)	{}
		~ScopedUnreg()
		{
			m_Factory.Unregister(m_ObjectIndex);
		}

	private:
		ScopedUnreg(const ScopedUnreg& other) = delete;
		ScopedUnreg& operator = (const ScopedUnreg& other) = delete;

		std::type_index m_ObjectIndex;
		InterfaceFactory& m_Factory;
	};

	template<class TInterface>
	inline bool IsRegistered() const;

	template<class TInterface>
	inline void Register(std::function<std::unique_ptr<TInterface>()> i_create_proc);

	template<class TInterface, class TImplementation>
	inline void Register();

	template<class TInterface, class TImplementation>
	inline std::unique_ptr <ScopedUnreg<TInterface>> RegisterScoped();

	template<class TInterface>
	inline void Unregister();

	inline void Unregister(std::type_index InterfaceTypeIndex);

	template<class TInterface>
	inline std::unique_ptr<TInterface> Create() const;

	template<class TInterface>
	inline TInterface* CreateRaw() const;

	static InterfaceFactory& Instance();

private:
	InterfaceFactory() {}
	InterfaceFactory(const InterfaceFactory& other) = delete;
	InterfaceFactory& operator = (const InterfaceFactory& other) = delete;

	friend class InterfaceFactoryDestroyer;

	static InterfaceFactoryDestroyer m_Destroyer;
	static InterfaceFactory* m_pInstance;
	std::map <std::type_index, std::any> m_ImplsMap;
};



InterfaceFactoryDestroyer::~InterfaceFactoryDestroyer()
{
	delete m_pInstance;
}

void InterfaceFactoryDestroyer::initialize(InterfaceFactory* pObj)
{
	m_pInstance = pObj;
}


InterfaceFactory* InterfaceFactory::m_pInstance = nullptr;
InterfaceFactoryDestroyer InterfaceFactory::m_Destroyer;

template<class TInterface>
bool InterfaceFactory::IsRegistered() const
{
	auto Iter = m_ImplsMap.find(std::type_index(typeid(TInterface)));

	if (m_ImplsMap.end() == Iter)
	{
		return false;
	}
	return true;
}

template<class TInterface>
void InterfaceFactory::Register(std::function<std::unique_ptr<TInterface>()> i_create_proc)
{
	if (IsRegistered<TInterface>())
	{
		throw std::logic_error("It is aleady present an implementation of the " + std::string(typeid(TInterface).name()));
	}
	m_ImplsMap.insert(std::make_pair<std::type_index, std::any>(std::type_index(typeid(TInterface)),
				      std::make_any<std::function< std::unique_ptr<TInterface>()>>(i_create_proc)));
}

template<class TInterface, class TImplementation>
void InterfaceFactory::Register()
{
	if(IsRegistered<TInterface>())
	{
		throw std::logic_error("It is aleady present an implementation of the " + std::string(typeid(TInterface).name()));
	}
	std::function<std::unique_ptr<TInterface>()> func = []
	{
		return std::make_unique<TImplementation>();
	};
	m_ImplsMap.insert(std::make_pair<std::type_index, std::any>(std::type_index(typeid(TInterface)),
					  std::make_any<std::function< std::unique_ptr<TInterface>()>>(func)));
}

template<class TInterface, class TImplementation>
std::unique_ptr <InterfaceFactory::ScopedUnreg<TInterface>> InterfaceFactory::RegisterScoped()
{
	if (IsRegistered<TInterface>())
	{
		throw std::logic_error("It is aleady present an implementation of the " + std::string(typeid(TInterface).name()));
	}
	std::function<std::unique_ptr<TInterface>()> func = []
	{
		return std::make_unique<TImplementation>();
	};
	m_ImplsMap.insert(std::make_pair<std::type_index, std::any>(std::type_index(typeid(TInterface)),
		std::make_any<std::function< std::unique_ptr<TInterface>()>>(func)));	

	return std::make_unique<ScopedUnreg<TInterface>>(Instance());
}

template<class TInterface>
void InterfaceFactory::Unregister()
{
	Unregister(std::type_index(typeid(TInterface)));
}

void InterfaceFactory::Unregister(std::type_index InterfaceTypeIndex)
{
	auto Iter = m_ImplsMap.find(InterfaceTypeIndex);

	if (m_ImplsMap.end() != Iter)
	{
		m_ImplsMap.erase(Iter);
	}
}

template<class TInterface>
std::unique_ptr<TInterface> InterfaceFactory::Create() const
{
	auto Iter = m_ImplsMap.find(std::type_index(typeid(TInterface)));

	if (m_ImplsMap.end() != Iter)
	{
		auto func = std::any_cast<std::function<std::unique_ptr<TInterface>()>>(Iter->second);

		return func();
	}
	else
	{
		throw std::logic_error("There are none present implementation of the " + std::string(typeid(TInterface).name()));
	}
}

template<class TInterface>
TInterface* InterfaceFactory::CreateRaw() const
{
	auto Iter = m_ImplsMap.find(std::type_index(typeid(TInterface)));

	if (m_ImplsMap.end() != Iter)
	{
		auto func = std::any_cast<std::function<std::unique_ptr<TInterface>()>>(Iter->second);

		return func().release();
	}
	else
	{
		throw std::logic_error("There are none present implementation of the " + std::string(typeid(TInterface).name()));
	}
}

InterfaceFactory& InterfaceFactory::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new InterfaceFactory;
		m_Destroyer.initialize(m_pInstance);
	}		
	return *m_pInstance;
}

