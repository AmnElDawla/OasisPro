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
    QString tmpString =
        "   session type: " + QString::number(sessionType) + "\n" +
        "   duration: " + QString::number(duration) + "\n" +
        "   intensity level: " + QString::number(intensityLevel);

    return tmpString;
}
