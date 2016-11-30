// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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
    const uint8_t command[3] = {
                                 BaseCodes::DLE,
                                 BaseCodes::EOT,
                                 BaseCodes::STATUS_PRINTER
                               };

    std::size_t numBytesWritten = writeBytes(command, 3);

    if (3 == numBytesWritten)
    {
        uint8_t data;

//        pSerial->waitByteTimes(3);

        

        std::size_t numBytesRead = readByte(data);

        if (numBytesRead > 0)
        {
            std::bitset<8> bits(data);
            std::cout << "Data Read: " << bits << std::endl;

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
