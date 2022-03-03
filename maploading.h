#ifndef MAPLOADING_H
#define MAPLOADING_H

#include <QObject>
#include<QString>
#include<QList>
#include<QByteArray>
#include<QMap>
#include<QVector>
#include<QtConcurrent/QtConcurrentDepends>
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QDebug>
#include <QHostAddress>

class maploading : public QObject
{
    Q_OBJECT
public:
    explicit maploading(QObject *parent = nullptr);

    static QVector<QString> MaploadingToUIvector;
    static bool MapLoadingFinished;
    QHostAddress PublicMainip;
    QHostAddress mainip;
    QByteArray ClientsID = "";
    QByteArray ClientsIP = "";
    QByteArray ClientsPort = "";
    QByteArray ClientsPacket = "";



    QSqlDatabase db = QSqlDatabase::database();
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>();
    QFuture<void> f1;

    QString FileName = "C:/PCSX2/" + QString::number(0) + ".txt";

    QVector <QString> WorldNameVector =
    {
        "Tunaria","Rathe Mountains","Odus","Lavastorm Mountains","Plane of Sky","Secrets"
    };

signals:


public slots:
         void MapStart();
         void Mapconstruction();
         QVector<QByteArray> Mapfinished();


private:

private:
         ////////////////////DB offload to Map//////////

         QString rowline = "";
         QString rowline2 = "";
         QString rowline3 = "";
         QByteArray rowline4 = "";
         QByteArray rowline5 = "";

         int tablesize = 0;
         int tablesize2 = 0;
         int tablesize3 = 0;
         int tablesize4 = 0;
         int tablesize5 = 0;
         int tablesize6 = 0;
         int tablesize7 = 0;
         int rotateZ = 0;
         int tablesizeZ = 0;
         int tablesizeG = 0;
         int tablesizeC = 0;
         int rotateC = 0;
         int rotate = 0;
         int rotate2 = 0;
         int rotate3 = 0;
         int rotate4 = 0;
         int rotate5 = 0;
         int rotate6 = 0;
         int rotate7 = 0;
         /////////////////////////////////////////////////


};

#endif // MAPLOADING_H
