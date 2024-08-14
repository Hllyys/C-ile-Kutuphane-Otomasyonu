#ifndef UYE_H
#define UYE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class uye;
}

class uye : public QDialog
{
    Q_OBJECT

public:
    explicit uye(QSqlDatabase,QWidget *parent = nullptr);
    ~uye();
    void listele();

private slots:
    void on_uye_tableView_clicked(const QModelIndex &index);

    void on_yenikayit_btn_clicked();

    void on_guncelle_btn_clicked();

    void on_sil_btn_clicked();

private:
    Ui::uye *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    int c,d;
};

#endif // UYE_H
