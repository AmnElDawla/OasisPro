#ifndef USERS_H
#define USERS_H

#include <QDebug>
#include <QString>
#include <QMessageBox>

class Users
{

public:
    // Constructor:
    Users(int id = 0, QString name = "N/A", QString = "unknown");

    // Destructor:
    ~Users();

    // Member funtions:
    void print() const;

    // Getters:
    int getId() const;
    QString getName() const;
    QString getType() const;

    // Virtual member functions (base case):

protected:
    // Member variables:
    int id;
    QString name;
    QString type;
};

#endif // USERS_H
