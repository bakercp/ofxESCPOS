#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    myPort.setup("/dev/tty.PL2303-000012FD", 38400);
    
    const char CTL_HT    = '\x09'; // Horizontal tab
    
    const unsigned char b = 'x';
    
    int k = 7;
    
    cout << "true? " << (6 <= k <= 8) << endl;
    
    cout << "const char CTL_HT=" << CTL_HT << "x" << endl;
    cout << "const char CTL_HT=" << static_cast<unsigned char>(CTL_HT) << "x" << endl;

    cout << b << endl;
    
//    ofBuffer buffer("this is a test\n\n\n\n\n\n\n\n");
//
//    unsigned char
//    
//    myPort.writeBytes(reinterpret_cast<unsigned char*>(buffer.getBinaryBuffer()),buffer.size());
    
    
//    myPort.flush();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}