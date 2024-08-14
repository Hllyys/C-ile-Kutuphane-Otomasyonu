#ifndef KITAP_H
#define KITAP_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class kitap;
}

class kitap : public QDialog
{
    Q_OBJECT

public:
    explicit kitap(QSqlDatabase,QWidget *parent = nullptr);
    ~kitap();
    void listele();

private slots:
    void on_tumkitaplar_tableView_clicked(const QModelIndex &index);

    void on_yenikayit2_btn_clicked();

    void on_guncelle2_btn_clicked();

    void on_sil_btn_clicked();



private:
    Ui::kitap *ui;
    QSqlQuery *sorgu;
    QSqlQuery *sorgu2;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
    int kitapno;
};

#endif // KITAP_H
