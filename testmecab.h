#include "mecab/mecab.h"
#include <QString>
#include <QStringList>
#include <iostream>

#define CHECK(eval)                                               \
    if (!eval)                                                    \
    {                                                             \
        fprintf(stderr, "Exception:%s\n", mecab_strerror(mecab)); \
        mecab_destroy(mecab);                                     \
        return false;                                             \
    }
// common.h 有提供
inline QString S(const std::string &s) { return QString::fromStdString(s); }
inline QString S(const std::wstring &s) { return QString::fromStdWString(s); }

class useMecab
{
public:
    useMecab(std::wstring &sentence)
    {
        char *argv = "";
        mecab = mecab_new(0, &argv);
        convertStr(sentence);
        outputHtml(sentence);
    };
    ~useMecab()
    {
        mecab_destroy(mecab);
    };
    char *char_sentence;
    const mecab_node_t *node_sentence;

private:
    mecab_t *mecab;
    void convertStr(std::wstring &sentence)
    {
        QString input_qs(S(sentence));
        QByteArray input_qr = input_qs.toLocal8Bit();
        char_sentence = input_qr.data();
        getMecabNode();
    };
    void getMecabNode()
    {
        node_sentence = mecab_sparse_tonode(mecab, char_sentence);
    };
    void outputHtml(std::wstring &sentence)
    {

        QString style = "<style>td{padding:0 1px;}</style>";
        QString tr1 = "";
        QString tr2 = "";
        
        for (; node_sentence; node_sentence = node_sentence->next)
        {
            if (node_sentence->stat == MECAB_NOR_NODE || node_sentence->stat == MECAB_UNK_NODE)
            {
                // 當下解析字
                QString current_str(node_sentence->surface);
                current_str.truncate(node_sentence->length);
                QString pronounce(node_sentence->feature);
                QStringList pronounce_list = pronounce.split(QString(","));

                tr1 += "<td align=\"center\" style=\"font-size:12px;\">" + pronounce_list.takeLast() + "</td>";
                tr2 += "<td align=\"center\">" + current_str + "</td>";
            }
        }
        tr1 = "<tr align=\"center\">" + tr1 + "</tr>";
        tr2 = "<tr align=\"center\">" + tr2 + "</tr>";
        sentence = (style + "<table>" + tr1 + tr2 + "</table>").toStdWString();
    }
};
