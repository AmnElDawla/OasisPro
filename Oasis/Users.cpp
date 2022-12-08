#include "Users.h"

// Constructor:
Users::Users(int newId, QString newName, QString newType) : id(newId), name(newName), type(newType){};

// Destructor:
Users::~Users(){};

// Member functions:
int Users::getId() const { return id; };

QString Users::getName() const { return name; };

QString Users::getType() const { return type; };

void Users::setName(const QString &newName) { this->name = newName; };

void Users::print() const
{
    QString msg = "User Information: \n";
    msg += "    id:" + QString::number(this->id) + "\n" +
           "    name:" + this->name;
           "    type:" + this->type;
    qDebug() << msg;
}

// Virtual member functions:


