/*!
@file
Defines `boost::hana::Product`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PRODUCT_HPP
#define BOOST_HANA_PRODUCT_HPP

#include <boost/hana/fwd/product.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/comparable.hpp>
#include <boost/hana/core/datatype.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/models.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/foldable.hpp>
#include <boost/hana/logical.hpp>
#include <boost/hana/orderable.hpp>


namespace boost { namespace hana {
    //////////////////////////////////////////////////////////////////////////
    // first
    //////////////////////////////////////////////////////////////////////////
    template <typename P, typename>
    struct first_impl : first_impl<P, when<true>> { };

    template <typename P, bool condition>
    struct first_impl<P, when<condition>> : default_ {
        static void apply(...) { }
    };

    //////////////////////////////////////////////////////////////////////////
    // second
    //////////////////////////////////////////////////////////////////////////
    template <typename P, typename>
    struct second_impl : second_impl<P, when<true>> { };

    template <typename P, bool condition>
    struct second_impl<P, when<condition>> : default_ {
        static void apply(...) { }
    };

    //////////////////////////////////////////////////////////////////////////
    // models
    //////////////////////////////////////////////////////////////////////////
    template <typename P>
    struct models_impl<Product, P>
        : _integral_constant<bool,
            !is_default<first_impl<P>>{}() &&
            !is_default<second_impl<P>>{}()
        >
    { };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct equal_impl<T, U, when<
        _models<Product, T>{}() && _models<Product, U>{}()
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const& x, Y const& y) {
            return hana::and_(
                hana::equal(hana::first(x), hana::first(y)),
                hana::equal(hana::second(x), hana::second(y))
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Orderable
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct less_impl<T, U, when<
        _models<Product, T>{}() && _models<Product, U>{}()
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const& x, Y const& y) {
            return hana::or_(
                hana::less(hana::first(x), hana::first(y)),
                hana::and_(
                    hana::less_equal(hana::first(x), hana::first(y)),
                    hana::less(hana::second(x), hana::second(y))
                )
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct unpack_impl<T, when<_models<Product, T>{}()>> {
        template <typename P, typename F>
        static constexpr decltype(auto) apply(P&& p, F&& f) {
            return static_cast<F&&>(f)(
                hana::first(static_cast<P&&>(p)),
                hana::second(static_cast<P&&>(p))
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_PRODUCT_HPP
