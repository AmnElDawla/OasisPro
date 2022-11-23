#ifndef USERS_H
#define USERS_H

#include <QString>

class Users {

public:
    Users(int, QString);
    QString getName();
    int getId();

private:
    int id;
    QString name;

};

#endif // USERS_H
