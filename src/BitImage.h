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


#pragma once


#include "BaseTypes.h"
#include "ByteBuffer.h"


//namespace ofx {
//namespace ESCPOS {
//
//
//class BitImage : public BaseHasByteBuffer {
//public:
//    struct Settings;
//
//
//    enum ByteFormat {
//        BYTE_FORMAT_RASTER,
//        BYTE_FORMAT_COLUMN
//    };
//
//    enum PrintResolution {
//        RESOLUTION_8_DOTS_SINGLE_DENSITY  = 0,
//        RESOLUTION_8_DOTS_DOUBLE_DENSITY  = 1,
//        RESOLUTION_24_DOTS_SINGLE_DENSITY = 32,
//        RESOLUTION_24_DOTS_DOUBLE_DENSITY = 33
//    };
//
//    enum PrintScale {
//        SCALE_NORMAL         = 0,
//        SCALE_DOUBLE_WIDTH   = 1,
//        SCALE_DOUBLE_HEIGHT  = 2,
//        SCALE_QUADRUPLE      = 3
//    };
//
//    BitImage(const ofPixels& pixelsRef,
//             
//
//             ByteFormat byteFormat,
//             unsigned char numBytesHorizontal,
//             unsigned char numBytesVertical);
//
//    virtual ~BitImage();
//
//    ByteBuffer getBuffer() const;
//
//    ByteFormat getByteFormat() const;
//
//    unsigned char getNumBytesHorizontal() const;
//    unsigned char getNumBytesVertical() const;
//
//    struct Settings {
//
//        
//
//        Settings();
//    };
//
//
//
//private:
//    ByteBuffer      _buffer;
//    ByteFormat      _byteFormat;
//    unsigned char   _numBytesHorizontal;
//    unsigned char   _numBytesVertical;
//
//};
//
//} } // namespace ofx::ESCPOS::Commands
