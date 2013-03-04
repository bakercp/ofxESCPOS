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

#include "ofFileUtils.h"
#include "ofLog.h"

class ofxBarcode {
public:
    enum TextFont {
        FONT_A, /// Character font A (12 × 24)
        FONT_B  /// Character font B (9 × 17)
    };
    
    enum TextLocation {
        TEXT_NONE            = 0, /// Not printed
        TEXT_ABOVE           = 1, /// Above the bar code
        TEXT_BELOW           = 2, /// Below the bar code
        TEXT_ABOVE_AND_BELOW = 3  /// Both above and below the bar code
    };
    
    // for use with GS K n
    enum Type {
        UPC_A                       = 65, /// http://en.wikipedia.org/wiki/Universal_Product_Code
        UPC_E                       = 66, /// http://en.wikipedia.org/wiki/Universal_Product_Code#UPC-E
        EAN13 /* aka JAN13 */       = 67, /// http://en.wikipedia.org/wiki/EAN13
        EAN8  /* aka JAN8 */        = 68, /// http://en.wikipedia.org/wiki/EAN_8
        CODE39                      = 69, /// http://en.wikipedia.org/wiki/Code39
        ITF   /* aka I25 */         = 70, /// http://en.wikipedia.org/wiki/ITF-14
        CODABAR                     = 71, /// http://en.wikipedia.org/wiki/Codabar
        CODE93                      = 72, /// http://en.wikipedia.org/wiki/Code_93
        CODE128                     = 73, /// http://en.wikipedia.org/wiki/Code_128
        GS1_128                     = 74, /// http://en.wikipedia.org/wiki/GS1-128
        GS1_DATABAR_OMNIDIRECTIONAL = 75, /// http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_TRUNCATED       = 76, /// http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_LIMITED         = 77, /// http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_EXPANDED        = 78, /// http://en.wikipedia.org/wiki/GS1_DataBar
    };

    ofxBarcode();
    ofxBarcode(Type _type);
    ofxBarcode(Type _type, TextLocation _textLocation);
    ofxBarcode(Type _type, TextLocation _textLocation, const ofBuffer& _buffer);
    
    virtual ~ofxBarcode() { }
    
    ofBuffer getData() const;
    bool setData(const ofBuffer& _buffer);

    bool hasValidData() const;
    
    Type getType() const;
    void setType(Type _type);

    TextLocation getTextLocation() const;
    void setTextLocation(TextLocation _textLocation);
    
    TextFont getTextFont() const;
    void setTextFont(TextFont _textFont);
    
    void setBarWidth(unsigned int _barWidth);
    unsigned int getBarWidth() const;

    void setHeight(unsigned int _height);
    unsigned int getHeight() const;
    
protected:
    static bool validateData(Type _type, const ofBuffer& _data);
    
    ofBuffer data;
    bool bHasValidData;
    
    Type type;
    TextLocation textLocation;
    TextFont textFont;
    
    unsigned int barWidth; // printer dependent 
    unsigned int height; // in dots
    
};