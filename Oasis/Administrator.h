#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Users.h"

class Administrator : public Users
{
public:
    // Constructor:
    Administrator(); // Default constructor
    Administrator(int id, QString name, QString type);

    // Destructor:
    ~Administrator();

    // Mmeber Functions:
    void setName(const QString &newName);
    void print() const;
    // Inherited virtual memember functions:

};

#endif // ADMINISTRATOR_H
