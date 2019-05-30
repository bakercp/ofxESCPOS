//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <string>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/SerialDevice.h"
#include "ofx/ESCPOS/Commands/DefaultCharacterCommands.h"
#include "ofx/ESCPOS/Commands/DefaultPrinterStatusCommands.h"
#include "ofx/ESCPOS/Commands/DefaultBitImageCommands.h"
#include "ofx/ESCPOS/Commands/DefaultMechanismCommands.h"
#include "ofx/ESCPOS/Commands/MiscellaneousCommands.h"
#include "ofx/ESCPOS/Commands/DefaultLineSpacingCommands.h"


namespace ofx {
namespace ESCPOS {


class DefaultSerialPrinter:
    public IO::SerialDevice,
    public Commands::DefaultCharacterCommands,
    public Commands::DefaultBitImageCommands,
    public Commands::DefaultMechanismCommands,
    public Commands::MiscellaneousCommands,
    public Commands::DefaultLineSpacingCommands,
    public Commands::DefaultPrinterStatusCommands
{
public:
    DefaultSerialPrinter();

    virtual ~DefaultSerialPrinter();

    std::string getSerialNumber();


};


} } // namespace ofx::ESCPOS
