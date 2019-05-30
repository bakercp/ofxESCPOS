//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofLog.h"
#include <stdint.h>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/ByteBufferUtils.h"
#include "ofx/ESCPOS/Codes.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


class CharacterCommands: public virtual IO::AbstractByteSink
{
public:
    CharacterCommands();
    virtual ~CharacterCommands();

    virtual std::size_t clearPage();
    virtual std::size_t setRightSideCharacterSpacing(uint8_t n);

    virtual std::size_t enableUserDefinedCharacterSet(bool enable);
    virtual std::size_t uploadUserDefinedCharacterSet(const std::vector<uint8_t>& charSet);
    virtual std::size_t clearUserDefinedCharacter(uint8_t character);
    virtual std::size_t setCharacterSet(Codes::CharacterSet charSet);
    virtual std::size_t setCharacterCodePage(Codes::CodePage codePage);

    virtual std::size_t setPrintMode(uint8_t modeByte);
    virtual std::size_t setInvert(bool enable);
    virtual std::size_t setUnderline(Codes::TextUnderline underline);
    virtual std::size_t setEmphasis(bool bEnable);
    virtual std::size_t setDoubleStrike(bool enable);
    virtual std::size_t setFont(Codes::TextFont font);
    virtual std::size_t setColor(Codes::TextColor color);
    virtual std::size_t setUpsideDown(bool enable);
    virtual std::size_t setCharacterSize(Codes::TextMagnification horizontal,
                                         Codes::TextMagnification vertical);
    virtual std::size_t setCharacterSmoothing(bool enable);
    virtual std::size_t setRotation(Codes::TextRotate textRotate);
    virtual std::size_t setAlign(Codes::TextAlignment align);

};


typedef CharacterCommands DefaultCharacterCommands;


} } } // namespace ofx::ESCPOS::Commands
