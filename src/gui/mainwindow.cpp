#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "core/ExchangeRate.hpp"
#include "api/ExchangeApi.hpp"
#include "utils/ConfigManager.hpp"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    try {
        ConfigManager configManager("config.json");
        ExchangeRate exchangeRate(configManager);



        for (const auto& currency : configManager.getCurrencies()) {
            ui->fromCurrencyComboBox->addItem(QString::fromStdString(currency.code));
            ui->toCurrencyComboBox->addItem(QString::fromStdString(currency.code));
        }

        connect(ui->amountLineEdit, &QLineEdit::textChanged, this, &MainWindow::onAmountChanged);
        connect(ui->fromCurrencyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &MainWindow::onToCurrencyChanged);
        connect(ui->toCurrencyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &MainWindow::onToCurrencyChanged);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to initialize: ") + e.what());
    }
}

void MainWindow::onAmountChanged(const QString &text)
{
    Q_UNUSED(text);
    updateConversion();
}

void MainWindow::onToCurrencyChanged(int index)
{
    Q_UNUSED(index);
    updateConversion();
}

void MainWindow::onFromCurrencyChanged(int index)
{
    Q_UNUSED(index);
    updateConversion();
}

void MainWindow::updateConversion()
{
    QString fromCurrency = ui->fromCurrencyComboBox->currentText();
    QString toCurrency = ui->toCurrencyComboBox->currentText();
    double amount = ui->amountLineEdit->text().toDouble();

    if(amount <= 0)
    {
        ui->resultLabel->setText("0 " + fromCurrency + " = 0 " + toCurrency);
        return;
    }

    try {
        ConfigManager configManager("config.json");
        ExchangeRate exchangeRate(configManager);


        double result = exchangeRate.convert(fromCurrency.toStdString(),
    toCurrency.toStdString(), amount);

        ui->resultLabel->setText(QString::number(amount, 'f', 2) + " " + fromCurrency + " = " +
    QString::number(result, 'f', 2) + " " + toCurrency);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Conversion failed: ") + e.what());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
