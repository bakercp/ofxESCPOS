// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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


using ofx::IO::AbstractByteSink;
using ofx::IO::ByteBuffer;
using ofx::IO::ByteBufferUtils;


class DefaultCharacterCommands: public virtual AbstractByteSink
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
