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
    QVector<Users *> getUserData(int id);
    bool validateTherapyRecord(const int sessionType, const int intensityLevel, const int duration);
    int getTherapyId(int userId);
    bool addTherapyHistoryRecord(int userId, TherapyRecord *tr);
    bool addUserRecord(QString name);
    QVector<TherapyRecord *> getTherapyHistoryRecords(int userId);
    void updateSelectedSession(TherapyRecord *tr);

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
