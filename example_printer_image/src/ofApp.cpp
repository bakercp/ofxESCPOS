//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    // We can get all of the connected serial devices using the
    // ofxIO::SerialDeviceUtils::listDevices() static method.
    //
    // auto devices = ofxIO::SerialDeviceUtils::listDevices();
    //
    // See ofxSerial documentation for more information.
    
    // Connect to the first available port.
    // Conform that this is the one you want.
    if (!printer.setup(9600))
    {
        ofLogError("ofApp::setup") << "Unable to connect to: " << printer.port();
        ofExit();
    }
    else
    {
        ofLogNotice("ofApp::setup") << "Connected to: " << printer.port();
    }
    
    // Set up hardware flow control if needed.
    printer.setDataTerminalReady();
    printer.setRequestToSend();
    
    // Initialize the printer.
    printer.initialize();
    printer.flush();
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofSetColor(255);
    ofDrawBitmapStringHighlight("Press any key for a test print.", ofVec2f(20, 30));
}


void ofApp::keyPressed(int key)
{
    ofPixels pixels;
    ofLoadImage(pixels, "puppy.jpeg");
    
    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
    printer.flush();

    printer.printImage(pixels, OF_ALIGN_HORZ_CENTER);
    printer.flush();
    
    printer.printImage(pixels, OF_ALIGN_HORZ_RIGHT);
    printer.flush();
}
