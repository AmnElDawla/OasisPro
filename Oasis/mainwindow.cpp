#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // device off's icons
    QString arrQListAbove[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};
    QString arrQListBelow[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    qDebug() << "Starting database initialization...";

    int success = 0;

    if(!newDatabase->initializeDatabase())  {
        qDebug() << "Unable to initialize the database...";
        success = 1;
    }
    else {
        qDebug() << "Created database...";
        success = 0;
    }

    if(!newDatabase->initializeDatabaseTables()) {
        qDebug() << "Unable to create the database's tables (users, therapy, therapy_history)...";
        success = 1;
    }
    else {
        qDebug() << "Created the database's tables (users, therapy, therapy_history)...";
        success = 0;
    }

    if(success == 0) {
        qDebug() << "Operation was successfully completed...";
        qDebug() << "Testing: Getting users details...";
        newDatabase->getUserData(1);
        newDatabase->getUserData(2);
        newDatabase->getUserData(3);
        qDebug() << "Operation was successfully completed...";
    }
    else {
        qDebug() << "Operation was not successfully completed...";
    }

    // Everything needs start in off state (power off) in the GUI
    deviceOff();
    offConnect();
    initialiazeListOfIcons();

    setWindowIcon(QIcon(":/resources/icons/companyIcon.png"));

}

MainWindow::~MainWindow()
{

    delete ui;

}

//============================================================================//
//                             Helper Functions                               //
//============================================================================//

// Keep buttons lit on while removing the highlighting of any single button
void MainWindow::resetButtons() {
    ui->ledEight->setStyleSheet("#ledEight { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ui->ledThree->setStyleSheet("#ledThree { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ui->ledTwo->setStyleSheet("#ledTwo { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ui->ledOne->setStyleSheet("#ledOne { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
}

// Flash the current selected intensity level for 3 seconds
void MainWindow::flashSelectedLevel(){
    resetButtons();

    if(sessionArray[2] == 1){
        ui->ledOne->setStyleSheet("#ledOne { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: #5ced73; border:2px solid rgb(255, 255, 255); }");
    }
    else if(sessionArray[2] == 2){
        ui->ledTwo->setStyleSheet("#ledTwo { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: #5ced73; border:2px solid rgb(255, 255, 255); }");
    }
    else if(sessionArray[2] == 3){
        ui->ledThree->setStyleSheet("#ledThree { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: #5ced73; border:2px solid rgb(255, 255, 255); }");
    }
    else if(sessionArray[2] == 4){
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: rgb(255, 255, 0); border:2px solid rgb(255, 255, 255); }");
    }
    else if(sessionArray[2] == 5){
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: rgb(255, 255, 0); border:2px solid rgb(255, 255, 255); }");
    }
    else if(sessionArray[2] == 6){
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: rgb(255, 255, 0); border:2px solid rgb(255, 255, 255); }");
    }
    else if(sessionArray[2] == 7){
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: #FF7e82; border:2px solid rgb(255, 255, 255); }");
    }
    else if(sessionArray[2] == 8){
        ui->ledEight->setStyleSheet("#ledEight { background-color: transparent; font-weight: 600; color: white; background-repeat: none; background: #FF7e82; border:2px solid rgb(255, 255, 255); }");
    }
}



//============================================================================//
//                             Button Functionality                           //
//============================================================================//

void MainWindow::on_powerBtn_clicked()
{

    // Change color of lights, enable/disable buttons.

    // Clicked power button once...
    if(numberOfTimesPowerBtnClicked == 0) {

        deviceOn();
        numberOfTimesPowerBtnClicked = 1;

    }

    // Clicked power button for the second time...
    else if(numberOfTimesPowerBtnClicked == 1) {

        onConnect();
        iconsOn();
        numberOfTimesPowerBtnClicked = 2;

    }

    // Clicked power button for the third time...
    else {

        deviceOff();
        iconsOff();
        offConnect();
        numberOfTimesPowerBtnClicked = 0;

    }

}

