#include "kitap.h"
#include "ui_kitap.h"

kitap::kitap(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kitap)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(db);
    sorgu2=new QSqlQuery(db);
    listele();
}

kitap::~kitap()
{
    delete ui;
}

void kitap::listele()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","kitap tablosundan veri çekerken hata ile karşılaşıldı!","ok");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tumkitaplar_tableView->setModel(model);
}

void kitap::on_tumkitaplar_tableView_clicked(const QModelIndex &index)
{
    ui->kitapno_ln->setText(model->index(index.row(),0).data().toString());
    ui->kitapad_ln->setText(model->index(index.row(),1).data().toString());
    ui->stok_ln->setText(model->index(index.row(),2).data().toString());

    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->kitapno_ln->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","odunc alınan tablosundan veri çekerken hata ile karşılaşıldı!","ok");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->oduncalinma_tableView->setModel(model);

    sorgu2->prepare("select * from odunc_teslim_edilen where kitap_no=?");
    sorgu2->addBindValue(ui->kitapno_ln->text().toInt());
    if(!sorgu2->exec())
    {
        QMessageBox::critical(this,"hata!","odunc teslim alınan tablosundan veri çekerken hata ile karşılaşıldı!","ok");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu2);
    ui->oncedenoduncalinma_tableView->setModel(model2);

}


void kitap::on_yenikayit2_btn_clicked()
{
    if(ui->kitapad_ln->text()=="" | ui->stok_ln->text()=="")
    {
        QMessageBox::critical(this,"Hata!","boş geçilemez");
    }
    else
    {
        sorgu->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?)");
        sorgu->addBindValue(ui->kitapad_ln->text());
        sorgu->addBindValue(ui->stok_ln->text());
    }
    sorgu->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?)");
    sorgu->addBindValue(ui->kitapad_ln->text());
    sorgu->addBindValue(ui->stok_ln->text());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","kitabı kaydederken hata oluştu","ok");
        return;
    }
    listele();
}


void kitap::on_guncelle2_btn_clicked()
{
    sorgu->prepare("update kitap set kitap_ad=?,kitap_sayisi=? where kitap_no=?");
    sorgu->addBindValue(ui->kitapad_ln->text());
    sorgu->addBindValue(ui->stok_ln->text().toInt());
    sorgu->addBindValue(ui->kitapno_ln->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","kitabı güncelleme yaparken hata oluştu","ok");
        return;
    }
    listele();
}


void kitap::on_sil_btn_clicked()
{
    sorgu->exec("select * from odunc_alinan");
    kitapno=ui->kitapno_ln->text().toInt();
    int b;
    while(sorgu->next())
    {
        int b=sorgu->value(1).toInt();

        if(b==kitapno)
        {
            QMessageBox::critical(this,"Hata","Bu kitap silinemez çünkü ödünç verilmiştir","ok");
            return;
        }
    }


    sorgu->prepare("delete from kitap where kitap_no=?");
    sorgu->addBindValue(ui->kitapno_ln->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","kitabı silerken hata olustu","ok");
        return;
    }
    listele();
}




