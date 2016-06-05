#pragma once

template <typename Class, typename T>
class Member {
public:
    using class_type = Class;
    using member_type = T;
    using member_ptr_t = T Class::*;

    // references
    using getter_func_ptr_t = const T& (Class::*)() const;
    using setter_func_ptr_t = void (Class::*)(const T&);

    // values
    using getter_func_ptr_tv = T (Class::*)() const;
    using setter_func_ptr_tv = void (Class::*)(T);

    // non const getter
    using nonconst_getter_func_ptr_t = T& (Class::*)();

    Member(std::string&& name, member_ptr_t ptr);

    Member& addNonConstGetter(nonconst_getter_func_ptr_t nonConstGetterPtr);

    Member& addGetterSetter(getter_func_ptr_t getterPtr, setter_func_ptr_t setterPtr);
    Member& addConstGetter(getter_func_ptr_t getterPtr);
    Member& addSetter(setter_func_ptr_t setterPtr);

    // overloads for values
    Member& addGetterSetter(getter_func_ptr_tv getterPtr, setter_func_ptr_tv setterPtr);
    Member& addConstGetter(getter_func_ptr_tv getterPtr);
    Member& addSetter(setter_func_ptr_tv setterPtr);

    // get sets methods can be used to add support
    // for getters/setters for members insstead of 
    // direct access to them
    const T& get(const Class& obj) const;
    T& getRef(Class& obj) const;
    void set(Class& obj, const T& value) const;

    const std::string& getName() const { return name; }
private:
    const std::string name;
    member_ptr_t ptr;

    
    getter_func_ptr_t getterPtr;
    setter_func_ptr_t setterPtr;

    getter_func_ptr_tv getterVPtr;
    setter_func_ptr_tv setterVPtr;

    nonconst_getter_func_ptr_t nonConstGetterPtr;
};

// useful function similar to make_pair which is used so I don't have to write this:
// Member<SomeClass, int>("someName", &SomeClass::someInt); and can just to this:
// member("someName", &SomeClass::someInt);

template <typename Class, typename T>
Member<Class, T> member(std::string&& name, T Class::* ptr);

#include "Member.inl"