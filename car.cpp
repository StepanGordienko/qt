#include "car.h"
#include "ui_car.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDate>
#include <QStringConverter>

Car::Car(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Car)
{
    ui->setupUi(this);
    connectSignals();
    resetForm();
}

Car::~Car()
{
    delete ui;
}

void Car::connectSignals()
{
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &Car::handleResetClicked);
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &Car::handleSaveClicked);
}

void Car::resetForm()
{
    ui->lineEditBrand->clear();
    ui->lineEditModel->clear();
    ui->lineEditYear->clear();
    ui->lineEditPlate->clear();

    ui->radioButtonPetrol->setChecked(true);
    ui->radioButtonDiesel->setChecked(false);

    ui->checkBoxHeatedSeats->setChecked(false);
    ui->checkBoxParktronic->setChecked(false);
    ui->checkBoxMats->setChecked(false);
}

QString Car::AutoData::toHumanReadableString() const
{
    const QString engineText = engine == EngineType::Petrol ? "Бензин" : "Дизель";
    const QString opts = QString("Подогрев сидений: %1; Парктроники: %2; Коврики: %3")
            .arg(heatedSeats ? "Да" : "Нет")
            .arg(parktronic ? "Да" : "Нет")
            .arg(mats ? "Да" : "Нет");

    return QString("Марка: %1; Модель: %2; Год: %3; Гос.номер: %4; Двигатель: %5; %6")
            .arg(brand, model)
            .arg(year)
            .arg(plate, engineText, opts);
}

std::optional<QString> Car::validateBrand(const QString &value) const
{
    if (value.isEmpty()) return QString("Поле 'Марка' обязательно");
    static const QRegularExpression re(QStringLiteral("^[A-ZА-ЯЁ]+$"));
    if (!re.match(value).hasMatch()) {
        return QString("Марка: только ПРОПИСНЫЕ буквы англ/рус");
    }
    return std::nullopt;
}

std::optional<QString> Car::validateModel(const QString &value) const
{
    if (value.isEmpty()) return QString("Поле 'Модель' обязательно");
    return std::nullopt;
}

std::optional<QString> Car::validateYear(const QString &value) const
{
    if (value.isEmpty()) return QString("Поле 'Год выпуска' обязательно");
    static const QRegularExpression re(QStringLiteral("^\\d{4}$"));
    if (!re.match(value).hasMatch()) {
        return QString("Год выпуска: введите ровно 4 цифры");
    }
    const int year = value.toInt();
    const int currentYear = QDate::currentDate().year();
    if (year < 1886 || year > currentYear) {
        return QString("Год выпуска: диапазон 1886-%1").arg(currentYear);
    }
    return std::nullopt;
}

std::optional<QString> Car::validatePlate(const QString &value) const
{
    if (value.isEmpty()) return QString("Поле 'Гос. номер' обязательно");
    const QString letters = QStringLiteral("АВЕКМНОРСТУХABEKMHOPCTYX");
    const QRegularExpression re(
        QStringLiteral("^[%1]\\d{3}[%1]{2}(?:\\d{2}|(?:101|111))$").arg(letters));
    if (!re.match(value).hasMatch()) {
        return QString("Гос. номер: A111AA22 или A111AA222 (регион 101/111 для трёх цифр)");
    }
    return std::nullopt;
}

bool Car::readAndValidateForm(AutoData &outData, QString &outError) const
{
    const QString brand = ui->lineEditBrand->text().trimmed();
    const QString model = ui->lineEditModel->text().trimmed();
    const QString yearStr = ui->lineEditYear->text().trimmed();
    const QString plate = ui->lineEditPlate->text().trimmed().toUpper();

    if (auto e = validateBrand(brand))  { outError = *e; return false; }
    if (auto e = validateModel(model))  { outError = *e; return false; }
    if (auto e = validateYear(yearStr)) { outError = *e; return false; }
    if (auto e = validatePlate(plate))  { outError = *e; return false; }

    AutoData data;
    data.brand = brand.toUpper();
    data.model = model;
    data.year = yearStr.toInt();
    data.plate = plate;
    data.engine = ui->radioButtonDiesel->isChecked() ? EngineType::Diesel : EngineType::Petrol;
    data.heatedSeats = ui->checkBoxHeatedSeats->isChecked();
    data.parktronic = ui->checkBoxParktronic->isChecked();
    data.mats = ui->checkBoxMats->isChecked();

    outData = data;
    return true;
}

void Car::saveToFile(const AutoData &data, const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(const_cast<Car*>(this), tr("Ошибка"), tr("Не удалось открыть файл для записи: %1").arg(filePath));
        return;
    }
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << data.toHumanReadableString() << "\n";
}

void Car::handleResetClicked()
{
    resetForm();
}

void Car::handleSaveClicked()
{
    AutoData data;
    QString error;
    if (!readAndValidateForm(data, error)) {
        QMessageBox::warning(this, tr("Проверка данных"), error);
        return;
    }

    saveToFile(data, QStringLiteral("result.txt"));
    QMessageBox::information(this, tr("Готово"), tr("Данные сохранены в файл result.txt"));
}
