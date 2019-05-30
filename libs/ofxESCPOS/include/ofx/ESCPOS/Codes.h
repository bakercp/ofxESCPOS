//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <string>
#include "json.hpp"


namespace ofx {
namespace ESCPOS {


class Codes
{
public:
	enum CommandFlags
    {
        PRIORITY_NORMAL       = 0x00000001,
        PRIORITY_REALTIME     = 0x00000010,
        REQUIRE_MODE_STANDARD = 0x00000100,
        REQUIRE_MODE_PAGE     = 0x00001000,
        CANCELS_MODE_PAGE     = 0x00010000,
        OBSOLETE              = 0x00100000
    };

	enum Command: uint8_t
    {
        NUL = 0,  ///< Null
        SOH = 1,  ///< Start of heading
        STX = 2,  ///< Start of text
        ETX = 3,  ///< End of text
        EOT = 4,  ///< End of text
        ENQ = 5,  ///< Enquiry
        ACK = 6,  ///< Achknowledge
        BEL = 7,  ///< Bell
        BS  = 8,  ///< Backspace
        HT  = 9,  ///< Horizontal tab
        LF  = 10, ///< NL line feed, new line
        VT  = 11, ///< Vertical tab
        FF  = 12, ///< NP form feed, new page
        CR  = 13, ///< Carriage return
        SO  = 14, ///< Shift out
        SI  = 15, ///< Shift in
        DLE = 16, ///< Data link escape
        DC1 = 17, ///< Device control 1
        DC2 = 18, ///< Device control 1
        DC3 = 19, ///< Device control 1
        DC4 = 20, ///< Device control 1
        NAK = 21, ///< Negative acknowlege
        SYN = 22, ///< Synchronous idle
        ETB = 23, ///< End of transmission block
        CAN = 24, ///< Cancel
        EM  = 25, ///< End of medium
        SUB = 26, ///< Substitute
        ESC = 27, ///< Escape
        FS  = 28, ///< File seperator
        GS  = 29, ///< Group seperator
        RS  = 30, ///< Record seperator
        US  = 31  ///< Unit seperator
    };


	enum PrintMode: uint8_t
    {
        MODE_STANDARD,
        MODE_PAGE
    };


	enum TextFont: uint8_t
    {
        FONT_A  = 0, ///< Character font A (12 x 24 normally)
        FONT_B  = 1, ///< Character font B (9 x 17 normally)
        FONT_C  = 2  ///< Character font C (optional)
    };


	enum TextUnderline: uint8_t
    {
        UNDERLINE_OFF    = 0, ///< Underline off
        UNDERLINE_NORMAL = 1, ///< Underline 1 dot thick
        UNDERLINE_THICK  = 2  ///< Underline 2 dots thick
    };


	enum TextAlignment: uint8_t
    {
        ALIGN_LEFT    = 0, ///< Align text left
        ALIGN_CENTER  = 1, ///< Align text center
        ALIGN_RIGHT   = 2  ///< Align text right
    };


	enum MoveToTopOfLine: uint8_t
    {
        BUFFER_ERASE_MOVE = 0,
        BUFFER_PRINT_MOVE = 1
    };


	enum TextMagnification: uint8_t
    {
        MAGNIFICATION_1X  = 0, //
        MAGNIFICATION_2X  = 1, //
        MAGNIFICATION_3X  = 2, //
        MAGNIFICATION_4X  = 3, //
        MAGNIFICATION_5X  = 4, //
        MAGNIFICATION_6X  = 5, //
        MAGNIFICATION_7X  = 6, //
        MAGNIFICATION_8X  = 7, //
    };


	enum TextRotate: uint8_t
    {
        ROTATE_OFF    = 0, ///< Rotate off
        ROTATE_90_CW  = 1, ///< Rotate 90deg clockwise
    };


	enum PagePrintDirection: uint8_t
    {
        LEFT_TO_RIGHT = 0,
        BOTTOM_TO_TOP = 1,
        RIGHT_TO_LEFT = 2,
        TOP_TO_BOTTOM = 3
    };


	enum TextColor: uint8_t
    {
        COLOR_1  = 0, ///< Black (normally)
        COLOR_2  = 1, ///< Red (normally)
    };


