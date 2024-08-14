#ifndef ODUNC_ALINAN_H
#define ODUNC_ALINAN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class odunc_alinan;
}

class odunc_alinan : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_alinan(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_alinan();
    void listele();
    void listele2();
    void listele3();


private slots:
    void on_tumuyeler2_tableView_clicked(const QModelIndex &index);



    void on_tumkitaplar2_tableview_clicked(const QModelIndex &index);

    void on_oduncal_btn_clicked();

private:
    Ui::odunc_alinan *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQuery *sorgu2;
    QSqlQueryModel *model2;
    QSqlQuery *sorgu3;
    QSqlQueryModel *model3;
    QSqlQuery *sorgu4;
    QSqlQuery *sorgu5;
    int a,b,c;
    int syc;




};

#endif // ODUNC_ALINAN_H
