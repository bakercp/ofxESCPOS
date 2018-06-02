//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <algorithm>
#include <cstring>
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


class DefaultBitImageCommands: public virtual IO::AbstractByteSink
{
public:
    DefaultBitImageCommands();

    virtual ~DefaultBitImageCommands();

    virtual std::size_t printImage(const ofPixels_<unsigned char>& pixels,
                                   ofAlignHorz alignHorz = OF_ALIGN_HORZ_LEFT,
                                   float ditherThreshold = 0.5,
                                   float ditherQuantWeight = 0.125,
                                   BaseCodes::PrintResolution printResolution = BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
                                   int printHeadWidth = 576,
                                   int printHeadHeight = 24);

    virtual std::size_t setPageModePrintArea(int x, int y, int width, int height);

protected:
    // the user is responsible for making sure that the binary pixels are appropriate
    // for the print resolution selected.
    virtual std::size_t selectBitImageMode(const ofPixels_<unsigned char>& binaryPixels,
                                           BaseCodes::PrintResolution printResolution);

    static uint8_t getHighByte(std::size_t d);
    static uint8_t getLowByte(std::size_t d);

};


} } } // namespace ofx::ESCPOS::Commands
