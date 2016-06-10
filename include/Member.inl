#include <cassert>

namespace meta
{

template <typename Class, typename T>
Member<Class, T>::Member(const char* name, member_ptr_t<Class, T> ptr) :
    name(name),
    ptr(ptr),
    refGetterPtr(nullptr),
    refSetterPtr(nullptr),
    valGetterPtr(nullptr),
    valSetterPtr(nullptr),
    nonConstRefGetterPtr(nullptr)
{ }

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addNonConstGetter(nonconst_ref_getter_func_ptr_t<Class, T> nonConstRefGetterPtr)
{
    this->nonConstRefGetterPtr = nonConstRefGetterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addGetterSetter(ref_getter_func_ptr_t<Class, T> getterPtr,
    ref_setter_func_ptr_t<Class, T> setterPtr)
{
    this->refGetterPtr = getterPtr;
    this->refSetterPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addConstGetter(ref_getter_func_ptr_t<Class, T> getterPtr)
{
    this->refGetterPtr = getterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addSetter(ref_setter_func_ptr_t<Class, T> setterPtr)
{
    this->refSetterPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addGetterSetter(val_getter_func_ptr_t<Class, T> getterPtr,
    val_setter_func_ptr_t<Class, T> setterPtr)
{
    this->valGetterPtr = getterPtr;
    this->valSetterPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addConstGetter(val_getter_func_ptr_t<Class, T> getterPtr)
{
    this->valGetterPtr = getterPtr;
    return *this;
}

template <typename Class, typename T>
Member<Class, T>& Member<Class, T>::addSetter(val_setter_func_ptr_t<Class, T> setterPtr)
{
    this->valSetterPtr = setterPtr;
    return *this;
}

template <typename Class, typename T>
const T& Member<Class, T>::get(const Class& obj) const
{
    if (refGetterPtr) {
        return (obj.*refGetterPtr)();
    } else {
        return obj.*ptr;
    }
    assert(false && "Wut");
    throw; // wut
}

template <typename Class, typename T>
T& Member<Class, T>::getRef(Class& obj) const
{
    if (nonConstRefGetterPtr) {
        (obj.*nonConstRefGetterPtr)();
    } else {
        return obj.*ptr;
    }
    assert(false && "Wut");
    throw; // wut
}

template<typename Class, typename T>
template <typename V, typename>
void Member<Class, T>::set(Class& obj, V&& value) const
{
    // TODO: add rvalueSetter?
    if (refSetterPtr) {
        (obj.*refSetterPtr)(value);
    } else if (valSetterPtr) {
        (obj.*valSetterPtr)(value); // will copy value
    } else {
        obj.*ptr = value;
    }
}

template <typename Class, typename T>
Member<Class, T> member(const char* name, T Class::* ptr)
{
    return Member<Class, T>(name, ptr);
}

} // end of namespace meta