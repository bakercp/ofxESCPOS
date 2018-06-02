//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/DefaultMechanismCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


DefaultMechanismCommands::DefaultMechanismCommands()
{
}


DefaultMechanismCommands::~DefaultMechanismCommands()
{
}


std::size_t DefaultMechanismCommands::cut(BaseCodes::PaperCut type,
                                          uint8_t numDotsToFeed)
{
    if (numDotsToFeed > 0)
    {
        const uint8_t command[3] = { BaseCodes::GS, 'V', type };
        return writeBytes(command, 3);
    }
    else
    {
        const uint8_t command[4] = { BaseCodes::GS,
									'V',
									 static_cast<uint8_t>(type + 'A'),
									 numDotsToFeed };

        return writeBytes(command, 4); // shift -> A/B
    }
}


} } } // namespace ofx::ESCPOS::Commands
