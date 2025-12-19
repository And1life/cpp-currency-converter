#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "core/ExchangeRate.hpp"
#include "api/ExchangeApi.hpp"
#include "utils/ConfigManager.hpp"
#include <QMessageBox>
#include <QDoubleValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fromCurrencyComboBox->setIconSize(QSize(24, 16));
    ui->toCurrencyComboBox->setIconSize(QSize(24, 16));

    auto *validator = new QDoubleValidator(0.0, 100000000000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->amountLineEdit->setValidator(validator);


    try {
        ConfigManager configManager("config.json");
        ExchangeRate exchangeRate(configManager);



        for (const auto& currency : configManager.getCurrencies()) {
            const QString code = QString::fromStdString(currency.code);
            const QIcon icon{flagForCode(currency.code)};
            ui->fromCurrencyComboBox->addItem(icon, code);
            ui->toCurrencyComboBox->addItem(icon, code);
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

QString MainWindow::formatNumber(double value)
{
    QLocale locale(QLocale::German);
    return locale.toString(value, 'f', 2);
}

void MainWindow::updateConversion()
{
    QString fromCurrency = ui->fromCurrencyComboBox->currentText();
    QString toCurrency = ui->toCurrencyComboBox->currentText();
    QString amountText = ui->amountLineEdit->text();
    double amount = amountText.replace(" ", "").toDouble();


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

        ui->resultLabel->setText(formatNumber(amount) + " " + fromCurrency + " = " +
    formatNumber(result) + " " + toCurrency);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Conversion failed: ") + e.what());
    }
}


QString MainWindow::flagForCode(const std::string& code)
{
    QString c = QString::fromStdString(code).toUpper();

    if (c == "EUR") return ":/flags/EUR.png";
    if (c == "USD") return ":/flags/USD.png";
    if (c == "RUB") return ":/flags/RUB.png";
    if (c == "SGD") return ":/flags/SGD.png";
    if (c == "SEK") return ":/flags/SEK.png";
    if (c == "NZD") return ":/flags/NZD.png";
    if (c == "KRW") return ":/flags/KRW.png";
    if (c == "JPY") return ":/flags/JPY.png";
    if (c == "INR") return ":/flags/INR.png";
    if (c == "GBR") return ":/flags/GBR.png";
    if (c == "CNY") return ":/flags/CNY.png";
    if (c == "CHF") return ":/flags/CHF.png";
    if (c == "CAD") return ":/flags/CAD.png";
    if (c == "BRL") return ":/flags/BRL.png";
    if (c == "AUD") return ":/flags/AUD.png";

    return ":/flags/USD.png";
}

MainWindow::~MainWindow()
{
    delete ui;
}
