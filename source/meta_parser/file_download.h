#ifndef FILE_DOWNLOAD_H
#define FILE_DOWNLOAD_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
  explicit FileDownloader(QUrl url, QObject *parent = 0);
  virtual ~FileDownloader();
  QByteArray downloadedData() const;

signals:
  void downloaded();

private slots:
  void fileDownloaded(QNetworkReply* pReply);

private:
  QNetworkAccessManager m_WebCtrl;
  QByteArray m_DownloadedData;
};

#endif // FILE_DOWNLOAD_H
