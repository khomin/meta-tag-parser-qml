#include "handle_input.h"
#include <QImage>
#include <QBuffer>
#include "../const_values.h"

HandleInput::HandleInput(QObject *parent) : QObject(parent) {}

void HandleInput::parseInput(QString input) {
    //
    // checking that the path contains url
    //
    if(checkIsContainsHyperlink(input)) {
        // in then in the line url without https or http
        // for example name.com
        // QNetworkAccessManager can't download
        // so it's easier just to add https:// in the start of the line
        input = appendHttpsPrefixIfUrlShort(input);

        QUrl url(input);

        // create meta foldler before
        ConstValues::createFolderMeta();

        // if file already exists
        if(loadHtmlLocal(url)) {
            // and image exists too
            if(QFile(m_result.og_image_local_path).exists()) {
                // then there is nothing to do
                emit signalParserDone(m_result);
            } else {
                // if image not exists
                downloadImage();
            }
        } else {
            // else start downloading
            downloadHtml(url);
        }
    } else {
        clearAllFields();
        emit signalParserDone(m_result);
    }
}

void HandleInput::downloadHtml(QUrl url) {
    m_downloader = new FileDownloader(url, this);
    connect(m_downloader, &FileDownloader::downloaded, [&, url]() {
        QByteArray array = m_downloader->downloadedData();
        if(!array.isEmpty()) {
            QString htmlFilePath = ConstValues::getFolderMeta() + getUrlToHashFileName(url);
            QFile htmlFile(htmlFilePath);
            if(htmlFile.open(QIODevice::WriteOnly)) {
                htmlFile.write(array);
                m_result.og_http_local_path = htmlFilePath;
            }
            auto res = m_og_parser.parseHtml(array.data(), url);
            m_result.og_url = res.og_url;
            m_result.og_title = res.og_title;
            m_result.og_site_name = res.og_site_name;
            m_result.og_image = res.og_image;
            m_result.og_image_local_path = res.og_image_local_path;

            downloadImage();
        } else {
            qDebug() << "downloadHtml start but reply nothing: "<< m_result.og_image;
            emit signalParserDone(m_result);
        }
    });
}

void HandleInput::downloadImage() {
    QUrl url = QUrl(m_result.og_image);

    QString imagePathName = m_result.og_image_local_path;
    if(!imagePathName.isEmpty()) {
        if(QFile(imagePathName).exists()) {
            m_result.og_image_local_path = imagePathName;
            emit signalParserDone(m_result);
        } else {
            m_downloader_image = new FileDownloader(url, this);
            connect(m_downloader_image, &FileDownloader::downloaded, [&, imagePathName]() {
                QByteArray array = m_downloader_image->downloadedData();
                if(!array.isEmpty()) {
                    QFile imageFile(imagePathName);
                    if(imageFile.open(QIODevice::WriteOnly)) {
                        imageFile.write(array);
                        m_result.og_image_local_path = imagePathName;
                    }
                } else {
                    qDebug() << "downloadImage start but loading reply nothing: "<< m_result.og_image;
                }
                emit signalParserDone(m_result);
            });
        }
    } else {
        emit signalParserDone(m_result);
    }
}

bool HandleInput::loadHtmlLocal(QUrl url) {
    QString htmlFilePath = ConstValues::getFolderMeta() + getUrlToHashFileName(url);
    QFile htmlFile(htmlFilePath);
    if(htmlFile.exists()) {
        QByteArray array;
        if(htmlFile.open(QIODevice::ReadOnly)) {
            array = htmlFile.readAll();
        }
        if(!array.isEmpty()) {
            auto res = m_og_parser.parseHtml(array.data(), url);
            m_result.og_url = res.og_url;
            m_result.og_title = res.og_title;
            m_result.og_site_name = res.og_site_name;
            m_result.og_image = res.og_image;
            m_result.og_image_file_name = res.og_image_file_name;
            m_result.og_image_local_path = res.og_image_local_path;
            return true;
        }
    }
    return false;
}

QString HandleInput::appendHttpsPrefixIfUrlShort(QString & url) {
    if(!url.contains(http_prefix) && !url.contains(https_prefix)) {
        url.push_front(https_prefix);
    }
    return url;
}

QString HandleInput::getUrlToHashFileName(QUrl url) {
    auto http = url.toString();
    http.remove(https_prefix);
    http.remove(http_prefix);
    http.replace("/", "_");
    http.replace("\\", "_");
    http.replace(".", "_");
    return http;
}

void HandleInput::clearAllFields() {
    m_result.og_site_name = "";
    m_result.og_title = "";
    m_result.og_description = "";
    m_result.og_image = "";
}
