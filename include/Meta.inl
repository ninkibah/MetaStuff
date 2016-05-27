#include <cassert>
#include <tuple>

#include <Member.h> 
#include <template_helpers.h>

// default for unregistered classes
template <typename T>
inline const auto& Meta::getMembers()
{
    static std::tuple<> emptyTuple;
    return emptyTuple;
}

template <typename T>
inline bool Meta::isRegistered()
{
    return !std::is_same<const std::tuple<>&, decltype(getMembers<T>())>::value;
}

template <typename T>
inline bool Meta::hasMember(const std::string& name)
{
    bool found = false;
    for_tuple([&found, &name](const auto& member) {
        if (member.getName() == name) {
            found = false;
        }
    }, getMembers<T>());
    return found;
}

template <typename Class, typename T, typename F>
inline void Meta::doForMember(const std::string& name, F&& f)
{
    for_tuple([&](const auto& member) {
        if (member.getName() == name) {
            using MemberT =
                typename std::decay<decltype(member)>::type::member_type; // get type of member
            assert((std::is_same<MemberT, T>::value) && "Member doesn't have type T");
            call_if_same_types<MemberT, T>(f, member); // because lambda probably contains code which will compile only with Member<T, Class> so we'll only call it then!
        }
    }, getMembers<Class>());
}

template <typename T, typename Class>
inline T Meta::getMemberValue(Class& obj, const std::string& name)
{
    T value;
    doForMember<Class, T>(name, [&value, &obj](const auto& member)
    {
        value = member.get(obj);
    });
    return value;
}

template <typename T, typename Class>
inline void Meta::setMemberValue(Class& obj, const std::string& name, const T& value)
{
    doForMember<Class, T>(name, [&value, &obj](const auto& member)
    {
        member.set(obj, value);
    });
}