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


class DefaultLineSpacingCommands: public virtual IO::AbstractByteSink
{
public:
    DefaultLineSpacingCommands();
    virtual ~DefaultLineSpacingCommands();

    virtual std::size_t setDefaultLineSpacing();
    virtual std::size_t setLineSpacing(uint8_t n);

};


} } } // namespace ofx::ESCPOS::Commands
