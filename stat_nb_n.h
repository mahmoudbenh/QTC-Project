#ifndef STAT_NB_H
#define STAT_NB_H
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class stat_nb;
}

class stat_nb : public QDialog
{
    Q_OBJECT

public:
    explicit stat_nb(QWidget *parent = nullptr);
    ~stat_nb();
    void stats();
        QChartView *chartView ;

private:
    Ui::stat_nb *ui;
};

#endif // STAT_NB_H
