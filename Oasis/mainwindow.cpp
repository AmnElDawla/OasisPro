#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //off icons
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

    //Everything needs to be off in the GUI
    ui->label_16->setStyleSheet("#label_16 { border-image: url(:/resources/icons/connectOff.png); border: 2px solid red; border-radius: 20px; }");
    ui->progressBar->setStyleSheet("#progressBar::chunk{ background-color: white; }");
    ui->label_4->setStyleSheet("#label_4 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_6->setStyleSheet("#label_6 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_7->setStyleSheet("#label_7 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_8->setStyleSheet("#label_8 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_9->setStyleSheet("#label_9 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_10->setStyleSheet("#label_10 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_11->setStyleSheet("#label_11 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
    ui->label_12->setStyleSheet("#label_12 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");

    //QList (above) initialize starts here...
    ui->listWidget->setFlow(QListView::Flow::LeftToRight);
    ui->listWidget->setIconSize(QSize(48, 48));
    ui->listWidget->setStyleSheet("#listWidget { background: black; }");

    for(int i = 0; i < 3; i++)  {

        ui->listWidget->addItem(new QListWidgetItem(QIcon(arrQListAbove[i]), NULL));

    }

    //QList (below) initialize starts here...
    ui->listWidget_2->setFlow(QListView::Flow::LeftToRight);
    ui->listWidget_2->setIconSize(QSize(48, 48));
    ui->listWidget_2->setStyleSheet("#listWidget_2 { background: black; }");

    for(int i = 0; i < 4; i++)  {

        ui->listWidget_2->addItem(new QListWidgetItem(QIcon(arrQListBelow[i]), NULL));

    }

}

MainWindow::~MainWindow()
{

    delete ui;

}


void MainWindow::on_pushButton_clicked()
{

    //on icons
    QString arrQListAboveOn[3] = {":/resources/icons/20MinuteOn.png", ":/resources/icons/45MinuteOn.png", ":/resources/icons/UserDesignatedOn.png"};
    QString arrQListBelowOn[4] = {":/resources/icons/AlphaOn.png", ":/resources/icons/Beta1On.png", ":/resources/icons/Beta2On.png", ":/resources/icons/ThetaOn.png"};

    //off icons
    QString arrQListAbove[3] = {":/resources/icons/20Minute.png", ":/resources/icons/45Minute.png", ":/resources/icons/UserDesignated.png"};
    QString arrQListBelow[4] = {":/resources/icons/Alpha.png", ":/resources/icons/Beta1.png", ":/resources/icons/Beta2.png", ":/resources/icons/Theta.png"};

    // Change color of lights, enable/disable buttons.

    if(numTimesClicked == 0) {

        ui->progressBar->setStyleSheet("#progressBar::chunk { background-color: #01fe00; }");
        ui->label_4->setStyleSheet("#label_4 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
        ui->label_6->setStyleSheet("#label_6 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82; }");
        ui->label_7->setStyleSheet("#label_7 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
        ui->label_8->setStyleSheet("#label_8 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
        ui->label_9->setStyleSheet("#label_9 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0); }");
        ui->label_10->setStyleSheet("#label_10 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
        ui->label_11->setStyleSheet("#label_11 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
        ui->label_12->setStyleSheet("#label_12 { background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73; }");
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        numTimesClicked = 1;

    }
    else if(numTimesClicked == 1) {

        ui->label_16->setStyleSheet("#label_16 { border-image: url(:/resources/icons/connect.PNG); border: 2px solid red; border-radius: 20px; }");
        ui->label_20->setStyleSheet("#label_20 { border-image: url(:/resources/icons/LeftEar_Connected.PNG); border: 2px solid red; border-radius: 20px; }");

        numTimesClicked = 2;
        ui->listWidget->setIconSize(QSize(48, 48));
        ui->listWidget_2->setIconSize(QSize(48, 48));

        for(int i = 0; i < 3; i++)  {

            ui->listWidget->item(i)->setIcon(QIcon(arrQListAboveOn[i]));

        }

        for(int i = 0; i < 4; i++)  {

            ui->listWidget_2->item(i)->setIcon(QIcon(arrQListBelowOn[i]));

        }

    }
    else {

        ui->label_20->setStyleSheet("#label_20 { border-image: url(:/resources/icons/LeftEar_Off.PNG); border: 2px solid red; border-radius: 20px; }");
        ui->label_16->setStyleSheet("#label_16 { border-image: url(:/resources/icons/connectOff.png); border: 2px solid red; border-radius: 20px; }");
        ui->progressBar->setStyleSheet("#progressBar::chunk{ background-color: white; }");
        ui->label_4->setStyleSheet("#label_4 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->label_6->setStyleSheet("#label_6 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->label_7->setStyleSheet("#label_7 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->label_8->setStyleSheet("#label_8 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->label_9->setStyleSheet("#label_9 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->label_10->setStyleSheet("#label_10 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->label_11->setStyleSheet("#label_11 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->label_12->setStyleSheet("#label_12 { background-color: white; font-weight: 600; color: black; background-repeat: none; }");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);

        ui->listWidget->setIconSize(QSize(48, 48));
        ui->listWidget_2->setIconSize(QSize(48, 48));

        for(int i = 0; i < 3; i++)  {

            ui->listWidget->item(i)->setIcon(QIcon(arrQListAbove[i]));

        }

        for(int i = 0; i < 4; i++)  {

            ui->listWidget_2->item(i)->setIcon(QIcon(arrQListBelow[i]));

        }
        numTimesClicked = 0;

    }

}
