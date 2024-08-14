#include "uye.h"
#include "ui_uye.h"

uye::uye(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uye)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(db);
    listele();
}

uye::~uye()
{
    delete ui;
}

void uye::listele()
{
    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","uye tablosundan veri çekerken hata ile karşılaşıldı!","ok");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->uye_tableView->setModel(model);
}

void uye::on_uye_tableView_clicked(const QModelIndex &index)
{
    ui->uye_no->setText(model->index(index.row(),0).data().toString());
    ui->uyead_ln->setText(model->index(index.row(),1).data().toString());
    ui->uyesoyad_ln->setText(model->index(index.row(),2).data().toString());
}


void uye::on_yenikayit_btn_clicked()
{
    if(ui->uyead_ln->text()=="" | ui->uyesoyad_ln->text()=="")
    {
        QMessageBox::critical(this,"Hata!","boş geçilemez");
    }
    else
    {
        sorgu->prepare("insert into uye(uye_ad,uye_soyad) values(?,?)");
        sorgu->addBindValue(ui->uyead_ln->text());
        sorgu->addBindValue(ui->uyesoyad_ln->text());
    }
    sorgu->prepare("insert into uye(uye_ad,uye_soyad) values(?,?)");
    sorgu->addBindValue(ui->uyead_ln->text());
    sorgu->addBindValue(ui->uyesoyad_ln->text());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","gerekli alanları doldurunuz","ok");
        return;
    }
    listele();
}


void uye::on_guncelle_btn_clicked()
{
    sorgu->prepare("update uye set uye_ad=?,uye_soyad=? where uye_no=?");
    sorgu->addBindValue(ui->uyead_ln->text());
    sorgu->addBindValue(ui->uyesoyad_ln->text());
    sorgu->addBindValue(ui->uye_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","uye güncellemede hata olustu","ok");
        return;
    }
    listele();
}


void uye::on_sil_btn_clicked()
{
    c=ui->uye_no->text().toInt();

    sorgu->exec("select * from odunc_alinan");

    while(sorgu->next())
    {
        d=sorgu->value(0).toInt();

        if(d==c)
        {
            QMessageBox::critical(this,"Hata","uye silinemez teslim etmedigi kitaplar var","ok");
            return;
        }
    }

    sorgu->prepare("delete from uye where uye_no=?");
    sorgu->addBindValue(ui->uye_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata!","uye silmede hata olustu","ok");
        return;
    }
    listele();

}

