// Including the necessary header files (.h files) and libraries (qDebug) to this .cpp file.
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Device off's icons for duration and sessions.
    QString arrQListAbove[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};
    QString arrQListBelow[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    qDebug() << "Starting database initialization...";

    // Creates a success variable to see if the database has successfully started certain components without errors.
    // - success = 0 =====> success (no errors).
    // - success = 1 =====> not successfully (errors were encountered).
    int success = 0;

    // Checks if the database was not initialize.
    if(!newDatabase->initializeDatabase())  {
        qDebug() << "Unable to initialize the database...";

        // Set success variable to 1 (not successful - errors found).
        success = 1;
    }
    else {
        qDebug() << "Created database...";

        // Set success variable to 0 (success - no errors found).
        success = 0;
    }

    // Checks if the database tables were not initialized.
    if(!newDatabase->initializeDatabaseTables()) {
        qDebug() << "Unable to create the database's tables (users, therapy, therapy_history)...";

        // Set success variable to 1 (not successful - errors found).
        success = 1;
    }
    else {
        qDebug() << "Created the database's tables (users, therapy, therapy_history)...";

        // Set success variable to 0 (success - no errors found).
        success = 0;
    }

    // Checks if the success variable is equal to 0 (if it is then that means that it was able to
    // to successfully initialize the table and database).
    if(success == 0) {
        qDebug() << "Operation was successfully completed...";
        qDebug() << "Testing: Getting users details...";

        // Testing if it can retrieve user data.
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

    // Set application icon.
    setWindowIcon(QIcon(":/resources/icons/companyIcon.png"));

    // Initialize and set parameters and connections of the necessary timers.
    batteryStartTimer = new QTimer(this);
    batteryStopTimer = new QTimer(this);
    batteryDegradationTimer = new QTimer(this);
    connect(batteryStartTimer, SIGNAL(timeout()), this, SLOT(showBatteryLevel()));
    connect(batteryStopTimer, SIGNAL(timeout()), this, SLOT(stopBatteryLevel()));
    batteryStopTimer->setSingleShot(true);
    connect(batteryDegradationTimer, SIGNAL(timeout()), this, SLOT(degradeBattery()));

    // When connection test passed do the following.
    connectionTestStartTimer = new QTimer(this);
    connectionTestStopTimer = new QTimer(this);
    connectionTestStopTimer->setSingleShot(true);

}

// This is the destructor function. When the application is close, it will delete ui pointer (to prevent memory leaks).
MainWindow::~MainWindow()
{

    // Delete pointer named ui.
    delete ui;

}

//============================================================================//
//                             Helper Functions                               //
//============================================================================//

// This function keeps the LEDs on while removing the highlighting of any single LED.
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

// This function flashes the current selected intensity level for 3 seconds
void MainWindow::flashSelectedLevel(){

    // Turn on all LEDs and set their respective boolean values to true.
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

    // Check that battery level is not equal to or below 12%.
    if(batteryLevel <= 12){
        // Start the necessary timers.
        batteryStartTimer->start(500);
        batteryStopTimer->start(2500);
        qDebug() << "Battery level critically low. Please replace the battery.";
        // Exit loop.
        return;
    }

    // Change color of lights, enable/disable buttons.

    // Clicked power button once...
    // Turns on the device, but not completely (icons for both duration and session, CES graph, and left and right ear.
    if(numberOfTimesPowerBtnClicked == 0) {

        // Disable all buttons.
        ui->powerBtn->setEnabled(false);
        ui->selectionBtn->setEnabled(false);
        ui->increaseIntensityBtn->setEnabled(false);
        ui->decreaseIntensityBtn->setEnabled(false);
        ui->sessionRight->setEnabled(false);
        ui->sessionLeft->setEnabled(false);
        ui->durationRight->setEnabled(false);
        ui->durationLeft->setEnabled(false);

        // Allow battery to degrade.
        degradeBatteryAllowed = true;

        // Turn the device / application partly on.
        deviceOn();

        // Start the necessary timers.
        batteryStartTimer->start(500);
        batteryStopTimer->start(2500);

        // Set the number of clicks to 1.
        numberOfTimesPowerBtnClicked = 1;

        qDebug() << "Device is partly turned on...";

    }

    // Clicked power button for the second time...
    // This turns the device completely on (everything is turned on).
    else if(numberOfTimesPowerBtnClicked == 1) {

        // Fully turn on the device / application.
        onConnect();
        iconsOn();

        // Start the necessary timers.
        connectionTestStartTimer->start(500);
        connectionTestStopTimer->start(3500);

        // Set the number of clicks to 2.
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

        // Set the text in time elapsed section back to default.
        ui->TimeElapse->setText("0s");

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

    // Style groupbox border to white (this signifies that it has been turned off).
    ui->groupBox_10->setStyleSheet("#groupBox_10 { border: 5px solid white; border-radius: 30px; background-color: black; } ");

    // Style progress bar background color to white (this signifies that it has been turned off).
    ui->indicatorOffOrOn->setStyleSheet("#indicatorOffOrOn::chunk{ background-color: white; }");

    // Turn off all LEDs.
    ledEightOff();
    ledSevenOff();
    ledSixOff();
    ledFiveOff();
    ledFourOff();
    ledThreeOff();
    ledTwoOff();
    ledOneOff();

    // Disable buttons.
    ui->selectionBtn->setEnabled(false);
    ui->increaseIntensityBtn->setEnabled(false);
    ui->decreaseIntensityBtn->setEnabled(false);

    // Clear selected options in listDuration and listSession.
    ui->listDuration->selectionModel()->clear();
    ui->listSession->selectionModel()->clear();

    // Disable buttons.
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

    // Turns the groupbox (the groupbox that will contain the right and left ear icon) on (by changing its border
    // to limegreen).
    ui->groupBox_10->setStyleSheet("#groupBox_10 { border: 5px solid limegreen; border-radius: 30px; background-color: black; } ");

    // Initializes and set the values of the array that will contain the path of the images for the duration icons
    // (these images will the on version).
    QString arrQListDurationOn[3] = {":/resources/icons/20MinuteOn.png", ":/resources/icons/45MinuteOn.png", ":/resources/icons/UserDesignatedOn.png"};

    // Initializes and set the values of the array that will contain the path of the images for the sessions icons
    // (these images will the on version).
    QString arrQListSessionOn[4] = {":/resources/icons/AlphaOn.png", ":/resources/icons/Beta1On.png", ":/resources/icons/Beta2On.png", ":/resources/icons/ThetaOn.png"};

    // Set the icon size for both list to be 48 pixels by 48 pixels.
    ui->listDuration->setIconSize(QSize(48, 48));
    ui->listSession->setIconSize(QSize(48, 48));

    // Loop through all items in the arrQListDuration array and set the icon in the listDuration QListWidget displayed on
    // the GUI to the corresponding item found at the specified index in the arrQListDuration array.
    for(int i = 0; i < 3; i++)  {

        ui->listDuration->item(i)->setIcon(QIcon(arrQListDurationOn[i]));

    }

    // Loop through all items in the arrQListSession array and set the icon in the listSession QListWidget displayed on
    // the GUI to the corresponding item found at the specified index in the arrQListSession array.
    for(int i = 0; i < 4; i++)  {

        ui->listSession->item(i)->setIcon(QIcon(arrQListSessionOn[i]));

    }

    // Set default values and enables buttons.
    ui->listDuration->setCurrentRow(newRowItemDuration);
    ui->listSession->setCurrentRow(newRowItemSession);

    // Set the text (the time left section) in GUI for the current session
    // (that is currently selected (or stored in database) or if not selected then go for default option).
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

    // Set the text (for the time elapse section - this section just display how much time is left until end of session)
    // in GUI for the current session (that is currently selected (or stored in database) or if not selected then go for default option).
    if(newRowItemDuration == 0) {
        ui->TimeElapse->setText("20s");
    }
    else if(newRowItemDuration == 1) {
        ui->TimeElapse->setText("45s");
    }
    else {
        ui->TimeElapse->setText("0s");
    }

    // Set the styling of the listDuration and listSession's borders.
    ui->listDuration->setStyleSheet("#listDuration::item:selected { background: transparent; border: 2px solid yellow; } #listDuration { background: black; } #listDuration::item { border: 2px solid transparent; padding-left: 3px; padding-right: 6px; }");
    ui->listSession->setStyleSheet("#listSession::item:selected { background: transparent; border: 2px solid yellow; } #listSession { background: black; } #listSession::item { border: 2px solid transparent; padding-left: 3px; padding-right: 6px; }");

    // Enables buttons.
    ui->sessionRight->setEnabled(true);
    ui->sessionLeft->setEnabled(true);
    ui->durationRight->setEnabled(true);
    ui->durationLeft->setEnabled(true);
    ui->selectionBtn->setEnabled(true);

    qDebug() << "Start the 2 minutes timer...";

    // Start timer to check if user has not click selection button after 2 minutes.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(turnOffNoSessionSelected()));
    timer->start(120000);

    // Reset LEDs (turn them all on).
    resetButtons();

    // Call this function to start to find the current session number based on the database data
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

    // Initializes and set the values of the array that will contain the path of the images for the duration icons
    // (these images will the off version).
    QString arrQListDuration[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};

    // Initializes and set the values of the array that will contain the path of the images for the sessions icons
    // (these images will the off version).
    QString arrQListSession[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    // Set the icon size for both list to be 48 pixels by 48 pixels.
    ui->listDuration->setIconSize(QSize(48, 48));
    ui->listSession->setIconSize(QSize(48, 48));

    // Loop through all items in the arrQListDuration array and set the icon in the listDuration QListWidget displayed on
    // the GUI to the corresponding item found at the specified index in the arrQListDuration array.
    for(int i = 0; i < 3; i++)  {

        ui->listDuration->item(i)->setIcon(QIcon(arrQListDuration[i]));

    }

    // Loop through all items in the arrQListSession array and set the icon in the listSession QListWidget displayed on
    // the GUI to the corresponding item found at the specified index in the arrQListSession array.
    for(int i = 0; i < 4; i++)  {

        ui->listSession->item(i)->setIcon(QIcon(arrQListSession[i]));

    }

}

// This function initializes the icons for the duration and session as well as sets the parameters for
// the QListWidget that will contains the duration and session icons.
void MainWindow::initialiazeListOfIcons() {

    // Initializes and set the values of the array that will contain the path of the images for the duration icons.
    QString arrQListDuration[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};

    // Initializes and set the values of the array that will contain the path of the images for the sessions icons.
    QString arrQListSession[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    // QList (above) for duration initializes starts here...
    ui->listDuration->setFlow(QListView::Flow::LeftToRight);
    ui->listDuration->setIconSize(QSize(48, 48));
    ui->listDuration->setStyleSheet("#listDuration { background: black; }");

    // Loop through all items in the arrQListDuration array and add these items to the listDuration QListWidgetItem to display them on
    // the GUI.
    for(int i = 0; i < 3; i++)  {

        ui->listDuration->addItem(new QListWidgetItem(QIcon(arrQListDuration[i]), NULL));

    }

    // QList (below) for session initializes starts here...
    ui->listSession->setFlow(QListView::Flow::LeftToRight);
    ui->listSession->setIconSize(QSize(48, 48));
    ui->listSession->setStyleSheet("#listSession { background: black; }");

    // Loop through all items in the arrQListSession array and add these items to the listSession QListWidgetItem to display them on
    // the GUI.
    for(int i = 0; i < 4; i++)  {

        ui->listSession->addItem(new QListWidgetItem(QIcon(arrQListSession[i]), NULL));

    }

    // Style the look for the QListWidget named listDuration and listSession on the GUI.
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
        customDuration = QInputDialog::getInt(this, "Custom Duration", "Enter duration:");
        // Old version:
        // QString str = QInputDialog::getInt(this, "Custom Duration", "");
        // customDuration = str.toInt();

        // Show the custom duration in the UI.
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
        customDuration = QInputDialog::getInt(this, "Custom Duration", "Enter duration:");
        // Old version:
        // QString str = QInputDialog::getInt(this, "Custom Duration", "");
        // customDuration = str.toInt();

        // Show the custom duration in the UI.
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

// Toggle graph LEDs to display battery level.
void MainWindow::showBatteryLevel() {

    // Checks if the battery level is greater than 87%.
    if(batteryLevel > 87) {

        // Turn on all LEDs.
        toggleLedEight();
        toggleLedSeven();
        toggleLedSix();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    }

    // Checks if the battery level is greater than 75%, but less than or equal to 87%.
    else if(batteryLevel <= 87 && batteryLevel > 75) {

        // Turn off all LEDs except the first, second, third, fourth, fifth, sixth, and seventh LED.
        ledEightOff();
        toggleLedSeven();
        toggleLedSix();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    }

    // Checks if the battery level is greater than 62%, but less than or equal to 75%.
    else if(batteryLevel <= 75 && batteryLevel > 62) {

        // Turn off all LEDs except the first, second, third, fourth, fifth, and sixth LED.
        ledEightOff();
        ledSevenOff();
        toggleLedSix();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    }

    // Checks if the battery level is greater than 50%, but less than or equal to 62%.
    else if(batteryLevel <= 62 && batteryLevel > 50) {

        // Turn off all LEDs except the first, second, third, fourth, and fifth LED.
        ledEightOff();
        ledSevenOff();
        ledSixOff();
        toggleLedFive();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    }

    // Checks if the battery level is greater than 37%, but less than or equal to 50%.
    else if(batteryLevel <= 50 && batteryLevel > 37) {

        // Turn off all LEDs except the first, second, third, and fourth LED.
        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        toggleLedFour();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    }

    // Checks if the battery level is greater than 25%, but less than or equal to 37%.
    else if(batteryLevel <= 37 && batteryLevel > 25) {

        // Turn off all LEDs except the first, second, and third LED.
        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        ledFourOff();
        toggleLedThree();
        toggleLedTwo();
        toggleLedOne();

    }

    // Checks if the battery level is greater than 12%, but less than or equal to 25%.
    else if(batteryLevel <= 25 && batteryLevel > 12) {

        // Turn off all LEDs except the first and second LED.
        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        ledFourOff();
        ledThreeOff();
        toggleLedTwo();
        toggleLedOne();

    }

    // Checks if the battery level is greater than 0%, but less than or equal to 12%.
    else if(batteryLevel <= 12 && batteryLevel > 0) {

        // Turn off all LEDs except the first LED.
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

// Reset all LEDs.
void MainWindow::stopBatteryLevel() {

    // Stop the timers.
    batteryStartTimer->stop();

    if(batteryLevel <= 12){
        // Turn off all LEDs.
        ledEightOff();
        ledSevenOff();
        ledSixOff();
        ledFiveOff();
        ledFourOff();
        ledThreeOff();
        ledTwoOff();
        ledOneOff();
    } else {
        // Turn on all LEDs.
        ledEightOn();
        ledSevenOn();
        ledSixOn();
        ledFiveOn();
        ledFourOn();
        ledThreeOn();
        ledTwoOn();
        ledOneOn();
    }

    // Enable the power button.
    ui->powerBtn->setEnabled(true);

}

// Degrade the battery.
void MainWindow::degradeBattery(){
    // Calculate degradation.
    int degRate = 50 + objData.sessionArray[2] * 3;
    batteryLevelEnlarged = batteryLevelEnlarged - degRate;
    qDebug("New Battery Percentage is %d.%d%.", batteryLevelEnlarged / 100, batteryLevelEnlarged % 100);
    // Adjust battery level to new level.
    batteryLevel = batteryLevelEnlarged / 100;
    // Display battery.
    batteryStartTimer->start(500);
    batteryStopTimer->start(2500);
    // Check if battery level is critical. If it is, shut down device.
    if(batteryLevel <= 12){
        degradeBatteryAllowed = false;
        on_powerBtn_clicked();
    }
}

// This function is called when the user has pressed the selection button.
// It disables the selection button and checks if the QTimer named timer is active (still running) and turns it
// off if it is (this QTimer is the one that check if the user has selected a session and duration within 2 minutes
// (120000 miliseconds). Then, it stores the session and duration values in an array called sessionArray.
// After this, it flashes the selected session's intensity for 3 seconds (3000 miliseconds) at an interval of 500 miliseconds.
void MainWindow::on_selectionBtn_clicked()
{

    // Checks if the custom duration value is 0 seconds and if the choosen newRowItemDuration (meaning the duration type that the
    // user has choosen - either 20 seconds, 45 seconds, or custom timer) is equal to 2, which is the custom time.
    if((customDuration == 0 || customDuration < 0) && newRowItemDuration == 2) {

        // If it is then, display that the custom time cannot be 0 seconds long
        // (as this does not make sense to have as a session duration).
        qDebug() << "Custom duration cannot be 0 seconds or less long...";

    }
    else {

        // Set the corresponding variables to false or true.

        // Set this variable to true as a session type was indeed selected.
        selectedSessionOrNot = true;

        // Set this variable to false as the flashing of the selected session number has yet to start (has not started).
        finishedFlashing = false;

        // Disable the selection button.
        ui->selectionBtn->setDisabled(true);

        // Check if the timer is not equal to nullptr and it the timeEnded variable is equal to false.
        // This timer is the one that keeps track if the user has not responded (has not clicked on the selection button)
        // after 2 minutes (120000 miliseconds).
        if(timer != nullptr && timerEnded == false) {

            // If this timer is still active then do the following.
            if(timer->isActive()) {

                // Stop the timer.
                timer->stop();

                // Delete the timer.
                delete timer;

                // Set the timer value to nullptr.
                timer = nullptr;

                // Set the timerEnded variable to false as the timer has ended (has been deleted).
                timerEnded = true;

                qDebug() << "Stopping timer...";

            }

        }

        // Reset the counter to 0.
        valueIntUntilEndOfFlash = 0;

        // Set the selected duration and session values to the corresponding variables.
        selectedDuration = newRowItemDuration;
        selectedSession = newRowItemSession;

        // Set the duration in the session array index to be equal to the selectedDuration variable value.
        objData.sessionArray[0] = selectedDuration;

        // If the selectedDuration variable value is equal to 2 (that means that the custom time was choosen).
        if(selectedDuration == 2) {

            // Set the duration in the session array index to be equal to the customDuration variable value.
            objData.sessionArray[0] = customDuration;
        }

        // Set the session in the session array index to be equal to the selectedSession variable value.
        objData.sessionArray[1] = selectedSession;

        // By default set intensity value to 0.
        objData.sessionArray[2] = 0;

        // Call the function flashSelectedLevelAfterSelection to flash the selected session number.
        flashSelectedLevelAfterSelection();

    }

}

// This function starts the QTimer named timerFlashes to flash the selected session's intensity at a 500 miliseconds (half a second)
// interval.
void MainWindow::flashSelectedLevelAfterSelection() {

    // Initializes the timer.
    timerFlashes = new QTimer(this);

    // Set the interval of the timer (when it will timeout) to every 500 miliseconds (half a second).
    timerFlashes->setInterval(500);

    // Connect the timer's timeout to the slot function name flashTimer (it will call this slot function whenever the
    // timer timeout).
    connect(timerFlashes, SIGNAL(timeout()), this, SLOT(flashTimer()));

    // Start the timer.
    timerFlashes->start();

}

// This function flashes the selected session's intensity based on the QTimer named timerFlashes.
// It does this for 3 seconds. After 3 seconds, it stops the timer, resets the counter named valueIntUntilEndOfFlash
// that keeps track of the amount of time this function has been called and starts the 5 seconds delay by calling
// the delay5Seconds function.
// REMEMBER:
// - sessionArray[0]: Stores duration of the session
// - sessionArray[1]: Stores session type
// - sessionArray[2]: Stores intensity level of the session at the time of completion
void MainWindow::flashTimer() {

    // Checks if the wet/dry combobox has not been pressed (changeWetOrDry = false) and
    // if the device / application is fully turned on.
    if(changeWetOrDry == false && numberOfTimesPowerBtnClicked == 2) {

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 0 and
        // if the fifth LED boolean variable is true (meaning the LED is off and now needs to be turned on).
        if(objData.sessionArray[1] == 0 && ledFiveFlash == true){

            // Turn on the LED (make the border's color red).
            ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: yellow; border: 3px solid red; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is off (as the variable is equal to false).
            ledFiveFlash = false;

        }

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 0 and
        // if the fifth LED boolean variable is false (meaning the LED is on and now needs to be turned off).
        else if(objData.sessionArray[1] == 0 && ledFiveFlash == false){

            // Turn off the LED (make the border's color cyan).
            ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is on (as the variable is equal to true).
            ledFiveFlash = true;

        }

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 1 and
        // if the sixth LED boolean variable is true (meaning the LED is off and now needs to be turned on).
        else if(objData.sessionArray[1] == 1 && ledSixFlash == true){

            // Turn on the LED (make the border's color red).
            ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: yellow; border: 3px solid red; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is off (as the variable is equal to false).
            ledSixFlash = false;

        }

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 1 and
        // if the sixth LED boolean variable is false (meaning the LED is on and now needs to be turned off).
        else if(objData.sessionArray[1] == 1 && ledSixFlash == false){

            // Turn on the LED (make the border's color cyan).
            ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: yellow; border: 3px solid cyan; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is on (as the variable is equal to true).
            ledSixFlash = true;

        }

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 2 and
        // if the seventh LED boolean variable is true (meaning the LED is off and now needs to be turned on).
        else if(objData.sessionArray[1] == 2 && ledSevenFlash == true){

            // Turn on the LED (make the border's color red).
            ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: #FF7e82; border: 3px solid red; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is off (as the variable is equal to false).
            ledSevenFlash = false;

        }

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 2 and
        // if the seventh LED boolean variable is false (meaning the LED is on and now needs to be turned off).
        else if(objData.sessionArray[1] == 2 && ledSevenFlash == false){

            // Turn on the LED (make the border's color cyan).
            ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; border: 3px solid cyan; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is on (as the variable is equal to true).
            ledSevenFlash = true;

        }

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 3 and
        // if the fourth LED boolean variable is true (meaning the LED is off and now needs to be turned on).
        else if(objData.sessionArray[1] == 3 && ledFourFlash == true){

            // Turn on the LED (make the border's color red).
            ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: red; background-repeat: none; background: rgb(255, 255, 0); border: 3px solid red; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is off (as the variable is equal to false).
            ledFourFlash = false;

        }

        // Checks if the sessionArray value at index 1 (which is in this case the session type) is equal to 3 and
        // if the fourth LED boolean variable is false (meaning the LED is on and now needs to be turned off).
        else if(objData.sessionArray[1] == 3 && ledFourFlash == false){

            // Turn on the LED (make the border's color cyan).
            ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); ; border: 3px solid cyan; }");

            // This boolean variable keeps track of what the next state of the LED is.
            // In this case the next state is on (as the variable is equal to true).
            ledFourFlash = true;

        }

        // Checks if the counter is equal to 10 (as the LED can only flash on and off five times).
        if(valueIntUntilEndOfFlash == 10) {

            // Stops the timer.
            timerFlashes->stop();

            // Reset the counter to 0.
            valueIntUntilEndOfFlash = 0;

            // Set the flashing boolean value (the one that check if the flashing of the LED is finished) to true.
            // This is needed to prevent the LED to light up when it is no longer needed (in other words to prevent
            // bugs).
            finishedFlashing = true;

            // Call the 5 seconds delay function to start the 5 seconds delay (before the connection test starts).
            delay5Seconds();

        }
        else {

            // Increment counter by 1.
            valueIntUntilEndOfFlash++;

        }

    }

}

// This function start the fiveSecondsDelay timer (this timer is a single shot one).
void MainWindow::delay5Seconds() {

    qDebug() << "Start 5 seconds delay...";

    // Initializes the timer.
    fiveSecondsDelay = new QTimer(this);

    // Set the timer interval to 5 seconds (5000 miliseconds).
    fiveSecondsDelay->setInterval(5000);

    // Set the timer to single shot. This means that the timer will end when it timeout (it will still call the slot function, but
    // it will no longer continue after that).
    fiveSecondsDelay->setSingleShot(true);

    // Connect the timer's timeout to the slot function name continueAfter5Seconds (it will call this slot function whenever the
    // timer timeout).
    connect(fiveSecondsDelay, SIGNAL(timeout()), this, SLOT(continueAfter5Seconds()));

    // Start the timer.
    fiveSecondsDelay->start();

}

// After the 5 seconds have been finished, this function will then call the connection test function.
void MainWindow::continueAfter5Seconds() {

    qDebug() << "5 seconds delay over...";

    // Checks if the connection test does not finish properly (unsuccessful).
    if(connectionTestMain() != -1) {

        qDebug() << "Connection test has unsuccessfully finished...";

    }
    else  {

        qDebug() << "Connection test has successfully finished...";

    }

}

// This function completely turns off the device if the user does not select a session after 2 minutes (120000
// miliseconds).
void MainWindow::turnOffNoSessionSelected() {

    // Checks if timer is still active.
    if(timer->isActive()) {

        // If it is then stop the timer.
        timer->stop();

    }

    qDebug() << "Shut down OasisPro...";

    // Proceeds to turn off device.
    deviceOff();
    iconsOff();
    offConnect();

    // Reset this variable that counts the number of time the power button has been clicked to 0.
    // When this variable is set to 0, then it means that the device is off (turned off).
    numberOfTimesPowerBtnClicked = 0;

}

// This function is called when the increase intensity button (arrow up) is pressed by the user.
void MainWindow::on_increaseIntensityBtn_clicked()
{

    // qDebug() << "Intensity level is "+QString::number(objData.sessionArray[2]);

    // Don't increase intensity level beyond 8
    if(objData.sessionArray[2] < 8){

        // Increment the intensity value.
        objData.sessionArray[2]++;

    }

    // Call this function to show what intensity value is currently selected.
    flashSelectedLevel();

}

// This function is called when the decrease intensity button (arrow down) is pressed by the user.
void MainWindow::on_decreaseIntensityBtn_clicked()
{

    // qDebug() << "Intensity level is "+QString::number(objData.sessionArray[2]);

    // Don't decrease intensity level beyond 0
    // If we set objData.sessionArray[2] > 0 instead of objData.sessionArray[2] > 1, then the user will never be able
    // to select intensity value 1.
    if(objData.sessionArray[2] > 1){

        // Decrement the intensity value.
        objData.sessionArray[2]--;

    }

    // Call this function to show what intensity value is currently selected.
    flashSelectedLevel();

}

//============================================================================//
//                            LED Control Functions                           //
//============================================================================//

// This function turns off the 1st LED and set the boolean variable named ledOneStatus to false (meaning it is off).
void MainWindow::ledOneOff(){

    ui->ledOne->setStyleSheet("#ledOne { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledOneStatus = false;

}

// This function turns off the 2nd LED and set the boolean variable named ledTwoStatus to false (meaning it is off).
void MainWindow::ledTwoOff(){

    ui->ledTwo->setStyleSheet("#ledTwo { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledTwoStatus = false;

}

// This function turns off the 3rd LED and set the boolean variable named ledThreeStatus to false (meaning it is off).
void MainWindow::ledThreeOff(){

    ui->ledThree->setStyleSheet("#ledThree { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledThreeStatus = false;

}

// This function turns off the 4th LED and set the boolean variable named ledFourStatus to false (meaning it is off).
void MainWindow::ledFourOff(){

    ui->ledFour->setStyleSheet("#ledFour { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledFourStatus = false;

}

// This function turns off the 5th LED and set the boolean variable named ledFiveStatus to false (meaning it is off).
void MainWindow::ledFiveOff(){
    ui->ledFive->setStyleSheet("#ledFive { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledFiveStatus = false;
}

// This function turns off the 6th LED and set the boolean variable named ledSixStatus to false (meaning it is off).
void MainWindow::ledSixOff(){

    ui->ledSix->setStyleSheet("#ledSix { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledSixStatus = false;

}

// This function turns off the 7th LED and set the boolean variable named ledSevenStatus to false (meaning it is off).
void MainWindow::ledSevenOff(){

    ui->ledSeven->setStyleSheet("#ledSeven { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledSevenStatus = false;

}

// This function turns off the 8th LED and set the boolean variable named ledEightStatus to false (meaning it is off).
void MainWindow::ledEightOff(){

    ui->ledEight->setStyleSheet("#ledEight { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ledEightStatus = false;
}

// This function turns on the 1st LED and set the boolean variable named ledOneStatus to true (meaning it is on).
void MainWindow::ledOneOn(){

    ui->ledOne->setStyleSheet("#ledOne { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledOneStatus = true;

}

// This function turns on the 2nd LED and set the boolean variable named ledTwoStatus to true (meaning it is on).
void MainWindow::ledTwoOn(){

    ui->ledTwo->setStyleSheet("#ledTwo { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledTwoStatus = true;

}

// This function turns on the 3rd LED and set the boolean variable named ledThreeStatus to true (meaning it is on).
void MainWindow::ledThreeOn(){

    ui->ledThree->setStyleSheet("#ledThree { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ledThreeStatus = true;

}

// This function turns on the 4th LED and set the boolean variable named ledFourStatus to true (meaning it is on).
void MainWindow::ledFourOn(){

    ui->ledFour->setStyleSheet("#ledFour { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledFourStatus = true;

}

// This function turns on the 5th LED and set the boolean variable named ledFiveStatus to true (meaning it is on).
void MainWindow::ledFiveOn(){

    ui->ledFive->setStyleSheet("#ledFive { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledFiveStatus = true;

}

// This function turns on the 6th LED and set the boolean variable named ledSixStatus to true (meaning it is on).
void MainWindow::ledSixOn(){

    ui->ledSix->setStyleSheet("#ledSix { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ledSixStatus = true;

}

// This function turns on the 7th LED and set the boolean variable named ledSevenStatus to true (meaning it is on).
void MainWindow::ledSevenOn(){

    ui->ledSeven->setStyleSheet("#ledSeven { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ledSevenStatus = true;

}

// This function turns on the 8th LED and set the boolean variable named ledEightStatus to true (meaning it is on).
void MainWindow::ledEightOn(){

    ui->ledEight->setStyleSheet("#ledEight { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ledEightStatus = true;
}

// This function toggles the 1st LED on or off.
void MainWindow::toggleLedOne(){

    if(ledOneStatus == false){
        ledOneOn();
    } else if(ledOneStatus == true){
        ledOneOff();
    }

}

// This function toggles the 2nd LED on or off.
void MainWindow::toggleLedTwo(){

    if(ledTwoStatus == false){
        ledTwoOn();
    } else if(ledTwoStatus == true){
        ledTwoOff();
    }

}

// This function toggles the 3rd LED on or off.
void MainWindow::toggleLedThree(){

    if(ledThreeStatus == false){
        ledThreeOn();
    } else if(ledThreeStatus == true){
        ledThreeOff();
    }

}

// This function toggles the 4th LED on or off.
void MainWindow::toggleLedFour(){

    if(ledFourStatus == false){
        ledFourOn();
    } else if(ledFourStatus == true){
        ledFourOff();
    }

}

// This function toggles the 5th LED on or off.
void MainWindow::toggleLedFive(){

    if(ledFiveStatus == false){
        ledFiveOn();
    } else if(ledFiveStatus == true){
        ledFiveOff();
    }

}

// This function toggles the 6th LED on or off.
void MainWindow::toggleLedSix(){

    if(ledSixStatus == false){
        ledSixOn();
    } else if(ledSixStatus == true){
        ledSixOff();
    }

}

// This function toggles the 7th LED on or off.
void MainWindow::toggleLedSeven(){

    if(ledSevenStatus == false){
        ledSevenOn();
    } else if(ledSevenStatus == true){
        ledSevenOff();
    }

}

// This function toggles the 8th LED on or off.
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
// graphSessionStatus = false ====> means turn off CES Mode light.
// graphSessionStatus = true  ====> means turn on CES Mode light.
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

// This function creates, sets, and start the timer that will flashes the CES Mode light for 3 seconds
void MainWindow::flashCesModeLight()
{

    // Checks if the timer is equal to nullptr, if the device or application is turned on, and if the combobox has not
    // been pressed or changed.
    if(timerCES == nullptr && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {

        // Initializes timer.
        timerCES = new QTimer(this);

        // Set the timer's interval to every 500 miliseconds (at 500 miliseconds the device will timeout).
        timerCES->setInterval(500);

        // Connect the timer's timeout to the slot function name flashGraphCounter (it will call this slot function whenever the
        // timer timeout).
        connect(timerCES, SIGNAL(timeout()), this, SLOT(flashGraphCounter()));

        // Start the timer.
        timerCES->start();
    }

}

// This function is the one toggles the light of the graph (CES Mode Light) from on to off or off to on.
void MainWindow::flashGraphCounter() {

    // Checks if the counter is equal to 6.
    // The CES mode light cannot be blinked more than 5 times.
    if(counterFlashGraph == 6) {

        // Stop the timer.
        timerCES->stop();

        // Delete the timer.
        delete timerCES;

        // Set the timer to nullptr.
        timerCES = nullptr;

        // Reset the counter to 0.
        counterFlashGraph = 0;

        // Check if the device is connected or not and set the CES Mode light to on or off based on that.
        // Disconnected ====> CES Mode light off.
        // Connected    ====> CES Mode light on.
        if(connectivity == false) {
            graphSessionOff();
        }
        else {
            graphSessionOn();
        }

        // Call this function to display the type of connection.
        // The connection is either green, yellow, or red.
        displayConnection(signal);

    }
    // Else if the counter is not equal to 6 then do the following.
    else {

        // Blink the CES Mode lights again.
        toggleCesModeLight();

        // Increment the counter by 1.
        counterFlashGraph++;

    }

}

// This function changes the status of the connection of the device from connected to connected.
// - connectivity = false ====> means disconnected.
// - connectivity = true  ====> means connected.
void MainWindow::onConnectivity()
{

    connectivity = true;

}

// This function changes the status of the connection of the device from connected to disconnected.
// - connectivity = false ====> means disconnected.
// - connectivity = true  ====> means connected.
void MainWindow::offConnectivity()
{

    connectivity = false;

}

// Set elements in graph to blanked status
// This function turns off all 8 LEDs.
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
// This function turns on all 8 LEDs.
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


// This function start the timer that will call the function everytime it timeout (the called function is the one that
// will blink the LEDs based on the signal (the strength of the connection).
void MainWindow::ledBlinkTimer() {

    // Initializes timer.
    timerBlinkLed = new QTimer(this);

    // Set timer interval to every 500 miliseconds (half a second).
    timerBlinkLed->setInterval(500);

    // Connect the timer's timeout (every 1 seconds) to the function named blinkCounter.
    connect(timerBlinkLed, SIGNAL(timeout()), this, SLOT(blinkCounter()));

    // Start the timer.
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

    // Checks counter's value is equal to 6, if the device / application is fully turned on and if the wet/dry combobox has not been
    // pressed (means that it has not change).
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

            // Not sure if this will be needed or removed.
            // Allocate and add a new history record into the QSQL database
            // Show a message
            // QMessageBox Alert;
            // Alert.setWindowTitle("Add Preferences");
            // Alert.setText("Would you like to create a threapy record for the current user?");
            // Alert.setStandardButtons(QMessageBox::Yes);
            // Alert.addButton(QMessageBox::No);
            // Alert.setDefaultButton(QMessageBox::No);
            // if (Alert.exec() == QMessageBox::Yes)
            // {
            //  int userId = ui->listOfUsers->currentIndex();
            //  userId++;
            //  qDebug() << "Debug: User id: " << userId;
            //  int duration = objData.sessionArray[0];
            //  qDebug() << "Debug: Duration: " << duration;
            //  int sessionType = objData.sessionArray[1];
            //  qDebug() << "Debug: Session type: " << sessionType;
            //  int intensityLevel = objData.sessionArray[2];
            //  qDebug() << "Debug: Intensity level: " << intensityLevel;
            //  TherapyRecord *tr = new TherapyRecord(sessionType, intensityLevel, duration);
            //  newDatabase->addTherapyHistoryRecord(userId, tr);
            //  qDebug() << "Adding a history therapy record into Table historyTreatments in QSQL Database... ";
            //  QString result = tr->stringify();
            //  qDebug() << result;
            //  // delete tr;
            // }
            // else
            // {
            //  // Do something else (cancelled adding action).
            //  qDebug() << "Action adding therapy record has been cancelled. ";
            // };

            // Enable intensity and selection buttons
            ui->increaseIntensityBtn->setEnabled(true);
            ui->decreaseIntensityBtn->setEnabled(true);
            ui->selectionBtn->setEnabled(true);

            // Start session timer based on the duration

            // Duration is 20 seconds.
            if(objData.sessionArray[0] == 0) {

                qDebug() << "Timer will go on for 20s";

                // Initializes 20 seconds timer.
                seconds20Timer = new QTimer(this);

                // Set the timer interval for every 1 second (1000 miliseconds).
                seconds20Timer->setInterval(1000);

                // Connect the timer's timeout (every 1 seconds) to the function named updateUITime20sDisplay.
                connect(seconds20Timer, SIGNAL(timeout()), this, SLOT(updateUITime20sDisplay()));

                // Start the timer.
                seconds20Timer->start();

                // Start the battery degradation timer (ten second intervals).
                if(degradeBatteryAllowed){
                    batteryDegradationTimer->start(10000);
                }

            }

            // Duration is 45 seconds.
            else if(objData.sessionArray[0] == 1) {

                qDebug() << "Timer will go on for 45s";

                // Initializes 45 seconds timer.
                seconds45Timer = new QTimer(this);

                // Set the timer interval for every 1 second (1000 miliseconds).
                seconds45Timer->setInterval(1000);

                // Connect the timer's timeout (every 1 seconds) to the function named updateUITime45sDisplay.
                connect(seconds45Timer, SIGNAL(timeout()), this, SLOT(updateUITime45sDisplay()));

                // Start the timer.
                seconds45Timer->start();

                // Start the battery degradation timer (ten second intervals).
                if(degradeBatteryAllowed){
                    batteryDegradationTimer->start(2000);
                }


            }

            // Duration is based on custom time provided by the user.
            else {

                qDebug().noquote() << "Timer will go on for "+QString::number(objData.sessionArray[0])+"s";

                // Initializes custom time timer.
                customTimer = new QTimer(this);

                // Set the timer interval for every 1 second (1000 miliseconds).
                customTimer->setInterval(1000);

                // Connect the timer's timeout (every 1 seconds) to the function named updateUITimeCustomDisplay.
                connect(customTimer, SIGNAL(timeout()), this, SLOT(updateUITimeCustomDisplay()));

                // Start the timer.
                customTimer->start();

                // Set countdown value (the counter that will keep track of much time is left until session end) equal to the
                // customDuration (the time value in seconds that was defined by the user).
                countdownCustom = customDuration;

                // Start the battery degradation timer (ten second intervals).
                if(degradeBatteryAllowed){
                    batteryDegradationTimer->start(2000);
                }


            }

        }
        // If none of the above is true, then that means that the device / application is turned off.
        else {

            qDebug() << "Device has been turned off. Unable to process with test....";

        }

    }
    else {

        // Increment counter by 1.
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

            // Stopping battery degradation.
            batteryDegradationTimer->stop();
            degradeBatteryAllowed = false;

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

            // Stopping battery degradation.
            batteryDegradationTimer->stop();
            degradeBatteryAllowed = false;

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

            // Stopping battery degradation.
            batteryDegradationTimer->stop();
            degradeBatteryAllowed = false;

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

            // Initializes the timer.
            intensityTimer = new QTimer(this);

            // Set the timer interval (when it will timeout) to 500 miliseconds (half a second)
            intensityTimer->setInterval(500);

            // Connect the timer's timeout to the slot function named swicthLeds.
            connect(intensityTimer, SIGNAL(timeout()), this, SLOT(switchLeds()));

            // Start the timer.
            intensityTimer->start();
        }
        // Checks if the application / device is disconnected, if the device / application is fully turned on,
        // and if the wet/dry combobox has not been pressed.
        else if(connectivity == false && numberOfTimesPowerBtnClicked == 2 && changeWetOrDry == false) {
            qDebug() << "Continue scrolling animation...";

            // Reset counter to 0.
            countSwitch = 0;

            // Restart the timer.
            intensityTimer->start();
        }
        // Checks if the user pressed the wet/dry combobox.
        else if(changeWetOrDry == true) {

            // Set counter to 0.
            countSwitch = 0;
            qDebug() << "Switched stated...";
        }
        else {

            // Set counter to 0.
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

    // Initializes and define parameter for the timer, such as setting the interval to 9 seconds (900 miliseconds).
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

    // Checks if the device is connected, and
    // if the device is fully turned on.
    else if (connectivity == true && numberOfTimesPowerBtnClicked == 2) {

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

    // Set batteryLevel variable back to 100%.
    batteryLevel = 100;
    batteryLevelEnlarged = batteryLevel * 100;

}

// This function only is called when the user press the combobox to connect or disconnect their application / device.
// Once they press it, this function will check if the value has changed, if the device is still turned on, and if there
// is a session currently running. If those conditions are true, it will call the connection test again.If they are false, it
// will check if the device / application is turned off. If it is not turned off, it will assumed that the selection button
// has not been pressed.
void MainWindow::on_listOfSkins_currentIndexChanged(const QString &arg1)
{

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
        qDebug().noquote() << "Unable to switch to "+arg1;
        qDebug() << "Device is not turned on...";
    }
    else {
        qDebug().noquote() << "Unable to switch to "+arg1;
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

    // Checks if the value is wet, if the device / application is fully on, if there is a session currently running
    // and if there is a session currently selected (selected button has been pressed).
    if(ui->listOfSkins->currentIndex() == 0 && numberOfTimesPowerBtnClicked == 2 && sessionOnOrOff == true && selectedSessionOrNot == true) {

        qDebug() << "Changed to wet...";
        changeWetOrDry = true;

        // Check if the 20 seconds timer is not equal to nullptr (if it is equal to nullptr, it means the timer has not been initialized)
        // or started).
        if(seconds20Timer != nullptr) {

            // Stop timer.
            seconds20Timer->stop();

            // Delete timer.
            delete seconds20Timer;

            // Set timer to nullptr.
            seconds20Timer = nullptr;

            // Reset counter to 0.
            countTo20 = 0;

            // Reset countdown value back to 20.
            from20to0 = 20;

            // Reset to default text.
            ui->TimeElapse->setText("20s");
            qDebug() << "Deleted 20s timer...";

        }

        // Check if the 45 seconds timer is not equal to nullptr (if it is equal to nullptr, it means the timer has not been initialized)
        // or started).
        if(seconds45Timer != nullptr) {

            // Stop timer.
            seconds45Timer->stop();

            // Delete timer.
            delete seconds45Timer;

            // Set timer to nullptr.
            seconds45Timer = nullptr;

            // Reset counter to 0.
            countTo45 = 0;

            // Reset countdown value back to 45.
            from45to0 = 45;

            // Reset to default text.
            ui->TimeElapse->setText("45s");
            qDebug() << "Deleted 45s timer...";

        }

        // Check if the custom timer is not equal to nullptr.
        if(customTimer != nullptr) {

            // Stop timer.
            customTimer->stop();

            // Delete timer.
            delete customTimer;

            // Set timer to nullptr.
            customTimer = nullptr;

            // Set countdownCustom equal to the customDuration given by the user (custom time inputted by the user).
            countdownCustom = customDuration;

            // Reset counter to 0.
            customCounter = 0;

            // Reset to default text.
            ui->TimeElapse->setText(QString::number(customDuration)+"s");
            qDebug() << "Deleted custom time timer...";

        }

        // Checks if the timer that is used to blink / flash the LEDs based on their connection is not equal to nullptr.
        // This is to prevent animation from occurring while change in state (wet to dry or dry to wet) is happening.
        if(timerBlinkLed != nullptr) {

            // Stop the timer.
            timerBlinkLed->stop();

            // Delete the timer.
            delete timerBlinkLed;

            // Set the timer to nullptr.
            timerBlinkLed = nullptr;
        }

        // Checks if the timer that is used to blink / flash the CES Mode light on or off is not equal to nullptr.
        // This is to prevent animation from occurring while change in state (wet to dry or dry to wet) is happening.
        if(timerCES != nullptr) {

            // Stop the timer.
            timerCES->stop();

            // Delete the timer.
            delete timerCES;

            // Set timer to nullptr.
            timerCES = nullptr;
        }
        connectionTestMain();

    }
    // Checks if the value is dry, if the device / application is fully on, if there is a session currently running
    // and if there is a session currently selected (selected button has been pressed).
    else if(ui->listOfSkins->currentIndex() == 1 && numberOfTimesPowerBtnClicked == 2 && sessionOnOrOff == true && selectedSessionOrNot == true) {

        qDebug() << "Changed to dry...";
        changeWetOrDry = true;

        // Check if the 20 seconds timer is not equal to nullptr (if it is equal to nullptr, it means the timer has not been initialized)
        // or started).
        if(seconds20Timer != nullptr) {

            // Stop timer.
            seconds20Timer->stop();

            // Delete timer.
            delete seconds20Timer;

            // Set timer to nullptr.
            seconds20Timer = nullptr;

            // Reset counter to 0.
            countTo20 = 0;

            // Reset countdown value back to 20.
            from20to0 = 20;

            // Reset to default text.
            ui->TimeElapse->setText("20s");
            qDebug() << "Deleted 20s timer...";

        }

        // Check if the 45 seconds timer is not equal to nullptr (if it is equal to nullptr, it means the timer has not been initialized)
        // or started).
        if(seconds45Timer != nullptr) {

            // Stop timer.
            seconds45Timer->stop();

            // Delete timer.
            delete seconds45Timer;

            // Set timer to nullptr.
            seconds45Timer = nullptr;

            // Reset counter to 0.
            countTo45 = 0;

            // Reset countdown value back to 45.
            from45to0 = 45;

            // Reset to default text.
            ui->TimeElapse->setText("45s");
            qDebug() << "Deleted 45s timer...";

        }

        // Check if the custom timer is not equal to nullptr.
        if(customTimer != nullptr) {

            // Stop timer.
            customTimer->stop();

            // Delete timer.
            delete customTimer;

            // Set timer to nullptr.
            customTimer = nullptr;

            // Set countdownCustom equal to the customDuration given by the user (custom time inputted by the user).
            countdownCustom = customDuration;

            // Reset counter to 0.
            customCounter = 0;

            // Reset to default text.
            ui->TimeElapse->setText(QString::number(customDuration)+"s");
            qDebug() << "Deleted custom time timer...";

        }

        // Checks if the timer that is used to blink / flash the LEDs based on their connection is not equal to nullptr.
        // This is to prevent animation from occurring while change in state (wet to dry or dry to wet) is happening.
        if(timerBlinkLed != nullptr) {

            // Stop the timer.
            timerBlinkLed->stop();

            // Delete the timer.
            delete timerBlinkLed;

            // Set the timer to nullptr.
            timerBlinkLed = nullptr;
        }

        // Checks if the timer that is used to blink / flash the CES Mode light on or off is not equal to nullptr.
        // This is to prevent animation from occurring while change in state (wet to dry or dry to wet) is happening.
        if(timerCES != nullptr) {

            // Stop the timer.
            timerCES->stop();

            // Delete the timer.
            delete timerCES;

            // Set timer to nullptr.
            timerCES = nullptr;
        }
        connectionTestMain();

    }
    // Checks if the device / application is turned off.
    else if(numberOfTimesPowerBtnClicked == 0){
        qDebug() << "Device is not turned on...";
    }
    // Checks if there is no session currently running.
    else if(sessionOnOrOff == false) {
        qDebug().noquote() << "Unable to switch to "+arg1;
        qDebug() << "Device is disconnected or no session was selected...";
    }
    else {
        qDebug().noquote() << "Unable to switch to "+arg1;
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

            // Set the text in time elapsed section back to default.
            ui->TimeElapse->setText("0s");

            qDebug() << "Device is turned off...";

        }

    }
    else {

        // Increment the counter by 1.
        countSwitchDescent++;
    }

}
