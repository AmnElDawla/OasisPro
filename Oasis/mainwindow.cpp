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

// This function change color of lights and enable/disable buttons based on the number of times the power button has been clicked.
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

        qDebug() << "Device is partly turned on...";

    }

    // Clicked power button for the second time...
    // This turns the device completely on (everything is turned on).
    else if(numberOfTimesPowerBtnClicked == 1) {

        onConnect();
        iconsOn();
        connectionTestStartTimer->start(500);
        connectionTestStopTimer->start(3500);
        numberOfTimesPowerBtnClicked = 2;

        qDebug() << "Device is turned on...";

    }

    // Clicked power button for the third time...
    // This completely turns off the device (everything is off).
    else {

        // Reset number of clicks to 0.
        numberOfTimesPowerBtnClicked = 0;

        // Set selected session boolean variable to false.
        selectedSessionOrNot = false;

        // Turn off all LEDs.
        offLeds();

        // Stop necessary timers.
        if(timerCES != nullptr) {
            timerCES->stop();
            counterFlashGraph = 6;
        }
        if(timerFlashes != nullptr) {
            timerFlashes->stop();
            valueIntUntilEndOfFlash = 10;
        }

        // Restart connection test to end the session.
        connectionTestMain();

        // Turns off the device completely.
        deviceOff();
        iconsOff();
        offConnect();

        // Reset to finished scroll down animation to false.
        finishedScrolledDown = false;

        // Set the text in time left section back to default.
        ui->TimeText->setText("Time Left");

        qDebug() << "Device is turned off...";

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

    // Set default values and enables buttons.
    ui->listDuration->setCurrentRow(newRowItemDuration);
    ui->listSession->setCurrentRow(newRowItemSession);
    if(newRowItemSession == 0) {
        ui->TimeText->setText("Time Left (Alpha)");
    }
    else if(newRowItemSession == 1) {
        ui->TimeText->setText("Time Left (SMR)");
    }
    else if(newRowItemSession == 2) {
        ui->TimeText->setText("Time Left (Beta)");
    }
    else {
        ui->TimeText->setText("Time Left (Theta)");
    }

    if(newRowItemDuration == 0) {
        ui->TimeElapse->setText("20s");
    }
    else if(newRowItemDuration == 1) {
        ui->TimeElapse->setText("45s");
    }
    else {
        ui->TimeElapse->setText("N/A");
    }

    ui->listDuration->setStyleSheet("#listDuration::item:selected { background: transparent; border: 2px solid yellow; } #listDuration { background: black; } #listDuration::item { border: 2px solid transparent; padding-left: 3px; padding-right: 6px; }");
    ui->listSession->setStyleSheet("#listSession::item:selected { background: transparent; border: 2px solid yellow; } #listSession { background: black; } #listSession::item { border: 2px solid transparent; padding-left: 3px; padding-right: 6px; }");
    ui->sessionRight->setEnabled(true);
    ui->sessionLeft->setEnabled(true);
    ui->durationRight->setEnabled(true);
    ui->durationLeft->setEnabled(true);
    ui->selectionBtn->setEnabled(true);

    // Start timer to check if user has not click selection button after 2 minutes.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(turnOffNoSessionSelected()));
    timer->start(120000);

    // Reset buttons and start find the current intensity (that is based on the session number) based on the database data.
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
        ui->listDuration->setCurrentRow(newRowItemDuration);

        // Button index -> actual value of duration
        qDebug() << "Selected custom duration...";

        // Input box for custom time selection (duration).
        QString str = QInputDialog::getText(this, "User-defined Duration (Integer)", "0");
        customDuration = str.toInt();

        ui->TimeElapse->setText(QString::number(customDuration)+"s");
    }
    else if(newRowItemDuration == 1) {
        newRowItemDuration = 0;
        ui->listDuration->setCurrentRow(newRowItemDuration);
        ui->TimeElapse->setText("20s");
    }
    else {
        newRowItemDuration = 1;
        ui->listDuration->setCurrentRow(newRowItemDuration);
        ui->TimeElapse->setText("45s");
    }

}

