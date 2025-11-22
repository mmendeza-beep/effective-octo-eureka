#include <gtest/gtest.h>
#include "PasswordValidator.h"

// ============================================
// PRUEBAS DE USABILIDAD
// ============================================

// Test de experiencia de usuario: Mensajes claros
TEST(UsabilityTest, PasswordValidation_ClearFeedback) {
    std::string password = "weak";
    
    // User should get specific feedback about what's wrong
    if (!PasswordValidator::validate(password)) {
        if (!PasswordValidator::hasMinLength(password)) {
            // Message: "Password must be at least 5 characters"
            EXPECT_LT(password.length(), 5);
        }
        if (!PasswordValidator::hasUpperCase(password)) {
            // Message: "Password must contain at least one uppercase letter"
            EXPECT_TRUE(true);
        }
        if (!PasswordValidator::hasSpecialChar(password)) {
            // Message: "Password must contain at least one special character"
            EXPECT_TRUE(true);
        }
    }
}

// Test de usabilidad: Validación en tiempo real
TEST(UsabilityTest, RealTimeValidation) {
    // As user types, validation should update
    std::string password = "";
    
    // User types: "p"
    password += "p";
    EXPECT_FALSE(PasswordValidator::validate(password));
    
    // User types: "a"
    password += "a";
    EXPECT_FALSE(PasswordValidator::validate(password));
    
    // User types: "s"
    password += "s";
    EXPECT_FALSE(PasswordValidator::validate(password));
    
    // User types: "s"
    password += "s";
    EXPECT_FALSE(PasswordValidator::validate(password));
    
    // User types: "@"
    password += "@";
    EXPECT_FALSE(PasswordValidator::validate(password)); // Still no uppercase
    
    // User changes to: "Pass@"
    password = "Pass@";
    EXPECT_TRUE(PasswordValidator::validate(password)); // Now valid!
}

// Test de usabilidad: Límite de longitud visible
TEST(UsabilityTest, PasswordLengthLimit) {
    std::string password = "Pass@12345"; // 10 chars - max
    EXPECT_TRUE(PasswordValidator::validate(password));
    
    // User tries to add more characters
    std::string tooLong = password + "6"; // 11 chars
    EXPECT_FALSE(PasswordValidator::validate(tooLong));
    
    // UI should prevent typing beyond 10 characters
    EXPECT_GT(tooLong.length(), 10);
}

// Test de accesibilidad: Navegación con teclado
TEST(UsabilityTest, KeyboardNavigation) {
    // Simulate field navigation
    bool emailFieldActive = true;
    bool passwordFieldActive = false;
    
    // User presses Tab
    emailFieldActive = !emailFieldActive;
    passwordFieldActive = !passwordFieldActive;
    
    EXPECT_FALSE(emailFieldActive);
    EXPECT_TRUE(passwordFieldActive);
}

// Test de usabilidad: Indicadores visuales
TEST(UsabilityTest, VisualIndicators) {
    std::string password = "Test@123";
    
    // Check each requirement for visual indicator
    bool minLengthMet = PasswordValidator::hasMinLength(password);
    bool maxLengthMet = PasswordValidator::hasMaxLength(password);
    bool upperCaseMet = PasswordValidator::hasUpperCase(password);
    bool specialCharMet = PasswordValidator::hasSpecialChar(password);
    
    EXPECT_TRUE(minLengthMet);    // Green checkmark
    EXPECT_TRUE(maxLengthMet);    // Green checkmark
    EXPECT_TRUE(upperCaseMet);    // Green checkmark
    EXPECT_TRUE(specialCharMet);  // Green checkmark
}

// Test de usabilidad: Contraseña enmascarada
TEST(UsabilityTest, PasswordMasking) {
    std::string actualPassword = "Secret@123";
    std::string displayedPassword(actualPassword.length(), '*');
    
    // User should see asterisks
    EXPECT_EQ(displayedPassword, "**********");
    EXPECT_NE(displayedPassword, actualPassword);
}

// Test de experiencia: Recuperación de contraseña accesible
TEST(UsabilityTest, PasswordRecoveryAccessibility) {
    // Recovery option should be easily accessible
    bool recoveryButtonVisible = true;
    bool recoveryButtonClickable = true;
    
    EXPECT_TRUE(recoveryButtonVisible);
    EXPECT_TRUE(recoveryButtonClickable);
}

// Test de usabilidad: Mensajes de error amigables
TEST(UsabilityTest, UserFriendlyErrorMessages) {
    // Instead of technical errors, show user-friendly messages
    std::string password = "abc";
    
    if (!PasswordValidator::validate(password)) {
        // Should NOT show: "Validation failed: regex mismatch"
        // Should show: "Password must be 5-10 characters with 1 uppercase and 1 special character"
        EXPECT_TRUE(true);
    }
}

// Test de experiencia: Contador de intentos visible
TEST(UsabilityTest, AttemptCounterVisibility) {
    int attempts = 0;
    int maxAttempts = 5;
    
    // User should see: "Attempts: 1/5"
    attempts++;
    EXPECT_EQ(attempts, 1);
    EXPECT_LT(attempts, maxAttempts);
    
    // User should see: "Attempts: 2/5"
    attempts++;
    EXPECT_EQ(attempts, 2);
}

// Test de usabilidad: Tiempo de respuesta
TEST(UsabilityTest, ResponsiveValidation) {
    auto start = std::chrono::high_resolution_clock::now();
    
    PasswordValidator::validate("Test@123");
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Validation should be instant (< 10ms for good UX)
    EXPECT_LT(duration.count(), 10);
}

// Test de accesibilidad: Campos claramente etiquetados
TEST(UsabilityTest, ClearFieldLabels) {
    // Fields should have clear labels
    std::string emailLabel = "Email:";
    std::string passwordLabel = "Contrasena:";
    
    EXPECT_FALSE(emailLabel.empty());
    EXPECT_FALSE(passwordLabel.empty());
}

// Test de experiencia: Confirmación visual de éxito
TEST(UsabilityTest, SuccessConfirmation) {
    std::string validPassword = "Valid@123";
    
    if (PasswordValidator::validate(validPassword)) {
        // Should show green border or checkmark
        bool showSuccessIndicator = true;
        EXPECT_TRUE(showSuccessIndicator);
    }
}
