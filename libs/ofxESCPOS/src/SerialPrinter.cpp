//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/SerialPrinter.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/Unicode.h"


namespace ofx {
namespace ESCPOS {


SerialPrinter::SerialPrinter()
{
    _cacheCodePages();
}


SerialPrinter::~SerialPrinter()
{
}


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
        ofLogError("SerialPrinter::clearUserDefinedCharacter") << "Invalid character " << character;
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
    // Disable realtime commands ...
    // https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=197#gs_lparen_cd


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
            ofLogError("SerialPrinter::getSerialPrinterStatus") << "No bytes read.";
        }

    }
    else
    {
        ofLogError("SerialPrinter::getSerialPrinterStatus") << "Number of bytes written was " << numBytesWritten;
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


bool SerialPrinter::clearBuffers()
{
    writeBytes({ Codes::DLE, Codes::DC4, 8, 1, 3, 20, 1, 6, 2, 8 });
    uint8_t buffer[3];
    return 3 == readBytes(buffer, 3)
        && buffer[0] == 55 // Header
        && buffer[1] == 37 // Identifier
        && buffer[2] == 0; // NUL
}


uint8_t SerialPrinter::modelId()
{
    if (_modelId == std::numeric_limits<uint8_t>::max())
    {
        writeBytes({ Codes::GS, 'I', 1 });
        readByte(_modelId);
    }

    return _modelId;
}


uint8_t SerialPrinter::typeId()
{
    if (_typeId == std::numeric_limits<uint8_t>::max())
    {
        writeBytes({ Codes::GS, 'I', 2 });
        readByte(_typeId);
    }

    return _typeId;
}


uint8_t SerialPrinter::versionId()
{
    if (_versionId == std::numeric_limits<uint8_t>::max())
    {
        writeBytes({ Codes::GS, 'I', 3 });
        readByte(_versionId);
    }

    return _versionId;
}


bool SerialPrinter::multibyteCharacterSupport()
{
    std::bitset<8> id = modelId();
    return id[0];
}


bool SerialPrinter::autoCutterInstalled()
{
    std::bitset<8> id = modelId();
    return id[1];
}


bool SerialPrinter::customerDisplayInstalled()
{
    std::bitset<8> id = modelId();
    return id[2];
}


bool SerialPrinter::columnEmulationMode()
{
    if (_columnEmulationMode == std::numeric_limits<uint8_t>::max())
    {
        writeBytes({ Codes::GS, 'I', 35 });
        auto mode = _readString(61, 0, 83);
        if (mode.size() == 2 && mode[0] == 35)
            _columnEmulationMode = mode[1];
        else
            _columnEmulationMode = '0';
    }

    return _columnEmulationMode != '0';
}


std::string SerialPrinter::firmwareVersion()
{
    if (_firmwareVersion.empty())
    {
        writeBytes({ Codes::GS, 'I', 65 });
        _firmwareVersion = _readString('_', 0, 83);
    }
    return _firmwareVersion;
}


std::string SerialPrinter::manufacterer()
{
    if (_manufacturer.empty())
    {
        writeBytes({ Codes::GS, 'I', 66 });
        _manufacturer = _readString('_', 0, 83);
    }
    return _manufacturer;
}


std::string SerialPrinter::model()
{
    if (_model.empty())
    {
        writeBytes({ Codes::GS, 'I', 67 });
        _model = _readString('_', 0, 83);
    }
    return _model;
}


std::string SerialPrinter::serialNumber()
{
    if (_serialNumber.empty())
    {
        writeBytes({ Codes::GS, 'I', 68 });
        _serialNumber = _readString('_', 0, 83);
    }
    return _serialNumber;
}


std::string SerialPrinter::additionalFonts()
{
    if (_additionalFonts.empty())
    {
        writeBytes({ Codes::GS, 'I', 69 });
        _additionalFonts = _readString('_', 0, 83);
    }
    return _additionalFonts;
}


void SerialPrinter::testPrint(Codes::TestPrintPattern pattern,
                              Codes::TestPrintPaper paper)
{
    writeBytes({ Codes::GS, '(', 'A', 2, 0, paper, pattern });
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


void SerialPrinter::_cacheCodePages()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::string table(256, '0');
    std::iota(table.begin(), table.end(), 0);

    for (auto codePage: _profile.codePages)
    {
        std::map<char32_t, char> page;

        TextConverter convert(to_string(codePage), "UTF-8");
        char c = 0;
        for (auto utf32: ofUTF8Iterator(convert.convert(table)))
            page[utf32] = c++;

        _codePages[codePage] = page;
    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken by function: " << duration.count() << " ms" << std::endl;


}


std::string SerialPrinter::_readString(uint8_t header,
                                       uint8_t terminator,
                                       std::size_t maxSize)
{
    std::string s = readStringUntil(terminator, maxSize);
    if (!s.empty() && s[0] == header)
        s = s.substr(1);
    if (!s.empty() && s.back() == terminator)
        s.resize(s.size() - 1);
    if (s.empty())
        s = "N/A";
    return s;
}


} } // namespace ofx::ESCPOS
