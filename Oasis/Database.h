#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlQuery>
#include "Users.h"

class Database {
public:
    Database();
    bool initializeDatabaseTables();
    bool initializeDatabase();
    bool initializeDefaultUserRecord();
    bool addTherapyRecord();
    bool addTherapyHistoryRecord();
    bool addUserRecord();
    bool addTherapyHistoryRecord(int userId, int therapyId);
    bool addTherapyRecord(QString session, int intensity, int duration);
    bool addUserRecord(QString name);
    QVector<Users*> getUserData(int id);

    ~Database();

private:
    QSqlDatabase databaseGui;

};


#endif // DATABASE_H
