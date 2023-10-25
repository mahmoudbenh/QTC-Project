#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "visite.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include <QIntValidator>
#include "stat_nb_n.h"
#include <QCalendarWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_valider_clicked();
    void on_modifier_clicked();

    void on_supprimer_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_rech_cursorPositionChanged(int arg1, int arg2);

    void on_pdf_clicked();

    void on_exel_clicked();

    void on_calendar_clicked();

private:
    Ui::MainWindow *ui;
    QString matricule,nature_v,marque,date_v;
    int code;
    Visite V;
    stat_nb *S;
    Visite tempvis;
    QCalendarWidget *calendar;
};

#endif // MAINWINDOW_H
