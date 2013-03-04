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

class ofxBaseByteReadWrite {
public:
    ofxBaseByteReadWrite() { }
    virtual ~ofxBaseByteReadWrite() { }
   // void int readBytes
    
    virtual int readByte() = 0;  // returns -1 on no read or error...
    virtual int readBytes(unsigned char * buffer, int length) = 0;

    virtual int writeBytes(unsigned char * buffer, int length) = 0;
    virtual bool writeByte(unsigned char singleByte) = 0;

    virtual int	available() = 0;

    int readBytes(ofBuffer& _buffer) {
        return readBytes(reinterpret_cast<unsigned char*>(_buffer.getBinaryBuffer()),_buffer.size());
    }
    
    int writeBytes(const ofBuffer& _buffer) {
        ofBuffer buffer(_buffer);
        return writeBytes(reinterpret_cast<unsigned char*>(buffer.getBinaryBuffer()),buffer.size());
    }

};

class ofxBaseESCPOSCodes {
public:
    ofxBaseESCPOSCodes() { }
    virtual ~ofxBaseESCPOSCodes() { }

    enum ControlCodes {
        NUL = 0,  // 0x00
        EOT = 4,  // 0x
        ENQ = 5,  // 0x
        HT  = 9,  // 0x
        LF  = 10, // 0x
        FF  = 12, // 0x
        CR  = 13, // 0x
        DLE = 16, // 0x
        DC4 = 20, // 0x
        CAN = 24, // 0x
        ESC = 27, // 0x
        FS  = 28, // 0x
        GS  = 29  // 0x
    };

    enum CharacterSet {
        USA              = 0,
        FRANCE           = 1,
        GERMANY          = 2,
        UNITED_KINGDOM   = 3,
        DENMARK_I        = 4,
        SWEDEN           = 5,
        ITALY            = 6,
        SPAIN_I          = 7,
        JAPAN            = 8,
        NORWAY           = 9,
        DENMARK_II       = 10,
        SPAIN_II         = 11,
        LATIN_AMERICA    = 12,
        KOREA            = 13,
        SLOVENIA_CROATIA = 14,
        CHINA            = 15,
        VIETNAM          = 16,
        ARABIA           = 17
    };

    enum CodePage {
        PC437       = 0,   /// USA, Standard Europe http://en.wikipedia.org/wiki/Code_page_437
        Katakana    = 1,   /// Katakana
        PC850       = 2,   /// Multilingual         http://en.wikipedia.org/wiki/Code_page_850
        PC860       = 3,   /// Portuguese           http://en.wikipedia.org/wiki/Code_page_860
        PC863       = 4,   /// Canadian-French      http://en.wikipedia.org/wiki/Code_page_863
        PC865       = 5,   /// Nordic               http://en.wikipedia.org/wiki/Code_page_865
        PC851       = 11,  /// Greek                http://en.wikipedia.org/wiki/Code_page_851
        PC853       = 12,  /// Turkish              http://en.wikipedia.org/wiki/Code_page_853
        PC857       = 13,  /// Turkish              http://en.wikipedia.org/wiki/Code_page_857
        PC737       = 14,  /// Greek                http://en.wikipedia.org/wiki/Code_page_737
        ISO8859_7   = 15,  /// Greek                http://en.wikipedia.org/wiki/ISO/IEC_8859-7
        WPC1252     = 16,  /// Windows-1252         http://en.wikipedia.org/wiki/Windows-1252
        PC866       = 17,  /// Cyrillic #2          http://en.wikipedia.org/wiki/Code_page_866
        PC852       = 18,  /// Latin2               http://en.wikipedia.org/wiki/Code_page_852
        PC858       = 19,  /// Euro                 http://en.wikipedia.org/wiki/Code_page_858
        KU42        = 20,  /// Thai                 http://en.wikipedia.org/wiki/Code_page_866
        TIS11       = 21,  /// Thai
        TIS18       = 26,  /// Thai
        TCVN_3_I    = 30,  /// Vietnamese (lower case)
        TCVN_3_II   = 31,  /// Vietnamese (upper case)
        PC720       = 32,  /// Arabic               http://en.wikipedia.org/wiki/Code_page_720
        PC775       = 33,  /// Baltic Rim           http://en.wikipedia.org/wiki/Code_page_775
        PC855       = 34,  /// Cyrillic             http://en.wikipedia.org/wiki/Code_page_855
        PC861       = 35,  /// Icelandic            http://en.wikipedia.org/wiki/Code_page_861
        PC862       = 36,  /// Hebrew               http://en.wikipedia.org/wiki/Code_page_862
        PC864       = 37,  /// Arabic               http://en.wikipedia.org/wiki/Code_page_864
        PC869       = 38,  /// Greek                http://en.wikipedia.org/wiki/Code_page_869
        ISO8859_2   = 39,  /// Latin2               http://en.wikipedia.org/wiki/ISO/IEC_8859-2
        ISO8859_15  = 40,  /// Latin9               http://en.wikipedia.org/wiki/ISO/IEC_8859-15
        PC1098      = 41,  /// Farsi                http://www-01.ibm.com/software/globalization/ccsid/ccsid1098.html
        PC1118      = 42,  /// Lithuanian           
        PC1119      = 43,  /// Lithuanian
        PC1125      = 44,  /// Ukrainian            http://ascii-table.com/codepage.php?1125
        WPC1250     = 45,  /// Latin2               http://en.wikipedia.org/wiki/Windows-1250
        WPC1251     = 46,  /// Cyrillic             http://en.wikipedia.org/wiki/Windows-1251
        WPC1253     = 47,  /// Greek                http://en.wikipedia.org/wiki/Windows-1253
        WPC1254     = 48,  /// Turkish              http://en.wikipedia.org/wiki/Windows-1254
        WPC1255     = 49,  /// Hebrew               http://en.wikipedia.org/wiki/Windows-1255
        WPC1256     = 50,  /// Arabic               http://en.wikipedia.org/wiki/Windows-1256
        WPC1257     = 51,  /// Baltic Rim           http://en.wikipedia.org/wiki/Windows-1257
        WPC1258     = 52,  /// Vietnamese           http://en.wikipedia.org/wiki/Windows-1258
        KZ_1048     = 53,  /// Kazakhstan           http://www.iana.org/assignments/charset-reg/KZ-1048
        USER_PAGE   = 255  /// User-defined page
    };

};

class ofxBaseThermalPrinter : public ofxBaseByteReadWrite {
public:
    ofxBaseThermalPrinter() { };
    virtual ~ofxBaseThermalPrinter() { };
        
    
    virtual void printAndFeed(int numLines = 0) = 0;

    
};