// This function allows the user to traverse the QListWidget of session from left to right
// from the first QlistSession of icons.
void MainWindow::on_sessionLeft_clicked()
{

    if(newRowItemSession == 0) {
        newRowItemSession = 3;
        resetButtons();
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");

        ui->TimeText->setText("Time Left (Theta)");
    }
    else if(newRowItemSession == 1) {
        newRowItemSession = 0;
        resetButtons();
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        ui->TimeText->setText("Time Left (Alpha)");
    }
    else if(newRowItemSession == 2) {
        newRowItemSession = 1;
        resetButtons();
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        ui->TimeText->setText("Time Left (SMR)");
    }
    else {
        newRowItemSession = 2;
        resetButtons();
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");
        ui->TimeText->setText("Time Left (Beta)");
    }
    ui->listSession->setCurrentRow(newRowItemSession);

}

// This function allows the user to traverse the QListWidget of duration from right to left
// from the first QlistDuration of icons.
void MainWindow::on_durationRight_clicked()
{

    if(newRowItemDuration == 0) {
        newRowItemDuration = 1;
        ui->listDuration->setCurrentRow(newRowItemDuration);
        ui->TimeElapse->setText("45s");
    }
    else if(newRowItemDuration == 1) {
        newRowItemDuration = 2;
        ui->listDuration->setCurrentRow(newRowItemDuration);

        // Button index -> actual value of duration
        qDebug() << "Selected custom duration...";

        // Input box for custom time selection (duration).
        QString str = QInputDialog::getText(this, "User-defined Duration (Integer)", "0");
        customDuration = str.toInt();

        ui->TimeElapse->setText(QString::number(customDuration)+"s");
    }
    else {
        newRowItemDuration = 0;
        ui->listDuration->setCurrentRow(newRowItemDuration);
        ui->TimeElapse->setText("20s");
    }

}

