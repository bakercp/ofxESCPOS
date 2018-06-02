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
    if (!printer.setup(38400))
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
    printer.setInvert(true);
    printer.println("Inverted");
    printer.setInvert(false);

    printer.setUnderline(ESCPOS::BaseCodes::UNDERLINE_NORMAL);
    printer.println("Normal Underline");
    printer.setUnderline(ESCPOS::BaseCodes::UNDERLINE_THICK);
    printer.println("Thick Underline");
    printer.setUnderline(ESCPOS::BaseCodes::UNDERLINE_OFF);

    printer.setEmphasis(true);
    printer.println("Emphasis");
    printer.setEmphasis(false);

    printer.setDoubleStrike(true);
    printer.println("Double Strike");
    printer.setDoubleStrike(true);

    printer.setFont(ESCPOS::BaseCodes::FONT_A);
    printer.println("FONT_A");
    printer.setFont(ESCPOS::BaseCodes::FONT_B);
    printer.println("FONT_B");
    printer.setFont(ESCPOS::BaseCodes::FONT_C);
    printer.println("FONT_C");
    printer.setFont(ESCPOS::BaseCodes::FONT_A);

    printer.setColor(ESCPOS::BaseCodes::COLOR_1);
    printer.println("COLOR_1");
    printer.setColor(ESCPOS::BaseCodes::COLOR_2);
    printer.println("COLOR_2");
    printer.setColor(ESCPOS::BaseCodes::COLOR_1);

    printer.setUpsideDown(true);
    printer.println("UPSIDE DOWN");
    printer.setUpsideDown(false);

    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_1X,
                             ESCPOS::BaseCodes::MAGNIFICATION_1X);
    printer.println("MAGNIFICATION_1X");
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_2X,
                             ESCPOS::BaseCodes::MAGNIFICATION_2X);
    printer.println("MAGNIFICATION_2X");
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_3X,
                             ESCPOS::BaseCodes::MAGNIFICATION_3X);
    printer.println("MAGNIFICATION_3X");
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_4X,
                             ESCPOS::BaseCodes::MAGNIFICATION_4X);
    printer.println("MAGNIFICATION_4X");
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_5X,
                             ESCPOS::BaseCodes::MAGNIFICATION_5X);
    printer.println("MAGNIFICATION_5X");
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_6X,
                             ESCPOS::BaseCodes::MAGNIFICATION_6X);
    printer.println("MAGNIFICATION_6X");
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_7X,
                             ESCPOS::BaseCodes::MAGNIFICATION_7X);
    printer.println("MAGNIFICATION_7X");
    printer.setCharacterSize(ESCPOS::BaseCodes::MAGNIFICATION_1X,
                             ESCPOS::BaseCodes::MAGNIFICATION_1X);
    printer.println("MAGNIFICATION_1X");

    printer.setCharacterSmoothing(true);
    printer.println("Smooth");
    printer.setCharacterSmoothing(false);

    printer.setRotation(ESCPOS::BaseCodes::ROTATE_90_CW);
    printer.println("ROTATE_90_CW");
    printer.setRotation(ESCPOS::BaseCodes::ROTATE_OFF);
    printer.println("ROTATE_OFF");

    printer.setAlign(ESCPOS::BaseCodes::ALIGN_RIGHT);
    printer.println("ALIGN_RIGHT");
    printer.setAlign(ESCPOS::BaseCodes::ALIGN_CENTER);
    printer.println("ALIGN_CENTER");
    printer.setAlign(ESCPOS::BaseCodes::ALIGN_LEFT);
    printer.println("ALIGN_LEFT");

    printer.setLineSpacing(0);
    printer.println("Tight line spacing.");
    printer.println("Tight line spacing.");
    printer.println("Tight line spacing.");

    printer.setDefaultLineSpacing();
    printer.println("Normal line spacing.");
    printer.println("Normal line spacing.");
    printer.println("Normal line spacing.");
    printer.println("-------");

    printer.cut(ESCPOS::BaseCodes::CUT_PARTIAL);
    printer.println("Partial cut.");
    printer.cut(ESCPOS::BaseCodes::CUT_FULL);
    printer.println("Full cut with 90 dots fed.");

}
