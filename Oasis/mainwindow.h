#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <unistd.h>
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
    void batteryLevel(int);
    void resetButtons();
    void flashSelectedLevel();

private slots:
    void on_powerBtn_clicked();
    void on_durationLeft_clicked();
    void on_sessionLeft_clicked();
    void on_durationRight_clicked();
    void on_sessionRight_clicked();
    void on_selectionBtn_clicked();    
    void on_increaseIntensityBtn_clicked();
    void on_decreaseIntensityBtn_clicked();

private:
    Ui::MainWindow *ui;
    Database* newDatabase = new Database();
    QVector<int> levels;
    int numberOfTimesPowerBtnClicked = 0;
    int newRowItemDuration = 0;
    int newRowItemSession = 0;
    int selectedDuration = 0;
    int selectedSession = 0;

    /*
     * This array is special. Its indices all follow a standard that should
     * be used everywhere in the project. The standard is as follows:
     *      sessionArray[0]: Stores duration of the session
     *      sessionArray[1]: Stores session type
     *      sessionArray[2]: Stores intensity level of the session at the time of completion
     */
    int sessionArray[3];
};
#endif // MAINWINDOW_H
