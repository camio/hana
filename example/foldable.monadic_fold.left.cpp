/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/ext/std/utility.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <type_traits>
using namespace boost::hana;


//! [monadic_fold.left]
auto builtin_common_t = sfinae([](auto&& t, auto&& u) -> decltype(type<
    std::decay_t<decltype(true ? traits::declval(t) : traits::declval(u))>
>) { return {}; });

template <typename ...T>
struct common_type { };

template <typename T, typename U>
struct common_type<T, U>
    : std::conditional_t<std::is_same<std::decay_t<T>, T>{} &&
                         std::is_same<std::decay_t<U>, U>{},
        decltype(builtin_common_t(type<T>, type<U>)),
        common_type<std::decay_t<T>, std::decay_t<U>>
    >
{ };

template <typename T1, typename ...Tn>
struct common_type<T1, Tn...>
    : decltype(monadic_fold<Optional>.left(
        tuple_t<Tn...>,
        type<std::decay_t<T1>>,
        sfinae(metafunction<common_type>)
    ))
{ };

template <typename ...Ts>
using common_type_t = typename common_type<Ts...>::type;

static_assert(std::is_same<
    common_type_t<char, short, char, short>, int
>{}, "");

static_assert(std::is_same<
    common_type_t<char, double, short, char, short, double>, double
>{}, "");

static_assert(std::is_same<
    common_type_t<char, short, float, short>, float
>{}, "");

static_assert(
    sfinae(metafunction<common_type>)(type<int>, type<int>, type<int*>) == nothing
, "");
//! [monadic_fold.left]

int main() { }
