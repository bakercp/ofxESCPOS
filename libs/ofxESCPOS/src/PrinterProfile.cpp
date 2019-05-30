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
    // Codes::Katakana, // Not supporting this yet, because the code page isn't correct.
    Codes::PC850,
    Codes::PC860,
    Codes::PC863,
    Codes::PC865,

    // Codes::PC851, Not used. Inconsistently supported.
    Codes::PC853,
    Codes::PC857,
    Codes::PC737,
    Codes::ISO8859_7,
    Codes::WPC1252,
    Codes::PC866,
    Codes::PC852,
    Codes::PC858,
    // Codes::KU42, Not supporting b/c no iconv support.
    Codes::TIS11,

    // Codes::TIS18, Not supporting b/c no iconv support.

    // Codes::TCVN_3_I, Not supporting b/c no iconv support.
    // Codes::TCVN_3_II, Not supporting b/c no iconv support.
    // Codes::PC720, Not supporting b/c no iconv support.
    Codes::PC775,
    Codes::PC855,
    Codes::PC861,
    Codes::PC862,
    Codes::PC864,
    Codes::PC869,
    Codes::ISO8859_2,
    Codes::ISO8859_15,
    // Codes::PC1098, Not supporting b/c no iconv support.
    // Codes::PC1118, Not supporting b/c no iconv support.
    // Codes::PC1119, Not supporting b/c no iconv support.
    Codes::PC1125,
    Codes::WPC1250,
    Codes::WPC1251,
    Codes::WPC1253,
    Codes::WPC1254,
    Codes::WPC1255,
    Codes::WPC1256,
    Codes::WPC1257,
    // Codes::WPC1258, Not supporting this yet.
    Codes::KZ_1048,

    // Codes::USER_PAGE // Not supporting for now.
};


PrinterProfile::PrinterProfile(): codePages(DEFAULT_CODE_PAGES)
{
}


PrinterProfile::~PrinterProfile()
{
}


} } // namespace ofx::ESCPOS
