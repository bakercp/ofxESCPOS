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
    // Confirm that this is the one you want and the correct speed.
    if (!printer.setup(115200))
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
    ofDrawBitmapStringHighlight("Press any key for a test print.", 20, 30);
}


void ofApp::keyPressed(int key)
{
    ofPixels pixels;
    ofLoadImage(pixels, "puppy.jpeg");

    // If you have printing problems, ensure that all default parameters work
    // for your device. For example depending on your printer, the print head
    // width or height may be different.

    printer.printImage(pixels,
                       OF_ALIGN_HORZ_LEFT,
                       ofxIO::ImageUtils::DEFAULT_DITHER_THRESHOLD,
                       ofxIO::ImageUtils::DEFAULT_DITHER_QUANT_WEIGHT,
                       ofxESCPOS::BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
                       ofxESCPOS::DefaultSerialPrinter::DEFAULT_PRINT_HEAD_WIDTH,
                       ofxESCPOS::DefaultSerialPrinter::DEFAULT_PRINT_HEAD_HEIGHT);

    printer.flush();

    printer.printImage(pixels, OF_ALIGN_HORZ_CENTER);
    printer.flush();
    
    printer.printImage(pixels, OF_ALIGN_HORZ_RIGHT);
    printer.flush();
}
