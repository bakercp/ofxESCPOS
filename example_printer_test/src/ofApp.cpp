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


//------------------------------------------------------------------------------
void ofApp::setup()
{

    std::vector<SerialDeviceInfo> devicesInfo = SerialDeviceUtils::getDevices("/dev/ttyUSB.*");

    devices = std::vector<DefaultSerialPrinter>(devicesInfo.size());

    for(std::size_t i = 0; i < devices.size(); ++i)
    {
        bool success = devices[i].setup(devicesInfo[i],
                                        9600,
                                        SerialDevice::DATA_BITS_EIGHT,
                                        SerialDevice::PAR_NONE,
                                        SerialDevice::STOP_ONE,
                                        SerialDevice::FLOW_CTRL_HARDWARE);

        if(success)
        {
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[i];
            devices[i].initialize();
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[i];
        }
    }
}

//------------------------------------------------------------------------------
void ofApp::update()
{
//    while(device.available() > 0)
//    {
//        uint8_t array[1024];
//
//        std::size_t n = device.readBytes(array, 1024);
//
//        for(std::size_t i = 0; i < n; ++i)
//        {
//            cout << array[i];
//        }
//    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    int xOffset = 200;
    int yOffset = 100;

    int x = 20;
    int y = 20;

    int tab = 8;

   for(std::size_t i = 0; i < devices.size(); ++i)
   {
       std::stringstream ss;

       ss << std::setw(tab) << "NAME: " << devices[i].getPortName() << endl;
       ss << std::setw(tab) <<  "DSR: " << devices[i].isDataSetReady() << endl;
       ss << std::setw(tab) <<  "CTS: " << devices[i].isClearToSend() << endl;
       ss << std::setw(tab) <<  " CD: " << devices[i].isCarrierDetected() << endl;
       ss << std::setw(tab) <<  " RI: " << devices[i].isRingIndicated();

       ofDrawBitmapStringHighlight(ss.str(), ofVec2f(x, y));

       if(y > ofGetWidth() - 100)
       {
           x = 20;
           y += yOffset;
       }
       else
       {
            x += xOffset;
       }
   }


}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (' ' == key)
    {
        for(std::size_t i = 0; i < devices.size(); ++i)
        {    
            std::string message = "Testing device " + ofToString(i) + " " + devices[i].getPortName();

            devices[i].setUpsideDown(true);

            devices[i].println("");
            devices[i].println("");

            devices[i].setFont(BaseCodes::FONT_B);
            devices[i].println("FONT_B");
            devices[i].setFont(BaseCodes::FONT_A);
            devices[i].println("FONT_A");

            devices[i].println(message);

            devices[i].setCharacterSize(BaseCodes::MAGNIFICATION_2X,
                                        BaseCodes::MAGNIFICATION_2X);

            devices[i].setUnderline(BaseCodes::UNDERLINE_NORMAL);
            devices[i].println("Thermal Printer Test");
            devices[i].setUnderline(BaseCodes::UNDERLINE_OFF);

            devices[i].setCharacterSize(BaseCodes::MAGNIFICATION_1X,
                                        BaseCodes::MAGNIFICATION_1X);


            devices[i].println("");
            devices[i].println("");

            devices[i].setUpsideDown(false);

        }
    }

}
