#include "test_contextmenu.h"
#include "ui_test_contextmenu.h"

#include <QtWidgets>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QString>


test_contextmenu::test_contextmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::test_contextmenu)
{
    ui->setupUi(this);

    actionCut = new QAction(tr("Cu&t"), this);
    connect(actionCut, &QAction::triggered, this, &test_contextmenu::cut);
    actionCopy = new QAction(tr("&Copy"), this);
    connect(actionCopy, &QAction::triggered, this, &test_contextmenu::copy);
    actionPaste = new QAction(tr("&Paste"), this);
    connect(actionPaste, &QAction::triggered, this, &test_contextmenu::paste);


    QStandardItemModel * model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("Var"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Value"));

    QList<QStandardItem *> brRow;
    brRow.append(new QStandardItem("var0"));
    brRow.append(new QStandardItem("100"));
    model->appendRow(brRow);
    brRow.clear();
    brRow.append(new QStandardItem("var1"));
    brRow.append(new QStandardItem("500"));
    model->appendRow(brRow);
    brRow.clear();

    ui->tableViewPackets->setModel(model);
    ui->tableViewPackets->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableViewPackets, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));
}

test_contextmenu::~test_contextmenu()
{
    delete ui;
}

void test_contextmenu::cut()
{
    QCheckBox * chB = ui->checkBoxCut;
    bool curState = chB->checkState();
    chB->setChecked(!curState);
}

void test_contextmenu::copy()
{
    //infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
    QCheckBox * chB = ui->checkBoxCopy;
    bool curState = chB->checkState();
    chB->setChecked(!curState);
}

void test_contextmenu::paste()
{
    //infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
    QCheckBox * chB = ui->checkBoxPaste;
    bool curState = chB->checkState();
    chB->setChecked(!curState);
}

void test_contextmenu::GetResult( QPoint pos )
{
    QModelIndex modelIdx = ui->tableViewPackets->indexAt( pos );
    int idxColumn = modelIdx.column();
    int idxRow = modelIdx.row();
    QStandardItemModel * model = static_cast<QStandardItemModel *>( ui->tableViewPackets->model() );
    QStandardItem * item = model->item( idxRow, idxColumn );

    QString result;
    if ( item != nullptr ) {
        result.sprintf( "item[row: %d; col: %d] = ", idxRow, idxColumn );
        result += item->text();
        ui->lineEditResult->setText( result );
    } else {
        result.sprintf( "row: %d; col: %d", idxRow, idxColumn );
        ui->lineEditResult->setText( "Out of cells' area: " + result );
    }
}


void test_contextmenu::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(actionCut);
    menu.addAction(actionCopy);
    menu.addAction(actionPaste);
    menu.exec(event->globalPos());
}


void test_contextmenu::customMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu( this );
    QAction * actionGetResult = new QAction( tr("Get result"), this );
    connect( actionGetResult, &QAction::triggered, this, [=]{ test_contextmenu::GetResult(pos); } );
    //menu->addAction(new QAction("Action 1", this));
    menu->addAction( actionGetResult );
    menu->addAction( new QAction( "Action 2", this ) );
    menu->addAction( new QAction( "Action 3", this ) );
    menu->popup( ui->tableViewPackets->viewport()->mapToGlobal(pos) );
}
