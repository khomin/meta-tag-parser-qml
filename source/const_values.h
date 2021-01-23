#ifndef CONSTVALUES_H
#define CONSTVALUES_H

#include <QObject>
#include <QDir>

class ConstValues : public QObject
{
    Q_OBJECT
public:
    explicit ConstValues(QObject *parent = nullptr);

    static QString getFolderMeta() {
        return (QDir::homePath() + "/meta/");
    }

    static void createFolderMeta() {
        QDir dir;
        // Initialize to the desired dir if 'path' is relative
        // By default the program's working directory "." is used.
        // We create the directory if needed
        if (!dir.exists(getFolderMeta()))
            dir.mkpath(getFolderMeta()); // You can check the success if needed
    }
};

#endif // CONSTVALUES_H
