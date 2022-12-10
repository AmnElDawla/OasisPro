#include "Database.h"

Database::Database() {}

Database::~Database()
{
    qDebug() << "Database: Disconnecting from database...";
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
    QString dbPath = QCoreApplication::applicationDirPath() + "/patient.db";
    qDebug("MainWindow: Full file path of database: ");
    qDebug()<<"     " << dbPath;
    qDebug(" ");

    databaseGui = QSqlDatabase::addDatabase("QSQLITE");
    databaseGui.setDatabaseName(dbPath);

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
    QVector <QString> userNames = {"Eric", "Robert", "Angelina", "Emma"};
    for (int i = 0; i < userNames.size() ; i++)
    {
        if (!(this->addUserRecord(i + 1, userNames[i])))
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
    QString queryDatabaseTreatmentHistoryTable = "CREATE TABLE IF NOT EXISTS treatmentHistory (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, uid INTEGER NOT NULL REFERENCES users, tid INTEGER NOT NULL, session_type INTEGER NOT NULL, intensity_level INTEGER NOT NULL, duration INTEGER NOT NULL)";
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
        int userId = queryTable.value("uid").toInt();
        QString userName = queryTable.value("username").toString();

        // Print Status:
        qDebug() << "Database: User " << userId << " is named " << userName;

        if (userId == 1)
        {
            Administrator *admin = new Administrator(userId, userName);
            userData.push_back(admin);
            count++;
        }
        else if (userId > 1)
        {
            Guest *guest = new Guest(userId, userName);
            userData.push_back(guest);
            count++;
        }
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

    // Update the id of a therapy history record:
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
    qDebug() << "Database: Response: Found " << rowCounter << " therapy history records. ";

    return therapyHistoryRecordData;
};

// Delete all threapy history records as an administrator.
bool Database::deleteTherapyHistoryRecords(Users *user)
{
    // Check if user pointer is valid:
    if (user)
    {
        // Identiy authentication:
        qDebug() << "Database: Veryfying user identiy before Operation 'delete all therapy history records'...";

        /* Unauthorized access: */

        // Notify user:
        if ((user->getId() != 1) || (user->getType() != "admin"))
        {
            QMessageBox AlertUnauthorizedUser;
            AlertUnauthorizedUser.critical(0, "Permission Denied", "Only an administrator is allowed to delete therapy records.");

            qDebug("Database: Operation 'delete all therapy records' was not completed (unauthorized user). ");

            return false;
        }

        /* Authourized access: */

        // Confirm operation:
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Administrator " + user->getName(), "Are you sure to remove all therapy records?", QMessageBox::Yes | QMessageBox::No).exec())
        {
            // Delete all therapy history records in database:
            databaseGui.transaction();
            QSqlQuery queryTable;
            // Select table:
            QString queryDatabaseTherapyHistoryRecordTable = "DELETE FROM treatmentHistory";
            queryDatabaseTherapyHistoryRecordTable = "DROP TABLE treatmentHistory";
            queryTable.prepare(queryDatabaseTherapyHistoryRecordTable);
            queryTable.exec();

            if (databaseGui.commit()) {
                if (this->initializeDatabaseTables()) {
                    qDebug("Database: Operation 'delete all therapy records' was successfually completed.");
                    return true;
                }
            }

            qDebug("Database: Operation 'delete all therapy records' was not completed.");

            return false;
        }

        qDebug("Database: Operation 'delete all therapy records' was cancelled. ");

        return false;
    }
    else
    {
        // Null pointer handler:
        qDebug("Database: Operation 'delete all therapy records' was not completed (null user pointer). ");

        return false;
    }
};
