#ifndef TEST_CONTEXTMENU_H
#define TEST_CONTEXTMENU_H

#include <QDialog>

namespace Ui {
class test_contextmenu;
}

class test_contextmenu : public QDialog
{
    Q_OBJECT


protected:
    void contextMenuEvent(QContextMenuEvent *event) override;


private slots:
    void cut();
    void copy();
    void paste();
    void GetResult(QPoint pos);

private:
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;

private:
    Ui::test_contextmenu *ui;

public:
    explicit test_contextmenu(QWidget *parent = nullptr);
    ~test_contextmenu() override;

public slots:
    void customMenuRequested(QPoint pos);


};

#endif // TEST_CONTEXTMENU_H
