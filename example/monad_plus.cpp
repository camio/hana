/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/ext/std/integral_constant.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <string>
#include <type_traits>
using namespace boost::hana;


int main() {

{

//! [concat]
using namespace boost::hana::literals;

static_assert(concat(make_tuple(1, '2'),
                     make_tuple(3.3, 4_c)) == make_tuple(1, '2', 3.3, 4_c), "");
//! [concat]

}{

//! [empty]
BOOST_HANA_CONSTANT_CHECK(empty<Tuple>() == make_tuple());
BOOST_HANA_CONSTANT_CHECK(empty<Optional>() == nothing);
//! [empty]

}{

//! [prepend]
static_assert(prepend(make_tuple(), 1) == make_tuple(1), "");
static_assert(prepend(make_tuple('2', 3.3), 1) == make_tuple(1, '2', 3.3), "");
//! [prepend]

}{

//! [append]
static_assert(append(make_tuple(), 1) == make_tuple(1), "");
static_assert(append(make_tuple(1, '2'), 3.3) == make_tuple(1, '2', 3.3), "");
static_assert(append(append(append(make_tuple(), 1), '2'), 3.3) == make_tuple(1, '2', 3.3), "");
//! [append]

}{

//! [filter]
static_assert(filter(make_tuple(1, 2.0, 3, 4.0), trait<std::is_integral>) == make_tuple(1, 3), "");
static_assert(filter(just(3), trait<std::is_integral>) == just(3), "");
BOOST_HANA_CONSTANT_CHECK(filter(just(3.0), trait<std::is_integral>) == nothing);
//! [filter]

}{

//! [cycle]
static_assert(cycle(make_tuple('x', 'y'), size_t<2>) == make_tuple('x', 'y', 'x', 'y'), "");
//! [cycle]

}{

//! [remove_if]
static_assert(remove_if(make_tuple(1, 2.0, 3, 4.0), trait<std::is_integral>) == make_tuple(2.0, 4.0), "");
static_assert(remove_if(just(3.0), trait<std::is_integral>) == just(3.0), "");
BOOST_HANA_CONSTANT_CHECK(remove_if(just(3), trait<std::is_integral>) == nothing);
//! [remove_if]

}{

using boost::hana::remove; // Make sure we don't clash with ::remove from <stdio.h>
//! [remove]
BOOST_HANA_CONSTANT_CHECK(remove(tuple_t<int, char, float>, type<char>) == tuple_t<int, float>);
BOOST_HANA_CONSTANT_CHECK(remove(just(type<int>), type<char>) == just(type<int>));
BOOST_HANA_CONSTANT_CHECK(remove(just(type<int>), type<int>) == nothing);
//! [remove]

}{

//! [repeat]
static_assert(repeat<Tuple>('x', size_t<2>) == make_tuple('x', 'x'), "");

// Of course, there can't be more than one element in an Optional.
static_assert(repeat<Optional>('x', size_t<2>) == just('x'), "");
//! [repeat]

}{

//! [prefix]
using namespace std::literals;

BOOST_HANA_RUNTIME_CHECK(
    prefix(make_tuple("dog"s, "car"s, "house"s), "my"s) ==
    make_tuple("my", "dog", "my", "car", "my", "house")
);
//! [prefix]

}{

//! [suffix]
static_assert(
    suffix(make_tuple(1, 2, 3, 4), 0) == make_tuple(1, 0, 2, 0, 3, 0, 4, 0)
, "");
//! [suffix]

}

}
