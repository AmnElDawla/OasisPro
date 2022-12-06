#include "Database.h"

Database::Database() {}

Database::~Database()
{
    databaseGui.close();
    QSqlDatabase::removeDatabase(databaseGui.defaultConnection);
};

// Initialize required datebase structure(s).
bool Database::initializeDatabase()
{
    databaseGui = QSqlDatabase::addDatabase("QSQLITE");
    databaseGui.setDatabaseName(QCoreApplication::applicationDirPath() + "/patient.db");

    if (!databaseGui.open())
    {
        qDebug() << "ERROR: Cannot open Database patient.db";
        return false;
    }

    return true;
};

// Initialize required tables in Database patient.db.
bool Database::initializeDatabaseTables()
{
    databaseGui.transaction();
    QSqlQuery queryTable;
    QString queryDatabaseUsersTable = "CREATE TABLE IF NOT EXISTS users (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, uid INTEGER NOT NULL, username TEXT NOT NULL);";
    QString queryDatabaseTreatmentHistoryTable = "CREATE TABLE IF NOT EXISTS treatmentHistory (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, uid INTEGER NOT NULL, tid INTEGER NOT NULL, session_type INTEGER NOT NULL, intensity_level INTEGER NOT NULL, duration INTEGER NOT NULL);";
    queryTable.exec(queryDatabaseUsersTable);
    queryTable.exec(queryDatabaseTreatmentHistoryTable);

    return databaseGui.commit();
};

// Initialize values in a user record.
bool Database::initializeDefaultUserRecord()
{
    databaseGui.transaction();
    QSqlQuery queryTable;
    // Initialize user names:
    QString queryRecordUser1 = "INSERT INTO users (username) VALUES (Eric)";
    QString queryRecordUser2 = "INSERT INTO users (username) VALUES (Robert)";
    QString queryRecordUser3 = "INSERT INTO users (username) VALUES (Angelina)";
    QString queryRecordUser4 = "INSERT INTO users (username) VALUES (Emma)";
    queryTable.exec(queryRecordUser1);
    queryTable.exec(queryRecordUser2);
    queryTable.exec(queryRecordUser3);
    queryTable.exec(queryRecordUser4);

    return databaseGui.commit();
};

// Insert a new user record into Database patient.db.
bool Database::addUserRecord(int userId, QString userName)
{
    databaseGui.transaction();
    QSqlQuery queryTable;
    // Select fields:
    QString queryDatabaseUsersTable = "INSERT INTO users (uid, username) VALUES (:uid, :username)";
    queryTable.prepare(queryDatabaseUsersTable);
    queryTable.bindValue(":uid", userId);
    queryTable.bindValue(":username", userName);
    queryTable.exec();

    // Print status:
    qDebug() << "";
    qDebug() << "Database: Inserting new user record into Table users:";
    qDebug() << "   user id: " << userId;
    qDebug() << "   user name: " << userName;

    return databaseGui.commit();
};

// Retrieve data of a user by user id from Database patient.db.
QVector<Users *> Database::getUserData(int userId)
{
    QVector<Users *> userData;

    databaseGui.transaction();
    QSqlQuery queryTable;
    // Select fields:
    QString queryDatabaseUsersTable = "SELECT uid FROM users WHERE uid = :userId";
    queryTable.prepare(queryDatabaseUsersTable);
    queryTable.bindValue(":userId", userId);
    queryTable.exec();

    int count = 0;
    while (queryTable.next())
    {
        count++;
        QString names = queryTable.value("username").toString();
        QString newCount = QString::fromStdString(std::to_string(count));
        qDebug() << "User " << newCount << " is named " << names;
    }

    return userData;
};

// Check if each value in a therapy record is valid.
bool Database::validateTherapyRecord(const int sessionType, const int intensityLevel, const int duration)
{
    int intensityMin = 0;
    int intensityMax = 8;
    bool validity = true;
    if (sessionType < 0)
    {
        qDebug() << "ERROR: Invalid " << sessionType << " record: session number is not valid";
        validity = false;
    }
    else if ((intensityLevel < intensityMin) || (intensityLevel > intensityMax))
    {
        qDebug() << "ERROR: Invalid " << sessionType << " record: intensity level is not valid";
        validity = false;
    }
    else if (duration < 0)
    {
        qDebug() << "ERROR: Invalid " << sessionType << " record: duration is not valid";
        validity = false;
    }
    return validity;
}

