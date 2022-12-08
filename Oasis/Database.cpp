#include "Database.h"

Database::Database() {}

Database::~Database()
{
    databaseGui.close();
    QSqlDatabase::removeDatabase(databaseGui.defaultConnection);
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

// Initialize values in a user record.
bool Database::initializeDefaultUserRecord()
{
    QString userNames[4] = {"Eric", "Robert", "Angelina", "Emma"};
    for (int i = 0; i < 4; i++)
    {
        if ((this->addUserRecord(i + 1, userNames[i])) == false)
        {
            return false;
        }
    }
    return true;
};

// Initialize required tables in Database patient.db.
bool Database::initializeDatabaseTables()
{
    databaseGui.transaction();
    QSqlQuery queryTable;

    QString queryDropUsersTable = "DROP TABLE users;";
    queryTable.exec(queryDropUsersTable);

    QString queryDatabaseUsersTable = "CREATE TABLE IF NOT EXISTS users (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, uid INTEGER NOT NULL, username TEXT NOT NULL)";
    QString queryDatabaseTreatmentHistoryTable = "CREATE TABLE IF NOT EXISTS treatmentHistory (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, uid INTEGER NOT NULL, tid INTEGER NOT NULL, session_type INTEGER NOT NULL, intensity_level INTEGER NOT NULL, duration INTEGER NOT NULL)";
    queryTable.exec(queryDatabaseUsersTable);
    queryTable.exec(queryDatabaseTreatmentHistoryTable);

    databaseGui.commit();

    return initializeDefaultUserRecord();
};

// Retrieve data of a user by user id from Database patient.db.
QVector<Users *> Database::getUserData()
{
    QVector<Users *> userData;

    databaseGui.transaction();
    QSqlQuery queryTable;
    // Select fields:
    QString queryDatabaseUsersTable = "SELECT * FROM users";
    queryTable.prepare(queryDatabaseUsersTable);
    queryTable.exec();

    int count = 0;
    while (queryTable.next())
    {
        count++;
        int UserId = queryTable.value("uid").toInt();
        QString userName = queryTable.value("username").toString();

        // Print Status:
        QString newCount = QString::fromStdString(std::to_string(count));
        qDebug() << "Database: User " << newCount << " is named " << userName;

        if (UserId == 1)
        {
            Administrator *admin = new Administrator(UserId, userName, "admin");
            userData.push_back(admin);
            delete admin;
        }
        else if (UserId > 1)
        {
            Guest *guest = new Guest(UserId, userName, "guest");
            userData.push_back(guest);
            delete guest;
        }
    }

    return userData;
};

// Return the specific username given a specific user id.
QString Database::getUserById(int id) {

    databaseGui.transaction();
    QSqlQuery queryTable;
    // Select fields:
    QString queryDatabaseUsersTable = "SELECT * FROM users";
    queryTable.prepare(queryDatabaseUsersTable);
    queryTable.exec();

    int count = 0;
    while (queryTable.next())
    {

        count++;
        int userId = queryTable.value("uid").toInt();

        if(userId == id) {
            QString userName = queryTable.value("username").toString();
            return userName;
        }
    }

    return nullptr;

}

// Check if each value in a therapy record is valid.
bool Database::validateTherapyRecord(const int sessionType, const int intensityLevel, const int duration)
{
    int intensityMin = 0;
    int intensityMax = 8;
    bool validity = true;
    if (sessionType < 0)
    {
        qDebug() << "ERROR: Invalid threapy record: session number is not valid";
        validity = false;
    }
    else if ((intensityLevel < intensityMin) || (intensityLevel > intensityMax))
    {
        qDebug() << "ERROR: Invalid threapy record: intensity level is not valid";
        validity = false;
    }
    else if (duration < 0)
    {
        qDebug() << "ERROR: Invalid threapy record: duration is not valid";
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
    QString queryRecordHistory = "SELECT uid FROM treatmentHistory WHERE uid = :userId";
    query.prepare(queryRecordHistory);
    query.bindValue(":userId", userId);
    query.exec();

    // Generate new therapy id:
    int therapyId = 0;
    while (query.next())
    {
        therapyId++;
    }
    therapyId++;

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
    qDebug() << "   session type: " << session;
    qDebug() << "   intensity level: " << intensity;
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
