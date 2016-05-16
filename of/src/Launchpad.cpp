//
//  Launchpad.cpp
//  visuals002
//
//  Created by Rico on 29.11.15.
//
//

#include "Launchpad.hpp"
#include "ofApp.h"

void Launchpad::setup(){
    midiOut.openPort(0);
    
    //init buttons
    initTemplate1();
}

void Launchpad::newMessage(ofxMidiEventArgs &args){
    /*
     cout << "MIDI message [port: " << args.port << ", channel: " << args.channel << ", status: " << args.status << ", byteOne: " << args.byteOne << ", byteTwo: " << args.byteTwo << ", timestamp: " << args.timestamp << "]" << endl;
     */
    
    
    int x = (args.byteOne & 15);
    int y = (args.byteOne >> 4);
    int index = x + y*9;
    cout << x << "  " << y << "  " << index << endl;
    
    Button button = buttons[index];
    
    if (buttons[index].status == STATUS_TOGGLE_GREEN && args.byteTwo) {
        buttons[index].color = buttons[index].color ? COLOR_OFF:COLOR_GREEN;
        midiOut.sendNoteOn(1, getMidiKey(x, y), getMidiColor(buttons[index].color, buttons[index].brightness));
    }
    if (buttons[index].status == STATUS_TOGGLE_RED && args.byteTwo) {
        buttons[index].color = buttons[index].color ? COLOR_OFF:COLOR_RED;
        midiOut.sendNoteOn(1, getMidiKey(x, y), getMidiColor(buttons[index].color, buttons[index].brightness));
    }
    if (buttons[index].status == STATUS_TOGGLE_YELLOW && args.byteTwo) {
        buttons[index].color = buttons[index].color ? COLOR_OFF : COLOR_YELLOW;
        midiOut.sendNoteOn(1, getMidiKey(x, y), getMidiColor(buttons[index].color, buttons[index].brightness));
    }
    if (buttons[index].status == STATUS_HOLD_GREEN) {
        buttons[index].color = buttons[index].color ? COLOR_OFF : COLOR_GREEN;
        midiOut.sendNoteOn(1, getMidiKey(x, y), getMidiColor(buttons[index].color, buttons[index].brightness));
    }
    if (buttons[index].status == STATUS_TOGGLE_BLINK_GREEN && args.byteTwo) {
        buttons[index].isBlinking = !buttons[index].isBlinking;
    }
    if (buttons[index].status == STATUS_TOGGLE_BLINK_RED && args.byteTwo) {
        buttons[index].isBlinking = !buttons[index].isBlinking;
    }
    if (buttons[index].status == STATUS_CYCLE && args.byteTwo) {
        buttons[index].color = buttons[index].color == COLOR_YELLOW ? COLOR_OFF : (buttons[index].color + 1);
        midiOut.sendNoteOn(1, getMidiKey(x, y), getMidiColor(buttons[index].color, buttons[index].brightness));
    }
    
    
}

void Launchpad::controlBlinking(){
    for (int i=0 ; i<buttons.size() ; ++i){
        if (buttons[i].status == STATUS_TOGGLE_BLINK_GREEN) {
            if (buttons[i].isBlinking) {
                int elapsed = ofGetElapsedTimeMillis() - buttons[i].tLastBlink;
                if (elapsed < buttons[i].blinkIntervall) {
                    if (elapsed < buttons[i].blinkIntervall * buttons[i].blinkDutyCycle) {
                        if (!buttons[i].color) {
                            buttons[i].color = COLOR_GREEN;
                            midiOut.sendNoteOn(1, getMidiKey(i%9, i/9), getMidiColor(COLOR_GREEN, buttons[i].brightness));
                        }
                    } else {
                        if (buttons[i].color) {
                            buttons[i].color = COLOR_OFF;
                            midiOut.sendNoteOn(1, getMidiKey(i%9, i/9), getMidiColor(0, 0));
                        }
                    }
                } else {
                    buttons[i].tLastBlink = ofGetElapsedTimeMillis();
                }
            } else {
                if (buttons[i].color) {
                    buttons[i].color = COLOR_OFF;
                    midiOut.sendNoteOn(1, getMidiKey(i%9, i/9), getMidiColor(0, 0));
                }
            }
        } else if (buttons[i].status == STATUS_TOGGLE_BLINK_RED) {
            if (buttons[i].isBlinking) {
                int elapsed = ofGetElapsedTimeMillis() - buttons[i].tLastBlink;
                if (elapsed < buttons[i].blinkIntervall) {
                    if (elapsed < buttons[i].blinkIntervall * buttons[i].blinkDutyCycle) {
                        if (!buttons[i].color) {
                            buttons[i].color = COLOR_RED;
                            midiOut.sendNoteOn(1, getMidiKey(i%9, i/9), getMidiColor(COLOR_RED, buttons[i].brightness));
                        }
                    } else {
                        if (buttons[i].color) {
                            buttons[i].color = COLOR_OFF;
                            midiOut.sendNoteOn(1, getMidiKey(i%9, i/9), getMidiColor(0, 0));
                        }
                    }
                } else {
                    buttons[i].tLastBlink = ofGetElapsedTimeMillis();
                }
            } else {
                if (buttons[i].color) {
                    buttons[i].color = COLOR_OFF;
                    midiOut.sendNoteOn(1, getMidiKey(i%9, i/9), getMidiColor(0, 0));
                }
            }
        }
    }
}

int Launchpad::getMidiColor(int color, int bri){
    int green=0,red=0;
    
    if (color == COLOR_GREEN) {
        green = bri;
    } else if (color == COLOR_RED) {
        red = bri;
    } else if (color == COLOR_YELLOW) {
        green = bri;
        red = bri;
    } else {
        red = green = 0;
    }
    int midiColor = 0;
    midiColor |= (green << 4) | (red << 0);
    midiColor |= (1 << 3) | (1 << 2);
    return midiColor;
}

int Launchpad::getMidiKey(int x, int y){
    return ((y & ROWMASK) << 4) | ((x & COLMASK) << 0);
}

void Launchpad::initTemplate1(){
    buttons.assign(72, Button());
    for (int i=0 ; i<buttons.size() ; ++i){
        buttons[i].status = STATUS_TOGGLE_GREEN;
        buttons[i].brightness = 3;
        midiOut.sendNoteOn(1, getMidiKey(i%9,i/9), getMidiColor(0, 0));
    }
    
    
}
