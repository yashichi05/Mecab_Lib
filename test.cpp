#include <iostream>
#include <Windows.h>
#include "Extension.h"


struct Extension
{
    std::wstring name;
    wchar_t *(*callback)(std::wstring&, const InfoForExtension *);
};
int main(int argc, char **argv)
{
    HMODULE module = LoadLibraryW(L"vExten.dll");
    auto callback = (decltype(Extension::callback))GetProcAddress(module, "OnNewSentence");
    InfoForExtension *b;
    b->value = 0;
    b->name = "vs";
    std::wstring a = L"aaaa";
    callback(a,b);
}