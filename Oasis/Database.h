#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlQuery>

class Database {
public:
    Database();
    bool initializeDatabaseTables();
    bool initializeDatabase();
    bool initializeDefaultUserRecord();
    bool addTherapyRecord();
    bool addTherapyHistoryRecord();
    bool addUserRecord();
    ~Database();

private:
    QSqlDatabase databaseGui;

};


#endif // DATABASE_H
