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
    void on_powerBtn_clicked();
    void on_durationLeft_clicked();
    void on_sessionLeft_clicked();
    void on_durationRight_clicked();
    void on_sessionRight_clicked();
    void on_selectionBtn_clicked();

private:
    Ui::MainWindow *ui;
    Database* newDatabase = new Database();
    QVector<int> levels;
    int numberOfTimesPowerBtnClicked = 0;
    int newRowItemAbove = 0;
    int newRowItemBelow = 0;
};
#endif // MAINWINDOW_H
