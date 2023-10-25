#include "mainwindow_n.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QTextDocument>
#include <QSqlDatabase>
#include <QFileDialog>
#include "exportexcelobject.h"
#include <QMainWindow>
#include <QCalendarWidget>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_visite->setModel(V.afficher());
    ui->le_code->setValidator( new QIntValidator(0, 9999, this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_valider_clicked()
{

        QString marque=ui->le_marque->text();
        QString matricule=ui->le_matricule->text();
        QString date_v=ui->le_date_v->text();
        QString nature_v=ui->le_nature_v->text();
        int code=ui->le_code->text().toInt();
        //QMessageBox::information(nullptr,"error",QString(" %1 ").arg(date_v));
       Visite v(marque,matricule,date_v,nature_v,code);
       bool test=v.ajouter();
           if(test)
           {
               ui->tab_visite->setModel(V.afficher());
               QMessageBox::information(nullptr, QObject::tr("database is open"),
                           QObject::tr("ajout effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

       }
          else
               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                           QObject::tr("ajout non effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           ui->le_marque->clear();
           ui->le_matricule->clear();
           ui->le_date_v->clear();
           ui->le_nature_v->clear();
           ui->le_code->clear();
}

void MainWindow::on_modifier_clicked()
{
            QString marque=ui->le_marque_2->text();
            QString matricule=ui->le_matricule_2->text();
            QString date_v=ui->le_date_v_2->text();
            QString nature_v=ui->le_nature_v_2->text();
            int code=ui->le_code_2->text().toInt();
            Visite v(marque,matricule,date_v,nature_v,code);
            bool test=v.update(code);
            if(test){
                ui->tab_visite->setModel(V.afficher());
                QMessageBox::information(nullptr,"modification activite","activite modifie avec succés");
            }
            else
                    QMessageBox::warning(nullptr,"Error","activite non modifie");


             ui->le_code->clear();
             ui->le_marque->clear();
             ui->le_matricule->clear();
             ui->le_date_v->clear();
             ui->le_nature_v->clear();
}

void MainWindow::on_supprimer_clicked()
{

      int supp=ui->le_code_sup->text().toInt();
                 bool test=V.supprimer(supp);
            QMessageBox msgBox;

            if (test)
            {

              msgBox.setText("Supprimer avec succes.");
             ui->tab_visite->setModel(V.afficher());

            }

            else
               msgBox.setText("Echec de suppression");
               msgBox.exec();

               ui->le_code_sup->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    S = new stat_nb();
              S->setWindowTitle("statistique par date ");
              S->stats();
              S->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    Visite a;

           ui->tab_visite->setModel(tempvis.trier());
}

void MainWindow::on_rech_cursorPositionChanged(int arg1, int arg2)
{
    ui->tab_visite->setModel(tempvis.rechercher(ui->rech->text()));



           QString test =ui->rech->text();



           if(test=="")

           {

               ui->tab_visite->setModel(tempvis.afficher());//refresh

           }
}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tab_visite->model()->rowCount();
    const int columnCount =ui->tab_visite->model()->columnCount();
    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"

                 <<  QString("<title>%1</title>\n").arg("eleve")
                              <<  "</head>\n"
                                  "<body>\n"
                                  "<h1>Liste des visites</h1>"
                                  "<table border=1 cellspacing=0 cellpadding=2>\n";

                 // headers
                out << "<thead><tr bgcolor=#f0f0f0>";

        for (int column = 0; column < columnCount; column++)

               if (!ui->tab_visite->isColumnHidden(column))

                   out << QString("<th>%1</th>").arg(ui->tab_visite->model()->headerData(column, Qt::Horizontal).toString());

                    out << "</tr></thead>\n";

                        // data table

       for (int row = 0; row < rowCount; row++) {

            out << "<tr>";

           for (int column = 0; column < columnCount; column++) {

               if (!ui->tab_visite->isColumnHidden(column)) {
                    QString data = ui->tab_visite->model()->data(ui->tab_visite->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                     }

                    }

         out << "</tr>\n";

        }

 out <<  "</table>\n"

      "</body>\n"

      "</html>\n";

      QTextDocument *document = new QTextDocument();

      document->setHtml(strStream);
      //QTextDocument document;
      //document.setHtml(html);
      QPrinter printer(QPrinter::PrinterResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setOutputFileName("visite.pdf");
      document->print(&printer);

}

void MainWindow::on_exel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->tab_visite);

        //colums to export
        obj.addField(0, "MARQUE", "char(20)");
        obj.addField(1, "MATRICULE", "char(15)");
        obj.addField(2, "DATE_VT", "char(20)");
        obj.addField(3, "NATURE_DE_VISITE", "char(20)");




        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
         }

}

void MainWindow::on_calendar_clicked()
{
    // Créez une instance de QCalendarWidget
    calendar = new QCalendarWidget(this);

    // Ajouter QCalendarWidget à la fenêtre principale
    setCentralWidget(calendar);

    // Définissez la date minimale et maximale pour le calendrier
    calendar->setMinimumDate(QDate::currentDate().addYears(-1));
    calendar->setMaximumDate(QDate::currentDate().addYears(1));

    // Connexion d'un signal pour récupérer la date sélectionnée
    connect(calendar, SIGNAL(clicked(QDate)), this, SLOT(calendarClicked(QDate)));
    qDebug() << "Date selected: " << date_v;
    QPushButton *backButton = new QPushButton("Retour", calendar);
    backButton->setGeometry(QRect(QPoint(90, 10), QSize(75, 30)));


    connect(backButton, &QPushButton::clicked, [=]() {
        calendar->hide();

        QWidget *mainWindow = qobject_cast<QWidget *>(this->parent());
        if (mainWindow) {
            mainWindow->show();
        }
    });

}
