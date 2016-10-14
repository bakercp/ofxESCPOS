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
