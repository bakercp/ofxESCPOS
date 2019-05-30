//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/SerialPrinter.h"


namespace ofx {
namespace ESCPOS {


SerialPrinter::SerialPrinter()
{
}


SerialPrinter::~SerialPrinter()
{
}


std::string SerialPrinter::getSerialNumber()
{
    std::size_t b = writeBytes({
        ESCPOS::Codes::GS,
        'I',
        68
    });

    std::cout << b << " bytes written." << std::endl;

    uint8_t buffer[256];

    std::size_t bytesRead = readBytes(buffer, 256);

    std::cout << bytesRead << " bytes read." << std::endl;

    return "";
}


} } // namespace ofx::ESCPOS
