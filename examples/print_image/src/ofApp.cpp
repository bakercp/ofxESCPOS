//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    // Set up the gui parameters.
    gui.setup();
    gui.add(ditherThreshold.setup("ditherThreshold", ofxIO::ImageUtils::DEFAULT_DITHER_THRESHOLD, 0, 6));
    gui.add(ditherQuantWeight.setup("ditherQuantWeight", ofxIO::ImageUtils::DEFAULT_DITHER_QUANT_WEIGHT, 0, 0.2));

    // Enable the grabber.
    grabber.setup(640, 480);

    // Set up printer parameters.
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

    ofBackground(0);
}


void ofApp::update()
{
    grabber.update();

    if (grabber.isFrameNew() || firstFrame)
    {
        ditheredImage = ofxIO::ImageUtils::dither(grabber.getPixels(),
                                                  ditherThreshold,
                                                  ditherQuantWeight);
        firstFrame = false;
    }
}


void ofApp::draw()
{
    ofSetColor(255);

    grabber.draw(0, 0);
    ditheredImage.draw(grabber.getWidth(), 0);

    gui.draw();
    ofDrawBitmapStringHighlight("Press (spacebar) to print the image.", 20, ofGetHeight() - 20);
}


void ofApp::keyPressed(int key)
{
    if (key != ' ')
        return;

    // If you have printing problems, ensure that all default parameters work
    // for your device. For example depending on your printer, the print head
    // width or height may be different.

    printer.printImage(ditheredImage.getPixels(),
                       OF_ALIGN_HORZ_CENTER,
                       ditherThreshold,
                       ditherQuantWeight,
                       ofxESCPOS::BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
                       ofxESCPOS::DefaultSerialPrinter::DEFAULT_PRINT_HEAD_WIDTH,
                       ofxESCPOS::DefaultSerialPrinter::DEFAULT_PRINT_HEAD_HEIGHT);

    printer.flush();
    printer.cut();
}

