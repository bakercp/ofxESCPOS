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
    return writeBytes({ 27, 50 });
}


std::size_t DefaultLineSpacingCommands::setLineSpacing(uint8_t n)
{
    return writeBytes({ 27, 51, n });
}


} } } // namespace ofx::ESCPOS::Commands
