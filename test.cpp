#include <iostream>
#include <Windows.h>
#include "Extension.h"
#include <array>
#include <concrt.h>
#include <mutex>

struct Extension
{
    std::wstring name;
    wchar_t *(*callback)(wchar_t *, const InfoForExtension *);
};

std::array<InfoForExtension, 10> info_ary{{
    {"current select", 1},
    {"text number", 1},
    {"process id", 2},
    {"hook address", 3},
    {"text handle", 4},
    {"text name", 5},
    {"void (*AddSentence)(int64_t number, const wchar_t* sentence)", 6},
    {"void (*AddText)(int64_t number, const wchar_t* text)", 7},
    {"DWORD (*GetSelectedProcessId)()", 8},
    {nullptr, 0} // nullptr marks end of info array
}};
InfoForExtension *info_arg = info_ary.data();
int main(int argc, char **argv)
{
    HMODULE module = LoadLibraryW(L"addMecab.dll");
    auto callback = (decltype(Extension::callback))GetProcAddress(module, "OnNewSentence");

    callback(L"今日もしないとね。", info_arg);
    // MSG msg = {};
    // while (GetMessage(&msg, NULL, 0, 0))
    // {
    //     TranslateMessage(&msg);
    //     DispatchMessage(&msg);
    // }
}