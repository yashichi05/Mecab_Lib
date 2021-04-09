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
int main(int argc, char **argv)
{
    concurrency::reader_writer_lock extenMutex;
    HMODULE module = LoadLibraryW(L"visual Extension.dll");
    auto callback = (decltype(Extension::callback))GetProcAddress(module, "OnNewSentence");
    std::scoped_lock writeLock(extenMutex);
    std::array<InfoForExtension, 10> b_ary{{
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
    InfoForExtension *b = b_ary.data();
    // b->name = "vs";
    callback(L"aaaa999999999999999999999999999999999", b);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // std::cin.get();
}