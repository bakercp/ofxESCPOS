//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/SerialPrinter.h"
#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace ESCPOS {


SerialPrinter::SerialPrinter()
{
}


SerialPrinter::~SerialPrinter()
{
}


//std::string SerialPrinter::getSerialNumber()
//{
//    std::size_t b = writeBytes({
//        ESCPOS::Codes::GS,
//        'I',
//        68
//    });
//
//    std::cout << b << " bytes written." << std::endl;
//
//    uint8_t buffer[256];
//
//    std::size_t bytesRead = readBytes(buffer, 256);
//
//    std::cout << bytesRead << " bytes read." << std::endl;
//
//    return "";
//}


std::size_t SerialPrinter::initialize()
{
    return writeBytes({ Codes::ESC, '@' });
}


std::size_t SerialPrinter::print(const std::string& text)
{
    return writeBytes(text);
}


std::size_t SerialPrinter::println(const std::string& text)
{
    return writeBytes(text + "\n");
}


std::size_t SerialPrinter::clearPage()
{
    return writeByte(Codes::CAN);
}


std::size_t SerialPrinter::setRightSideCharacterSpacing(uint8_t n)
{
    return writeBytes({ Codes::ESC, ' ', n });
}


std::size_t SerialPrinter::enableUserDefinedCharacterSet(bool enable)
{
    return writeBytes({ Codes::ESC, '%', enable });
}


std::size_t SerialPrinter::uploadUserDefinedCharacterSet(const std::vector<uint8_t>& charSet)
{
    IO::ByteBuffer buffer({ Codes::ESC, '&' });
    buffer.writeBytes(charSet);

    return writeBytes(buffer.getData());
}


std::size_t SerialPrinter::clearUserDefinedCharacter(uint8_t character)
{
    if (character > 126 || character < 32)
    {
        ofLogError("CharacterCommands::clearUserDefinedCharacter") << "Invalid character " << character;
        return 0;
    }

    return writeBytes({ Codes::ESC, '?', character });
}


std::size_t SerialPrinter::setCharacterSet(Codes::CharacterSet charSet)
{
    return writeBytes({ Codes::ESC, 'R', charSet });
}


std::size_t SerialPrinter::setCharacterCodePage(Codes::CodePage codePage)
{
    return writeBytes({ Codes::ESC, 't', codePage });
}


std::size_t SerialPrinter::setPrintMode(uint8_t modeByte)
{
    return writeBytes({ Codes::ESC, '!', modeByte });
}


std::size_t SerialPrinter::setInvert(bool enable)
{
    return writeBytes({ Codes::GS, 'B', enable });
}


std::size_t SerialPrinter::setUnderline(Codes::TextUnderline underline)
{
    return writeBytes({ Codes::ESC, '-', underline });
}


std::size_t SerialPrinter::setEmphasis(bool enable)
{
    return writeBytes({ Codes::ESC, 'E', enable });
}


std::size_t SerialPrinter::setDoubleStrike(bool enable)
{
    return writeBytes({ Codes::ESC, 'G', enable });
}


std::size_t SerialPrinter::setFont(Codes::TextFont font)
{
    return writeBytes({ Codes::ESC, 'M', font });
}


std::size_t SerialPrinter::setColor(Codes::TextColor color)
{
    return writeBytes({ Codes::ESC, 'r', color });
}

std::size_t SerialPrinter::setAlign(Codes::TextAlignment align)
{
    return writeBytes({ Codes::ESC,'a',align});
}


std::size_t SerialPrinter::setUpsideDown(bool enable)
{
    return writeBytes({ Codes::ESC, '{', enable });
}


std::size_t SerialPrinter::setCharacterSize(Codes::TextMagnification horizontal,
                                            Codes::TextMagnification vertical)
{
    return writeBytes({
        Codes::GS,
        '!',
        static_cast<uint8_t>((horizontal << 4) | (vertical))
    });
}


std::size_t SerialPrinter::setCharacterSmoothing(bool enable)
{
    return writeBytes({ Codes::GS, 'b', enable });
}


std::size_t SerialPrinter::setRotation(Codes::TextRotate textRotate)
{
    return writeBytes({ Codes::ESC, 'V', textRotate });
}


