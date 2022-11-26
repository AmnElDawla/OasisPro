// File Record.h
#ifndef RECORD_H
#define RECORD_H

#include <QDateTime>
#include <QTime>
#include <QString>

/* Team #37:

 * Goal: To save contents about a user as a Record in mainwindow and in database

 * Member functions:

    // getters:
    Qstring getSessionType(): a function to return a string to store the infomation of session type
    int getDuration(): a function to return the duration of a treatment (in seconds)
    int getIntensityLevel(): a function to return the intensitiy level of a treatment

    // setters:
    void setDuration(int d): a function to replace the duration of a Record with a new value
    void setIntensityLevel(int i): a functio to replace the level intensity of a Record with a new value

    // other function(s):
    QString stringify(): a function to convert all attributes of a Record into a string

 * Member variables:
    − intensityLevel: int
    − duration: int
    − sessionType: QString
 */

class Record
{
public:
    Record(const QString &sessionType, const int intensityLevel, const int duration);

    QString getSessionType();
    int getDuration();
    int getIntensityLevel();

    void setDuration(int d);
    void setIntensityLevel(int i);

    QString stringify();

private:
    QString sessionType;
    int intensityLevel;
    int duration;
};

#endif // RECORD_H
