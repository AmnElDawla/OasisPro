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

}

MainWindow::~MainWindow()
{

    delete ui;

}


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

    ui->label_16->setStyleSheet("#label_16 { border-image: url(:/resources/icons/connect.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->label_20->setStyleSheet("#label_20 { border-image: url(:/resources/icons/LeftEar_Connected.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->label_21->setStyleSheet("#label_21 { border-image: url(:/resources/icons/rightConnectOn.PNG); border: 2px solid red; border-radius: 20px; }");

}

void MainWindow::offConnect() {

    ui->label_20->setStyleSheet("#label_20 { border-image: url(:/resources/icons/LeftEar_Off.PNG); border: 2px solid red; border-radius: 20px; }");
    ui->label_16->setStyleSheet("#label_16 { border-image: url(:/resources/icons/connectOff.png); border: 2px solid red; border-radius: 20px; }");
    ui->label_21->setStyleSheet("#label_21 { border-image: url(:/resources/icons/rightConnect.PNG); border: 2px solid red; border-radius: 20px; }");

}

void MainWindow::deviceOff() {

    ui->progressBar->setStyleSheet("#progressBar::chunk{ background-color: white; }");
    ui->label_4->setStyleSheet("#label_4 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_6->setStyleSheet("#label_6 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_7->setStyleSheet("#label_7 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_8->setStyleSheet("#label_8 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_9->setStyleSheet("#label_9 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_10->setStyleSheet("#label_10 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_11->setStyleSheet("#label_11 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_12->setStyleSheet("#label_12 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->selectionBtn->setEnabled(false);
    ui->increaseIntensityBtn->setEnabled(false);
    ui->decreaseIntensityBtn->setEnabled(false);

}

void MainWindow::deviceOn() {

    ui->progressBar->setStyleSheet("#progressBar::chunk { background-color: #01fe00; }");
    ui->label_4->setStyleSheet("#label_4 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ui->label_6->setStyleSheet("#label_6 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
    ui->label_7->setStyleSheet("#label_7 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ui->label_8->setStyleSheet("#label_8 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ui->label_9->setStyleSheet("#label_9 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
    ui->label_10->setStyleSheet("#label_10 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ui->label_11->setStyleSheet("#label_11 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ui->label_12->setStyleSheet("#label_12 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
    ui->selectionBtn->setEnabled(true);
    ui->increaseIntensityBtn->setEnabled(true);
    ui->decreaseIntensityBtn->setEnabled(true);

}

void MainWindow::iconsOn() {

    //on icons
    QString arrQListDurationOn[3] = {":/resources/icons/20MinuteOn.png", ":/resources/icons/45MinuteOn.png", ":/resources/icons/UserDesignatedOn.png"};
    QString arrQListSessionOn[4] = {":/resources/icons/AlphaOn.png", ":/resources/icons/Beta1On.png", ":/resources/icons/Beta2On.png", ":/resources/icons/ThetaOn.png"};

    ui->listWidget->setIconSize(QSize(48, 48));
    ui->listWidget_2->setIconSize(QSize(48, 48));

    for(int i = 0; i < 3; i++)  {

        ui->listWidget->item(i)->setIcon(QIcon(arrQListDurationOn[i]));

    }

    for(int i = 0; i < 4; i++)  {

        ui->listWidget_2->item(i)->setIcon(QIcon(arrQListSessionOn[i]));

    }

}

void MainWindow::iconsOff() {

    //off icons
    QString arrQListDuration[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};
    QString arrQListSession[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    ui->listWidget->setIconSize(QSize(48, 48));
    ui->listWidget_2->setIconSize(QSize(48, 48));

    for(int i = 0; i < 3; i++)  {

        ui->listWidget->item(i)->setIcon(QIcon(arrQListDuration[i]));

    }

    for(int i = 0; i < 4; i++)  {

        ui->listWidget_2->item(i)->setIcon(QIcon(arrQListSession[i]));

    }

}

void MainWindow::initialiazeListOfIcons() {

    QString arrQListDuration[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};
    QString arrQListSession[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    //QList (above) initialize starts here...
    ui->listWidget->setFlow(QListView::Flow::LeftToRight);
    ui->listWidget->setIconSize(QSize(48, 48));
    ui->listWidget->setStyleSheet("#listWidget { background: black; }");

    for(int i = 0; i < 3; i++)  {

        ui->listWidget->addItem(new QListWidgetItem(QIcon(arrQListDuration[i]), NULL));

    }

    ui->listWidget->setCurrentRow(0);

    //QList (below) initialize starts here...
    ui->listWidget_2->setFlow(QListView::Flow::LeftToRight);
    ui->listWidget_2->setIconSize(QSize(48, 48));
    ui->listWidget_2->setStyleSheet("#listWidget_2 { background: black; }");

    for(int i = 0; i < 4; i++)  {

        ui->listWidget_2->addItem(new QListWidgetItem(QIcon(arrQListSession[i]), NULL));

    }

    ui->listWidget_2->setCurrentRow(0);

}

// Goes left from the first QListWidget of icons.
void MainWindow::on_durationLeft_clicked()
{
    if(newRowItemAbove == 0) {
        newRowItemAbove = 2;
    }
    else if(newRowItemAbove == 1) {
        newRowItemAbove = 0;
    }
    else {
        newRowItemAbove = 1;
    }
    ui->listWidget->setCurrentRow(newRowItemAbove);
}

// Goes left from the second QListWidget of icons.
void MainWindow::on_sessionLeft_clicked()
{
    if(newRowItemBelow == 0) {
        newRowItemBelow = 3;
    }
    else if(newRowItemBelow == 1) {
        newRowItemBelow = 0;
    }
    else if(newRowItemBelow == 2) {
        newRowItemBelow = 1;
    }
    else {
        newRowItemBelow = 2;
    }
    ui->listWidget_2->setCurrentRow(newRowItemBelow);
}

// Goes right from the first QListWidget of icons.
void MainWindow::on_durationRight_clicked()
{
    if(newRowItemAbove == 0) {
        newRowItemAbove = 1;
    }
    else if(newRowItemAbove == 1) {
        newRowItemAbove = 2;
    }
    else {
        newRowItemAbove = 0;
    }
    ui->listWidget->setCurrentRow(newRowItemAbove);
}

// Goes right from the second QListWidget of icons.
void MainWindow::on_sessionRight_clicked()
{
    if(newRowItemBelow == 0) {
        newRowItemBelow = 1;
    }
    else if(newRowItemBelow == 1) {
        newRowItemBelow = 2;
    }
    else if(newRowItemBelow == 2) {
        newRowItemBelow = 3;
    }
    else {
        newRowItemBelow = 0;
    }
    ui->listWidget_2->setCurrentRow(newRowItemBelow);
}

void MainWindow::on_selectionBtn_clicked()
{
    selectedDuration = newRowItemAbove;
    selectedSession = newRowItemBelow;
}
