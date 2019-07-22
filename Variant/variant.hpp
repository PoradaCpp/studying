#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <iostream>
#include <type_traits>

template <typename T, typename ...Args>
class Variant
{
public:
    template<typename Type>
    Variant& operator = (Type&& object)
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

    template<typename Type>
    Type get()
    {
        if(SaveTypes<T, Args...>::template check<Type>(m_fTypeArr, false))
        {
            return static_cast<Object<Type>*>(m_pObject)->getObject();
        }
        std::string sError( "Variant::Bad cast to " );
        sError += typeid(Type).name();
        throw std::runtime_error(sError);
    }

private:
    template<typename Type, typename ...TypeArgs>
    struct SaveTypes
    {
        template <typename U>
        static bool check(bool *pArr, bool fWrite = false)
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
    };

    template <typename Type>
    struct SaveTypes<Type>
    {
        template <typename U>
        static bool check(bool *pArr, bool fWrite = false)
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

#endif // VARIANT_HPP
