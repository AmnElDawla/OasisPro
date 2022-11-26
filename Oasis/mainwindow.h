#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <unistd.h>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
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
    void resetButtons();
    void flashSelectedLevel();
    //LED controls
    void ledOneOff();
    void ledTwoOff();
    void ledThreeOff();
    void ledFourOff();
    void ledFiveOff();
    void ledSixOff();
    void ledSevenOff();
    void ledEightOff();
    void ledOneOn();
    void ledTwoOn();
    void ledThreeOn();
    void ledFourOn();
    void ledFiveOn();
    void ledSixOn();
    void ledSevenOn();
    void ledEightOn();
    void toggleLedOne();
    void toggleLedTwo();
    void toggleLedThree();
    void toggleLedFour();
    void toggleLedFive();
    void toggleLedSix();
    void toggleLedSeven();
    void toggleLedEight();
    //LED controls end

private slots:
    void on_powerBtn_clicked();
    void on_durationLeft_clicked();
    void on_sessionLeft_clicked();
    void on_durationRight_clicked();
    void on_sessionRight_clicked();
    void on_selectionBtn_clicked();    
    void showBatteryLevel();
    void stopBatteryLevel();
    void on_increaseIntensityBtn_clicked();
    void on_decreaseIntensityBtn_clicked();
    void turnOffNoSessionSelected();

private:
    Ui::MainWindow *ui;
    Database* newDatabase = new Database();
    QVector<int> levels;
    int numberOfTimesPowerBtnClicked = 0;
    int newRowItemDuration = 0;
    int newRowItemSession = 0;
    int selectedDuration = 0;
    int selectedSession = 0;
    QTimer *batteryStartTimer;
    QTimer *batteryStopTimer;
    bool selectedSessionOrNot = false;
    int batteryLevel = 12;
    bool ledOneStatus = false;
    bool ledTwoStatus = false;
    bool ledThreeStatus = false;
    bool ledFourStatus = false;
    bool ledFiveStatus = false;
    bool ledSixStatus = false;
    bool ledSevenStatus = false;
    bool ledEightStatus = false;
    QTimer *timer;

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
