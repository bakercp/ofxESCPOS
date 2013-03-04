#include "ofxBarcode.h"

#define DEFAULT_BAR_WIDTH 3
#define DEFAULT_HEIGHT_IN_DOTS 162

//------------------------------------------------------------------------------
ofxBarcode::ofxBarcode() :
type(UPC_A),
textFont(FONT_A),
textLocation(TEXT_NONE),
bHasValidData(false),
barWidth(DEFAULT_BAR_WIDTH),
height(DEFAULT_HEIGHT_IN_DOTS)
{ }

//------------------------------------------------------------------------------
ofxBarcode::ofxBarcode(ofxBarcode::Type _type) :
type(_type),
textFont(FONT_A),
textLocation(TEXT_NONE),
bHasValidData(false),
barWidth(DEFAULT_BAR_WIDTH),
height(DEFAULT_HEIGHT_IN_DOTS)
{ }

//------------------------------------------------------------------------------
ofxBarcode::ofxBarcode(ofxBarcode::Type _type, ofxBarcode::TextLocation _textLocation) :
type(_type),
textFont(FONT_A),
textLocation(_textLocation),
bHasValidData(false),
barWidth(DEFAULT_BAR_WIDTH),
height(DEFAULT_HEIGHT_IN_DOTS)
{ }

//------------------------------------------------------------------------------
ofxBarcode::ofxBarcode(ofxBarcode::Type _type, ofxBarcode::TextLocation _textLocation, const ofBuffer& _buffer) :
type(_type),
textFont(FONT_A),
textLocation(_textLocation),
bHasValidData(false),
barWidth(DEFAULT_BAR_WIDTH),
height(DEFAULT_HEIGHT_IN_DOTS)
{ setData(_buffer); }

//------------------------------------------------------------------------------
ofBuffer ofxBarcode::getData() const {
    return data;
}

//------------------------------------------------------------------------------
bool ofxBarcode::setData(const ofBuffer& _data) {
    data = _data;
    bHasValidData = validateData(type, data);
    if(!bHasValidData) {
        ofLogError("ofxBarcode::setData") << "Data is invalid for barcode type: " << type;
    }
}

//------------------------------------------------------------------------------
bool ofxBarcode::hasValidData() const {
    return bHasValidData;
}

//------------------------------------------------------------------------------
ofxBarcode::Type ofxBarcode::getType() const {
    return type;
}

//------------------------------------------------------------------------------
void ofxBarcode::setType(ofxBarcode::Type _type) {
    type = _type;
    setData(data); // resubmit data
}

//------------------------------------------------------------------------------
ofxBarcode::TextLocation ofxBarcode::getTextLocation() const {
    return textLocation;
}

//------------------------------------------------------------------------------
void ofxBarcode::setTextLocation(ofxBarcode::TextLocation _textLocation) {
    textLocation = _textLocation;
}

//------------------------------------------------------------------------------
ofxBarcode::TextFont ofxBarcode::getTextFont() const {
    return textFont;
}

//------------------------------------------------------------------------------
void ofxBarcode::setTextFont(ofxBarcode::TextFont _textFont) {
    textFont = _textFont;
}

//------------------------------------------------------------------------------
void ofxBarcode::setHeight(unsigned int _height) {
    // we don't really need an unsinged int here, but
    // perhaps it will help be future "proof"
    // ofClamp is specialized for floats
    height = CLAMP(_height,1,255); // must be between 1 and 255    
}

//------------------------------------------------------------------------------
unsigned int ofxBarcode::getHeight() const {
    return height;
}

//------------------------------------------------------------------------------
void ofxBarcode::setBarWidth(unsigned int _barWidth) {
    // we don't really need an unsinged int here, but
    // perhaps it will help be future "proof"
    // ofClamp is specialized for floats
    // Star Micronics Co. (Revision 1.00) allows 1 ≤ n ≤ 6 but 1 is not recommended
    barWidth = CLAMP(_barWidth,2,6); // must be between 2 and 6
}

//------------------------------------------------------------------------------
unsigned int ofxBarcode::getBarWidth() const {
    return barWidth;
}

