#include "test_qjson.h"
#include "ui_test_qjson.h"

#include <QStandardItem>

test_QJSON::test_QJSON(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test_QJSON)
{
    ui->setupUi(this);

    QStandardItemModel * model = new QStandardItemModel(this);
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

    ui->tableViewData->setModel(model);

}

test_QJSON::~test_QJSON()
{
    delete ui;
}
