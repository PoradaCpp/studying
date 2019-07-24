#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <type_traits>
#include <memory>

template <typename UnusedType>
class function;

template <typename T, typename ...Args>
class function<T(Args...)>
{
public:
	function() {}

	template <typename Type>
	function(Type object): m_pObject(new Object<Type>(object)) {}

	function(const function& other): m_pObject(other.m_pObject->clone()) {}

    ~function() {}

	template <typename Type>
	function<T(Args...)>& operator = (Type object)
	{
		m_pObject = std::make_unique<Object<Type>>(object);
		return *this;
	}

	T operator () (Args ...args)
	{
		return m_pObject->action(args...);
	}

	operator bool()
	{
		return m_pObject.operator bool();
	}

private:
    class ObjectBase
    {
    public:
		ObjectBase() {}
        virtual ~ObjectBase() {}
		virtual T action (Args ...args) = 0;
		virtual ObjectBase* clone() = 0;
    };

    template <typename Type>
    class Object: public ObjectBase
    {
    public:
		Object(Type object): ObjectBase(), m_Object(object) {}
        ~Object() override {}

		virtual T action(Args ...args) override
		{
			return m_Object(args...);
		}

		virtual ObjectBase* clone() override
		{
			return new Object<Type>(*this);
		}

    private:
        Type m_Object;
    };

	std::unique_ptr<ObjectBase> m_pObject = nullptr;
};


#endif // FUNCTION_HPP
