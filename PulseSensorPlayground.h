/*
 * A central Playground object to exercise the PulseSensor.
 * See https://www.pulsesensor.com to get started.
 *
 * Portions Copyright (c) 2016, 2017 Bradford Needham, North Plains, Oregon, USA
 * @bneedhamia, https://bluepapertech.com
 * Licensed under the MIT License, a copy of which
 * should have been included with this software.
 *
 * This software is not intended for medical use.
 */

#ifndef PULSE_SENSOR_PLAYGROUND_H
#define PULSE_SENSOR_PLAYGROUND_H

#include <Arduino.h>
#include "utility/PulseSensorBeatDetector.h"

class PulseSensorPlayground {
  public:
    PulseSensorBeatDetector *pBeat;
    void beginBeatDetection() {
      pBeat = new PulseSensorBeatDetector();
    }
    void setBeatSampleIntervalMs(long sampleIntervalMs) {
      pBeat->setSampleIntervalMs(sampleIntervalMs);
	}
    int getBeatsPerMinute() { return pBeat->getBPM(); }
    int getInterBeatIntervalMs() { return pBeat->getIBI(); }
    boolean isBeat() { return pBeat->isBeat(); }
    boolean addBeatValue(int analogValue) {
      return pBeat->addBeatValue(analogValue);
    }

    void begin(void);
    void begin(int);    // FUTURE: use for more than one Pulse Sensor
    void sample_detect(void);

    int blinkPin[2] = {13,12};
    int fadePin[2] = {5,6};

    boolean testBool = false;

    boolean uno = false;
    boolean leo = false;
};

extern PulseSensorPlayground pulse;

#endif // PULSE_SENSOR_PLAYGROUND_H
