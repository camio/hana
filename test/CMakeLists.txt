#=============================================================================
# Setup unit tests
#=============================================================================
enable_testing()
add_custom_target(tests
    COMMAND ${CMAKE_CTEST_COMMAND}
    COMMENT "Build and run all the unit tests.")

function(boost_hana_add_test name)
    string(REGEX REPLACE "[.]" "/" source ${name})
    add_executable(${name} EXCLUDE_FROM_ALL ${source}.cpp)
    add_test(NAME ${name} COMMAND ${name})
    add_dependencies(tests ${name})
endfunction()


boost_hana_add_test(adapted.std_array.iterable)
boost_hana_add_test(adapted.std_integer_sequence.iterable)
boost_hana_add_test(adapted.std_tuple.functor)
boost_hana_add_test(adapted.std_tuple.iterable)

boost_hana_add_test(detail.comparable_from_iterable)
boost_hana_add_test(detail.foldable_from_iterable)
boost_hana_add_test(detail.integer_sequence)
boost_hana_add_test(detail.left_folds)

boost_hana_add_test(foldable.maximum)
boost_hana_add_test(foldable.minimum)
boost_hana_add_test(foldable.product)
boost_hana_add_test(foldable.sum)

boost_hana_add_test(functional.always)
boost_hana_add_test(functional.apply)
boost_hana_add_test(functional.compose)
boost_hana_add_test(functional.fix)
boost_hana_add_test(functional.flip)
boost_hana_add_test(functional.id)
boost_hana_add_test(functional.partial)

boost_hana_add_test(integral.comparable)
boost_hana_add_test(integral.operators)

boost_hana_add_test(iterable.all_of)
boost_hana_add_test(iterable.at)
boost_hana_add_test(iterable.drop)
boost_hana_add_test(iterable.last)
boost_hana_add_test(iterable.length)

boost_hana_add_test(list.comparable)
boost_hana_add_test(list.concat)
boost_hana_add_test(list.cons)
boost_hana_add_test(list.filter)
boost_hana_add_test(list.functor)
boost_hana_add_test(list.iterable)
boost_hana_add_test(list.reverse)
boost_hana_add_test(list.snoc)
boost_hana_add_test(list.take)
boost_hana_add_test(list.take_while)
boost_hana_add_test(list.zip)
boost_hana_add_test(list.zip_with)

boost_hana_add_test(logical.and)
boost_hana_add_test(logical.if)
boost_hana_add_test(logical.or)

boost_hana_add_test(range.comparable)
boost_hana_add_test(range.functor)
boost_hana_add_test(range.iterable)

boost_hana_add_test(type.comparable)
boost_hana_add_test(type.lift)
boost_hana_add_test(type.traits)

boost_hana_add_test(typelist.comparable)
boost_hana_add_test(typelist.functor)
boost_hana_add_test(typelist.iterable)


boost_hana_add_test(hana)
boost_hana_add_test(misc.adl)