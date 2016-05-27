#pragma once

template <typename Class, typename T>
class Member {
public:
    using class_type = Class;
    using member_type = T;
    using member_ptr_t = T Class::*;
    using getter_func_ptr_t = const T& (Class::*)() const;
    using setter_func_ptr_t = void (Class::*)(const T&);

    Member(std::string&& name, member_ptr_t ptr);
    Member(std::string&& name, getter_func_ptr_t getterPtr, setter_func_ptr_t setterPtr);

    // get sets methods can be used to add support
    // for getters/setters for members insstead of 
    // direct access to them
    const T& get(const Class& obj) const;
    void set(Class& obj, const T& value) const;

    const std::string& getName() const { return name; }
private:
    const std::string name;
    member_ptr_t ptr;
    getter_func_ptr_t getterPtr;
    setter_func_ptr_t setterPtr;
};

// useful function similar to make_pair which is used so I don't have to write this:
// Member<SomeClass, int>("someName", &SomeClass::someInt); and can just to this:
// member("someName", &SomeClass::someInt);

template <typename Class, typename T>
Member<Class, T> member(std::string&& name, T Class::* ptr);

template <typename Class, typename T>
Member<Class, T> member(std::string&& name, const T& (Class::*getterPtr)() const, void (Class::*setterPtr)(const T&));

#include "Member.inl"