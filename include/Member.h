/* -----------------------------------------------------------------------------------------------

Member<Class, T> is a representation of a registered member
Class - a class this member belongs to
T - type of that member

Member contains pointer to data member which can be used to get / set stuff
Different getters and setters can be added via fluent interface (see addGetter/addConstGetter/addSetter)
Getters and setters are always preffered to using raw data member pointers (because why would you
set them in the other place?)

-------------------------------------------------------------------------------------------------*/

#pragma once


namespace meta
{

template <typename Class, typename T>
using member_ptr_t = T Class::*;

// reference getter/setter func pointer type
template <typename Class, typename T>
using ref_getter_func_ptr_t = const T& (Class::*)() const;

template <typename Class, typename T>
using ref_setter_func_ptr_t = void (Class::*)(const T&);

// value getter/setter func pointer type
template <typename Class, typename T>
using val_getter_func_ptr_t = T(Class::*)() const;

template <typename Class, typename T>
using val_setter_func_ptr_t = void (Class::*)(T);

// non const reference getter
template <typename Class, typename T>
using nonconst_ref_getter_func_ptr_t = T& (Class::*)();

template <typename Class, typename T>
class Member {
public:
    using class_type = Class;
    using member_type = T;

    Member(const char* name, member_ptr_t<Class, T> ptr);

    Member& addNonConstGetter(nonconst_ref_getter_func_ptr_t<Class, T> nonConstRefGetterPtr);

    Member& addGetterSetter(ref_getter_func_ptr_t<Class, T> getterPtr, ref_setter_func_ptr_t<Class, T> setterPtr);
    Member& addConstGetter(ref_getter_func_ptr_t<Class, T> getterPtr);
    Member& addSetter(ref_setter_func_ptr_t<Class, T> setterPtr);

    // overloads for values
    Member& addGetterSetter(val_getter_func_ptr_t<Class, T> getterPtr, val_setter_func_ptr_t<Class, T> setterPtr);
    Member& addConstGetter(val_getter_func_ptr_t<Class, T> getterPtr);
    Member& addSetter(val_setter_func_ptr_t<Class, T> setterPtr);

    // get sets methods can be used to add support
    // for getters/setters for members instead of 
    // direct access to them
    const T& get(const Class& obj) const;
    T& getRef(Class& obj) const;

    template <typename V,
        typename = std::enable_if_t<std::is_constructible<T, V>::value>>
        void set(Class& obj, V&& value) const; // accepts lvalues and rvalues!

    const char* getName() const { return name; }
    bool hasSetter() const { return refSetterPtr || valSetterPtr; }
private:
    const char* name;
    member_ptr_t<Class, T> ptr;

    ref_getter_func_ptr_t<Class, T> refGetterPtr;
    ref_setter_func_ptr_t<Class, T> refSetterPtr;

    val_getter_func_ptr_t<Class, T> valGetterPtr;
    val_setter_func_ptr_t<Class, T> valSetterPtr;

    nonconst_ref_getter_func_ptr_t<Class, T> nonConstRefGetterPtr;
};

// useful function similar to make_pair which is used so you don't have to write this:
// Member<SomeClass, int>("someName", &SomeClass::someInt); and can just to this:
// member("someName", &SomeClass::someInt);

template <typename Class, typename T>
Member<Class, T> member(const char* name, T Class::* ptr);

} // end of namespace meta

#include "Member.inl"