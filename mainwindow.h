#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void aktualizujSinus(double amp, double freq, double bias, double phase);
    void aktualizujProstokat(double amp, double freq, double bias);
    void aktualizujPile(double amp, double freq, double bias);
private slots:
    void on_settings_clicked();
    void on_toggleSinus_clicked();
    void on_TimerInterrupt1();
    void on_toggleProstokat_clicked();
    void on_TimerInterrupt2();
    void on_togglePila_clicked();
    void on_TimerInterrupt3();
private:
    Ui::MainWindow *ui;
    QTimer *timer1, *timer2, *timer3;
    bool StartStop1, StartStop2, StartStop3;
    double sin_amp, sin_freq, sin_bias, sin_phase;
    double rect_amp, rect_freq, rect_bias;
    double saw_amp, saw_freq, saw_bias;
};
#endif // MAINWINDOW_H
