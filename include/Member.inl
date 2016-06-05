#include <cassert>

template <typename Class, typename T>
Member<Class, T>::Member(std::string&& name, 
    typename Member<Class, T>::member_ptr_t ptr) :
    name(std::move(name)),
    ptr(ptr),
    getterPtr(nullptr),
    setterPtr(nullptr),
    getterVPtr(nullptr),
    setterVPtr(nullptr),
    nonConstGetterPtr(nullptr)
{ }

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addGetterSetter(
    typename Member<Class, T>::getter_func_ptr_t getterPtr,
    typename Member<Class, T>::setter_func_ptr_t setterPtr)
{
    this->getterPtr = getterPtr;
    this->setterPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addNonConstGetter(typename Member<Class, T>::nonconst_getter_func_ptr_t nonConstGetterPtr)
{
    this->nonConstGetterPtr = nonConstGetterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addConstGetter(typename Member<Class, T>::getter_func_ptr_t getterPtr)
{
    this->getterPtr = getterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addSetter(typename Member<Class, T>::setter_func_ptr_t setterPtr)
{
    this->setterPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addGetterSetter(
    typename Member<Class, T>::getter_func_ptr_tv getterPtr,
    typename Member<Class, T>::setter_func_ptr_tv setterPtr)
{
    this->getterVPtr = getterPtr;
    this->setterVPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addConstGetter(typename Member<Class, T>::getter_func_ptr_tv getterPtr)
{
    this->getterVPtr = getterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addSetter(typename Member<Class, T>::setter_func_ptr_tv setterPtr)
{
    this->setterVPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
const T& Member<Class, T>::get(const Class& obj) const
{
    if (getterPtr) {
        return (obj.*getterPtr)();
    } else {
        return obj.*ptr;
    }
    assert(false && "Wut");
    throw; // wut
}

template <typename Class, typename T>
T& Member<Class, T>::getRef(Class& obj) const
{
    if (nonConstGetterPtr) {
        (obj.*nonConstGetterPtr)();
    } else {
        return obj.*ptr;
    }
    assert(false && "Wut");
    throw; // wut
}

template<typename Class, typename T>
void Member<Class, T>::set(Class& obj, const T& value) const
{
    if (setterPtr) {
        (obj.*setterPtr)(value);
    } else if (setterVPtr) {
        (obj.*setterVPtr)(value); // will copy value
    } else {
        obj.*ptr = value;
    }
}

template <typename Class, typename T>
Member<Class, T> member(std::string&& name, T Class::* ptr)
{
    return Member<Class, T>(std::move(name), ptr);
}