// File TherapyRecord.cpp
#include "TherapyRecord.h"

// constructor:
TherapyRecord::TherapyRecord(const int sessionType, const int intensityLevel, const int duration)
{
    this->sessionType = sessionType;
    this->duration = duration;
    this->intensityLevel = intensityLevel;
}

// getters:
int TherapyRecord::getSessionType() { return sessionType; }
int TherapyRecord::getIntensityLevel() { return intensityLevel; }
int TherapyRecord::getDuration() { return duration; }

// setters:
void TherapyRecord::setDuration(int d) { duration = d; }
void TherapyRecord::setIntensityLevel(int i) { intensityLevel = i; }

// member function(s):
QString TherapyRecord::stringify()
{
    // Prepare values to parse:
    int sessionNumberTherapy = this->getSessionType();
    int sessionDurationTherapy = this->getDuration();
    int sessionIntensityLevelTherapy = this->getIntensityLevel();

    // Record the session number associated with the index of the selected session:
    if (sessionNumberTherapy == 0)
    {
        sessionNumberTherapy = 5;
    }
    else if (sessionNumberTherapy == 1)
    {
        sessionNumberTherapy = 6;
    }
    else if (sessionNumberTherapy == 2)
    {
        sessionNumberTherapy = 7;
    }
    else if (sessionNumberTherapy == 3)
    {
        sessionNumberTherapy = 4;
    }

    // Generating output:
    QString tmpString =
        "   session number: " + QString::number(sessionNumberTherapy) + "\n" +
        "   intensity level: " + QString::number(sessionIntensityLevelTherapy) + "\n" +
        "   duration: " + QString::number(sessionDurationTherapy) + "s";

    return tmpString;
}
