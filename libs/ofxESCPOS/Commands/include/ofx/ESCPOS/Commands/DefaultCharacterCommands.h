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
#include "ofx/ESCPOS/BaseCodes.h"
#include "ofx/ESCPOS/BaseTypes.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


class DefaultCharacterCommands: public virtual IO::AbstractByteSink
{
public:
    DefaultCharacterCommands();
    virtual ~DefaultCharacterCommands();

    virtual std::size_t clearPage();
    virtual std::size_t setRightSideCharacterSpacing(uint8_t n);

    virtual std::size_t enableUserDefinedCharacterSet(bool enable);
    virtual std::size_t uploadUserDefinedCharacterSet(const std::vector<uint8_t>& charSet);
    virtual std::size_t clearUserDefinedCharacter(uint8_t character);
    virtual std::size_t setCharacterSet(BaseCodes::CharacterSet charSet);
    virtual std::size_t setCharacterCodePage(BaseCodes::CodePage codePage);

    virtual std::size_t setPrintMode(uint8_t modeByte);
    virtual std::size_t setInvert(bool enable);
    virtual std::size_t setUnderline(BaseCodes::TextUnderline underline);
    virtual std::size_t setEmphasis(bool bEnable);
    virtual std::size_t setDoubleStrike(bool enable);
    virtual std::size_t setFont(BaseCodes::TextFont font);
    virtual std::size_t setColor(BaseCodes::TextColor color);
    virtual std::size_t setUpsideDown(bool enable);
    virtual std::size_t setCharacterSize(BaseCodes::TextMagnification horizontal,
                                         BaseCodes::TextMagnification vertical);
    virtual std::size_t setCharacterSmoothing(bool enable);
    virtual std::size_t setRotation(BaseCodes::TextRotate textRotate);
    virtual std::size_t setAlign(BaseCodes::TextAlignment align);

};


} } } // namespace ofx::ESCPOS::Commands
