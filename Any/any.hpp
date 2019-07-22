#ifndef ANY_HPP
#define ANY_HPP

#include <typeinfo>
#include <stdexcept>
#include <type_traits>

class Any
{
public:
    Any();
    //Any(const Any& other);

    ~Any();

    //Any& operator = (const Any& rhs);

    template<typename T>
    Any& operator = (T&& rhs);

    void reset();
    //void swap(Any& other);
    bool has_value() const;
    const std::type_info& type() const;

    template<typename Type>
    Type any_cast();

private:
    class ObjectBase
    {
    public:
        ObjectBase(const std::type_info& typeInfo ): m_TypeInfo(typeInfo) {}
        virtual ~ObjectBase() {}

        const std::type_info& type() const
        {
            return m_TypeInfo;
        }

    private:
        const std::type_info& m_TypeInfo;
    };

    template <typename T>
    class Object: public ObjectBase
    {
    public:
        Object(const T& object): ObjectBase(typeid(T)), m_Object(object) {}
        ~Object() override {}

        T getObject()
        {
            return m_Object;
        }

    private:
        T m_Object;
    };

    ObjectBase *m_pObject;
};

Any::Any(): m_pObject(nullptr) {}

Any::~Any() {}

template<typename T>
Any& Any::operator = (T&& object)
{
    if(m_pObject)
    {
        delete m_pObject;
    }
    m_pObject = new Object<T>(object);

    return *this;
}

void Any::reset()
{
    if(m_pObject)
    {
        delete m_pObject;
        m_pObject = nullptr;
    }
}

bool Any::has_value() const
{
    return m_pObject == nullptr;
}

const std::type_info& Any::type() const
{
    return m_pObject->type();
}

template<typename Type>
Type Any::any_cast()
{
    Object<Type>* p = dynamic_cast<Object<Type>*>(m_pObject);
    if(p)
    {
       return p->getObject();
    }
    std::string sError( "Any::Bad cast from " );
    sError += type().name();
    sError += " to ";
    sError += typeid(Type).name();
    throw std::runtime_error(sError);
}

#endif // ANY_HPP
