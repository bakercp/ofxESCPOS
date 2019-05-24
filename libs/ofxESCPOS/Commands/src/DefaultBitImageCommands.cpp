//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "DefaultBitImageCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


DefaultBitImageCommands::DefaultBitImageCommands()
{
}


DefaultBitImageCommands::~DefaultBitImageCommands()
{
}


std::size_t DefaultBitImageCommands::printImage(const ofPixels_<unsigned char>& pixels,
                                                ofAlignHorz alignHorz,
                                                float ditherThreshold,
                                                float ditherQuantWeight,
                                                BaseCodes::PrintResolution printResolution,
                                                std::size_t printHeadWidth,
                                                std::size_t printHeadHeight)
{

    std::size_t numVerticalDots = 0;
    std::size_t maxHorizontalDots = 0;

    switch (printResolution)
    {
        case BaseCodes::RESOLUTION_8_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = printHeadWidth / 2;
            numVerticalDots = 8;
            break;
        case BaseCodes::RESOLUTION_8_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = printHeadWidth;
            numVerticalDots = 8;
            break;
        case BaseCodes::RESOLUTION_24_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = printHeadWidth / 2;
            numVerticalDots = 24;
            break;
        case BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = printHeadWidth;
            numVerticalDots = 24;
            break;
    }

    std::size_t totalBytesWritten = 0;

    ofRectangle imageRect(0, 0, pixels.getWidth(), pixels.getHeight());
    ofRectangle rectangle(0, 0, maxHorizontalDots, pixels.getHeight());

    imageRect.scaleTo(rectangle,
                      OF_ASPECT_RATIO_KEEP,
                      alignHorz,
                      OF_ALIGN_VERT_TOP,
                      alignHorz,
                      OF_ALIGN_VERT_TOP);

    std::size_t width = std::size_t(rectangle.getWidth());
    std::size_t height = std::size_t(imageRect.getHeight());

    // ensure vertical res.
    if (height != numVerticalDots)
    {
        std::size_t remainder = height % numVerticalDots;

        if (remainder != 0)
        {
            height = height + numVerticalDots - remainder;
        }
    }

    ofPixels pix = pixels; // get a copy
    ofPixels toPrint;

    toPrint.allocate(width, height, pix.getNumChannels());
    toPrint.setColor(ofColor(255));

    pix.resize(std::size_t(imageRect.getWidth()),
               std::size_t(imageRect.getHeight()));

    pix.pasteInto(toPrint,
                  std::size_t(imageRect.getX()),
                  std::size_t(imageRect.getY()));

    toPrint = IO::ImageUtils::dither(toPrint,
                                     ditherThreshold,
                                     ditherQuantWeight);

    ofPixels bandBuffer;

    bandBuffer.allocate(toPrint.getWidth(),
                        numVerticalDots,
                        toPrint.getNumChannels());

    // Enter Page Mode
    // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=193
    totalBytesWritten += writeByte(BaseCodes::ESC);
    totalBytesWritten += writeByte('L');

    // set the print area / origin
    totalBytesWritten += setPageModePrintArea(0,
                                              0,
                                              toPrint.getWidth(),
                                              toPrint.getHeight() * 2); // TODO 2 * works for double vert density

    for (std::size_t y = 0; y < height; y += numVerticalDots)
    {
        // set the vertical displacement
        // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=20
        std::vector<uint8_t> command = { BaseCodes::ESC, '3', static_cast<uint8_t>(numVerticalDots * 2) }; // TODO 2 * works for double vert density
        totalBytesWritten += writeBytes(command);

        bandBuffer.clear();
        toPrint.cropTo(bandBuffer, 0, y, width, numVerticalDots);
        totalBytesWritten += selectBitImageMode(bandBuffer, printResolution);
        totalBytesWritten += writeByte(BaseCodes::LF); // feed a line

        // set vertical displacement back to normal
        // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=19
        const uint8_t command0[2] = { BaseCodes::ESC, '2' };
        totalBytesWritten += writeBytes(command0, 2);
    }

    // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=10
    // totalBytesWritten += writeByte(BaseCodes::LF); // feed a line

    // Print and return to standard mode, while in page mode.
    // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=12
    totalBytesWritten += writeByte(BaseCodes::FF);

    return totalBytesWritten;
}


std::size_t DefaultBitImageCommands::setPageModePrintArea(std::size_t x,
                                                          std::size_t y,
                                                          std::size_t width,
                                                          std::size_t height)
{
    uint8_t xL = getLowByte(x);
    uint8_t xH = getHighByte(x);

    uint8_t yL = getLowByte(y);
    uint8_t yH = getHighByte(y);

    uint8_t dXL = getLowByte(width);
    uint8_t dXH = getHighByte(width);

    uint8_t dYL = getLowByte(height);
    uint8_t dYH = getHighByte(height);

    // Set print area in Page mode
    // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=56
    const uint8_t command[10] = { BaseCodes::ESC, 'W', xL, xH, yL, yH, dXL, dXH, dYL, dYH };

    return writeBytes(command, 10);
}


std::size_t DefaultBitImageCommands::selectBitImageMode(const ofPixels_<unsigned char>& binaryPixels,
                                                        BaseCodes::PrintResolution printResolution)
{
    // width = nL + (nH * 256)
    // nH is the HIGH part of the WIDTH VALUE.
    // nL is the LOW part of the WIDTH VALUE.
    // nH will always be 0 for values less that 256 (1 byte)
    uint8_t nH = getHighByte(binaryPixels.getWidth());
    uint8_t nL = getLowByte(binaryPixels.getWidth());

    std::vector<uint8_t> buffer;

    // Select bit image mode.
    // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=88
    buffer.push_back(BaseCodes::ESC);
    buffer.push_back('*');

    buffer.push_back(printResolution);
    buffer.push_back(nL);
    buffer.push_back(nH);

    uint8_t currentByte = 0;
    std::size_t bitIndex = 0;

    for (std::size_t x = 0; x < binaryPixels.getWidth(); ++x)
    {
        currentByte = 0;
        bitIndex = 0;

        // Pack pixels into bytes.
        for (std::size_t y = 0; y < binaryPixels.getHeight(); ++y)
        {
            bool binaryValue = binaryPixels[binaryPixels.getPixelIndex(x, y)] < ofColor_<unsigned char>::limit() / 2;

            currentByte |= binaryValue << (7 - bitIndex);

            bitIndex++;

            if (8 == bitIndex)
            {
                buffer.push_back(currentByte);
                currentByte = 0;
                bitIndex = 0;
            }
        }
    }

    return writeBytes(buffer);
}


uint8_t DefaultBitImageCommands::getHighByte(std::size_t d)
{
    return uint8_t(d >> 8);
}


uint8_t DefaultBitImageCommands::getLowByte(std::size_t d)
{
    return uint8_t(d & 0xFF);
}


} } } // namespace ofx::ESCPOS::Commands
