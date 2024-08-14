#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uye.h"
#include "kitap.h"
#include "odunc_alinan.h"
#include "odunc_teslim_edilen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.setDatabaseName("C:/Users/EXCALIBUR/Desktop/dersler/gorselprogramlamaLAB/kutuphane3/kutuphabe_otomasyon.db");
    if(!db.open())
    {
        ui->statusbar->showMessage("veri tabanına bağlanılamadı.");
    }
    else
    {
        ui->statusbar->showMessage("veri tabanına bağlanıldı.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_uyeislemleri_btn_clicked()
{
    uye *uyeler=new uye(db);
    uyeler->show();
}


void MainWindow::on_kitapislemleri_btn_clicked()
{
    kitap *ktp=new kitap(db);
    ktp->show();
}


void MainWindow::on_oduncalma_btn_clicked()
{
    odunc_alinan *o_alinan=new odunc_alinan(db);
    o_alinan->show();
}





void MainWindow::on_teslimetme_btn_clicked()
{
    odunc_teslim_edilen *teslim=new odunc_teslim_edilen(db);
    teslim->show();
}

