//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofMain.h"
#include "ofxESCPOS.h"
#include "ofxGui.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

    // The printer.
    ofxESCPOS::SerialPrinter printer;

    // A camera grabber.
    ofVideoGrabber grabber;

    // The dithered image.
    ofImage ditheredImage;

    // The gui.
    ofxPanel gui;

    // Dither threshold.
    ofxFloatSlider ditherThreshold;

    // Dither quantization weight.
    ofxFloatSlider ditherQuantWeight;

    // Make sure a texture is loaded before displaying to avoid warnings.
    bool firstFrame = true;

};
