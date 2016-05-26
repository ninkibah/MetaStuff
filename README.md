Meta stuff WIP
=======

This is the code I use in my game for all serialization/deserialization/introspection stuff. The code is not limited to any class, you can easily modify it to support your own formats.
At the moment this code is not fully developed, so it's not recommended to use it for anything really serious as lots of stuff can change!
I put this code mostly for other people to learn from and maybe help me expand this to a pretty good lib. Still, use it as you like, it's MIT licensed after all.

This library is still in development and all suggestions are welcome!

Requirements
----
- Compiler with C++14 support (I managed to compile it with Visual Studio 2015, GCC 5.0, Clang 3.8)

Dependencies
-----
- None! ([JsonCpp](https://github.com/open-source-parsers/jsoncpp) is used in example, but you can use any library you want, probably)

How-to / example
----

See example for complete example of JSON serialization.

Suppose you have classes like this:
```c++
struct Person {
    void setAge(const int& a)
    {
        if (a >= 0 && a < 128) { // sorry, if you're older than 128
            age = a;
        } else {
            std::cout << "Can't set age. " << a << " is out of allowed range\n";
        }
    }

    const int& getAge() const { return age; }

    int age;
    float salary;
    std::string name;
    std::unordered_map<std::string, std::vector<MovieInfo>> favouriteMovies;
};

struct MovieInfo {
    std::string name;
    float rating;
};
```
And you want to serialize them to some format (for example, JSON). Or perhaps you want to add some GUI which will let you edit each member easily.
No problem, just write these static functions,

```c++
#include "Meta.h"
template <>
inline auto& Meta::getMembers<Person>()
{
    static auto memberPtrs = std::make_tuple(
        member("age", &Person::getAge, &Person::setAge),
        member("salary", &Person::salary),
        member("name", &Person::name),
        member("favouriteMovies", &Person::favouriteMovies));
    return memberPtrs; 

template <>
inline auto& Meta::getMembers<MovieInfo>()
{
    static auto memberPtrs = std::make_tuple(
        member("name", &MovieInfo::name),
        member("rating", &MovieInfo::rating));
    return memberPtrs;
}
```
Note that you can either use pointers to members or pointers to getters/setters. They will be used for doing stuff with members of registered classes. (for reading and setting values).

and now you can call do this:
```c++
forTuple(/* your lambda */, Meta::getMembers<Class>());
```

Your lambda should have one parameter which will be an instance of MemberPtr. Calling forTuple with T::getMembers() gives you ability to do something with each registered member of class T.
(See example/JsonCast.inl for examples of such lambdas).

MemberPtr has the following functions:

- std::string getName() - returns std::string of member name you've set during "registration"
- const T& get(const Class& obj) - gets const reference to the member
- void set(const Class& obj, const T& value) - sets value to member

If you provide MemberPtr with getters and setters it will use these functions for getting/setting members, otherwise the member will be accessed directly with pointer to member.

In general Meta::getMembers<T>() template function specialization should have a following form and be put in header with you class (see comments in Meta.h for more info):

```c++
#include <Meta.h>
template <>
inline auto& Meta::getMembers<SomeClass>()
{
    static auto members = std::make_tuple(
        member("someMember", &SomeClass::someMember),
        ...);
    return members;
}
```

You can make Meta class a friend to your registered class to be able to add private members to getMembers function specialization.

License
---

This library is licensed under the MIT License, see LICENSE for more information.