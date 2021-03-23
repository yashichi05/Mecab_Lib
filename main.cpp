#include <iostream>
#include <locale>
#include <windows.h>
#include "mecab/mecab.h"
#include <string>

#define CHECK(eval)                                               \
    if (!eval)                                                    \
    {                                                             \
        fprintf(stderr, "Exception:%s\n", mecab_strerror(mecab)); \
        mecab_destroy(mecab);                                     \
        return -1;                                                \
    }

int main(int argc, char **argv)
{
    char input[] = "今日もしないとね。";

    mecab_t *mecab = mecab_new(argc, argv);
    CHECK(mecab);

    // 取得結果
    const char *res1 = mecab_sparse_tostr(mecab, input);
    CHECK(res1)
    std::cout << "取得結果" << std::endl;
    std::cout << res1 << std::endl;

    // 取的前n個最好結果

    // const char *res2 = mecab_nbest_sparse_tostr2(mecab, 3, input,1);
    // CHECK(res2);
    // std::cout << "取的前n個最好結果" << std::endl;
    // std::cout << res2 << std::endl;

    // const mecab_node_t *node;
    // int i;
    // size_t len;
    // CHECK(mecab_nbest_init(mecab, input));
    // for (i = 0; i < 3; ++i)
    // {
    //     printf("%d:\n%s", i, mecab_nbest_next_tostr(mecab));
    // }

    std::cout << "取得node object" << std::endl;
    const mecab_node_t *node = mecab_sparse_tonode(mecab, input);
    CHECK(node);
    for (; node; node = node->next)
    {
        if (node->stat == MECAB_NOR_NODE || node->stat == MECAB_UNK_NODE)
        {
            // fwrite(node->surface, sizeof(char), node->length, stdout);
            //剩餘的字
            std::cout << node->surface << std::endl;
            // 解析字數
            std::cout << node->length << std::endl;
            // 當下解析字(剩餘字,當前解析字數) ，顯示字串的前N個
            std::cout.write(node->surface, node->length);
            //後面的解析
            std::cout << node->feature << std::endl;
        }
    }

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

    return 0;
}