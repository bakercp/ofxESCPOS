// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
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

    ofEnableAlphaBlending();

//    serial.setup("/dev/tty.PL2303-0030121A",9600);
//
//
//    unsigned char command[3] = { 0x1D, 0x49, 0x44 };
//    int i = serial.writeBytes(command, 3);
//
////    serial.drain();
//
//    cout << "i = " << i << endl;
//
//    while(true)
//    {
//        int b = serial.readByte();
//        if(b >= 0) {
//            cout << (char) b;
//        }
//    }
//
//    
//
//
    printer.setup("/dev/ttyUSB0",
                 115200);//,
                 // SerialDevice::DATA_BITS_EIGHT,
                 // SerialDevice::PAR_NONE,
                 // SerialDevice::STOP_ONE,
                 // SerialDevice::FLOW_CTRL_HARDWARE,
                 // SerialDevice::Timeout::simpleTimeout(1000));


   printer.setDataTerminalReady();
   printer.setRequestToSend();

   printer.initialize();
   // printer.println("Initialization!");


   // printer.getPrinterStatusRealTime();


   // printer.setInvert(true);
   // printer.println("Inverted");
   // printer.setInvert(false);

   // printer.setUnderline(BaseCodes::UNDERLINE_NORMAL);
   // printer.println("Normal Underline");
   // printer.setUnderline(BaseCodes::UNDERLINE_THICK);
   // printer.println("Thick Underline");
   // printer.setUnderline(BaseCodes::UNDERLINE_OFF);

   // printer.setEmphasis(true);
   // printer.println("Emphasis");
   // printer.setEmphasis(false);

   // printer.setDoubleStrike(true);
   // printer.println("Double Strike");
   // printer.setDoubleStrike(true);

   // printer.setFont(BaseCodes::FONT_A);
   // printer.println("FONT_A");
   // printer.setFont(BaseCodes::FONT_B);
   // printer.println("FONT_B");
   // printer.setFont(BaseCodes::FONT_C);
   // printer.println("FONT_C");
   // printer.setFont(BaseCodes::FONT_A);

   // printer.setColor(BaseCodes::COLOR_1);
   // printer.println("COLOR_1");
   // printer.setColor(BaseCodes::COLOR_2);
   // printer.println("COLOR_2");
   // printer.setColor(BaseCodes::COLOR_1);

   // printer.setUpsideDown(true);
   // printer.println("UPSIDE DOWN");
   // printer.setUpsideDown(false);

   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_1X,
   //                          BaseCodes::MAGNIFICATION_1X);
   // printer.println("MAGNIFICATION_1X");
   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_2X,
   //                          BaseCodes::MAGNIFICATION_2X);
   // printer.println("MAGNIFICATION_2X");
   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_3X,
   //                          BaseCodes::MAGNIFICATION_3X);
   // printer.println("MAGNIFICATION_3X");
   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_4X,
   //                          BaseCodes::MAGNIFICATION_4X);
   // printer.println("MAGNIFICATION_4X");
   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_5X,
   //                          BaseCodes::MAGNIFICATION_5X);
   // printer.println("MAGNIFICATION_5X");
   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_6X,
   //                          BaseCodes::MAGNIFICATION_6X);
   // printer.println("MAGNIFICATION_6X");
   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_7X,
   //                          BaseCodes::MAGNIFICATION_7X);
   // printer.println("MAGNIFICATION_7X");
   // printer.setCharacterSize(BaseCodes::MAGNIFICATION_1X,
   //                          BaseCodes::MAGNIFICATION_1X);
   // printer.println("MAGNIFICATION_1X");

   // printer.setCharacterSmoothing(true);
   // printer.println("Smooth");
   // printer.setCharacterSmoothing(false);

   // printer.setRotation(BaseCodes::ROTATE_90_CW);
   // printer.println("ROTATE_90_CW");
   // printer.setRotation(BaseCodes::ROTATE_OFF);
   // printer.println("ROTATE_OFF");


   // printer.setLineSpacing(0);
   // printer.println("Tight line spacing.");
   // printer.println("Tight line spacing.");
   // printer.println("Tight line spacing.");
   // printer.setDefaultLineSpacing();

   // printer.println("Normal line spacing.");
   // printer.println("Normal line spacing.");
   // printer.println("Normal line spacing.");
   // printer.println("Normal line spacing.println");
   // printer.println("-------");

   // printer.cut(BaseCodes::CUT_PARTIAL);
   // printer.println("Partial cut.");
   // printer.cut(BaseCodes::CUT_FULL);
   // printer.println("Full cut with 90 dots fed.");



    target = ofRectangle(0, 0, 576, 24 * 8);
//
    img.loadImage("puppy.jpeg");
    pixels = ImageUtils::scaleAndCropTo(img.getPixelsRef(),
                                        target.getWidth(),
                                        target.getHeight(),
                                        OF_SCALEMODE_FILL);

    pixels = ImageUtils::dither(pixels);

    post.setFromPixels(pixels);
    postPost.setFromPixels(pixels);

}


void ofApp::update()
{
}


void ofApp::draw()
{
    ofBackground(0);
    ofSetColor(255);
//
//    grabber.draw(0,0);
//
    ofPushMatrix();
    ofTranslate(img.getWidth(), 0);

//    ofScale(4,4);


    if(post.isAllocated())
    {
        post.draw(0,0);

        postPost.draw(400,0);

        ofNoFill();
        ofSetColor(255,255,0,200);


        for(int i = 0; i < post.getWidth(); ++i)
        {
//            ofLine(i,0,i,post.getHeight());
//            ofLine(i,0,i,post.getHeight());
        }
//        ofRect(0,0,post.getWidth(),post.getHeight());

    }
//
//
//
//
//    ofPopMatrix();


//    img.draw(100,100);
}

void ofApp::keyPressed(int key)
{

printer.printImage(pixels);

    // if(key == 'w')
    // {
    //     target.y -= 24;
    //     if(target.y < 0) target.y = 0;
    // }
    // else if(key == 's')
    // {
    //     target.y += 24;
    //     if(target.y >= target.height) target.y = target.height - 24;

    // }

   //  ofPixels p = pixels;
   //  p.crop(0, target.y, target.getWidth(), 24);
   //  postPost.setFromPixels(p);

   // printer.setLineSpacing(0);
   //  printer.printPixels(p);
   // printer.setDefaultLineSpacing();

}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
}

void ofApp::mouseDragged(int x, int y, int button)
{
}

void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::windowResized(int w, int h)
{
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
