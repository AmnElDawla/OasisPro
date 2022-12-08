#include "Guest.h"

// Constructor:
Guest::Guest() : Users(){
    this->type = "guest";
};

Guest::Guest(int id, QString name, QString type) : Users(id, name, type){};

// Destructors:
Guest::~Guest(){};

// Member functions:
void Guest::print() const
{
    QString msg = "Guest Information: \n";
    msg += "    id:" + QString::number(this->id) + "\n" +
           "    name:" + this->name;
           "    type:" + this->type;
    qDebug() << msg;
};

// Inherited virtual member functions:
