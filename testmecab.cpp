#include "Extension.h"
#include "testmecab.h"


bool ProcessSentence(std::wstring &sentence, SentenceInfo sentenceInfo)
{
    // QString a("abcdefg");
    // std::cout.write("abcdefg",2);
    // a.truncate(2);
    // std::cout << a.toUtf8().constData();
    // QString pronounce("");
    // QStringList pronounce_list = pronounce.split(',');
    // std::cout << pronounce_list.takeLast().toUtf8().constData();
    useMecab res(sentence);
    std::wcout << sentence;
    return false;
}