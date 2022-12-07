#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes all the necessary libraries and header files.
#include <unistd.h>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QInputDialog>
#include "Database.h"
#include "TherapyRecord.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Database object to store session data.
    Database objData;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Device on or off functions.
    void onConnect();
    void offConnect();
    void deviceOff();
    void deviceOn();
    void iconsOn();
    void iconsOff();
    void initialiazeListOfIcons();
    void resetButtons();
    void flashSelectedLevel();

    // LED controls functions.
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
    void offLeds();
    void onLeds();

    // Connectivity functions.
    void graphSessionOn();
    void graphSessionOff();
    void flashCesModeLight();
    bool getConnectivity();
    void onConnectivity();
    void offConnectivity();
    void toggleCesModeLight();
    void displayConnection(int signal);
    void playScrollAnimation();

    // Connection test main control.
    int connectionTestMain();

    // Connection test functions.
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

    // These slots show battery level and reset the graph afterwards when called.
    void showBatteryLevel();
    void stopBatteryLevel();

    // Simulate battery degradation.
    void degradeBattery();

    // This slot below is called when user presses the up arrow next to the intensity labels (1 to 8).
    // This is used to select an intensity.
    void on_increaseIntensityBtn_clicked();

    // This slot below is called when user presses the down arrow next to the intensity labels (1 to 8).
    // This is used to select an intensity.
    void on_decreaseIntensityBtn_clicked();

    // This slot is called when QTimer named timer timeout. This is called after 2 minutes (or 120000 miliseconds)
    // of having no response from the user (who did not select a session).
    void turnOffNoSessionSelected();

    // This slot is called when QTimer named timerFlashes timeout. It flashes (turns on or off at a 500 miliseconds interval)
    // the respective session number in the intensity column (the column that goes from 1 to 8 in the GUI). It does
    // this for 3 seconds.
    void flashTimer();

    // This slot is called when the QTimer named timerCes timeout. It calls the toggleCesModeLight() function to turn on
    // or off the CES mode light for 3 seconds (3000 miliseconds) at an interval of 500 miliseconds.
    void flashGraphCounter();

    // This slot is called when the QTimer named pauseTimerDefault timeout. It calls the intervalTimerIntensity() that performs
    // the scrolling animation (when the device's disconnected). It does this for 8 seconds (8000 miliseconds).
    void pauseCounter();

    // This slot is called when the QTimer named timerBlinkLed timeout. It checks what group of LEDs will be called based
    // on the connection (connected or disconnected) and state (dry or wet).
    // - If the state is dry and the device's connected, the LEDs 4, 5, and 6 will blink yellow (turn on and off) at the same time.
    //   This means that the user has an okay connection.
    // - If the state is wet and the device's connected, the LEDs 1, 2, and 3 will blink green (turn on or off) at the same time.
    //   This means that the user has a good connection.
    // - If the state is either dry or wet and the device's disconnected, the LEDs 7 and 8 will blink red (turn on or off) at the same time.
    //   This means that the user has no connection.
    // It will blink these group of LEDs for 3 seconds (3000 miliseconds) at an interval of 500 miliseconds.
    void blinkCounter();

    // This slot is called when the QTimer named intensityTimer timeout. This slot performs the turn on and off the LEDs (the labels
    // 1 to 8 found in the UI) in scrolling manner (turns on and off one at a time) in an interval of 500 miliseconds.
    // Once it reaches 15 (as there is 15 times that it needs to turn on or off of the LEDs - 8 numbers * 2 states (turn on or off) equals
    // to 16 (15 goes from 0 to 15, which is 16 as it counts 0 as well), it stops the timer and reset the countSwitch counter back to 0.
    // The countSwitch keeps track of how many times the slot has been called (when it reaches 15 the animation ends).
    void switchLeds();

    // This slot is called the user presses the new battery button. This will make the battery of the device go back
    // to 100%.
    void on_newBattery_clicked();

    // This slot is called when the user changes the connectivity of the application (switches from connected to
    // disconnected and vice-versa). This checks if the device is fully turned on and that a session has started in
    // order for the change to go through (this means once it has confirmed that the device is fully on and that a
    // session has started, it will proceed to restart the connection test).
    void on_listOfSkins_currentIndexChanged(const QString &arg1);

    // This slot is called when the QTimer named fiveSecondsDelay timeout. As a SingleShot QTimer, we do not need
    // to stop the fiveSecondsDelay QTimer, which means that this slot just calls the connection test function to
    // start the connection test.
    void continueAfter5Seconds();

    // This slot is called when the user switches from wet to dry and vice-versa.
    // This checks if the device is fully turned on and that a session has started in
    // order for the change to go through (this means once it has confirmed that the device is fully on and that a
    // session has started, it will proceed to restart the connection test).
    void on_listWetOrDry_currentIndexChanged(const QString &arg1);

    // This slot is called when the QTimer named endSession timeout. It will start the descend (scrolling down) animation
    // in the intensity section of UI (where the vertical labels containing number from 1 to 8 are found).
    void startDescendEndSession();

    // This slot is called when the QTimer named seconds20Timer timeout. It will update the part of the GUI that displays
    // the time left for the session (time left before the session ends).
    void updateUITime20sDisplay();

    // This slot is called when the QTimer named seconds45Timer timeout. It will update the part of the GUI that displays
    // the time left for the session (time left before the session ends).
    void updateUITime45sDisplay();

    // This slot is called when the QTimer named customTimer timeout. It will update the part of the GUI that displays
    // the time left for the session (time left before the session ends).
    void updateUITimeCustomDisplay();

    void on_treatmentRefreshBtn_clicked();

    void on_treatmentDownBtn_clicked();

    void on_treatmentUpBtn_clicked();

