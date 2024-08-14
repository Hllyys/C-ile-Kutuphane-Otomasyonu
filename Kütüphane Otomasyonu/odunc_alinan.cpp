#include "odunc_alinan.h"
#include "ui_odunc_alinan.h"
#include <QDebug>

odunc_alinan::odunc_alinan(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odunc_alinan)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(db);
    sorgu2=new QSqlQuery(db);
    sorgu3=new QSqlQuery(db);
    sorgu4=new QSqlQuery(db);
    sorgu5=new QSqlQuery(db);
    listele();
    listele2();
    listele3();
}

odunc_alinan::~odunc_alinan()
{
    delete ui;
}

void odunc_alinan::listele()
{
    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"uye tablosu çekerken hata olustu","ok");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tumuyeler2_tableView->setModel(model);
}

void odunc_alinan::listele2()
{
    sorgu2->prepare("select * from kitap");
    if(!sorgu2->exec())
    {
        QMessageBox::critical(this,"kitap tablosu çekerken hata olustu","ok");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu2);
    ui->tumkitaplar2_tableview->setModel(model2);
}

void odunc_alinan::listele3()
{
    sorgu3->prepare("select * from odunc_alinan");
    if(!sorgu3->exec())
    {
        QMessageBox::critical(this,"odunc alinan tablosu çekerken hata olustu","ok");
        return;
    }
    model3=new QSqlQueryModel();
    model3->setQuery(*sorgu3);
    ui->kitaplistesi_tableView->setModel(model3);

}



void odunc_alinan::on_tumuyeler2_tableView_clicked(const QModelIndex &index)
{
    ui->uyeno2_ln->setText(model->index(index.row(),0).data().toString());

}


void odunc_alinan::on_tumkitaplar2_tableview_clicked(const QModelIndex &index)
{
    ui->kitapno2_ln->setText(model->index(index.row(),0).data().toString());

}


void odunc_alinan::on_oduncal_btn_clicked()
{
    sorgu5->exec("select * from kitap");
    while(sorgu5->next())
    {
        int no=sorgu5->value(0).toInt();
        if(no==ui->kitapno2_ln->text().toInt())
        {
            c=sorgu5->value(2).toInt();
            break;
        }
    }

    sorgu4->prepare("SELECT * FROM odunc_alinan WHERE kitap_no=?");
    sorgu4->addBindValue(ui->kitapno2_ln->text().toInt());
    sorgu4->exec();

    while (sorgu4->next())
    {
        syc+=1;
    }

    if(syc>c)
    {
        QMessageBox::information(this,"Hata","stok yok");
        return;
    }





    sorgu->exec("select * from odunc_alinan");


    while (sorgu->next())
    {
            a = sorgu->value(0).toInt();
            b = sorgu->value(1).toInt();

            if(a==ui->uyeno2_ln->text().toInt() && b==ui->kitapno2_ln->text().toInt())
            {
                QMessageBox::information(this,"Hata","Aynı kitap tekrar ödünç alinamaz");
                return;
            }
    }
    sorgu2->prepare("insert into odunc_alinan(uye_no,kitap_no,odunc_alma_tarihi) values(?,?,?)");
    sorgu2->addBindValue(ui->uyeno2_ln->text());
    sorgu2->addBindValue(ui->kitapno2_ln->text());
    sorgu2->addBindValue(ui->dateEdit->text());
    if(!sorgu2->exec())
    {
        QMessageBox::critical(this,"hata!","ödünç alırken hata olustu","ok");
        return;
    }
    listele();
    listele2();
    listele3();
}

