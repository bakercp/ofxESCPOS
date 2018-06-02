//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <bitset>
#include "ofLog.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/ESCPOS/BaseCodes.h"
#include "ofx/ESCPOS/BaseTypes.h"
#include "ofx/ESCPOS/BitImage.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


class DefaultPrinterStatus
{
public:
    DefaultPrinterStatus()
    {
    }


    virtual ~DefaultPrinterStatus()
    {
    }


private:
    int _modelId;
    int _typeId;

};


class DefaultPrinterStatusCommands:
    public virtual IO::AbstractByteSink,
    public virtual IO::AbstractBufferedByteSource
{
public:
    DefaultPrinterStatusCommands();
    virtual ~DefaultPrinterStatusCommands();

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



    std::bitset<8> _typeId;
    std::string _firmwareVersion;
    std::string _manufacturer;
    std::string _printerName;
    std::string _serialNumber;
    std::string _additionalFonts;

};


} } } // namespace ofx::ESCPOS::Commands
