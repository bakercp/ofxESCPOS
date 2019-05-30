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


std::size_t DefaultMechanismCommands::cut(Codes::PaperCut type,
                                          uint8_t numDotsToFeed)
{
    if (numDotsToFeed > 0)
        return writeBytes({ Codes::GS, 'V', type });


    return writeBytes({ Codes::GS, 'V',
                        static_cast<uint8_t>(type + 'A'),
                        numDotsToFeed }); // shift -> A/B
}


} } } // namespace ofx::ESCPOS::Commands
