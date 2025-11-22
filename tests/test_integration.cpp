#include <gtest/gtest.h>
#include "Database.h"
#include "PasswordValidator.h"
#include <filesystem>

// ============================================
// PRUEBAS DE INTEGRACIÓN
// ============================================

class IntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        testDbPath = "integration_test.db";
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

// Test de integración: Validación de contraseña + Base de datos
TEST_F(IntegrationTest, PasswordValidationBeforeDatabaseCheck) {
    Database db(testDbPath);
    db.initialize();
    
    // Invalid password should not even reach database
    std::string invalidPassword = "weak";
    EXPECT_FALSE(PasswordValidator::validate(invalidPassword));
    
    // Valid password format
    std::string validPassword = "Pass@123";
    EXPECT_TRUE(PasswordValidator::validate(validPassword));
}

// Test de flujo completo de autenticación
TEST_F(IntegrationTest, CompleteAuthenticationFlow) {
    Database db(testDbPath);
    db.initialize();
    
    std::string email = "test@example.com";
    std::string password = "Valid@123";
    
    // Step 1: Validate password format
    EXPECT_TRUE(PasswordValidator::validate(password));
    
    // Step 2: Check database (user doesn't exist yet)
    EXPECT_FALSE(db.validateUser(email, password));
}

// Test de múltiples validaciones consecutivas
TEST_F(IntegrationTest, MultipleValidationAttempts) {
    Database db(testDbPath);
    db.initialize();
    
    std::string email = "user@example.com";
    
    // Multiple failed attempts
    EXPECT_FALSE(db.validateUser(email, "Wrong@1"));
    EXPECT_FALSE(db.validateUser(email, "Wrong@2"));
    EXPECT_FALSE(db.validateUser(email, "Wrong@3"));
}

// Test de integración con diferentes formatos de email
TEST_F(IntegrationTest, DifferentEmailFormats) {
    Database db(testDbPath);
    db.initialize();
    
    std::string validPassword = "Pass@123";
    
    EXPECT_FALSE(db.validateUser("simple@example.com", validPassword));
    EXPECT_FALSE(db.validateUser("user.name@example.com", validPassword));
    EXPECT_FALSE(db.validateUser("user+tag@example.com", validPassword));
}

// Test de validación de contraseña con todos los requisitos
TEST_F(IntegrationTest, PasswordMeetsAllRequirements) {
    std::string password = "MyP@ss123";
    
    EXPECT_TRUE(PasswordValidator::hasMinLength(password));
    EXPECT_TRUE(PasswordValidator::hasMaxLength(password));
    EXPECT_TRUE(PasswordValidator::hasUpperCase(password));
    EXPECT_TRUE(PasswordValidator::hasSpecialChar(password));
    EXPECT_TRUE(PasswordValidator::validate(password));
}
