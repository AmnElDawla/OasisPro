#ifndef GUEST_H
#define GUEST_H

#include "Users.h"

class Guest : public Users
{
public:
    // Constructor:
    Guest(); // Default constructor
    Guest(int id, QString name);

    // Destructor:
    ~Guest();

    // Mmeber Functions:
    void print() const;

    // Inherited virtual memember functions:
};

#endif // GUEST_H
