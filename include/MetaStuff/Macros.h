#pragma once

#pragma once

// This code is described here: http://jhnet.co.uk/articles/cpp_magic
#define FIRST_(a, ...) a
#define SECOND_(a, b, ...) b

#define FIRST(...) FIRST_(__VA_ARGS__,)
#define SECOND(...) SECOND_(__VA_ARGS__,)

#define EMPTY()

#define EVAL(...) EVAL1024(__VA_ARGS__)
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()

#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define PROBE() ~, 1

#define CAT(a,b) a ## b

#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()

#define BOOL(x) NOT(NOT(x))

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)

#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define COMMA ,

#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

#define MAP(m, first, ...)           \
  m(first)                           \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    COMMA DEFER2(_MAP)()(m, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP

#define STRINGIZE(x) #x

// This macro converts all its inputs into a list of C-strings.
#define STRING_LIST(...) EVAL(MAP(STRINGIZE, __VA_ARGS__))

#define METASTUFF_DEFINE_MEMBERS(CLASS, ...) \
namespace meta { \
template <> \
inline auto registerMembers<CLASS>() { \
    return members(                          \
        METASTUFF_MEMBER_LIST(CLASS, __VA_ARGS__) \
    ); \
} \
}

#define METASTUFF_DETAIL_MEMBER_LIST(CLASS, first, ...) \
        ([]<typename T>(T* t) {                         \
            if constexpr (requires { t->first; }) { return member(#first, &T::first); } \
            else if constexpr (requires { t->set##first(t->get##first()); }) { return member(#first, &T::get##first, &T::set##first); } \
            else static_assert(always_false<T>, #CLASS "::" #first " is not a field or a getter"); \
        })(static_cast<CLASS *>(nullptr))                                   \
    IF_ELSE(HAS_ARGS(__VA_ARGS__))(                                         \
        COMMA DEFER2(_METASTUFF_DETAIL_MEMBER_LIST)()(CLASS, __VA_ARGS__)   \
    )(/* Do nothing, just terminate */)

#define _METASTUFF_DETAIL_MEMBER_LIST() METASTUFF_DETAIL_MEMBER_LIST

#define METASTUFF_MEMBER_LIST(...) EVAL(METASTUFF_DETAIL_MEMBER_LIST(__VA_ARGS__))