	enum PaperCut: uint8_t
    {
        CUT_FULL    = 0,
        CUT_PARTIAL = 1
    };


    enum ByteFormat
    {
        BYTE_FORMAT_RASTER,
        BYTE_FORMAT_COLUMN
    };


    enum PrintResolution
    {
        RESOLUTION_8_DOTS_SINGLE_DENSITY  = 0,
        RESOLUTION_8_DOTS_DOUBLE_DENSITY  = 1,
        RESOLUTION_24_DOTS_SINGLE_DENSITY = 32,
        RESOLUTION_24_DOTS_DOUBLE_DENSITY = 33
    };


    enum PrintScale
    {
        SCALE_NORMAL         = 0,
        SCALE_DOUBLE_WIDTH   = 1,
        SCALE_DOUBLE_HEIGHT  = 2,
        SCALE_QUADRUPLE      = 3
    };


    // Usually used with ESC R <CharacterSet>
    enum CharacterSet: uint8_t
    {
        USA              = 0,
        FRANCE           = 1,
        GERMANY          = 2,
        UNITED_KINGDOM   = 3,
        DENMARK_I        = 4,
        SWEDEN           = 5,
        ITALY            = 6,
        SPAIN_I          = 7,
        JAPAN            = 8,
        NORWAY           = 9,
        DENMARK_II       = 10,
        SPAIN_II         = 11,
        LATIN_AMERICA    = 12,
        KOREA            = 13, // Many printers stop here
        SLOVENIA_CROATIA = 14,
        CHINA            = 15,
        VIETNAM          = 16,
        ARABIA           = 17
    };


    /// \brief Code page enumeration.
    ///
    /// These enumeration values are non-standard (e.g. PC437 is usually known
    /// as CP437). They can be converted to more standard names using the
    /// to_string and from_string methods.
    ///
    /// \sa https://reference.epson-biz.com/modules/ref_charcode_en/index.php?content_id=118
	enum CodePage: uint8_t
    {
        PC437       = 0,   ///< USA, Standard Europe http://en.wikipedia.org/wiki/Code_page_437
        Katakana    = 1,   ///< Katakana
        PC850       = 2,   ///< Multilingual         http://en.wikipedia.org/wiki/Code_page_850
        PC860       = 3,   ///< Portuguese           http://en.wikipedia.org/wiki/Code_page_860
        PC863       = 4,   ///< Canadian-French      http://en.wikipedia.org/wiki/Code_page_863
        PC865       = 5,   ///< Nordic               http://en.wikipedia.org/wiki/Code_page_865

        PC851       = 11,  ///< Greek                http://en.wikipedia.org/wiki/Code_page_851
        PC853       = 12,  ///< Turkish              http://en.wikipedia.org/wiki/Code_page_853
        PC857       = 13,  ///< Turkish              http://en.wikipedia.org/wiki/Code_page_857
        PC737       = 14,  ///< Greek                http://en.wikipedia.org/wiki/Code_page_737
        ISO8859_7   = 15,  ///< Greek                http://en.wikipedia.org/wiki/ISO/IEC_8859-7
        WPC1252     = 16,  ///< Windows-1252         http://en.wikipedia.org/wiki/Windows-1252
        PC866       = 17,  ///< Cyrillic #2          http://en.wikipedia.org/wiki/Code_page_866
        PC852       = 18,  ///< Latin2               http://en.wikipedia.org/wiki/Code_page_852
        PC858       = 19,  ///< Euro                 http://en.wikipedia.org/wiki/Code_page_858
        KU42        = 20,  ///< Thai                 http://en.wikipedia.org/wiki/Code_page_866
        TIS11       = 21,  ///< Thai

        TIS18       = 26,  ///< Thai

