#include "ofxDefaultESCPOSPrinter.h"

//------------------------------------------------------------------------------
bool ofxDefaultESCPOSPrinter::supportsBarcodeType(ofxBarcode::Type barcodeType) {
    switch (barcodeType) {
        case ofxBarcode::UPC_A:
        case ofxBarcode::UPC_E:
        case ofxBarcode::EAN13:
        case ofxBarcode::EAN8:
        case ofxBarcode::CODE39:
        case ofxBarcode::ITF:
        case ofxBarcode::CODABAR:
        case ofxBarcode::CODE93:
        case ofxBarcode::CODE128:
        case ofxBarcode::GS1_128:
        case ofxBarcode::GS1_DATABAR_OMNIDIRECTIONAL:
        case ofxBarcode::GS1_DATABAR_TRUNCATED:
        case ofxBarcode::GS1_DATABAR_LIMITED:
        case ofxBarcode::GS1_DATABAR_EXPANDED:
            return true;
        default:
            return false;
    }
}

//------------------------------------------------------------------------------
bool ofxDefaultESCPOSPrinter::print(const ofxBarcode& barcode) {
    
}

