//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofPixels.h"
#include "ofRectangle.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/ESCPOS/BaseCodes.h"
#include "ofx/ESCPOS/BitImage.h"


namespace ofx {
namespace ESCPOS {


/// TODO template on ofPixels_
class ImageUtils
{
public:
    static ofPixels_<unsigned char> scaleAndCropTo(const ofPixels_<unsigned char>& pixelsRef,
                                                   std::size_t width,
                                                   std::size_t height,
                                                   ofScaleMode scaleMode = OF_SCALEMODE_FIT);

    static ofPixels_<unsigned char> dither(const ofPixels_<unsigned char>& pixels,
                                           float threshold = 0.5, // will template
                                           float quantWeight = 0.125);

//    static BitImage makeBitImage(const ofPixels& pixels,
//                                 BitImage::ByteFormat = BitImage::BYTE_FORMAT_COLUMN,
//                                 float threshold = 0.5);

    static ofPixels_<unsigned char> toGrayscale(const ofPixels_<unsigned char>& pixels);


    static ofPixels_<unsigned char> slice(const ofPixels_<unsigned char>& pixelsRef,
                                          const ofRectangle& subsection);


protected:
    static void accumulateDitherError(std::size_t x,
                                      std::size_t y,
                                      ofPixels_<unsigned char>& pixels,
                                      int qError,
                                      float* qErrors,
                                      float quantWeight)
    {
        if (x < pixels.getWidth() && y < pixels.getHeight())
        {
            qErrors[pixels.getPixelIndex(x, y)] += quantWeight * qError;
        }
    }

};


} } // namespace ofx::ESCPOS
