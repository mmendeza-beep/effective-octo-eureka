#include <gtest/gtest.h>
#include "PasswordValidator.h"

// ============================================
// PRUEBAS DE CAJA NEGRA - Password Validator
// ============================================

// Tests de longitud mínima (5 caracteres)
TEST(PasswordValidatorTest, RejectsTooShort) {
    EXPECT_FALSE(PasswordValidator::validate("Ab@1"));  // 4 chars
    EXPECT_FALSE(PasswordValidator::validate("A@"));     // 2 chars
    EXPECT_FALSE(PasswordValidator::validate(""));       // empty
}

TEST(PasswordValidatorTest, AcceptsMinimumLength) {
    EXPECT_TRUE(PasswordValidator::validate("Ab@12"));  // 5 chars - exactly minimum
}

// Tests de longitud máxima (10 caracteres)
TEST(PasswordValidatorTest, RejectsTooLong) {
    EXPECT_FALSE(PasswordValidator::validate("Ab@1234567890"));  // 14 chars
    EXPECT_FALSE(PasswordValidator::validate("Ab@12345678"));    // 11 chars
}

TEST(PasswordValidatorTest, AcceptsMaximumLength) {
    EXPECT_TRUE(PasswordValidator::validate("Ab@1234567"));  // 10 chars - exactly maximum
}

// Tests de mayúscula requerida
TEST(PasswordValidatorTest, RejectsNoUpperCase) {
    EXPECT_FALSE(PasswordValidator::validate("ab@12"));   // no uppercase
    EXPECT_FALSE(PasswordValidator::validate("abc@123")); // no uppercase
}

TEST(PasswordValidatorTest, AcceptsWithUpperCase) {
    EXPECT_TRUE(PasswordValidator::validate("Ab@12"));    // has uppercase A
    EXPECT_TRUE(PasswordValidator::validate("aBc@12"));   // has uppercase B
    EXPECT_TRUE(PasswordValidator::validate("abC@12"));   // has uppercase C
}

// Tests de carácter especial requerido
TEST(PasswordValidatorTest, RejectsNoSpecialChar) {
    EXPECT_FALSE(PasswordValidator::validate("Abc12"));    // no special char
    EXPECT_FALSE(PasswordValidator::validate("ABCDE"));    // no special char
}

TEST(PasswordValidatorTest, AcceptsWithSpecialChar) {
    EXPECT_TRUE(PasswordValidator::validate("Ab@12"));    // has @
    EXPECT_TRUE(PasswordValidator::validate("Ab#12"));    // has #
    EXPECT_TRUE(PasswordValidator::validate("Ab$12"));    // has $
    EXPECT_TRUE(PasswordValidator::validate("Ab!12"));    // has !
    EXPECT_TRUE(PasswordValidator::validate("Ab*12"));    // has *
}

// Tests de combinaciones válidas
TEST(PasswordValidatorTest, AcceptsValidPasswords) {
    EXPECT_TRUE(PasswordValidator::validate("Pass@123"));
    EXPECT_TRUE(PasswordValidator::validate("Secure#1"));
    EXPECT_TRUE(PasswordValidator::validate("MyP@ss99"));
    EXPECT_TRUE(PasswordValidator::validate("Test!2024"));
}

// Tests de combinaciones inválidas
TEST(PasswordValidatorTest, RejectsInvalidCombinations) {
    EXPECT_FALSE(PasswordValidator::validate("password"));     // no upper, no special
    EXPECT_FALSE(PasswordValidator::validate("PASSWORD"));     // no special
    EXPECT_FALSE(PasswordValidator::validate("Pass1234"));     // no special
    EXPECT_FALSE(PasswordValidator::validate("pass@word"));    // no upper
    EXPECT_FALSE(PasswordValidator::validate("P@"));           // too short
}

// ============================================
// PRUEBAS UNITARIAS - Funciones individuales
// ============================================

TEST(PasswordValidatorTest, HasMinLengthFunction) {
    EXPECT_FALSE(PasswordValidator::hasMinLength("1234"));
    EXPECT_TRUE(PasswordValidator::hasMinLength("12345"));
    EXPECT_TRUE(PasswordValidator::hasMinLength("123456"));
}

TEST(PasswordValidatorTest, HasMaxLengthFunction) {
    EXPECT_TRUE(PasswordValidator::hasMaxLength("1234567890"));
    EXPECT_FALSE(PasswordValidator::hasMaxLength("12345678901"));
    EXPECT_TRUE(PasswordValidator::hasMaxLength("12345"));
}

TEST(PasswordValidatorTest, HasUpperCaseFunction) {
    EXPECT_FALSE(PasswordValidator::hasUpperCase("lowercase"));
    EXPECT_TRUE(PasswordValidator::hasUpperCase("Uppercase"));
    EXPECT_TRUE(PasswordValidator::hasUpperCase("ALLCAPS"));
    EXPECT_TRUE(PasswordValidator::hasUpperCase("miXed"));
}

TEST(PasswordValidatorTest, HasSpecialCharFunction) {
    EXPECT_FALSE(PasswordValidator::hasSpecialChar("NoSpecial123"));
    EXPECT_TRUE(PasswordValidator::hasSpecialChar("Has@Special"));
    EXPECT_TRUE(PasswordValidator::hasSpecialChar("Has#Special"));
    EXPECT_TRUE(PasswordValidator::hasSpecialChar("Has!Special"));
    EXPECT_TRUE(PasswordValidator::hasSpecialChar("Has$Special"));
}

// Tests de casos extremos
TEST(PasswordValidatorTest, EdgeCases) {
    // Exactamente 5 caracteres con todos los requisitos
    EXPECT_TRUE(PasswordValidator::validate("A@bcd"));
    
    // Exactamente 10 caracteres con todos los requisitos
    EXPECT_TRUE(PasswordValidator::validate("A@bcdefgh1"));
    
    // Solo caracteres especiales
    EXPECT_FALSE(PasswordValidator::validate("@#$%^"));
    
    // Solo mayúsculas
    EXPECT_FALSE(PasswordValidator::validate("ABCDE"));
    
    // Múltiples caracteres especiales
    EXPECT_TRUE(PasswordValidator::validate("A@#$%b"));
}
