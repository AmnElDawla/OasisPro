// File Record.cpp
#include "Record.h"

// constructor:
Record::Record(const QString &sessionType, const int intensityLevel, const int duration)
{
    this->sessionType = sessionType;
    this->duration = duration;
    this->intensityLevel = intensityLevel;
};

// getters:
QString Record::getSessionType() { return sessionType; };
int Record::getIntensityLevel() { return intensityLevel; };
int Record::getDuration() { return duration; };

// setters:
void Record::setDuration(int d) { duration = d; };
void Record::setIntensityLevel(int i) { intensityLevel = i; };

// member function(s):
QString Record::stringify()
{
    QString durationToString = QString::number(duration / 60);
    durationToString += ((duration % 60 < 10) ? +":0" + QString::number(duration % 60)
                                              : +":" + QString::number(duration % 60));
    QString tmpString =
        "   session type: " + sessionType + "\n" +
        "   duration: " + durationToString + "\n" +
        "   intensity level: " + QString::number(intensityLevel);

    return tmpString;
};
