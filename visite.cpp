#include "visite.h"


Visite::Visite(QString marque,QString matricule,QString date_v,QString nature_v,int code)
{
    this->matricule=matricule;
    this->marque=marque;
    this->nature_v=nature_v;
    this->date_v=date_v;
    this->code=code;
}

Visite::Visite(){
    this->matricule=" ";
    this->marque=" ";
    this->nature_v=" ";
    this->date_v="0000/00/00";
    this->code=0;
}
bool Visite::ajouter()
{

    QSqlQuery query;
    QString res= QString::number(code);
    query.prepare("INSERT INTO VISITE(MARQUE,MATRICULE,DATE_VT,NATURE_DE_VISITE,CODE_DE_CONFIRMATION) VALUES(:marque,:matricule,:date_v,:nature_v,:code);");
    query.bindValue(":code",res);
    query.bindValue(":matricule",matricule);
    query.bindValue(":marque",marque);
    query.bindValue(":nature_v",nature_v);
    query.bindValue(":date_v",date_v);

return query.exec();
}
QSqlQueryModel * Visite::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM VISITE;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("marque"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("matricule"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date_v"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nature_v"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("code"));
      return model;
    }
bool Visite::supprimer(int code){
    QSqlQuery query;
    QString res=QString::number(code);
    query.prepare("DELETE FROM VISITE WHERE CODE_DE_CONFIRMATION = :code ;");
    query.bindValue(":code",res);
    return query.exec();
}
bool Visite::update(int code){
    QSqlQuery query;
    QString res=QString::number(code);
    query.prepare("UPDATE VISITE SET MARQUE= :marque,MATRICULE= :matricule,DATE_VT= :date_v,NATURE_DE_VISITE= :nature_v,CODE_DE_CONFIRMATION= :code WHERE CODE_DE_CONFIRMATION = :code;");
    query.bindValue(":code",res);
    query.bindValue(":marque",marque);
    query.bindValue(":matricule",matricule);
    query.bindValue(":date_v",date_v);
    query.bindValue(":nature_v",nature_v);
    return query.exec();
}
QSqlQueryModel * Visite::trier()
  {
      QSqlQueryModel * model= new QSqlQueryModel();
              model->setQuery("SELECT * FROM VISITE ORDER BY CODE_DE_CONFIRMATION ");
              return model;
  }
QSqlQueryModel* Visite::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
             QString recher="select * from VISITE where CODE_DE_CONFIRMATION like '%"+rech+"%'";
           model->setQuery(recher);
             return model;
}

