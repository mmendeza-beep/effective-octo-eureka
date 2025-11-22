# Test executable
add_executable(AuthScreenTests
    test_password_validator.cpp
    test_database.cpp
    test_integration.cpp
    test_system.cpp
    test_performance.cpp
    test_security.cpp
    test_usability.cpp
    test_recovery.cpp
)

target_link_libraries(AuthScreenTests
    AuthScreenLib
    GTest::GTest
    GTest::Main
)

# Discover tests
gtest_discover_tests(AuthScreenTests)
