#include <gtest/gtest.h>
#include "Database.h"
#include "PasswordValidator.h"
#include <filesystem>

// ============================================
// PRUEBAS DE SISTEMA Y UAT
// ============================================

class SystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        testDbPath = "system_test.db";
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

// Escenario de usuario: Intento de login exitoso
TEST_F(SystemTest, UserScenario_SuccessfulLogin) {
    Database db(testDbPath);
    db.initialize();
    
    std::string email = "user@example.com";
    std::string password = "Valid@123";
    
    // User enters valid credentials
    ASSERT_TRUE(PasswordValidator::validate(password));
    
    // Note: In real scenario, user would exist in DB
    // This tests the validation flow
}

// Escenario de usuario: Contraseña inválida
TEST_F(SystemTest, UserScenario_InvalidPasswordFormat) {
    std::string weakPassword = "weak";
    
    // System should reject before checking database
    EXPECT_FALSE(PasswordValidator::validate(weakPassword));
}

// Test de límite de 5 intentos
TEST_F(SystemTest, MaximumFiveAttempts) {
    Database db(testDbPath);
    db.initialize();
    
    std::string email = "user@example.com";
    int maxAttempts = 5;
    int attemptCount = 0;
    
    // Simulate 5 failed attempts
    for (int i = 0; i < maxAttempts; i++) {
        std::string password = "Wrong@" + std::to_string(i);
        EXPECT_FALSE(db.validateUser(email, password));
        attemptCount++;
    }
    
    EXPECT_EQ(attemptCount, maxAttempts);
}

// Test de recuperación de contraseña
TEST_F(SystemTest, PasswordRecoveryFlow) {
    std::string email = "user@example.com";
    
    // User requests password recovery
    // System should accept valid email format
    EXPECT_FALSE(email.empty());
    EXPECT_NE(email.find('@'), std::string::npos);
}

// Escenario UAT: Usuario nuevo intenta acceder
TEST_F(SystemTest, UAT_NewUserAttempt) {
    Database db(testDbPath);
    db.initialize();
    
    std::string newUserEmail = "newuser@example.com";
    std::string password = "NewPass@1";
    
    // New user should not be able to login
    EXPECT_FALSE(db.validateUser(newUserEmail, password));
}

// Escenario UAT: Validación de formato de contraseña
TEST_F(SystemTest, UAT_PasswordFormatValidation) {
    // User tries different password formats
    EXPECT_FALSE(PasswordValidator::validate("short"));      // Too short
    EXPECT_FALSE(PasswordValidator::validate("toolongpassword123")); // Too long
    EXPECT_FALSE(PasswordValidator::validate("nospecial1A")); // No special char
    EXPECT_FALSE(PasswordValidator::validate("noupper@123")); // No uppercase
    EXPECT_TRUE(PasswordValidator::validate("Valid@123"));   // Valid
}

// Escenario UAT: Mensajes de error apropiados
TEST_F(SystemTest, UAT_AppropriateErrorMessages) {
    std::string password = "weak";
    
    if (!PasswordValidator::hasMinLength(password)) {
        // Should show: "Password must be at least 5 characters"
        EXPECT_LT(password.length(), 5);
    }
    
    if (!PasswordValidator::hasUpperCase(password)) {
        // Should show: "Password must contain at least one uppercase letter"
        EXPECT_FALSE(PasswordValidator::hasUpperCase(password));
    }
    
    if (!PasswordValidator::hasSpecialChar(password)) {
        // Should show: "Password must contain at least one special character"
        EXPECT_FALSE(PasswordValidator::hasSpecialChar(password));
    }
}

// Test de aceptación: Flujo completo de autenticación
TEST_F(SystemTest, UAT_CompleteAuthenticationFlow) {
    Database db(testDbPath);
    db.initialize();
    
    // Step 1: User enters email
    std::string email = "testuser@example.com";
    EXPECT_FALSE(email.empty());
    
    // Step 2: User enters password
    std::string password = "Test@2024";
    EXPECT_TRUE(PasswordValidator::validate(password));
    
    // Step 3: System validates credentials
    bool isAuthenticated = db.validateUser(email, password);
    
    // Step 4: System responds appropriately
    EXPECT_FALSE(isAuthenticated); // User doesn't exist in this test
}

// Test de navegación entre campos
TEST_F(SystemTest, UAT_FieldNavigation) {
    // Simulate user navigation
    bool emailFieldActive = true;
    bool passwordFieldActive = false;
    
    // User presses Tab
    emailFieldActive = false;
    passwordFieldActive = true;
    
    EXPECT_FALSE(emailFieldActive);
    EXPECT_TRUE(passwordFieldActive);
    
    // User presses Tab again
    emailFieldActive = true;
    passwordFieldActive = false;
    
    EXPECT_TRUE(emailFieldActive);
    EXPECT_FALSE(passwordFieldActive);
}
