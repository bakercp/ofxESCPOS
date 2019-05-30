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


class LineSpacingCommands: public virtual IO::AbstractByteSink
{
public:
    LineSpacingCommands();
    virtual ~LineSpacingCommands();

    virtual std::size_t setDefaultLineSpacing();
    virtual std::size_t setLineSpacing(uint8_t n);

};


typedef LineSpacingCommands DefaultLineSpacingCommands;


} } } // namespace ofx::ESCPOS::Commands
