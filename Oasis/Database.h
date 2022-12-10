#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "TherapyRecord.h"
#include "Administrator.h"
#include "Guest.h"

class Database
{

public:
    // Constructor:
    Database();
    // Destructor:
    ~Database();
    // Member functions:
    bool initializeDatabaseTables();
    bool initializeDatabase();
    bool addUserRecord(int userId, QString name);
    bool initializeDefaultUserRecord();
    QVector<Users *> getUserData();
    bool validateTherapyRecord(const int sessionType, const int intensityLevel, const int duration);
    int getTherapyId(int userId);
    bool addTherapyHistoryRecord(int userId, TherapyRecord *tr);
    QVector<TherapyRecord *> getTherapyHistoryRecords(int userId);
    bool deleteTherapyHistoryRecords(Users *user);

private:
    // Member variables:
    QSqlDatabase databaseGui;
    /*
     * This array is special. Its indices all follow a standard that should
     * be used everywhere in the project. The standard is as follows:
     *      sessionArray[0]: Stores duration of the session
     *      sessionArray[1]: Stores session type
     *      sessionArray[2]: Stores intensity level of the session at the time of completion
     */
    int sessionArray[3];
    friend class MainWindow;
};

#endif // DATABASE_H
