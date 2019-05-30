//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <vector>
#include "ofx/ESCPOS/Codes.h"


namespace ofx {
namespace ESCPOS {


class PrinterProfile
{
public:
    PrinterProfile();
    ~PrinterProfile();

    std::size_t printHeadWidthPixels = DEFAULT_PRINT_HEAD_WIDTH_PIXELS;
    std::size_t printHeadHeightPixels = DEFAULT_PRINT_HEAD_HEIGHT_PIXELS;
    std::vector<Codes::CodePage> codePages;

    static const std::size_t DEFAULT_PRINT_HEAD_WIDTH_PIXELS = 576;
    static const std::size_t DEFAULT_PRINT_HEAD_HEIGHT_PIXELS = 24;
    static const std::vector<Codes::CodePage> DEFAULT_CODE_PAGES;
};


inline void to_json(nlohmann::json& j, const PrinterProfile& v)
{
    j["code_pages"] = v.codePages;
    j["print_head"]["width"]["pixels"] = v.printHeadWidthPixels;
    j["print_head"]["height"]["pixels"] = v.printHeadHeightPixels;
}


inline void from_json(const nlohmann::json& j, PrinterProfile& v)
{
    v.codePages = j.value("code_pages", std::vector<Codes::CodePage>());

    nlohmann::json printHead = j.value("print_head", nlohmann::json());

    if (!printHead.is_null())
    {
        nlohmann::json width = j.value("width", nlohmann::json());
        nlohmann::json height = j.value("height", nlohmann::json());

        if (!width.is_null())
            v.printHeadWidthPixels = j.value("pixels", PrinterProfile::DEFAULT_PRINT_HEAD_WIDTH_PIXELS);

        if (!height.is_null())
            v.printHeadHeightPixels = j.value("pixels", PrinterProfile::DEFAULT_PRINT_HEAD_HEIGHT_PIXELS);
    }
}


} } // namespace ofx::ESCPOS
