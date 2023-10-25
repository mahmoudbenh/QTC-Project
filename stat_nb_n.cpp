#include "stat_nb_n.h"
#include "ui_stat_nb.h"
QT_CHARTS_USE_NAMESPACE
stat_nb::stat_nb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_nb)
{
    ui->setupUi(this);
}

stat_nb::~stat_nb()
{
    delete ui;
}
void stat_nb::stats()
{

    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM VISITE");
    q1.exec();

    q2.prepare("SELECT * FROM VISITE WHERE NATURE_DE_VISITE='normale'");
    q2.exec();

    q3.prepare("SELECT * FROM VISITE WHERE NATURE_DE_VISITE>='vff'");
    q3.exec();

    q4.prepare("SELECT * FROM VISITE WHERE NATURE_DE_VISITE='bcf' ");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("normale",c1);
    series->append("vff",c2);
    series->append("bcf",c3);




    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->stat_label);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(621,471);
    chartView->show();


}
