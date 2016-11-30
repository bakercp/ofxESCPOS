// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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
