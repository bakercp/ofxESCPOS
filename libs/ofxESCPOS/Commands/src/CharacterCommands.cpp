//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "CharacterCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


CharacterCommands::CharacterCommands()
{
}


CharacterCommands::~CharacterCommands()
{
}


std::size_t CharacterCommands::clearPage()
{
    return writeByte(Codes::CAN);
}


std::size_t CharacterCommands::setRightSideCharacterSpacing(uint8_t n)
{
    return writeBytes({ Codes::ESC, ' ', n });
}


std::size_t CharacterCommands::enableUserDefinedCharacterSet(bool enable)
{
    return writeBytes({ Codes::ESC, '%', enable });
}


std::size_t CharacterCommands::uploadUserDefinedCharacterSet(const std::vector<uint8_t>& charSet)
{
    IO::ByteBuffer buffer({ Codes::ESC, '&' });
    buffer.writeBytes(charSet);

    return writeBytes(buffer.getData());
}


std::size_t CharacterCommands::clearUserDefinedCharacter(uint8_t character)
{
    if (character > 126 || character < 32)
    {
        ofLogError("CharacterCommands::clearUserDefinedCharacter") << "Invalid character " << character;
        return 0;
    }

    return writeBytes({ Codes::ESC, '?', character });
}


std::size_t CharacterCommands::setCharacterSet(Codes::CharacterSet charSet)
{
    return writeBytes({ Codes::ESC, 'R', charSet });
}


std::size_t CharacterCommands::setCharacterCodePage(Codes::CodePage codePage)
{
    return writeBytes({ Codes::ESC, 't', codePage });
}


std::size_t CharacterCommands::setPrintMode(uint8_t modeByte)
{
    return writeBytes({ Codes::ESC, '!', modeByte });
}


std::size_t CharacterCommands::setInvert(bool enable)
{
    return writeBytes({ Codes::GS, 'B', enable });
}


std::size_t CharacterCommands::setUnderline(Codes::TextUnderline underline)
{
    return writeBytes({ Codes::ESC, '-', underline });
}


std::size_t CharacterCommands::setEmphasis(bool enable)
{
    return writeBytes({ Codes::ESC, 'E', enable });
}


std::size_t CharacterCommands::setDoubleStrike(bool enable)
{
    return writeBytes({ Codes::ESC, 'G', enable });
}


std::size_t CharacterCommands::setFont(Codes::TextFont font)
{
    return writeBytes({ Codes::ESC, 'M', font });
}


std::size_t CharacterCommands::setColor(Codes::TextColor color)
{
    return writeBytes({ Codes::ESC, 'r', color });
}

std::size_t CharacterCommands::setAlign(Codes::TextAlignment align)
{
    return writeBytes({ Codes::ESC,'a',align});
}


std::size_t CharacterCommands::setUpsideDown(bool enable)
{
    return writeBytes({ Codes::ESC, '{', enable });
}


std::size_t CharacterCommands::setCharacterSize(Codes::TextMagnification horizontal,
                                                       Codes::TextMagnification vertical)
{
    return writeBytes({
        Codes::GS,
        '!',
        static_cast<uint8_t>((horizontal << 4) | (vertical))
    });
}


std::size_t CharacterCommands::setCharacterSmoothing(bool enable)
{
    return writeBytes({ Codes::GS, 'b', enable });
}


std::size_t CharacterCommands::setRotation(Codes::TextRotate textRotate)
{
    return writeBytes({ Codes::ESC, 'V', textRotate });
}


} } } // namespace ofx::ESCPOS::Commands
