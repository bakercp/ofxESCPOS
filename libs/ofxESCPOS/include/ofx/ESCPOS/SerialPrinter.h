//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <string>
#include "ofPixels.h"
#include "ofRectangle.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ImageUtils.h"
#include "ofx/IO/SerialDevice.h"
#include "ofx/ESCPOS/Codes.h"


namespace ofx {
namespace ESCPOS {


class SerialPrinter:
    public IO::SerialDevice
{
public:
    SerialPrinter();

    virtual ~SerialPrinter();

    virtual std::size_t initialize();

    virtual std::size_t print(const std::string& text);
    virtual std::size_t println(const std::string& text);

    /// Character commands.
    virtual std::size_t clearPage();
    virtual std::size_t setRightSideCharacterSpacing(uint8_t n);

    virtual std::size_t enableUserDefinedCharacterSet(bool enable);
    virtual std::size_t uploadUserDefinedCharacterSet(const std::vector<uint8_t>& charSet);
    virtual std::size_t clearUserDefinedCharacter(uint8_t character);
    virtual std::size_t setCharacterSet(Codes::CharacterSet charSet);
    virtual std::size_t setCharacterCodePage(Codes::CodePage codePage);

    virtual std::size_t setPrintMode(uint8_t modeByte);
    virtual std::size_t setInvert(bool enable);
    virtual std::size_t setUnderline(Codes::TextUnderline underline);
    virtual std::size_t setEmphasis(bool bEnable);
    virtual std::size_t setDoubleStrike(bool enable);
    virtual std::size_t setFont(Codes::TextFont font);
    virtual std::size_t setColor(Codes::TextColor color);
    virtual std::size_t setUpsideDown(bool enable);
    virtual std::size_t setCharacterSize(Codes::TextMagnification horizontal,
                                         Codes::TextMagnification vertical);
    virtual std::size_t setCharacterSmoothing(bool enable);
    virtual std::size_t setRotation(Codes::TextRotate textRotate);
    virtual std::size_t setAlign(Codes::TextAlignment align);

    /// Bit image commands.
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


    /// Mechanism commands.
    virtual std::size_t cut(Codes::PaperCut type = Codes::CUT_FULL,
                            uint8_t numDotsToFeed = 0);

    /// Line spacing commands.
    virtual std::size_t setDefaultLineSpacing();
    virtual std::size_t setLineSpacing(uint8_t n);

    /// Printer status commands.
    virtual std::size_t getPrinterStatusRealTime();

    virtual std::size_t getOfflineStatus();
    virtual std::size_t getErrorStatus();
    virtual std::size_t getPaperStatus();

    //    virtual uint8_t getPrinterModelId();
    //
    //    virtual const std::string& getFirmwareVersion();
    //    virtual const std::string& getManufacturer();
    //    virtual const std::string& getPrinterName();
    //
    //    virtual uint8_t getTypeId();
    //
    //    virtual bool multibyteCharactersSupported();
    //    virtual bool autocutterInstalled();

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


//    std::string getSerialNumber();


private:
    /// \brief Printer Status
    std::bitset<8> _typeId;
    std::string _firmwareVersion;
    std::string _manufacturer;
    std::string _printerName;
    std::string _serialNumber;
    std::string _additionalFonts;

};


typedef SerialPrinter DefaultSerialPrinter;


} } // namespace ofx::ESCPOS
