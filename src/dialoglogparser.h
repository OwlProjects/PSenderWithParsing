#ifndef DIALOGLOGPARSER_H
#define DIALOGLOGPARSER_H

#include <QDialog>
#include <QStandardItem>
#include "packet.h"

namespace Ui {
class DialogLogParser;
}

class DialogLogParser : public QDialog
{
    Q_OBJECT

/*
 * private fields
 */
private:
    Ui::DialogLogParser *ui;

    int const hex_char_count = 2;

/*
 * Private methods
 */
private:

    QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, QString value ) const;

    QStandardItem * CreateFieldView( QStandardItemModel * model, QString name, uint32_t value, int bytesCount ) const;

    QStandardItem * CreateFieldView( QStandardItem * item, QString name, QString value ) const;

    QStandardItem * CreateFieldView( QStandardItem * item, QString name, uint32_t value, int bytesCount ) const;

    QStandardItem * CreateCommandHeaderView( QStandardItem * item, uint8_t id, uint32_t length, uint8_t timeHi, uint32_t timeLo ) const;

//    brValue.sprintf("ID: 0x%02X (Receive Confirmation)", ID_Command);
//    QStandardItem * rF_RC = new QStandardItem(brValue);
//    responseFrames->appendRow(rF_RC);

    //void CreateCommandIDNodeView( QStandardItem * item, QString name, uint32_t value, int bytesCount ) const;


/*
 * Public methods
 */
public:
    explicit DialogLogParser(QWidget *parent = nullptr);
    DialogLogParser(QWidget *parent, QString name, Packet * packet);
    ~DialogLogParser();






};

#endif // DIALOGLOGPARSER_H
