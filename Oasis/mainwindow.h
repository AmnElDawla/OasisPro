#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include "Database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onConnect();
    void offConnect();
    void deviceOff();
    void deviceOn();
    void iconsOn();
    void iconsOff();
    void initialiazeListOfIcons();

private slots:
    void on_pushButton_clicked();
    void on_aboveLeft_clicked();
    void on_belowLeft_clicked();
    void on_aboveRight_clicked();
    void on_belowRight_clicked();

private:
    Ui::MainWindow *ui;
    Database* newDatabase = new Database();
    QVector<int> levels;
    int numberOfTimesPowerBtnClicked = 0;
    int newRowItemAbove = 0;
    int newRowItemBelow = 0;
};
#endif // MAINWINDOW_H
