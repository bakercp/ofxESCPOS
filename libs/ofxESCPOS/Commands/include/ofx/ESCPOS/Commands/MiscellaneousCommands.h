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


class MiscellaneousCommands: public virtual IO::AbstractByteSink
{
public:
    MiscellaneousCommands();
    virtual ~MiscellaneousCommands();

    virtual std::size_t initialize();

    virtual std::size_t print(const std::string& text);
    virtual std::size_t println(const std::string& text);

};


} } } // namespace ofx::ESCPOS::Commands
