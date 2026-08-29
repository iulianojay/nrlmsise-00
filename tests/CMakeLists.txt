find_package(Cppunit)

list(
    APPEND test_FILES
    Nrlmsise00Test.cpp
)

if (CPPUNIT_FOUND)
    add_executable(
        unit_tests
        TestRunner.cpp
        ${test_FILES}
    )

    target_link_libraries(
        unit_tests
        ${CPPUNIT_LIBRARIES}
        nrlmsise00
    )

    add_test(Nrlmsise00 unit_tests)
endif()