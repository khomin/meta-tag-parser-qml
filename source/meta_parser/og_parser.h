#ifndef OG_PARSER_H
#define OG_PARSER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextDocument>
#include <QRegExp>
#include <QRegularExpression>
#include "../const_values.h"

class OgParser : public QObject
{
    Q_OBJECT
public:
    explicit OgParser(QObject *parent = nullptr);

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

    ParseResult parseHtml(QString html, QUrl originalUrl) {
        ParseResult res;
        QRegularExpression site_name_regex(og_site_name);
        QRegularExpression title_regex(og_title);
        QRegularExpression description_regex(og_description);
        QRegularExpression url_regex(og_url);
        QRegularExpression image_regex(og_image);
        QRegularExpressionMatch match;

        //
        // first attempts
        // find otg tags
        //
        match = site_name_regex.match(html);
        if (match.hasMatch()) {
            res.og_site_name = match.captured(1);
        }
        match = title_regex.match(html);
        if (match.hasMatch()) {
            res.og_title = match.captured(1);
        }
        match = description_regex.match(html);
        if (match.hasMatch()) {
            res.og_description = match.captured(1);
        }
        match = url_regex.match(html);
        if (match.hasMatch()) {
            res.og_url = match.captured(1);
        }
        match = image_regex.match(html);
        if (match.hasMatch()) {
            res.og_image = match.captured(1);
        }

        //
        // second attempts
        //
        QRegularExpression regex_second;
        if(res.og_title.isEmpty()) {
            regex_second.setPattern(og_description_simple);
            match = regex_second.match(html);
            if (match.hasMatch()) {
                res.og_title = match.captured(1);
            }
        }
        if(res.og_image.isEmpty()) {
            regex_second.setPattern(og_first_png);
            match = regex_second.match(html);
            if (match.hasMatch()) {
                res.og_image = originalUrl.toString() + match.captured(1);
            }
        }
        if(res.og_site_name.isEmpty()) {
            regex_second.setPattern(og_title_simple);
            match = regex_second.match(html);
            if (match.hasMatch()) {
                res.og_site_name = match.captured(1);
            } else {
                if(!res.og_title.isEmpty()) {
                    res.og_site_name = res.og_title;
                } else {
                    res.og_site_name = originalUrl.toString();
                }
            }
        }

        if(!res.og_image.isEmpty()) {
            QUrl info(res.og_image);
            res.og_image_file_name = info.fileName();
        }

        if(res.og_url.isEmpty()) {
            res.og_url = originalUrl.toString();
        }

        res.og_http_local_path = originalUrl.fileName();

        if(!res.og_image_file_name.isEmpty()) {
            res.og_image_local_path = ConstValues::getFolderMeta() + res.og_image_file_name;
        }

        return res;
    }

private:
};

#endif // OG_PARSER_H
