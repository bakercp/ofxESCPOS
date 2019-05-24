//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofPixels.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ImageUtils.h"
#include "ofx/ESCPOS/BaseCodes.h"


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
                                   float ditherThreshold = IO::ImageUtils::DEFAULT_DITHER_THRESHOLD,
                                   float ditherQuantWeight = IO::ImageUtils::DEFAULT_DITHER_QUANT_WEIGHT,
                                   BaseCodes::PrintResolution printResolution = BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
                                   int printHeadWidth = DEFAULT_PRINT_HEAD_WIDTH,
                                   int printHeadHeight = DEFAULT_PRINT_HEAD_HEIGHT);

    virtual std::size_t setPageModePrintArea(int x, int y, int width, int height);

    static const int DEFAULT_PRINT_HEAD_WIDTH = 576;
    static const int DEFAULT_PRINT_HEAD_HEIGHT = 24;

protected:
    // the user is responsible for making sure that the binary pixels are appropriate
    // for the print resolution selected.
    ///
    /// \sa https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=88
    virtual std::size_t selectBitImageMode(const ofPixels_<unsigned char>& binaryPixels,
                                           BaseCodes::PrintResolution printResolution);

    static uint8_t getHighByte(std::size_t d);
    static uint8_t getLowByte(std::size_t d);

};


} } } // namespace ofx::ESCPOS::Commands