void MainWindow::onConnect() {

    ui->graphSession->setStyleSheet("#graphSession { border-image: url(:/resources/icons/connect.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->leftEar->setStyleSheet("#leftEar { border-image: url(:/resources/icons/LeftEar_Connected.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->rightEar->setStyleSheet("#rightEar { border-image: url(:/resources/icons/rightConnectOn.PNG); border: 2px solid red; border-radius: 20px; }");

}

void MainWindow::offConnect() {

    ui->leftEar->setStyleSheet("#leftEar { border-image: url(:/resources/icons/LeftEar_Off.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->graphSession->setStyleSheet("#graphSession { border-image: url(:/resources/icons/connectOff.png); border: 2px solid red; border-radius: 20px; }");
    ui->rightEar->setStyleSheet("#rightEar { border-image: url(:/resources/icons/rightConnect.PNG); border: 2px solid red; border-radius: 20px; }");

}

void MainWindow::deviceOff() {

    ui->groupBox_10->setStyleSheet("#groupBox_10 { border: 5px solid white; border-radius: 30px; background-color: black; } ");
    ui->indicatorOffOrOn->setStyleSheet("#indicatorOffOrOn::chunk{ background-color: white; }");
    ui->ledEight->setStyleSheet("#ledEight { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->ledSeven->setStyleSheet("#ledSeven { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->ledSix->setStyleSheet("#ledSix { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->ledFive->setStyleSheet("#ledFive { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->ledFour->setStyleSheet("#ledFour { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->ledThree->setStyleSheet("#ledThree { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->ledTwo->setStyleSheet("#ledTwo { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->ledOne->setStyleSheet("#ledOne { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->selectionBtn->setEnabled(false);
    ui->increaseIntensityBtn->setEnabled(false);
    ui->decreaseIntensityBtn->setEnabled(false);

}

void MainWindow::deviceOn() {

    ui->indicatorOffOrOn->setStyleSheet("#indicatorOffOrOn::chunk { background-color: #01fe00; }");
    resetButtons();
    ui->selectionBtn->setEnabled(true);
    ui->increaseIntensityBtn->setEnabled(true);
    ui->decreaseIntensityBtn->setEnabled(true);

}

void MainWindow::iconsOn() {

    //on icons
    ui->groupBox_10->setStyleSheet("#groupBox_10 { border: 5px solid limegreen; border-radius: 30px; background-color: black; } ");

    QString arrQListDurationOn[3] = {":/resources/icons/20MinuteOn.png", ":/resources/icons/45MinuteOn.png", ":/resources/icons/UserDesignatedOn.png"};
    QString arrQListSessionOn[4] = {":/resources/icons/AlphaOn.png", ":/resources/icons/Beta1On.png", ":/resources/icons/Beta2On.png", ":/resources/icons/ThetaOn.png"};

    ui->listDuration->setIconSize(QSize(48, 48));
    ui->listSession->setIconSize(QSize(48, 48));

    for(int i = 0; i < 3; i++)  {

        ui->listDuration->item(i)->setIcon(QIcon(arrQListDurationOn[i]));

    }

    for(int i = 0; i < 4; i++)  {

        ui->listSession->item(i)->setIcon(QIcon(arrQListSessionOn[i]));

    }

}

void MainWindow::iconsOff() {

    //off icons
    QString arrQListDuration[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};
    QString arrQListSession[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    ui->listDuration->setIconSize(QSize(48, 48));
    ui->listSession->setIconSize(QSize(48, 48));

    for(int i = 0; i < 3; i++)  {

        ui->listDuration->item(i)->setIcon(QIcon(arrQListDuration[i]));

    }

    for(int i = 0; i < 4; i++)  {

        ui->listSession->item(i)->setIcon(QIcon(arrQListSession[i]));

    }

}

void MainWindow::initialiazeListOfIcons() {

    QString arrQListDuration[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};
    QString arrQListSession[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    //QList (above) initialize starts here...
    ui->listDuration->setFlow(QListView::Flow::LeftToRight);
    ui->listDuration->setIconSize(QSize(48, 48));
    ui->listDuration->setStyleSheet("#listDuration { background: black; }");

    for(int i = 0; i < 3; i++)  {

        ui->listDuration->addItem(new QListWidgetItem(QIcon(arrQListDuration[i]), NULL));

    }

    ui->listDuration->setCurrentRow(0);

    //QList (below) initialize starts here...
    ui->listSession->setFlow(QListView::Flow::LeftToRight);
    ui->listSession->setIconSize(QSize(48, 48));
    ui->listSession->setStyleSheet("#listSession { background: black; }");

    for(int i = 0; i < 4; i++)  {

        ui->listSession->addItem(new QListWidgetItem(QIcon(arrQListSession[i]), NULL));

    }

    ui->listSession->setCurrentRow(0);

}

// Goes left from the first QlistDuration of icons.
void MainWindow::on_durationLeft_clicked()
{
    if(newRowItemDuration == 0) {
        newRowItemDuration = 2;
    }
    else if(newRowItemDuration == 1) {
        newRowItemDuration = 0;
    }
    else {
        newRowItemDuration = 1;
    }
    ui->listDuration->setCurrentRow(newRowItemDuration);
}

// Goes left from the second QlistDuration of icons.
void MainWindow::on_sessionLeft_clicked()
{
    if(newRowItemSession == 0) {
        newRowItemSession = 3;
    }
    else if(newRowItemSession == 1) {
        newRowItemSession = 0;
    }
    else if(newRowItemSession == 2) {
        newRowItemSession = 1;
    }
    else {
        newRowItemSession = 2;
    }
    ui->listSession->setCurrentRow(newRowItemSession);
}

// Goes right from the first QlistDuration of icons.
void MainWindow::on_durationRight_clicked()
{
    if(newRowItemDuration == 0) {
        newRowItemDuration = 1;
    }
    else if(newRowItemDuration == 1) {
        newRowItemDuration = 2;
    }
    else {
        newRowItemDuration = 0;
    }
    ui->listDuration->setCurrentRow(newRowItemDuration);
}

// Goes right from the second QlistDuration of icons.
void MainWindow::on_sessionRight_clicked()
{
    if(newRowItemSession == 0) {
        newRowItemSession = 1;
    }
    else if(newRowItemSession == 1) {
        newRowItemSession = 2;
    }
    else if(newRowItemSession == 2) {
        newRowItemSession = 3;
    }
    else {
        newRowItemSession = 0;
    }
    ui->listSession->setCurrentRow(newRowItemSession);
}

void MainWindow::batteryLevel(int sessionDuration) {

}

void MainWindow::on_selectionBtn_clicked()
{
    // ADD CODE TO DISABLE BUTTON WHEN WE HAVE A WAY
    // TO KEEP TRACK OF THE NUMBER OF TIMES THE POWER
    // BUTTON HAS BEEN PRESSED

    selectedDuration = newRowItemDuration;
    selectedSession = newRowItemSession;

    sessionArray[0] = selectedDuration;
    sessionArray[1] = selectedSession;
    sessionArray[2] = 0;
}

void MainWindow::on_increaseIntensityBtn_clicked()
{
    // Don't increase intensity level beyond 8
    if(sessionArray[2] < 8){
        sessionArray[2]++;
    }

    flashSelectedLevel();
}

void MainWindow::on_decreaseIntensityBtn_clicked()
{
    // Don't decrease intensity level beyond 0
    if(sessionArray[2] > 0){
        sessionArray[2]--;
    }

    flashSelectedLevel();
}
