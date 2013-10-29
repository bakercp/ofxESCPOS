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


#include <algorithm>
#include "ofImage.h"
#include "ofPixels.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/ESCPOS/ImageUtils.h"
#include "ofx/ESCPOS/BaseCodes.h"
#include "ofx/ESCPOS/BitImage.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


class DefaultBitImageCommands: public virtual ofx::IO::AbstractByteSink
{
public:
    DefaultBitImageCommands();
    virtual ~DefaultBitImageCommands();

    virtual void printPixels(const ofPixels_<unsigned char>& pixels,
                             float threshold = 0.5,
                             BaseCodes::PrintResolution printResolution = BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
                             std::size_t maxWidth = 576);


//    virtual void printImage(const ofPixels_<unsigned char>& pixels,
//                            float threshold = 0.5,
//                            BaseCodes::PrintResolution printResolution = BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
//                            std::size_t maxWidth = 576);

    // TODO: check print for DLE EOT n marks
};


} } } // namespace ofx::ESCPOS::Commands
