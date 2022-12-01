// File TherapyRecord.cpp
#include "TherapyRecord.h"

// constructor:
TherapyRecord::TherapyRecord(const QString &sessionType, const int intensityLevel, const int duration)
{
    this->sessionType = sessionType;
    this->duration = duration;
    this->intensityLevel = intensityLevel;
}

// getters:
QString TherapyRecord::getSessionType() { return sessionType; }
int TherapyRecord::getIntensityLevel() { return intensityLevel; }
int TherapyRecord::getDuration() { return duration; }

// setters:
void TherapyRecord::setDuration(int d) { duration = d; }
void TherapyRecord::setIntensityLevel(int i) { intensityLevel = i; }

// member function(s):
QString TherapyRecord::stringify()
{
    QString durationToString = QString::number(duration / 60);
    durationToString += ((duration % 60 < 10) ? +":0" + QString::number(duration % 60)
                                              : +":" + QString::number(duration % 60));
    QString tmpString =
        "   session type: " + sessionType + "\n" +
        "   duration: " + durationToString + "\n" +
        "   intensity level: " + QString::number(intensityLevel);

    return tmpString;
}
