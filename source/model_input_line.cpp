#include "./model_input_line.h"
#include "./meta_parser/og_parser.h"
#include "./meta_parser/og_parser_result.h"

ModelInputLine::ModelInputLine(QObject *parent) : QObject(parent)
{
    connect(&m_input_handle, &HandleInput::signalParserDone, this,
            [&](OgParserRes::ParseResult data) {
        emit signalMetaPreviewChanged();

        if(m_input_handle.getResult().og_image != data.og_image) {
            emit signalMetaPreviewImageChanged();
        }
    });
}
