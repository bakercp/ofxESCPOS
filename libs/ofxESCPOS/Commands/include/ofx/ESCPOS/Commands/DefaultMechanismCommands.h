//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <stdint.h>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/ESCPOS/Codes.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


class DefaultMechanismCommands: public virtual IO::AbstractByteSink
{
public:
    DefaultMechanismCommands();

    virtual ~DefaultMechanismCommands();

    virtual std::size_t cut(Codes::PaperCut type = Codes::CUT_FULL,
                            uint8_t numDotsToFeed = 0);

};


} } } // namespace ofx::ESCPOS::Commands
