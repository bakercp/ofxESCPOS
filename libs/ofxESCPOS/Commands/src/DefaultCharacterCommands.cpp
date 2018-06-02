//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


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

    IO::ByteBuffer buffer(command,2);
    buffer.writeBytes(charSet);

    return writeBytes(buffer.getData());
}


std::size_t DefaultCharacterCommands::clearUserDefinedCharacter(uint8_t character)
{
    if (character > 126 || character < 32)
    {
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

std::size_t DefaultCharacterCommands::setAlign(BaseCodes::TextAlignment align)
{
    const uint8_t command[3] = { BaseCodes::ESC,'a',align};
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
    const uint8_t command[3] = {
								BaseCodes::GS,
								'!',
								static_cast<uint8_t>((horizontal << 4) | (vertical))
								};

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