        TCVN_3_I    = 30,  ///< Vietnamese (lower case)
        TCVN_3_II   = 31,  ///< Vietnamese (upper case)
        PC720       = 32,  ///< Arabic               http://en.wikipedia.org/wiki/Code_page_720
        PC775       = 33,  ///< Baltic Rim           http://en.wikipedia.org/wiki/Code_page_775
        PC855       = 34,  ///< Cyrillic             http://en.wikipedia.org/wiki/Code_page_855
        PC861       = 35,  ///< Icelandic            http://en.wikipedia.org/wiki/Code_page_861
        PC862       = 36,  ///< Hebrew               http://en.wikipedia.org/wiki/Code_page_862
        PC864       = 37,  ///< Arabic               http://en.wikipedia.org/wiki/Code_page_864
        PC869       = 38,  ///< Greek                http://en.wikipedia.org/wiki/Code_page_869
        ISO8859_2   = 39,  ///< Latin2               http://en.wikipedia.org/wiki/ISO/IEC_8859-2
        ISO8859_15  = 40,  ///< Latin9               http://en.wikipedia.org/wiki/ISO/IEC_8859-15
        PC1098      = 41,  ///< Farsi                http://www-01.ibm.com/software/globalization/ccsid/ccsid1098.html / https://en.wikipedia.org/wiki/Code_page_1098
        PC1118      = 42,  ///< Lithuanian           https://en.wikipedia.org/wiki/Code_page_1118 or CP772
        PC1119      = 43,  ///< Lithuanian           https://en.wikipedia.org/wiki/Code_page_1119 or CP774
        PC1125      = 44,  ///< Ukrainian            http://ascii-table.com/codepage.php?1125
        WPC1250     = 45,  ///< Latin2               http://en.wikipedia.org/wiki/Windows-1250
        WPC1251     = 46,  ///< Cyrillic             http://en.wikipedia.org/wiki/Windows-1251
        WPC1253     = 47,  ///< Greek                http://en.wikipedia.org/wiki/Windows-1253
        WPC1254     = 48,  ///< Turkish              http://en.wikipedia.org/wiki/Windows-1254
        WPC1255     = 49,  ///< Hebrew               http://en.wikipedia.org/wiki/Windows-1255
        WPC1256     = 50,  ///< Arabic               http://en.wikipedia.org/wiki/Windows-1256
        WPC1257     = 51,  ///< Baltic Rim           http://en.wikipedia.org/wiki/Windows-1257
        WPC1258     = 52,  ///< Vietnamese           http://en.wikipedia.org/wiki/Windows-1258
        KZ_1048     = 53,  ///< Kazakhstan           http://www.iana.org/assignments/charset-reg/KZ-1048

        UNKNOWN     = 254, ///< Unknown
        USER_PAGE   = 255  ///< User-defined page
    };


    enum BarcodeTextLocation: uint8_t
    {
        TEXT_NONE            = 0, ///< Not printed
        TEXT_ABOVE           = 1, ///< Above the bar code
        TEXT_BELOW           = 2, ///< Below the bar code
        TEXT_ABOVE_AND_BELOW = 3  ///< Both above and below the bar code
    };


    // for use with GS K n
    enum BarcodeType1D: uint8_t
    {
        UPC_A                       = 65, ///< http://en.wikipedia.org/wiki/Universal_Product_Code
        UPC_E                       = 66, ///< http://en.wikipedia.org/wiki/Universal_Product_Code#UPC-E
        EAN13 /* aka JAN13 */       = 67, ///< http://en.wikipedia.org/wiki/EAN13
        EAN8  /* aka JAN8 */        = 68, ///< http://en.wikipedia.org/wiki/EAN_8
        CODE39                      = 69, ///< http://en.wikipedia.org/wiki/Code39
        ITF   /* aka I25 */         = 70, ///< http://en.wikipedia.org/wiki/ITF-14
        CODABAR                     = 71, ///< http://en.wikipedia.org/wiki/Codabar
        CODE93                      = 72, ///< http://en.wikipedia.org/wiki/Code_93
        CODE128                     = 73, ///< http://en.wikipedia.org/wiki/Code_128
        GS1_128                     = 74, ///< http://en.wikipedia.org/wiki/GS1-128
        GS1_DATABAR_OMNIDIRECTIONAL = 75, ///< http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_TRUNCATED       = 76, ///< http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_LIMITED         = 77, ///< http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_EXPANDED        = 78, ///< http://en.wikipedia.org/wiki/GS1_DataBar
    };


