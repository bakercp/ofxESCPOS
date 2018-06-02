//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/DefaultLineSpacingCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


DefaultLineSpacingCommands::DefaultLineSpacingCommands()
{
}


DefaultLineSpacingCommands::~DefaultLineSpacingCommands()
{
}


std::size_t DefaultLineSpacingCommands::setDefaultLineSpacing()
{
    const uint8_t command[2] = { 27, 50 };
    return writeBytes(command, 2);
}


std::size_t DefaultLineSpacingCommands::setLineSpacing(uint8_t n)
{
    const uint8_t command[3] = { 27, 51, n };
    return writeBytes(command, 3);
}


} } } // namespace ofx::ESCPOS::Commands
