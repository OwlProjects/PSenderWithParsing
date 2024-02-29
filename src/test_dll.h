#ifndef TEST_DLL_H
#define TEST_DLL_H

#include <QMainWindow>
#include <QLibrary>

namespace Ui {
class test_DLL;
}

class test_DLL : public QMainWindow
{
    Q_OBJECT

public:
    explicit test_DLL(QWidget *parent = nullptr);
    ~test_DLL();

private slots:
    void on_pushButtonCallDLLWindow_clicked();

private:
    Ui::test_DLL *ui;
    QLibrary * libWindow;
};

#endif // TEST_DLL_H