// Generate an increasing id for the a particular user's theraypy record.
int Database::getTherapyId(int userId)
{
    databaseGui.transaction();
    // Select and iterate through the uid column in datbase:
    QSqlQuery query;
    QString queryRecordHistory = "SELECT COUNT(uid) FROM treatmentHistory WHERE uid = :userId";
    query.prepare(queryRecordHistory);
    query.bindValue(":userId", userId);
    query.exec();

    // Generate new therapy id:
    query.first();
    int therapyId = query.value(0).toInt() + 1;

    return therapyId;
};

// Insert a therapy history record into Database patient.db.
bool Database::addTherapyHistoryRecord(int userId, TherapyRecord *tr)
{
    /* Note:
    Conversion of each elemment in seesion array:
    session -> button index
    duration -> actual value of the duration (not button index)
    intensity level -> actual values
    */
    int session = tr->getSessionType();
    int intensity = tr->getIntensityLevel();
    int duration = tr->getDuration();

    // Validate input therapy record:
    if (!validateTherapyRecord(session, intensity, duration))
    {
        return false;
    }

    // Upadate the id of a therapy history record:
    int therapyId = getTherapyId(userId);

    // Insert therapy history into Table treatmentHistory:
    databaseGui.transaction();
    QSqlQuery queryTable;
    QString queryRecordHistory = "INSERT INTO treatmentHistory (uid, tid, session_type, intensity_level, duration) VALUES (:uid, :tid, :session_type, :intensity_level, :duration)";
    queryTable.prepare(queryRecordHistory);
    queryTable.bindValue(":uid", userId);
    queryTable.bindValue(":tid", therapyId);
    queryTable.bindValue(":session_type", session);
    queryTable.bindValue(":intensity_level", intensity);
    queryTable.bindValue(":duration", duration);
    queryTable.exec();

    // Print status:
    qDebug() << "";
    qDebug() << "Database: Inserting therapy history record into Table treatmentHistory:";
    qDebug() << "   user id: " << userId;
    qDebug() << "   therapy id: " << therapyId;
    qDebug() << "   session: " << session;
    qDebug() << "   database: " << intensity;
    qDebug() << "   duration: " << duration;

    return databaseGui.commit();
};

// Retrieve all therapy records of a specific user by user id.
QVector<TherapyRecord *> Database::getTherapyHistoryRecords(int userId)
{
    QVector<TherapyRecord *> therapyHistoryRecordData;

    databaseGui.transaction();
    QSqlQuery queryTable;
    // Select fields:
    QString queryDatabaseTherapyHistoryRecordTable = "SELECT * FROM treatmentHistory WHERE uid = :userId";
    queryTable.prepare(queryDatabaseTherapyHistoryRecordTable);
    queryTable.bindValue(":userId", userId);
    queryTable.exec();

    // iterate through the columns by uid in Database patient.db:
    int rowCounter = 0;
    while (queryTable.next())
    {
        rowCounter++;
        int session = queryTable.value("session_type").toInt();
        int intensity = queryTable.value("intensity_level").toInt();
        int duration = queryTable.value("duration").toInt();
        TherapyRecord *thr = new TherapyRecord(session, intensity, duration);
        therapyHistoryRecordData.push_back(thr);
    }

    // Print status:
    qDebug() << "   Result: Found " << rowCounter << " therapy history records about User " << userId;

    return therapyHistoryRecordData;
};

// Delete all threapy history records of a specified user.
bool Database::deleteTherapyHistoryRecords(int userId)
{
    databaseGui.transaction();
    QSqlQuery queryTable;
    // select fields:
    QString queryDatabaseTherapyHistoryRecordTable = "DELETE FROM treatmentHistory WHERE uid = :userId";
    queryTable.prepare(queryDatabaseTherapyHistoryRecordTable);
    queryTable.bindValue(":userId", userId);
    queryTable.exec();

    return databaseGui.commit();
};

// Read a therapy record and update elements of session array.
void Database::updateSelectedSession(TherapyRecord *tr){
    //        objData.sessionArray[0] = tr->getDuration();
    //        objData.sessionArray[1] = tr->getSessionType();
    //        objData.sessionArray[2] = tr->getIntensityLevel();
};
