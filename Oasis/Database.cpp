#include "Database.h"

Database::Database() {}

Database::~Database() {

    databaseGui.close();
    QSqlDatabase::removeDatabase(databaseGui.defaultConnection);

}

bool Database::initializeDatabase() {

    databaseGui = QSqlDatabase::addDatabase("QSQLITE");
    databaseGui.setDatabaseName(QCoreApplication::applicationDirPath()+"/patient.db");

    if(!databaseGui.open()) {
        return false;
    }

    return true;
}

bool Database::initializeDatabaseTables() {

    databaseGui.transaction();

    QString queryDatabaseUsersTable = "CREATE TABLE IF NOT EXISTS users (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL)";
    QString queryDatabaseTherapyTable = "CREATE TABLE IF NOT EXISTS therapy (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, session_type TEXT NOT NULL, duration INT NOT NULL, intensity_level INT NOT NULL)";
    QString queryDatabaseTreatmentHistoryTable = "CREATE TABLE IF NOT EXISTS treatmentHistory (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, fk_therapy INT NOT NULL, fk_users INT NOT NULL)";

    QSqlQuery queryTable;
    queryTable.exec(queryDatabaseUsersTable);
    queryTable.exec(queryDatabaseTherapyTable);
    queryTable.exec(queryDatabaseTreatmentHistoryTable);

    return databaseGui.commit();

}

bool Database::initializeDefaultUserRecord() {

    databaseGui.transaction();

    QString queryRecordUser1 = "INSERT INTO users (name) VALUES (Eric)";
    QString queryRecordUser2 = "INSERT INTO users (name) VALUES (Robert)";
    QString queryRecordUser3 = "INSERT INTO users (name) VALUES (Angelina)";
    QString queryRecordUser4 = "INSERT INTO users (name) VALUES (Emma)";

    SqlQuery queryTable;

    queryTable.exec(queryRecordUser1);
    queryTable.exec(queryRecordUser2);
    queryTable.exec(queryRecordUser3);
    queryTable.exec(queryRecordUser4);

    return databaseGui.commit();

}

bool Database::addTherapyRecord(QString session, int intensity, int duration) {

    databaseGui.transaction();

    QString queryRecordTherapy1 = "INSERT INTO therapy (session_type, intensity_level, duration) VALUES (:session, :intensity, :duration)";

    QSqlQuery queryTable;
    queryTable.prepare(queryRecordTherapy1);
    queryTable.bindValue(":session", session);
    queryTable.bindValue(":intensity", intensity);
    queryTable.bindValue(":duration", duration);
    queryTable.exec();

    return databaseGui.commit();

}

bool Database::addTherapyHistoryRecord(int userId, int therapyId) {

    databaseGui.transaction();

    QString queryRecordHistory = "INSERT INTO treatmentHistory (fk_therapy, fk_users) VALUES (:therapy, :users)";

    QSqlQuery queryTable;
    queryTable.prepare(queryRecordHistory);
    queryTable.bindValue(":therapy", therapyId);
    queryTable.bindValue(":users", userId);
    queryTable.exec();

    return databaseGui.commit();

}

bool Database::addUserRecord(QString name) {

    databaseGui.transaction();

    QString queryDatabaseUsersTable = "INSERT INTO users (name) VALUES (:name)";

    QSqlQuery queryTable;
    queryTable.prepare(queryDatabaseUsersTable);
    queryTable.bindValue(":name", name);
    queryTable.exec();

    return databaseGui.commit();

}
