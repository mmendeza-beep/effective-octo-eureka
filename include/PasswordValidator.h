#ifndef PASSWORDVALIDATOR_H
#define PASSWORDVALIDATOR_H

#include <string>

class PasswordValidator {
public:
    static bool validate(const std::string& password);
    static bool hasMinLength(const std::string& password);
    static bool hasMaxLength(const std::string& password);
    static bool hasUpperCase(const std::string& password);
    static bool hasSpecialChar(const std::string& password);
};

#endif
