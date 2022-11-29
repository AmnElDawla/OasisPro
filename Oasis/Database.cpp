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

bool Database::validateRecord(const QString &sessionType, const int intensityLevel, const int duration)
{
    bool validity = true;
    else if (intensityLevel < 1 || intensityLevel > 8)
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

bool Database::addTherapyHistoryRecord(int userId, int therapyId, TherapyRecord &tr)
{
    QString session = tr.getSessionType();
    int intensity = tr.getIntensityLevel();
    int duration = tr.getDuration();
    if (!validateRecord(session, intensity, duration))
    {
        return false;
    }

    databaseGui.transaction();

    QString queryRecordHistory = "INSERT INTO treatmentHistory (users, therapy, session_type, intensity_level, duration) VALUES (:therapy, :users, :session, :intensity, :duration)";

    QSqlQuery query;
    int rowCounter = 0;
    query.exec("SELECT COUNT(*) FROM therapy treatmentHistory WHERE userId = :id");
    if (query.first())
        rowCounter = query.value(0).toInt();
    therapyId = rowCounter++;

    QSqlQuery queryTable;
    queryTable.prepare(queryRecordHistory);
    queryTable.bindValue(":therapy", therapyId);
    queryTable.bindValue(":users", userId);
    queryTable.bindValue(":session", session);
    queryTable.bindValue(":intensity", intensity);
    queryTable.bindValue(":duration", duration);
    queryTable.exec();

    return databaseGui.commit();
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

QVector<TherapyRecord *> Database::getTherapyHistoryRecords(int userId)
{
    // TODO: retrieve all therapy records of a user by userId
    databaseGui.transaction();
    QString queryDatabaseTherapyHistoryRecordTable = "SELECT * FROM treatmentHistory WHERE userId = :users";
    //"SELECT session as treatment,date,intensity,duration FROM ( SELECT session as session,tid as rid FROM therapy_records UNION SELECT session as session,fid as rid FROM frequency_records ) NATURAL JOIN records ORDER BY rid;";
    QSqlQuery queryTable;
    queryTable.prepare(queryDatabaseTherapyHistoryRecordTable);
    queryTable.bindValue(":id", userId);
    queryTable.exec();
    QVector<TherapyRecord *> therapyHistoryRecordData;
    while (queryTable.next())
    {
        QString session = queryTable.value(0).toString();
        int intensity = queryTable.value(1).toString().toInt();
        int duration = queryTable.value(2).toString().toInt();
        TherapyRecord *thr = new TherapyRecord(session, intensity, duration);
        therapyHistoryRecordData.push_back(thr);
    }

    return therapyHistoryRecordData;
};

void Database::updateSelectedSession(TherapyRecord &tr)
{
    QString session = tr.getSessionType();
    int intensity = tr.getIntensityLevel();
    int duration = tr.getDuration();

    if (validateRecord(session, intensity, duration))
    {
        sessionArray[0] = duration;
        sessionArray[1] = session;
        sessionArray[2] = intensity;
    }
    /* Problem:
     * Need another method to access the sessionArray
     *
     * possible solutions:
     * 1. set it as public variable in mainwindow.h?
     * 2. make this class as a friend
     *
     * */
};
