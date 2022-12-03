#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Users.h"
#include "TherapyRecord.h"
#include <QDebug>
#include <QCoreApplication>

class Database
{

public:
    Database();
    bool initializeDatabaseTables();
    bool initializeDatabase();
    bool initializeDefaultUserRecord();
    bool addUserRecord();
    bool validateTherapyRecord(const int sessionType, const int intensityLevel, const int duration);
    bool addTherapyHistoryRecord(int userId, TherapyRecord *tr); // Construct a NEW threapy record from current session first
    bool addUserRecord(QString name);
    // void selectFromHistoryRecords();
    void updateSelectedSession(TherapyRecord *tr);

    QVector<Users *> getUserData(int id);
    QVector<TherapyRecord *> getTherapyHistoryRecords(int userId);
    // Need another function to select a record from the list above.

    ~Database();

private:
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