    enum BarcodeType2D: uint8_t
    {
        PDF417                      = 48, ///< http://en.wikipedia.org/wiki/PDF417
        QR_CODE                     = 49, ///< http://en.wikipedia.org/wiki/QR_code
        MAXICODE                    = 50, ///< http://en.wikipedia.org/wiki/MaxiCode
        GS1_DATABAR_2D              = 51, ///< http://www.gs1.org/barcodes/technical/bar_code_types#data_matrix
        COMPOSITE_SYMBOLOGY         = 52  ///< http://www.tec-it.com/en/support/knowbase/symbologies/rss-codes/Default.aspx
    };


    enum RealTimeStatus: uint8_t
    {
        STATUS_PRINTER        = 1,
        STATUS_OFFLINE_CAUSE  = 2,
        STATUS_ERROR_CAUSE    = 3,
        STATUS_PAPER          = 4
    };


    /// \sa https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=196#gs_lparen_ca
    enum TestPrintPaper: uint8_t
    {
        TEST_PRINT_PAPER_SHEET = 0,
        TEST_PRINT_PAPER_ROLL = 1
    };

    /// \sa https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=196#gs_lparen_ca
    enum TestPrintPattern: uint8_t
    {
        TEST_PRINT_PATTERN_HEX_DUMP = 1,
        TEST_PRINT_PATTERN_STATUS = 2,
        TEST_PRINT_PATTERN_ROLLING = 3,
        TEST_PRINT_PATTERN_AUTO_SET_PAPER_LAYOUT = 64
    };

};


inline std::string to_string(Codes::CodePage page)
{
    switch (page)
    {
        case Codes::CodePage::PC437: return "CP437";
        case Codes::CodePage::Katakana: return "CP932";//Katakana"; https://mike42.me/blog/2018-05-how-to-print-the-characters-in-an-esc-pos-printer-code-page
        case Codes::CodePage::PC850: return "CP850";
        case Codes::CodePage::PC860: return "CP860";
        case Codes::CodePage::PC863: return "CP863";
        case Codes::CodePage::PC865: return "CP865";
        case Codes::CodePage::PC851: return "CP851";
        case Codes::CodePage::PC853: return "CP853";
        case Codes::CodePage::PC857: return "CP857";
        case Codes::CodePage::PC737: return "CP737";
        case Codes::CodePage::ISO8859_7: return "ISO8859-7";
        case Codes::CodePage::WPC1252: return "CP1252";
        case Codes::CodePage::PC866: return "CP866";
        case Codes::CodePage::PC852: return "CP852";
        case Codes::CodePage::PC858: return "CP858";
        case Codes::CodePage::KU42: return "KU42";
        case Codes::CodePage::TIS11: return "TIS-620";// TIS11"; https://github.com/mike42/escpos-php/issues/51
        case Codes::CodePage::TIS18: return "TIS18";
        case Codes::CodePage::TCVN_3_I: return "TCVN_3_I";
        case Codes::CodePage::TCVN_3_II: return "TCVN_3_II";
        case Codes::CodePage::PC720: return "CP720";
        case Codes::CodePage::PC775: return "CP775";
        case Codes::CodePage::PC855: return "CP855";
        case Codes::CodePage::PC861: return "CP861";
        case Codes::CodePage::PC862: return "CP862";
        case Codes::CodePage::PC864: return "CP864";
        case Codes::CodePage::PC869: return "CP869";
        case Codes::CodePage::ISO8859_2: return "ISO8859-2";
        case Codes::CodePage::ISO8859_15: return "ISO8859-15";
        case Codes::CodePage::PC1098: return "CP1098"; // URDU https://en.wikipedia.org/wiki/Code_page_1098
        case Codes::CodePage::PC1118: return "CP774"; // aka 774 https://en.wikipedia.org/wiki/Code_page_1118
        case Codes::CodePage::PC1119: return "CP772"; // aka 772 https://en.wikipedia.org/wiki/Code_page_1119
        case Codes::CodePage::PC1125: return "CP1125";
        case Codes::CodePage::WPC1250: return "CP1250";
        case Codes::CodePage::WPC1251: return "CP1251";
        case Codes::CodePage::WPC1253: return "CP1253";
        case Codes::CodePage::WPC1254: return "CP1254";
        case Codes::CodePage::WPC1255: return "CP1255";
        case Codes::CodePage::WPC1256: return "CP1256";
        case Codes::CodePage::WPC1257: return "CP1257";
        case Codes::CodePage::WPC1258: return "CP1258";
        case Codes::CodePage::KZ_1048: return "KZ-1048";
        case Codes::CodePage::UNKNOWN: return "UNKNOWN";
        case Codes::CodePage::USER_PAGE: return "USER_PAGE";
    }

    return "UNKNOWN";
}


inline Codes::CodePage from_string(std::string page)
{
    if (page == to_string(Codes::PC437)) return Codes::PC437;
    else if (page == to_string(Codes::Katakana)) return Codes::Katakana;
    else if (page == to_string(Codes::PC850)) return Codes::PC850;
    else if (page == to_string(Codes::PC860)) return Codes::PC860;
    else if (page == to_string(Codes::PC863)) return Codes::PC863;
    else if (page == to_string(Codes::PC865)) return Codes::PC865;

    else if (page == to_string(Codes::PC851)) return Codes::PC851;
    else if (page == to_string(Codes::PC853)) return Codes::PC853;
    else if (page == to_string(Codes::PC857)) return Codes::PC857;
    else if (page == to_string(Codes::PC737)) return Codes::PC737;
    else if (page == to_string(Codes::ISO8859_7)) return Codes::ISO8859_7;
    else if (page == to_string(Codes::WPC1252)) return Codes::WPC1252;
    else if (page == to_string(Codes::PC866)) return Codes::PC866;
    else if (page == to_string(Codes::PC852)) return Codes::PC852;
    else if (page == to_string(Codes::PC858)) return Codes::PC858;
    else if (page == to_string(Codes::KU42)) return Codes::KU42;
    else if (page == to_string(Codes::TIS11)) return Codes::TIS11;

    else if (page == to_string(Codes::TIS18)) return Codes::TIS18;

    else if (page == to_string(Codes::TCVN_3_I)) return Codes::TCVN_3_I;
    else if (page == to_string(Codes::TCVN_3_II)) return Codes::TCVN_3_II;
    else if (page == to_string(Codes::PC720)) return Codes::PC720;
    else if (page == to_string(Codes::PC775)) return Codes::PC775;
    else if (page == to_string(Codes::PC855)) return Codes::PC855;
    else if (page == to_string(Codes::PC861)) return Codes::PC861;
    else if (page == to_string(Codes::PC862)) return Codes::PC862;
    else if (page == to_string(Codes::PC864)) return Codes::PC864;
    else if (page == to_string(Codes::PC869)) return Codes::PC869;
    else if (page == to_string(Codes::ISO8859_2)) return Codes::ISO8859_2;
    else if (page == to_string(Codes::ISO8859_15)) return Codes::ISO8859_15;
    else if (page == to_string(Codes::PC1098)) return Codes::PC1098;
    else if (page == to_string(Codes::PC1118)) return Codes::PC1118;
    else if (page == to_string(Codes::PC1119)) return Codes::PC1119;
    else if (page == to_string(Codes::PC1125)) return Codes::PC1125;
    else if (page == to_string(Codes::WPC1250)) return Codes::WPC1250;
    else if (page == to_string(Codes::WPC1251)) return Codes::WPC1251;
    else if (page == to_string(Codes::WPC1253)) return Codes::WPC1253;
    else if (page == to_string(Codes::WPC1254)) return Codes::WPC1254;
    else if (page == to_string(Codes::WPC1255)) return Codes::WPC1255;
    else if (page == to_string(Codes::WPC1256)) return Codes::WPC1256;
    else if (page == to_string(Codes::WPC1257)) return Codes::WPC1257;
    else if (page == to_string(Codes::WPC1258)) return Codes::WPC1258;
    else if (page == to_string(Codes::KZ_1048)) return Codes::KZ_1048;

    else if (page == to_string(Codes::UNKNOWN)) return Codes::UNKNOWN;
    else if (page == to_string(Codes::USER_PAGE)) return Codes::USER_PAGE;

    return Codes::CodePage::UNKNOWN;
}


inline void to_json(nlohmann::json& j, const Codes::CodePage& v)
{
    j = to_string(v);
}


inline void from_json(const nlohmann::json& j, Codes::CodePage& v)
{
    v = from_string(j);
}



} } // namespace ofx::ESCPOS
