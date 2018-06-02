//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <stdint.h>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/ESCPOS/BaseCodes.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


class DefaultMechanismCommands: public virtual IO::AbstractByteSink
{
public:
    DefaultMechanismCommands();

    virtual ~DefaultMechanismCommands();

    virtual std::size_t cut(BaseCodes::PaperCut type = BaseCodes::CUT_FULL,
                            uint8_t numDotsToFeed = 0);

};


} } } // namespace ofx::ESCPOS::Commands
