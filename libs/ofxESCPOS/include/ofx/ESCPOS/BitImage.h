//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//

//
//
//#pragma once
//
//
//#include "BaseTypes.h"
//#include "ByteBuffer.h"
//
//
//namespace ofx {
//namespace ESCPOS {
//
//
//class BitImage
//{
//public:
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
//             ByteFormat byteFormat = BYTE_FORMAT_COLUMN,
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
//
//private:
//    ByteBuffer      _buffer;
//    ByteFormat      _byteFormat;
//    unsigned char   _numBytesHorizontal;
//    unsigned char   _numBytesVertical;
//
//};
//
//
//} } // namespace ofx::ESCPOS
