//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/DefaultSerialPrinter.h"


namespace ofx {
namespace ESCPOS {


DefaultSerialPrinter::DefaultSerialPrinter()
{
}


DefaultSerialPrinter::~DefaultSerialPrinter()
{
}


std::string DefaultSerialPrinter::getSerialNumber()
{
    const uint8_t command[3] = {
        ESCPOS::BaseCodes::GS,
        'I',
        68
    };

    std::size_t b = writeBytes(command, 3);

    std::cout << b << " bytes written." << std::endl;

    uint8_t buffer[256];

    std::size_t bytesRead = readBytes(buffer, 256);

    std::cout << bytesRead << " bytes read." << std::endl;

    return "";
}


} } // namespace ofx::ESCPOS
