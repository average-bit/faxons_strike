#include "dns.h"
#include "mainwindow.h"
#include "worldthread.h"
#include "opcodes.h"


dns::dns(QObject *parent) : QObject(parent)
{

}

QVector <QByteArray> dns::dns_main(QByteArray dns_input, QString mainip, QString sender, QByteArray senderPort)
{

    QByteArray hold = dns_input;


    QByteArray middle1 = hold.mid(26,16);
    QByteArray udpcheck1 = middle1.toUpper();
    qDebug() <<"gate/patch" <<hold;
    QString Data = hold.fromHex(hold);
    qDebug() <<"Data" << Data;

    QString MessageType = Data.mid(0,4);

    if(MessageType == "XXXX")
    {
        QHostAddress newsender = QHostAddress(sender);
        quint16 senderPort1 = senderPort.toUShort(nullptr,10);

        QString LargeString = "";

        if(db.isOpen())
        {
            db.close();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        }

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(Opcodes::m_FileName);
        db.open();

        QSqlQuery querysl ("SELECT COUNT (*) FROM MAINTOON_STARTING_LOCATIONS");

        int rotatesl = 0;

        while(querysl.next())
        {
            rotatesl = querysl.value(0).toInt();
        }

        for(int it = 1; it < rotatesl+1; it++)
        {

            querysl.prepare (QString ("SELECT * FROM MAINTOON_STARTING_LOCATIONS WHERE rowid = :val"));
            querysl.bindValue(":val",it);
            querysl.exec();

            qDebug() << "";



            QString PacketID = "";
            QString PlayersName = "";
            QString PlayersID = "";
            QString StartingCity = "";

            LargeString.clear();

            while(querysl.next())
            {
                PacketID = querysl.value(0).toString();;
                PlayersName = querysl.value(1).toString();;
                PlayersID = querysl.value(2).toString();
                StartingCity = querysl.value(3).toString();

                qDebug() << "PacketID" << PacketID;
                qDebug() << "PlayersID" << PlayersID;
                qDebug() << "PlayersName" << PlayersName;
                qDebug() << "StartingCity" << StartingCity;

                LargeString.append(PacketID + "#1#" + PlayersID + "#2#" + PlayersName + "#3#" + StartingCity);
            }



            worldthread::udpsocket3->writeDatagram(LargeString.toUtf8(),newsender,senderPort1);
        }

        LargeString = "Finished";
        worldthread::udpsocket3->writeDatagram(LargeString.toUtf8(),newsender,senderPort1);
    }




    QByteArray SendOut = "";



    //0001010000010000000000000236390130033136380331393207696E2D61646472046172706100000C0001
    //BC940100000100000000000003777777076578616D706C6503636F6D0000010001

    int skip = 0;

    if (hold.contains("0001010000010000000000000") || hold.contains("7061746368196576") || hold.contains("23639013003313638033")) //PATCH DNS CALL
    {
        skip = 1;
        QByteArray header2 = hold.mid(0,4); //get 2 byte header from received packet
        QByteArray gateout2 = patchdns;
        header2.append(gateout2);
        QString hexip = QString("%1").arg(QHostAddress(MainWindow::PublicMainip).toIPv4Address(), 8, 16, QLatin1Char( '0' )); //make sure we get a 8 byte ip
        QByteArray outip = hexip.toUtf8(); //move ip to array
        QByteArray patchresult1 = header2.append(outip);
        QByteArray finalpatch1 = patchresult1.fromHex(patchresult1);

        QVector <QByteArray> dnsvector;
        dnsvector.append(finalpatch1);
        dnsvector.append("PATCH DNS Done...");

        qDebug() << "finalpatch1" << finalpatch1;
        qDebug() << "PATCH DNS Done...";

        return dnsvector;


    }

    if ((hold.contains("0001010000010000000000000") && skip == 0) || (hold.contains("6761746531027573") && skip == 0)) //GATE DNS CALL
    {
        QByteArray header = hold.mid(0,4); //get 2 byte header from received packet
        QByteArray gateout1 = gatedns;
        header.append(gateout1);
        QString hexip = QString("%1").arg(QHostAddress(MainWindow::PublicMainip).toIPv4Address(), 8, 16, QLatin1Char( '0' )); //make sure we get a 8 byte ip
        QByteArray outip = hexip.toUtf8(); //move ip to array
        QByteArray gateresult1 = header.append(outip); //add ip to the packet
        QByteArray finalgate1 = gateresult1.fromHex(gateresult1); //change from hex to send it out

        QVector <QByteArray> dnsvector;
        dnsvector.append(finalgate1);
        dnsvector.append("Gate DNS Done...");

        qDebug() << "finalpatch1" << finalgate1;
        qDebug() << "Gate DNS Done...";

        return dnsvector;

    }

    QVector <QByteArray> null;
    null.append("NULL");
    return null;
}
