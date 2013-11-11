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
    ofSetFrameRate(30);

    BasicWebSocketServerSettings settings;

    server = BasicWebSocketServer::makeShared(settings);

    server->getWebSocketRoute()->registerWebSocketEvents(this);
    server->start();

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

    thisHost = Network::getThisHost();
    nodeName = Network::getNodeName();
    publicIp = Network::getPublicIPAddress();

    siteLocalInterfaces = Network::listNetworkInterfaces(Network::SITE_LOCAL);


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

       if(yOffset > ofGetWidth() - 100)
       {
           x = 20;
           y += yOffset;
       }
       else
       {
            x += xOffset;
       }
   }

    x = 20;
    y += yOffset;

    std::stringstream ss;

    ss << std::setw(10) << "Hostname: " << nodeName << std::endl;
    ss << std::setw(10) << "Public IP: " << publicIp.toString() << std::endl;
    ss << "------------------------------" << endl;

    NetworkInterface::NetworkInterfaceList::iterator iter = siteLocalInterfaces.begin();


    while(iter != siteLocalInterfaces.end())
    {

        NetworkInterface iface = (*iter);

        ss << std::endl << std::setw(18) << "IFace Name: " << iface.name();
        ss << std::endl << std::setw(18) << "Local IP: " << iface.address().toString();


        ++iter;
    }

    ss << std::endl << "PORT 8080";

    ofDrawBitmapStringHighlight(ss.str(), x, y);


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


//------------------------------------------------------------------------------
void ofApp::onWebSocketOpenEvent(WebSocketEventArgs& evt)
{
    cout << "Connection opened from: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}

//------------------------------------------------------------------------------
void ofApp::onWebSocketCloseEvent(WebSocketEventArgs& evt)
{
    cout << "Connection closed from: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}

//------------------------------------------------------------------------------
void ofApp::onWebSocketFrameReceivedEvent(WebSocketFrameEventArgs& evt)
{
    cout << "Frame from: " << evt.getConnectionRef().getClientAddress().toString() << endl;

    ofxJSONElement json;

    if(json.parse(evt.getFrameRef().getText()))
    {
        std::cout << json.toStyledString() << std::endl;

        if(json.isMember("command") && json["command"] == "PRINT")
        {
            keyPressed(' ');
        }
    }
    else
    {
        ofLogError("ofApp::onWebSocketFrameReceivedEvent") << "Unable to parse JSON: "  << evt.getFrameRef().getText();
    }
}

//------------------------------------------------------------------------------
void ofApp::onWebSocketFrameSentEvent(WebSocketFrameEventArgs& evt)
{
    // frame was sent to clients
}

//------------------------------------------------------------------------------
void ofApp::onWebSocketErrorEvent(WebSocketEventArgs& evt)
{
    cout << "Error from: " << evt.getConnectionRef().getClientAddress().toString() << endl;
}
