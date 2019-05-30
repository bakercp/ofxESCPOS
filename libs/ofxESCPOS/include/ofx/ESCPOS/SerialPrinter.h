//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <string>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/SerialDevice.h"
#include "ofx/ESCPOS/Commands/CharacterCommands.h"
#include "ofx/ESCPOS/Commands/PrinterStatusCommands.h"
#include "ofx/ESCPOS/Commands/BitImageCommands.h"
#include "ofx/ESCPOS/Commands/MechanismCommands.h"
#include "ofx/ESCPOS/Commands/MiscellaneousCommands.h"
#include "ofx/ESCPOS/Commands/LineSpacingCommands.h"


namespace ofx {
namespace ESCPOS {


class SerialPrinter:
    public IO::SerialDevice,
    public Commands::CharacterCommands,
    public Commands::BitImageCommands,
    public Commands::MechanismCommands,
    public Commands::MiscellaneousCommands,
    public Commands::LineSpacingCommands,
    public Commands::PrinterStatusCommands
{
public:
    SerialPrinter();

    virtual ~SerialPrinter();

    std::string getSerialNumber();


};


typedef SerialPrinter DefaultSerialPrinter;


} } // namespace ofx::ESCPOS
