#ifndef ODUNC_TESLIM_EDILEN_H
#define ODUNC_TESLIM_EDILEN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStringList>


namespace Ui {
class odunc_teslim_edilen;
}

class odunc_teslim_edilen : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_teslim_edilen(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_teslim_edilen();
    void listele();
    void listele2();







private slots:
    void on_odunckitaplarlist_tableView_clicked(const QModelIndex &index);



    void on_oduncuver_btn_clicked();

private:
    Ui::odunc_teslim_edilen *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQuery *sorgu2;
    QSqlQueryModel *model2;
    QSqlQuery *sorgu3;
    QSqlQueryModel *model3;
    QSqlQuery *sorgu4;
    QSqlQueryModel *model4;
    QString oduncverilen_tarih="";
    int borc;

};

#endif // ODUNC_TESLIM_EDILEN_H
