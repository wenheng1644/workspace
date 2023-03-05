//
// Created by 文恒 on 2022/4/16.
//

#ifndef CLIENT_CODE_CONVERT_H
#define CLIENT_CODE_CONVERT_H

#include <codecvt>
#include <locale>

#include <string>


namespace coding {

#ifdef _WIN32
    //GBK locale name in windows
    inline constexpr const char * GBK_LOCALE_NAME = ".936";
#else
    inline constexpr const char * GBK_LOCALE_NAME = "zh_CN.GBK";
#endif

    /**
     * utf-8 --> wchar
     * @param _utf8 要求std::string的编码是utf-8
     * @return 宽字符串
     */
    std::wstring utf8_to_wstr(const std::string& _utf8);

    /**
     * wchar --> utf-8
     * @param _wstr 宽字符串
     * @return 转化为utf-8 编码的字符串
     */
    std::string wstr_to_utf8(const std::wstring& _wstr);

    /**
     * utf-8 --> gbk
     * @param _utf8 utf-8
     * @return gbk
     */
    std::string utf8_to_gbk(const std::string& _utf8);

    /**
     * gbk --> utf-8
     * @param _gbk gbk
     * @return utf-8
     */
    std::string gbk_to_utf8(const std::string& _gbk);

    /**
     * gbk --> std::wstring
     * @param _gbk gbk
     * @return 宽字符串
     */
    std::wstring gbk_to_wstr(const std::string& _gbk);

    /**
     * std::wstring --> gbk
     * @param _wstr 宽字符串
     * @return gbk
     */
    std::string wstr_to_gbk(const std::wstring& _wstr);
}

#endif //CLIENT_CODE_CONVERT_H