std::size_t SerialPrinter::printImage(const ofPixels_<unsigned char>& pixels,
                                      ofAlignHorz alignHorz,
                                      float ditherThreshold,
                                      float ditherQuantWeight,
                                      Codes::PrintResolution printResolution)
{

    std::size_t numVerticalDots = 0;
    std::size_t maxHorizontalDots = 0;

    switch (printResolution)
    {
        case Codes::RESOLUTION_8_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = _profile.printHeadWidthPixels / 2;
            numVerticalDots = 8;
            break;
        case Codes::RESOLUTION_8_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = _profile.printHeadWidthPixels;
            numVerticalDots = 8;
            break;
        case Codes::RESOLUTION_24_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = _profile.printHeadWidthPixels / 2;
            numVerticalDots = 24;
            break;
        case Codes::RESOLUTION_24_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = _profile.printHeadWidthPixels;
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
    totalBytesWritten += writeByte(Codes::ESC);
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
        totalBytesWritten += writeBytes({ Codes::ESC, '3', static_cast<uint8_t>(numVerticalDots * 2) }); // TODO 2 * works for double vert density

        bandBuffer.clear();
        toPrint.cropTo(bandBuffer, 0, y, width, numVerticalDots);
        totalBytesWritten += selectBitImageMode(bandBuffer, printResolution);
        totalBytesWritten += writeByte(Codes::LF); // feed a line

        // set vertical displacement back to normal
        // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=19
        totalBytesWritten += writeBytes({ Codes::ESC, '2' });
    }

    // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=10
    // totalBytesWritten += writeByte(Codes::LF); // feed a line

    // Print and return to standard mode, while in page mode.
    // https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=12
    totalBytesWritten += writeByte(Codes::FF);

    return totalBytesWritten;
}


std::size_t SerialPrinter::setPageModePrintArea(std::size_t x,
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
    return writeBytes({ Codes::ESC, 'W', xL, xH, yL, yH, dXL, dXH, dYL, dYH });
}



std::size_t SerialPrinter::cut(Codes::PaperCut type,
                               uint8_t numDotsToFeed)
{
    if (numDotsToFeed > 0)
        return writeBytes({ Codes::GS, 'V', type });

    return writeBytes({ Codes::GS, 'V',
        static_cast<uint8_t>(type + 'A'),
        numDotsToFeed }); // shift -> A/B
}



std::size_t SerialPrinter::setDefaultLineSpacing()
{
    return writeBytes({ Codes::ESC, 50 });
}


std::size_t SerialPrinter::setLineSpacing(uint8_t n)
{
    return writeBytes({ Codes::ESC, 51, n });
}


std::size_t SerialPrinter::getPrinterStatusRealTime()
{
    std::size_t numBytesWritten = writeBytes({
        Codes::DLE,
        Codes::EOT,
        Codes::STATUS_PRINTER
    });

    if (3 == numBytesWritten)
    {
        uint8_t data;

        //        pSerial->waitByteTimes(3);



        std::size_t numBytesRead = readByte(data);

        if (numBytesRead > 0)
        {
            std::bitset<8> bits(data);
            // std::cout << "Data Read: " << bits << std::endl;

            bool isDrawerKickoutHigh = bits[2];
            bool isOnline = bits[3];

            // package these

        }
        else
        {
            ofLogError("PrinterStatusCommands::getPrinterStatus") << "No bytes read.";
        }

    }
    else
    {
        ofLogError("PrinterStatusCommands::getPrinterStatus") << "Number of bytes written was " << numBytesWritten;
    }

    return numBytesWritten;
}


std::size_t SerialPrinter::getOfflineStatus()
{
    return 0; // TBI
}


std::size_t SerialPrinter::getErrorStatus()
{
    return 0; // TBI
}


std::size_t SerialPrinter::getPaperStatus()
{
    return 0; // TBI
}





std::size_t SerialPrinter::selectBitImageMode(const ofPixels_<unsigned char>& binaryPixels,
                                              Codes::PrintResolution printResolution)
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
    buffer.push_back(Codes::ESC);
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


uint8_t SerialPrinter::getHighByte(std::size_t d)
{
    return uint8_t(d >> 8);
}


uint8_t SerialPrinter::getLowByte(std::size_t d)
{
    return uint8_t(d & 0xFF);
}


} } // namespace ofx::ESCPOS
