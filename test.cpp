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
    HMODULE module = LoadLibraryW(L"testmecab.dll");
    auto callback = (decltype(Extension::callback))GetProcAddress(module, "OnNewSentence");

    callback(L"ウィキはウィキソフトウェア（ウィキエンジンとも呼ばれる）上で動作する。ウィキソフトウェアはコンテンツ管理システムの一種であるが、サイト所有者や特定のユーザーによってコンテンツが作られるわけではないという点において、ブログなど他のコンテンツ管理システムとは異なる。またウィキには固まったサイト構造というものはなく、サイトユーザーのニーズに沿って様々にサイト構造を作り上げることが可能であり、そうした点でも他のシステムとは異なっている[2]。", info_arg);
    // MSG msg = {};
    // while (GetMessage(&msg, NULL, 0, 0))
    // {
    //     TranslateMessage(&msg);
    //     DispatchMessage(&msg);
    // }
}