#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <iostream>
#include <type_traits>

template <typename T, typename ...Args>
class Variant
{
public:
    ~Variant()
    {
        if(m_pObject)
        {
            delete m_pObject;
        }
    }

    template<typename Type>
    Variant& operator = (Type&& object);

    template<typename Type>
    Type get();

private:
    template<typename Type, typename ...TypeArgs>
    struct SaveTypes
    {
        template <typename U>
        static bool check(bool *pArr, bool fWrite = false);
    };

    template <typename Type>
    struct SaveTypes<Type>
    {
        template <typename U>
        static bool check(bool *pArr, bool fWrite = false);
    };

    class ObjectBase
    {
    public:
        ObjectBase() {}
        virtual ~ObjectBase() {}
    };

    template <typename Type>
    class Object: public ObjectBase
    {
    public:
        Object(const Type& object): ObjectBase(), m_Object(object) {}
        ~Object() override {}

        Type getObject()
        {
            return m_Object;
        }

    private:
        Type m_Object;
    };

    ObjectBase *m_pObject = nullptr;
    bool m_fTypeArr[sizeof...(Args) + 1] = {false};
};

template <typename T, typename ...Args>
template<typename Type>
Variant<T, Args...>& Variant<T, Args...>::operator = (Type&& object)
{
    for (bool &fPos: m_fTypeArr)
    {
        fPos = false;
    }

    if(SaveTypes<T, Args...>::template check<Type>(m_fTypeArr, true))
    {
        if(m_pObject)
        {
            delete m_pObject;
        }
        m_pObject = new Object<Type>(object);

        return *this;
    }
    std::string sError( "Variant::Bad cast to " );
    sError += typeid(Type).name();
    throw std::runtime_error(sError);
}

template <typename T, typename ...Args>
template<typename Type>
Type Variant<T, Args...>::get()
{
    if(SaveTypes<T, Args...>::template check<Type>(m_fTypeArr))
    {
        return static_cast<Object<Type>*>(m_pObject)->getObject();
    }
    std::string sError( "Variant::Bad cast to " );
    sError += typeid(Type).name();
    throw std::runtime_error(sError);
}

template <typename T, typename ...Args>
template<typename Type, typename ...TypeArgs>
template <typename U>
bool Variant<T, Args...>::SaveTypes<Type, TypeArgs...>::check(bool *pArr, bool fWrite)
{
    if(std::is_same<Type, U>::value)
    {
        if(fWrite)
        {
            *pArr = true;
        }
        return true && (fWrite || *pArr);
    }
    return SaveTypes<TypeArgs...>::template check<U>(++pArr, fWrite);
}

template <typename T, typename ...Args>
template<typename Type>
template <typename U>
bool Variant<T, Args...>::SaveTypes<Type>::check(bool *pArr, bool fWrite)
{
    if(std::is_same<Type, U>::value)
    {
        if(fWrite)
        {
            *pArr = true;
        }
        return true && (fWrite || *pArr);
    }
    return false;
}

#endif // VARIANT_HPP
