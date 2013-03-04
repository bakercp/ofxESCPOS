/*==============================================================================
 
 Copyright (c) 2013- Christopher Baker <http://christopherbaker.net>
 
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
 
 ==============================================================================*/

#pragma once

#include "ofxBarcode.h"


class ofxDefaultESCPOSPrinter {
public:
    ofxDefaultESCPOSPrinter() { }
    virtual ~ofxDefaultESCPOSPrinter() { }
    
    void initialize();
    
    void horizontalTab()    const;
    void lineFeed()         const;
    void formFeed()         const;
    void carriageReturn()   const;

    void printAndFeedPaper(); // (ESC J)
    void printAndFeedLines(); // (ESC d)
    
    void selectPrintMode();
    
    // layout
    void setRightSideCharacterSpacing();

    void setAbsolutePrintPosition();
    void setRelativePrintPosition();

    void selectJustification();
    void enableRotate();
    void disableRotate();

    void enableUpsideDown();
    void disableUpsideDown();
    
    // characters / character sets
    void selectUserDefinedCharacter();
    void defineUserCharacters();
    
    void selectCharacterSet();
    
    void selectCharacterCodeTable();
    
    
    void selectBitImageMode();
    
    
    // font
    void selectFont();
    void selectCharacterSize(); // GS !
    
    void enableUnderline();
    void disableUnderline();
    void enableEmphasize();
    void disableEmphasize();
    void enableDoubleStrike();
    void disableDoubleStrike();
    void setDefaultLineSpacing();
    void setLineSpacing();

    // recipt enhancement control (FS ( E)
    void resetTopBottomLogo();
    void sendTopBottomLogo();
    void setTopLogoPrinting();
    void setBottomLogoPrinting();
    void makeExtendedSettingsForTopBottomLogoPrinting();
    void enableTopBottomLogoPrinting();
    void disableTopBottomLogoPrinting();
    
    // images
    
//    void printImage(ofImage)
    
    // barcode
    virtual bool supportsBarcodeType(ofxBarcode::Type barcodeType);
    virtual bool print(const ofxBarcode& barcode);
    
    
    // NV memory
    void nvWrite();
    void nvRead();

    // ALL GS ( L / GS 8 L
//    void nvMemoryCapacity();
//    void nvDelete();
    
    
    
    // page mode
    void selectMode();
    void selectPageMode();
    void selectStandardMode();
    void pageModePrintArea();
    
    void pageModeCancelAndPrint()   const;
    void pageModePrint()            const;
    
    
    // hardware
    void enablePanelButtons();
    void disablePanelButtons();
    
    void generatePulse(bool bInRealTime = false);
    void controlBuzzer(bool bInRealTime = false);
    
    // real time
    void enableRealTimeCommands();
    void disableRealTimeCommands();
    void transmitRealTimeRequest();
    void generatePulse();
    void powerOff();
    void clearBuffers();
    void selectPeripheralDevice();
    
    // user settings mode
    // void GS ( E
    // request transmission response GS ( H
    // request transmission response GS ( H

    void setPrintSpeed(); // GS ( K
    
    // utils
    void testPrint(); // GS ( A
    

};
