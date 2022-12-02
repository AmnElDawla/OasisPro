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
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Database objData;

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
    // LED controls
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
    // LED controls end

    void graphSessionOn();
    void graphSessionOff();
    void flashCesModeLight();
    bool getConnectivity();
    void onConnectivity();
    void offConnectivity();
    void offLeds();
    void onLeds();
    void toggleCesModeLight();
    void displayConnection(int signal);
    void playScrollAnimation();
    // connection test main control
    int connectionTestMain();
    //LED controls end
    void flashSelectedLevelAfterSelection();
    void selectedIntensityAtStart();
    void pauseTimer(int);
    void ledBlinkTimer();
    void intervalTimerIntensity();
    void onLeftEar();
    void offLeftEar();
    void onRightEar();
    void offRightEar();
    void offGroupBoxEars();
    void onGroupBoxEars();
    void delay5Seconds();

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
    void flashTimer();
    void flashGraphCounter();
    void pauseCounter();
    void blinkCounter();
    void switchLeds();
    void on_newBattery_clicked();
    void on_listOfSkins_currentIndexChanged(const QString &arg1);
    void continueAfter5Seconds();

private:
    Ui::MainWindow *ui;
    Database *newDatabase = new Database();
    QVector<int> levels;
    int numberOfTimesPowerBtnClicked = 0;
    int newRowItemDuration = 0;
    int newRowItemSession = 0;
    int selectedDuration = 0;
    int selectedSession = 0;
    QTimer *batteryStartTimer = nullptr;
    QTimer *batteryStopTimer = nullptr;
    bool selectedSessionOrNot = false;
    int batteryLevel = 43;
    bool ledOneStatus = false;
    bool ledTwoStatus = false;
    bool ledThreeStatus = false;
    bool ledFourStatus = false;
    bool ledFiveStatus = false;
    bool ledSixStatus = false;
    bool ledSevenStatus = false;
    bool ledEightStatus = false;
    int valueIntUntilEndOfFlash = 0;
    bool ledFourFlash = false;
    bool ledFiveFlash = false;
    bool ledSixFlash = false;
    bool ledSevenFlash = false;
    QTimer *timer = nullptr;
    // Connection test:
    bool graphSessionStatus = false;
    bool connectivity = true;
    QTimer *timerFlashes = nullptr;
    QTimer *timerCES = nullptr;
    // Connection test:
    /* CES Mode light control */
    QTimer *connectionTestStartTimer = nullptr;
    QTimer *connectionTestStopTimer = nullptr;
    int counterFlashGraph = 0;
    bool OptionDry = false;
    bool OptionWet = false;
    QTimer *pauseTimerDefault = nullptr;
    int valuePause = 0;
    int countForPauseEnd = 0;
    QTimer *timerBlinkLed = nullptr;
    /*
     * Grp 0 ====> blinking LEDs 7 and 8
     * Grp 1 ====> blinking LEDs 4, 5, and 6
     * Grp 2 ====> blinking LEDs 1, 2, and 3
     */
    int groupToBlink = 0;
    int counterBlinkingLed = 0;
    bool blinkTrueOrFalse = true;
    int signal = 0;
    QTimer *intensityTimer = nullptr;
    int countSwitch = 0;
    QTimer *fiveSecondsDelay = nullptr;

};
#endif // MAINWINDOW_H
