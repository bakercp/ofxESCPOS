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


#include "ofPixels.h"
#include "ofRectangle.h"
#include "BaseCodes.h"
#include "ByteBuffer.h"
#include "BitImage.h"


namespace ofx {
namespace ESCPOS {

class ImageUtils {
public:
    static ofPixels scaleAndCropTo(const ofPixels& pixelsRef,
                            int width,
                            int height,
                            ofScaleMode scaleMode = OF_SCALEMODE_FIT);
                            
    static ofPixels dither(const ofPixels& pixels,
                           float threshold = 0.5,
                           float quantWeight = 0.125);

//    static BitImage makeBitImage(const ofPixels& pixels,
//                                 BitImage::ByteFormat = BitImage::BYTE_FORMAT_COLUMN,
//                                 float threshold = 0.5);

protected:

    static void accumulateDitherError(int x,
                                      int y,
                                      ofPixels& pixels,
                                      int qError,
                                      float* qErrors,
                                      float quantWeight) {
        if(x >= 0 && x < pixels.getWidth() && y >= 0 && y < pixels.getHeight())
        {
            qErrors[pixels.getPixelIndex(x, y)] += quantWeight * qError;
        }
    }

};




} } // namespace ofx::ESCPOS
