//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/MiscellaneousCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


MiscellaneousCommands::MiscellaneousCommands()
{
}


MiscellaneousCommands::~MiscellaneousCommands()
{
}


std::size_t MiscellaneousCommands::initialize()
{
    return writeBytes({ Codes::ESC, '@' });
}


std::size_t MiscellaneousCommands::print(const std::string& text)
{
    return writeBytes(text);
}


std::size_t MiscellaneousCommands::println(const std::string& text)
{
    return writeBytes(text + "\n");
}


} } } // namespace ofx::ESCPOS::Commands
