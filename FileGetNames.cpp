#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <array>
#include "FileGetNames.h"
#include "FormLoad.h"

std::string convert(const std::wstring& wstr)
{
    const int BUFF_SIZE = 7;
    if (MB_CUR_MAX >= BUFF_SIZE) throw std::invalid_argument("BUFF_SIZE too small");
    std::string result;
    bool shifts = std::wctomb(nullptr, 0);  // reset the conversion state
    for (const wchar_t wc : wstr)
    {
        std::array<char, BUFF_SIZE> buffer;
        const int ret = std::wctomb(buffer.data(), wc);
        if (ret < 0) errorForm("inconvertible wide characters in the current locale");
        buffer[ret] = '\0';  // make 'buffer' contain a C-style string
        result = result + std::string(buffer.data());
    }
    return result;
}

void getfilename(std::vector<std::string>& names, std::wstring Dir)
{
    WIN32_FIND_DATAW wfd;
    std::wstring Direct = Dir + std::wstring(L"\\*.wav");
    HANDLE const hFind = FindFirstFileW(Direct.c_str(), &wfd);
    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            names.push_back(convert(Dir.c_str())+ "\\" + convert(&wfd.cFileName[0]));
        } while (NULL != FindNextFileW(hFind, &wfd));

        FindClose(hFind);
    }
}