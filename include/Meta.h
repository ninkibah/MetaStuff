/* -----------------------------------------------------------------------------------------------
Meta struct which getMembers() function which can be specialized for specific classes.
This is how class registration works.

Here's an example:
template <>
inline auto& Meta::getMembers<SomeClass>()
{
    static auto members = std::make_tuple(
        member("someMember", &SomeClass::someMember),
        ...
    );
    return members;
}

! Some important details:
1) This specialization should be defined in header, because compiler needs to deduce the return type.
2) It's guaranteed that members for each class will be created ONCE and there won't be any copies
(TODO: find this in C++11 standard)

    "[..] An inline function with external linkage shall have the same address in all translation units.
    A static local variable in an extern inline function always refers to the same object.
    A string literal in an extern inline function is the same object in different translation units."
                                                                                - [dcl.fct.spec]/4
    
3) getMembers could easily be a free function, but befriending such function is hard if you want to
   be able to get pointers to private members... Writing "friend class Meta" in your preferred class
   is just much easier. Though this might be somehow fixed in the future.
4) If the class is not registered then forTuple(<your function>, Meta::getMembers<T>()) would do nothing,
   because the function will return empty tuple.
5) MemberPtr.h is included in this file just so that user can #include "Meta.h" and get MemberPtr.h
   included too, which is always needed for registration.

-------------------------------------------------------------------------------------------------*/

#pragma once

struct Meta {
    // Returns const std::tuple<...>&, where ... is Member<T, Class>. Used for iteration over members 
    template <typename T>
    inline static const auto& getMembers();

    // Check if class has getMembers<T> specialization (has been registered)
    template <typename T>
    inline static bool isRegistered();

    // Check if class T has member
    template <typename T>
    inline static bool hasMember(const std::string& name);

    // Do F for member named 'name' with type T. It's important to pass correct type of the member
    template <typename Class, typename T, typename F>
    inline static void doForMember(const std::string& name, F&& f);

    // Get value of the member named 'name'
    template <typename T, typename Class>
    inline static T getMemberValue(Class& obj, const std::string& name);

    // Set value of the member named 'name'
    template <typename T, typename Class>
    inline static void setMemberValue(Class& obj, const std::string& name, const T& value);
};

#include "Meta.inl"