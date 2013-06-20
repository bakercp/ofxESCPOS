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


#include "BaseCodes.h"
#include "BaseTypes.h"
#include "ByteBuffer.h"

namespace ofx {
namespace ESCPOS {
namespace Commands {


class DefaultCharacterCommands : public BaseWriteBytes {
public:
    DefaultCharacterCommands();
    virtual ~DefaultCharacterCommands();

    virtual void clearPage();
    virtual void setRightSideCharacterSpacing(unsigned char n);

    virtual void enableUserDefinedCharacterSet(bool bEnable);
    virtual void uploadUserDefinedCharacterSet(const BaseUserDefinedCharacterSet& charSet);
    virtual void clearUserDefinedCharacter(unsigned char character);
    virtual void setCharacterSet(BaseCodes::CharacterSet charSet);
    virtual void setCharacterCodePage(BaseCodes::CodePage codePage);

    virtual void setPrintMode(unsigned char modeByte);
    virtual void setInvert(bool bEnable);
    virtual void setUnderline(BaseCodes::TextUnderline underline);
    virtual void setEmphasis(bool bEnable);
    virtual void setDoubleStrike(bool bEnable);
    virtual void setFont(BaseCodes::TextFont font);
    virtual void setColor(BaseCodes::TextColor color);
    virtual void setUpsideDown(bool bEnable);
    virtual void setCharacterSize(BaseCodes::TextMagnification horizontal,
                                        BaseCodes::TextMagnification vertical);
    virtual void setCharacterSmoothing(bool bEnable);
    virtual void setRotation(BaseCodes::TextRotate textRotate);

};


} } } // namespace ofx::ESCPOS::Commands
