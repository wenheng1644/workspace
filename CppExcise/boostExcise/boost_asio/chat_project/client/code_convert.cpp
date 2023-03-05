//
// Created by 文恒 on 2022/4/16.
//

#include "code_convert.h"


// 包装 wstring/wbuffer_convert 所用的绑定本地环境平面的工具
template<class Facet>
struct deletable_facet : Facet
{
    template<class ...Args>
    explicit deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
    ~deletable_facet() override = default;
};


std::wstring coding::utf8_to_wstr(const std::string &_utf8) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(_utf8);
}

std::string coding::wstr_to_utf8(const std::wstring &_wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    return convert.to_bytes(_wstr);
}

std::string coding::utf8_to_gbk(const std::string &_utf8) {
    std::wstring tmp_wstr = utf8_to_wstr(_utf8);
    return wstr_to_gbk(tmp_wstr);
}

std::string coding::gbk_to_utf8(const std::string &_gbk) {
    std::wstring tmp_wstr = gbk_to_wstr(_gbk);
    return wstr_to_utf8(tmp_wstr);
}

std::wstring coding::gbk_to_wstr(const std::string &_gbk) {
    using codecvt = deletable_facet<std::codecvt_byname<wchar_t, char, mbstate_t>>;
    std::wstring_convert<codecvt> convert(new codecvt(GBK_LOCALE_NAME));
    return convert.from_bytes(_gbk);
}

std::string coding::wstr_to_gbk(const std::wstring& _wstr) {
    using codecvt = deletable_facet<std::codecvt_byname<wchar_t, char, mbstate_t>>;
    std::wstring_convert<codecvt> convert(new codecvt(GBK_LOCALE_NAME));
    return convert.to_bytes(_wstr);
}