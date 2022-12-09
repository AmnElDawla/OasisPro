#include "Administrator.h"

// Constructors:
Administrator::Administrator() : Users(){
    this->type = "admin";
};

Administrator::Administrator(int id, QString name) : Users(id, name, "admin"){};

// Destructors:
Administrator::~Administrator(){};

// Member functions:
void Administrator::print() const
{
    QString msg = "Administrator Information: \n";
    msg += "    id:" + QString::number(this->id) + "\n" +
           "    name:" + this->name + "\n" +
           "    type:" + this->type;
    qDebug() << msg;
};

// Inherited virtual member functions:
