#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rk41d.h"
#include "pot.h"
#include "myplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplay()
{
    double x0 = ui->xSlider->value()/100.0;
    double v0 = ui->vSlider->value()/100.0;
    double dt = ui->tSlider->value()/100.0;

    double t0 = 0.0;
    double x1,v1,t1;

    int pot = ui->potComboBox->currentIndex();

    rk41d(x0,v0,t0,dt,chosen_a(pot),x1,v1);
    t1 = t0 + dt;

    ui->outputTextBrowser->clear();

    ui->outputTextBrowser->append(QString().sprintf("Start:\nx0: %.3f\nv0: %.3f\ndt: %.3f",x0,v0,t1));
    ui->outputTextBrowser->append(QString().sprintf("\nRK4:\nx1: %.3f\nv1: %.3f",x1,v1));
    ui->outputTextBrowser->append(QString().sprintf("\nEuler:\nx1: %.3f\nv1: %.3f",
                                          x0+v0*dt, v1+a_harmonic(x0,v0,t0)*dt));

    int chosen_plot = ui->plotComboBox->currentIndex();
    myplot(ui->myCustomPlot, chosen_plot, x0, v0, chosen_a(pot));
}
