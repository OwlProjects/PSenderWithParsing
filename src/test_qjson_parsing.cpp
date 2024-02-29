
#include "test_qjson_parsing.h"
#include "ui_test_qjson_parsing.h"

#include <QStandardItem>
#include <QJsonDocument>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject>
#include <QDir>
#include <QFileDialog>



test_QJSON_Parsing::test_QJSON_Parsing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test_QJSON_Parsing)
{
    ui->setupUi(this);

    //QJsonDocument * pjsDoc;

    QString jsFilePath = ui->lineEditPathFileJSON->text();
    if ( QFileInfo::exists( jsFilePath ) ) {
        QFile jsFile( jsFilePath );
        jsFile.open( QIODevice::ReadOnly | QIODevice::Text );
        QByteArray jsArray = jsFile.readAll();
        jsFile.close();
        QJsonParseError jsError;
        //pjsDoc = new QJsonDocument( QJsonDocument::fromJson( jsArray, &jsError ) );
        QJsonDocument jsDoc( QJsonDocument::fromJson( jsArray, &jsError ) );
        if ( jsError.error != QJsonParseError::NoError ) {
            QString stringError;
            stringError.sprintf( "jsFile with error: %d", jsError.error );
            ui->lineEditResult->setText( stringError + " (" + jsError.errorString() + ")" );
        } else {
            QStandardItemModel * model = new QStandardItemModel( this );

            QJsonObject object = jsDoc.object();
            QStringList jsKeys = object.keys();
            for ( QString jsKey : jsKeys ) {
                QStandardItem * subItem = new QStandardItem( jsKey );
                model->appendRow(subItem);
                QJsonValue jsValue = object.value( jsKey );
                if ( jsValue.isObject() ) {
                    QJsonObject subObject = jsValue.toObject();
                    QStringList jsSubKeys = subObject.keys();
                    for ( QString jsSubKey : jsSubKeys ) {
                        if ( subObject.value(jsSubKey).isObject() )
                            subItem->appendRow( new QStandardItem( jsSubKey ) );
                    }
                }
            }

            ui->treeViewData->setModel(model);
            ui->lineEditResult->setText( "t: " + jsDoc[jsKeys[1]]["popup"]["menuitem"][1]["onclick"].toString() );

            /*
            if ( jsDoc["menu"]["popup"]["menuitem"].isArray() ) {
                ui->lineEditResult->setText( "a: " + jsDoc["menu"]["popup"]["menuitem"][1]["value"].toString() );
            } else
            {
                ui->lineEditResult->setText( "t: " + jsDoc["menu"]["id"].toString() );
            }
            */
        }

    } else {
        ui->lineEditResult->setText( "No jsFile" );
    }


    /*
    QStandardItemModel * model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Var"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Value"));

    //
    QList<QStandardItem *> brRow;
    //
    brRow.append(new QStandardItem("var0"));
    brRow.append(new QStandardItem("100"));
    model->appendRow(brRow);
    brRow.clear();
    //
    QStandardItem * root0 = new QStandardItem("var1");
    brRow.append(root0);
    brRow.append(new QStandardItem("500"));
    model->appendRow(brRow);
    brRow.clear();
    //
    brRow.append(new QStandardItem("var1_0"));
    brRow.append(new QStandardItem("200"));
    root0->appendRow(brRow);
    brRow.clear();
    //
    brRow.append(new QStandardItem("var1_1"));
    brRow.append(new QStandardItem("400"));
    root0->appendRow(brRow);
    brRow.clear();

    ui->treeViewData->setModel(model);
    */

}

test_QJSON_Parsing::~test_QJSON_Parsing()
{
    delete ui;
}

void test_QJSON_Parsing::pushButtonGetPathFileJSON_onClick( void ) {
    //QFileDialog * pwDialog = new QFileDialog(this, "Open JSON", QString(), "JSON (*.json)");



}



void test_QJSON_Parsing::on_pushButtonGetPathFileJSON_clicked()
{
    QString path = QFileDialog::getOpenFileName( this, "Open Parser DLL", QDir::currentPath(), "library (*.DLL, *.dll)" );
    if ( !path.isEmpty() ) {
        ui->lineEditPathFileJSON->setText( path );
    }
}
