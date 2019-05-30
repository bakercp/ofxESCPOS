//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


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
        PC1098      = 41,  ///< Farsi                http://www-01.ibm.com/software/globalization/ccsid/ccsid1098.html
        PC1118      = 42,  ///< Lithuanian
        PC1119      = 43,  ///< Lithuanian
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

};


inline std::string to_string(Codes::CodePage page)
{
    switch (page)
    {
        case Codes::CodePage::PC437: return "PC437";
        case Codes::CodePage::Katakana: return "Katakana";
        case Codes::CodePage::PC850: return "PC850";
        case Codes::CodePage::PC860: return "PC860";
        case Codes::CodePage::PC863: return "PC863";
        case Codes::CodePage::PC865: return "PC865";
        case Codes::CodePage::PC851: return "PC851";
        case Codes::CodePage::PC853: return "PC853";
        case Codes::CodePage::PC857: return "PC857";
        case Codes::CodePage::PC737: return "PC737";
        case Codes::CodePage::ISO8859_7: return "ISO8859_7";
        case Codes::CodePage::WPC1252: return "WPC1252";
        case Codes::CodePage::PC866: return "PC866";
        case Codes::CodePage::PC852: return "PC852";
        case Codes::CodePage::PC858: return "PC858";
        case Codes::CodePage::KU42: return "KU42";
        case Codes::CodePage::TIS11: return "TIS11";
        case Codes::CodePage::TIS18: return "TIS18";
        case Codes::CodePage::TCVN_3_I: return "TCVN_3_I";
        case Codes::CodePage::TCVN_3_II: return "TCVN_3_II";
        case Codes::CodePage::PC720: return "PC720";
        case Codes::CodePage::PC775: return "PC775";
        case Codes::CodePage::PC855: return "PC855";
        case Codes::CodePage::PC861: return "PC861";
        case Codes::CodePage::PC862: return "PC862";
        case Codes::CodePage::PC864: return "PC864";
        case Codes::CodePage::PC869: return "PC869";
        case Codes::CodePage::ISO8859_2: return "ISO8859_2";
        case Codes::CodePage::ISO8859_15: return "ISO8859_15";
        case Codes::CodePage::PC1098: return "PC1098";
        case Codes::CodePage::PC1118: return "PC1118";
        case Codes::CodePage::PC1119: return "PC1119";
        case Codes::CodePage::PC1125: return "PC1125";
        case Codes::CodePage::WPC1250: return "WPC1250";
        case Codes::CodePage::WPC1251: return "WPC1251";
        case Codes::CodePage::WPC1253: return "WPC1253";
        case Codes::CodePage::WPC1254: return "WPC1254";
        case Codes::CodePage::WPC1255: return "WPC1255";
        case Codes::CodePage::WPC1256: return "WPC1256";
        case Codes::CodePage::WPC1257: return "WPC1257";
        case Codes::CodePage::WPC1258: return "WPC1258";
        case Codes::CodePage::KZ_1048: return "KZ_1048";
        case Codes::CodePage::UNKNOWN: return "UNKNOWN";
        case Codes::CodePage::USER_PAGE: return "USER_PAGE";
    }

    return "UNKNOWN";
}


inline Codes::CodePage from_string(std::string page)
{
    if (page == "PC437") return Codes::CodePage::PC437;
    else if (page == "Katakana") return Codes::CodePage::Katakana;
    else if (page == "PC850") return Codes::CodePage::PC850;
    else if (page == "PC860") return Codes::CodePage::PC860;
    else if (page == "PC863") return Codes::CodePage::PC863;
    else if (page == "PC865") return Codes::CodePage::PC865;
    else if (page == "PC851") return Codes::CodePage::PC851;
    else if (page == "PC853") return Codes::CodePage::PC853;
    else if (page == "PC857") return Codes::CodePage::PC857;
    else if (page == "PC737") return Codes::CodePage::PC737;
    else if (page == "ISO8859_7") return Codes::CodePage::ISO8859_7;
    else if (page == "WPC1252") return Codes::CodePage::WPC1252;
    else if (page == "PC866") return Codes::CodePage::PC866;
    else if (page == "PC852") return Codes::CodePage::PC852;
    else if (page == "PC858") return Codes::CodePage::PC858;
    else if (page == "KU42") return Codes::CodePage::KU42;
    else if (page == "TIS11") return Codes::CodePage::TIS11;
    else if (page == "TIS18") return Codes::CodePage::TIS18;
    else if (page == "TCVN_3_I") return Codes::CodePage::TCVN_3_I;
    else if (page == "TCVN_3_II") return Codes::CodePage::TCVN_3_II;
    else if (page == "PC720") return Codes::CodePage::PC720;
    else if (page == "PC775") return Codes::CodePage::PC775;
    else if (page == "PC855") return Codes::CodePage::PC855;
    else if (page == "PC861") return Codes::CodePage::PC861;
    else if (page == "PC862") return Codes::CodePage::PC862;
    else if (page == "PC864") return Codes::CodePage::PC864;
    else if (page == "PC869") return Codes::CodePage::PC869;
    else if (page == "ISO8859_2") return Codes::CodePage::ISO8859_2;
    else if (page == "ISO8859_15") return Codes::CodePage::ISO8859_15;
    else if (page == "PC1098") return Codes::CodePage::PC1098;
    else if (page == "PC1118") return Codes::CodePage::PC1118;
    else if (page == "PC1119") return Codes::CodePage::PC1119;
    else if (page == "PC1125") return Codes::CodePage::PC1125;
    else if (page == "WPC1250") return Codes::CodePage::WPC1250;
    else if (page == "WPC1251") return Codes::CodePage::WPC1251;
    else if (page == "WPC1253") return Codes::CodePage::WPC1253;
    else if (page == "WPC1254") return Codes::CodePage::WPC1254;
    else if (page == "WPC1255") return Codes::CodePage::WPC1255;
    else if (page == "WPC1256") return Codes::CodePage::WPC1256;
    else if (page == "WPC1257") return Codes::CodePage::WPC1257;
    else if (page == "WPC1258") return Codes::CodePage::WPC1258;
    else if (page == "KZ_1048") return Codes::CodePage::KZ_1048;
    else if (page == "UNKNOWN") return Codes::CodePage::UNKNOWN;
    else if (page == "USER_PAGE") return Codes::CodePage::USER_PAGE;

    return Codes::CodePage::UNKNOWN;
}


} } // namespace ofx::ESCPOS
