#ifndef CAR_H
#define CAR_H

#include <QMainWindow>
#include <QString>
#include <QRegularExpression>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui {
class Car;
}
QT_END_NAMESPACE

class Car : public QMainWindow
{
    Q_OBJECT

public:
    Car(QWidget *parent = nullptr);
    ~Car();

private:
    Ui::Car *ui;

    enum class EngineType {
        Petrol,
        Diesel
    };

    struct AutoData {
        QString brand;
        QString model;
        QString plate;
        int year;
        EngineType engine;
        bool heatedSeats;
        bool parktronic;
        bool mats;

        QString toHumanReadableString() const;
    };

    void resetForm();
    void connectSignals();

    std::optional<QString> validateBrand(const QString &value) const;
    std::optional<QString> validateModel(const QString &value) const;
    std::optional<QString> validateYear(const QString &value) const;
    std::optional<QString> validatePlate(const QString &value) const;

    bool readAndValidateForm(AutoData &outData, QString &outError) const;
    void saveToFile(const AutoData &data, const QString &filePath) const;

private slots:
    void handleResetClicked();
    void handleSaveClicked();
};
#endif
