//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofMain.h"
#include "ofxESCPOS.h"


using namespace ofx;


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();

    void keyPressed(int key);

    ESCPOS::DefaultSerialPrinter printer;

};
