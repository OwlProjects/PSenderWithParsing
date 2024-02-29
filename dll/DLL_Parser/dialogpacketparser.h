#ifndef DIALOGPACKETPARSER_H
#define DIALOGPACKETPARSER_H

#include "DLL_Parser_global.h"

#include <QDialog>
#include <QStandardItem>

#include "packetparsererror.h"

namespace Ui {
class DialogPacketParser;
}

class DialogPacketParser : public QDialog
{
    Q_OBJECT

/*
 * Public c-tors/d-tors
 */
public:
    explicit DialogPacketParser(QWidget *parent = nullptr, QByteArray packetArray = QByteArray());
    ~DialogPacketParser();

/*
 * Private slots
 */
private slots:
    void on_pushButtonOK_clicked();

/*
 * Private fields
 */
private:
    Ui::DialogPacketParser *ui;
    PacketParserError *error;

private:
    QStandardItemModel *GetPacketModel(QWidget *parent = nullptr, QByteArray packetArray = QByteArray());
};

extern "C" DLL_PARSER_EXPORT QDialog *GetPacketParserWindow(QWidget *parent = nullptr, QByteArray packetArray = QByteArray());


#endif // DIALOGPACKETPARSER_H
