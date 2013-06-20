/*==============================================================================

 Copyright (c) 2013 - Christopher Baker <http://christopherbaker.net>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 =============================================================================*/


#include "exampleApp.h"

//--------------------------------------------------------------
void exampleApp::setup(){



//    grabber.initGrabber(640,480);
//    printer.setup("/dev/tty.PL2303-00001014",38400); //  home
//    printer.setup("/dev/tty.PL2303-0040121A",9600); //  small
    printer.setup("/dev/tty.PL2303-00001014",38400); //  t20
    target.set(0,0,200,100);

    img.loadImage("puppy.jpeg");
        pixels = ImageUtils::scaleAndCropTo(img.getPixelsRef(),
                                            target.getWidth(),
                                            target.getHeight(),
                                            OF_SCALEMODE_FILL);

        pixels = ImageUtils::dither(pixels);
        post.setFromPixels(pixels);

}

//--------------------------------------------------------------
void exampleApp::update(){
    grabber.update();

//    if(grabber.isFrameNew()) {
//        pixels = ImageUtils::scaleAndCropTo(grabber.getPixelsRef(),
//                                            target.getWidth(),
//                                            target.getHeight(),
//                                            OF_SCALEMODE_FILL);
//
//        pixels = ImageUtils::dither(pixels);
//        post.setFromPixels(pixels);
//    }

}

//--------------------------------------------------------------
void exampleApp::draw(){
    ofSetColor(255);

    grabber.draw(0,0);

    ofPushMatrix();
    ofTranslate(img.getWidth(), 0);

    if(post.isAllocated()) {
        post.draw(0,0);
        ofNoFill();
        ofSetColor(255,255,0);
        ofRect(0,0,post.getWidth(),post.getHeight());
        ofRect(0,0,200,200);
    }

    ofPopMatrix();

}

//--------------------------------------------------------------
void exampleApp::keyPressed(int key){

    printer.setLineSpacing(24);
    printer.print(post.getPixelsRef());//,BaseCodes::RESOLUTION_8_DOTS_SINGLE_DENSITY);
    printer.setDefaultLineSpacing();
}

//--------------------------------------------------------------
void exampleApp::keyReleased(int key){

}

//--------------------------------------------------------------
void exampleApp::mouseMoved(int x, int y ){
    
//    t = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0,1);
//    f = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0,1);
//    cout << t << "/" << f << endl;
}

//--------------------------------------------------------------
void exampleApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void exampleApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void exampleApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void exampleApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void exampleApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void exampleApp::dragEvent(ofDragInfo dragInfo){ 

}