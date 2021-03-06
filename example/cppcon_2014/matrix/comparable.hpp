/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXAMPLE_CPPCON_2014_MATRIX_COMPARABLE_HPP
#define BOOST_HANA_EXAMPLE_CPPCON_2014_MATRIX_COMPARABLE_HPP

#include "matrix.hpp"

#include <boost/hana/bool.hpp>
#include <boost/hana/comparable.hpp>
#include <boost/hana/foldable.hpp>
#include <boost/hana/sequence.hpp>


namespace boost { namespace hana {
    template <unsigned R1, unsigned C1, unsigned R2, unsigned C2>
    struct equal_impl<cppcon::Matrix<R1, C1>, cppcon::Matrix<R2, C2>> {
        template <typename M1, typename M2>
        static constexpr auto apply(M1 const& m1, M2 const& m2) {
            return bool_<R1 == R2 && C1 == C2> &&
                   all(zip.with(equal, cppcon::rows(m1), cppcon::rows(m2)));
        }
    };
}}

#endif // !BOOST_HANA_EXAMPLE_CPPCON_2014_MATRIX_COMPARABLE_HPP
