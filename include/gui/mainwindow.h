#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void onAmountChanged(const QString &text);
    void onFromCurrencyChanged(int index);
    void onToCurrencyChanged(int index);

    QString flagForCode(const std::string& code);

private:
    Ui::MainWindow *ui;
    void updateConversion();
};

#endif // MAINWINDOW_H
