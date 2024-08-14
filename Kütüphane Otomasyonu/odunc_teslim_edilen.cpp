#include "odunc_teslim_edilen.h"
#include "ui_odunc_teslim_edilen.h"

odunc_teslim_edilen::odunc_teslim_edilen(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odunc_teslim_edilen)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(db);
    sorgu2=new QSqlQuery(db);
    sorgu3=new QSqlQuery(db);
    sorgu4=new QSqlQuery(db);
    listele();
    listele2();
}

odunc_teslim_edilen::~odunc_teslim_edilen()
{
    delete ui;
}

void odunc_teslim_edilen::listele()
{
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","odunc alinan tablosundan veri çekerken hata ile karşılaşıldı!","ok");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->odunckitaplarlist_tableView->setModel(model);
}

void odunc_teslim_edilen::listele2()
{
    sorgu2->prepare("select * from odunc_teslim_edilen");
    if(!sorgu2->exec())
    {
        QMessageBox::critical(this,"hata!","odunc teslim tablosundan veri çekerken hata ile karşılaşıldı!","ok");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu2);
    ui->teslimedilenlist_tableView->setModel(model2);
}






void odunc_teslim_edilen::on_odunckitaplarlist_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_2->setText(model->index(index.row(),1).data().toString());

}


void odunc_teslim_edilen::on_oduncuver_btn_clicked()
{
    oduncverilen_tarih=ui->dateEdit2->text();
    sorgu->prepare("insert into odunc_teslim_edilen(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?)");
    sorgu->addBindValue(ui->lineEdit->text().toInt());
    sorgu->addBindValue(ui->lineEdit_2->text().toInt());
    sorgu->addBindValue(ui->dateEdit2->text());
    sorgu->addBindValue(oduncverilen_tarih);
    sorgu->addBindValue(borc);
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","odunc vermede hata oluştu","ok");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->teslimedilenlist_tableView->setModel(model);
    listele2();


    sorgu4->prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu4->addBindValue(ui->lineEdit->text().toInt());
    sorgu4->addBindValue(ui->lineEdit_2->text().toInt());

    if(!sorgu4->exec())
    {
        QMessageBox::critical(this,"hata!","odunc almada silme hatası ile karşılaşıldı!","ok");
        return;
    }
    model4=new QSqlQueryModel();
    model4->setQuery(*sorgu4);
    ui->odunckitaplarlist_tableView->setModel(model4);
    listele();

}

