#ifndef TEST_QJSON_PARSING_H
#define TEST_QJSON_PARSING_H

#include <QMainWindow>

namespace Ui {
class test_QJSON_Parsing;
}

class test_QJSON_Parsing : public QMainWindow
{
    Q_OBJECT

/*
 * Private slots
 */
private slots:
    void pushButtonGetPathFileJSON_onClick( void );

/*
 * public methods
 */
public:
    explicit test_QJSON_Parsing(QWidget *parent = nullptr);
    ~test_QJSON_Parsing();
    QJsonObject toJson() const;
/*
 * private fields
 */
private:
    Ui::test_QJSON_Parsing *ui;
};

/*
 * public fields
 */

#endif // TEST_QJSON_PARSING_H
