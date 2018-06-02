//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    printer.setup(115200,
                  ofxESCPOS::DefaultSerialPrinter::DATA_BITS_EIGHT,
                  ofxESCPOS::DefaultSerialPrinter::PAR_NONE,
                  ofxESCPOS::DefaultSerialPrinter::STOP_ONE,
                  ofxESCPOS::DefaultSerialPrinter::FLOW_CTRL_HARDWARE);

    printer.setDataTerminalReady();
    printer.setRequestToSend();
    printer.initialize();

    ofPixels pixels;
    ofLoadImage(pixels, "puppy.jpeg");



    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
    printer.flush();
//    printer.println("OF_ALIGN_HORZ_LEFT");
    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
    printer.flush();
//    printer.println("OF_ALIGN_HORZ_LEFT");
    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
    printer.flush();
//    printer.println("OF_ALIGN_HORZ_LEFT");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
//    printer.println("OF_ALIGN_HORZ_LEFT");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
//    printer.println("OF_ALIGN_HORZ_LEFT");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
//    printer.println("OF_ALIGN_HORZ_LEFT");

//    printer.printImage(pixels, OF_ALIGN_HORZ_IGNORE);
//    printer.println("OF_ALIGN_HORZ_IGNORE");

//    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
//    printer.println("OF_ALIGN_HORZ_IGNORE");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_RIGHT);
//    printer.println("OF_ALIGN_HORZ_RIGHT");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_CENTER);
//    printer.println("OF_ALIGN_HORZ_CENTER");
//
//    ///
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_IGNORE);
//    printer.println("OF_ALIGN_HORZ_IGNORE");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_LEFT);
//    printer.println("OF_ALIGN_HORZ_IGNORE");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_RIGHT);
//    printer.println("OF_ALIGN_HORZ_RIGHT");
//
//    printer.printImage(pixels, OF_ALIGN_HORZ_CENTER);
//    printer.println("OF_ALIGN_HORZ_CENTER");


//    const ofPixels_<unsigned char>& pixels,
//    ofAlignHorz alignHorz = OF_ALIGN_HORZ_LEFT,
//    float ditherThreshold = 0.5,
//    float ditherQuantWeight = 0.125,
//    BaseCodes::PrintResolution printResolution = BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
//    int printHeadWidth = 576,
//    int printHeadHeight = 24


//    printer.println("");
//    printer.println("");
//    printer.println("");
//    printer.println("");
//    printer.println("");

}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofSetColor(255);
    ofDrawBitmapStringHighlight("Press any key for a test print.", ofVec2f(20, 30));
}


void ofApp::keyPressed(int key)
{
    printer.println("");

}
