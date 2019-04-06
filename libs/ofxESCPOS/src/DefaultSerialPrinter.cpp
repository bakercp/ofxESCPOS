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
//    const uint8_t command[3] = {
//        ESCPOS::BaseCodes::GS,
//        'I',
//        68
//    };
//
//    std::size_t b = writeBytes(command, 3);
//
//    char buffer[256];

//    std::size bytesRead = read(buffer, 256);
}


} } // namespace ofx::ESCPOS
