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


DefaultCharacterCommands::DefaultCharacterCommands()
{
}


DefaultCharacterCommands::~DefaultCharacterCommands()
{
}


std::size_t DefaultCharacterCommands::clearPage()
{
    return writeByte(BaseCodes::CAN);
}


std::size_t DefaultCharacterCommands::setRightSideCharacterSpacing(uint8_t n)
{
    const uint8_t command[3] = { BaseCodes::ESC, ' ', n };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::enableUserDefinedCharacterSet(bool enable)
{
    const uint8_t command[3] = { BaseCodes::ESC, '%', enable };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::uploadUserDefinedCharacterSet(const std::vector<uint8_t>& charSet)
{
    const uint8_t command[2] = { BaseCodes::ESC, '&' };

    ByteBuffer buffer(command,2);
    buffer.writeBytes(charSet);

    return writeBytes(buffer.getDataRef());
}


std::size_t DefaultCharacterCommands::clearUserDefinedCharacter(uint8_t character)
{
    if(character > 126 || character < 32) {
        ofLogError("DefaultCharacterCommands::clearUserDefinedCharacter") << "Invalid character " << character;
        return 0;
    }

    const uint8_t command[3] = { BaseCodes::ESC, '?', character };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setCharacterSet(BaseCodes::CharacterSet charSet)
{
    const uint8_t command[3] = { BaseCodes::ESC, 'R', charSet };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setCharacterCodePage(BaseCodes::CodePage codePage)
{
    const uint8_t command[3] = { BaseCodes::ESC, 't', codePage };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setPrintMode(uint8_t modeByte)
{
    const uint8_t command[3] = { BaseCodes::ESC, '!', modeByte };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setInvert(bool enable)
{
    const uint8_t command[3] = { BaseCodes::GS, 'B', enable };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setUnderline(BaseCodes::TextUnderline underline)
{
    const uint8_t command[3] = { BaseCodes::ESC, '-', underline };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setEmphasis(bool enable)
{
    const uint8_t command[3] = { BaseCodes::ESC, 'E', enable };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setDoubleStrike(bool enable)
{
    const uint8_t command[3] = { BaseCodes::ESC, 'G', enable };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setFont(BaseCodes::TextFont font)
{
    const uint8_t command[3] = { BaseCodes::ESC, 'M', font };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setColor(BaseCodes::TextColor color)
{
    const uint8_t command[3] = { BaseCodes::ESC, 'r', color };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setUpsideDown(bool enable)
{
    const uint8_t command[3] = { BaseCodes::ESC, '{', enable };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setCharacterSize(BaseCodes::TextMagnification horizontal,
                                                       BaseCodes::TextMagnification vertical)
{
    const uint8_t command[3] = { BaseCodes::GS, '!', (horizontal << 4) | (vertical) };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setCharacterSmoothing(bool enable)
{
    const uint8_t command[3] = { BaseCodes::GS, 'b', enable };
    return writeBytes(command, 3);
}


std::size_t DefaultCharacterCommands::setRotation(BaseCodes::TextRotate textRotate)
{
    const uint8_t command[3] = { BaseCodes::ESC, 'V', textRotate };
    return writeBytes(command, 3);
}
    
    
} } } // namespace ofx::ESCPOS::Commands