// This function allows the user to traverse the QListWidget of session from right to left
// from the first QlistSession of icons.
void MainWindow::on_sessionRight_clicked()
{

    if(newRowItemSession == 0) {
        newRowItemSession = 1;
        resetButtons();
        ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        ui->TimeText->setText("Time Left (SMR)");
    }
    else if(newRowItemSession == 1) {
        newRowItemSession = 2;
        resetButtons();
        ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");
        ui->TimeText->setText("Time Left (Beta)");
    }
    else if(newRowItemSession == 2) {
        newRowItemSession = 3;
        resetButtons();
        ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        ui->TimeText->setText("Time Left (Theta)");
    }
    else {
        newRowItemSession = 0;
        resetButtons();
        ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");
        ui->TimeText->setText("Time Left (Alpha)");
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

    if(customDuration == 0 && newRowItemDuration == 2) {
        qDebug() << "Custom duration cannot be 0 seconds long...";
    }
    else {
        selectedSessionOrNot = true;
        finishedFlashing = false;

        ui->selectionBtn->setDisabled(true);

        // COMMENT FROM MINGRUI: THIS TIMER WILL TERMINATE THE PROGRAM WHEN CLICKING SELECT BUTTON TWICE
        // (Fixed)
        if(timer != nullptr && timerEnded == false) {
            if(timer->isActive()) {
                timer->stop();
                delete timer;
                timer = nullptr;
                timerEnded = true;
                qDebug() << "Stopping timer...";
            }
        }

        valueIntUntilEndOfFlash = 0;

        selectedDuration = newRowItemDuration;
        selectedSession = newRowItemSession;

        objData.sessionArray[0] = selectedDuration;

        if(selectedDuration == 2) {
            objData.sessionArray[0] = customDuration;
        }

        objData.sessionArray[1] = selectedSession;
        objData.sessionArray[2] = 0;

        flashSelectedLevelAfterSelection();
    }

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

    if(changeWetOrDry == false && numberOfTimesPowerBtnClicked == 2) {
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
        if(valueIntUntilEndOfFlash == 10) {
            timerFlashes->stop();
            valueIntUntilEndOfFlash = 0;
            finishedFlashing = true;
            delay5Seconds();
        }
        else {
            valueIntUntilEndOfFlash++;
        }
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
    // Checks if the connection test does not
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

// Toggle between on or off state of the CES mode light (graph turn on or off).
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

    if(timerCES == nullptr && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {
        timerCES = new QTimer(this);
        timerCES->setInterval(500);
        connect(timerCES, SIGNAL(timeout()), this, SLOT(flashGraphCounter()));
        timerCES->start();
    }

}

void MainWindow::flashGraphCounter() {

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
    else {

        toggleCesModeLight();
        counterFlashGraph++;

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

// Set elements in graph to blanked status
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

// Resume graph display
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

    // Checks if the grpToBlink is equal to 0, if the device / application is fully turned on and if the wet/dry combobox has not been
    // pressed (means that it has not change).
    if(groupToBlink == 0 && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

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

    // Checks if the grpToBlink is equal to 1, if the device / application is fully turned on and if the wet/dry combobox has not been
    // pressed (means that it has not change).
    if(groupToBlink == 1 && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

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

    // Checks if the grpToBlink is equal to 2, if the device / application is fully turned on and if the wet/dry combobox has not been
    // pressed (means that it has not change).
    if(groupToBlink == 2 && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

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

    if(counterBlinkingLed == 6 && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

        // Stop the timer.
        timerBlinkLed->stop();

        // Reset the counter to 0.
        counterBlinkingLed = 0;

        // Turn on all leds
        onLeds();

        // Finding correct session number based on the newRowItemSession value.
        // - newRowItemSession = 0 =====> means that actual session number value is based on the Theta session type.
        // - newRowItemSession = 1 =====> means that actual session number value is based on the Alpha session type.
        // - newRowItemSession = 2 =====> means that actual session number value is based on the SMR session type.
        // - newRowItemSession = 3 =====> means that actual session number value is based on the Beta session type.
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

        // Displaying correct session number.
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

        // After finishing all the tests, it now performs the following functions based on whether the
        // device is connected or not.
        if(connectivity == false && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {
            playScrollAnimation();
        }
        else if(connectivity == true && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

            // Allocate and add a new histroy record into the QSQL database
            // Show a message
            QMessageBox Alert;
            Alert.setWindowTitle("Add Preferences");
            Alert.setText("Would you like to create a threapy record for the current user?");
            Alert.setStandardButtons(QMessageBox::Yes);
            Alert.addButton(QMessageBox::No);
            Alert.setDefaultButton(QMessageBox::No);
            if (Alert.exec() == QMessageBox::Yes)
            {
                int userId = ui->listOfUsers->currentIndex();
                userId++;
                qDebug() << "Debug: User id: " << userId;
                int duration = objData.sessionArray[0];
                qDebug() << "Debug: Duration: " << duration;
                int sessionType = objData.sessionArray[1];
                qDebug() << "Debug: Session type: " << sessionType;
                int intensityLevel = objData.sessionArray[2];
                qDebug() << "Debug: Intensity level: " << intensityLevel;
                TherapyRecord *tr = new TherapyRecord(sessionType, intensityLevel, duration);
                newDatabase->addTherapyHistoryRecord(userId, tr);
                qDebug() << "Adding a history therapy record into Table historyTreatments in QSQL Database... ";
                QString result = tr->stringify();
                qDebug() << result;
                // delete tr;
            }
            else
            {
                // Do something else (cancelled adding action).
                qDebug() << "Action adding therapy record has been cancelled. ";
            };

            // Enable intensity and selection buttons
            ui->increaseIntensityBtn->setEnabled(true);
            ui->decreaseIntensityBtn->setEnabled(true);
            ui->selectionBtn->setEnabled(true);

            // Start session timer based on the duration
            if(objData.sessionArray[0] == 0) {
                qDebug() << "Timer will go on for 20s";
                seconds20Timer = new QTimer(this);
                seconds20Timer->setInterval(1000);
                connect(seconds20Timer, SIGNAL(timeout()), this, SLOT(updateUITime20sDisplay()));
                seconds20Timer->start();
            }
            else if(objData.sessionArray[0] == 1) {
                qDebug() << "Timer will go on for 45s";
                seconds45Timer = new QTimer(this);
                seconds45Timer->setInterval(1000);
                connect(seconds45Timer, SIGNAL(timeout()), this, SLOT(updateUITime45sDisplay()));
                seconds45Timer->start();
            }
            else {
                qDebug().noquote() << "Timer will go on for "+QString::number(objData.sessionArray[0])+"s";
                customTimer = new QTimer(this);
                customTimer->setInterval(1000);
                connect(customTimer, SIGNAL(timeout()), this, SLOT(updateUITimeCustomDisplay()));
                customTimer->start();
                countdownCustom = customDuration;
            }
        }
        else {
            qDebug() << "Device has been turned off. Unable to process with test....";
        }

    }
    else {
        counterBlinkingLed++;
    }

}

// This function updates the time left based on a custom time countdown (if the user chooses the custom duration).
// Once custom time has elapse, it will proceed to shut down the application, reset all counters, and delete timer for
// the custom time countdown named customTimer.
void MainWindow::updateUITimeCustomDisplay() {

    // Checks if application is fully turn on and the wet/dry state has not been changed.
    if(numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

        // If the counter that keeps track of how many times this function has been called is equal to custom duration
        // (given by the user when they selected the custom duration option), then that means that the custom time has
        // elapsed.
        if(customCounter == (customDuration+1)) {

            qDebug().noquote() << QString::number(customDuration)+"s timer finished...";

            // Stopping, deleteing and making timer equal to nullptr;
            customTimer->stop();
            delete customTimer;
            customTimer = nullptr;

            // Resetting counters
            customCounter = 0;
            countdownCustom = 0;

            // Turning all LEDs off.
            offLeds();

            // Only true if the session ends at the time it needs to end (in this case after 20 seconds).
            finishedScrolledDown = true;

            // Scrolling down animation - end of session.
            descendEndSession();

        }
        else {

            // Updates the UI with new time (goes down from custom time (given by user) every 1 second).
            ui->TimeElapse->setText(QString::number(countdownCustom)+"s");

            // Increment counter that counts how many times function has been called.
            customCounter++;

            // Decrements counter that is used to keep track of time left or remaining.
            countdownCustom--;

        }
    }

}


// This function updates the time left based on a 20 seconds countdown (if the user chooses the 20 seconds duration).
// Once 20 seconds has elapse, it will proceed to shut down the application, reset all counters, and delete timer for
// the 20 seconds countdown named seconds20Timer.
void MainWindow::updateUITime20sDisplay() {

    // Checks if application is fully turn on and the wet/dry state has not been changed.
    if(numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

        // If the counter that keeps track of how many times this function has been called is equal to 21, then that means
        // that the 20 seconds has elapsed.
        if(countTo20 == 21) {

            qDebug() << "20s timer finished...";

            // Stopping, deleteing and making timer equal to nullptr;
            seconds20Timer->stop();
            delete seconds20Timer;
            seconds20Timer = nullptr;

            // Resetting counters
            countTo20 = 0;
            from20to0 = 20;

            // Turning all LEDs off.
            offLeds();

            // Only true if the session ends at the time it needs to end (in this case after 20 seconds).
            finishedScrolledDown = true;

            // Scrolling down animation - end of session.
            descendEndSession();

        }
        else {

            // Updates the UI with new time (goes down from 20 seconds every 1 second).
            ui->TimeElapse->setText(QString::number(from20to0)+"s");

            // Increment counter that counts how many times function has been called.
            countTo20++;

            // Decrements counter that is used to keep track of time left or remaining.
            from20to0--;

        }
    }

}

// This function updates the time left based on a 45 seconds countdown (if the user chooses the 45 seconds duration).
// Once 45 seconds has elapse, it will proceed to shut down the application, reset all counters, and delete timer for
// the 45 seconds countdown named seconds45Timer.
void MainWindow::updateUITime45sDisplay() {

    // Checks if application is fully turn on and the wet/dry state has not been changed.
    if(numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

        // If the counter that keeps track of how many times this function has been called is equal to 46, then that means
        // that the 45 seconds has elapsed.
        if(countTo45 == 46) {

            qDebug() << "45s timer finished...";

            // Stopping, deleteing and making timer equal to nullptr;
            seconds45Timer->stop();
            delete seconds45Timer;
            seconds45Timer = nullptr;

            // Resetting counters
            countTo45 = 0;
            from45to0 = 45;

            // Turning all LEDs off.
            offLeds();

            // Only true if the session ends at the time it needs to end (in this case after 45 seconds).
            finishedScrolledDown = true;

            // Scrolling down animation - end of session.
            descendEndSession();

        }
        else {

            // Updates the UI with new time (goes down from 45 seconds every 1 second).
            ui->TimeElapse->setText(QString::number(from45to0)+"s");

            // Increment counter that counts how many times function has been called.
            countTo45++;

            // Decrements counter that is used to keep track of time left or remaining.
            from45to0--;

        }
    }

}

// This function basically takes three signals, which are:
// - Signal = 0 => this signal means that there is no connection (application / device is disconnected - red light
//   will flash - LEDs 7 and 8)
// - Signal = 1 => this signal means that there is an okay connection (yellow light will flash - LEDs 4, 5, and 6)
// - Signal = 2 => this signal means that there is an excellent / good connection - green light will flash - LEDs 1, 2 and 3)
// From the switch case (which is based on signal value), it will decide how to flash the intensity lights (or LEDs) based
// on the given signal (as stated in the bullet points above).
void MainWindow::displayConnection(int signal)
{

    // Turn off all LEDs. Just a precaution in case the LEDs are still on.
    offLeds();

    // Switch case that handles cases based on the signal's value.
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

// This function calls the function(s) that plays the scroll animation on GUI.
void MainWindow::playScrollAnimation()
{

    qDebug() << "Scrolling animation...";

    // Run animation 5 times.
    int timeout = 5;

    // Call QTimer for starting and displaying animation in GUI.
    pauseTimer(timeout);

}

// This function manages the scrolling animation by stopping and starting a timer named
// intensity timer at an interval of 500 miliseconds (half a second).
void MainWindow::intervalTimerIntensity() {

    // Checks if the countForPauseEnd is less than 5 (valuePause is equal to 5).
    // This means that the timer must only time out 5 times and not more.
    if(countForPauseEnd < valuePause) {

        // Checks if the timer is equal to nullptr, if the device / application is fully turned on, and if the
        // wet/dry combobox has not been pressed.
        if(intensityTimer == nullptr && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {
            qDebug() << "New intensity timer...";
            intensityTimer = new QTimer(this);
            intensityTimer->setInterval(500);
            connect(intensityTimer, SIGNAL(timeout()), this, SLOT(switchLeds()));
            intensityTimer->start();
        }
        // Checks if the application / device is disconnected, if the device / application is fully turned on,
        // and if the wet/dry combobox has not been pressed.
        else if(connectivity == false && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {
            qDebug() << "Continue scrolling animation...";
            countSwitch = 0;
            intensityTimer->start();
        }
        // Checks if the user pressed the wet/dry combobox.
        else if(changeWetOrDry == true) {
            countSwitch = 0;
            qDebug() << "Switched stated...";
        }
        else {
            countSwitch = 0;
            qDebug() << "Scrolling animation has stopped...";
        }
    }

}

// This function does the scrolling animation (scrolling up from 1 to 8).
// This only occurs if the device / application's disconnected.
void MainWindow::switchLeds() {

    // First checks if the connectivity is false, the application is fully turned on (numberOfTimesPowerBtnClick is equal
    // to 2 when it is turned on fully, and if the wet/dry combobox has not been changed (or pressed).
    if(connectivity == false && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

        // The scrolling animation based on the value of the countSwitchDescent counter.
        // It either turns on or off a certain LED based on the counter's current value.
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

        // Checks if the counter named countSwitch is equal to 15 (meaning it reached the last LED and should not continue the scrolling animation).
        if(countSwitch == 15) {
            qDebug() << "Stopping timer...";

            // Resets the counter to 0.
            countSwitch = 0;

            // Stops the timer.
            intensityTimer->stop();
        }
        // If the counter is not equal to 15, then increment the counter by 1.
        else {

            // Increments counter by 1.
            countSwitch++;
        }
    }

}

// This function creates, defines, and starts the timer that calls the function that those the scrolling animation,
// which is the function named pauseCounter.
void MainWindow::pauseTimer(int value) {

    // Turn off all LEDs (1 to 8)
    offLeds();

    // Set variable equal to the value
    valuePause = value;

    // Start and define parameter for the timer, such as setting the interval to 9 seconds (900 miliseconds).
    pauseTimerDefault = new QTimer(this);

    // Set the interval of this timer to 9 seconds (9000 miliseconds) meaning that this timer will timeout every 9 seconds.
    pauseTimerDefault->setInterval(9000);

    // Connects the timer's timeout signal to the slot function named pausedCounter.
    // This function will be called at an interval of 9 seconds.
    connect(pauseTimerDefault, SIGNAL(timeout()), this, SLOT(pauseCounter()));

    // Starts the timer.
    pauseTimerDefault->start();

}

// This function is called to start the scrolling animation. It does the animation as long as the counter named countForPaused is
// not equal to the valuePause, which is 5. If it is equal to valuePause, it will proceed to stop the timer, delete it, reset the counter,
// and set the value of the timer to nullptr.
void MainWindow::pauseCounter() {

    // If statement to check if the counter named countForPausedEnd (which keeps track of how times the function has been
    // called. If the counter equals to the valuePause, then stop and delete timer and reset all the counter found in that
    // file (or section of the code base.
    if(countForPauseEnd == valuePause) {

        // Stop timer.
        pauseTimerDefault->stop();

        // Reset counter to 0.
        countForPauseEnd = 0;

        // Turned off all LEDs (1 to 8).
        offLeds();

        // Delete the timer.
        delete pauseTimerDefault;

        // Set the timer to nullptr.
        pauseTimerDefault = nullptr;
        qDebug() << "End scrolling animation...";
    }

    // else statament that is called until the counter named countForPausedEnd is not equal to the valuePause, then
    // increment the counter and star intervalTimerIntensity.
    else {

        // Call this function to start the scrolling animation.
        intervalTimerIntensity();

        // Increment counter by 1.
        countForPauseEnd++;
    }

}

/* Main control of connection test
 *** Note: check power level before calling this function ***
 *** Checks if the application is connected, disconnected and a session ended early.
 *** The session only truly begins after the connection test ends (successfully - meaning the session timer goes to 0
 *** and the session did not end early).
 */
int MainWindow::connectionTestMain()
{

    qDebug() << "Connection test started...";

    // Define maximum value for safe voltage level.
    int defaultSafeLevel = 4;

    // Disable intensity buttons, which are the increase and decrease buttons (up and down arrow buttons).
    ui->increaseIntensityBtn->setEnabled(false);
    ui->decreaseIntensityBtn->setEnabled(false);

    // Check if intensity level of the selected session is safe.
    // If it is greater than the safe value, then set the intensity level to the safe intensity value.
    if (objData.sessionArray[2] > defaultSafeLevel) {
        objData.sessionArray[2] = defaultSafeLevel;
    }

    // Checks if the wet/dry value is equal to wet and that the device is connected.
    if(ui->listWetOrDry->currentIndex() == 0 && ui->listOfSkins->currentIndex() == 0) {
        signal = 2;
        OptionWet = true;
        OptionDry = false;
        connectivity = true;
    }

    // Checks if the wet/dry value is equal to dry and that the device is connected.
    else if(ui->listWetOrDry->currentIndex() == 1 && ui->listOfSkins->currentIndex() == 0) {
        signal = 1;
        OptionDry = true;
        OptionWet = false;
        connectivity = true;
    }

    // This else statement will only be called if the device is disconnected.
    else {
        signal = 0;
        connectivity = false;
    }

    // Exceptions lead to connection test shut down:
    // 1. low battery level
    // 2. press powerbutton (added functionality - working)

    // Check if the connection is false (disconnected) and the application is fully turn on.
    if (connectivity == false && numberOfTimesPowerBtnClicked == 2) {

        qDebug() << "Device is disconnected...";

        // Not connected to session
        sessionOnOrOff = false;

        // Disconnect left and right ear
        offLeftEar();
        offRightEar();
        offGroupBoxEars();

        // Turn off all LEDs
        offLeds();

        // Update connection status
        signal = 0;
        changeWetOrDry = false;

        // Update GUI elements
        flashCesModeLight();

    }

    // Checks if the device is connected, if the battery level is greater or equal to 25, and
    // if the device is fully turned on.
    else if (connectivity == true && batteryLevel >= 25 && numberOfTimesPowerBtnClicked == 2) {

        // Successful scenario: passed connection test
        // Start session
        sessionOnOrOff = true;

        qDebug() << "Device is successfully connected...";

        // To make sure scrolling animation is off completely.
        offLeds();

        //Checks if the device is still turned on.
        if(numberOfTimesPowerBtnClicked == 2) {

            // Connect right and left ear
            onLeftEar();
            onRightEar();
            onGroupBoxEars();

            qDebug() << "Starting connection test with connected device...";

            // Set variable to false as the combobox is no longer being change from dry to wet or vice-versa.
            changeWetOrDry = false;

            // Update GUI elements
            flashCesModeLight();

        }

        // Exit with connection
        qDebug() << "Connection test ended successfully...";

        ui->selectionBtn->setDisabled(false);

    }

    // Checks if device is turned off (that only happens if numberOfTimesPowerBtnClicked == 0), and that there is
    // a session running.
    else if (numberOfTimesPowerBtnClicked == 0 && sessionOnOrOff == true) {


        // Only true if the session ends at the time it needs to end.
        // In this case session ends early.
        finishedScrolledDown = false;

        qDebug() << "Ending session early...";

        // Turning all LEDs off.
        offLeds();

        // Scrolling down animation - end of session.
        descendEndSession();

        // Set variable to false as there is no active session.
        sessionOnOrOff = false;

        qDebug() << "Session ended...";

    }
    else {

        // Exit without connection
        qDebug() << "Connection test has been terminated ...";

    }

    return -1;

}


// This function displays the battery level going back to 100%. It sets the battery level variable to 100.
void MainWindow::on_newBattery_clicked()
{

    qDebug() << "Battery has been recharged back to 100%...";

    // Set batteryLevel varianle back to 100%.
    batteryLevel = 100;

}

// This function only is called when the user press the combobox to connect or disconnect their application / device.
// Once they press it, this function will check if the value has changed, if the device is still turned on, and if there
// is a session currently running. If those conditions are true, it will call the connection test again.If they are false, it
// will check if the device / application is turned off. If it is not turned off, it will assumed that the selection button
// has not been pressed.
void MainWindow::on_listOfSkins_currentIndexChanged(const QString &arg1)
{

    qDebug() << arg1;

    // Checks if the value is connected, if the device / application is fully on, and if there is a session currenly selected (selected button has been pressed).
    if(ui->listOfSkins->currentIndex() == 0 && numberOfTimesPowerBtnClicked == 2 && selectedSessionOrNot == true) {
        qDebug() << "Connected...";

        //If the conditions are true, it reruns the connection test.
        connectionTestMain();
    }
    // Checks if the value is disconnected, if the device / application is fully on, and if there is a session currenly selected (selected button has been pressed).
    else if(ui->listOfSkins->currentIndex() == 1 && numberOfTimesPowerBtnClicked == 2 && selectedSessionOrNot == true) {
        qDebug() << "Disconnected...";

        //If the conditions are true, it reruns the connection test.
        connectionTestMain();
    }
    // Checks if the device is turned off.
    // Remember:
    // - numberOfTimesPowerBtnClicked = 0 ======> means device is fully off (turned off).
    // - numberOfTimesPowerBtnClicked = 1 ======> means device is partly turned on.
    // - numberOfTimesPowerBtnClicked = 2 ======> means device is completely turned on.
    else if(numberOfTimesPowerBtnClicked == 0) {
        qDebug() << "Device is not turned on...";
    }
    else {
        qDebug() << "Selection button has not been pressed...";
    }

}

// This function only is called when the user press the combobox to change state from wet to dry or dry to wet for their application / device.
// Once they press it, this function will check if the value has changed, if the device is still turned on, if there
// is a session currently running, and if there is a session currently selected (selected button has been pressed). If those conditions are true, it will call the connection test again.If they are false, it
// will check if the device / application is turned off. Then, it will check if there is no session currently running.
// If it is not turned off and there is a session currenly running, then it will assumed that the selection button has not been pressed
// (no session has been selected).
void MainWindow::on_listWetOrDry_currentIndexChanged(const QString &arg1)
{

    qDebug() << arg1;

    // Checks if the value is wet, if the device / application is fully on, if there is a session currently running
    // and if there is a session currently selected (selected button has been pressed).
    if(ui->listOfSkins->currentIndex() == 0 && numberOfTimesPowerBtnClicked == 2 && sessionOnOrOff == true && selectedSessionOrNot == true) {
        qDebug() << "Changed to wet...";
        changeWetOrDry = true;
        connectionTestMain();
    }
    // Checks if the value is dry, if the device / application is fully on, if there is a session currently running
    // and if there is a session currently selected (selected button has been pressed).
    else if(ui->listOfSkins->currentIndex() == 1 && numberOfTimesPowerBtnClicked == 2 && sessionOnOrOff == true && selectedSessionOrNot == true) {
        qDebug() << "Changed to dry...";
        changeWetOrDry = true;
        connectionTestMain();
    }
    // Checks if the device / application is turned off.
    else if(numberOfTimesPowerBtnClicked == 0){
        qDebug() << "Device is not turned on...";
    }
    // Checks if there is no session currently running.
    else if(sessionOnOrOff == false) {
        qDebug() << "Device is disconnected or no session was selected...";
    }
    else {
        qDebug() << "Selection button has not been pressed...";
    }

}

// This function initializes the timer that will allow for the descent scrolling animation from 8 to 1 to work.
void MainWindow::descendEndSession() {

    // Turns off all LEDS (1 to 8)
    offLeds();

    // Initializes the timer.
    endSession = new QTimer(this);

    // Sets the timer interval to 500 miliseconds.
    endSession->setInterval(500);

    // Connects the timer's timeout to the slot function named startDescendEndSession().
    // This function is the one that will be called every 500 miliseconds to perform the
    // scrolling down animation.
    connect(endSession, SIGNAL(timeout()), this, SLOT(startDescendEndSession()));

    // Starts the timer.
    endSession->start();

}

// This function is the one that performs the scrolling down animation when a session ends on-time or when the power button is
// clicked for a third time (numberOfTimesPowerBtnClicked = 0, this means the session ended early).
// Notice: countSwitchDescent starts at 0 and increments by 1 everytime this function is called, which is what allows the scrolling
// animation to happen as for each increment, the corresponding LED will be either turned on or off.
void MainWindow::startDescendEndSession() {

    // The scrolling animation based on the value of the countSwitchDescent counter.
    // It either turns on or off a certain LED based on the counter's current value.
    if(countSwitchDescent == 15) {
        ledOneOff();
    }
    else if(countSwitchDescent == 14) {
        ledOneOn();
    }
    else if(countSwitchDescent == 13) {
        ledTwoOff();
    }
    else if(countSwitchDescent == 12) {
        ledTwoOn();
    }
    else if(countSwitchDescent == 11) {
        ledThreeOff();
    }
    else if(countSwitchDescent == 10) {
        ledThreeOn();
    }
    else if(countSwitchDescent == 9) {
        ledFourOff();
    }
    else if(countSwitchDescent == 8) {
        ledFourOn();
    }
    else if(countSwitchDescent == 7) {
        ledFiveOff();
    }
    else if(countSwitchDescent == 6) {
        ledFiveOn();
    }
    else if(countSwitchDescent == 5) {
        ledSixOff();
    }
    else if(countSwitchDescent == 4) {
        ledSixOn();
    }
    else if(countSwitchDescent == 3) {
        ledSevenOff();
    }
    else if(countSwitchDescent == 2) {
        ledSevenOn();
    }
    else if(countSwitchDescent == 1) {
        ledEightOff();
    }
    else {
        qDebug() << "Arrived at the first intensity...";
        ledEightOn();
    }

    // Checks if the countSwitchDescent counter is equal to 15.
    if(countSwitchDescent == 15) {
        qDebug() << "Stopping end session timer...";

        // Counter is reset to 0.
        countSwitchDescent = 0;

        // Timer is stopped.
        endSession->stop();

        // Timer is deleted.
        delete endSession;

        // Timer is value is set to nullptr.
        endSession = nullptr;

        // Checks if the session ended on time (this means that no power button has been pressed).
        if(finishedScrolledDown == true) {

            qDebug() << "Resetting all necessary components before shut down...";

            // Set variable to false as there is no active session.
            sessionOnOrOff = false;

            // Reset number of clicks to 0.
            numberOfTimesPowerBtnClicked = 0;

            // Set selected session boolean variable to false.
            selectedSessionOrNot = false;

            // Stop necessary timers.
            if(timerCES != nullptr) {
                timerCES->stop();
                counterFlashGraph = 6;
            }
            if(timerFlashes != nullptr) {
                timerFlashes->stop();
                valueIntUntilEndOfFlash = 10;
            }

            // Turns off the device completely.
            deviceOff();
            iconsOff();
            offConnect();

            // Reset to finished scroll down animation to false.
            finishedScrolledDown = false;

            // Set the text in time left section back to default.
            ui->TimeText->setText("Time Left");

            qDebug() << "Device is turned off...";

        }

    }
    else {

        // Increment the counter by 1.
        countSwitchDescent++;
    }

}
