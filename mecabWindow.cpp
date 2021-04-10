﻿#include <iostream>
#include <locale>
#include <windows.h>
#include "mecab/mecab.h"
#include <string>
#include "Extension.h"
#include <QString>

#define CHECK(eval)                                               \
    if (!eval)                                                    \
    {                                                             \
        fprintf(stderr, "Exception:%s\n", mecab_strerror(mecab)); \
        mecab_destroy(mecab);                                     \
        return false;                                             \
    }
#define BUFFER_SIZE 100

inline QString S(const std::string &s) { return QString::fromStdString(s); }
inline QString S(const std::wstring &s) { return QString::fromStdWString(s); }

bool ProcessSentence(std::wstring &sentence, SentenceInfo sentenceInfo)
{
    // char input[] = u8"今日もしないとね。";
    QString input_qs(S(sentence));
    // char input[999];
    QByteArray ba = input_qs.toLocal8Bit();
    char *input = ba.data();
    // strcpy(o_i, input);
    char *argv = "";
    //
    //

    mecab_t *mecab = mecab_new(0, &argv);
    CHECK(mecab);

    // 取得結果
    const char *res1 = mecab_sparse_tostr(mecab, input);
    CHECK(res1);
    std::cout << "result" << std::endl;
    std::cout << res1 << std::endl;
    //
    //
    //

    // 取的前n個最好結果
    mecab_set_lattice_level(mecab, 1);
    // 全部結果
    const char *res2 = mecab_nbest_sparse_tostr(mecab, 2, input);
    CHECK(res2);
    std::cout << "n result" << std::endl;
    std::cout << res2 << std::endl;

    CHECK(mecab_nbest_init(mecab, input));
    //一個一個取
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "number " << i << std::endl;
        std::cout << mecab_nbest_next_tostr(mecab) << std::endl;
    }
    //
    //
    //

    std::cout << "get node object" << std::endl;
    const mecab_node_t *node = mecab_sparse_tonode(mecab, input);
    CHECK(node);
    for (; node; node = node->next)
    {
        if (node->stat == MECAB_NOR_NODE || node->stat == MECAB_UNK_NODE)
        {
            //剩餘的字
            std::cout << node->surface << std::endl;
            // 解析字數
            std::cout << node->length << std::endl;
            // 當下解析字(剩餘字,當前解析字數) ，顯示字串的前N個
            std::cout.write(node->surface, node->length) << std::endl;
            //後面的解析
            std::cout << node->feature << std::endl;
        }
    }
    //
    //
    //

    // // Dictionary info
    // const mecab_dictionary_info_t *d = mecab_dictionary_info(mecab);
    // for (; d; d = d->next)
    // {
    //     printf("filename: %s\n", d->filename);
    //     printf("charset: %s\n", d->charset);
    //     printf("size: %d\n", d->size);
    //     printf("type: %d\n", d->type);
    //     printf("lsize: %d\n", d->lsize);
    //     printf("rsize: %d\n", d->rsize);
    //     printf("version: %d\n", d->version);
    // }

    mecab_destroy(mecab);
    return false;
}