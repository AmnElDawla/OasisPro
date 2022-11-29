#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Users.h"
#include "TherapyRecord.h"


class Database
{
public:
    Database();
    bool initializeDatabaseTables();
    bool initializeDatabase();
    bool initializeDefaultUserRecord();
    bool validateRecord(const QString &sessionType, const int intensityLevel, const int duration);
    bool addTherapyRecord(const QString &session, int intensity, int duration);
    bool addUserRecord();
    bool addTherapyHistoryRecord(int userId, int therapyId, TherapyRecord &tr); // Construct a NEW threapy record from current session first
    bool addUserRecord(QString name);
    // void selectFromHistoryRecords();
    void updateSelectedSession(TherapyRecord &tr);

    QVector<Users *> getUserData(int id);
    QVector<TherapyRecord *> getTherapyHistoryRecords(int userId);
    // Need another function to select a record from the list above.

    ~Database();

private:
    QSqlDatabase databaseGui;
};

#endif // DATABASE_H
