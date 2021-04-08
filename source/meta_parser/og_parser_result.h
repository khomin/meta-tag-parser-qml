#ifndef OG_PARSER_RES_H
#define OG_PARSER_RES_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextDocument>
#include <QRegExp>
#include <QRegularExpression>
#include "../const_values.h"

class OgParserRes : public QObject
{
    Q_OBJECT
public:
    typedef struct {
        QString og_site_name;
        QString og_title;
        QString og_description;
        QString og_url;
        QString og_image;
        QString og_image_file_name;
        QString og_image_local_path;
        QString og_http_local_path;
    }ParseResult;
};

#endif // OG_PARSER_RES_H
