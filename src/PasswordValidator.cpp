#include "PasswordValidator.h"
#include <cctype>

bool PasswordValidator::validate(const std::string& password) {
    return hasMinLength(password) && 
           hasMaxLength(password) && 
           hasUpperCase(password) && 
           hasSpecialChar(password);
}

bool PasswordValidator::hasMinLength(const std::string& password) {
    return password.length() >= 5;
}

bool PasswordValidator::hasMaxLength(const std::string& password) {
    return password.length() <= 10;
}

bool PasswordValidator::hasUpperCase(const std::string& password) {
    for (char c : password) {
        if (std::isupper(c)) {
            return true;
        }
    }
    return false;
}

bool PasswordValidator::hasSpecialChar(const std::string& password) {
    for (char c : password) {
        if (!std::isalnum(c)) {
            return true;
        }
    }
    return false;
}
