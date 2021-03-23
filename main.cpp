#include <iostream>
#include <locale>
#include <windows.h>
#include "mecab.h"
#include <string>

int main()
{
    //   std::locale::global(std::locale("ja.UTF-8"));
    // HMODULE lib = LoadLibraryW(L"libmecab");
    int abc = 1234;
    std::cout << abc << std::endl;
    std::cout << "abc";
    char input[1024] = "太郎は次郎が持っている本を花子に渡した。";

    mecab_t *tagger = mecab_new2("");
    const char *res = mecab_sparse_tostr(tagger, input);
    std::cout << "INPUT: " << input << std::endl;
    std::cout << "RESULT: " << res << std::endl;
    std::cin.get();
    return 0;
}