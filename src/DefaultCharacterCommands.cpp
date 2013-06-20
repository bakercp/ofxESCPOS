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


#include "DefaultCharacterCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


//------------------------------------------------------------------------------
DefaultCharacterCommands::DefaultCharacterCommands()
{
}

//------------------------------------------------------------------------------
DefaultCharacterCommands::~DefaultCharacterCommands()
{
}


//------------------------------------------------------------------------------
void DefaultCharacterCommands::clearPage()
{
    write(ByteBuffer(BaseCodes::CAN));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setRightSideCharacterSpacing(unsigned char n)
{
    write(ByteBuffer(BaseCodes::ESC,' ',n));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::enableUserDefinedCharacterSet(bool bEnable)
{
    write(ByteBuffer(BaseCodes::ESC,'%',(unsigned char)bEnable));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::uploadUserDefinedCharacterSet(const BaseUserDefinedCharacterSet& charSet)
{
    ByteBuffer buffer(BaseCodes::ESC,'&');
    buffer.write(charSet.getBuffer()); // set charset bytes
    write(buffer);
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::clearUserDefinedCharacter(unsigned char character)
{
    if(character > 126 || character < 32) {
        // TODO: throw exception
    }

    write(ByteBuffer(BaseCodes::ESC,'?',character));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setCharacterSet(BaseCodes::CharacterSet charSet)
{
    write(ByteBuffer(BaseCodes::ESC,'R',charSet));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setCharacterCodePage(BaseCodes::CodePage codePage)
{
    write(ByteBuffer(BaseCodes::ESC,'t',codePage));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setPrintMode(unsigned char modeByte)
{
    write(ByteBuffer(BaseCodes::ESC,'!',modeByte));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setInvert(bool bEnable)
{
    write(ByteBuffer(BaseCodes::GS,'B',bEnable));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setUnderline(BaseCodes::TextUnderline underline)
{
    write(ByteBuffer(BaseCodes::ESC,'-',underline));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setEmphasis(bool bEnable)
{
    write(ByteBuffer(BaseCodes::ESC,'E',bEnable));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setDoubleStrike(bool bEnable)
{
    write(ByteBuffer(BaseCodes::ESC,'G',bEnable));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setFont(BaseCodes::TextFont font)
{
    write(ByteBuffer(BaseCodes::ESC,'M',font));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setColor(BaseCodes::TextColor color)
{
    write(ByteBuffer(BaseCodes::ESC,'r',color));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setUpsideDown(bool bEnable)
{
    write(ByteBuffer(BaseCodes::ESC,'{',bEnable));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setCharacterSize(BaseCodes::TextMagnification horizontal,
                                                      BaseCodes::TextMagnification vertical)
{
    write(ByteBuffer(BaseCodes::GS,'!',(horizontal << 4) | (vertical)));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setCharacterSmoothing(bool bEnable)
{
    write(ByteBuffer(BaseCodes::GS,'b',bEnable));
}

//------------------------------------------------------------------------------
void DefaultCharacterCommands::setRotation(BaseCodes::TextRotate textRotate)
{
    write(ByteBuffer(BaseCodes::ESC,'V',textRotate));
}
    
    
} } } // namespace ofx::ESCPOS::Commands
