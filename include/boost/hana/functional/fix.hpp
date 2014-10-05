/*!
@file
Defines `boost::hana::fix`.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_FIX_HPP
#define BOOST_HANA_FUNCTIONAL_FIX_HPP

#include <boost/hana/detail/std/forward.hpp>
#include <boost/hana/detail/std/move.hpp>
#include <boost/hana/functional/always.hpp>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Return a function computing the fixed point of a function.
    //!
    //! `fix` is an implementation of the [Y-combinator][], also called the
    //! fixed-point combinator. It encodes the idea of recursion, and in fact
    //! any recursive function can be written in terms of it.
    //!
    //! Specifically, `fix(f)` is a function such that
    //! @code
    //!     fix(f)(x...) == f(fix(f), x...)
    //! @endcode
    //!
    //! This definition allows `f` to use its first argument as a continuation
    //! to call itself recursively. Indeed, if `f` calls its first argument
    //! with `y...`, it is equivalent to calling `f(fix(f), y...)` per the
    //! above equation.
    //!
    //! Most of the time, it is more convenient and efficient to define
    //! recursive functions without using a fixed-point combinator. However,
    //! there are some cases where `fix` provides either more flexibility
    //! (e.g. the ability to change the callback inside `f`) or makes it
    //! possible to write functions that couldn't be defined recursively
    //! otherwise.
    //!
    //! @param f
    //! A function called as `f(self, x...)`, where `x...` are the arguments
    //! in the `fix(f)(x...)` expression and `self` is `fix(f)`.
    //!
    //! ### Example
    //! @snippet example/functional/fix.cpp main
    //!
    //! [Y-combinator]: http://en.wikipedia.org/wiki/Fixed-point_combinator
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fix = [](auto f) {
        return [f(std::move(f))](auto&& ...x) -> decltype(auto) {
            return f(fix(f), std::forward<decltype(x)>(x)...);
        };
    };
#else
    namespace functional_detail {
        struct fix {
            template <typename F>
            constexpr auto operator()(F f) const {
                return [f(detail::std::move(f))](auto&& ...x) -> decltype(auto) {
                    // always is used to make the expression dependent on x.
                    // Otherwise, we recursively instantiate fix::operator()
                    // too soon and it blows up.
                    return f(
                        fix{}(always(f)(&x...)),
                        detail::std::forward<decltype(x)>(x)...
                    );
                };
            }
        };
    }

    constexpr functional_detail::fix fix{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_FIX_HPP
