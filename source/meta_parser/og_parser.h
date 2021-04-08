#ifndef OG_PARSER_H
#define OG_PARSER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextDocument>
#include <QRegExp>
#include <QRegularExpression>
#include "../const_values.h"
#include "./og_parser_result.h"

class OgParser : public QObject
{
    Q_OBJECT
public:
    explicit OgParser(QObject *parent = nullptr);

    //
    // main tags
    //
    constexpr static const char* og_site_name = "<meta [^>]*property=[\"']og:site_name[\"'] [^>]*content=[\"']([^'^\"]+?)[\"'][^>]*>";
    constexpr static const char* og_title = "<meta [^>]*property=[\"']og:title[\"'] [^>]*content=[\"']([^'^\"]+?)[\"'][^>]*>";
    constexpr static const char* og_description = "<meta [^>]*property=[\"']og:description[\"'] [^>]*content=[\"']([^'^\"]+?)[\"'][^>]*>";
    constexpr static const char* og_url= "<meta [^>]*property=[\"']og:url[\"'] [^>]*content=[\"']([^'^\"]+?)[\"'][^>]*>";
    constexpr static const char* og_image= "<meta [^>]*property=[\"']og:image[\"'] [^>]*content=[\"']([^'^\"]+?)[\"'][^>]*>";

    //
    // second variants
    //
    constexpr static const char* og_description_simple = "<meta [^>]*name=[\"']description[\"'] [^>]*content=[\"']([^'^\"]+?)[\"'][^>]*>";
    constexpr static const char* og_title_simple = "<title>([\\w]{1,65})<\\/title>";
    constexpr static const char* og_title_alternative = "<meta [^>]*name=\"title\"([^'^\"]+?)[\"']([^>]*)>";
    constexpr static const char* og_first_png = "href=\"([^\"]*.png)\">";

    OgParserRes::ParseResult parseHtml(QString html, QUrl originalUrl);
};

#endif // OG_PARSER_H
