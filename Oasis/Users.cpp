#include "Users.h"
#include <QString>

Users::Users(int newId, QString newName) {
    this->id = newId;
    this->name = newName;
}

QString Users::getName() {
    return name;
}

int Users::getId() {
    return id;
}

