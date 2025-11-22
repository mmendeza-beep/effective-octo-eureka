#include <gtest/gtest.h>
#include "Database.h"
#include "PasswordValidator.h"
#include <chrono>
#include <filesystem>

// ============================================
// PRUEBAS DE RENDIMIENTO
// ============================================

class PerformanceTest : public ::testing::Test {
protected:
    void SetUp() override {
        testDbPath = "performance_test.db";
        if (std::filesystem::exists(testDbPath)) {
            std::filesystem::remove(testDbPath);
        }
    }
    
    void TearDown() override {
        if (std::filesystem::exists(testDbPath)) {
            std::filesystem::remove(testDbPath);
        }
    }
    
    std::string testDbPath;
};

// Test de carga: Múltiples validaciones de contraseña
TEST_F(PerformanceTest, LoadTest_MultiplePasswordValidations) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Simulate 1000 password validations
    int validationCount = 1000;
    for (int i = 0; i < validationCount; i++) {
        PasswordValidator::validate("Test@" + std::to_string(i));
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Should complete in reasonable time (< 1 second)
    EXPECT_LT(duration.count(), 1000);
}

// Test de carga: Múltiples consultas a base de datos
TEST_F(PerformanceTest, LoadTest_MultipleDatabaseQueries) {
    Database db(testDbPath);
    db.initialize();
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Simulate 100 database queries
    int queryCount = 100;
    for (int i = 0; i < queryCount; i++) {
        db.validateUser("user" + std::to_string(i) + "@example.com", "Pass@123");
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Should complete in reasonable time (< 2 seconds)
    EXPECT_LT(duration.count(), 2000);
}

// Test de estrés: Validaciones simultáneas
TEST_F(PerformanceTest, StressTest_ConcurrentValidations) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // High volume of validations
    int stressCount = 10000;
    for (int i = 0; i < stressCount; i++) {
        PasswordValidator::validate("P@ss" + std::to_string(i % 100));
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Should handle stress without crashing
    EXPECT_LT(duration.count(), 5000);
}

// Test de estrés: Múltiples conexiones a BD
TEST_F(PerformanceTest, StressTest_MultipleDatabaseConnections) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Create and destroy multiple database instances
    for (int i = 0; i < 50; i++) {
        Database db(testDbPath);
        db.initialize();
        db.validateUser("stress@test.com", "Pass@123");
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Should handle multiple connections
    EXPECT_LT(duration.count(), 3000);
}

// Test de volumen: Gran cantidad de datos
TEST_F(PerformanceTest, VolumeTest_LargePasswordStrings) {
    // Test with maximum allowed password length
    std::string maxPassword = "A@bcdefgh1"; // 10 chars
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000; i++) {
        PasswordValidator::validate(maxPassword);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_LT(duration.count(), 500);
}

// Test de rendimiento: Tiempo de inicialización de BD
TEST_F(PerformanceTest, DatabaseInitializationTime) {
    auto start = std::chrono::high_resolution_clock::now();
    
    Database db(testDbPath);
    db.initialize();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Database initialization should be fast (< 100ms)
    EXPECT_LT(duration.count(), 100);
}

// Test de rendimiento: Validación de contraseña individual
TEST_F(PerformanceTest, SinglePasswordValidationTime) {
    std::string password = "Test@123";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    PasswordValidator::validate(password);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Single validation should be very fast (< 1ms)
    EXPECT_LT(duration.count(), 1000);
}

// Test de volumen: Múltiples emails diferentes
TEST_F(PerformanceTest, VolumeTest_MultipleUniqueEmails) {
    Database db(testDbPath);
    db.initialize();
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Test with many different email addresses
    for (int i = 0; i < 500; i++) {
        std::string email = "user" + std::to_string(i) + "@domain" + std::to_string(i % 10) + ".com";
        db.validateUser(email, "Pass@123");
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_LT(duration.count(), 3000);
}
