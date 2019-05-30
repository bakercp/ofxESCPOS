//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/PrinterStatusCommands.h"
#include "ofx/IO/ByteBufferUtils.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


PrinterStatusCommands::PrinterStatusCommands()
{
}


PrinterStatusCommands::~PrinterStatusCommands()
{
}


std::size_t PrinterStatusCommands::getPrinterStatusRealTime()
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


std::size_t PrinterStatusCommands::getOfflineStatus()
{
    return 0; // TBI
}


std::size_t PrinterStatusCommands::getErrorStatus()
{
    return 0; // TBI
}


std::size_t PrinterStatusCommands::getPaperStatus()
{
    return 0; // TBI
}


} } } // namespace ofx::ESCPOS::Commands
