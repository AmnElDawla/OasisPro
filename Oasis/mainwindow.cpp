#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
        mainDatabase->getUserData(0);
        mainDatabase->getUserData(1);
        mainDatabase->getUserData(2);
        mainDatabase->getUserData(3);
        qDebug() << "Operation was successfully completed...";
    }
    else {
        qDebug() << "Operation was not successfully completed...";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // Change color of lights, enable/disable buttons.
    if(deviceOn == false){
        ui->progressBar->setStyleSheet("#progressBar::chunk{background-color: #01fe00;}");
        ui->label_4->setStyleSheet("#label_4{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82;}");
        ui->label_6->setStyleSheet("#label_6{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #FF7e82;}");
        ui->label_7->setStyleSheet("#label_7{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0);}");
        ui->label_8->setStyleSheet("#label_8{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0);}");
        ui->label_9->setStyleSheet("#label_9{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(255, 255, 0);}");
        ui->label_10->setStyleSheet("#label_10{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73;}");
        ui->label_11->setStyleSheet("#label_11{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73;}");
        ui->label_12->setStyleSheet("#label_12{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #5ced73;}");
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
    } else if(deviceOn == true){
        ui->progressBar->setStyleSheet("#progressBar::chunk{background-color: #ff0000;}");
        ui->label_4->setStyleSheet("#label_4{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #4d0000;}");
        ui->label_6->setStyleSheet("#label_6{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #4d0000;}");
        ui->label_7->setStyleSheet("#label_7{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(120, 120, 0);}");
        ui->label_8->setStyleSheet("#label_8{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(120, 120, 0);}");
        ui->label_9->setStyleSheet("#label_9{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: rgb(120, 120, 0);}");
        ui->label_10->setStyleSheet("#label_10{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #2e7639;}");
        ui->label_11->setStyleSheet("#label_11{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #2e7639;}");
        ui->label_12->setStyleSheet("#label_12{background-color: transparent; font-weight: 600; color: black; background-repeat: none; background: #2e7639;}");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
    }
    // Change device on/off bool variable.
    deviceOn = !deviceOn;
}
