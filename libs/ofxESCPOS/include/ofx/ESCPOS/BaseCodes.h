//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


namespace ofx {
namespace ESCPOS {


class BaseCodes
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
        NUL = 0,  // Null
        SOH = 1,  // Start of heading
        STX = 2,  // Start of text
        ETX = 3,  // End of text
        EOT = 4,  // End of text
        ENQ = 5,  // Enquiry
        ACK = 6,  // Achknowledge
        BEL = 7,  // Bell
        BS  = 8,  // Backspace
        HT  = 9,  // Horizontal tab
        LF  = 10, // NL line feed, new line
        VT  = 11, // Vertical tab
        FF  = 12, // NP form feed, new page
        CR  = 13, // Carriage return
        SO  = 14, // Shift out
        SI  = 15, // Shift in
        DLE = 16, // Data link escape
        DC1 = 17, // Device control 1
        DC2 = 18, // Device control 1
        DC3 = 19, // Device control 1
        DC4 = 20, // Device control 1
        NAK = 21, // Negative acknowlege
        SYN = 22, // Synchronous idle
        ETB = 23, // End of transmission block
        CAN = 24, // Cancel
        EM  = 25, // End of medium
        SUB = 26, // Substitute
        ESC = 27, // Escape
        FS  = 28, // File seperator
        GS  = 29, // Group seperator
        RS  = 30, // Record seperator
        US  = 31  // Unit seperator
    };


	enum PrintMode: uint8_t
    {
        MODE_STANDARD,
        MODE_PAGE
    };


	enum TextFont: uint8_t
    {
        FONT_A  = 0, // Character font A (12 x 24 normally)
        FONT_B  = 1, // Character font B (9 x 17 normally)
        FONT_C  = 2  // Character font C (optional)
    };


	enum TextUnderline: uint8_t
    {
        UNDERLINE_OFF    = 0, // Underline off
        UNDERLINE_NORMAL = 1, // Underline 1 dot thick
        UNDERLINE_THICK  = 2  // Underline 2 dots thick
    };


	enum TextAlignment: uint8_t
    {
        ALIGN_LEFT    = 0, // Align text left
        ALIGN_CENTER  = 1, // Align text center
        ALIGN_RIGHT   = 2  // Align text right
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
        ROTATE_OFF    = 0, // Rotate off
        ROTATE_90_CW  = 1, // Rotate 90deg clockwise
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
        COLOR_1  = 0, // Black (normally)
        COLOR_2  = 1, // Red (normally)
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


	enum CodePage: uint8_t
    {
        PC437       = 0,   /// USA, Standard Europe http://en.wikipedia.org/wiki/Code_page_437
        Katakana    = 1,   /// Katakana
        PC850       = 2,   /// Multilingual         http://en.wikipedia.org/wiki/Code_page_850
        PC860       = 3,   /// Portuguese           http://en.wikipedia.org/wiki/Code_page_860
        PC863       = 4,   /// Canadian-French      http://en.wikipedia.org/wiki/Code_page_863
        PC865       = 5,   /// Nordic               http://en.wikipedia.org/wiki/Code_page_865
        PC851       = 11,  /// Greek                http://en.wikipedia.org/wiki/Code_page_851
        PC853       = 12,  /// Turkish              http://en.wikipedia.org/wiki/Code_page_853
        PC857       = 13,  /// Turkish              http://en.wikipedia.org/wiki/Code_page_857
        PC737       = 14,  /// Greek                http://en.wikipedia.org/wiki/Code_page_737
        ISO8859_7   = 15,  /// Greek                http://en.wikipedia.org/wiki/ISO/IEC_8859-7
        WPC1252     = 16,  /// Windows-1252         http://en.wikipedia.org/wiki/Windows-1252
        PC866       = 17,  /// Cyrillic #2          http://en.wikipedia.org/wiki/Code_page_866
        PC852       = 18,  /// Latin2               http://en.wikipedia.org/wiki/Code_page_852
        PC858       = 19,  /// Euro                 http://en.wikipedia.org/wiki/Code_page_858
        KU42        = 20,  /// Thai                 http://en.wikipedia.org/wiki/Code_page_866
        TIS11       = 21,  /// Thai
        TIS18       = 26,  /// Thai
        TCVN_3_I    = 30,  /// Vietnamese (lower case)
        TCVN_3_II   = 31,  /// Vietnamese (upper case)
        PC720       = 32,  /// Arabic               http://en.wikipedia.org/wiki/Code_page_720
        PC775       = 33,  /// Baltic Rim           http://en.wikipedia.org/wiki/Code_page_775
        PC855       = 34,  /// Cyrillic             http://en.wikipedia.org/wiki/Code_page_855
        PC861       = 35,  /// Icelandic            http://en.wikipedia.org/wiki/Code_page_861
        PC862       = 36,  /// Hebrew               http://en.wikipedia.org/wiki/Code_page_862
        PC864       = 37,  /// Arabic               http://en.wikipedia.org/wiki/Code_page_864
        PC869       = 38,  /// Greek                http://en.wikipedia.org/wiki/Code_page_869
        ISO8859_2   = 39,  /// Latin2               http://en.wikipedia.org/wiki/ISO/IEC_8859-2
        ISO8859_15  = 40,  /// Latin9               http://en.wikipedia.org/wiki/ISO/IEC_8859-15
        PC1098      = 41,  /// Farsi                http://www-01.ibm.com/software/globalization/ccsid/ccsid1098.html
        PC1118      = 42,  /// Lithuanian
        PC1119      = 43,  /// Lithuanian
        PC1125      = 44,  /// Ukrainian            http://ascii-table.com/codepage.php?1125
        WPC1250     = 45,  /// Latin2               http://en.wikipedia.org/wiki/Windows-1250
        WPC1251     = 46,  /// Cyrillic             http://en.wikipedia.org/wiki/Windows-1251
        WPC1253     = 47,  /// Greek                http://en.wikipedia.org/wiki/Windows-1253
        WPC1254     = 48,  /// Turkish              http://en.wikipedia.org/wiki/Windows-1254
        WPC1255     = 49,  /// Hebrew               http://en.wikipedia.org/wiki/Windows-1255
        WPC1256     = 50,  /// Arabic               http://en.wikipedia.org/wiki/Windows-1256
        WPC1257     = 51,  /// Baltic Rim           http://en.wikipedia.org/wiki/Windows-1257
        WPC1258     = 52,  /// Vietnamese           http://en.wikipedia.org/wiki/Windows-1258
        KZ_1048     = 53,  /// Kazakhstan           http://www.iana.org/assignments/charset-reg/KZ-1048
        USER_PAGE   = 255  /// User-defined page
    };


