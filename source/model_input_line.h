#ifndef MODEL_INPUT_LINE_H
#define MODEL_INPUT_LINE_H

#include <QObject>
#include "meta_parser/handle_input.h"

class ModelInputLine : public QObject
{
    Q_OBJECT
public:
    explicit ModelInputLine(QObject *parent = nullptr);

    //
    // the input line
    //
    Q_PROPERTY(QString inputText READ getInputText WRITE setInputText NOTIFY signalInputTextChanged)
    //
    // meta preview (above input field)
    //
    Q_PROPERTY(QString metaUrlName READ getUrlName NOTIFY signalMetaPreviewChanged)
    Q_PROPERTY(QString metaUrlTitle READ getUrlTitle NOTIFY signalMetaPreviewChanged)
    Q_PROPERTY(QString metaUrlDesc READ getUrlDesc NOTIFY signalMetaPreviewChanged)
    Q_PROPERTY(QString metaUrlImage READ getUrlImage NOTIFY signalMetaPreviewChanged)

    QString getUrlName() { return m_input_handle.getResult().og_site_name; }
    QString getUrlTitle() { return m_input_handle.getResult().og_title; }
    QString getUrlDesc() { return m_input_handle.getResult().og_description; }
    QString getUrlImage() { return m_input_handle.getResult().og_image; }

    QString getInputText() {
        return m_input_text;
    }

    void setInputText(QString value) {
        m_input_text = value;
        emit signalInputTextChanged();
        m_input_handle.parseInput(value);
    }

signals:
    void signalInputTextChanged();

    //
    // meta previews
    //
    void signalMetaPreviewChanged();
    void signalMetaPreviewImageChanged();

private:

    QString m_input_text;
    HandleInput m_input_handle;
};

#endif // MODEL_INPUT_LINE_H
