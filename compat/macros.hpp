#pragma once

#if defined _MSC_VER
#   define cc_noinline __declspec(noinline)
#else
#   define cc_noinline __attribute__((noinline))
#endif

#if defined _MSC_VER
#   define cc_forceinline __forceinline
#else
#   define cc_forceinline __attribute__((always_inline))
#endif

#if !defined likely
#   if defined __GNUC__
#      define likely(x)       __builtin_expect(!!(x),1)
#      define unlikely(x)     __builtin_expect(!!(x),0)
#   else
#      define likely(x) (x)
#      define unlikely(x) (x)
#   endif
#endif

#if defined _MSC_VER
#   define cc_function_name __FUNCSIG__
#else
#   define cc_function_name __PRETTY_FUNCTION__
#endif

#if !defined PP_CAT
#   define PP_CAT(x,y) PP_CAT1(x,y)
#   define PP_CAT1(x,y) PP_CAT2(x,y)
#   define PP_CAT2(x,y) x ## y
#endif

#ifndef PP_EXPAND
#   define PP_EXPAND(x) PP_EXPAND__2(x)
#   define PP_EXPAND__2(x) PP_EXPAND__3(x) x
#   define PP_EXPAND__3(x) x
#endif

#if defined __cplusplus

// from now only C++

#include <utility>
#include <type_traits>

// before C++20
namespace cxx20_compat {
    template<typename T>
    struct remove_cvref {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };
} // ns cxx20_compat

template<typename t>
using remove_cvref_t = typename cxx20_compat::remove_cvref<t>::type;

template<typename t>
using to_const_cvref_t = std::add_lvalue_reference_t<std::add_const_t<remove_cvref_t<t>>>;

// causes ICE in Visual Studio 2017 Preview. the ICE was reported and they handle them seriously in due time.
// the ICE is caused by decltype(auto) and const& return value
//#define eval_once(expr) ([&]() -> decltype(auto) { static decltype(auto) ret___1132 = (expr); return (decltype(ret___1132) const&) ret___1132; }())

#define eval_once(expr) eval_once__2(expr, PP_CAT(_EVAL_ONCE__, __COUNTER__))
#define eval_once__2(expr, ident) eval_once__3(expr, ident)

#define eval_once__3(expr, ident)                                                               \
    ([&]() -> decltype(auto) {                                                                  \
        static auto INIT##ident = (expr);                                                       \
        return static_cast<to_const_cvref_t<decltype(INIT##ident)>>(INIT##ident);    \
    }())

#include <type_traits>

template<typename t>
using cv_qualified = std::conditional_t<std::is_fundamental_v<remove_cvref_t<t>>,
                                        remove_cvref_t<t>,
                                        to_const_cvref_t<t>>;

template<bool>
[[deprecated]] constexpr cc_forceinline void static_warn() {}

template<>
constexpr cc_forceinline void static_warn<true>() {}

#define static_warning(cond)            \
        static_warn<(cond)>();          \

#define progn(...) ([&]() -> decltype(auto) { __VA_ARGS__ }())

// end c++-only macros
#endif
