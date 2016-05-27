#include <cassert>

template <typename Class, typename T>
Member<Class, T>::Member(std::string&& name, 
    typename Member<Class, T>::member_ptr_t ptr) :
    name(std::move(name)),
    ptr(ptr),
    getterPtr(nullptr),
    setterPtr(nullptr)
{ }

template <typename Class, typename T>
Member<Class, T>::Member(std::string&& name,
    typename Member<Class, T>::getter_func_ptr_t getterPtr,
    typename Member<Class, T>::setter_func_ptr_t setterPtr) :
    name(std::move(name)),
    ptr(nullptr),
    getterPtr(getterPtr),
    setterPtr(setterPtr)
{ }


template <typename Class, typename T>
const T& Member<Class, T>::get(const Class& obj) const
{
    if (ptr) {
        return obj.*ptr;
    } else if (getterPtr) {
        return (obj.*getterPtr)();
    }
    // something went wrong, deal with it!
    assert(false && "Member doesn't have member ptr or getter!");
    throw; // should crash? Or maybe do something another?
}

template<typename Class, typename T>
void Member<Class, T>::set(Class& obj, const T& value) const
{
    if (ptr) {
        obj.*ptr = value;
    } else if (setterPtr) {
        (obj.*setterPtr)(value);
    } else { // oops
        assert(false && "Member doesn't have member ptr or setter!");
    }
}

template <typename Class, typename T>
Member<Class, T> member(std::string&& name, T Class::* ptr)
{
    return Member<Class, T>(std::move(name), ptr);
}

template <typename Class, typename T>
Member<Class, T> member(std::string&& name, const T& (Class::*getterPtr)() const, void (Class::*setterPtr)(const T&))
{
    return Member<Class, T>(std::move(name), getterPtr, setterPtr);
}