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
//    printer.setup("/dev/tty.PL2303-0030121A");

    printer.setup("/dev/ttyUSB0");

    printer.initialize();
    printer.println("Initialization!");

    printer.setInvert(true);
    printer.println("Inverted");
    printer.setInvert(false);

    printer.setUnderline(BaseCodes::UNDERLINE_NORMAL);
    printer.println("Normal Underline");
    printer.setUnderline(BaseCodes::UNDERLINE_THICK);
    printer.println("Thick Underline");
    printer.setUnderline(BaseCodes::UNDERLINE_OFF);

    printer.setEmphasis(true);
    printer.println("Emphasis");
    printer.setEmphasis(false);

    printer.setDoubleStrike(true);
    printer.println("Double Strike");
    printer.setDoubleStrike(true);

    printer.setFont(BaseCodes::FONT_A);
    printer.println("FONT_A");
    printer.setFont(BaseCodes::FONT_B);
    printer.println("FONT_B");
    printer.setFont(BaseCodes::FONT_C);
    printer.println("FONT_C");
    printer.setFont(BaseCodes::FONT_A);

    printer.setColor(BaseCodes::COLOR_1);
    printer.println("COLOR_1");
    printer.setColor(BaseCodes::COLOR_2);
    printer.println("COLOR_2");
    printer.setColor(BaseCodes::COLOR_1);

    printer.setUpsideDown(true);
    printer.println("UPSIDE DOWN");
    printer.setUpsideDown(false);

    printer.setCharacterSize(BaseCodes::MAGNIFICATION_1X,
                             BaseCodes::MAGNIFICATION_1X);
    printer.println("MAGNIFICATION_1X");
    printer.setCharacterSize(BaseCodes::MAGNIFICATION_2X,
                             BaseCodes::MAGNIFICATION_2X);
    printer.println("MAGNIFICATION_2X");
    printer.setCharacterSize(BaseCodes::MAGNIFICATION_3X,
                             BaseCodes::MAGNIFICATION_3X);
    printer.println("MAGNIFICATION_3X");
    printer.setCharacterSize(BaseCodes::MAGNIFICATION_4X,
                             BaseCodes::MAGNIFICATION_4X);
    printer.println("MAGNIFICATION_4X");
    printer.setCharacterSize(BaseCodes::MAGNIFICATION_5X,
                             BaseCodes::MAGNIFICATION_5X);
    printer.println("MAGNIFICATION_5X");
    printer.setCharacterSize(BaseCodes::MAGNIFICATION_6X,
                             BaseCodes::MAGNIFICATION_6X);
    printer.println("MAGNIFICATION_6X");
    printer.setCharacterSize(BaseCodes::MAGNIFICATION_7X,
                             BaseCodes::MAGNIFICATION_7X);
    printer.println("MAGNIFICATION_7X");
    printer.setCharacterSize(BaseCodes::MAGNIFICATION_1X,
                             BaseCodes::MAGNIFICATION_1X);
    printer.println("MAGNIFICATION_1X");

    printer.setCharacterSmoothing(true);
    printer.println("Smooth");
    printer.setCharacterSmoothing(false);

    printer.setRotation(BaseCodes::ROTATE_90_CW);
    printer.println("ROTATE_90_CW");
    printer.setRotation(BaseCodes::ROTATE_OFF);
    printer.println("ROTATE_OFF");


    printer.setLineSpacing(0);
    printer.println("Tight line spacing.");
    printer.println("Tight line spacing.");
    printer.println("Tight line spacing.");
    printer.setDefaultLineSpacing();

    printer.println("Normal line spacing.");
    printer.println("Normal line spacing.");
    printer.println("Normal line spacing.");
    printer.println("Normal line spacing.println");
    printer.println("-------");

    printer.cut(BaseCodes::CUT_PARTIAL);
    printer.println("Partial cut.");
    printer.cut(BaseCodes::CUT_FULL);
    printer.println("Full cut with 90 dots fed.");



//
//    img.loadImage("puppy.jpeg");
//    pixels = ImageUtils::scaleAndCropTo(img.getPixelsRef(),
//                                        target.getWidth(),
//                                        target.getHeight(),
//                                        OF_SCALEMODE_FILL);

//    pixels = ImageUtils::dither(pixels);

    ofPixels pix;
    pixels.allocate(200,12,OF_PIXELS_MONO);

    for(int x = 0; x < pixels.getWidth(); x++)
    {
        for(int y = 0; y < pixels.getHeight(); y++)
        {
            pixels.getPixels()[pixels.getPixelIndex(x,y)] = (y % 5) || (x % 5) == 0 ? 0 : 255;
        }
    }

    post.setFromPixels(pixels);


}


void ofApp::update()
{
////    if(grabber.isFrameNew()) {
////        pixels = ImageUtils::scaleAndCropTo(grabber.getPixelsRef(),
////                                            target.getWidth(),
////                                            target.getHeight(),
////                                            OF_SCALEMODE_FILL);
////
////        pixels = ImageUtils::dither(pixels);
////        post.setFromPixels(pixels);
////    }

}


void ofApp::draw()
{
    ofSetColor(255);
//
//    grabber.draw(0,0);
//
    ofPushMatrix();
    ofTranslate(img.getWidth(), 0);

    if(post.isAllocated())
    {
        post.draw(0,0);
        ofNoFill();
        ofSetColor(255,255,0);
        ofRect(0,0,post.getWidth(),post.getHeight());
        ofRect(0,0,200,200);
    }

    ofPopMatrix();

}

void ofApp::keyPressed(int key)
{
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