private:
    Ui::MainWindow *ui;

    // Database variable (starts new database)
    Database *newDatabase = new Database();

    QVector<int> levels;

    // Records how many times the power button has been clicked.
    int numberOfTimesPowerBtnClicked = 0;

    // Duration and session variables.
    int newRowItemDuration = 0;
    int newRowItemSession = 0;
    int selectedDuration = 0;
    int selectedSession = 0;

    // Battery variables.
    QTimer *batteryStartTimer = nullptr;
    QTimer *batteryStopTimer = nullptr;
    QTimer *batteryDegradationTimer = nullptr;
    bool selectedSessionOrNot = false;
    int batteryLevel = 14;
    int batteryLevelEnlarged = batteryLevel * 100;
    bool degradeBatteryAllowed = true;

    // LEDs variables (boolean).
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

    // Timer variable to check if user does
    // not click selection button after 2 minutes.
    QTimer *timer = nullptr;

    // Connection test variables
    bool graphSessionStatus = false;
    bool connectivity = true;
    QTimer *timerFlashes = nullptr;
    QTimer *timerCES = nullptr;
    int signal = 0;
    bool OptionDry = false;
    bool OptionWet = false;
    bool changeWetOrDry = false;

    /* CES Mode light control */
    QTimer *connectionTestStartTimer = nullptr;
    QTimer *connectionTestStopTimer = nullptr;
    int counterFlashGraph = 0;
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

    // Flashes intensity variables.
    int counterBlinkingLed = 0;
    bool blinkTrueOrFalse = true;

    // Scrolling animation variables
    QTimer *intensityTimer = nullptr;
    int countSwitch = 0;

    // Delay timer.
    QTimer *fiveSecondsDelay = nullptr;

    // End session variables.
    bool sessionOnOrOff = false;
    QTimer *endSession = nullptr;
    int countSwitchDescent = 0;

    // Session countdown timer
    QTimer *sessionCountdown = nullptr;
    int countDownSession = 0;

    // Finished flashing choosen intensity (based on session) variable
    bool finishedFlashing = false;

    // Check if two minutes timer is deleted
    // Set to false (default)
    bool timerEnded = false;

    // 20s timer
    QTimer *seconds45Timer = nullptr;

    // 45s timer
    QTimer *seconds20Timer = nullptr;

    // 20s counter that will count up to 20
    int countTo20 = 0;

    // 45s counter that will count up to 45
    int countTo45 = 0;

    // Countdown variable that will countdown from 20 to 0
    int from20to0 = 20;

    // Countdown variable that will countdown from 45 to 0
    int from45to0 = 45;

    // Finds out if the session scrolldown animation is finished (only works when session finishes at its described /
    // prescribed time and not earlier than that).
    bool finishedScrolledDown = false;

    // Custom duration value variable that is set to 0.
    int customDuration = 0;

    // Custom counter for the custom duration (used in the QTimer named customTimer)
    int customCounter = 0;

    // Custom QTimer for the custom duration
    QTimer *customTimer = nullptr;

    // Custom countdown that is set to 0.
    int countdownCustom = 0;

    // Keep track of which item in the recordings listview we've selected
    int recordlistItemIndex = -1;

};
#endif // MAINWINDOW_H
