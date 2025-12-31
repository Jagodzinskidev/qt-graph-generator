#include "ustawienia.h"
#include "ui_ustawienia.h"

Ustawienia::Ustawienia(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ustawienia)
{
    ui->setupUi(this);
    ui->dialSinA->setRange(0, 300);
    ui->dialSinFreq->setRange(0, 100);
    ui->dialSinBias->setRange(-150, 150);
    ui->dialSinPhase->setRange(-1800, 1800);

    ui->dialRectA->setRange(0, 300);
    ui->dialRectFreq->setRange(0, 100);
    ui->dialRectBias->setRange(-150, 150);

    ui->dialSawA->setRange(0, 300);
    ui->dialSawFreq->setRange(0, 100);
    ui->dialSawBias->setRange(-150, 150);

    connect(ui->dialSinA, &QDial::valueChanged, this, &Ustawienia::on_sinDialChanged);
    connect(ui->dialSinFreq, &QDial::valueChanged, this, &Ustawienia::on_sinDialChanged);
    connect(ui->dialSinBias, &QDial::valueChanged, this, &Ustawienia::on_sinDialChanged);
    connect(ui->dialSinPhase, &QDial::valueChanged, this, &Ustawienia::on_sinDialChanged);

    connect(ui->dialRectA, &QDial::valueChanged, this, &Ustawienia::on_rectDialChanged);
    connect(ui->dialRectFreq, &QDial::valueChanged, this, &Ustawienia::on_rectDialChanged);
    connect(ui->dialRectBias, &QDial::valueChanged, this, &Ustawienia::on_rectDialChanged);

    connect(ui->dialSawA, &QDial::valueChanged, this, &Ustawienia::on_sawDialChanged);
    connect(ui->dialSawFreq, &QDial::valueChanged, this, &Ustawienia::on_sawDialChanged);
    connect(ui->dialSawBias, &QDial::valueChanged, this, &Ustawienia::on_sawDialChanged);
}

Ustawienia::~Ustawienia()
{
    delete ui;
}

void Ustawienia::on_sinDialChanged()
{
    double amp = ui->dialSinA->value() / 10.0;
    double freq = ui->dialSinFreq->value() / 10.0;
    double bias = ui->dialSinBias->value() / 10.0;
    double phase = ui->dialSinPhase->value() / 10.0;

    ui->sinAmpVal->setText(QString::number(amp,'f', 1));
    ui->sinFreqVal->setText(QString::number(freq,'f', 1));
    ui->sinBiasVal->setText(QString::number(bias,'f', 1));
    ui->sinPhaseVal->setText(QString::number(phase,'f', 1));

    emit parametersSinChanged(amp, freq, bias, phase);
}

void Ustawienia::on_rectDialChanged()
{
    double amp = ui->dialRectA->value() / 10.0;
    double freq = ui->dialRectFreq->value() / 10.0;
    double bias = ui->dialRectBias->value() / 10.0;

    ui->rectAmpVal->setText(QString::number(amp,'f', 1));
    ui->rectFreqVal->setText(QString::number(freq,'f', 1));
    ui->rectBiasVal->setText(QString::number(bias,'f', 1));
    emit parametersRectChanged(amp, freq, bias);
}

void Ustawienia::on_sawDialChanged()
{
    double amp = ui->dialSawA->value() / 10.0;
    double freq = ui->dialSawFreq->value() / 10.0;
    double bias = ui->dialSawBias->value() / 10.0;

    ui->sawAmpVal->setText(QString::number(amp,'f', 1));
    ui->sawFreqVal->setText(QString::number(freq,'f', 1));
    ui->sawBiasVal->setText(QString::number(bias,'f', 1));
    emit parametersSawChanged(amp, freq, bias);
}
