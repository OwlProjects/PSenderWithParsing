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

/*
 * Public methods
 */
public:
    explicit DialogLogParser(QWidget *parent = nullptr);
    DialogLogParser(QWidget *parent, QString name, Packet * packet);
    DialogLogParser(QWidget *parent, QString name, QStandardItemModel * model, QString messString);
    ~DialogLogParser();

};

#endif // DIALOGLOGPARSER_H
