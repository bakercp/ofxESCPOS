//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/PrinterProfile.h"


namespace ofx {
namespace ESCPOS {


const std::vector<Codes::CodePage> PrinterProfile::DEFAULT_CODE_PAGES =
{
    Codes::PC437,
    Codes::Katakana,
    Codes::PC850,
    Codes::PC860,
    Codes::PC863,
    Codes::PC865,

    Codes::PC851,
    Codes::PC853,
    Codes::PC857,
    Codes::PC737,
    Codes::ISO8859_7,
    Codes::WPC1252,
    Codes::PC866,
    Codes::PC852,
    Codes::PC858,
    Codes::KU42,
    Codes::TIS11,

    Codes::TIS18,

    Codes::TCVN_3_I,
    Codes::TCVN_3_II,
    Codes::PC720,
    Codes::PC775,
    Codes::PC855,
    Codes::PC861,
    Codes::PC862,
    Codes::PC864,
    Codes::PC869,
    Codes::ISO8859_2,
    Codes::ISO8859_15,
    Codes::PC1098,
    Codes::PC1118,
    Codes::PC1119,
    Codes::PC1125,
    Codes::WPC1250,
    Codes::WPC1251,
    Codes::WPC1253,
    Codes::WPC1254,
    Codes::WPC1255,
    Codes::WPC1256,
    Codes::WPC1257,
    Codes::WPC1258,
    Codes::KZ_1048,

    Codes::USER_PAGE
};


PrinterProfile::PrinterProfile(): codePages(DEFAULT_CODE_PAGES)
{
}


PrinterProfile::~PrinterProfile()
{
}


} } // namespace ofx::ESCPOS
