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

    QString queryDatabaseUsersTable = "CREATE TABLE IF NOT EXISTS users (pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, joined DATE NOT NULL, age INT NOT NULL, birth_date TEXT NOT NULL, username TEXT NOT NULL UNIQUE)";
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

    QString queryRecordUser = "INSERT INTO users (name, joined, age, birth_date, username) VALUES (Bot, )";

    //QSqlQuery queryTable;
    //queryTable.exec(queryDatabaseUsersTable);

    return databaseGui.commit();

}

bool Database::addTherapyRecord() {

    databaseGui.transaction();

    QString queryRecordTherapy = "";

    //QSqlQuery queryTable;
    //queryTable.exec(queryDatabaseUsersTable);

    return databaseGui.commit();

}

bool Database::addTherapyHistoryRecord() {

    databaseGui.transaction();

    QString queryRecordHistory = "";

    //QSqlQuery queryTable;
    //queryTable.exec(queryDatabaseUsersTable);

    return databaseGui.commit();

}

bool Database::addUserRecord() {

    databaseGui.transaction();

    QString queryDatabaseUsersTable = "";

    QSqlQuery queryTable;
    queryTable.exec(queryDatabaseUsersTable);

    return databaseGui.commit();

}
