//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/DefaultPrinterStatusCommands.h"
#include "ofx/IO/ByteBufferUtils.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


DefaultPrinterStatusCommands::DefaultPrinterStatusCommands()
{
}


DefaultPrinterStatusCommands::~DefaultPrinterStatusCommands()
{
}


std::size_t DefaultPrinterStatusCommands::getPrinterStatusRealTime()
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
            ofLogError("DefaultPrinterStatusCommands::getPrinterStatus") << "No bytes read.";
        }

    }
    else
    {
        ofLogError("DefaultPrinterStatusCommands::getPrinterStatus") << "Number of bytes written was " << numBytesWritten;
    }

    return numBytesWritten;
}


std::size_t DefaultPrinterStatusCommands::getOfflineStatus()
{
    return 0; // TBI
}


std::size_t DefaultPrinterStatusCommands::getErrorStatus()
{
    return 0; // TBI
}


std::size_t DefaultPrinterStatusCommands::getPaperStatus()
{
    return 0; // TBI
}


} } } // namespace ofx::ESCPOS::Commands
