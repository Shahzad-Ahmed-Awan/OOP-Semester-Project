#ifndef MODULE_H
#define MODULE_H

#include "Utils.h"

// --- OOP Core Classes ---

// Base Class for all Application Modules
// This is a key part of polymorphism. All modules will inherit from this class.
class Module {
protected:         // This is main parrents class from which task management, fitness, habit, finance and mental wellness classes will inherit
    std::string currentUser;
public:
    Module(const std::string& user) : currentUser(user) {}
    virtual ~Module() = default;

    // A pure virtual function. This forces all derived classes to implement a `runMenu` method.
    // This is the core of our polymorphic design.
    virtual void runMenu() = 0;
};

#endif