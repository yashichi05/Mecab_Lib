#include <iostream>
#include <Windows.h>

int main(int argc, char **argv){
    LoadLibraryW(L"mecabWindow.dll");
    return 0;
}