#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ustawienia.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->timer1 = new QTimer();
    this->timer2 = new QTimer();
    this->timer3 = new QTimer(this);
    connect(this->timer1, SIGNAL(timeout()), this, SLOT(on_TimerInterrupt1()));
    connect(this->timer2, SIGNAL(timeout()), this, SLOT(on_TimerInterrupt2()));
    connect(this->timer3, SIGNAL(timeout()), this, SLOT(on_TimerInterrupt3()));
    ui->wykresSinus->addGraph();
    ui->wykresProstokat->addGraph();
    ui->wykresPila->addGraph();
    this->StartStop1 = false;
    this->StartStop2 = false;
    this->StartStop3 = false;
    sin_amp = 5.0; sin_freq = 1.0; sin_bias = 0.0; sin_phase = 0.0;
    rect_amp = 5.0; rect_freq = 1.0; rect_bias = 0.0;
    saw_amp = 5.0; saw_freq = 1.0; saw_bias = 0.0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer1;
    delete timer2;
}

void MainWindow::on_settings_clicked()
{
    Ustawienia *oknoUstawien = new Ustawienia(this);
    connect(oknoUstawien, &Ustawienia::parametersSinChanged, this, &MainWindow::aktualizujSinus);
    connect(oknoUstawien, &Ustawienia::parametersRectChanged, this, &MainWindow::aktualizujProstokat);
    connect(oknoUstawien, &Ustawienia::parametersSawChanged, this, &MainWindow::aktualizujPile);
    oknoUstawien->show();
}
void MainWindow::aktualizujSinus(double amp, double freq, double bias, double phase) {
    this->sin_amp = amp; this->sin_freq = freq; this->sin_bias = bias; this->sin_phase = phase;
}
void MainWindow::aktualizujProstokat(double amp, double freq, double bias) {
    this->rect_amp = amp; this->rect_freq = freq; this->rect_bias = bias;
}
void MainWindow::aktualizujPile(double amp, double freq, double bias) {
    this->saw_amp = amp; this->saw_freq = freq; this->saw_bias = bias;
}
void MainWindow::on_toggleSinus_clicked()
{
    if(this->StartStop1){
        timer1->stop();
        this->StartStop1 = false;
    }
    else{
        timer1->start(20);
        this->StartStop1 = true;
    }
}

void MainWindow::on_toggleProstokat_clicked()
{
    if(this->StartStop2){
        timer2->stop();
        this->StartStop2 = false;
    } else {
        timer2->start(20);
        this->StartStop2 = true;
    }
}

void MainWindow::on_togglePila_clicked()
{
    if(this->StartStop3){
        timer3->stop();
        this->StartStop3 = false;
    } else {
        timer3->start(20);
        this->StartStop3 = true;
    }
}

void MainWindow::on_TimerInterrupt1()
{
    double maxX = 2;
    static unsigned int licznik = 0;
    static QVector<double> time;
    static QVector<double> value;
    double t = licznik * 0.01;
    double val = sin_bias + sin_amp * sin(3.1416 * 2 * sin_freq * t + sin_phase);
    time.append(t);
    value.append(val);
    if (time.size() > 400) {
        time.removeFirst();
        value.removeFirst();
    }
    ui->wykresSinus->graph(0)->setData(time, value);
    if (t < maxX) {
        ui->wykresSinus->xAxis->setRange(0, maxX);
    } else {
        ui->wykresSinus->xAxis->setRange(t - maxX, t);
    }
    double margin = sin_amp * 0.1;
    if (margin == 0) margin = 1.0;
    double bottomLimit = (sin_bias - sin_amp) - margin;
    double topLimit    = (sin_bias + sin_amp) + margin;
    ui->wykresSinus->yAxis->setRange(bottomLimit, topLimit);
    ui->wykresSinus->replot();
    licznik++;
}

void MainWindow::on_TimerInterrupt2()
{
    double maxX = 2;
    static unsigned int licznik = 0;
    static QVector<double> time;
    static QVector<double> value;
    double t = licznik * 0.01;
    double sinVal = sin(3.1416 * 2 * rect_freq * t);
    double val = (sinVal >= 0) ? (rect_bias + rect_amp) : (rect_bias - rect_amp);

    time.append(t);
    value.append(val);
    if (time.size() > 400) {
        time.removeFirst();
        value.removeFirst();
    }
    ui->wykresProstokat->graph(0)->setData(time, value);
    if (t < maxX) {
        ui->wykresProstokat->xAxis->setRange(0, maxX);
    } else {
        ui->wykresProstokat->xAxis->setRange(t - maxX, t);
    }
    double margin = rect_amp * 0.1;
    if (margin == 0) margin = 1.0;
    double bottomLimit = (rect_bias - rect_amp) - margin;
    double topLimit    = (rect_bias + rect_amp) + margin;

    ui->wykresProstokat->yAxis->setRange(bottomLimit, topLimit);
    ui->wykresProstokat->replot();

    licznik++;
}

void MainWindow::on_TimerInterrupt3()
{
    double maxX = 2;
    static unsigned int licznik = 0;
    static QVector<double> time;
    static QVector<double> value;

    double t = licznik * 0.01;
    double cycle = 0.0;
    if (saw_freq != 0.0) cycle = std::fmod(t * saw_freq, 1.0);
    double val = saw_bias + (cycle * 2.0 * saw_amp) - saw_amp;

    time.append(t);
    value.append(val);
    if (time.size() > 400) {
        time.removeFirst();
        value.removeFirst();
    }
    ui->wykresPila->graph(0)->setData(time, value);

    if (t < maxX) {
        ui->wykresPila->xAxis->setRange(0, maxX);
    } else {
        ui->wykresPila->xAxis->setRange(t - maxX, t);
    }
    double margin = saw_amp * 0.1;
    if (margin == 0) margin = 1.0;
    double bottomLimit = (saw_bias - saw_amp) - margin;
    double topLimit    = (saw_bias + saw_amp) + margin;

    ui->wykresPila->yAxis->setRange(bottomLimit, topLimit);
    ui->wykresPila->replot();

    licznik++;
}
