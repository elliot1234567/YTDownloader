#pragma once
#include <cstring>
#include <algorithm>
#include <tchar.h>
#include <wtypes.h>
#include <winnt.h>
#include <string>

static class Converters
{
    static void lptstr2str(LPTSTR tch, char*& pch) // or (TCHAR* tch, char* &pch)
    {
#ifndef UNICODE
        std::memcpy(pch, tch, strlen(tch) + 1);
#else
        size_t n =
            sizeof(TCHAR) / sizeof(char) * wcsnlen(tch, std::string::npos);
        pch = new char[n + 1];
        std::memcpy(pch, tch, n + 1);
        int len = n - std::count(pch, pch + n, NULL);
        std::remove(pch, pch + n, NULL);
        pch[len] = NULL;
#endif
    }
};