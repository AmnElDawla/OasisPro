#include "Database.h"

Database::Database() {}

Database::~Database()
{

    databaseGui.close();
    QSqlDatabase::removeDatabase(databaseGui.defaultConnection);
}

bool Database::initializeDatabase()
{

    databaseGui = QSqlDatabase::addDatabase("QSQLITE");
    databaseGui.setDatabaseName(QCoreApplication::applicationDirPath() + "/patient.db");

    if (!databaseGui.open())
    {
        return false;
    }

    return true;

}

bool Database::initializeDatabaseTables()
{

    databaseGui.transaction();

    QString queryDatabaseUsersTable = "CREATE TABLE IF NOT EXISTS users (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, session TEXT NOT NULL)";
    QString queryDatabaseTherapyTable = "CREATE TABLE IF NOT EXISTS therapy (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, session_type TEXT NOT NULL, duration INT NOT NULL, intensity_level INT NOT NULL)";
    QString queryDatabaseTreatmentHistoryTable = "CREATE TABLE IF NOT EXISTS treatmentHistory (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, fk_therapy INT NOT NULL, fk_users INT NOT NULL)";

    QSqlQuery queryTable;
    queryTable.exec(queryDatabaseUsersTable);
    queryTable.exec(queryDatabaseTherapyTable);
    queryTable.exec(queryDatabaseTreatmentHistoryTable);

    return databaseGui.commit();

}

bool Database::initializeDefaultUserRecord()
{

    databaseGui.transaction();

    QString queryRecordUser1 = "INSERT INTO users (session) VALUES (Eric)";
    QString queryRecordUser2 = "INSERT INTO users (session) VALUES (Robert)";
    QString queryRecordUser3 = "INSERT INTO users (session) VALUES (Angelina)";
    QString queryRecordUser4 = "INSERT INTO users (session) VALUES (Emma)";

    QSqlQuery queryTable;

    queryTable.exec(queryRecordUser1);
    queryTable.exec(queryRecordUser2);
    queryTable.exec(queryRecordUser3);
    queryTable.exec(queryRecordUser4);

    return databaseGui.commit();

}

bool Database::addUserRecord(QString session)
{

    databaseGui.transaction();

    QString queryDatabaseUsersTable = "INSERT INTO users (session) VALUES (:session)";

    QSqlQuery queryTable;
    queryTable.prepare(queryDatabaseUsersTable);
    queryTable.bindValue(":session", session);
    queryTable.exec();

    return databaseGui.commit();

}

bool Database::validateTherapyRecord(const int sessionType, const int intensityLevel, const int duration)
{

    int intensityMin = 0;
    int intensityMax = 8;
    bool validity = true;
    if (intensityLevel < intensityMin || intensityLevel > intensityMax)
    {
        qDebug() << "Error: Invalid " << sessionType << " record: intensity level is not valid";
        validity = false;
    }
    else if (duration < 0)
    {
        qDebug() << "Error: Invalid " << sessionType << " record: duration is not valid";
        validity = false;
    }
    return validity;

}

QVector<Users *> Database::getUserData(int id)
{

    databaseGui.transaction();

    QString queryDatabaseUsersTable = "SELECT * FROM users WHERE id = :id";

    QSqlQuery queryTable;
    QVector<Users *> userData;

    queryTable.prepare(queryDatabaseUsersTable);
    queryTable.bindValue(":id", id);
    queryTable.exec();

    int count = 0;

    while (queryTable.next())
    {
        QString names = queryTable.value("session").toString();
        QString newCount = QString::fromStdString(std::to_string(count));
        qDebug() << "User " << newCount << " is named " << names;
        count++;
    }

    return userData;

}

int Database::getTherapyId(int userId)
{

    databaseGui.transaction();

    QSqlQuery query;
    QString queryRecordHistory = "SELECT * FROM treatmentHistory";
    query.prepare(queryRecordHistory);
    query.exec();

    int rowCounter = 0;

    while (query.next())
    {
        int uid = query.value("uid").toInt();
        if (uid == userId)
        {
            rowCounter++;
        }
    }
    qDebug() << "Generating Therapy Id: found " << rowCounter << "results of user " << userId;
    int therapyId = rowCounter;
    therapyId++;
    return therapyId;

}

/*
Conversion of each elemment in seesion array:

session -> button index
duration -> actual value of the duration (not button index)
intensity level -> actual values

*/
bool Database::addTherapyHistoryRecord(int userId, TherapyRecord *tr)
{

    int session = tr->getSessionType();
    int intensity = tr->getIntensityLevel();
    int duration = tr->getDuration();
    if (!validateTherapyRecord(session, intensity, duration))
    {
        return false;
    }

    int therapyId = getTherapyId(userId);

    databaseGui.transaction();
    qDebug() << userId << therapyId << session << intensity << duration;

    QString queryRecordHistory = "INSERT INTO treatmentHistory (uid, tid, session_type, intensity_level, duration) VALUES (:uid, :tid, :session_type, :intensity_level, :duration);";
    QSqlQuery queryTable;
    queryTable.prepare(queryRecordHistory);
    queryTable.bindValue(":uid", userId);
    queryTable.bindValue(":tid", therapyId);
    queryTable.bindValue(":session_type", session);
    queryTable.bindValue(":intensity_level", intensity);
    queryTable.bindValue(":duration", duration);
    queryTable.exec();

    return databaseGui.commit();

}

QVector<TherapyRecord *> Database::getTherapyHistoryRecords(int userId)
{

    // TODO: retrieve all therapy records of a user by userId
    databaseGui.transaction();
    QString queryDatabaseTherapyHistoryRecordTable = "SELECT * FROM treatmentHistory";
    QSqlQuery queryTable;
    queryTable.prepare(queryDatabaseTherapyHistoryRecordTable);
    queryTable.bindValue(":uid", userId);
    queryTable.exec();
    QVector<TherapyRecord *> therapyHistoryRecordData;
    while (queryTable.next())
    {
        int uid = queryTable.value("uid").toInt();
        if (uid == userId)
        {
            int session = queryTable.value(0).toString().toInt();
            int intensity = queryTable.value(1).toString().toInt();
            int duration = queryTable.value(2).toString().toInt();
            TherapyRecord *thr = new TherapyRecord(session, intensity, duration);
            therapyHistoryRecordData.push_back(thr);
        }
    }

    return therapyHistoryRecordData;

}

void Database::updateSelectedSession(TherapyRecord *tr)
{

    sessionArray[0] = tr->getDuration();
    sessionArray[1] = tr->getSessionType();
    sessionArray[2] = tr->getIntensityLevel();

}
