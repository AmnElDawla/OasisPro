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

    batteryStartTimer = new QTimer(this);
    batteryStopTimer = new QTimer(this);
    connect(batteryStartTimer, SIGNAL(timeout()), this, SLOT(showBatteryLevel()));
    connect(batteryStopTimer, SIGNAL(timeout()), this, SLOT(stopBatteryLevel()));
    batteryStopTimer->setSingleShot(true);

    // When connection test passed:
    connectionTestStartTimer = new QTimer(this);
    connectionTestStopTimer = new QTimer(this);
    // ANDRE AND MENGRUI, YOU MADE A MISTAKE HERE. THIS IS REPEATING MY CODE FROM LINE 58 AND 59 AND BROKE THE FLASHING MECHANIC.
    // I LEFT THIS HERE COMMENTED INSTEAD OF DELETED IN CASE YOU INTENDED TO USE IT FOR SOMETHING ELSE.
    // DELETE THIS COMMENT WHEN YOU SEE THIS AND DO WHAT YOU WANT WITH THE TWO LINES BELOW.
    // connect(batteryStartTimer, SIGNAL(timeout()), this, SLOT(showBatteryLevel()));
    // connect(batteryStopTimer, SIGNAL(timeout()), this, SLOT(stopBatteryLevel()));
    connectionTestStopTimer->setSingleShot(true);

    // Add items to the comboboxes.
    // ui->listWetOrDry->addItem(tr("Wet"));
    // ui->listWetOrDry->addItem(tr("Dry"));

    // ui->listOfSkins->addItem(tr("Connect"));
    // ui->listOfSkins->addItem((tr("Disconnect")));

    // ui->listOfUsers->addItem(tr("User 1"));
    // ui->listOfUsers->addItem(tr("User 2"));
    // ui->listOfUsers->addItem(tr("User 3"));
    // ui->listOfUsers->addItem(tr("User 4"));

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
    ledEightStatus = true;
    ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ledSevenStatus = true;
    ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledSixStatus = true;
    ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledFiveStatus = true;
    ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledFourStatus = true;
    ui->ledThree->setStyleSheet("#ledThree { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledThreeStatus = true;
    ui->ledTwo->setStyleSheet("#ledTwo { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledTwoStatus = true;
    ui->ledOne->setStyleSheet("#ledOne { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledOneStatus = true;
}

// Flash the current selected intensity level for 3 seconds
void MainWindow::flashSelectedLevel(){
    resetButtons();

    if(objData.sessionArray[2] == 1){
        ui->ledOne->setStyleSheet("#ledOne { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; border: 3px solid #008080; }");
    }
    else if(objData.sessionArray[2] == 2){
        ui->ledTwo->setStyleSheet("#ledTwo { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; border: 3px solid #008080; }");
    }
    else if(objData.sessionArray[2] == 3){
        ui->ledThree->setStyleSheet("#ledThree { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; border: 3px solid #008080; }");
    }
    else if(objData.sessionArray[2] == 4){
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); border: 3px solid #008080; }");
    }
    else if(objData.sessionArray[2] == 5){
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); border: 3px solid #008080; }");
    }
    else if(objData.sessionArray[2] == 6){
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); border: 3px solid #008080; }");
    }
    else if(objData.sessionArray[2] == 7){
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid #008080; }");
    }
    else if(objData.sessionArray[2] == 8){
        ui->ledEight->setStyleSheet("#ledEight { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid #008080; }");
    }

}

//============================================================================//
//                             Button Functionality                           //
//============================================================================//

// This function change color of lights and enable/disable buttons based on the number of times the power button
// has been clicked.
// Clicked once = 1 (this is the value of numberOfTimesPowerBtnClicked variable).
// Clicked twice = 2 (this is the value of numberOfTimesPowerBtnClicked variable).
// Clicked thrice (3 times) = 0 (this is the value of numberOfTimesPowerBtnClicked variable).
void MainWindow::on_powerBtn_clicked()
{

    // Change color of lights, enable/disable buttons.

    // Clicked power button once...
    // Turns on the device, but not completely (icons for both duration and session, CES graph, and left and right ear.
    if(numberOfTimesPowerBtnClicked == 0) {

        ui->powerBtn->setEnabled(false);
        ui->selectionBtn->setEnabled(false);
        ui->increaseIntensityBtn->setEnabled(false);
        ui->decreaseIntensityBtn->setEnabled(false);
        ui->sessionRight->setEnabled(false);
        ui->sessionLeft->setEnabled(false);
        ui->durationRight->setEnabled(false);
        ui->durationLeft->setEnabled(false);
        deviceOn();
        batteryStartTimer->start(500);
        batteryStopTimer->start(3500);
        numberOfTimesPowerBtnClicked = 1;

    }

    // Clicked power button for the second time...
    // This turns the device completely on (everything is turned on).
    else if(numberOfTimesPowerBtnClicked == 1) {

        onConnect();
        iconsOn();
        connectionTestStartTimer->start(500);
        connectionTestStopTimer->start(3500);
        numberOfTimesPowerBtnClicked = 2;

    }

    // Clicked power button for the third time...
    // This completely turns off the device (everything is off).
    else {

        offLeds();

        if(timerCES != nullptr) {
            timerCES->stop();
        }
        if(timerFlashes != nullptr) {
            timerFlashes->stop();
        }

        connectionTestMain();
        deviceOff();
        iconsOff();
        offConnect();
        numberOfTimesPowerBtnClicked = 0;

    }

}

