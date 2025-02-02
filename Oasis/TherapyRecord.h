// File TherapyRecord.h
#ifndef THERAPYRECORD_H
#define THERAPYRECORD_H

#include <QDateTime>
#include <QTime>
#include <QString>

/* Team #37:

 * Goal: To save contents about a user as a TherapyRecord in mainwindow and in database

 * Member functions:

    // getters:
    int getSessionType(): a function to return an integer to store the infomation of session type
    int getDuration(): a function to return the duration of a treatment
    int getIntensityLevel(): a function to return the intensitiy level of a treatment

    // setters:
    void setDuration(int d): a function to replace the duration of a TherapyRecord with a new value
    void setIntensityLevel(int i): a functio to replace the level intensity of a TherapyRecord with a new value

    // other function(s):
    QString stringify(): a function to convert all attributes of a TherapyRecord into a string

 * Member variables:
    − intensityLevel: int
    − duration: int
    − sessionType: QString
 */

class TherapyRecord
{
public:
    TherapyRecord(const int sessionType, const int intensityLevel, const int duration);

    int getSessionType();
    int getDuration();
    int getIntensityLevel();

    void setDuration(int d);
    void setIntensityLevel(int i);

    QString stringify();

private:
    int sessionType;
    int intensityLevel;
    int duration;
};

#endif // THERAPYRECORD_H
