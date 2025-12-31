#ifndef USTAWIENIA_H
#define USTAWIENIA_H

#include <QDialog>

namespace Ui {
class Ustawienia;
}

class Ustawienia : public QDialog
{
    Q_OBJECT

public:
    explicit Ustawienia(QWidget *parent = nullptr);
    ~Ustawienia();
signals:
    void parametersSinChanged(double amp, double freq, double bias, double phase);
    void parametersRectChanged(double amp, double freq, double bias);
    void parametersSawChanged(double amp, double freq, double bias);
private slots:
    void on_sinDialChanged();
    void on_rectDialChanged();
    void on_sawDialChanged();
private:
    Ui::Ustawienia *ui;
};

#endif // USTAWIENIA_H
