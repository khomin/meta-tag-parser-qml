#ifndef HANDLEURL_H
#define HANDLEURL_H

#include <QObject>
#include "./file_download.h"
#include "og_parser.h"
#include "og_parser_result.h"

class HandleInput : public QObject
{
    Q_OBJECT
public:
    explicit HandleInput(QObject *parent = nullptr);

    // this need for fast decision
    // without creating a object
    // if line contents url or not
    static bool checkIsContainsHyperlink(QString line) {
        static QRegularExpression regex(web_pattern);
        QRegularExpressionMatch match = regex.match(line);
        return match.hasMatch();
    }

    // method must be called
    // then a text changes or after first time
    void parseInput(QString input);

    // get the final result
    OgParserRes::ParseResult getResult() {
        return m_result;
    }

signals:
    void signalParserDone(OgParserRes::ParseResult data);

private:

    // in then in the line url without https or http
    // for example name.com
    // QNetworkAccessManager can't download
    // so it's easier just to add https:// in the start of the line
    QString appendHttpsPrefixIfUrlShort(QString & url);

    // to prevent page reloading every time
    // downloaded pages are saved in the cache folder
    // so next request can be handled without real dowloading
    QString getUrlToHashFileName(QUrl url);

    // dowloading html, image and save to cache folder
    void downloadHtml(QUrl url);
    void downloadImage();
    bool loadHtmlLocal(QUrl url);

    // if url is invalided
    // clear all fields
    // which may contains any old data
    void clearAllFields();

    OgParserRes::ParseResult m_result;
    OgParser m_og_parser;
    FileDownloader* m_downloader;
    FileDownloader* m_downloader_image;

    // the regex for validate url in the input line
    // valided examples:
    //
    // https://www.example.com/blog/problem-with#commento?v=something
    // www.example.com
    // http://example.com
    // https://www.example.com
    // example.com/exam-1/exam.php
    // example.com/exam
    static constexpr const char* web_pattern = "^(?:https?:\\/\\/)?(?:www\\.)?[a-zA-Z0-9-#.=?&_/]+$";

    static constexpr const char* const http_prefix = "http://";
    static constexpr const char* const https_prefix = "https://";
};

#endif // HANDLEURL_H
