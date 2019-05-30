//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/LineSpacingCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


LineSpacingCommands::LineSpacingCommands()
{
}


LineSpacingCommands::~LineSpacingCommands()
{
}


std::size_t LineSpacingCommands::setDefaultLineSpacing()
{
    return writeBytes({ 27, 50 });
}


std::size_t LineSpacingCommands::setLineSpacing(uint8_t n)
{
    return writeBytes({ 27, 51, n });
}


} } } // namespace ofx::ESCPOS::Commands
