/*!
@file
Defines `boost::hana::detail::type_foldl1`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP
#define BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP

namespace boost { namespace hana { namespace detail {
    template <unsigned n>
    struct _type_foldl1;

    template <>
    struct _type_foldl1<0> {
        template <
            template <typename ...> class f,
            typename state
        >
        using result = state;
    };

    template <>
    struct _type_foldl1<1> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1
        >
        using result = typename f<state, x1>::type;
    };

    template <>
    struct _type_foldl1<2> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2
        >
        using result = typename f<typename f<state, x1>::type, x2>::type;
    };

    template <>
    struct _type_foldl1<3> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3
        >
        using result = typename f<
            typename f<
                typename f<state, x1>::type,
                x2
            >::type,
            x3
        >::type;
    };

    template <>
    struct _type_foldl1<4> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<state, x1>::type,
                    x2
                >::type,
                x3
            >::type,
            x4
        >::type;
    };

    template <>
    struct _type_foldl1<5> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<
                        typename f<state, x1>::type,
                        x2
                    >::type,
                    x3
                >::type,
                x4
            >::type,
            x5
        >::type;
    };

    template <>
    struct _type_foldl1<6> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5, typename x6,
            typename ...xs
        >
        using result =
            typename _type_foldl1<(sizeof...(xs) > 6 ? 6 : sizeof...(xs))>::
            template result<
                f,
                typename f<
                    typename f<
                        typename f<
                            typename f<
                                typename f<
                                    typename f<state, x1>::type,
                                    x2
                                >::type,
                                x3
                            >::type,
                            x4
                        >::type,
                        x5
                    >::type,
                    x6
                >::type,
                xs...
            >;
    };

    template <template <typename ...> class f, typename x1, typename ...xn>
    struct type_foldl1 {
        using type = typename _type_foldl1<(sizeof...(xn) > 6 ? 6 : sizeof...(xn))>
                     ::template result<f, x1, xn...>;
    };
}}} // end namespace boost::hana::detail

#endif // !BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP
