#ifndef VISITE_H
#define VISITE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QtDebug>
class Visite
{
public:
    Visite(QString,QString,QString,QString,int);
    Visite();
    QString getMatricule()
    {
        return matricule;
    }
    QString getNature_v()
    {
        return nature_v;
    }
    QString getMarque()
    {
        return marque;
    }
    QString getDate_v()
    {
        return date_v;
    }
    int getCode()
    {
        return code;
    }
    void setMatricule(QString matricule)
    {
        this->matricule=matricule;
    }
    void setMarque(QString marque)
    {
        this->marque=marque;
    }
    void setNature_v(QString nature_v)
    {
        this->nature_v=nature_v;
    }
    void setDate_v(QString date_v)
    {
        this->date_v=date_v;
    }
    void setCode(int code)
    {
        this->code=code;
    }
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool update(int);
    QSqlQueryModel * trier();
    QSqlQueryModel* rechercher(QString);
private:
   QString matricule,nature_v,marque,date_v;
   int code;

};

#endif // VISITE_H
