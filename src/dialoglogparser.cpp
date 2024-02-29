
#include "dialoglogparser.h"
#include "ui_dialoglogparser.h"

#include <QLibrary>

DialogLogParser::DialogLogParser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogParser)
{
    ui->setupUi(this);
}

DialogLogParser::DialogLogParser( QWidget *parent, QString name, Packet * packet ) : DialogLogParser( parent )
{
    this->setWindowTitle(name);
    QString messBytesView = packet->hexString;
    ui->lineEditPacketHex->setText( messBytesView );
    ui->lineEditPacketHex->setCursorPosition(0);
    QStandardItemModel * const model = new QStandardItemModel();
    QList<QStandardItem *> brRow;
    brRow.append( new QStandardItem( "Packet" ) );
    brRow.append( new QStandardItem( messBytesView ) );
    model->appendRow( brRow );

    ui->treeViewPacketFields->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->treeViewPacketFields->setModel( model );
    ui->treeViewPacketFields->expandAll();
    for (int column = 0; column < model->columnCount(); ++column)
        ui->treeViewPacketFields->resizeColumnToContents(column);
}

DialogLogParser::DialogLogParser(QWidget *parent, QString name, QStandardItemModel *model, QString messString) : DialogLogParser(parent)
{
    this->setWindowTitle( name );
    QString messBytesView = QString();
    ui->lineEditPacketHex->setText( messString );
    ui->lineEditPacketHex->setCursorPosition( 0 );
    ui->treeViewPacketFields->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->treeViewPacketFields->setModel( model );
    ui->treeViewPacketFields->expandAll();
    for ( int column = 0; column < model->columnCount(); ++column )
        ui->treeViewPacketFields->resizeColumnToContents( column );
}

DialogLogParser::~DialogLogParser()
{
    delete ui;
}
