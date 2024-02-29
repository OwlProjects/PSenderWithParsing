#include "test_dll.h"
#include "ui_test_dll.h"
#include "dllclass.h"
#include <QStandardItem>
#include <QMessageBox>
#include <QDebug>

typedef int (*pMath_t)(int, int);


test_DLL::test_DLL(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test_DLL)
{
    ui->setupUi(this);

    libWindow = nullptr;

    QStandardItemModel * model = new QStandardItemModel();
    ui->treeViewDLLResults->setModel(model);
    model->setHorizontalHeaderItem( 0, new QStandardItem( "DLL Load results" ) );

    DllClass cDLL;
    QStandardItem * root;
    root = new QStandardItem( "Statically added DLL" );
    model->appendRow( root );
    root->appendRow( new QStandardItem( QString::number( cDLL.Add( 7, 2 ) ) ) );
    root->appendRow( new QStandardItem( QString::number( cDLL.Sub( 7, 2 ) ) ) );

    QLibrary lib("dllSimple.dll");
    if ( lib.load() ) {
        root = new QStandardItem( "Dynamically added DLL" );
        model->appendRow( root );
        pMath_t pMul = reinterpret_cast<pMath_t>( lib.resolve( "Mul" ) );
        if ( pMul ) {
            root->appendRow( new QStandardItem( QString::number( pMul( 10, 5 ) ) ) );
            root->appendRow( new QStandardItem( QString::number( pMul( 12, 4 ) ) ) );
            root->appendRow( new QStandardItem( QString::number( pMul( 13, 3 ) ) ) );
            lib.unload();
        } else {
            root->appendRow( new QStandardItem( "DLL function Mul not load" ) );
        }        
        pMath_t pDiv = reinterpret_cast<pMath_t>( lib.resolve( "Div" ) );
        if ( pDiv ) {
            root->appendRow( new QStandardItem( QString::number( pDiv( 10, 5 ) ) ) );
            root->appendRow( new QStandardItem( QString::number( pDiv( 12, 4 ) ) ) );
            root->appendRow( new QStandardItem( QString::number( pDiv( 13, 3 ) ) ) );
            lib.unload();
        } else {
            root->appendRow( new QStandardItem( "DLL function Div not load" ) );
            lib.unload();
        }
    } else {
        model->appendRow( new QStandardItem( "DLL not load" ) );
    }
}

test_DLL::~test_DLL()
{
    delete ui;
}

void test_DLL::on_pushButtonCallDLLWindow_clicked()
{
    QLibrary lib("DLL_6C213.dll");
    //libWindow = new QLibrary("DLL_6C213.dll");

    /*
    if ( lib.isLibrary("DLL_6C213.dll") ) {
        QMessageBox::information(this, "DLL info", "library is good");
         if ( lib.load() ) {
             QMessageBox::information(this, "DLL info", "library is loaded");
         } else {
             QMessageBox::critical(this, "DLL error", "library isn't loaded");
         }
    } else {
        QMessageBox::critical(this, "DLL error", "not library");
    }
    */

    /*
    if ( lib.load() ) {
        QWidget *(* pGetWnd)(QWidget *) = reinterpret_cast<QWidget *(*)(QWidget *)>( lib.resolve( "GetPacketParserDialog" ) );
        if ( pGetWnd ) {
            QWidget * pWnd = pGetWnd(this);
            if ( pWnd ) {
                pWnd->show();
            } else {
                QMessageBox::critical(this, "DLL error", "Window isn't loaded");
            }
        } else {
            QMessageBox::critical(this, "DLL error", "GetPacketParserForm isn't found");
        }
        lib.unload();
    } else {
        QString errorString = "DLL_6C213.dll isn't loaded \n\r";
        errorString += lib.errorString();
        QMessageBox::critical(this, "DLL error", errorString);
    }
    */


    if ( lib.load() ) {
        QMainWindow *(* pGetWnd)(QWidget *) =
            reinterpret_cast<QMainWindow *(*)(QWidget *)>( lib.resolve( "GetPacketParserWindow" ) );
        if ( pGetWnd ) {
            QMainWindow * pWnd = pGetWnd(this);
            if ( pWnd ) {
                pWnd->show();
            } else {
                QMessageBox::critical(this, "DLL error", "Window isn't loaded");
            }
        } else {
            QMessageBox::critical(this, "DLL error", "GetPacketParserForm isn't found");
        }
    } else {
        QString errorString = "DLL_6C213.dll isn't loaded \n\r";
        errorString += lib.errorString();
        QMessageBox::critical(this, "DLL error", errorString);
    }

    /*
    QMainWindow *widget = new QMainWindow(  );
    widget->show();
    */

}
