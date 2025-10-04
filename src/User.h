#ifndef USER_H
#define USER_H

#include "Utils.h"

// User Management Class (Encapsulates user data and authentication logic)
class User {
private:
    std::string username;
    std::string password;
    std::string email;

    std::string cipher(const std::string& text);

public:
    void registerUser();
    std::string loginUser();
};

#endif