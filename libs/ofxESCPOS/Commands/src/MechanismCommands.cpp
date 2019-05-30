//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/MechanismCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


MechanismCommands::MechanismCommands()
{
}


MechanismCommands::~MechanismCommands()
{
}


std::size_t MechanismCommands::cut(Codes::PaperCut type,
                                          uint8_t numDotsToFeed)
{
    if (numDotsToFeed > 0)
        return writeBytes({ Codes::GS, 'V', type });


    return writeBytes({ Codes::GS, 'V',
                        static_cast<uint8_t>(type + 'A'),
                        numDotsToFeed }); // shift -> A/B
}


} } } // namespace ofx::ESCPOS::Commands