// When the device is completely turn on, this function is called to turn on the CES graph, left ear, and right
// ear icons.
void MainWindow::onConnect() {

    ui->graphSession->setStyleSheet("#graphSession { border-image: url(:/resources/icons/connect.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->leftEar->setStyleSheet("#leftEar { border-image: url(:/resources/icons/LeftEar_Connected.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->rightEar->setStyleSheet("#rightEar { border-image: url(:/resources/icons/rightConnectOn.PNG); border: 2px solid red; border-radius: 20px; }");

}

// When the device is completely turn off, this function is called to turn off the CES graph, left ear, and right
// ear icons.
void MainWindow::offConnect() {

    ui->leftEar->setStyleSheet("#leftEar { border-image: url(:/resources/icons/LeftEar_Off.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->graphSession->setStyleSheet("#graphSession { border-image: url(:/resources/icons/connectOff.png); border: 2px solid red; border-radius: 20px; }");
    ui->rightEar->setStyleSheet("#rightEar { border-image: url(:/resources/icons/rightConnect.PNG); border: 2px solid red; border-radius: 20px; }");

}

// When the device is completely turn off, this function is called to turn off all the LEDs (the section in the UI
// where the labels going from 1 to 8 are found), turning off border of where left and right ear are located, changes
// the colors progress bar found on top of the power button to white, disables all the buttons found in the device's UI,
// clears (remove selection) and deselect the session and duration icons.
void MainWindow::deviceOff() {

    ui->groupBox_10->setStyleSheet("#groupBox_10 { border: 5px solid white; border-radius: 30px; background-color: black; } ");
    ui->indicatorOffOrOn->setStyleSheet("#indicatorOffOrOn::chunk{ background-color: white; }");
    ledEightOff();
    ledSevenOff();
    ledSixOff();
    ledFiveOff();
    ledFourOff();
    ledThreeOff();
    ledTwoOff();
    ledOneOff();
    ui->selectionBtn->setEnabled(false);
    ui->increaseIntensityBtn->setEnabled(false);
    ui->decreaseIntensityBtn->setEnabled(false);
    ui->listDuration->selectionModel()->clear();
    ui->listSession->selectionModel()->clear();
    ui->sessionRight->setEnabled(false);
    ui->sessionLeft->setEnabled(false);
    ui->durationRight->setEnabled(false);
    ui->durationLeft->setEnabled(false);

}

// This function is called when the device's turned on for the first time (numberOfTimesPowerBtnClicked variable = 1).
// It changes the color of the progress bar found on top of the power button to green as well as turns on the
// LEDs of the labels going from 1 to 8 (through the resetButtons function).
void MainWindow::deviceOn() {

    ui->indicatorOffOrOn->setStyleSheet("#indicatorOffOrOn::chunk { background-color: #01fe00; }");
    resetButtons();

}

// This function turns on the icons for the duration and session. This occurs when the power button is clicked
// for the second time. It also calls and starts a QTimer called timer to checks if the user does not respond or click the selection
// button for 2 minutes (120000 miliseconds), enables the duration and session's left and right arrows, and
// sets the current selected item in the duration and session's QListWidget.
void MainWindow::iconsOn() {

    // turns the icons on
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

    ui->listDuration->setCurrentRow(newRowItemDuration);
    ui->listSession->setCurrentRow(newRowItemSession);
    ui->listDuration->setStyleSheet("#listDuration::item:selected { background: transparent; border: 2px solid yellow; } #listDuration { background: black; } #listDuration::item { border: 2px solid transparent; padding-left: 3px; padding-right: 6px; }");
    ui->listSession->setStyleSheet("#listSession::item:selected { background: transparent; border: 2px solid yellow; } #listSession { background: black; } #listSession::item { border: 2px solid transparent; padding-left: 3px; padding-right: 6px; }");
    ui->sessionRight->setEnabled(true);
    ui->sessionLeft->setEnabled(true);
    ui->durationRight->setEnabled(true);
    ui->durationLeft->setEnabled(true);
    ui->selectionBtn->setEnabled(true);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(turnOffNoSessionSelected()));
    timer->start(120000);

    resetButtons();
    selectedIntensityAtStart();

}

// This function checks if there is a value for newRowItemSession (which stores the session number that corresponds to an LED).
// - If the newRowItemSession (default) equals to  0 then it select (puts a cyan border around the label) corresponding LED, which
//   is 5.
// - If the newRowItemSession equals to 1 then it select (puts a cyan border around the label) corresponding LED, which
//   is 6.
// - If the newRowItemSession equals to 2 then it select (puts a cyan border around the label) corresponding LED, which
//   is 7.
// - If the newRowItemSession equals to 3 then it select (puts a cyan border around the label) corresponding LED, which
//   is 4.
void MainWindow::selectedIntensityAtStart() {

    if(newRowItemSession == 0) {
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    else if(newRowItemSession == 1) {
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    else if(newRowItemSession == 2) {
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");
    }
    else {
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }

}

// This function is called when the user presses the power button for the third time (to completely turn off the
// device). This turns off all the icons for the duration and session (bringing them back to white).
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

// This function initializes the icons for the duration and session as well as sets the parameters for
// the QListWidget that will contains the duration and session icons.
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

    //QList (below) initialize starts here...
    ui->listSession->setFlow(QListView::Flow::LeftToRight);
    ui->listSession->setIconSize(QSize(48, 48));
    ui->listSession->setStyleSheet("#listSession { background: black; }");

    for(int i = 0; i < 4; i++)  {

        ui->listSession->addItem(new QListWidgetItem(QIcon(arrQListSession[i]), NULL));

    }

    ui->listDuration->setStyleSheet("#listDuration { background: black; } #listDuration::item { background: black; outline: none; border: 2px solid black; padding-left: 3px; padding-right: 6px; }");
    ui->listSession->setStyleSheet("#listSession { background: black; } #listSession::item { background: black; outline: none; border: 2px solid black; padding-left: 3px; padding-right: 6px; }");

}

// This function allows the user to traverse the QListWidget of duration from left to right
// from the first QlistDuration of icons.
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

// This function allows the user to traverse the QListWidget of session from left to right
// from the first QlistSession of icons.
void MainWindow::on_sessionLeft_clicked()
{

    if(newRowItemSession == 0) {
        newRowItemSession = 3;
        resetButtons();
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    else if(newRowItemSession == 1) {
        newRowItemSession = 0;
        resetButtons();
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    else if(newRowItemSession == 2) {
        newRowItemSession = 1;
        resetButtons();
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    else {
        newRowItemSession = 2;
        resetButtons();
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");
    }
    ui->listSession->setCurrentRow(newRowItemSession);

}

// This function allows the user to traverse the QListWidget of duration from right to left
// from the first QlistDuration of icons.
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

// This function allows the user to traverse the QListWidget of session from right to left
// from the first QlistSession of icons.
void MainWindow::on_sessionRight_clicked()
{

    if(newRowItemSession == 0) {
        newRowItemSession = 1;
        resetButtons();
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    else if(newRowItemSession == 1) {
        newRowItemSession = 2;
        resetButtons();
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");
    }
    else if(newRowItemSession == 2) {
        newRowItemSession = 3;
        resetButtons();
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    else {
        newRowItemSession = 0;
        resetButtons();
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
    }
    ui->listSession->setCurrentRow(newRowItemSession);

}

void MainWindow::showBatteryLevel() {

    if(batteryLevel > 87) {

        toggleLedEight();
        toggleLedSeven();
        toggleLedSix();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    } else if(batteryLevel <= 87 && batteryLevel > 75) {

        ledEightOff();
        toggleLedSeven();
        toggleLedSix();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    } else if(batteryLevel <= 75 && batteryLevel > 62) {

        ledEightOff();
        ledSevenOff();
        toggleLedSix();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    } else if(batteryLevel <= 62 && batteryLevel > 50) {

        ledEightOff();
        ledSevenOff();
        ledSixOff();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    } else if(batteryLevel <= 50 && batteryLevel > 37) {

        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    } else if(batteryLevel <= 37 && batteryLevel > 25) {

        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        ledFourOff();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    } else if(batteryLevel <= 25 && batteryLevel > 12) {

        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        ledFourOff();
        ledThreeOff();
        toggleLedTwo();
        toggleLedOne();

    } else if(batteryLevel <= 12 && batteryLevel > 0) {

        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        ledFourOff();
        ledThreeOff();
        ledTwoOff();
        toggleLedOne();

    }

}

void MainWindow::stopBatteryLevel() {

    // stop timer
    batteryStartTimer->stop();
    ledEightOn();
    ledSevenOn();
    ledSixOn();
    ledFiveOn();
    ledFourOn();
    ledThreeOn();
    ledTwoOn();
    ledOneOn();
    ui->powerBtn->setEnabled(true);

}

// This function is called when the user has pressed the selection button.
// It disables the selection button and checks if the QTimer named timer is active (still running) and turns it
// off if it is (this QTimer is the one that check if the user has selected a session and duration within 2 minutes
// (120000 miliseconds). Then, it stores the session and duration values in an array called sessionArray.
// After this, flashes the selected session's intensity for 3 seconds (3000 miliseconds) at an interval of 500 miliseconds.
void MainWindow::on_selectionBtn_clicked()
{
    // ADD CODE TO DISABLE BUTTON WHEN WE HAVE A WAY
    // TO KEEP TRACK OF THE NUMBER OF TIMES THE POWER
    // BUTTON HAS BEEN PRESSED

    ui->selectionBtn->setDisabled(true);

    if(timer->isActive()) {
        timer->stop();
        qDebug() << "Stopping timer...";
    }
    valueIntUntilEndOfFlash = 0;
    selectedSessionOrNot = true;

    selectedDuration = newRowItemDuration;
    selectedSession = newRowItemSession;

    objData.sessionArray[0] = selectedDuration;
    objData.sessionArray[1] = selectedSession;
    objData.sessionArray[2] = 0;

    flashSelectedLevelAfterSelection();

}

// This function starts the QTimer named timerFlashes to flash the selected session's intensity at a 500 miliseconds
// interval.
void MainWindow::flashSelectedLevelAfterSelection() {

    timerFlashes = new QTimer(this);
    timerFlashes->setInterval(500);
    connect(timerFlashes, SIGNAL(timeout()), this, SLOT(flashTimer()));
    timerFlashes->start();

}

// This function flashes the selected session's intensity based on the QTimer named timerFlashes.
// It does this for 3 seconds. After 3 seconds, it stops the timer, resets the counter named valueIntUntilEndOfFlash
// that keeps track of the amount of time this function has been called and starts the 5 seconds delay by calling
// the delay5Seconds function.
void MainWindow::flashTimer() {

    if(objData.sessionArray[1] == 0 && ledFiveFlash == true){
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: yellow; border: 3px solid red; }");
        ledFiveFlash = false;
    }
    else if(objData.sessionArray[1] == 0 && ledFiveFlash == false){
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        ledFiveFlash = true;
    }
    else if(objData.sessionArray[1] == 1 && ledSixFlash == true){
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: yellow; border: 3px solid red; }");
        ledSixFlash = false;
    }
    else if(objData.sessionArray[1] == 1 && ledSixFlash == false){
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        ledSixFlash = true;
    }
    else if(objData.sessionArray[1] == 2 && ledSevenFlash == true){
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: #FF7e82; border: 3px solid red; }");
        ledSevenFlash = false;
    }
    else if(objData.sessionArray[1] == 2 && ledSevenFlash == false){
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");
        ledSevenFlash = true;
    }
    else if(objData.sessionArray[1] == 3 && ledFourFlash == true){
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: rgb(255, 255, 0); border: 3px solid red; }");
        ledFourFlash = false;
    }
    else if(objData.sessionArray[1] == 3 && ledFourFlash == false){
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); ; border: 3px solid cyan; }");
        ledFourFlash = true;
    }
    valueIntUntilEndOfFlash++;
    if(valueIntUntilEndOfFlash == 10) {
        timerFlashes->stop();
        valueIntUntilEndOfFlash = 0;
        delay5Seconds();
    }

}

// This function start the fiveSecondsDelay timer (this timer is a single shot one).
void MainWindow::delay5Seconds() {

    qDebug() << "Start 5 seconds delay...";
    fiveSecondsDelay = new QTimer(this);
    fiveSecondsDelay->setInterval(5000);
    fiveSecondsDelay->setSingleShot(true);
    connect(fiveSecondsDelay, SIGNAL(timeout()), this, SLOT(continueAfter5Seconds()));
    fiveSecondsDelay->start();

}

// After the 5 seconds have been finished, this function will then call the connection test function.
void MainWindow::continueAfter5Seconds() {

    qDebug() << "5 seconds delay over...";
    if(connectionTestMain() != -1) {
        qDebug() << "Start of the connection test...";
    }

}

// This function completely turns off the device if the user does not select a session after 2 minutes (120000
// miliseconds).
void MainWindow::turnOffNoSessionSelected() {

    if(timer->isActive()) {
        timer->stop();
    }
    qDebug() << "Shut down OasisPro...";
    deviceOff();
    iconsOff();
    offConnect();
    numberOfTimesPowerBtnClicked = 0;

}

void MainWindow::on_increaseIntensityBtn_clicked()
{

    // Don't increase intensity level beyond 8
    // qDebug() << "Intensity level is "+QString::number(objData.sessionArray[2]);

    if(objData.sessionArray[2] < 8){
        objData.sessionArray[2]++;
    }

    flashSelectedLevel();

}

void MainWindow::on_decreaseIntensityBtn_clicked()
{

    // qDebug() << "Intensity level is "+QString::number(objData.sessionArray[2]);
    // Don't decrease intensity level beyond 0

    if(objData.sessionArray[2] > 1){
        objData.sessionArray[2]--;
    }

    flashSelectedLevel();

}

//============================================================================//
//                            LED Control Functions                           //
//============================================================================//

void MainWindow::ledOneOff(){

    ui->ledOne->setStyleSheet("#ledOne { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledOneStatus = false;

}

void MainWindow::ledTwoOff(){

    ui->ledTwo->setStyleSheet("#ledTwo { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledTwoStatus = false;

}

void MainWindow::ledThreeOff(){

    ui->ledThree->setStyleSheet("#ledThree { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledThreeStatus = false;

}

void MainWindow::ledFourOff(){

    ui->ledFour->setStyleSheet("#ledFour { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledFourStatus = false;

}

void MainWindow::ledFiveOff(){
    ui->ledFive->setStyleSheet("#ledFive { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledFiveStatus = false;
}

void MainWindow::ledSixOff(){

    ui->ledSix->setStyleSheet("#ledSix { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledSixStatus = false;

}

void MainWindow::ledSevenOff(){

    ui->ledSeven->setStyleSheet("#ledSeven { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledSevenStatus = false;

}

void MainWindow::ledEightOff(){

    ui->ledEight->setStyleSheet("#ledEight { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledEightStatus = false;
}

void MainWindow::ledOneOn(){

    ui->ledOne->setStyleSheet("#ledOne { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledOneStatus = true;

}

void MainWindow::ledTwoOn(){

    ui->ledTwo->setStyleSheet("#ledTwo { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledTwoStatus = true;

}

void MainWindow::ledThreeOn(){

    ui->ledThree->setStyleSheet("#ledThree { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledThreeStatus = true;

}

void MainWindow::ledFourOn(){

    ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledFourStatus = true;

}

void MainWindow::ledFiveOn(){

    ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledFiveStatus = true;

}

void MainWindow::ledSixOn(){

    ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledSixStatus = true;

}

void MainWindow::ledSevenOn(){

    ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ledSevenStatus = true;

}

void MainWindow::ledEightOn(){

    ui->ledEight->setStyleSheet("#ledEight { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ledEightStatus = true;
}

void MainWindow::toggleLedOne(){

    if(ledOneStatus == false){
        ledOneOn();
    } else if(ledOneStatus == true){
        ledOneOff();
    }

}

void MainWindow::toggleLedTwo(){

    if(ledTwoStatus == false){
        ledTwoOn();
    } else if(ledTwoStatus == true){
        ledTwoOff();
    }

}


void MainWindow::toggleLedThree(){

    if(ledThreeStatus == false){
        ledThreeOn();
    } else if(ledThreeStatus == true){
        ledThreeOff();
    }

}

void MainWindow::toggleLedFour(){

    if(ledFourStatus == false){
        ledFourOn();
    } else if(ledFourStatus == true){
        ledFourOff();
    }

}

void MainWindow::toggleLedFive(){

    if(ledFiveStatus == false){
        ledFiveOn();
    } else if(ledFiveStatus == true){
        ledFiveOff();
    }

}

void MainWindow::toggleLedSix(){

    if(ledSixStatus == false){
        ledSixOn();
    } else if(ledSixStatus == true){
        ledSixOff();
    }

}

void MainWindow::toggleLedSeven(){

    if(ledSevenStatus == false){
        ledSevenOn();
    } else if(ledSevenStatus == true){
        ledSevenOff();
    }

}

void MainWindow::toggleLedEight(){

    if(ledEightStatus == false){
        ledEightOn();
    } else if(ledEightStatus == true){
        ledEightOff();
    }

}



//============================================================================//
//                          Connection Test Functions                         //
//============================================================================//

/* UI control of CES mode light */
// This function turn CES graph (CES mode light) on and set the corresponding boolean variable to true.
void MainWindow::graphSessionOn()
{

    ui->graphSession->setStyleSheet("#graphSession { border-image: url(:/resources/icons/connect.PNG); border: 2px solid red; border-radius: 20px; }");
    graphSessionStatus = true;

}

// This function turn CES graph (CES mode light) off and set the corresponding boolean variable to false.
void MainWindow::graphSessionOff()
{

    ui->graphSession->setStyleSheet("#graphSession { border-image: url(:/resources/icons/connectOff.png); border: 2px solid red; border-radius: 20px; }");
    graphSessionStatus = false;

}
// This function turn the left ear icon off.
void MainWindow::offLeftEar() {

    ui->leftEar->setStyleSheet("#leftEar { border-image: url(:/resources/icons/LeftEar_Off.PNG); border: 2px solid red; border-radius: 20px; }");

}

// This function turn the left ear icon on.
void MainWindow::onLeftEar() {

    ui->leftEar->setStyleSheet("#leftEar { border-image: url(:/resources/icons/LeftEar_Connected.PNG); border: 2px solid red; border-radius: 20px; }");

}

// This function turn the right ear icon off.
void MainWindow::offRightEar() {

    ui->rightEar->setStyleSheet("#rightEar { border-image: url(:/resources/icons/rightConnect.PNG); border: 2px solid red; border-radius: 20px; }");

}

// This function turn the right ear icon on.
void MainWindow::onRightEar() {

    ui->rightEar->setStyleSheet("#rightEar { border-image: url(:/resources/icons/rightConnectOn.PNG); border: 2px solid red; border-radius: 20px; }");

}

// This function turns off the group box where the left and right ear are found and change its color to white.
void MainWindow::offGroupBoxEars() {

    ui->groupBox_10->setStyleSheet("#groupBox_10 { border: 5px solid white; border-radius: 30px; background-color: black; } ");

}

// This function turns on the group box where the left and right ear are found.
void MainWindow::onGroupBoxEars() {

    ui->groupBox_10->setStyleSheet("#groupBox_10 { border: 5px solid limegreen; border-radius: 30px; background-color: black; } ");

}


void MainWindow::toggleCesModeLight()
{

    if (graphSessionStatus == false)
    {
        graphSessionOn();
    }
    else if (graphSessionStatus == true)
    {
        graphSessionOff();
    }

}

// This function flashes the CES Mode light for 3 seconds
void MainWindow::flashCesModeLight()
{

    if(timerCES == nullptr) {
        timerCES = new QTimer(this);
        timerCES->setInterval(500);
        connect(timerCES, SIGNAL(timeout()), this, SLOT(flashGraphCounter()));
        timerCES->start();
    }

}

void MainWindow::flashGraphCounter() {

    toggleCesModeLight();
    counterFlashGraph++;
    if(counterFlashGraph == 6) {

        timerCES->stop();
        delete timerCES;
        timerCES = nullptr;

        counterFlashGraph = 0;

        if(connectivity == false) {
            graphSessionOff();
        }
        else {
            graphSessionOn();
        }

        displayConnection(signal);

    }

}

void MainWindow::onConnectivity()
{

    connectivity = true;

}

void MainWindow::offConnectivity()
{

    connectivity = false;

}

/* Set elements in graph to blanked status*/
void MainWindow::offLeds()
{

    ledEightOff();
    ledSevenOff();
    ledSixOff();
    ledFiveOff();
    ledFourOff();
    ledThreeOff();
    ledTwoOff();
    ledOneOff();

}

/* Resume graph display */
void MainWindow::onLeds()
{

    ledEightOn();
    ledSevenOn();
    ledSixOn();
    ledFiveOn();
    ledFourOn();
    ledThreeOn();
    ledTwoOn();
    ledOneOn();

}

void MainWindow::ledBlinkTimer() {

    timerBlinkLed = new QTimer(this);
    timerBlinkLed->setInterval(500);
    connect(timerBlinkLed, SIGNAL(timeout()), this, SLOT(blinkCounter()));
    timerBlinkLed->start();

}

// This function is called when the QTimer named timerBlinked timeout.
// Grp 0 - Blinks LEDs 7 and 8 (no connection)
// Grp 1 - Blinks LEDs 4, 5, and 6 (okay connection)
// Grp 2 - Blinks LEDs 1, 2, and 3 (good or excellent connection)
// counterBlinkingLed - counter that keeps track of how many times the blinkCounter
void MainWindow::blinkCounter() {

    counterBlinkingLed++;
    if(groupToBlink == 0) {

        if(blinkTrueOrFalse == true) {
            ledEightOn();
            ledSevenOn();
            blinkTrueOrFalse = false;
        }
        else {
            ledEightOff();
            ledSevenOff();
            blinkTrueOrFalse = true;
        }

    }
    else if(groupToBlink == 1) {

        if(blinkTrueOrFalse == true) {
            ledSixOn();
            ledFiveOn();
            ledFourOn();
            blinkTrueOrFalse = false;
        }
        else {
            ledSixOff();
            ledFiveOff();
            ledFourOff();
            blinkTrueOrFalse = true;
        }
    }
    else {

        if(blinkTrueOrFalse == true) {
            ledOneOn();
            ledTwoOn();
            ledThreeOn();
            blinkTrueOrFalse = false;
        }
        else {
            ledOneOff();
            ledTwoOff();
            ledThreeOff();
            blinkTrueOrFalse = true;
        }

    }

    if(counterBlinkingLed == 6) {
        timerBlinkLed->stop();
        counterBlinkingLed = 0;

        // Turn on all leds
        onLeds();

        // Finding correct intensity level

        int realValueRow = 0;
        if(newRowItemSession == 0) {
            realValueRow = 3;
        }
        else if(newRowItemSession == 1) {
            realValueRow = 0;
        }
        else if(newRowItemSession == 2) {
            realValueRow = 1;
        }
        else {
            realValueRow = 2;
        }

        // Displaying correct intensity level
        if(realValueRow == 0) {
            ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        }
        else if(realValueRow == 1) {
            ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");
        }
        else if(realValueRow == 2) {
            ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        }
        else {
            ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        }

        if(connectivity == false) {
            playScrollAnimation();
        }
        else {
            // Enable intensity and selection buttons:
            ui->increaseIntensityBtn->setEnabled(true);
            ui->decreaseIntensityBtn->setEnabled(true);
            ui->selectionBtn->setEnabled(true);
        }

    }

}

// Updating connection status on GUI:
void MainWindow::displayConnection(int signal)
{

    offLeds();
    switch (signal)
    {
        case 0:
            // No connection: blink Led Group (7 and 8):
            groupToBlink = 0;
            ledBlinkTimer();
            break;
        case 1:
            // tigger by: dry tesing mode
            // OK connection: blink Led Group (6, 5 and 4):
            groupToBlink = 1;
            ledBlinkTimer();
            break;
        default:
            // triggered by: wet testing mode
            // Excellent connection: blink Led Group (3, 2 and 1):
            groupToBlink = 2;
            ledBlinkTimer();
            break;
    }

}

// Play scroll animation on GUI.
void MainWindow::playScrollAnimation()
{

    qDebug() << "Scrolling animation...";
    // update Qtimer (missing???)
    /* [...] */
    int timeout = 5; // <- subject to change based on Qtimer

    pauseTimer(timeout);

}

// This function manages the scrolling animation by stopping and starting a timer named
// intensity timer at an interval of 500 miliseconds (half a second).
void MainWindow::intervalTimerIntensity() {

    if(countForPauseEnd < valuePause) {
        if(intensityTimer == nullptr) {
            qDebug() << "New intensity timer...";
            intensityTimer = new QTimer(this);
            intensityTimer->setInterval(500);
            connect(intensityTimer, SIGNAL(timeout()), this, SLOT(switchLeds()));
            intensityTimer->start();
        }
        else if(connectivity == false) {
            qDebug() << "Continue scrolling animation...";
            countSwitch = 0;
            intensityTimer->start();
        }
        else {
            countSwitch = 0;
            qDebug() << "Scrolling animation has stopped...";
        }
    }

}

void MainWindow::switchLeds() {

    if(connectivity == false) {
        if(countSwitch == 0) {
            ledOneOn();
        }
        else if(countSwitch == 1) {
            ledOneOff();
        }
        else if(countSwitch == 2) {
            ledTwoOn();
        }
        else if(countSwitch == 3) {
            ledTwoOff();
        }
        else if(countSwitch == 4) {
            ledThreeOn();
        }
        else if(countSwitch == 5) {
            ledThreeOff();
        }
        else if(countSwitch == 6) {
            ledFourOn();
        }
        else if(countSwitch == 7) {
            ledFourOff();
        }
        else if(countSwitch == 8) {
            ledFiveOn();
        }
        else if(countSwitch == 9) {
            ledFiveOff();
        }
        else if(countSwitch == 10) {
            ledSixOn();
        }
        else if(countSwitch == 11) {
            ledSixOff();
        }
        else if(countSwitch == 12) {
            ledSevenOn();
        }
        else if(countSwitch == 13) {
            ledSevenOff();
        }
        else if(countSwitch == 14) {
            ledEightOn();
        }
        else {
            qDebug() << "Last intensity...";
            ledEightOff();
        }

        if(countSwitch == 15) {
            qDebug() << "Stopping timer...";
            countSwitch = 0;
            intensityTimer->stop();
        }
        else {
            countSwitch++;
        }
    }

}

void MainWindow::pauseTimer(int value) {

    offLeds();
    valuePause = value;
    pauseTimerDefault = new QTimer(this);
    pauseTimerDefault->setInterval(9000);
    connect(pauseTimerDefault, SIGNAL(timeout()), this, SLOT(pauseCounter()));
    pauseTimerDefault->start();

}

void MainWindow::pauseCounter() {

    if(countForPauseEnd == valuePause) {
        pauseTimerDefault->stop();
        countForPauseEnd = 0;
        offLeds();
        delete pauseTimerDefault;
        pauseTimerDefault = nullptr;
        qDebug() << "End scrolling animation...";
    }
    else {
        intervalTimerIntensity();
        countForPauseEnd++;
    }

}

/* Main control of connection test
 *** Note: check power level before calling this function ***
 */
int MainWindow::connectionTestMain()
{

    qDebug() << "Connection test started...";

    // Start session
    sessionOnOrOff = true;

    // Define maximum value for safe voltage level:
    int defaultSafeLevel = 4;

    // Disable intensity buttons:
    ui->increaseIntensityBtn->setEnabled(false);
    ui->decreaseIntensityBtn->setEnabled(false);

    // Check if intensity level of the selected session is safe:
    if (objData.sessionArray[2] > defaultSafeLevel) {
        objData.sessionArray[2] = defaultSafeLevel;
    }

    if(ui->listWetOrDry->currentIndex() == 0 && ui->listOfSkins->currentIndex() == 0) {
        signal = 2;
        OptionWet = true;
        OptionDry = false;
        connectivity = true;
    }
    else if(ui->listWetOrDry->currentIndex() == 1 && ui->listOfSkins->currentIndex() == 0) {
        signal = 1;
        OptionDry = true;
        OptionWet = false;
        connectivity = true;
    }
    else {
        signal = 0;
        connectivity = false;
    }

    // a counter to keep track of the waiting process
    int timeNow = 0;
    int timeOut = 20;

    // Check connection
    if (connectivity == false && numberOfTimesPowerBtnClicked == 2) {
        qDebug() << "Device is disconnected...";

        // Disconnect left and right ear
        offLeftEar();
        offRightEar();
        offGroupBoxEars();

        // Update connection status
        signal = 0;

        // Update GUI elements
        flashCesModeLight();

    }

    // Exceptions that will terminate the while loop:
    // 1. low battery level
    // 2. press powerbutton (missing, need add functionality)
    // 3. time is out (> 20 secs)

    else if (connectivity == true && timeNow < timeOut && batteryLevel >= 25 && numberOfTimesPowerBtnClicked == 2){

        qDebug() << "Device is successfully connected...";

        // To make sure scrolling animation is off completely.
        offLeds();

        // Connect right and left ear
        onLeftEar();
        onRightEar();
        onGroupBoxEars();

        // Update GUI elements
        flashCesModeLight();

        // Exit with connection
        qDebug() << "Connection test ended...";

    }

    else if (numberOfTimesPowerBtnClicked == 0 && sessionOnOrOff == true) {

        qDebug() << "Ending session early...";

        // Scrolling down animation - end of session.
        descendEndSession();

        // Set variable to false as there is no active session.
        sessionOnOrOff = false;

        qDebug() << "Session ended...";

    }

    // Exit without connection
    else {

        qDebug() << "Connection test has been terminated ...";

    }

    return -1;

}

void MainWindow::on_newBattery_clicked()
{

    qDebug() << "Battery has been recharged back to 100%...";
    batteryLevel = 100;

}

void MainWindow::on_listOfSkins_currentIndexChanged(const QString &arg1)
{

    if(ui->listOfSkins->currentIndex() == 0 && numberOfTimesPowerBtnClicked == 2) {
        qDebug() << "Connected...";
        connectionTestMain();
    }
    else if(ui->listOfSkins->currentIndex() == 1 && numberOfTimesPowerBtnClicked == 2) {
        qDebug() << "Disconnected...";
        connectionTestMain();
    }
    else {
        qDebug() << "Device is not turned on...";
    }

}

void MainWindow::on_listWetOrDry_currentIndexChanged(const QString &arg1)
{
    if(ui->listOfSkins->currentIndex() == 0 && numberOfTimesPowerBtnClicked == 2) {
        qDebug() << "Changed to wet...";
        connectionTestMain();
    }
    else if(ui->listOfSkins->currentIndex() == 1 && numberOfTimesPowerBtnClicked == 2) {
        qDebug() << "Changed to dry...";
        connectionTestMain();
    }
    else {
        qDebug() << "Device is not turned on...";
    }
}

void MainWindow::descendEndSession() {

    offLeds();
    endSession = new QTimer(this);
    endSession->setInterval(500);
    connect(endSession, SIGNAL(timeout()), this, SLOT(startDescendEndSession()));
    endSession->start();

}

void MainWindow::startDescendEndSession() {

    if(countSwitchDescent == 15) {
        ledOneOn();
    }
    else if(countSwitchDescent == 14) {
        ledOneOff();
    }
    else if(countSwitchDescent == 13) {
        ledTwoOn();
    }
    else if(countSwitchDescent == 12) {
        ledTwoOff();
    }
    else if(countSwitchDescent == 11) {
        ledThreeOn();
    }
    else if(countSwitchDescent == 10) {
        ledThreeOff();
    }
    else if(countSwitchDescent == 9) {
        ledFourOn();
    }
    else if(countSwitchDescent == 8) {
        ledFourOff();
    }
    else if(countSwitchDescent == 7) {
        ledFiveOn();
    }
    else if(countSwitchDescent == 6) {
        ledFiveOff();
    }
    else if(countSwitchDescent == 5) {
        ledSixOn();
    }
    else if(countSwitchDescent == 4) {
        ledSixOff();
    }
    else if(countSwitchDescent == 3) {
        ledSevenOn();
    }
    else if(countSwitchDescent == 2) {
        ledSevenOff();
    }
    else if(countSwitchDescent == 1) {
        ledEightOn();
    }
    else {
        qDebug() << "Arrived at the first intensity...";
        ledEightOff();
    }

    if(countSwitchDescent == 15) {
        qDebug() << "Stopping end session timer...";
        countSwitchDescent = 0;
        endSession->stop();
        delete endSession;
        endSession = nullptr;
    }
    else {
        countSwitchDescent++;
    }

}
