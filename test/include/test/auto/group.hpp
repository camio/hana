/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TEST_TEST_AUTO_GROUP_HPP
#define BOOST_HANA_TEST_TEST_AUTO_GROUP_HPP

#include <boost/hana/group.hpp>

#include <boost/hana/comparable.hpp>
#include <boost/hana/detail/assert.hpp>
#include <boost/hana/monoid.hpp>

#include <test/auto/base.hpp>

// required instances
#include <test/auto/monoid.hpp>


namespace boost { namespace hana { namespace test {
    template <typename G>
    auto laws<Group, G> = [] {
        laws<Monoid, G>();

        // Instance laws
        {
            for_each(objects<G>, [](auto x) {
                BOOST_HANA_ASSERT(equal(
                    plus(x, negate(x)),
                    zero<G>
                ));

                BOOST_HANA_ASSERT(equal(
                    plus(negate(x), x),
                    zero<G>
                ));
            });
        }

        // minus
        {
            for_each(objects<G>, [](auto x) {
                for_each(objects<G>, [=](auto y) {
                    BOOST_HANA_ASSERT(equal(
                        minus(x, y),
                        plus(x, negate(y))
                    ));

                    BOOST_HANA_ASSERT(equal(
                        minus(y, x),
                        plus(y, negate(x))
                    ));
                });
            });
        }

        // negate
        {
            for_each(objects<G>, [](auto x) {
                BOOST_HANA_ASSERT(equal(
                    negate(negate(x)),
                    x
                ));
            });
        }
    };
}}} // end namespace boost::hana::test

#endif // !BOOST_HANA_TEST_TEST_AUTO_GROUP_HPP