//------------------------------------------------------------------------------
bool ofxBarcode::validateData(ofxBarcode::Type _type, const ofBuffer& _data) {
    size_t k = _data.size();
    
    if(k == 0) return false;
    
    const char * d = _data.getBinaryBuffer();
    
    switch (_type) {
        case UPC_A:
            if(11 <= k <= 12) {
                for(int i = 0; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }
                return true;
            } else {
                return false;
            }
        case UPC_E:
            if(6 <= k <= 8 || 11 <= k <= 12) {
                if((7 <= k <= 8 || 11 <= k <= 12) && d[0] != 48) {
                    return false;
                }
                
                // checked i = 0 above
                for(int i = 1; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }

                return true;
            } else {
                return false;
            }
        case EAN13:
            if(12 <= k <= 13) {
                for(int i = 0; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }
                return true;
            } else {
                return false;
            }
        case EAN8:
            if(7 <= k <= 8) {
                for(int i = 0; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }
                return true;
            } else {
                return false;
            }
        case CODE39:
            if(1 <= k <= 255) {
                for(int i = 0; i < k; i++) {
                    if(!(48 <= d[i] <= 57 ||
                         65 <= d[i] <= 90 ||
                               d[i] == 32 ||
                               d[i] == 36 ||
                               d[i] == 37 ||
                               d[i] == 42 ||
                               d[i] == 43 ||
                               d[i] == 45 ||
                               d[i] == 46 ||
                               d[i] == 47
                        )) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        case ITF:
            if(2 <= k <= 254 && k % 2 == 0) {
                for(int i = 0; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }
                return true;
            } else {
                return false;
            }
        case CODABAR:
            if(2 <= k <= 255) {
                if(!(65 <= d[0] <= 68 ||
                     97 <= d[0] <= 100)) return false;
                
                if(!(65 <= d[k-1] <= 68 ||
                     97 <= d[k-1] <= 100)) return false;
                
                for(int i = 1; i < k - 1; i++) {
                    if(!(48 <= d[i] <= 57  ||
                         65 <= d[i] <= 68  ||
                         97 <= d[i] <= 100 ||
                               d[i] == 36  ||
                               d[i] == 43  ||
                               d[i] == 46  ||
                               d[i] == 47  ||
                               d[i] == 58
                         )) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        case CODE93:
            if(1 <= k <= 255) {
                for(int i = 0; i < k; i++) {
                    if(!(0 <= d[i] <= 127)) return false;
                }
                return true;
            } else {
                return false;
            }
        case CODE128:
            if(2 <= k <= 255) {
                if(        d[0] != 123) return false;
                if(!(65 <= d[1] <= 67)) return false;
                
                for(int i = 2; i < k; i++) {
                    if(!(0 <= d[i] <= 127)) return false;
                }
                
                return true;
            } else {
                return false;
            }
        case GS1_128:
            if(2 <= k <= 255) {
                for(int i = 0; i < k; i++) {
                    if(!(0 <= d[i] <= 127)) return false;
                }
                return true;
            } else {
                return false;
            }
        case GS1_DATABAR_OMNIDIRECTIONAL:
            if(k == 13) {
                for(int i = 0; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }
                return true;
            } else {
                return false;
            }
        case GS1_DATABAR_TRUNCATED:
            if(k == 13) {
                for(int i = 0; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }
                return true;
            } else {
                return false;
            }
        case GS1_DATABAR_LIMITED:
            if(k == 13) {
                if(!(48 <= d[0] <= 49)) return false;
                
                for(int i = 1; i < k; i++) {
                    if(!(48 <= d[i] <= 57)) return false;
                }
                
                return true;
            } else {
                return false;
            }
        case GS1_DATABAR_EXPANDED:
            if(2 <= k <= 255) {
                int start = 0;
                
                if(3 <= k) {
                    if(!(      d[0] == 40)) return false;
                    if(!(48 <= d[1] <= 57)) return false;
                    if(!(48 <= d[2] <= 57)) return false;
                    start = 3;
                } else {
                    if(!(48 <= d[0] <= 57)) return false;
                    if(!(48 <= d[1] <= 57)) return false;
                    start = 2;
                }
                
                for(int i = start; i < k; i++) {
                    if(!(32 <= d[i] <= 34  ||
                         37 <= d[i] <= 63  ||
                         65 <= d[i] <= 90  ||
                               d[i] == 95  ||
                         97 <= d[i] <= 122 ||
                               d[i] == 123
                         )) return false;
                }
                return true;
            } else {
                return false;
            }
        default:
            ofLogError("ofxBarcode::validateData") << "Unknown barcode type: " << _type;
            return false;
    }
}


//    /// for GS K null terminated
//    enum TypeNullTerminated {
//        UPC_A = 0,
//        UPC_E = 1,
//        JAN13_EAN13 = 2,
//        JAN8_EAN8 = 3,
//        CODE39 = 4,
//        ITF = 5,
//        CODABAR = 6, /// NW-7
//    };

