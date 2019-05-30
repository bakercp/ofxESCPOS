//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofPixels.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ImageUtils.h"
#include "ofx/ESCPOS/Codes.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


class DefaultBitImageCommands: public virtual IO::AbstractByteSink
{
public:
    DefaultBitImageCommands();

    virtual ~DefaultBitImageCommands();

    virtual std::size_t printImage(const ofPixels_<unsigned char>& pixels,
                                   ofAlignHorz alignHorz = OF_ALIGN_HORZ_CENTER,
                                   float ditherThreshold = IO::ImageUtils::DEFAULT_DITHER_THRESHOLD,
                                   float ditherQuantWeight = IO::ImageUtils::DEFAULT_DITHER_QUANT_WEIGHT,
                                   Codes::PrintResolution printResolution = Codes::RESOLUTION_24_DOTS_DOUBLE_DENSITY,
                                   std::size_t printHeadWidth = DEFAULT_PRINT_HEAD_WIDTH,
                                   std::size_t printHeadHeight = DEFAULT_PRINT_HEAD_HEIGHT);

    virtual std::size_t setPageModePrintArea(std::size_t x,
                                             std::size_t y,
                                             std::size_t width,
                                             std::size_t height);

    static const std::size_t DEFAULT_PRINT_HEAD_WIDTH = 576;
    static const std::size_t DEFAULT_PRINT_HEAD_HEIGHT = 24;

protected:
    // the user is responsible for making sure that the binary pixels are appropriate
    // for the print resolution selected.
    ///
    /// \sa https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=88
    virtual std::size_t selectBitImageMode(const ofPixels_<unsigned char>& binaryPixels,
                                           Codes::PrintResolution printResolution);

    static uint8_t getHighByte(std::size_t d);
    static uint8_t getLowByte(std::size_t d);

};


} } } // namespace ofx::ESCPOS::Commands
