#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbrir, SIGNAL(triggered(bool)), this, SLOT(abrir(bool)));
    connect(ui->actionExecutar, SIGNAL(triggered(bool)), this, SLOT(executar(bool)));
    connect(ui->actionSalvar, SIGNAL(triggered(bool)), this, SLOT(salvar(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::abrir(bool value){

    QString fn = QFileDialog::getOpenFileName();

    if(!fn.isEmpty())
    {
        original = QImage (fn);
        ui->img1->setPixmap(QPixmap::fromImage(original));
    }
}

void MainWindow::salvar(bool value){
    QString fn = QFileDialog::getSaveFileName();

    if(!fn.isEmpty())
    {
        resultado.save(fn);
    }
}

void MainWindow::executar(bool value){
    resultado = QImage (original.width(), original.height(), QImage::Format_RGB32);

    for(int i = 0; i < original.width(); ++i)
    {
        for(int j = 0; j < original.height(); ++j)
        {
            QRgb cor = original.pixel(i, j); //coluna, linha
            QRgb corAnt = original.pixel(i-1, j); //coluna, linha
            QRgb corProx = original.pixel(i+1, j); //coluna, linha

            int pesoAtual =0;
            int pesoAnt = -1;
            int pesoProx = 1;

           QRgb corFinal =
                    qRgb((qRed(cor)*pesoAtual + qRed(corAnt)*pesoAnt + qRed(corProx)*pesoProx),
                         (qGreen(cor)*pesoAtual + qGreen(corAnt)*pesoAnt + qGreen(corProx)*pesoProx),
                         (qBlue(cor)*pesoAtual + qBlue(corAnt)*pesoAnt + qBlue(corProx)*pesoProx));


            resultado.setPixel(i,j, corFinal);
        }
    }

    ui->img2->setPixmap(QPixmap::fromImage(resultado));
}
