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

    void flashSelectedLevelAfterSelection();
    void selectedIntensityAtStart();
    void pauseTimer(int);
    void ledBlinkTimer();
    void intervalTimerIntensity();

    // Turns on or off left or right ear.
    void onLeftEar();
    void offLeftEar();
    void onRightEar();
    void offRightEar();

    // Turns on or off the border where the right and left ear are found
    void offGroupBoxEars();
    void onGroupBoxEars();

    // This function below makes sure that after pressing the selection button, there 5 seconds delay.
    void delay5Seconds();

    // This function below does the scrolling down animation when user ends the session
    // (either the user ends the session early or not).
    void descendEndSession();

private slots:

    // This slot below is called when the user clicks the powerbutton. It checks if the power button has been clicked
    // how many times it has been clicked.
    // - One clicks means that the device turn on but not completely (this click does not turn on the icons for the duration and session
    //   as well as the left and right ear and the session graph.
    // - Two clicks opens the device fully (everything is turned on).
    // - Three clicks shuts down the device (everything is turned off).
    void on_powerBtn_clicked();

    // This slot below is called when the user presses the left arrow next to the duration icons. This is used
    // to select a duration for the selected session.
    void on_durationLeft_clicked();

    // This slot below is called when user presses the left arrow next to the session icons. This is used to select
    // a session.
    void on_sessionLeft_clicked();

    // This slot below is called when the user presses the right arrow next to the duration icons. This is used
    // to select a duration for the selected session.
    void on_durationRight_clicked();

    // This slot below is called when user presses the right arrow next to the session icons. This is used to select
    // a session.
    void on_sessionRight_clicked();

    // This slot is called when the user presses the selection button. When this is pressed the chosen duration
    // and session are stored as variables.
    void on_selectionBtn_clicked();

    void showBatteryLevel();
    void stopBatteryLevel();
    void on_increaseIntensityBtn_clicked();
    void on_decreaseIntensityBtn_clicked();

    // This slot is called when QTimer named timer timeout. This is called after 2 minutes (or 120000 miliseconds)
    // of having no response from the user (who did not select a session).
    void turnOffNoSessionSelected();

    // This slot is called when QTimer named timerFlashes timeout. It flashes (turns on or off at a 500 miliseconds interval)
    // the respective session number in the intensity column (the column that goes from 1 to 8 in the GUI). It does
    // this for 3 seconds.
    void flashTimer();
    void flashGraphCounter();
    void pauseCounter();
    void blinkCounter();
    void switchLeds();
    void on_newBattery_clicked();
    void on_listOfSkins_currentIndexChanged(const QString &arg1);
    void continueAfter5Seconds();
    void on_listWetOrDry_currentIndexChanged(const QString &arg1);
    void startDescendEndSession();

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
    bool sessionOnOrOff = false;
    QTimer *endSession = nullptr;
    int countSwitchDescent = 15;

};
#endif // MAINWINDOW_H
