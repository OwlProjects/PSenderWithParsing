#ifndef TEST_QJSON_H
#define TEST_QJSON_H

#include <QWidget>

namespace Ui {
class test_QJSON;
}

class test_QJSON : public QWidget
{
    Q_OBJECT

public:
    explicit test_QJSON(QWidget *parent = nullptr);
    ~test_QJSON();

private:
    Ui::test_QJSON *ui;
};

#endif // TEST_QJSON_H