    enum BarcodeTextLocation: uint8_t
    {
        TEXT_NONE            = 0, /// Not printed
        TEXT_ABOVE           = 1, /// Above the bar code
        TEXT_BELOW           = 2, /// Below the bar code
        TEXT_ABOVE_AND_BELOW = 3  /// Both above and below the bar code
    };


    // for use with GS K n
    enum BarcodeType1D: uint8_t
    {
        UPC_A                       = 65, /// http://en.wikipedia.org/wiki/Universal_Product_Code
        UPC_E                       = 66, /// http://en.wikipedia.org/wiki/Universal_Product_Code#UPC-E
        EAN13 /* aka JAN13 */       = 67, /// http://en.wikipedia.org/wiki/EAN13
        EAN8  /* aka JAN8 */        = 68, /// http://en.wikipedia.org/wiki/EAN_8
        CODE39                      = 69, /// http://en.wikipedia.org/wiki/Code39
        ITF   /* aka I25 */         = 70, /// http://en.wikipedia.org/wiki/ITF-14
        CODABAR                     = 71, /// http://en.wikipedia.org/wiki/Codabar
        CODE93                      = 72, /// http://en.wikipedia.org/wiki/Code_93
        CODE128                     = 73, /// http://en.wikipedia.org/wiki/Code_128
        GS1_128                     = 74, /// http://en.wikipedia.org/wiki/GS1-128
        GS1_DATABAR_OMNIDIRECTIONAL = 75, /// http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_TRUNCATED       = 76, /// http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_LIMITED         = 77, /// http://en.wikipedia.org/wiki/GS1_DataBar
        GS1_DATABAR_EXPANDED        = 78, /// http://en.wikipedia.org/wiki/GS1_DataBar
    };


    enum BarcodeType2D: uint8_t
    {
        PDF417                      = 48, /// http://en.wikipedia.org/wiki/PDF417
        QR_CODE                     = 49, /// http://en.wikipedia.org/wiki/QR_code
        MAXICODE                    = 50, /// http://en.wikipedia.org/wiki/MaxiCode
        GS1_DATABAR_2D              = 51, /// http://www.gs1.org/barcodes/technical/bar_code_types#data_matrix
        COMPOSITE_SYMBOLOGY         = 52  /// http://www.tec-it.com/en/support/knowbase/symbologies/rss-codes/Default.aspx
    };


    enum RealTimeStatus: uint8_t
    {
        STATUS_PRINTER        = 1,
        STATUS_OFFLINE_CAUSE  = 2,
        STATUS_ERROR_CAUSE    = 3,
        STATUS_PAPER          = 4
    };

};


} } // namespace ofx::ESCPOS
