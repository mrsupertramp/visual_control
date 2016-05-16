//
//  Launchpad.hpp
//  visuals002
//
//  Created by Rico on 29.11.15.
//
//

#pragma once
#define Launchpad_hpp

#include <stdio.h>
#include "ofxMidi.h"

#define LIGHT_LOW       0
#define LIGHT_MIDDLE    1
#define LIGHT_HIGH      2

#define STATUS_TOGGLE_GREEN         0
#define STATUS_TOGGLE_RED           1
#define STATUS_TOGGLE_YELLOW        2
#define STATUS_HOLD_GREEN           3
#define STATUS_HOLD_RED             4
#define STATUS_CYCLE                5
#define STATUS_TOGGLE_BLINK_GREEN   6
#define STATUS_TOGGLE_BLINK_RED     7
#define STATUS_BLINK_RED            8
#define STATUS_BLINK_YELLOW         9

#define ROWMASK     7
#define COLMASK     15

#define COLOR_OFF       0
#define COLOR_GREEN     1
#define COLOR_RED       2
#define COLOR_YELLOW    3

class Button{
public:
    uint8_t status;
    uint8_t color;
    uint8_t brightness;

    bool isBlinking;
    uint16_t blinkIntervall = 800;
    uint32_t tLastBlink;
    float blinkDutyCycle = 0.3;


};

class Launchpad{
public:
    void setup();
    void initTemplate1();
    void controlBlinking();
    
    void newMessage(ofxMidiEventArgs &args);
     
    vector <Button> buttons;

private:
    ofxMidiOut midiOut;
    int getMidiColor(int red, int green);
    int getMidiKey(int x, int y);

};



