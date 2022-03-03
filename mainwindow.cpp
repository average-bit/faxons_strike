#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "objectpacket.h"
#include "packetsize.h"
#include "generator.h"
#include "increment.h"
#include "coaching.h"
#include "targeting.h"
#include "xorpacket.h"
#include "add_or_sub.h"
#include "merchants.h"
#include "convert.h"
#include "loot.h"
#include "combat.h"
#include "charcreate.h"
#include "facingdirection.h"
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QFont>
#include <QFontDialog>
#include <QTreeWidgetItem>
#include <QRandomGenerator>
#include <QtCore/qglobal.h>
#include <QStyle>
#include <QCommonStyle>
#include "quests.h"
#include "maploading.h"
#include "fortytwentyninedec.h"
#include "loginthread.h"
#include "serverselectthread.h"
#include "worldthread.h"
#include "login.h"
#include "crc.h"
#include "serverselect.h"
#include "packetparsing.h"
#include "opcodes.h"
#include "flipped.h"
#include "loadingcharacter.h"
#include "checkthezone.h"
#include "dns.h"
#include "dnsthread.h"
#include "patch.h"
#include "patchthread.h"


QVector <QString> Loot::Loot_list;
ADD_OR_SUB CurrentItem;


/////////////////////////////////////Teleport////////////////
QStandardItem *treetop;
QStandardItem *one;
QStandardItem *two;
QStandardItem *three;
QStandardItemModel  *standardModel = new QStandardItemModel; //Set Up The Tree Model
QStandardItem *rootNode = standardModel->invisibleRootItem();//Set Invisible Root Item
/////////////////////////////////////////////////////////////




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    qDebug() << "";
    qDebug() << "";
    qDebug() << "";
    qDebug() << "";
    qDebug() << "Opening_MainWindow";

    Quests::FakeFlag = ui->lineEdit_247->text().toInt(nullptr,10);


    //Mr.Faxon
    ui->lineEdit->setText("192.168.000.112");
    ui->lineEdit_234->setText("108.184.198.155");

    //Wisbe
//    ui->lineEdit->setText("192.168.000.112");
//    ui->lineEdit_234->setText("097.112.166.252");

    //engle2010
//    ui->lineEdit->setText("192.168.001.112");
//    ui->lineEdit_234->setText("107.167.233.169");


    ui->progressBar->setMinimum(0);

    connect(&worldtimer,&QTimer::timeout,this,&MainWindow::world_servercall);
    connect(&servtimer,&QTimer::timeout,this,&MainWindow::serv_servercall);
    connect(&logintimer,&QTimer::timeout,this,&MainWindow::login_servercall);
    connect(&timer, &QTimer::timeout, this, &MainWindow::teleportoff);
    connect(&coachtimer,&QTimer::timeout,this,&MainWindow::coachingoff);
    connect(&dnstimer,&QTimer::timeout,this,&MainWindow::dns_servercall);
    connect(&patchtimer,&QTimer::timeout,this,&MainWindow::patch_servercall);
    connect(&aggroTimer,&QTimer::timeout,this,&MainWindow::AggroCheck);

    QString directory = QCoreApplication::applicationDirPath();

    Opcodes::m_FileName = directory + Database;



    Opcodes::GroupID = "9D030C00";


    ui->pushButton_4->setDisabled(true);
    ui->pushButton_25->setDisabled(true);

    ui->pushButton_172->setDisabled(true);
    ui->pushButton_191->setDisabled(true);

    ui->pushButton_165->setDisabled(true);
    ui->pushButton_173->setDisabled(true);
    ui->pushButton_156->setDisabled(true);

    ui->pushButton_167->setDisabled(true);
    ui->pushButton_187->setDisabled(true);

    ui->tabWidget_2->setDisabled(true);
    ui->tabWidget_4->setDisabled(true);
    ui->tabWidget_12->setDisabled(true);


    QString filename = "C:/Customize/122_Vector_Compass.jpg";
    ui->label_217->setPixmap(filename);

    filename = "C:/Customize/Main1.jpg";
    ui->label_72->setPixmap(filename);



    ui->pushButton_26->setDisabled(true);
    ui->pushButton_27->setDisabled(true);
    ui->pushButton_61->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");

    Combat::ExtraDamage = ui->lineEdit_153->text().toInt(nullptr,10);

    ui->actionReset_Main_Coordinates->setDisabled(true);
    ui->actionReset_All_Coaches->setDisabled(true);


    ui->pushButton_47->setDisabled(true);
    ui->pushButton_17->setDisabled(true);
    ui->pushButton_48->setDisabled(true);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(25000);
    ///////////////////////////////////////////////////////

    /////////////////////////Teleport///////////////////




    ////////////////////////Teleport//////////////////

    ////////////////////////////Map/////////////////////
    scene = new QGraphicsScene(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setBackgroundBrush(QColor (95, 213, 253));
    item2 = scene->addPixmap(a);
    item2->setPos(210,230);
    scene->setSceneRect(1600,1600,100,100);
    item1 = scene->addPixmap(b.scaled(100,100));

    scene2 = new QGraphicsScene(this);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    scene2->setBackgroundBrush(QColor (95, 213, 253));
    item3 = scene2->addPixmap(c);
    scene2->setSceneRect(0,0,2000,2000);
    item4 = scene2->addPixmap(d.scaled(1,1));
    ui->graphicsView_2->setScene(scene2);
    ui->graphicsView_2->show();


    /////////////////////////////Map////////////////////
    //qDebug() << "MapOfChannelVectors00" << MapOfChannelVectors;




    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Opcodes::m_FileName);
    db.open();


    db.transaction();


    if(ui->checkBox_48->isChecked() == true)
    {
        if(!db.isOpen() == true)
        {
            qDebug() << "db is closed";
        }

        if(db.isOpen() == true)
        {
            qDebug() << "db is open";
        }

        if(db.isOpenError())
        {
            qDebug() << "db has error";
        }

        if(!db.isOpenError())
        {
            qDebug() << "db has  no error";
        }

        QSqlQuery querytlpt2;
        QString Table = "MAINTOON";
        QString ObjectID = "ObjectID (4)";
        QString RemainingTPs = "RemainingTPs";
        QString XPbar = "XPbar";
        QString TotalXP = "TotalXP";
        QString Level = "Level (1)";

        QString CharSelectionID = "01012000";
        QString RemainingTPs1 = "00";
        QString XPbar1 = "00";
        QString TotalXP1 = "00";
        QString Level1 = "01";

        querytlpt2.prepare(QStringLiteral("UPDATE %1 SET [%2] = :val2,[%3] = :val3,[%4] = :val4,[%5] = :val5 WHERE [%6] = :val6")
                           .arg(Table).arg(RemainingTPs).arg(XPbar).arg(TotalXP).arg(Level).arg(ObjectID));


        querytlpt2.bindValue(":val2",RemainingTPs1);
        querytlpt2.bindValue(":val3",XPbar1);
        querytlpt2.bindValue(":val4",TotalXP1);
        querytlpt2.bindValue(":val5",Level1);
        querytlpt2.bindValue(":val6",CharSelectionID);

        querytlpt2.exec();

        if(!querytlpt2.exec())
        {
            qDebug() << "querytlpt2.lastError() = " << querytlpt2.lastError();
        }

        ///////////////////////////////////////////////////////////
    }



    QSqlQuery queryQr ("SELECT COUNT (*) FROM QUEST_ID_RESULTS");

    while(queryQr.next())
    {
        qDebug() << "queryQr.value(0).toInt()" << queryQr.value(0).toInt();

        Quests::PacketID_Quests = queryQr.value(0).toInt();
    }

    qDebug() << "Quests::PacketID_Quests0" << Quests::PacketID_Quests;
    Quests::PacketID_Quests++;
    qDebug() << "Quests::PacketID_Quests1" << Quests::PacketID_Quests;

    for(int it = 1; it < Quests::PacketID_Quests; it++)
    {
        queryQr.prepare (QString ("SELECT * FROM QUEST_ID_RESULTS WHERE rowid = :val"));
        queryQr.bindValue(":val",it);
        queryQr.exec();

        QString QuestID = "";
        QString Description = "";
        int PacketID = 0;
        QVector<QString> tempvect;

        QSqlRecord record = queryQr.record();

        while(queryQr.next())
        {
            PacketID = queryQr.value(0).toInt();
            QuestID = queryQr.value(1).toString();
            Description = queryQr.value(2).toString();

            for(int re = 3; re < record.count(); re++)
            {
                QString Result = queryQr.value(re).toString();

                if(Result.isEmpty() == false)
                {
                    tempvect.append(Result);
                }
                else
                {
                    break;
                }
            }
        }

        Description_PacketID.insert(Description,PacketID);


        Quests::QuestsIDs_ResultsVectorMap.insert(QuestID,tempvect);
    }

    //----------------------------------------------------------------------------------------------

    QSqlQuery queryQ1 ("SELECT COUNT (*) FROM QUEST_ID_RANGES");

    int Rotate = 0;

    while(queryQ1.next())
    {
        Rotate = queryQ1.value(0).toInt();
    }

    Rotate++;

    for(int it = 1; it < Rotate; it++)
    {

        QMap<QVector<int>,QString>TempVectMap;


        queryQ1.prepare (QString ("SELECT * FROM QUEST_ID_RANGES WHERE rowid = :val"));
        queryQ1.bindValue(":val",it);
        queryQ1.exec();

        QString RaceClassLocation = "";
        QString QuestID = "";
        int StartRange = 0;
        int EndRange = 0;

        while(queryQ1.next())
        {
            QSqlRecord record = queryQ1.record();

            RaceClassLocation = queryQ1.value(1).toString();

            for(int re = 2; re < record.count(); re+=4)
            {
                QuestID = queryQ1.value(re).toString();

                if(QuestID.isEmpty() == false)
                {
                    QVector<int> TempVaLvect;
                    StartRange = queryQ1.value(re+2).toInt();
                    EndRange = queryQ1.value(re+3).toInt();

                    TempVaLvect.append(StartRange);
                    TempVaLvect.append(EndRange);

                    TempVectMap.insert(TempVaLvect,QuestID);
                }
                else
                {
                    break;
                }
            }
        }

        Quests::LocationQuestID_QuestVectorsMap.insert(RaceClassLocation,TempVectMap);
    }

    qDebug() << "";

    //----------------------------------------------------------------------------------------------

    QSqlQuery queryQ ("SELECT COUNT (*) FROM QUESTGIVERS_IDS");

    while(queryQ.next())
    {
        Quests::Quest_Givers_PacketID = queryQ.value(0).toInt();
    }

    Quests::Quest_Givers_PacketID++;
    ui->lineEdit_239->setText(QString::number(Quests::Quest_Givers_PacketID));

    for(int it = 1; it < Quests::Quest_Givers_PacketID; it++)
    {
        QVector<QString> TempVaLvect;

        queryQ.prepare (QString ("SELECT * FROM QUESTGIVERS_IDS WHERE rowid = :val"));
        queryQ.bindValue(":val",it);
        queryQ.exec();

        QString Name = "";
        QString NPCsID = "";
        int PacketID = 0;

        while(queryQ.next())
        {
            QSqlRecord record = queryQ.record();

            PacketID = queryQ.value(0).toInt();
            Name = queryQ.value(1).toString();
            NPCsID = queryQ.value(2).toString();

            qDebug() << "";
            qDebug() << "Query_Has_Next" << it;

            for(int re = 3; re < record.count(); re++)
            {
                QString val = queryQ.value(re).toString();

                if(val.isEmpty() == false)
                {
                    qDebug() << "val" << val;
                    TempVaLvect.append(val);
                }
                else
                {
                    break;
                }
            }
        }

        Quests::QuestGiversNames_IDS_Map.insert(Name,PacketID);
        Quests::QuestValuesVectorMap.insert(it,TempVaLvect);
        Quests::QuestGiversID_NameMap.insert(NPCsID,Name);

        QString QuestsID = "";
        QString Description = "";
        QString StartingCity1 = "";
        QString Faction = "";
        QString Race = "";
        QString Class = "";
        QString Level = "";

        QMap<QString,QVector<QString>> tempMap;

        QVector<QString> QuestIDVector;

        for(int re = 0; re < TempVaLvect.size(); re+=7)
        {
            QuestsID = TempVaLvect.at(re);
            Description = TempVaLvect.at(re+1);
            StartingCity1 = TempVaLvect.at(re+2);
            Faction = TempVaLvect.at(re+3);
            Race = TempVaLvect.at(re+4);
            Class = TempVaLvect.at(re+5);
            Level = TempVaLvect.at(re+6);

            QVector<QString>tempvect;

            tempvect.append(QuestsID);
            tempvect.append(Description);
            tempvect.append(StartingCity1);
            tempvect.append(Faction);
            tempvect.append(Race);
            tempvect.append(Class);

            tempMap.insert(Level,tempvect);

            QuestIDVector.append(QuestsID);
        }

        Quests::NPCsID_QuestIDsVectorMap.insert(NPCsID,QuestIDVector);

        Quests::QuestGiversID_Level_LocationClassRaceMap.insert(NPCsID,tempMap);
    }

    qDebug() << "";



    QSqlQuery queryt ("SELECT COUNT (*) FROM QUEST_TEXT");

    while(queryt.next())
    {
        Quests::PacketID_Text = queryt.value(0).toInt();
    }


    Quests::PacketID_Text++;

    ui->lineEdit_245->setText(QString::number(Quests::PacketID_Text));


    QString Object_ID2 = "Text_ID";
    QSqlQuery query2;
    query2.prepare (QString ("SELECT [%1] FROM QUEST_TEXT WHERE rowid = :val").arg(Object_ID2));
    query2.bindValue(":val",Quests::PacketID_Text -1);
    query2.exec();


    while (query2.next())
    {
        Quests::Text_ID = query2.value(0).toString().toUpper();
    }

    QByteArray split1 = Quests::Text_ID.toUtf8();

    QByteArray first_4_digits = split1.mid(0,4);
    QByteArray last_4_digits = split1.mid(4,4);

    if(last_4_digits.isEmpty() == true)
    {
        last_4_digits = "0000";
    }

    increment first1; //get class object
    QByteArray firstresult1 = first1.count(first_4_digits).toUpper(); //ABAA

    if(firstresult1 == "0000")
    {
        first_4_digits = "0000";

        increment second1; //get class object
        QByteArray secondresult1 = second1.count(last_4_digits).toUpper(); //if first is FFFF this will be BCBB //secondresult is bytearray in header
        QByteArray New_Text_ID = firstresult1 + secondresult1.toUpper();
        ui->lineEdit_226->setText(New_Text_ID);
        ui->lineEdit_220->setText(New_Text_ID);
        Quests::Text_ID = New_Text_ID;
    }
    else
    {
        QByteArray New_Text_ID = firstresult1 + last_4_digits.toUpper();
        ui->lineEdit_226->setText(New_Text_ID);
        ui->lineEdit_220->setText(New_Text_ID);
        Quests::Text_ID = New_Text_ID;
    }




    QSqlQuery queryQM ("SELECT COUNT (*) FROM QUEST_MENUS");

    int rotateqm = 0;

    while(queryQM.next())
    {
        rotateqm = queryQM.value(0).toInt();
    }

    Quests::PacketID_Menu = rotateqm;
    Quests::PacketID_Menu++;

    QString MenusID = "";

    for(int it = 1; it < rotateqm+1; it++)
    {
        QVector<QString> tempOptionIDVect;

        queryQM.prepare (QString ("SELECT * FROM QUEST_MENUS WHERE rowid = :val"));
        queryQM.bindValue(":val",it);
        queryQM.exec();

        QSqlRecord record = queryQM.record();


        QString MenusText = "";

        while(queryQM.next())
        {
            MenusID = queryQM.value(1).toString();
            tempOptionIDVect.append(queryQM.value(2).toString());
            MenusText = queryQM.value(2).toString();

            qDebug() << "";
            qDebug() << "MenusID" << MenusID;

            for(int fd = 3; fd < record.count(); fd+=2)
            {
                QString OptionsID = queryQM.value(fd).toString();
                QString OptionsText = queryQM.value(fd+1).toString();

                if(OptionsID.isEmpty() == false)
                {
                    tempOptionIDVect.append(OptionsID);
                    tempOptionIDVect.append(OptionsText);
                }
                else
                {
                    break;
                }
            }
        }

        Quests::MenuTextCheckVector.append(MenusText);
        Quests::MenuID_MenuText_Map.insert(MenusID,MenusText);
        Quests::InGame_MenuesVectorMap.insert(MenusID,tempOptionIDVect);
    }

    Quests::Menu_ID = MenusID;

    if(Quests::Menu_ID.size() < 10)
    {
        do
        {
            Quests::Menu_ID.append("0");

        }while(Quests::Menu_ID.size() < 10);
    }

    Quests::Menu_ID.remove(0,2);

    QString Byte1st_half = Quests::Menu_ID.mid(0,4);
    QString Byte2nd_half = Quests::Menu_ID.mid(4,8);

    increment sendto;

    if(Byte1st_half == "FFFF")
    {
        Byte1st_half = "0000";
        Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
        Quests::Menu_ID = Byte1st_half;
    }
    else
    {
        Quests::Menu_ID = sendto.count(Byte1st_half.toUtf8());
        Quests::Menu_ID.append(Byte2nd_half);
    }


    Quests::Menu_ID.insert(0,"M_");

    ui->lineEdit_261->setText(QString::number(Quests::PacketID_Menu));
    ui->lineEdit_243->setText(Quests::Menu_ID);
    /////////////////////////////////////////////////////////////////////////////

    QSqlQuery queryMO ("SELECT COUNT (*) FROM QUEST_MENUS_OPTIONS");


    while(queryMO.next())
    {
        Quests::PacketID_Menu_Option = queryMO.value(0).toInt();
    }

    Quests::PacketID_Menu_Option++;

    ui->lineEdit_233->setText(QString::number(Quests::PacketID_Menu_Option));

    QString OptionsID = "";

    for(int it = 1; it < Quests::PacketID_Menu_Option; it++)
    {
        QVector<QString> tempOptionIDVect;

        queryMO.prepare (QString ("SELECT * FROM QUEST_MENUS_OPTIONS WHERE rowid = :val"));
        queryMO.bindValue(":val",it);
        queryMO.exec();

        QSqlRecord record = queryMO.record();

        QMap<QString,QVector<QString>> tempVectorMap;
        QString MenusID = "";

        QString OptionsText = "";

        while(queryMO.next())
        {
            MenusID = queryMO.value(1).toString();
            OptionsID = queryMO.value(2).toString();
            OptionsText = queryMO.value(3).toString();

            qDebug() << "";
            qDebug() << "OptionsID" << OptionsID;

            for(int fd = 4; fd < record.count(); fd++)
            {
                QString Results = queryMO.value(fd).toString();

                if(Results.isEmpty() == false)
                {
                    qDebug() << "Result_#" << fd-3 << "=" << Results;
                    tempOptionIDVect.append(Results);
                }
                else
                {
                    break;
                }
            }
        }

        qDebug() << "tempOptionIDVect" << tempOptionIDVect;

        if(Quests::MenuID_OptionsIDs_ResultsVectorMap.contains(MenusID))
        {
            tempVectorMap = Quests::MenuID_OptionsIDs_ResultsVectorMap.value(MenusID);
        }

        qDebug() << "tempVectorMap1" << tempVectorMap;

        tempVectorMap.insert(OptionsID,tempOptionIDVect);

        qDebug() << "tempVectorMap2" << tempVectorMap;

        Quests::MenuID_OptionsIDs_ResultsVectorMap.insert(MenusID,tempVectorMap);

        Quests::OptionID_OptionText_Map.insert(OptionsID,OptionsText);
    }

    //qDebug() << "Quests::MenuID_OptionsIDs_ResultsVectorMap" << Quests::MenuID_OptionsIDs_ResultsVectorMap;

    Quests::Menu_Option_ID = OptionsID;

    if(Quests::Menu_Option_ID.size() < 10)
    {
        do
        {
            Quests::Menu_Option_ID.append("0");

        }while(Quests::Menu_Option_ID.size() < 10);
    }

    Quests::Menu_Option_ID.remove(0,2);

    Byte1st_half = Quests::Menu_Option_ID.mid(0,4);
    Byte2nd_half = Quests::Menu_Option_ID.mid(4,8);



    if(Byte1st_half == "FFFF")
    {
        Byte1st_half = "0000";
        Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
        Quests::Menu_Option_ID = Byte1st_half;
    }
    else
    {
        Quests::Menu_Option_ID = sendto.count(Byte1st_half.toUtf8());
        Quests::Menu_Option_ID.append(Byte2nd_half);
    }

    Quests::Menu_Option_ID.insert(0,"O_");

    ui->lineEdit_165->setText(Quests::Menu_Option_ID);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    QSqlQuery querypop ("SELECT COUNT (*) FROM QUEST_POPUPS");



    while(querypop.next())
    {
        Quests::PacketID_Popup = querypop.value(0).toInt();
    }

    Quests::PacketID_Popup++;

    ui->lineEdit_235->setText(QString::number(Quests::PacketID_Popup));

    QString PopUpID = "";

    for(int it = 1; it < Quests::PacketID_Popup; it++)
    {
        QVector<QString> tempPopUpResultVect;

        querypop.prepare (QString ("SELECT * FROM QUEST_POPUPS WHERE rowid = :val"));
        querypop.bindValue(":val",it);
        querypop.exec();


        QString PopUpText = "";
        QSqlRecord record = querypop.record();

        while(querypop.next())
        {
            PopUpID = querypop.value(1).toString();
            PopUpText = querypop.value(2).toString();

            for(int fd = 3; fd < record.count(); fd++)
            {
                QString Results = querypop.value(fd).toString();

                if(Results.isEmpty() == false)
                {
                    qDebug() << "Result_#" << fd << "=" << Results;
                    tempPopUpResultVect.append(Results);
                }
                else
                {
                    break;
                }
            }
        }

        Quests::PopUpID_PopUpResltsVectorMap.insert(PopUpID,tempPopUpResultVect);

        Quests::PopUpID_PopUpText_Map.insert(PopUpID,PopUpText);
    }

    Quests::Popup_ID = PopUpID;

    if(Quests::Popup_ID.size() < 10)
    {
        do
        {
            Quests::Popup_ID.append("0");

        }while(Quests::Popup_ID.size() < 10);
    }

    Quests::Popup_ID.remove(0,2);

    Byte1st_half = Quests::Popup_ID.mid(0,4);
    Byte2nd_half = Quests::Popup_ID.mid(4,8);

    if(Byte1st_half == "FFFF")
    {
        Byte1st_half = "0000";
        Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
        Quests::Popup_ID = Byte1st_half;
    }
    else
    {
        Quests::Popup_ID = sendto.count(Byte1st_half.toUtf8());
        Quests::Popup_ID.append(Byte2nd_half);
    }

    Quests::Popup_ID.insert(0,"P_");

    ui->lineEdit_229->setText(Quests::Popup_ID);

    //--------------------------------------------------------------------------------------

    QSqlQuery queryLogs ("SELECT COUNT (*) FROM QUEST_LOGS");

    while(queryLogs.next())
    {
        Quests::PacketID_Logs = queryLogs.value(0).toInt();
    }

    Quests::PacketID_Logs++;

    ui->lineEdit_296->setText(QString::number(Quests::PacketID_Logs));

    QString LogsID = "";

    for(int it = 1; it < Quests::PacketID_Logs; it++)
    {
        queryLogs.prepare (QString ("SELECT * FROM QUEST_LOGS WHERE rowid = :val"));
        queryLogs.bindValue(":val",it);
        queryLogs.exec();


        QString LogsText = "";

        while(queryLogs.next())
        {
            LogsID = queryLogs.value(1).toString();
            LogsText = queryLogs.value(2).toString();
        }

        Quests::LogTextID_Text.insert(LogsID,LogsText);
    }

    Quests::Logs_ID = LogsID;


    if(Quests::Logs_ID.size() < 11)
    {
        do
        {
            Quests::Logs_ID.append("0");

        }while(Quests::Logs_ID.size() < 11);
    }

    Quests::Logs_ID.remove(0,3);

    Byte1st_half = Quests::Logs_ID.mid(0,4);
    Byte2nd_half = Quests::Logs_ID.mid(4,8);

    if(Byte1st_half == "FFFF")
    {
        Byte1st_half = "0000";
        Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
        Quests::Logs_ID = Byte1st_half;
    }
    else
    {
        Quests::Logs_ID = sendto.count(Byte1st_half.toUtf8());
        Quests::Logs_ID.append(Byte2nd_half);
    }

    Quests::Logs_ID.insert(0,"QL_");

    ui->lineEdit_297->setText(Quests::Logs_ID);

    //-----------------------------------------------------------------------------

    QSqlQuery queryDecription ("SELECT COUNT (*) FROM QUEST_DESCRIPTIONS");

    while(queryDecription.next())
    {
        Quests::PacketID_Decription = queryDecription.value(0).toInt();
    }

    Quests::PacketID_Decription++;

    ui->lineEdit_298->setText(QString::number(Quests::PacketID_Decription));

    QString DecriptionID = "";

    for(int it = 1; it < Quests::PacketID_Decription; it++)
    {
        queryDecription.prepare (QString ("SELECT * FROM QUEST_DESCRIPTIONS WHERE rowid = :val"));
        queryDecription.bindValue(":val",it);
        queryDecription.exec();


        QString DecriptionText = "";

        while(queryDecription.next())
        {
            DecriptionID = queryDecription.value(1).toString();
            DecriptionText = queryDecription.value(2).toString();
        }

        Quests::DescriptionTextID_Text.insert(DecriptionID,DecriptionText);
    }

    Quests::Decription_ID = DecriptionID;

    if(Quests::Decription_ID.size() < 11)
    {
        do
        {
            Quests::Decription_ID.append("0");

        }while(Quests::Decription_ID.size() < 11);
    }

    Quests::Decription_ID.remove(0,3);

    Byte1st_half = Quests::Decription_ID.mid(0,4);
    Byte2nd_half = Quests::Decription_ID.mid(4,8);

    if(Byte1st_half == "FFFF")
    {
        Byte1st_half = "0000";
        Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
        Quests::Decription_ID = Byte1st_half;
    }
    else
    {
        Quests::Decription_ID = sendto.count(Byte1st_half.toUtf8());
        Quests::Decription_ID.append(Byte2nd_half);
    }

    Quests::Decription_ID.insert(0,"QD_");

    ui->lineEdit_299->setText(Quests::Decription_ID);

    //----------------------------------------------------------------------------

    QSqlQuery queryPQL ("SELECT COUNT (*) FROM PLAYERS_QUESTLOGS");

    int rotatepql = 0;

    while(queryPQL.next())
    {
        rotatepql = queryPQL.value(0).toInt();
    }

    QMap<int,QString>tempvalMap =
    {
        {3,"00"}, {4 ,"02"}, {5,"04"}, {6,"06"}
    };

    for(int it = 1; it < rotatepql+1; it++)
    {
        queryPQL.prepare (QString ("SELECT * FROM PLAYERS_QUESTLOGS WHERE rowid = :val"));
        queryPQL.bindValue(":val",it);
        queryPQL.exec();

        QString PlayersID = "";
        QString QuestLogID = "";

        QMap<QString,QString> QuestLogSlot_QuestID_Map =
        {
            {"00",{""}},{"02",{""}},{"04",{""}},{"06",{""}}
        };

        QSqlRecord record = queryPQL.record();

        while(queryPQL.next())
        {
            PlayersID = queryPQL.value(1).toString();

            for(int re = 3; re < record.count(); re++)
            {
                QuestLogID = queryPQL.value(re).toString();

                if(QuestLogID.isEmpty() == false)
                {
                    QString Slot = tempvalMap.value(re);

                    QuestLogSlot_QuestID_Map.insert(Slot,QuestLogID);
                }
                else
                {
                    break;
                }
            }
        }

        Quests::PlayersID_QuestLogSlot_QuestID_MapOfMaps.insert(PlayersID,QuestLogSlot_QuestID_Map);
    }



    QSqlQuery queryzn ("SELECT COUNT (*) FROM ZONES_NAMES");

    int rotatezn= 0;

    while(queryzn.next())
    {
        rotatezn = queryzn.value(0).toInt();
    }

    for(int it = 1; it < rotatezn+1; it++)
    {
        queryzn.prepare (QString ("SELECT * FROM ZONES_NAMES WHERE rowid = :val"));
        queryzn.bindValue(":val",it);
        queryzn.exec();

        QString NewName = "";
        QString ZonesName = "";

        while(queryzn.next())
        {
            NewName = queryzn.value(1).toString();
            ZonesName = queryzn.value(2).toString();
        }

        Quests::NPCsName_ZoneMap.insert(NewName,ZonesName);

        //qDebug() << NewName << ZonesName;
    }

    qDebug() << "Finished with ZoneNames";


    db.commit();




    //////////Adding Pictures/////////



    for(int Index = 0; Index < Race_AND_Gender.size(); Index++)
    {
        QString Model = Race_AND_Gender.key(Index);

        QString filename = "C:/Customize/CharacterForms/" + Model + ".jpg";

        class QIcon pix_01(filename);
        ui->comboBox->addItem(Model);
        ui->comboBox->setItemIcon(Index,pix_01);
        ui->comboBox->setIconSize(QSize(261,341));
    }





    QString Folder = MobFolder.at(0);

    filename = "C:/Customize/Forms/" + Folder + "/" + QString::number(1) + ".jpg";

    ui->label_213->setPixmap(filename);


    for(int Index = 0; Index < GraphicValue.size(); Index++)
    {
        QString Graphic = GraphicValue.at(Index);
        ui->comboBox_40->addItem(Graphic);
    }



}

MainWindow::~MainWindow()
{
    packetparsing::packetvars IN_MainWindow;
    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    /////////////////////////Save Location///////////////////////////


    QSqlQuery querytlpt2;
    QString tablesel2 = "MAINTOON";
    QString objecttlpt2 = "ObjectID (4)";
    QString worldtlpt = "World (1)";
    QString xtlpt = "X (3)";
    QString ztlpt = "Z (3)";
    QString ytlpt = "Y (3)";
    QString facing1 = "Facing (1)";

    QString tlptid2 = IN_MainWindow.CharSelectID;
    QString chosenworld = QString("%1").arg(IN_MainWindow.masterworld,2,16,QLatin1Char('0')).toUpper();
    QString facing = IN_MainWindow.masterf;
    QString x1 = QString::fromUtf8(IN_MainWindow.masterx);
    QString z1 = QString::fromUtf8(IN_MainWindow.masterz);
    QString y1 = QString::fromUtf8(IN_MainWindow.mastery);



    if(chosenworld.isEmpty() == false && facing.isEmpty() == false && x1.isEmpty() == false &&
            z1.isEmpty() == false && y1.isEmpty() == false)
    {
        db.transaction();

        querytlpt2.prepare(QStringLiteral("UPDATE %1 SET [%2] = :val2,[%3] = :val3,[%4] = :val4,[%5] = :val5,[%6] = :val6 WHERE [%7] = :val").arg(tablesel2).arg(xtlpt).arg(ytlpt).arg(ztlpt).arg(worldtlpt).arg(facing1).arg(objecttlpt2));

        querytlpt2.bindValue(":val",tlptid2);
        querytlpt2.bindValue(":val2",x1.toUpper());
        querytlpt2.bindValue(":val3",y1.toUpper());
        querytlpt2.bindValue(":val4",z1.toUpper());
        querytlpt2.bindValue(":val5",chosenworld.toUpper());
        querytlpt2.bindValue(":val6",facing.toUpper());

        querytlpt2.exec();
        db.commit();
    }

    ///////////////////////////////////////////////////////////

    delete ui;
}


QVector<int> MainWindow::CheckTheZoneHeight()
{
    packetparsing::packetvars IN_CheckTheZoneHeight;
    IN_CheckTheZoneHeight = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);



    QVector <QVector<float>> CurrentZoneCentralVector = checkthezone::VectorOfWorlds.at(IN_CheckTheZoneHeight.masterworld);

    QString CurrentWorld = WorldNameVector.at(IN_CheckTheZoneHeight.masterworld);

    ui->lineEdit_196->setText(CurrentWorld);


    QVector <int> XandYvector;

    for(int CZ = 0; CZ < CurrentZoneCentralVector.size(); CZ++)
    {



        QCoreApplication::processEvents(QEventLoop::AllEvents);

        QVector <QString> tempWorldZoneNamesVector = checkthezone::WorldZoneNamesVector.at(IN_CheckTheZoneHeight.masterworld);


        QVector <float> CurrentZone = CurrentZoneCentralVector.at(CZ);
        QString ZonesName = tempWorldZoneNamesVector.at(CZ);




        if(ZonesName.contains("(C)"))
        {




            float ZoneX = 0.0;
            float ZoneZ = 0.0;
            float ZoneY = 0.0;



            ZoneX = CurrentZone.at(0);
            ZoneZ = CurrentZone.at(1);
            ZoneY = CurrentZone.at(2);

            QString tempstrx = IN_CheckTheZoneHeight.masterx;
            int tempint1 = tempstrx.toInt(nullptr,16);
            float NPCx = tempint1 / 128.0;

            QString tempstrz = IN_CheckTheZoneHeight.masterz;
            int tempint2 = tempstrz.toInt(nullptr,16);
            float  NPCz = tempint2 / 128.0;

            QString tempstry = IN_CheckTheZoneHeight.mastery;
            int tempint3 = tempstry.toInt(nullptr,16);
            float NPCy = tempint3 / 128.0;

            if
                    (
                     //North                 //South
                     NPCx >= ZoneX - 1000 && NPCx <= ZoneX + 1000 &&

                     //West                  //East
                     NPCy >= ZoneY - 1000 && NPCy <= ZoneY + 1000

                     )
            {
                ui->lineEdit_138->setText(ZonesName);

                IN_CheckTheZoneHeight.MyZoneh = ZonesName;

                IN_CheckTheZoneHeight.CurrentCentralZone = ZonesName;

                ui->textEdit_22->append("CurrentCentralZone1 " + IN_CheckTheZoneHeight.CurrentCentralZone);
                ui->textEdit_22->append("ZoneX " + QString::number(ZoneX));
                ui->textEdit_22->append("ZoneY " + QString::number(ZoneY));



                XandYvector.append(ZoneX);
                XandYvector.append(ZoneY);

                break;
            }
        }
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_CheckTheZoneHeight);

    return XandYvector;
}



void MainWindow::on_pushButton_clicked() //set up ip
{
    if(ui->checkBox_20->isChecked() == false)
    {
        ui->lineEdit->setText("192.168.000.112");
    }

    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(false);

    QString ip2 = ui->lineEdit->text(); //get ip from ui
    bool getit =  mainip.setAddress(ip2); //set ip address in hostadress

    if(getit == false)
    {
        QMessageBox msgBox3; //something bad happened
        msgBox3.setText("Please Enter IP");
        msgBox3.exec();
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setDisabled(true);
        ui->lineEdit->setDisabled(false);
        return;
    }
    else
    {



        //maploading

        QThread::currentThread()->setObjectName("Main_Thread");
        qDebug() << "MainWindow" << QThread::currentThread();




        connect(test->watcher,SIGNAL(progressValueChanged(int)),this,SLOT(mapprogress(int)));
        test->MapStart();




    }


    /////UI//////
    ui->actionAbout_Hagley2->setDisabled(true);
    ui->actionLoad_Database->setDisabled(true);
    ui->lineEdit->setDisabled(true);

    ui->pushButton_2->setDisabled(false);
    ui->pushButton->setDisabled(true);
    ui->pushButton_138->setDisabled(true);
    ui->textEdit_5->append("Started UDP Server...");
    ui->textEdit_5->append("Started TCP Server...");
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_17->clear();



}

void MainWindow::on_pushButton_2_clicked() //STOP SERVER
{
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
    ui->lineEdit->setDisabled(false);
    ui->textEdit_3->clear();

    world_networklist.clear();
    dns_networklist.clear();
    serv_networklist.clear();
    patch_networklist.clear();
    login_networklist.clear();

    worldtimer.stop();
    dnstimer.stop();
    servtimer.stop();
    patchtimer.stop();
    logintimer.stop();
    aggroTimer.stop();

    emit stopworldthread();
    emit stopdnsthread();
    emit stopservthread();
    emit stoppatchthread();
    emit stoploginthread();

    StopSending = true;



    ui->textEdit_5->append("Stopped UDP Server...");
    ui->textEdit_5->append("Stopped TCP Server...");
    ui->lineEdit->setDisabled(false);
    ui->lineEdit->clear();
    ui->pushButton->setDisabled(false);
    ui->pushButton_138->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
    ui->actionLoad_Database->setDisabled(false);
    ui->actionAbout_Hagley2->setDisabled(false);
    ui->actionReset_Main_Coordinates->setDisabled(false);
    ui->actionReset_All_Coaches->setDisabled(false);
    ui->treeView->setDisabled(true);
    ui->progressBar->reset();


}

void MainWindow::mapprogress(int value)
{
    if(maploading::MapLoadingFinished == true)
    {
        maploading::MapLoadingFinished = false;
        trip = true;


        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(100);

        qDebug() << "";
        qDebug() << "Map Loading is Finished";

        QString PubLic = ui->lineEdit_234->text();
        PublicMainip.setAddress(PubLic);
        //dns
        dnstimer.start(10);
        QThread* thread_dns = new QThread;
        dnsthread *worker_dns = new dnsthread;
        worker_dns->moveToThread(thread_dns);
        connect(thread_dns, SIGNAL(started()), worker_dns,SLOT(start_dns_thread()));
        connect(this,SIGNAL(bind_dns_socket(QString)),worker_dns,SLOT(binding_dns_socket(QString)));
        connect(this,SIGNAL(stopdnsthread()),worker_dns,SLOT(stop_dns_thread()));
        connect(worker_dns,SIGNAL(senddata_dns(QByteArray,QString,quint16)),this,SLOT(dnsread(QByteArray,QString,quint16)));
        connect(this,SIGNAL(outgoingdata_dns(QByteArray,QString,quint16)),worker_dns,SLOT(outgoing_dns(QByteArray,QString,quint16)));
        connect(thread_dns,SIGNAL(finished()),thread_dns,SLOT(deleteLater()));
        connect(worker_dns,SIGNAL(finished()),worker_dns,SLOT(deleteLater()));
        thread_dns->start();
        qDebug() << "DNS Thread Connected";
        emit bind_dns_socket(mainip.toString());
        //dns

        //patch
        patchtimer.start(10);
        QThread* thread_patch = new QThread;
        patchthread *worker_patch = new patchthread;
        worker_patch->moveToThread(thread_patch);
        connect(thread_patch, SIGNAL(started()), worker_patch,SLOT(start_patch_thread()));
        connect(this,SIGNAL(listen_patch_socket(QString)),worker_patch,SLOT(listen_patch_socket(QString)));
        connect(this,SIGNAL(stoppatchthread()),worker_patch,SLOT(stop_patch_thread()));
        connect(worker_patch,SIGNAL(senddata_patch(QByteArray,QString,quint16)),this,SLOT(patchread(QByteArray,QString,quint16)));
        connect(this,SIGNAL(outgoingdata_patch(QByteArray,QString,quint16)),worker_patch,SLOT(outgoing_patch(QByteArray,QString,quint16)));
        connect(thread_patch,SIGNAL(finished()),thread_patch,SLOT(deleteLater()));
        connect(worker_patch,SIGNAL(finished()),worker_patch,SLOT(deleteLater()));
        thread_patch->start();
        qDebug() << "Patch Thread Connected";
        emit listen_patch_socket(mainip.toString());
        //patch

        //login
        logintimer.start(500);
        QThread* thread_login = new QThread;
        loginthread *worker_login = new loginthread;
        worker_login->moveToThread(thread_login);
        connect(thread_login, SIGNAL(started()), worker_login,SLOT(start_login_thread()));
        connect(this,SIGNAL(listen_login_socket(QString)),worker_login,SLOT(listen_login_socket(QString)));
        connect(this,SIGNAL(stoploginthread()),worker_login,SLOT(stop_login_thread()));
        connect(worker_login,SIGNAL(senddata_login(QByteArray,QString,quint16)),this,SLOT(loginread(QByteArray,QString,quint16)));
        connect(this,SIGNAL(outgoingdata_login(QByteArray,QString,quint16)),worker_login,SLOT(outgoing_login(QByteArray,QString,quint16)));
        connect(thread_login,SIGNAL(finished()),thread_login,SLOT(deleteLater()));
        connect(worker_login,SIGNAL(finished()),worker_login,SLOT(deleteLater()));
        thread_login->start();
        qDebug() << "Login Thread Connected";
        emit listen_login_socket(mainip.toString());
        //login


        //serverselect
        servtimer.start(10);
        QThread* thread_serv = new QThread;
        serverselectthread *worker_serv = new serverselectthread;
        worker_serv->moveToThread(thread_serv);
        connect(thread_serv, SIGNAL(started()), worker_serv,SLOT(start_serv_thread()));
        connect(this,SIGNAL(bind_serv_socket(QString)),worker_serv,SLOT(binding_serv_socket(QString)));
        connect(this,SIGNAL(stopservthread()),worker_serv,SLOT(stop_serv_thread()));
        connect(worker_serv,SIGNAL(senddata_serv(QByteArray,QString,quint16)),this,SLOT(gameread1(QByteArray,QString,quint16)));
        connect(this,SIGNAL(outgoingdata_game1(QByteArray,QString,quint16)),worker_serv,SLOT(outgoing_serv(QByteArray,QString,quint16)));
        connect(thread_serv,SIGNAL(finished()),thread_serv,SLOT(deleteLater()));
        connect(worker_serv,SIGNAL(finished()),worker_serv,SLOT(deleteLater()));
        thread_serv->start();
        qDebug() << "Server Select Thread Connected";




        emit bind_serv_socket(mainip.toString());
        //serverselect

        //world /char select
        worldtimer.start(10); //start network parser clock,  can be set to zero for fastest speed
        QThread* thread_world = new QThread;
        worldthread* worker_world = new worldthread;
        worker_world->moveToThread(thread_world);
        connect(thread_world, SIGNAL(started()), worker_world, SLOT(start_world_thread()));
        connect(this,SIGNAL(bind_world_socket(QString)),worker_world,SLOT(binding_world_socket(QString)));
        connect(this,SIGNAL(stopworldthread()),worker_world,SLOT(stop_world_thread()));
        connect(worker_world,SIGNAL(senddata_world(QByteArray,QString,quint16)),this,SLOT(gameread2(QByteArray,QString,quint16)));
        connect(this,SIGNAL(outgoingdata_game2(QByteArray,QString,quint16)),worker_world,SLOT(outgoing_world(QByteArray,QString,quint16)));
        connect(thread_world,SIGNAL(finished()),thread_world,SLOT(deleteLater()));
        connect(worker_world,SIGNAL(finished()),worker_world,SLOT(deleteLater()));
        thread_world->start();
        qDebug() << "World Thread Connected";
        emit bind_world_socket(mainip.toString());


        int time = ui->lineEdit_AggroTimer->text().toInt(nullptr,10);

        aggroTimer.start(time);

        //this->showMinimized();

        //QSound::play("C:/Customize/everquest.wav");

        if(db.isOpen())
        {
            db.close();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        }

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(Opcodes::m_FileName);
        db.open();


        ui->lineEdit_72->setText(maploading::MaploadingToUIvector.at(0));
        ui->lineEdit_130->setText(maploading::MaploadingToUIvector.at(1));
        ui->Count->setText(maploading::MaploadingToUIvector.at(2));

        model = new QSqlTableModel(this);
        model->setTable("ITEMS");
        model->select();
        ui->Icon_tableView_5->setModel(model);
        ui->tableView_26->setModel(model);
        ui->tableView_26->setColumnWidth(1,300);




        model1 = new QSqlTableModel(this);
        model1->setTable("NPCS");
        model1->select();


        ui->tableView_5->setModel(model1);
        ui->tableView_5->setColumnWidth(1,300);
        ui->tableView_6->setModel(model1);
        ui->tableView_6->setColumnWidth(1,300);
        ui->tableView_7->setModel(model1);
        ui->tableView_7->setColumnWidth(1,300);
        ui->tableView_8->setModel(model1);
        ui->tableView_8->setColumnWidth(1,300);
        ui->A_tableView_5->setModel(model1);
        ui->A_tableView_5->setColumnWidth(1,300);
        ui->tableView_11->setModel(model1);
        ui->tableView_11->setColumnWidth(1,300);
        ui->tableView_12->setModel(model1);
        ui->tableView_12->setColumnWidth(1,300);

        model6 = new QSqlTableModel(this);
        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView->setModel(model6);
        ui->tableView->setColumnWidth(2,1000);
        ui->tableView_2->setModel(model6);
        ui->tableView_2->setColumnWidth(2,1000);
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);

        model9 = new QSqlTableModel(this);
        model9->setTable("QUEST_MENUS");
        model9->select();
        ui->tableView_4->setModel(model9);
        ui->tableView_4->setColumnWidth(2,300);

        model10 = new QSqlTableModel(this);
        model10->setTable("QUEST_MENUS_OPTIONS");
        model10->select();
        ui->tableView_9->setModel(model10);
        ui->tableView_9->setColumnWidth(3,300);

        model3 = new QSqlTableModel(this);
        model3->setTable("QUEST_POPUPS");
        model3->select();
        ui->tableView_10->setModel(model3);
        ui->tableView_10->setColumnWidth(2,300);

        model16 = new QSqlTableModel(this);
        model16->setTable("QUEST_LOGS");
        model16->select();
        ui->tableView_16->setModel(model16);
        ui->tableView_16->setColumnWidth(2,300);

        model17 = new QSqlTableModel(this);
        model17->setTable("QUEST_DESCRIPTIONS");
        model17->select();
        ui->tableView_17->setModel(model17);
        ui->tableView_17->setColumnWidth(2,300);

        model18 = new QSqlTableModel(this);
        model18->setTable("QUEST_ID_RESULTS");
        model18->select();
        ui->tableView_18->setModel(model18);
        ui->tableView_18->setColumnWidth(2,300);

        ui->tabWidget_2->setDisabled(false);
        ui->tabWidget_4->setDisabled(false);
        ui->tabWidget_12->setDisabled(false);

    }
    else
    {
        ui->progressBar->setValue(value + 1);

        if(trip == true)
        {
            ui->progressBar->setMaximum(100);
            ui->progressBar->setValue(100);
        }
    }
}


void MainWindow::on_actionAbout_Hagley2_triggered()
{
    QMessageBox msgBox4; //about triggered
    msgBox4.setText("EQOA Revival Test Server Hagley-2\r\nVersion 5.8\r\n''Teleport sucks...''\r\n\r\nBy Devin K.\r\nLitany 60 Druid\r\nMarrs Fist\r\nKnights Templar\r\n\r\n& Dustin F.\r\nFaxon 60 rge \r\nPPO");
    msgBox4.exec();
    return;
}



void MainWindow::on_actionLoad_Database_triggered()
{



    Opcodes::m_FileName = QFileDialog::getOpenFileName(this,tr("Open File"),"/",tr("DB Files (*.db)")); //Open File Dialog

    if(!Opcodes::m_FileName.isEmpty()) //If Cancel Is Not Pressed
    {
        if(db.isOpen())
        {
            db.close();
            db = QSqlDatabase();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        }

        ui->textEdit_5->append(Opcodes::m_FileName); //Show Path and Filename

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(Opcodes::m_FileName);


    }


}



void MainWindow::dnsread(QByteArray clientdata, QString sender, quint16 senderPort) //dns read
{
    dns_networklist.append(sender.toUtf8()); //append ip in first position
    dns_networklist.append(QString::number(senderPort,10).toUtf8()); //append port in second
    dns_networklist.append(clientdata); //append packet to third position
    ui->textEdit->append(sender + "----" + QString::number(senderPort,10) + "----" + QString::fromUtf8(clientdata));


}

void MainWindow::patchread(QByteArray clientdata, QString sender, quint16 senderPort) //patch read
{
    patch_networklist.append(sender.toUtf8()); //append ip in first position
    patch_networklist.append(QString::number(senderPort,10).toUtf8()); //append port in second
    patch_networklist.append(clientdata); //append packet to third position
    ui->textEdit->append(sender + "----" + QString::number(senderPort,10) + "----" + QString::fromUtf8(clientdata));

}

void MainWindow::loginread(QByteArray clientdata, QString sender, quint16 senderPort) //login read
{
    if(!BlockedList.contains(sender))
    {
        login_networklist.append(sender.toUtf8());
        login_networklist.append(QString::number(senderPort,10).toUtf8()); //append port in second
        login_networklist.append(clientdata); //append packet to third position

        QByteArray ClientID = clientdata.mid(0,4);
        packetparsing::packetvars IN_MainWindow;

        if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + sender.toUtf8() + QByteArray::number(senderPort)))
        {
            IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + sender.toUtf8() + QByteArray::number(senderPort));
        }

        QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);


        QDateTime dateTime = dateTime.currentDateTime();
        QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

        qDebug() << "";
        qDebug() << "";
        qDebug() << "----------------------------------------------------------";
        qDebug() << dateTimeString;
        qDebug() << "Login";
        qDebug() << "From Client: " + MainToon;
        qDebug() << "IP: " + sender;
        qDebug() << "Port: " + QString::number(senderPort,10);
        qDebug() << "To Server: Packet:";
        qDebug() << QString::fromUtf8(clientdata);
        qDebug() << "----------------------------------------------------------";
        qDebug() << "";
    }
}

void MainWindow::gameread1(QByteArray clientdata, QString sender, quint16 senderPort) //serverselect read
{
    if(!BlockedList.contains(sender))
    {

        serv_networklist.append(sender.toUtf8()); //append ip in first position
        serv_networklist.append(QString::number(senderPort,10).toUtf8()); //append port in second
        serv_networklist.append(clientdata); //append packet to third position

        QByteArray ClientID = clientdata.mid(0,4);
        packetparsing::packetvars IN_MainWindow;

        if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + sender.toUtf8() + QByteArray::number(senderPort)))
        {
            IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + sender.toUtf8() + QByteArray::number(senderPort));
        }

        QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);




        QDateTime dateTime = dateTime.currentDateTime();
        QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

        qDebug() << "";
        qDebug() << "";
        qDebug() << "----------------------------------------------------------";
        qDebug() << dateTimeString;
        qDebug() << "GameRead1";
        qDebug() << "From Client: " + MainToon;
        qDebug() << "IP: " + sender;
        qDebug() << "Port: " + QString::number(senderPort,10);
        qDebug() << "To Server: Packet:";
        qDebug() << QString::fromUtf8(clientdata);
        qDebug() << "----------------------------------------------------------";
        qDebug() << "";
    }
}

void MainWindow::gameread2(QByteArray clientdata, QString sender,quint16 senderPort) //world read
{
    if(!BlockedList.contains(sender))
    {
        world_networklist.append(sender.toUtf8()); //append ip in first position
        world_networklist.append(QString::number(senderPort,10).toUtf8()); //append port in second
        world_networklist.append(clientdata); //append packet to third position

        QByteArray ClientID = clientdata.mid(0,4);
        packetparsing::packetvars IN_MainWindow;

        ui->lineEdit_247->setText(QString::number(Quests::FakeFlag));

        if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + sender.toUtf8() + QByteArray::number(senderPort)))
        {
            IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + sender.toUtf8() + QByteArray::number(senderPort));
        }

        QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);



        QDateTime dateTime = dateTime.currentDateTime();
        QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");


        qDebug() << "";
        qDebug() << "";
        qDebug() << "----------------------------------------------------------";
        qDebug() << dateTimeString;
        qDebug() << "GameRead2";
        qDebug() << "From Client: " + MainToon;
        qDebug() << "IP: " + sender;
        qDebug() << "Port: " + QString::number(senderPort,10);
        qDebug() << "To Server: Packet:";
        qDebug() << QString::fromUtf8(clientdata);
        qDebug() << "----------------------------------------------------------";
        qDebug() << "";
    }
}



void MainWindow::dns_servercall() //testing parsing when we want to (on a timer) instead of when we get a packet
{
    if (dns_networklist.isEmpty() == false)
    {
        QByteArray ClientsIP = dns_networklist.at(0); //ip
        QByteArray ClientsPort = dns_networklist.at(1); //port
        QByteArray ClientsPacket = dns_networklist.at(2); //read data
        dns_networklist.remove(0,3); //remove the one u just read like a stack

        dns calldnsclass;
        QVector <QByteArray> dnsreturn = calldnsclass.dns_main(ClientsPacket,mainip.toString(),ClientsIP,ClientsPort);

        if (dnsreturn.isEmpty() == false && dnsreturn.at(0) != "NULL")
        {
            QByteArray dnsout = dnsreturn.at(0);
            QString dnstype = QString::fromUtf8(dnsreturn.at(1));
            ui->textEdit_5->append(dnstype);

            QHostAddress current_client_address;
            current_client_address.setAddress(QString::fromUtf8(ClientsIP));
            quint16 current_client_port = ClientsPort.toUShort(nullptr,10);
            QString addy = current_client_address.toString();
            ui->textEdit_5->append(dnsout.toHex());
            emit outgoingdata_dns(dnsout,addy,current_client_port);

        }
    }

}

void MainWindow::patch_servercall()
{
    if (patch_networklist.isEmpty() == false)
    {
        QByteArray ClientsIP = patch_networklist.at(0); //ip
        QByteArray ClientsPort = patch_networklist.at(1); //port
        QByteArray ClientsPacket = patch_networklist.at(2); //read data
        patch_networklist.remove(0,3); //remove the one u just read like a stack

        patch callpatchclass;
        QVector <QByteArray> patchreturn = callpatchclass.patch_main(ClientsPacket);

        if (patchreturn.isEmpty() == false && patchreturn.at(0) != "NULL")
        {
            QByteArray patchout = patchreturn.at(0);
            QString patchtype = QString::fromUtf8(patchreturn.at(1));
            ui->textEdit_5->append(patchtype);


            QHostAddress current_client_address;
            current_client_address.setAddress(QString::fromUtf8(ClientsIP));
            quint16 current_client_port = ClientsPort.toUShort(nullptr,10);
            QString change = current_client_address.toString();
            ui->textEdit_5->append(patchout);
            emit outgoingdata_patch(patchout,change,current_client_port);
        }
    }
}


void MainWindow::login_servercall()
{
    if(login_networklist.isEmpty() == false)
    {
        QByteArray ClientsIP = login_networklist.at(0); //ip
        QByteArray ClientsPort = login_networklist.at(1); //port
        QByteArray ClientsPacket = login_networklist.at(2); //read data
        login_networklist.remove(0,3); //remove the one u just read like a stack


        login callloginclass;
        QVector <QByteArray> loginreturn = callloginclass.login_main(ClientsIP,ClientsPort,ClientsPacket);

        if(packetparsing::SkipKey == false && ui->checkBox_2->isChecked() == true)
        {
            ui->checkBox_2->setChecked(false);
        }

        if(loginreturn.isEmpty() == false && loginreturn.at(0).contains("FAIL"))
        {
            qDebug() << "loginreturn.at(0)" << loginreturn.at(0);
        }
        else
        {
            if(loginreturn.isEmpty() == false && loginreturn.at(0) != "NULL")
            {
                QByteArray loginout = loginreturn.at(0);
                QString logintype = QString::fromUtf8(loginreturn.at(1));

                QByteArray ClientID = ClientsPacket.mid(0,4);
                packetparsing::packetvars IN_MainWindow;

                if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + ClientsIP + ClientsPort))
                {
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);
                }

                QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);



                QDateTime dateTime = dateTime.currentDateTime();
                QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

                qDebug() << "";
                qDebug() << "";
                qDebug() << "----------------------------------------------------------";
                qDebug() << dateTimeString;
                qDebug() << logintype;
                qDebug() << "To Client: " + MainToon;
                qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
                qDebug() << "IP: " + ClientsIP;
                qDebug() << "Port: " + ClientsPort;
                qDebug() << "From Server: ";
                qDebug() << loginout;
                qDebug() << "----------------------------------------------------------";
                qDebug() << "";


                QHostAddress current_client_address;
                current_client_address.setAddress(QString::fromUtf8(ClientsIP));
                quint16 current_client_port = ClientsPort.toUShort(nullptr,10);
                QString change = current_client_address.toString();


                emit outgoingdata_login(loginout,change,current_client_port);
            }
        }
    }
}

void MainWindow::serv_servercall()
{
    if(serv_networklist.isEmpty() == false)
    {
        QByteArray ClientsIP = serv_networklist.at(0); //ip
        QByteArray ClientsPort = serv_networklist.at(1); //port
        QByteArray ClientsPacket = serv_networklist.at(2); //read data
        serv_networklist.remove(0,3); //remove the one u just read like a stack

        serverselect callserverselectclass;
        QVector <QByteArray> servreturn = callserverselectclass.serverselect_main(ClientsIP,ClientsPort,ClientsPacket,PublicMainip.toString());

        QByteArray servout = "";
        QString servtype = "";
        QByteArray PacketOut = "";
        QByteArray ClientMain = "";

        qDebug() << "";
        qDebug() << "";
        qDebug() << "inside serv_servercall Mainwindow.cpp";

        if(servreturn.isEmpty() == false && servreturn.at(0) != "NULL")
        {


            servout = servreturn.at(0);
            servtype = QString::fromUtf8(servreturn.at(1));
            PacketOut = servreturn.at(2);

            QByteArray ClientID = ClientsPacket.mid(0,4);
            packetparsing::packetvars IN_MainWindow;


            if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + ClientsIP + ClientsPort))
            {
                qDebug() << "Already contained in Keep Alive";

                ClientMain = ClientID + ClientsIP + ClientsPort;

                IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientMain);
            }
            else
            {
                if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + ClientsIP))
                {
                    qDebug() << "Already added at Server Selection";

                    ClientMain = ClientID + ClientsIP;

                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientMain);

                    qDebug() << "IN_MainWindow.UserName = " << IN_MainWindow.UserName;
                }
                else
                {

                    if(packetparsing::IPandPort_AllvariablesMap.contains(ClientsIP))
                    {
                        qDebug() << "Does contain in Keep Alive";

                        ClientMain = ClientsIP;

                        IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientMain);
                    }
                    else
                    {
                        qDebug() << "Did not contain";


                        if(!packetparsing::IPandPort_AllvariablesMap.contains(ClientsIP))
                        {
                            qDebug() << "Adding to Keep Alive";

                            ClientMain = ClientsIP;

                            IN_MainWindow = packetparsing::pX;
                            packetparsing::IPandPort_AllvariablesMap.insert(ClientMain,IN_MainWindow);
                            qDebug() << "Now it contains";
                        }
                    }
                }
            }

            if(servreturn.at(0) == "Server_Keep_Alive")
            {
                qDebug() << "inside Server_Keep_Alive";

                qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;

                if(!Opcodes::CharID_ServerMessageNumbers.contains(IN_MainWindow.CharSelectID) && IN_MainWindow.CharSelectID.isEmpty() == false)
                {
                    qDebug() << "Opcodes::CharID_ServerMessageNumbers did not contain";

                    QVector<QByteArray> tempVect =
                    {"0000","0000","0000"};

                    Opcodes::CharID_ServerMessageNumbers.insert(IN_MainWindow.CharSelectID,tempVect);
                }
                else
                {
                    qDebug() << "Opcodes::CharID_ServerMessageNumbers does contain";
                }

                QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_MainWindow.CharSelectID);
                QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

                increment GrpOut;
                QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
                PacketOut.append(GrpOut_a);
                Servers_Last_MessageNumber = GrpOut_a.toUpper();

                MessNumbVect.replace(0,Servers_Last_MessageNumber);

                Opcodes::CharID_ServerMessageNumbers.insert(IN_MainWindow.CharSelectID,MessNumbVect);

                PacketOut.append(IN_MainWindow.Clients_Last_MessageNumber);
                PacketOut.append(IN_MainWindow.Clients_Last_FB_MessageNumber);

                crc sendcrc;
                QByteArray outcrc =  sendcrc.elcrc(PacketOut);

                PacketOut.append(outcrc);

                servout = PacketOut.fromHex(PacketOut);

                QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);




                QDateTime dateTime = dateTime.currentDateTime();
                QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

                qDebug() << "";
                qDebug() << "";
                qDebug() << "----------------------------------------------------------";
                qDebug() << dateTimeString;
                qDebug() << servtype + " F901 reply";
                qDebug() << "To Client: " + MainToon;
                qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
                qDebug() << "IP: " + ClientsIP;
                qDebug() << "Port: " + ClientsPort;
                qDebug() << "From Server: ";
                qDebug() << PacketOut;
                qDebug() << "----------------------------------------------------------";
                qDebug() << "";

            }
            else
            {
                servout = servreturn.at(0);
                servtype = QString::fromUtf8(servreturn.at(1));
                PacketOut = servreturn.at(2);


                QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);



                QDateTime dateTime = dateTime.currentDateTime();
                QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

                qDebug() << "";
                qDebug() << "";
                qDebug() << "----------------------------------------------------------";
                qDebug() << dateTimeString;
                qDebug() << servtype + " Server_Selection_Screen ";
                qDebug() << "To Client: " + MainToon;
                qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
                qDebug() << "IP: " + ClientsIP;
                qDebug() << "Port: " + ClientsPort;
                qDebug() << "From Server: ";
                qDebug() << PacketOut;
                qDebug() << "----------------------------------------------------------";
                qDebug() << "";


            }
        }


        if(servout.isEmpty() == false)
        {
            QHostAddress current_client_address;
            current_client_address.setAddress(QString::fromUtf8(ClientsIP));
            quint16 current_client_port = ClientsPort.toUShort(nullptr,10);
            QString change = current_client_address.toString();
            emit outgoingdata_game1(servout,change,current_client_port);
        }
    }
}

void MainWindow::AggroCheck()
{
    QMapIterator<QByteArray,struct packetparsing::packetvars> iterp(packetparsing::IPandPort_AllvariablesMap);
    while(iterp.hasNext())
    {
        iterp.next();
        QByteArray ID_IP_PORT = iterp.key();

        packetparsing::packetvars AggroCheck;

        AggroCheck = iterp.value();

        if(AggroCheck.CombatAllValuesMap.isEmpty() == false)
        {
            QMapIterator<QString,QVector<QString>> iter(AggroCheck.CombatAllValuesMap);
            while(iter.hasNext())
            {
                iter.next();
                QString NPCID = iter.key();

                if(NPCID != AggroCheck.CharSelectID_Main && NPCID.isEmpty() == false && !MainWindow::StopMovementVector.contains(NPCID))
                {
                    FacingDirection New_Movement1; //get class

                    QString MOB_Master_c9 = objectpacket::Master_Map.value(NPCID.toUtf8().toUpper());
                    QString MobX = MOB_Master_c9.mid(12,6);
                    QString MobZ = MOB_Master_c9.mid(18,6);
                    QString MobY = MOB_Master_c9.mid(24,6);
                    QString MobFacing = MOB_Master_c9.mid(30,2);
                    QString MobHP_OldVal2 = MOB_Master_c9.mid(54,2);//HP2

                    qDebug() << "";

                    QString Name = checkthezone::NPCsNames.value(NPCID);
                    qDebug() << "NPCsName" << Name;
                    qDebug() << "MobX2" << MobX;
                    qDebug() << "MobZ2" << MobZ;
                    qDebug() << "MobY2" << MobY;
                    qDebug() << "MobFacing" << MobFacing;
                    qDebug() << "MobC9HP" << MobHP_OldVal2;

                    if(MobHP_OldVal2 != "00")
                    {
                        packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT,AggroCheck);

                        QString xorC9 = New_Movement1.AGGRO_Radius_Movement
                                (AggroCheck.ClientsID,AggroCheck.ClientsIP,AggroCheck.ClientsPort,
                                 AggroCheck.masterx, AggroCheck.masterz, AggroCheck.mastery,
                                 NPCID,MobX, MobZ, MobY);

                        AggroCheck = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT);


                        if(xorC9.isEmpty() == false)
                        {
                            QByteArray Channel = xorC9.mid(0,2).toUtf8();

                            qDebug() << "Channel" << Channel;

                            QVector <QByteArray> CurrenChannelVector = AggroCheck.MapOfChannelVectors.value(Channel);

                            qDebug() << "CurrenChannelVector.size() = " << CurrenChannelVector.size();
                            qDebug() << "CurrenChannelVector" << CurrenChannelVector;

                            CurrenChannelVector.append(xorC9.toUtf8());
                            AggroCheck.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

                            packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT,AggroCheck);

                            flipped sento;
                            sento.SendOut(AggroCheck.ClientsID, AggroCheck.ClientsIP, AggroCheck.ClientsPort);

                            AggroCheck = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT);
                        }
                    }

                     qDebug() << "";
                }
            }
        }
    }
}



void MainWindow::world_servercall() //testing parsing when we want to (on a timer) instead of when we get a packet
{
    if(world_networklist.isEmpty() == false) //incoming data
    {
        QByteArray ClientsIP = world_networklist.at(0); //ip
        QByteArray ClientsPort = world_networklist.at(1); //port
        QByteArray ClientsPacket = world_networklist.at(2).toUpper(); //read data
        world_networklist.remove(0,3); //remove the one u just read like a stack

        if(world_networklist.size() > 0)
        {
            ui->lineEdit_14->setText(QString::number(world_networklist.size()/3));
        }
        else
        {
            ui->lineEdit_14->setText("0");
        }

        QByteArray ClientID = ClientsPacket.mid(0,4).toUpper();

        QByteArray clientffcall = ClientsPacket.mid(0,8).toUpper();

        if(ClientID != "FFFF" && ClientsPacket.size() > 22)
        {

            // //////////////Adding the port to the key///////////////////////////////////////////
            if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + ClientsIP))
            {
                //adding port to key
                //if the key doesnt contain the port
                packetparsing::packetvars pSWAP;

                pSWAP = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP);

                pSWAP.clientid1 = ClientsPacket.mid(0,4);
                pSWAP.serverid1 = ClientsPacket.mid(4,4);

                qDebug() << "";
                qDebug() << "pSWAP.SessionID = " << pSWAP.SessionID;
                qDebug() << "pSWAP.PreCharSelect = " << pSWAP.PreCharSelect;
                qDebug() << "pSWAP.CharSelectID = " << pSWAP.CharSelectID;
                qDebug() << "";

                pSWAP.ClientsID = ClientID;
                pSWAP.ClientsIP = ClientsIP;
                pSWAP.ClientsPort = ClientsPort;

                packetparsing::IPandPort_AllvariablesMap.remove(ClientID + ClientsIP);
                packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,pSWAP);
            }

            packetparsing::packetvars IN_MainWindow;
            IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);


            if(IN_MainWindow.Disconnected == false)
            {
                /////////////////restructuring client packet///////////////////////////////////////////

                if(IN_MainWindow.flipped == true)// one you had
                {
                    QByteArray fninehalfid0 = ClientsPacket.mid(12,6);
                    QByteArray fninehalfid1 = ClientsPacket.mid(20,6);
                    QByteArray fninehalfid2 = ClientsPacket.mid(12,8);

                    if(fninehalfid1 == IN_MainWindow.SessionID && fninehalfid2 != "BF543213"  && IN_MainWindow.Server_2A00_reply == true)
                    {
                        ClientsPacket.insert(12,"BF543213");
                    }

                    if(fninehalfid0 == IN_MainWindow.SessionID)
                    {
                        ClientsPacket.insert(12,"BF543213");
                    }
                }

                if(IN_MainWindow.flipped == false)// had to add this one
                {
                    QByteArray fninehalfid0 = ClientsPacket.mid(12,6);
                    QByteArray fninehalfid1 = ClientsPacket.mid(20,6);


                    if(fninehalfid0 == IN_MainWindow.SessionID && IN_MainWindow.Server_2A00_reply == false)
                    {
                        ClientsPacket.insert(12,"F1463213");
                    }

                    if(fninehalfid0 == IN_MainWindow.SessionID && IN_MainWindow.Server_2A00_reply == true)
                    {
                        ClientsPacket.insert(12,"BF543213");
                    }

                    QByteArray fninehalfid2 = ClientsPacket.mid(12,8);

                    if(fninehalfid1 == IN_MainWindow.SessionID && fninehalfid2 != "F1463213" && IN_MainWindow.Server_2A00_reply == false)
                    {
                        ClientsPacket.insert(12,"F1463213");
                    }

                    if(fninehalfid1 == IN_MainWindow.SessionID && fninehalfid2 != "BF543213" && IN_MainWindow.Server_2A00_reply == true)
                    {
                        ClientsPacket.insert(12,"BF543213");
                    }
                }



                ///////////////////Packet parsing///////////////////////////////////////////////
                packetparsing sendto;

                qDebug() << "IN_MainWindow.CurrentQuestMenuID_5" << IN_MainWindow.CurrentQuestMenuID;
                packetparsing::IPandPort_AllvariablesMap = sendto.ParseThePacket(ClientID,  ClientsIP,  ClientsPort,  ClientsPacket, packetparsing::IPandPort_AllvariablesMap);
                IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);
                qDebug() << "IN_MainWindow.CurrentQuestMenuID_20" << IN_MainWindow.CurrentQuestMenuID;

                ///////////////////Packet parsing///////////////////////////////////////////////

                if(IN_MainWindow.opcoderesult1 == "6007")
                {
                    IN_MainWindow.opcoderesult1 = "";

                    int tabWidgetIndex1 = ui->tabWidget->currentIndex();
                    int tabWidgetIndex2 = ui->tabWidget_2->currentIndex();
                    int tabWidgetIndex3 = ui->tabWidget_3->currentIndex();

                    ui->lineEdit_207->setText(IN_MainWindow.Target_ID);

                    ui->tabWidget->setCurrentIndex(4);
                    ui->tabWidget_2->setCurrentIndex(0);
                    ui->tabWidget_3->setCurrentIndex(4);

                    QString World_OldVal1 = "";

                    if(IN_MainWindow.Target_ID == IN_MainWindow.CharSelectID_Main)
                    {
                        ui->checkBox_5->setChecked(true);
                        IN_MainWindow.current_c9 = generator::Players_Map.value(IN_MainWindow.CharSelectID.toUtf8());
                        ui->lineEdit_130->setText(IN_MainWindow.Target_ID);
                        QString PacketNumber = Opcodes::ID_PacketNumber_Map.value(IN_MainWindow.CharSelectID);
                        ui->lineEdit_72->setText(PacketNumber);
                        int PacketNumber2 = PacketNumber.toInt(nullptr,10);
                        packetid = PacketNumber2;
                        QString chosenworld = QString("%1").arg(IN_MainWindow.masterworld,2,16,QLatin1Char('0')).toUpper(); //get the world
                        World_OldVal1 = chosenworld;
                    }

                    else
                    {
                        ui->checkBox_5->setChecked(false);
                        ui->checkBox_7->setChecked(true);
                        IN_MainWindow.current_c9 = objectpacket::Master_Map.value(IN_MainWindow.Target_ID);
                        ui->lineEdit_130->setText(IN_MainWindow.Target_ID);
                        QString PacketNumber = Opcodes::ID_PacketNumber_Map.value(IN_MainWindow.Target_ID);

                        if(reSpawnIDsMap.contains(IN_MainWindow.Target_ID))
                        {
                            QString ID = reSpawnIDsMap.value(IN_MainWindow.Target_ID);
                            PacketNumber = Opcodes::ID_PacketNumber_Map.value(ID);
                        }

                        ui->lineEdit_72->setText(PacketNumber);
                        int PacketNumber2 = PacketNumber.toInt(nullptr,10);
                        packetid = PacketNumber2;
                        World_OldVal1 = IN_MainWindow.current_c9.mid(34,2);
                    }

                    QString ModelID_OldVal1 = IN_MainWindow.current_c9.mid(56,8);



                    if(Race_AND_Gender.contains(ModelID_OldVal1))
                    {
                        ui->lineEdit_8->setText(ModelID_OldVal1.toUpper());//ModelID
                    }
                    else
                    {
                        SliderUsed = "NO";
                        ui->Mob_Models_3->setText(ModelID_OldVal1.toUpper());
                    }


                    QString X_OldVal1 = IN_MainWindow.current_c9.mid(12,6);
                    QString Z_OldVal1 = IN_MainWindow.current_c9.mid(18,6);
                    QString Y_OldVal1 = IN_MainWindow.current_c9.mid(24,6);
                    QString Facing_OldVal1 = IN_MainWindow.current_c9.mid(30,2);

                    QString HP_OldVal1 = IN_MainWindow.current_c9.mid(52,2);

                    QString Size_OldVal1 = IN_MainWindow.current_c9.mid(76,4);
                    QString Primary_OldVal1 = IN_MainWindow.current_c9.mid(134,8);
                    QString Secondary_OldVal1 = IN_MainWindow.current_c9.mid(142,8);
                    QString Shield_OldVal1 = IN_MainWindow.current_c9.mid(150,8);
                    IN_MainWindow.AtackType = IN_MainWindow.current_c9.mid(182,4);
                    QString Torso_OldVal1 = IN_MainWindow.current_c9.mid(186,2);
                    QString Forearms_OldVal1 = IN_MainWindow.current_c9.mid(188,2);
                    QString Gloves_OldVal1 = IN_MainWindow.current_c9.mid(190,2);
                    QString Legs_OldVal1 = IN_MainWindow.current_c9.mid(192,2);
                    QString Feet_OldVal1 = IN_MainWindow.current_c9.mid(194,2);
                    QString Head_OldVal1 = IN_MainWindow.current_c9.mid(196,2);
                    QString TorsoC_OldVal1 = IN_MainWindow.current_c9.mid(222,8);
                    QString ForearmsC_OldVal1 = IN_MainWindow.current_c9.mid(232,8);
                    QString GlovesC_OldVal1 = IN_MainWindow.current_c9.mid(242,8);
                    QString LegsC_OldVal1 = IN_MainWindow.current_c9.mid(252,8);
                    QString FeetC_OldVal1 = IN_MainWindow.current_c9.mid(262,8);
                    QString HeadC_OldVal1 = IN_MainWindow.current_c9.mid(272,8);
                    QString RobeC_OldVal1 = IN_MainWindow.current_c9.mid(282,8);
                    QString HairColor_OldVal1 = IN_MainWindow.current_c9.mid(290,2);//hair color
                    QString HairLength_OldVal1 = IN_MainWindow.current_c9.mid(292,2);//hair length
                    QString HairStyle_OldVal1 = IN_MainWindow.current_c9.mid(294,2);//hair style
                    QString Face_OldVal1 = IN_MainWindow.current_c9.mid(296,2);//face
                    QString RobeType_OldVal1 = IN_MainWindow.current_c9.mid(298,2);//robe type
                    QString Race_OldVal1 = IN_MainWindow.current_c9.mid(300,2);//race
                    QString Name24Hex_OldVal1 = IN_MainWindow.current_c9.mid(310,48);//name
                    QString Level_OldVal1 = IN_MainWindow.current_c9.mid(358,2);//level
                    QString Class_OldVal1 = IN_MainWindow.current_c9.mid(368,2);//class
                    QString NPC_Type_OldVal1 = IN_MainWindow.current_c9.mid(370,4);//npc type
                    QString Unk1 = IN_MainWindow.current_c9.mid(382,2);
                    QString Unk2 = IN_MainWindow.current_c9.mid(384,2);
                    QString Unk3 = IN_MainWindow.current_c9.mid(386,2);
                    QString Unk4 = IN_MainWindow.current_c9.mid(388,2);
                    QString Unk5 = IN_MainWindow.current_c9.mid(390,2);
                    QString Unk6 = IN_MainWindow.current_c9.mid(392,2);

                    ui->lineEdit_95->setText(Unk1.toUpper());
                    ui->lineEdit_96->setText(Unk2.toUpper());
                    ui->lineEdit_97->setText(Unk3.toUpper());
                    ui->lineEdit_98->setText(Unk4.toUpper());
                    ui->lineEdit_99->setText(Unk5.toUpper());
                    ui->lineEdit_100->setText(Unk6.toUpper());

                    ui->lineEdit_39->setText(Torso_OldVal1.toUpper());//torso
                    ui->lineEdit_43->setText(Forearms_OldVal1.toUpper());//forearms
                    ui->lineEdit_48->setText(Gloves_OldVal1.toUpper());//gloves
                    ui->lineEdit_27->setText(Legs_OldVal1.toUpper());//legs
                    ui->lineEdit_49->setText(Feet_OldVal1.toUpper());//feet
                    ui->lineEdit_47->setText(Head_OldVal1.toUpper());//head
                    ui->lineEdit_124->setText(RobeType_OldVal1.toUpper());//RobeType

                    ui->lineEdit_7->setText(Torso_OldVal1.toUpper());//torso
                    ui->lineEdit_36->setText(Forearms_OldVal1.toUpper());//forearms
                    ui->lineEdit_38->setText(Gloves_OldVal1.toUpper());//gloves
                    ui->lineEdit_46->setText(Legs_OldVal1.toUpper());//legs
                    ui->lineEdit_40->setText(Feet_OldVal1.toUpper());//feet
                    ui->lineEdit_42->setText(Head_OldVal1.toUpper());//head
                    ui->lineEdit_44->setText(RobeType_OldVal1.toUpper());//RobeType

                    ui->X_4->setText(X_OldVal1.toUpper());//x
                    ui->Z_4->setText(Z_OldVal1.toUpper());//z
                    ui->Y_4->setText(Y_OldVal1.toUpper());//y
                    ui->lineEdit_45->setText(X_OldVal1.toUpper());//x
                    ui->lineEdit_53->setText(Z_OldVal1.toUpper());//z
                    ui->lineEdit_74->setText(Y_OldVal1.toUpper());//y

                    ui->lineEdit_133->setText(Facing_OldVal1.toUpper());//facing
                    ui->lineEdit_50->setText(Facing_OldVal1.toUpper());//facing

                    ui->lineEdit_90->setText(Race_OldVal1.toUpper());//race
                    ui->lineEdit_130->setText(IN_MainWindow.Target_ID.toUpper());//ObjectID

                    ui->lineEdit_34->setText(TorsoC_OldVal1.toUpper());//torsoC
                    ui->lineEdit_28->setText(ForearmsC_OldVal1.toUpper());//forearmC
                    ui->lineEdit_52->setText(GlovesC_OldVal1.toUpper());//GlovesC
                    ui->lineEdit_76->setText(LegsC_OldVal1.toUpper());//LegsC
                    ui->lineEdit_32->setText(FeetC_OldVal1.toUpper());//FeetC
                    ui->lineEdit_41->setText(HeadC_OldVal1.toUpper());//HeadC
                    ui->lineEdit_33->setText(RobeC_OldVal1.toUpper());//RobeC

                    ui->lineEdit_68->setText(TorsoC_OldVal1.toUpper());//torsoC
                    ui->lineEdit_75->setText(ForearmsC_OldVal1.toUpper());//forearmC
                    ui->lineEdit_81->setText(GlovesC_OldVal1.toUpper());//GlovesC
                    ui->lineEdit_78->setText(LegsC_OldVal1.toUpper());//LegsC
                    ui->lineEdit_67->setText(FeetC_OldVal1.toUpper());//FeetC
                    ui->lineEdit_77->setText(HeadC_OldVal1.toUpper());//HeadC
                    ui->lineEdit_82->setText(RobeC_OldVal1.toUpper());//RobeC

                    ui->lineEdit_125->setText(Face_OldVal1.toUpper());//face
                    ui->lineEdit_126->setText(HairStyle_OldVal1.toUpper());//hairStyle
                    ui->lineEdit_127->setText(HairLength_OldVal1.toUpper());//HairLength
                    ui->lineEdit_128->setText(HairColor_OldVal1.toUpper());//HairColor

                    ui->lineEdit_122->setText(Class_OldVal1.toUpper());//Class
                    ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name
                    ui->lineEdit_66->setText(HP_OldVal1.toUpper());//hp

                    ui->lineEdit_79->setText(Level_OldVal1.toUpper());//Level
                    ui->lineEdit_37->setText(Size_OldVal1.toUpper());//Size
                    ui->lineEdit_26->setText(Level_OldVal1.toUpper());//Level
                    ui->lineEdit_24->setText(Size_OldVal1.toUpper());//Size

                    ui->lineEdit_73->setText(NPC_Type_OldVal1.toUpper());//NPC_Type
                    ui->lineEdit_54->setText(ModelID_OldVal1.toUpper());//ModelID

                    ui->lineEdit_62->setText(Primary_OldVal1.toUpper());//Primary
                    ui->lineEdit_63->setText(Secondary_OldVal1.toUpper());//Secondary
                    ui->lineEdit_64->setText(Shield_OldVal1.toUpper());//Shield

                    ui->lineEdit_324->setText(Primary_OldVal1.toUpper());//Primary
                    ui->lineEdit_325->setText(Secondary_OldVal1.toUpper());//Secondary
                    ui->lineEdit_326->setText(Shield_OldVal1.toUpper());//Shield

                    int ZoneNumber = checkthezone::IDandZoneNumber.value(IN_MainWindow.Target_ID);
                    ui->lineEdit_72->setText(QString::number(ZoneNumber));

                    ui->lineEdit_71->setText(World_OldVal1.toUpper());//World
                    ui->lineEdit_65->setText(World_OldVal1.toUpper());//World
                    int Face_OldVal2 = Face_OldVal1.toInt(nullptr,10);
                    ui->horizontalSlider->setValue(Face_OldVal2);//face
                    int HairStyle_OldVal2 = HairStyle_OldVal1.toInt(nullptr,10);
                    ui->horizontalSlider_2->setValue(HairStyle_OldVal2);//hairStyle
                    int HairLength_OldVal2 = HairLength_OldVal1.toInt(nullptr,10);
                    ui->horizontalSlider_3->setValue(HairLength_OldVal2);//HairLength
                    int HairColor_OldVal2 = HairColor_OldVal1.toInt(nullptr,10);
                    ui->horizontalSlider_4->setValue(HairColor_OldVal2);//HairColor


                    ui->tabWidget->setCurrentIndex(tabWidgetIndex1);
                    ui->tabWidget_2->setCurrentIndex(tabWidgetIndex2);
                    ui->tabWidget_3->setCurrentIndex(tabWidgetIndex3);


                    packetparsing::IPandPort_AllvariablesMap.insert(IN_MainWindow.ClientsID + IN_MainWindow.ClientsIP + IN_MainWindow.ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(IN_MainWindow.ClientsID + IN_MainWindow.ClientsIP + IN_MainWindow.ClientsPort);
                }

                if(IN_MainWindow.MobRespawnTimer == "20000")
                {
                    int time = IN_MainWindow.MobRespawnTimer.toInt(nullptr,10);
                    IN_MainWindow.MobRespawnTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *SpawningTimers  = new QTimer(this);
                    SpawningTimers->setInterval(time);
                    SpawningTimers->setSingleShot(true);
                    SpawningTimers->setObjectName(IN_MainWindow.Target_ID);
                    MainWindow::SpawningTimersVector.append(SpawningTimers);
                    SpawningTimers->start();

                    connect(SpawningTimers ,SIGNAL (timeout()),this,SLOT(on_DespawnMob()));
                }





                if(IN_MainWindow.MobDamageTimer.mid(0,3) == "880")
                {
                    QString ObjectID = IN_MainWindow.MobDamageTimer.mid(3,8);
                    int time = IN_MainWindow.MobDamageTimer.mid(0,3).toInt(nullptr,10);
                    IN_MainWindow.MobDamageTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *SwingTimers  = new QTimer(this);
                    SwingTimers->setInterval(time);
                    SwingTimers->setSingleShot(true);
                    SwingTimers->setObjectName(ObjectID + ClientID + ClientsIP + ClientsPort);
                    MobSwingTimersVector.append(SwingTimers);
                    SwingTimers->start();

                    connect(SwingTimers, SIGNAL(timeout()), this, SLOT(Mob_DMG_Sent()));
                }


                if(IN_MainWindow.MyDamageTimer == "250")
                {
                    int time = IN_MainWindow.MyDamageTimer.toInt(nullptr,10);
                    IN_MainWindow.MyDamageTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *PauseTimers  = new QTimer(this);
                    PauseTimers->setInterval(time);
                    PauseTimers->setSingleShot(true);
                    PauseTimers->setObjectName(ClientID + ClientsIP + ClientsPort);
                    MySwingTimersVector.append(PauseTimers);
                    PauseTimers->start();

                    connect(PauseTimers, SIGNAL(timeout()), this, SLOT(My_DMG_Sent()));
                }



                if(IN_MainWindow.Resend42ecTimer == "400")
                {
                    int time = IN_MainWindow.Resend42ecTimer.toInt(nullptr,10);
                    IN_MainWindow.Resend42ecTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *Send42ecTimers  = new QTimer(this);
                    Send42ecTimers->setInterval(time);
                    Send42ecTimers->setSingleShot(true);
                    Send42ecTimers->setObjectName(ClientID + ClientsIP + ClientsPort);
                    reSendFBsTimersVector.append(Send42ecTimers);
                    Send42ecTimers->start();

                    connect(Send42ecTimers, SIGNAL(timeout()), this, SLOT(ResendingFBs()));
                }



                if(IN_MainWindow.ResendChannelsTimer == "400")
                {
                    int time = IN_MainWindow.ResendChannelsTimer.toInt(nullptr,10);
                    IN_MainWindow.ResendChannelsTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *SendChannelsTimers  = new QTimer(this);
                    SendChannelsTimers->setInterval(time);
                    SendChannelsTimers->setSingleShot(true);
                    SendChannelsTimers->setObjectName(ClientID + ClientsIP + ClientsPort);
                    reSendChannelsTimersVector.append(SendChannelsTimers);
                    SendChannelsTimers->start();

                    connect(SendChannelsTimers, SIGNAL(timeout()), this, SLOT(ResendingChannels()));
                }


                if(IN_MainWindow.ResendFBsTimer == "400x" || IN_MainWindow.ResendAllFBs == true)
                {
                    int time = IN_MainWindow.ResendFBsTimer.toInt(nullptr,10);
                    IN_MainWindow.ResendFBsTimer = "";

                    if(IN_MainWindow.ResendAllFBs == true)
                    {
                        time = 10;
                    }

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *SendFBTimers  = new QTimer(this);
                    SendFBTimers->setInterval(time);
                    SendFBTimers->setSingleShot(true);
                    SendFBTimers->setObjectName(ClientID + ClientsIP + ClientsPort);
                    reSendFBsTimersVector.append(SendFBTimers);
                    SendFBTimers->start();

                    connect(SendFBTimers, SIGNAL(timeout()), this, SLOT(ResendingFBs()));
                }



                if(IN_MainWindow.GroupTimer == "500")
                {
                    int time = IN_MainWindow.GroupTimer.toInt(nullptr,10);
                    IN_MainWindow.GroupTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *GroupTimers  = new QTimer(this);
                    GroupTimers->setInterval(time);
                    GroupTimers->setSingleShot(true);
                    GroupTimers->setObjectName(IN_MainWindow.ClientsID + IN_MainWindow.ClientsIP + IN_MainWindow.ClientsPort);
                    GroupTimersVector.append(GroupTimers);
                    GroupTimers->start();

                    connect(GroupTimers ,SIGNAL (timeout()),this,SLOT(Group_Timer()));
                }





                if(IN_MainWindow.CoachTimer == "1000")
                {
                    int time = IN_MainWindow.CoachTimer.toInt(nullptr,10);
                    IN_MainWindow.CoachTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);


                    QTimer *CoachTimers  = new QTimer(this);
                    CoachTimers->setInterval(time);
                    CoachTimers->setSingleShot(true);
                    CoachTimers->setObjectName(IN_MainWindow.ClientsID+IN_MainWindow.ClientsIP+IN_MainWindow.ClientsPort);
                    CoachTimersVector.append(CoachTimers);
                    CoachTimers->start();

                    connect(CoachTimers ,SIGNAL (timeout()),this,SLOT(coachingoff()));
                }

                if(IN_MainWindow.TeleportTimer == "50")
                {
                    int time = IN_MainWindow.TeleportTimer.toInt(nullptr,10);
                    IN_MainWindow.TeleportTimer = "";

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *TeleportTimers  = new QTimer(this);
                    TeleportTimers->setInterval(time);
                    TeleportTimers->setSingleShot(true);
                    TeleportTimers->setObjectName(IN_MainWindow.ClientsID+IN_MainWindow.ClientsIP+IN_MainWindow.ClientsPort);
                    TeleportTimersVector.append(TeleportTimers);
                    TeleportTimers->start();

                    connect(TeleportTimers ,SIGNAL (timeout()),this,SLOT(teleportoff()));
                }




                if(IN_MainWindow.FC02D007 == false && IN_MainWindow.flipped == true)
                {
                    IN_MainWindow.FC02D007 = true;

                    packetparsing::IPandPort_AllvariablesMap.insert(ClientID + ClientsIP + ClientsPort,IN_MainWindow);
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

                    QTimer *F901Timers  = new QTimer(this);
                    F901Timers->setInterval(3500);
                    F901Timers->setSingleShot(true);
                    F901Timers->setObjectName(ClientID+ClientsIP+ClientsPort);
                    StandingStillTimersVector.append(F901Timers);
                    F901Timers->start();

                    connect(F901Timers ,SIGNAL (timeout()),this,SLOT(on_StandingStill()));

                }



                if(MastersClientsID.isEmpty() == true)
                {
                    MastersClientsID = IN_MainWindow.ClientsID;
                    MastersClientsIP = IN_MainWindow.ClientsIP;
                    MastersClientsPort = IN_MainWindow.ClientsPort;
                    MastersClientsObjectID = IN_MainWindow.CharSelectID.toUtf8();
                }
            }
        }
        else
        {
            if(clientffcall == "FFFF9209") //FFFF reply
            {
                QByteArray ffsendpacket = packetffff;
                QByteArray clientvalue1 = ClientsPacket.mid(8,4); //get the count from the client
                ffsendpacket.replace(8,4,clientvalue1);
                QByteArray ffffmessage = ffsendpacket.fromHex(ffsendpacket);

                QHostAddress current_client_address;
                current_client_address.setAddress(QString::fromUtf8(ClientsIP));
                quint16 current_client_port = ClientsPort.toUShort(nullptr,10);
                QString changeIP = current_client_address.toString();



                QByteArray ClientID = ClientsPacket.mid(0,4);
                packetparsing::packetvars IN_MainWindow;

                if(packetparsing::IPandPort_AllvariablesMap.contains(ClientID + ClientsIP + ClientsPort))
                {
                    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);
                }

                QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);



                QDateTime dateTime = dateTime.currentDateTime();
                QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

                qDebug() << "";
                qDebug() << "";
                qDebug() << "----------------------------------------------------------";
                qDebug() << dateTimeString;
                qDebug() << "FFFF_reply: " + ClientsPacket;
                qDebug() << "To Client: " + MainToon;
                qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
                qDebug() << "IP: " + ClientsIP;
                qDebug() << "Port: " + ClientsPort;
                qDebug() << "From Server: ";
                qDebug() << ffsendpacket;
                qDebug() << "----------------------------------------------------------";
                qDebug() << "";

                emit outgoingdata_game2(ffffmessage,changeIP,current_client_port);
            }
        }
    }
}



void MainWindow::on_pushButton_4_clicked() //TELEPORT send out packet here
{
    packetparsing::packetvars IN_TELEPORT;
    IN_TELEPORT = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    FacingDirection::Now_Roaming = "NO";
    spellunmemorize(); //clearing all active spells before port...they wont ungrey after for some reason
    //qDebug() << "teleport_destination.count()" << teleport_destination.count();
    if(IN_TELEPORT.teleport_destination.count() != 0)
    {
        ui->treeView->setDisabled(true); //grey it out til we arrive
        QByteArray telepacket = IN_TELEPORT.teleport_destination;

        increment F607_End; //get class
        QByteArray endpacket_f607 = F607_End.count(IN_TELEPORT.mastertelinc); //end packet increment
        telepacket.replace(54,4,IN_TELEPORT.mastertelinc); //replace new count at 96 //!! trying to be one behind so it starts at 0000
        IN_TELEPORT.mastertelinc = endpacket_f607.toUpper();

        IN_TELEPORT.SendFBsVector.append(telepacket);
        IN_TELEPORT.FBReplyOrNotVector.append("00");
        IN_TELEPORT.FBPacketDescriptionVector.append("Teleporting, ");

        ui->pushButton_4->setEnabled(false);
        ui->textEdit->clear();
        ui->textEdit_3->clear();
        ui->textEdit_6->clear();

        ////////////////////////4 Byte to 3 Byte//////////////////////////////


        QByteArray Teleport_Code = IN_TELEPORT.teleport_destination;
        QByteArray Teleport_Code_X = Teleport_Code.mid(6,8);
        QByteArray Teleport_Code_Z = Teleport_Code.mid(14,8);
        QByteArray Teleport_Code_Y = Teleport_Code.mid(22,8);

        QByteArray numinput1 = Teleport_Code_X;
        qlonglong outnum1 = numinput1.toLongLong(nullptr,16);
        quint32 reversenum5 = ((outnum1 & 0xFF) << 24) | ((outnum1 & 0xFF00) << 8) | ((outnum1 >> 8) & 0xFF00) | (outnum1 >> 24);
        QString outhex5 = QString("%1").arg(reversenum5,8,16,QLatin1Char('0'));
        qlonglong outnum2 = outhex5.toLongLong(nullptr,16); //adding union code instead of punning
        union {
            qlonglong outnum2;
            float array6;
        } xresult = {outnum2};
        qlonglong smallhex1 = xresult.array6 * 128.0;

        //float array6  = *reinterpret_cast<float*>(&outnum2);
        // qlonglong smallhex1 = array6 * 128.0;

        QString outaxo2 = QString("%1").arg(smallhex1,6,16,QLatin1Char('0'));
        ui->lineEdit_14->setText(outaxo2.toUpper()); //3 byte X
        IN_TELEPORT.masterx = outaxo2.toUtf8().toUpper(); //send to radius code
        IN_TELEPORT.holdmasterx = outaxo2.toUtf8().toUpper();

        ///////////////////////////////X/////////////////////////////////


        QByteArray numinput3 = Teleport_Code_Z;
        qlonglong outnum5 = numinput3.toLongLong(nullptr,16);
        quint32 reversenum7 = ((outnum5 & 0xFF) << 24) | ((outnum5 & 0xFF00) << 8) | ((outnum5 >> 8) & 0xFF00) | (outnum5 >> 24);
        QString outhex7 = QString("%1").arg(reversenum7,8,16,QLatin1Char('0'));
        qlonglong outnum6 = outhex7.toLongLong(nullptr,16);

        union {
            qlonglong outnum6;
            float array8;
        } zresult = {outnum6};

        qlonglong smallhex3 = zresult.array8 * 128.0;
        // float array8  = *reinterpret_cast<float*>(&outnum6);
        //qlonglong smallhex3 = array8 * 128.0;
        QString outazo4 = QString("%1").arg(smallhex3,6,16,QLatin1Char('0'));


        if(smallhex3 < 0)
        {

            QByteArray neg1 = neg1.number(smallhex3,16).toUpper();
            QByteArray neg2 = neg1.mid(neg1.size() - 6,6);
            ui->lineEdit_16->setText(neg2.toUpper()); //3 byte Negative Z
            IN_TELEPORT.masterz = neg2.toUpper();
            IN_TELEPORT.holdmasterz = QString::fromUtf8(neg2.toUpper()); //save teleport z

        }
        else
        {
            outazo4 = QString("%1").arg(smallhex3,6,16,QLatin1Char('0'));
            ui->lineEdit_16->setText(outazo4.toUpper()); //3 byte Positive Z
            IN_TELEPORT.masterz = outazo4.toUtf8().toUpper();
            IN_TELEPORT.holdmasterz = outazo4.toUpper(); //save teleport z
        }

        /////////////////////////////////Z//////////////////////////////////




        QByteArray numinput2 = Teleport_Code_Y;
        qlonglong outnum3 = numinput2.toLongLong(nullptr,16);
        quint32 reversenum6 = ((outnum3 & 0xFF) << 24) | ((outnum3 & 0xFF00) << 8) | ((outnum3 >> 8) & 0xFF00) | (outnum3 >> 24);
        QString outhex6 = QString("%1").arg(reversenum6,8,16,QLatin1Char('0'));
        qlonglong outnum4 = outhex6.toLongLong(nullptr,16);

        union {
            qlonglong outnum4;
            float array7;
        } yresult = {outnum4};

        qlonglong smallhex2 = yresult.array7 * 128.0;
        //float array7  = *reinterpret_cast<float*>(&outnum4);
        // qlonglong smallhex2 = array7 * 128.0;
        QString outayo3 = QString("%1").arg(smallhex2,6,16,QLatin1Char('0'));
        ui->lineEdit_15->setText(outayo3.toUpper()); //3 byte Y
        IN_TELEPORT.mastery = outayo3.toUtf8().toUpper(); //send to radius code
        IN_TELEPORT.holdmastery = outayo3.toUtf8().toUpper();

        IN_TELEPORT.masterworld = IN_TELEPORT.tele_world.toInt(nullptr,16);

        packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_TELEPORT);

        checkthezone sendto;
        sendto.CheckTheZone(IN_TELEPORT.masterx,IN_TELEPORT.masterz,IN_TELEPORT.mastery);

        IN_TELEPORT = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);
        //qDebug() << "Teleport-X-" << holdmasterx;
        //qDebug() << "Teleport-Z-" << holdmasterz;
        //qDebug() << "Teleport-Y-" << holdmastery;
        ui->textEdit_5->append(QString("Teleport-X-%1-Z-%2-Y-%3").arg(IN_TELEPORT.holdmasterx).arg(IN_TELEPORT.holdmasterz).arg(IN_TELEPORT.holdmastery));
        //////////////////////////Y///////////4 Byte to 3 Byte///////////////////////////////////////////////////////

        QByteArray newc91 = generator::Players_Map.value(IN_TELEPORT.CharSelectID.toUtf8());
        newc91.replace(12,6,IN_TELEPORT.holdmasterx.toUtf8());
        newc91.replace(18,6,IN_TELEPORT.holdmasterz.toUtf8());
        newc91.replace(24,6,IN_TELEPORT.holdmastery.toUtf8());
        QString chosenworld2 = QString("%1").arg(IN_TELEPORT.masterworld,2,16,QLatin1Char('0')).toUpper();
        newc91.replace(34,2,chosenworld2.toUtf8());
        generator::Players_Map.insert(IN_TELEPORT.CharSelectID.toUtf8(),newc91); //replace the new coordinates in the map!!!

        /////////////////////////////9007/////////////////////////////////
        //ip
        QByteArray ourip1 = IN_TELEPORT.teleport_ip; //get current ip
        QByteArray first4 =  ourip1.mid(0,2); //reverse it
        QByteArray second4 = ourip1.mid(2,2);
        QByteArray third4 =  ourip1.mid(4,2);
        QByteArray fourth4 = ourip1.mid(6,2);

        QByteArray revip4 = fourth4 += third4 += second4 += first4;

        //9007 0A1F 57277000A8C00300000034173B1D6977621876B2640B
        //9007 0A1F 57277000A8C0030000005AE73B1D69776218AC401540
        increment packetcount4; //get class
        QByteArray newcount4 = packetcount4.count(IN_TELEPORT.C_9007_endcount); //end of packet count
        IN_TELEPORT.C_9007_endcount = newcount4.toUpper();

        QByteArray nineoseven = "9007" + IN_TELEPORT.serverid1 + "5727" + revip4 +
                IN_TELEPORT.C_9007_endcount + "0000" + IN_TELEPORT.clientid1 + "3b1d69776218";


        IN_TELEPORT.SendFBsVector.append(nineoseven);
        IN_TELEPORT.FBReplyOrNotVector.append("00");
        IN_TELEPORT.FBPacketDescriptionVector.append("C_9007, ");



        /////////////////////////Save Location///////////////////////////


        QSqlQuery querytlpt2;
        QString tablesel2 = "MAINTOON";
        QString objecttlpt2 = "ObjectID (4)";
        QString worldtlpt = "World (1)";
        QString xtlpt = "X (3)";
        QString ztlpt = "Z (3)";
        QString ytlpt = "Y (3)";
        QString facing1 = "Facing (1)";

        QString tlptid2 = IN_TELEPORT.CharSelectID;
        QString chosenworld = QString("%1").arg(IN_TELEPORT.masterworld,2,16,QLatin1Char('0')).toUpper();
        QString facing = IN_TELEPORT.masterf;
        QString x1 = QString::fromUtf8(IN_TELEPORT.masterx);
        QString z1 = QString::fromUtf8(IN_TELEPORT.masterz);
        QString y1 = QString::fromUtf8(IN_TELEPORT.mastery);



        if(chosenworld.isEmpty() == false && facing.isEmpty() == false && x1.isEmpty() == false &&
                z1.isEmpty() == false && y1.isEmpty() == false)
        {
            db.transaction();

            querytlpt2.prepare(QStringLiteral("UPDATE %1 SET [%2] = :val2,[%3] = :val3,[%4] = :val4,[%5] = :val5,[%6] = :val6 WHERE [%7] = :val").arg(tablesel2).arg(xtlpt).arg(ytlpt).arg(ztlpt).arg(worldtlpt).arg(facing1).arg(objecttlpt2));

            querytlpt2.bindValue(":val",tlptid2);
            querytlpt2.bindValue(":val2",x1.toUpper());
            querytlpt2.bindValue(":val3",y1.toUpper());
            querytlpt2.bindValue(":val4",z1.toUpper());
            querytlpt2.bindValue(":val5",chosenworld.toUpper());
            querytlpt2.bindValue(":val6",facing.toUpper());

            querytlpt2.exec();
            db.commit();
        }

        ///////////////////////////////////////////////////////////


        QByteArray HolderXorDespawn = "";

        QMapIterator<QString,QString> iter (IN_TELEPORT.Map_Channel_ID);
        while (iter.hasNext())
        {
            iter.next();
            QString Current_channel = iter.key();

            QString FreeORUsed = IN_TELEPORT.channelmap.value(Current_channel);

            if(FreeORUsed == "used")// no reason to xor if the channel is empty..
            {
                QByteArray holderXorC9 = "XXc9xxxx01100180c800";

                holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());

                //qDebug() << "MapOfChannelVectors4" << MapOfChannelVectors;

                QByteArray Channel = holderXorC9.mid(0,2);
                QVector <QByteArray> CurrenChannelVector = IN_TELEPORT.MapOfChannelVectors.value(Channel);
                CurrenChannelVector.append(holderXorC9);
                IN_TELEPORT.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

                //qDebug() << "MapOfChannelVectors4" << MapOfChannelVectors;
            }
        }





        if(IN_TELEPORT.LastTeleportWorld != IN_TELEPORT.masterworld)//only xor 00 channel if the last world is not where you are going
        {
            QByteArray holdergen2 = "00c9xxxx01100180c800";

            IN_TELEPORT.SendZeroChannelVector.append(holdergen2);

        }


        QMapIterator<QString,QString> iter2 (IN_TELEPORT.channelmap); //go thru map to get ids and ranges
        while (iter2.hasNext())
        {

            iter2.next();
            QString chkey1 = iter2.key();
            QString mapval1 = "free";
            IN_TELEPORT.channelmap.insert(chkey1,mapval1);

        }


        IN_TELEPORT.sent_ids_map.clear(); //clear sent ids
        IN_TELEPORT.keptlist1.clear(); //clear keptlist

        IN_TELEPORT.teleporting = true; //set teleport flag to true
        IN_TELEPORT.teleportmainswitch = true; //turn on fc02d007 sender


        if(IN_TELEPORT.Death == false)
        {
            IN_TELEPORT.FullHealth = true;
            ui->label_FullHealth->setText("FullHealth = True");
        }
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_TELEPORT);
}




QByteArray MainWindow::ConvertSession(QString SessionID1)
{
    //qDebug() << "";
    //qDebug() << "ObjectID to SessionID";
    //qDebug() << "SessionID1" << SessionID1;


    QString byte1 = SessionID1.mid(0,2);
    QString byte2 = SessionID1.mid(2,2);
    QString byte3 = SessionID1.mid(4,2);
    QString byte4 = SessionID1.mid(6,2);

    QString CharSelectID_rev = byte4 + byte3 + byte2 + byte1;

    QByteArray objectid = CharSelectID_rev.toUtf8();

    int object1;

    object1 = objectid.toInt(nullptr,16); //this needs to be input as reversed byte order ( dudderz 035e59)

    QByteArray test2;
    QByteArray test3;

    do
    {
        //qDebug() << "object1" << object1;

        uchar lower7bits = (uchar)(object1 & 0x7f);
        object1 >>= 7;

        if (object1 > 0)

            lower7bits |= 128;
        uchar add(lower7bits);
        test2.append(add);

        //qDebug() << "add" << add;
        //qDebug() << "Val" << test2.toHex().toUpper();
        //qDebug() << "lower7bits" << lower7bits;


        test3.append(lower7bits);


    } while (object1 > 0);

    //qDebug() << "test3" << test3.toHex().toUpper();

    ui->lineEdit_256->setText(test2.toHex().toUpper());

    //qDebug() << "SessionID2" << test2;

    return test2.toHex().toUpper();
}



void MainWindow::on_treeView_clicked(const QModelIndex &index) //get the selection
{
    packetparsing::packetvars IN_treeView;
    IN_treeView = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QStandardItem *item3 = standardModel->itemFromIndex(index); //get index of what was selected
    QString hiddentext = item3->data(Qt::UserRole+1).toString(); //get the hidden userrole data
    int hiddenworld = item3->data(Qt::UserRole+2).toInt();
    QString world = QString("%1").arg(hiddenworld,2,16,QLatin1Char('0')).toUpper(); //get the world
    IN_treeView.LastTeleportWorld = IN_treeView.masterworld;
    IN_treeView.masterworld = hiddenworld; //save it to use it later
    IN_treeView.teleport_destination = item3->data(Qt::UserRole+3).toByteArray();
    ui->textEdit->setText(hiddentext); //show destination
    ui->textEdit_3->setText(world); //show world
    ui->textEdit_6->setText(IN_treeView.teleport_destination); //show packet

    if(hiddentext.count() != 0 && IN_treeView.flipped == true)
    {
        ui->pushButton_4->setEnabled(true);
    }
    else
    {
        ui->pushButton_4->setEnabled(false);
        ui->textEdit->clear();
        ui->textEdit_3->clear();
        ui->textEdit_6->clear();
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_treeView);

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index != 2)
    {
        ui->pushButton_4->setEnabled(false);
        ui->textEdit->clear();
        ui->textEdit_3->clear();
        ui->textEdit_6->clear();
        ui->checkBox_14->setChecked(false);
    }


    if(index == 2) //if  teleport tab is selected
    {
        standardModel->clear(); //clear model if tab clicked on and off
        QStandardItem *rootNode = standardModel->invisibleRootItem();//Set Invisible Root Item again after clearing model
        ////////////////////TREE  & MODEL/////////////////////////////////
        treetop = new QStandardItem("Teleport"); //Set TreeView Header Text
        standardModel->setHorizontalHeaderItem(0,treetop);
        ui->treeView->setUniformRowHeights(true);
        ui->treeView->setModel(standardModel); //Hook View Into Model
        //////////////////////TREE & MODEL////////////////////////////////

        //////////////////Tunaria and subs//////////////////////////

        QString fin1 = "Tunaria";
        one = new QStandardItem(fin1);
        rootNode->appendRow(one);

        QString sub_tun1 = "One";
        two = new QStandardItem(sub_tun1);
        one->appendRow(two);


        QString sub1_1 = "Permafrost";
        three = new QStandardItem(sub1_1);
        three->setData(sub1_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Permafrost_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_1 = "Zentar's Keep";
        three = new QStandardItem(sub2_1);
        three->setData(sub2_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Zentars_Keep_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_1 = "Bogman Village";
        three = new QStandardItem(sub3_1);
        three->setData(sub3_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Bogman_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_1 = "Mariel Village";
        three = new QStandardItem(sub4_1);
        three->setData(sub4_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Mariel_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_1 = "Wyndhaven";
        three = new QStandardItem(sub5_1);
        three->setData(sub5_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Wyndhaven_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_1 = "Whale Hill";
        three = new QStandardItem(sub6_1);
        three->setData(sub6_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Whale_Hill_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_1 = "Qeynos";
        three = new QStandardItem(sub7_1);
        three->setData(sub7_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Qeynos_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_1 = "Qeynos Prison";
        three = new QStandardItem(sub8_1);
        three->setData(sub8_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Qeynos_Prison_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_1 = "Highbourne";
        three = new QStandardItem(sub9_1);
        three->setData(sub9_1,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Highbourne_tp,Qt::UserRole+3);
        two->appendRow(three);
        /////////////////////////////////////////////////Two/////////////////////////////
        QString sub_tun2 = "Two";
        two = new QStandardItem(sub_tun2);
        one->appendRow(two);

        QString sub1_2 = "SnowBlind Plains";
        three = new QStandardItem(sub1_2);
        three->setData(sub1_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Snowblind_Plains_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_2 = "Unkempt North";
        three = new QStandardItem(sub2_2);
        three->setData(sub2_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Unkempt_North_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_2 = "Unkempt Glade";
        three = new QStandardItem(sub3_2);
        three->setData(sub3_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Unkempt_Glade_tp,Qt::UserRole+3);
        two->appendRow(three);


        QString sub4_2 = "Twisted Tower";
        three = new QStandardItem(sub4_2);
        three->setData(sub4_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Twisted_Tower_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_2 = "Jethros Cast";
        three = new QStandardItem(sub5_2);
        three->setData(sub5_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Jethros_Cast_tp,Qt::UserRole+3);
        two->appendRow(three);


        QString sub6_2 = "Crethley Manor";
        three = new QStandardItem(sub6_2);
        three->setData(sub6_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Crethley_Manor_tp,Qt::UserRole+3);
        two->appendRow(three);


        QString sub7_2 = "Hagley1";
        three = new QStandardItem(sub7_2);
        three->setData(sub7_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Hagley1_tp,Qt::UserRole+3);
        two->appendRow(three);


        QString sub8_2 = "Hagley2";
        three = new QStandardItem(sub8_2);
        three->setData(sub8_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Hagley2_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_2 = "Druids Watch";
        three = new QStandardItem(sub9_2);
        three->setData(sub9_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Druids_Watch_tp,Qt::UserRole+3);
        two->appendRow(three);


        QString sub10_2 = "Stoneclaw";
        three = new QStandardItem(sub10_2);
        three->setData(sub10_2,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Stoneclaw_tp,Qt::UserRole+3);
        two->appendRow(three);

        ///////////////////////////////////////////Three/////////////////////////////

        QString sub_tun3 = "Three";
        two = new QStandardItem(sub_tun3);
        one->appendRow(two);

        QString sub1_3 = "Anu Village";
        three = new QStandardItem(sub1_3);
        three->setData(sub1_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Anu_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_3 = "North Wilderlands";
        three = new QStandardItem(sub2_3);
        three->setData(sub2_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::North_Wilderlands_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_3 = "Castle Lightwolf";
        three = new QStandardItem(sub3_3);
        three->setData(sub3_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Castle_Lightwolf_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_3 = "Salisearaneen";
        three = new QStandardItem(sub4_3);
        three->setData(sub4_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Salisearaneen_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_3 = "Murnf";
        three = new QStandardItem(sub5_3);
        three->setData(sub5_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Murnf_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_3 = "Surefall Glade";
        three = new QStandardItem(sub6_3);
        three->setData(sub6_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Surefall_Glade_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_3 = "Fog Marsh";
        three = new QStandardItem(sub7_3);
        three->setData(sub7_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Fog_Marsh_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_3 = "Honjour";
        three = new QStandardItem(sub8_3);
        three->setData(sub8_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Honjour_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_3 = "Bear Cave";
        three = new QStandardItem(sub9_3);
        three->setData(sub9_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Bear_Cave_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_3 = "Spider Mine";
        three = new QStandardItem(sub10_3);
        three->setData(sub10_3,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Spider_Mine_tp,Qt::UserRole+3);
        two->appendRow(three);


        ///////////////////////////Four///////////////////////////////

        QString sub_tun4 = "Four";
        two = new QStandardItem(sub_tun4);
        one->appendRow(two);

        QString sub1_4 = "Aviak Village";
        three = new QStandardItem(sub1_4);
        three->setData(sub1_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Aviak_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_4 = "Frosteye Vally";
        three = new QStandardItem(sub2_4);
        three->setData(sub2_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Frosteye_Vally_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_4 = "Guardian Forest";
        three = new QStandardItem(sub3_4);
        three->setData(sub3_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Guardian_Forest_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_4 = "Gramash Ruins";
        three = new QStandardItem(sub4_4);
        three->setData(sub4_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Gramash_Ruins_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_4 = "Spirit Talkers Wood";
        three = new QStandardItem(sub5_4);
        three->setData(sub5_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Spirit_Talkers_Wood_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_4 = "Spirit Talkers Wood2";
        three = new QStandardItem(sub6_4);
        three->setData(sub6_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Spirit_Talkers_Wood2_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_4 = "Wymondham";
        three = new QStandardItem(sub7_4);
        three->setData(sub7_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Wymondham_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_4 = "Al Karad Ruins";
        three = new QStandardItem(sub8_4);
        three->setData(sub8_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Al_Karad_Ruins_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_4 = "Blakedown";
        three = new QStandardItem(sub9_4);
        three->setData(sub9_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Blakedown_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_4 = "Mayfly Glade";
        three = new QStandardItem(sub10_4);
        three->setData(sub10_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Mayfly_Glade_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_4 = "Urglunts Wall";
        three = new QStandardItem(sub11_4);
        three->setData(sub11_4,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Urglunts_Wall_tp,Qt::UserRole+3);
        two->appendRow(three);


        ///////////////////////////Five/////////////////////////

        QString sub_tun5 = "Five";
        two = new QStandardItem(sub_tun5);
        one->appendRow(two);

        QString sub1_5 = "Halas";
        three = new QStandardItem(sub1_5);
        // three->setForeground(Qt::red);
        three->setData(sub1_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Halas_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_5 = "Freezeblood Village";
        three = new QStandardItem(sub2_5);
        three->setData(sub2_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Freezeblood_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_5 = "Diren Village";
        three = new QStandardItem(sub3_5);
        three->setData(sub3_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Diren_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_5 = "Mt Hatespike";
        three = new QStandardItem(sub4_5);
        three->setData(sub4_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Mt_Hatespike_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_5 = "Blackburrow";
        three = new QStandardItem(sub5_5);
        three->setData(sub5_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Blackburrow_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_5 = "Jareds Blight";
        three = new QStandardItem(sub6_5);
        three->setData(sub6_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Jareds_Blight_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_5 = "Darvar Manor";
        three = new QStandardItem(sub7_5);
        three->setData(sub7_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Darvar_Manor_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_5 = "Alseops Wall";
        three = new QStandardItem(sub8_5);
        three->setData(sub8_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Alseops_Wall_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_5 = "Forkwatch";
        three = new QStandardItem(sub9_5);
        three->setData(sub9_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Forkwatch_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_5 = "South Crossroads";
        three = new QStandardItem(sub10_5);
        three->setData(sub10_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::South_Crossroads_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_5 = "Dark Solace";
        three = new QStandardItem(sub11_5);
        three->setData(sub11_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Dark_Solace_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub12_5 = "Widows Peak";
        three = new QStandardItem(sub12_5);
        three->setData(sub12_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Widows_Peak_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub13_5 = "Kelinar";
        three = new QStandardItem(sub13_5);
        three->setData(sub13_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Kelinar_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub14_5 = "Gerntar Mines";
        three = new QStandardItem(sub14_5);
        three->setData(sub14_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Gerntar_Mines_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub15_5 = "Oggok Gate";
        three = new QStandardItem(sub15_5);
        three->setData(sub15_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Oggok_Gate_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub16_5 = "Milas Reef";
        three = new QStandardItem(sub16_5);
        three->setData(sub16_5,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Milas_Reef_tp,Qt::UserRole+3);
        two->appendRow(three);

        ///////////////////////////////Six///////////////////////////////

        QString sub_tun6 = "Six";
        two = new QStandardItem(sub_tun6);
        one->appendRow(two);

        QString sub1_6 = "Snowfist";
        three = new QStandardItem(sub1_6);
        three->setData(sub1_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Snowfist_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_6 = "Goldfeather Eyrie";
        three = new QStandardItem(sub2_6);
        three->setData(sub2_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Goldfeather_Eyrie_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_6 = "Moradhim";
        three = new QStandardItem(sub3_6);
        three->setData(sub3_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Moradhim_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_6 = "Baga Village";
        three = new QStandardItem(sub4_6);
        three->setData(sub4_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Baga_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_6 = "Merry by Water";
        three = new QStandardItem(sub5_6);
        three->setData(sub5_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Merry_by_Water_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_6 = "Bandit Hills";
        three = new QStandardItem(sub6_6);
        three->setData(sub6_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Bandit_Hills_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_6 = "Strags Rest";
        three = new QStandardItem(sub7_6);
        three->setData(sub7_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Strags_Rest_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_6 = "Salt Mine";
        three = new QStandardItem(sub8_6);
        three->setData(sub8_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Salt_Mine_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_6 = "Centaur Vally";
        three = new QStandardItem(sub9_6);
        three->setData(sub9_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Centaur_Vally_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_6 = "Brog Fens";
        three = new QStandardItem(sub10_6);
        three->setData(sub10_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Brog_Fens_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_6 = "Blackwater";
        three = new QStandardItem(sub11_6);
        three->setData(sub11_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Blackwater_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub12_6 = "Fort Alliance";
        three = new QStandardItem(sub12_6);
        three->setData(sub12_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Fort_Alliance_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub13_6 = "Elephant Graveyard";
        three = new QStandardItem(sub13_6);
        three->setData(sub13_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Elephant_Graveyard_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub14_6 = "Kerplunk";
        three = new QStandardItem(sub14_6);
        three->setData(sub14_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Kerplunk_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub15_6 = "Cazic Thule";
        three = new QStandardItem(sub15_6);
        three->setData(sub15_6,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Cazic_Thule_tp,Qt::UserRole+3);
        two->appendRow(three);


        //////////////////////////Seven///////////////////////////////////////

        QString sub_tun7 = "Seven";
        two = new QStandardItem(sub_tun7);
        one->appendRow(two);

        QString sub1_7 = "Greyvaxs Caves";
        three = new QStandardItem(sub1_7);
        three->setData(sub1_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Greyvaxs_Caves_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_7 = "Snafitzers House";
        three = new QStandardItem(sub2_7);
        three->setData(sub2_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Snafitzers_House_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_7 = "Shon To Monastery";
        three = new QStandardItem(sub3_7);
        three->setData(sub3_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Shon_To_Monastery_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_7 = "Misty Thicket";
        three = new QStandardItem(sub4_7);
        three->setData(sub4_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Misty_Thicket_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_7 = "Runnyeye";
        three = new QStandardItem(sub5_7);
        three->setData(sub5_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Runnyeye_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_7 = "Highpass";
        three = new QStandardItem(sub6_7);
        three->setData(sub6_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Highpass_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_7 = "Trails End";
        three = new QStandardItem(sub7_7);
        three->setData(sub7_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Trails_End_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_7 = "Dshinns Redoubt";
        three = new QStandardItem(sub8_7);
        three->setData(sub8_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Dshinns_Redoubt_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_7 = "Wktaans 4th Talon";
        three = new QStandardItem(sub9_7);
        three->setData(sub9_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Wktaans_4th_Talon_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_7 = "Serpent Hills";
        three = new QStandardItem(sub10_7);
        three->setData(sub10_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Serpent_Hills_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_7 = "Tak Xiz";
        three = new QStandardItem(sub11_7);
        three->setData(sub11_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Tak_Xiz_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub12_7 = "Tak Xiz South";
        three = new QStandardItem(sub12_7);
        three->setData(sub12_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Tak_Xiz_South_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub13_7 = "Lake Noregard";
        three = new QStandardItem(sub13_7);
        three->setData(sub13_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Lake_Noregard_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub14_7 = "Dinbak";
        three = new QStandardItem(sub14_7);
        three->setData(sub14_7,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Dinbak_tp,Qt::UserRole+3);
        two->appendRow(three);



        //////////////////////////////Eight////////////////////////////////////////

        QString sub_tun8 = "Eight";
        two = new QStandardItem(sub_tun8);
        one->appendRow(two);

        QString sub1_8 = "Fayspire Gate";
        three = new QStandardItem(sub1_8);
        three->setData(sub1_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Fayspire_Gate_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_8 = "Fayspires";
        three = new QStandardItem(sub2_8);
        three->setData(sub2_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Fayspires_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_8 = "Tethelin";
        three = new QStandardItem(sub3_8);
        three->setData(sub3_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Tethelin_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_8 = "Thedruk";
        three = new QStandardItem(sub4_8);
        three->setData(sub4_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Thedruk_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_8 = "Rivervale";
        three = new QStandardItem(sub5_8);
        three->setData(sub5_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Rivervale_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_8 = "Moss Mouth Cavern";
        three = new QStandardItem(sub6_8);
        three->setData(sub6_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Moss_Mouth_Cavern_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_8 = "Bastable Village";
        three = new QStandardItem(sub7_8);
        three->setData(sub7_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Bastable_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_8 = "Ferrans Hope";
        three = new QStandardItem(sub8_8);
        three->setData(sub8_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Ferrans_Hope_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_8 = "Deathfist Horde";
        three = new QStandardItem(sub9_8);
        three->setData(sub9_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Deathfist_Horde_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_8 = "Chiktar Hive";
        three = new QStandardItem(sub10_8);
        three->setData(sub10_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Chiktar_Hive_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_8 = "Tak Xiv";
        three = new QStandardItem(sub11_8);
        three->setData(sub11_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Tak_Xiv_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub12_8 = "Takish Hiz";
        three = new QStandardItem(sub12_8);
        three->setData(sub12_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Takish_Hiz_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub13_8 = "Burial Mounds";
        three = new QStandardItem(sub13_8);
        three->setData(sub13_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Burial_Mounds_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub14_8 = "Stone Watchers";
        three = new QStandardItem(sub14_8);
        three->setData(sub14_8,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Stone_Watchers_tp,Qt::UserRole+3);
        two->appendRow(three);


        ////////////////////////////////////Nine/////////////////////////////////////


        QString sub_tun9 = "Nine";
        two = new QStandardItem(sub_tun9);
        one->appendRow(two);

        QString sub1_9 = "NE Mountain Boundary";
        three = new QStandardItem(sub1_9);
        three->setData(sub1_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::NE_Mountain_Boundary_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_9 = "Kara Village";
        three = new QStandardItem(sub2_9);
        three->setData(sub2_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Kara_Village_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_9 = "Castle Felstar";
        three = new QStandardItem(sub3_9);
        three->setData(sub3_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Castle_Felstar_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_9 = "Fort Seriak";
        three = new QStandardItem(sub4_9);
        three->setData(sub4_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Fort_Seriak_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_9 = "North Kithicor";
        three = new QStandardItem(sub5_9);
        three->setData(sub5_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::North_Kithicor_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_9 = "Saerk Towers";
        three = new QStandardItem(sub6_9);
        three->setData(sub6_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Saerk_Towers_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_9 = "Tomb of Kings";
        three = new QStandardItem(sub7_9);
        three->setData(sub7_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Tomb_of_Kings_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_9 = "Deathfist Forge";
        three = new QStandardItem(sub8_9);
        three->setData(sub8_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Deathfist_Forge_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_9 = "Deathfist Citadel";
        three = new QStandardItem(sub9_9);
        three->setData(sub9_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Deathfist_Citadel_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_9 = "Box Canyons";
        three = new QStandardItem(sub10_9);
        three->setData(sub10_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Box_Canyons_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_9 = "Eternal Desert";
        three = new QStandardItem(sub11_9);
        three->setData(sub11_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Eternal_Desert_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub12_9 = "Oasis";
        three = new QStandardItem(sub12_9);
        three->setData(sub12_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Oasis_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub13_9 = "Sea of Lions";
        three = new QStandardItem(sub13_9);
        three->setData(sub13_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Sea_of_Lions_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub14_9 = "Ant Colonies";
        three = new QStandardItem(sub14_9);
        three->setData(sub14_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Ant_Colonies_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub15_9 = "Brokenskull Rock";
        three = new QStandardItem(sub15_9);
        three->setData(sub15_9,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Brokenskull_Rock_tp,Qt::UserRole+3);
        two->appendRow(three);

        ////////////////////////////////Ten//////////////////////////////////////


        QString sub_tun10 = "Ten";
        two = new QStandardItem(sub_tun10);
        one->appendRow(two);

        QString sub1_10 = "Klick Anon";
        three = new QStandardItem(sub1_10);
        three->setData(sub1_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Klick_Anon_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub2_10 = "Collonridge Cemetary";
        three = new QStandardItem(sub2_10);
        three->setData(sub2_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Collonridge_Cemetary_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_10 = "The Green Rift";
        three = new QStandardItem(sub3_10);
        three->setData(sub3_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::The_Green_Rift_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_10 = "Mu Lins Reach";
        three = new QStandardItem(sub4_10);
        three->setData(sub4_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Mu_Lins_Reach_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_10 = "Temple of Light";
        three = new QStandardItem(sub5_10);
        three->setData(sub5_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Temple_of_Light_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_10 = "Northwestern Ro";
        three = new QStandardItem(sub6_10);
        three->setData(sub6_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Northwestern_Ro_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_10 = "Muniels Tea Garden";
        three = new QStandardItem(sub7_10);
        three->setData(sub7_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Muniels_Tea_Garden_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_10 = "Al Farak Ruins";
        three = new QStandardItem(sub8_10);
        three->setData(sub8_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Al_Farak_Ruins_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_10 = "Sycamore Joys Rest";
        three = new QStandardItem(sub9_10);
        three->setData(sub9_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Sycamore_Joys_Rest_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_10 = "Great Waste";
        three = new QStandardItem(sub10_10);
        three->setData(sub10_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Great_Waste_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_10 = "Silthtar Hive";
        three = new QStandardItem(sub11_10);
        three->setData(sub11_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Silthtar_Hive_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub12_10 = "Sslathis";
        three = new QStandardItem(sub12_10);
        three->setData(sub12_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Sslathis_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub13_10 = "Bashers Enclave";
        three = new QStandardItem(sub13_10);
        three->setData(sub13_10,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Bashers_Enclave_tp,Qt::UserRole+3);
        two->appendRow(three);

        /////////////////////////////////Eleven////////////////////////////////

        QString sub_tun11 = "Eleven";
        two = new QStandardItem(sub_tun11);
        one->appendRow(two);



        QString sub2_11 = "Rogue Clockworks";
        three = new QStandardItem(sub2_11);
        three->setData(sub2_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Rogue_Clockworks_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub3_11 = "Neriak";
        three = new QStandardItem(sub3_11);
        three->setData(sub3_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Neriak_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub4_11 = "Bobble by Water";
        three = new QStandardItem(sub4_11);
        three->setData(sub4_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Bobble_by_Water_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub5_11 = "Hodstock and Temby";
        three = new QStandardItem(sub5_11);
        three->setData(sub5_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Hodstock_and_Temby_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub6_11 = "Freeport";
        three = new QStandardItem(sub6_11);
        three->setData(sub6_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Freeport_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub7_11 = "Northern Ro";
        three = new QStandardItem(sub7_11);
        three->setData(sub7_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Northern_Ro_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub8_11 = "Elemental Towers";
        three = new QStandardItem(sub8_11);
        three->setData(sub8_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Elemental_Towers_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub9_11 = "Hazinak Dock";
        three = new QStandardItem(sub9_11);
        three->setData(sub9_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Hazinak_Dock_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub10_11 = "Hazinak Temple";
        three = new QStandardItem(sub10_11);
        three->setData(sub10_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Hazinak_Temple_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub11_11 = "Guk";
        three = new QStandardItem(sub11_11);
        three->setData(sub11_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Guk_tp,Qt::UserRole+3);
        two->appendRow(three);

        QString sub12_11 = "Grobb";
        three = new QStandardItem(sub12_11);
        three->setData(sub12_11,Qt::UserRole+1); //hide name
        three->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        three->setData(Opcodes::Grobb_tp,Qt::UserRole+3);
        two->appendRow(three);

        ////////////////////////////////////Tunaria End///////////////////////



        //////////////////////Rathe//////////////////////////////////////////

        QString fin2 = "Rathe";
        one = new QStandardItem(fin2);
        rootNode->appendRow(one);


        QString sub_rat1 = "Oggok";
        two = new QStandardItem(sub_rat1);
        two->setData(sub_rat1,Qt::UserRole+1); //Hide Name
        two->setData(0x01,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Oggok_tp,Qt::UserRole+3);
        one->appendRow(two);


        ///////////////////Rathe End///////////////////////////////////////////

        ////////////////////Odus////////////////////////////////////////////////
        QString fin3 = "Odus";
        one = new QStandardItem(fin3);
        rootNode->appendRow(one);

        QString sub_odu1 = "Phantoms";
        two = new QStandardItem(sub_odu1);
        two->setData(sub_odu1,Qt::UserRole+1); //Hide Name
        two->setData(0x02,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Phantoms_tp,Qt::UserRole+3);
        one->appendRow(two);

        ////////////////////Odus End/////////////////////////////////////////////

        ////////////////////Lavastorm////////////////////////////////////////////////

        QString fin4 = "Lavastorm";
        one = new QStandardItem(fin4);
        rootNode->appendRow(one);

        QString sub_lav1 = "Waysender";
        two = new QStandardItem(sub_lav1);
        two->setData(sub_lav1,Qt::UserRole+1); //Hide Name
        two->setData(0x03,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Waysender_tp,Qt::UserRole+3);
        one->appendRow(two);

        ///////////////////Lavastorm End////////////////////////////////////////////////

        ////////////////////Plane of Sky////////////////////////////////////////////////

        QString fin5 = "Plane of Sky";
        one = new QStandardItem(fin5);
        rootNode->appendRow(one);

        QString sub_sky1 = "Main Island";
        two = new QStandardItem(sub_sky1);
        two->setData(sub_sky1,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Pos_Main_Isle,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky2 = "Isle of Wonder";
        two = new QStandardItem(sub_sky2);
        two->setData(sub_sky2,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Isle_of_Wonder,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky3 = "Sun 1 In";
        two = new QStandardItem(sub_sky3);
        two->setData(sub_sky3,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_1_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky4 = "Sun 1 Village";
        two = new QStandardItem(sub_sky4);
        two->setData(sub_sky4,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_1_village,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky5 = "Sun 1 Out";
        two = new QStandardItem(sub_sky5);
        two->setData(sub_sky5,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_1_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky6 = "Sun 2 In";
        two = new QStandardItem(sub_sky6);
        two->setData(sub_sky6,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_2_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky7 = "Sun 2 Ramp";
        two = new QStandardItem(sub_sky7);
        two->setData(sub_sky7,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_2_ramp,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky8 = "Sun 2 Out";
        two = new QStandardItem(sub_sky8);
        two->setData(sub_sky8,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_2_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky9 = "Sun 3 In";
        two = new QStandardItem(sub_sky9);
        two->setData(sub_sky9,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_3_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky10 = "Sun 3 Out";
        two = new QStandardItem(sub_sky10);
        two->setData(sub_sky10,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_3_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky11 = "Sun 4 In";
        two = new QStandardItem(sub_sky11);
        two->setData(sub_sky11,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_4_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky12 = "Sun 4 Out";
        two = new QStandardItem(sub_sky12);
        two->setData(sub_sky12,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Sun_4_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky13 = "Rain 1 In";
        two = new QStandardItem(sub_sky13);
        two->setData(sub_sky13,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_1_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky14 = "Rain 1 Out";
        two = new QStandardItem(sub_sky14);
        two->setData(sub_sky14,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_1_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky15 = "Rain 2 In";
        two = new QStandardItem(sub_sky15);
        two->setData(sub_sky15,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_2_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky16 = "Rain 2 Out";
        two = new QStandardItem(sub_sky16);
        two->setData(sub_sky16,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_2_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky17 = "Rain 3 In";
        two = new QStandardItem(sub_sky17);
        two->setData(sub_sky17,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_3_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky18 = "Rain 3 Out";
        two = new QStandardItem(sub_sky18);
        two->setData(sub_sky18,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_3_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky19 = "Rain 4 In";
        two = new QStandardItem(sub_sky19);
        two->setData(sub_sky19,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_4_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky20 = "Rain 4 Out";
        two = new QStandardItem(sub_sky20);
        two->setData(sub_sky20,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_4_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky21 = "Rain 5 In";
        two = new QStandardItem(sub_sky21);
        two->setData(sub_sky21,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_5_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky22 = "Rain 5 Out";
        two = new QStandardItem(sub_sky22);
        two->setData(sub_sky22,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Rain_5_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky23 = "Night 1 In";
        two = new QStandardItem(sub_sky23);
        two->setData(sub_sky23,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_1_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky24 = "Night 1 Out";
        two = new QStandardItem(sub_sky24);
        two->setData(sub_sky24,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_1_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky25 = "Night 2 In";
        two = new QStandardItem(sub_sky25);
        two->setData(sub_sky25,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_2_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky26 = "Night 2 Out";
        two = new QStandardItem(sub_sky26);
        two->setData(sub_sky26,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_2_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky27 = "Night 3 In";
        two = new QStandardItem(sub_sky27);
        two->setData(sub_sky27,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_3_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky28 = "Night 3 Out";
        two = new QStandardItem(sub_sky28);
        two->setData(sub_sky28,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_3_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky29 = "Night 4 In";
        two = new QStandardItem(sub_sky29);
        two->setData(sub_sky29,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_4_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky30 = "Night 4 Out";
        two = new QStandardItem(sub_sky30);
        two->setData(sub_sky30,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_4_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky31 = "Night 5 In";
        two = new QStandardItem(sub_sky31);
        two->setData(sub_sky31,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_5_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky32 = "Night 5 Out";
        two = new QStandardItem(sub_sky32);
        two->setData(sub_sky32,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Night_5_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky33 = "Snow 1 In";
        two = new QStandardItem(sub_sky33);
        two->setData(sub_sky33,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_1_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky34 = "Snow 1 Center";
        two = new QStandardItem(sub_sky34);
        two->setData(sub_sky34,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_1_center,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky35 = "Snow 1 Bottom";
        two = new QStandardItem(sub_sky35);
        two->setData(sub_sky35,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_1_bottom,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky36 = "Snow 2 In";
        two = new QStandardItem(sub_sky36);
        two->setData(sub_sky36,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_2_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky37 = "Snow 2 Out";
        two = new QStandardItem(sub_sky37);
        two->setData(sub_sky37,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_2_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky38 = "Snow 3 In";
        two = new QStandardItem(sub_sky38);
        two->setData(sub_sky38,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_3_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky39 = "Snow 3 Out";
        two = new QStandardItem(sub_sky39);
        two->setData(sub_sky39,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_3_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky40 = "Snow 4 In";
        two = new QStandardItem(sub_sky40);
        two->setData(sub_sky40,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_4_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky41 = "Snow 4 Pad";
        two = new QStandardItem(sub_sky41);
        two->setData(sub_sky41,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_4_pad,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky42 = "Snow 4 Out";
        two = new QStandardItem(sub_sky42);
        two->setData(sub_sky42,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Snow_4_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky43 = "Deso 1 In";
        two = new QStandardItem(sub_sky43);
        two->setData(sub_sky43,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_1_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky44 = "Deso 1 Out";
        two = new QStandardItem(sub_sky44);
        two->setData(sub_sky44,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_1_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky45 = "Deso 2 In";
        two = new QStandardItem(sub_sky45);
        two->setData(sub_sky45,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_2_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky46 = "Deso 2 Village";
        two = new QStandardItem(sub_sky46);
        two->setData(sub_sky46,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_2_village,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky47 = "Deso 2 Out";
        two = new QStandardItem(sub_sky47);
        two->setData(sub_sky47,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_2_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky48 = "Deso 3 In";
        two = new QStandardItem(sub_sky48);
        two->setData(sub_sky48,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_3_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky49 = "Deso 3 Out";
        two = new QStandardItem(sub_sky49);
        two->setData(sub_sky49,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_3_out,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky50 = "Deso 4 In";
        two = new QStandardItem(sub_sky50);
        two->setData(sub_sky50,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_4_in,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_sky51 = "Deso 4 Out";
        two = new QStandardItem(sub_sky51);
        two->setData(sub_sky51,Qt::UserRole+1); //Hide Name
        two->setData(0x04,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Deso_4_out,Qt::UserRole+3);
        one->appendRow(two);

        ////////////////////Plane of Sky End////////////////////////////////////////////////

        /////////////////Plane of Disease////////////////////////////////////////
        QString fin7= "Plane of Disease";
        one = new QStandardItem(fin7);
        rootNode->appendRow(one);

        QString sub_zao1 = "Last Home";
        two = new QStandardItem(sub_zao1);
        two->setData(sub_zao1,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Last_Home_tp,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zao2 = "Last Home 2";
        two = new QStandardItem(sub_zao2);
        two->setData(sub_zao2,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Last_Home_2,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zao3 = "Pod 1";
        two = new QStandardItem(sub_zao3);
        two->setData(sub_zao3,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Pod_1,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zao4 = "Pod 2";
        two = new QStandardItem(sub_zao4);
        two->setData(sub_zao4,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Pod_2,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zao5 = "Pod 3";
        two = new QStandardItem(sub_zao5);
        two->setData(sub_zao5,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Pod_3,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zao6 = "Pod 4";
        two = new QStandardItem(sub_zao6);
        two->setData(sub_zao6,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Pod_4,Qt::UserRole+3);
        one->appendRow(two);



        ////////////////////////Isle of Dread///////////////////////////////
        QString fin8 = "Isle of Dread";
        one = new QStandardItem(fin8);
        rootNode->appendRow(one);

        QString sub1_isle1 = "Boat";
        two = new QStandardItem(sub1_isle1);
        two->setData(sub1_isle1,Qt::UserRole+1); //hide name
        two->setData(0x00,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Isle_of_Dread_tp,Qt::UserRole+3);
        one->appendRow(two);


        ////////////////////Zp////////////////////////////////////////////////
        QString fin6 = "Zaorean Plateau";
        one = new QStandardItem(fin6);
        rootNode->appendRow(one);

        QString sub_zp1 = "Zp 1";
        two = new QStandardItem(sub_zp1);
        two->setData(sub_zp1,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Zp_1,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zp2 = "Zp 2";
        two = new QStandardItem(sub_zp2);
        two->setData(sub_zp2,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Zp_2,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zp3 = "Zp 3";
        two = new QStandardItem(sub_zp3);
        two->setData(sub_zp3,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Zp_3,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zp4 = "Zp 4";
        two = new QStandardItem(sub_zp4);
        two->setData(sub_zp4,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Zp_4,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zp5 = "Zp 5";
        two = new QStandardItem(sub_zp5);
        two->setData(sub_zp5,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Zp_5,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zp6 = "Zp 6";
        two = new QStandardItem(sub_zp6);
        two->setData(sub_zp6,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Zp_6,Qt::UserRole+3);
        one->appendRow(two);

        QString sub_zp7 = "Zp 7";
        two = new QStandardItem(sub_zp7);
        two->setData(sub_zp7,Qt::UserRole+1); //Hide Name
        two->setData(0x05,Qt::UserRole+2); //Hide World Data Inside Each One :)
        two->setData(Opcodes::Zp_7,Qt::UserRole+3);
        one->appendRow(two);

        //////////////////Zp End/////////////////////////////////////////////


    }


}





void MainWindow::teleportoff()
{
    packetparsing::packetvars IN_TELEPORT;
    IN_TELEPORT = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    timer.stop();
    IN_TELEPORT.teleporting = false;
    IN_TELEPORT.teleport_destination.clear();
    ui->treeView->setDisabled(false);


    //only need to xor the 00 channel here
    // xoring the rest of the channels after they have been xored or are empty is pointless.

    ui->plainTextEdit->appendPlainText("");
    ui->plainTextEdit->appendPlainText("teleportoff-------------------------------");
    ui->plainTextEdit->appendPlainText("LastTeleportWorld " + QString::number(IN_TELEPORT.LastTeleportWorld));
    ui->plainTextEdit->appendPlainText("masterworld " + QString::number(IN_TELEPORT.masterworld));
    ui->plainTextEdit->appendPlainText("teleportoff-------------------------------");
    ui->plainTextEdit->appendPlainText("");


    if(IN_TELEPORT.LastTeleportWorld != IN_TELEPORT.masterworld)
    {
        QByteArray holdergen2 = "00c9xxxx01100180c800";

        IN_TELEPORT.SendZeroChannelVector.append(holdergen2);
    }
    ///////////////////////////////////////////////////

    IN_TELEPORT.SendZeroChannelVector.append("FC02D007");

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_TELEPORT);

}



void MainWindow::spellcooldown()
{

    packetparsing::packetvars IN_TELEPORT;
    IN_TELEPORT = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    auto* receivedtimer = qobject_cast<QTimer*>(sender()); //get the pointer of the original sender
    if(timers1.contains(receivedtimer)) //remove from unmemorize all list if it arrives here first if not we crash!!!
    {
        timers1.removeOne(receivedtimer);
    }
    QString  ident = receivedtimer->objectName(); //get the name we set
    receivedtimer->deleteLater(); //delete our pointer so we dont leak from using "new"
    int book_pos = ident.indexOf("%%",0);
    QString new_spell_id = ident.mid(book_pos + 2,2);
    int new_slot = spellslot_map.key(new_spell_id.toInt(nullptr,16));

    switch (new_slot)
    {
    case 0:
        slot_0_trigger = false;
        cooldown_0 = false;
        master_spell_count = spell_0_counter;
        break;
    case 1:
        slot_1_trigger = false;
        cooldown_1 = false;
        master_spell_count = spell_1_counter;
        break;
    case 2:
        slot_2_trigger = false;
        cooldown_2 = false;
        master_spell_count = spell_2_counter;
        break;
    case 3:
        slot_3_trigger = false;
        cooldown_3 = false;
        master_spell_count = spell_3_counter;
        break;
    case 4:
        slot_4_trigger = false;
        cooldown_4 = false;
        master_spell_count = spell_4_counter;
        break;
    case 5:
        slot_5_trigger = false;
        cooldown_5 = false;
        master_spell_count = spell_5_counter;
        break;
    case 6:
        slot_6_trigger = false;
        cooldown_6 = false;
        master_spell_count = spell_6_counter;
        break;
    case 7:
        slot_7_trigger = false;
        cooldown_7 = false;
        master_spell_count = spell_7_counter;
        break;
    case 8:
        slot_8_trigger = false;
        cooldown_8 = false;
        master_spell_count = spell_8_counter;
        break;
    case 9:
        slot_9_trigger = false;
        cooldown_9 = false;
        master_spell_count = spell_9_counter;
        break;
    default:
        break;
    }



    QByteArray ungrey = "CD0000010000000000";

    ungrey.replace(4,2,new_spell_id.toUtf8()); //spell id ///check this, pcaps are times two like login
    ungrey.replace(6,4,master_spell_count);

    IN_TELEPORT.SendFBsVector.append(ungrey);
    IN_TELEPORT.FBReplyOrNotVector.append("00");
    IN_TELEPORT.FBPacketDescriptionVector.append("Ungrey_Spell, ");

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_TELEPORT);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//this is just to stop and ungrey any running spells if you remove all or overwrite
void MainWindow::spellunmemorize() //memorize and unmemorize all both come here, only unmemorize all resets the spellslot map
{

    packetparsing::packetvars IN_TELEPORT;
    IN_TELEPORT = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    for(int cc = 0; cc < timers1.size(); cc++) //clear all timers
    {

        auto* receivedtimer = timers1.at(cc); //attempting to stop timers on memorize and unmemorize all

        QString  ident = receivedtimer->objectName(); //get the name we set
        int book_pos = ident.indexOf("%%",0);
        QString new_spell_id2 = ident.mid(book_pos + 2,2);
        int new_slot2 = spellslot_map.key(new_spell_id2.toInt(nullptr,16));

        receivedtimer->stop();
        //      ui->textEdit_4->append("timer attempted stop..." + ident + "...done"); //show to ui
        receivedtimer->deleteLater();
        //            ui->textEdit_4->append("new_slot_2..." + QString::number(new_slot2,10));
        slot_0_trigger = false;     slot_1_trigger = false;   slot_2_trigger = false;     slot_3_trigger = false;   slot_4_trigger = false; //to get the old one thats now something new
        slot_5_trigger = false;     slot_6_trigger = false;   slot_7_trigger = false;     slot_8_trigger = false;   slot_9_trigger = false;


        switch (new_slot2)
        {
        case 0:
            slot_0_trigger = false;
            cooldown_0 = false;
            master_spell_count = spell_0_counter;
            break;
        case 1:
            slot_1_trigger = false;
            cooldown_1 = false;
            master_spell_count = spell_1_counter;
            break;
        case 2:
            slot_2_trigger = false;
            cooldown_2 = false;
            master_spell_count = spell_2_counter;
            break;
        case 3:
            slot_3_trigger = false;
            cooldown_3 = false;
            master_spell_count = spell_3_counter;
            break;
        case 4:
            slot_4_trigger = false;
            cooldown_4 = false;
            master_spell_count = spell_4_counter;
            break;
        case 5:
            slot_5_trigger = false;
            cooldown_5 = false;
            master_spell_count = spell_5_counter;
            break;
        case 6:
            slot_6_trigger = false;
            cooldown_6 = false;
            master_spell_count = spell_6_counter;
            break;
        case 7:
            slot_7_trigger = false;
            cooldown_7 = false;
            master_spell_count = spell_7_counter;
            break;
        case 8:
            slot_8_trigger = false;
            cooldown_8 = false;
            master_spell_count = spell_8_counter;
            break;
        case 9:
            slot_9_trigger = false;
            cooldown_9 = false;
            master_spell_count = spell_9_counter;
            break;
        default:
            break;
        }



        QByteArray ungrey = "CD0000010000000000";

        ungrey.replace(4,2,new_spell_id2.toUtf8()); //spell id...///check this..pcap is times two so login numbers
        ungrey.replace(6,4,master_spell_count);

        IN_TELEPORT.SendFBsVector.append(ungrey);
        IN_TELEPORT.FBReplyOrNotVector.append("00");
        IN_TELEPORT.FBPacketDescriptionVector.append("Ungrey_Spells, ");
    }

    timers1.clear(); //clear the timer list for unmemorize

    if(unmemorize == true) //clear all spellslots in map
    {
        QMapIterator<int, int>  iter1 (spellslot_map); //clearing all spell slots to an unreachable number
        while (iter1.hasNext())
        {
            iter1.next();
            int curr_key = iter1.key();
            spellslot_map.insert(curr_key,0xFF);
        }
        unmemorize = false; //set the bool back
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_TELEPORT);

    return; //try returning from this...should be ok
}



void MainWindow::on_actionReset_Main_Coordinates_triggered()
{
    packetparsing::packetvars IN_Reset_Main;
    IN_Reset_Main = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QString tablesel3 = "MAINTOON";
    QString objecttlpt3 = "ObjectID (4)";
    QString xtlpt3 = "X (3)";
    QString ytlpt3 = "Y (3)";
    QString ztlpt3 = "Z (3)";
    QString worldtlpt3 = "World (1)";
    QString tlptid3 = IN_Reset_Main.CharSelectID;
    QString chosenworld2 = "00";

    QString x2 = "317B17";
    QString y2 = "1EC231";
    QString z2 = "001B10";

    db.transaction();
    QSqlQuery querytlpt3;
    querytlpt3.prepare(QStringLiteral("UPDATE %1 SET [%2] = :val2,[%3] = :val3,[%4] = :val4,[%5] = :val5 WHERE [%6] = :val").arg(tablesel3).arg(xtlpt3).arg(ytlpt3).arg(ztlpt3).arg(worldtlpt3).arg(objecttlpt3));

    querytlpt3.bindValue(":val",tlptid3);
    querytlpt3.bindValue(":val2",x2.toUpper());
    querytlpt3.bindValue(":val3",y2.toUpper());
    querytlpt3.bindValue(":val4",z2.toUpper());
    querytlpt3.bindValue(":val5",chosenworld2.toUpper());

    querytlpt3.exec();
    db.commit();
    ui->textEdit_5->append("Reset Main Coordinates...OK");


}

void MainWindow::coachingoff()
{
    coachtimer.stop();
    on_pushButton_4_clicked(); //send coaching to teleport after filling teleport_destination
}

void MainWindow::on_actionReset_All_Coaches_triggered()
{
    packetparsing::packetvars IN_Reset_Coaches;
    IN_Reset_Coaches = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QList<QString> positionlist2;


    db.transaction();
    QString objectidb1 = "ObjectID (4)";
    QString maintoonb1 = IN_Reset_Coaches.CharSelectID;
    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT * FROM COACHES WHERE [%1] = '%2'").arg(objectidb1).arg(maintoonb1));
    query.exec();
    query.next();

    QSqlRecord record = query.record();

    for(int rr = 0; rr < record.count(); rr++)
    {
        positionlist2.append(record.fieldName(rr));
    }

    positionlist2.removeAt(0);
    positionlist2.removeAt(0);
    positionlist2.removeAt(0);

    int writenum = 0; //resetting coaching

    for(int rt = 0; rt < positionlist2.count(); rt++)
    {
        QString place1 = positionlist2.value(rt);
        query.prepare(QString("UPDATE COACHES SET [%1] = :val WHERE [%2] = :val2").arg(place1).arg(objectidb1));

        writenum = StartingCoachVector.at(rt);

        query.bindValue(":val",writenum);
        query.bindValue(":val2",maintoonb1);
        query.exec();
    }
    db.commit();
    ui->textEdit_5->append("Reset All Coaches...OK");
    positionlist2.clear();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider_2->setValue(0);
    ui->horizontalSlider_3->setValue(0);
    ui->horizontalSlider_4->setValue(0);

    ui->Selection->setCurrentRow(index);

    int index1 = Race_Gender_Index.value(index);
    ui->comboBox_35->setCurrentIndex(index1);

    QString Race = Race_C9_1Byte_MapX2.value(index);
    ui->lineEdit_70->setText(Race);
    ui->lineEdit_90->setText(Race);

    int Race_GenderIndex = ui->comboBox->currentIndex();

    QString Folder = RaceAndGenderFolder.at(Race_GenderIndex);
    QString filename = "C:/Customize/Forms/" + Folder + "/" + QString::number(1) + ".jpg";

    ui->label_216->setPixmap(filename);


}



//Color Dialog Torso
void MainWindow::on_pushButton_46_clicked()
{
    color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_68->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_68->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");
    ui->lineEdit_68->setText(Gear_Color);
    ui->lineEdit_34->setText(Gear_Color);

    on_pushButton_48_clicked();
}

//Color Dialog Forearms
void MainWindow::on_pushButton_49_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_75->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_75->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");
    ui->lineEdit_75->setText(Gear_Color);
    ui->lineEdit_28->setText(Gear_Color);

    on_pushButton_48_clicked();
}

//Color Dialog Glove
void MainWindow::on_pushButton_50_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_81->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_81->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");
    ui->lineEdit_81->setText(Gear_Color);
    ui->lineEdit_52->setText(Gear_Color);

    on_pushButton_48_clicked();
}
// Color Dialog Legs
void MainWindow::on_pushButton_51_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_78->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_78->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");
    ui->lineEdit_78->setText(Gear_Color);
    ui->lineEdit_76->setText(Gear_Color);

    on_pushButton_48_clicked();
}
// Color Dialog Feet
void MainWindow::on_pushButton_52_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_67->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_67->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");
    ui->lineEdit_67->setText(Gear_Color);
    ui->lineEdit_32->setText(Gear_Color);

    on_pushButton_48_clicked();
}

// Color Dialog Head
void MainWindow::on_pushButton_53_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_77->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_77->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");
    ui->lineEdit_77->setText(Gear_Color);
    ui->lineEdit_41->setText(Gear_Color);

    on_pushButton_48_clicked();
}
// Color Dialog Robe
void MainWindow::on_pushButton_54_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_82->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_82->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");
    ui->lineEdit_82->setText(Gear_Color);
    ui->lineEdit_33->setText(Gear_Color);

    on_pushButton_48_clicked();
}









//Facing Dial

void MainWindow::on_pushButton_South_clicked()
{
    int South = ui->Y_4->text().toInt(nullptr,16);
    int South_Plus = South + 0x00000A;

    QString South_Equals = QString("%1").arg(South_Plus,6,16,QLatin1Char('0')).toUpper(); //pad zeros

    ui->Y_4->setText(South_Equals.toUpper());
    ui->lineEdit_74->setText(South_Equals.toUpper());

    if(ui->tabWidget_2->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }

}

void MainWindow::on_pushButton_North_clicked()
{
    int North = ui->Y_4->text().toInt(nullptr,16);
    int North_Plus = North - 0x00000A;

    QString North_Equals = QString("%1").arg(North_Plus,6,16,QLatin1Char('0')).toUpper(); //pad zeros

    ui->Y_4->setText(North_Equals.toUpper());
    ui->lineEdit_74->setText(North_Equals.toUpper());

    if(ui->tabWidget_2->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}

void MainWindow::on_pushButton_East_clicked()
{
    int East = ui->X_4->text().toInt(nullptr,16);
    int East_Plus = East + 0x00000A;

    QString East_Equals = QString("%1").arg(East_Plus,6,16,QLatin1Char('0')).toUpper(); //pad zeros

    ui->X_4->setText(East_Equals.toUpper());
    ui->lineEdit_45->setText(East_Equals.toUpper());

    if(ui->tabWidget_2->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}

void MainWindow::on_pushButton_West_clicked()
{
    int West = ui->X_4->text().toInt(nullptr,16);
    int West_Plus = West - 0x00000A;

    QString West_Equals = QString("%1").arg(West_Plus,6,16,QLatin1Char('0')).toUpper(); //pad zeros

    ui->X_4->setText(West_Equals.toUpper());
    ui->lineEdit_45->setText(West_Equals.toUpper());

    if(ui->tabWidget_2->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}

void MainWindow::on_Z_Plus_clicked()
{
    int Z_Plus = ui->Z_4->text().toInt(nullptr,16);
    int Z_Plus_Plus = Z_Plus + 0x00000A;

    QString Z_Plus_Equals = QString("%1").arg(Z_Plus_Plus,6,16,QLatin1Char('0')).toUpper(); //pad zeros

    ui->Z_4->setText(Z_Plus_Equals.toUpper());
    ui->lineEdit_53->setText(Z_Plus_Equals.toUpper());

    if(ui->tabWidget_2->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}

void MainWindow::on_Z_Minus_clicked()
{
    int Z_Minus = ui->Z_4->text().toInt(nullptr,16);
    int Z_Minus_Plus = Z_Minus - 0x00000A;

    QString Z_Minus_Equals = QString("%1").arg(Z_Minus_Plus,6,16,QLatin1Char('0')).toUpper(); //pad zeros

    ui->Z_4->setText(Z_Minus_Equals.toUpper());
    ui->lineEdit_53->setText(Z_Minus_Equals.toUpper());

    if(ui->tabWidget_2->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}



void MainWindow::on_dial_valueChanged(int value)
{
    ui->spinBox->setValue(value);
}

void MainWindow::on_spinBox_valueChanged(int value)
{
    QString value2 = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();


    ui->lineEdit_133->setText(value2);
    ui->dial->setValue(value);
}



void MainWindow::on_lineEdit_133_textChanged(const QString &arg1)
{
    int Value = arg1.toInt(nullptr,16);
    QString value2 = QString("%1").arg(Value,2,16,QLatin1Char('0')).toUpper();
    ui->lineEdit_133->setText(value2.toUpper());




    if(arg1 == "" || arg1.isEmpty() == true)
    {
        ui->lineEdit_133->setText("00");
        ui->dial->setValue(0);
        ui->spinBox->setValue(0);
    }

    if(ui->tabWidget_2->currentIndex() == 1)
    {
        ui->lineEdit_50->setText(arg1);
        ui->spinBox->setValue(Value);
        ui->dial->setValue(Value);
        on_pushButton_48_clicked();
    }
    else
    {
        ui->lineEdit_50->setText(arg1);

        int arg2 = arg1.toInt(nullptr,16);
        ui->spinBox->setValue(arg2);
        ui->dial->setValue(arg2);
    }
}

void MainWindow::on_Selection_currentRowChanged(int currentRow)
{
    ui->comboBox->setCurrentIndex(currentRow);
}

void MainWindow::on_comboBox_35_currentIndexChanged(int index)
{
    QString Race = Race_C9_1Byte_Map.value(index);
    ui->lineEdit_70->setText(Race);
    ui->lineEdit_90->setText(Race);
}

void MainWindow::on_comboBox_8_currentIndexChanged(int index)
{
    int index1 = index;
    QString value2 = QString("%1").arg(index1,2,16,QLatin1Char('0')).toUpper();
    ui->lineEdit_69->setText(value2);
    ui->lineEdit_122->setText(value2);
}

void MainWindow::on_comboBox_6_currentIndexChanged(int index)
{
    QString value2 = QString("%1").arg(index,2,16,QLatin1Char('0')).toUpper();
    ui->lineEdit_65->setText(value2);
    ui->lineEdit_71->setText(value2);
}


//-100
void MainWindow::on_pushButton_11_clicked()
{
    QString S_Minus = ui->lineEdit_24->text();
    QString Byte_1st = S_Minus.mid(0,2);
    QString Byte_2nd = S_Minus.mid(2,2);
    QString S_Minus_reverse =  Byte_2nd + Byte_1st;

    int S_Minus_reverse1 = S_Minus_reverse.toInt(nullptr,16);
    S_Minus_reverse1 = S_Minus_reverse1 - 0x100;

    QString S_Minus_Equals = QString("%1").arg(S_Minus_reverse1,4,16,QLatin1Char('0')).toUpper(); //pad zeros

    QString Byte_1st2 = S_Minus_Equals.mid(0,2);
    QString Byte_2nd2 = S_Minus_Equals.mid(2,2);

    QString S_Minus_reverse2 =  Byte_2nd2 + Byte_1st2;
    ui->lineEdit_24->setText(S_Minus_reverse2.toUpper());
    ui->lineEdit_37->setText(S_Minus_reverse2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 0)
    {
        on_pushButton_48_clicked();
    }
}

//-10
void MainWindow::on_pushButton_9_clicked()
{
    QString S_Minus = ui->lineEdit_24->text();
    QString Byte_1st = S_Minus.mid(0,2);
    QString Byte_2nd = S_Minus.mid(2,2);
    QString S_Minus_reverse =  Byte_2nd + Byte_1st;

    int S_Minus_reverse1 = S_Minus_reverse.toInt(nullptr,16);
    S_Minus_reverse1 = S_Minus_reverse1 - 0x10;

    QString S_Minus_Equals = QString("%1").arg(S_Minus_reverse1,4,16,QLatin1Char('0')).toUpper(); //pad zeros

    QString Byte_1st2 = S_Minus_Equals.mid(0,2);
    QString Byte_2nd2 = S_Minus_Equals.mid(2,2);

    QString S_Minus_reverse2 =  Byte_2nd2 + Byte_1st2;
    ui->lineEdit_24->setText(S_Minus_reverse2.toUpper());
    ui->lineEdit_37->setText(S_Minus_reverse2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 0)
    {
        on_pushButton_48_clicked();
    }
}

//-1
void MainWindow::on_pushButton_7_clicked()
{
    QString S_Minus = ui->lineEdit_24->text();
    QString Byte_1st = S_Minus.mid(0,2);
    QString Byte_2nd = S_Minus.mid(2,2);
    QString S_Minus_reverse =  Byte_2nd + Byte_1st;

    int S_Minus_reverse1 = S_Minus_reverse.toInt(nullptr,16);
    S_Minus_reverse1 = S_Minus_reverse1 - 0x01;

    QString S_Minus_Equals = QString("%1").arg(S_Minus_reverse1,4,16,QLatin1Char('0')).toUpper(); //pad zeros

    QString Byte_1st2 = S_Minus_Equals.mid(0,2);
    QString Byte_2nd2 = S_Minus_Equals.mid(2,2);

    QString S_Minus_reverse2 =  Byte_2nd2 + Byte_1st2;
    ui->lineEdit_24->setText(S_Minus_reverse2.toUpper());
    ui->lineEdit_37->setText(S_Minus_reverse2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 0)
    {
        on_pushButton_48_clicked();
    }
}

//+1
void MainWindow::on_pushButton_8_clicked()
{
    QString S_Plus = ui->lineEdit_24->text();
    QString Byte_1st = S_Plus.mid(0,2);
    QString Byte_2nd = S_Plus.mid(2,2);
    QString S_Plus_reverse =  Byte_2nd + Byte_1st;

    int S_Plus_reverse1 = S_Plus_reverse.toInt(nullptr,16);

    S_Plus_reverse1 = S_Plus_reverse1 + 0x01;

    QString S_Plus_Equals = QString("%1").arg(S_Plus_reverse1,4,16,QLatin1Char('0')).toUpper(); //pad zeros

    QString Byte_1st2 = S_Plus_Equals.mid(0,2);
    QString Byte_2nd2 = S_Plus_Equals.mid(2,2);

    QString S_Plus_reverse2 =  Byte_2nd2 + Byte_1st2;
    ui->lineEdit_24->setText(S_Plus_reverse2.toUpper());
    ui->lineEdit_37->setText(S_Plus_reverse2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 0)
    {
        on_pushButton_48_clicked();
    }
}

//+10
void MainWindow::on_pushButton_10_clicked()
{
    QString S_Plus = ui->lineEdit_24->text();
    QString Byte_1st = S_Plus.mid(0,2);
    QString Byte_2nd = S_Plus.mid(2,2);
    QString S_Plus_reverse =  Byte_2nd + Byte_1st;

    int S_Plus_reverse1 = S_Plus_reverse.toInt(nullptr,16);

    S_Plus_reverse1 = S_Plus_reverse1 + 0x10;

    QString S_Plus_Equals = QString("%1").arg(S_Plus_reverse1,4,16,QLatin1Char('0')).toUpper(); //pad zeros

    QString Byte_1st2 = S_Plus_Equals.mid(0,2);
    QString Byte_2nd2 = S_Plus_Equals.mid(2,2);

    QString S_Plus_reverse2 =  Byte_2nd2 + Byte_1st2;
    ui->lineEdit_24->setText(S_Plus_reverse2.toUpper());
    ui->lineEdit_37->setText(S_Plus_reverse2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 0)
    {
        on_pushButton_48_clicked();
    }
}

//+100
void MainWindow::on_pushButton_12_clicked()
{
    QString S_Plus = ui->lineEdit_24->text();
    QString Byte_1st = S_Plus.mid(0,2);
    QString Byte_2nd = S_Plus.mid(2,2);
    QString S_Plus_reverse =  Byte_2nd + Byte_1st;

    int S_Plus_reverse1 = S_Plus_reverse.toInt(nullptr,16);

    S_Plus_reverse1 = S_Plus_reverse1 + 0x100;

    QString S_Plus_Equals = QString("%1").arg(S_Plus_reverse1,4,16,QLatin1Char('0')).toUpper(); //pad zeros

    QString Byte_1st2 = S_Plus_Equals.mid(0,2);
    QString Byte_2nd2 = S_Plus_Equals.mid(2,2);

    QString S_Plus_reverse2 =  Byte_2nd2 + Byte_1st2;
    ui->lineEdit_24->setText(S_Plus_reverse2.toUpper());
    ui->lineEdit_37->setText(S_Plus_reverse2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 0)
    {
        on_pushButton_48_clicked();
    }
}

void MainWindow::on_comboBox_34_currentIndexChanged(int index)
{
    QString NPC_Type1 = NPC_Type.value(index);
    ui->lineEdit_25->setText(NPC_Type1);
    ui->lineEdit_73->setText(NPC_Type1);

    if(index == 6)
    {
        ui->lineEdit_66->setText("00");
    }
    else
    {
        ui->lineEdit_66->setText("01");
    }
}

void MainWindow::on_lineEdit_9_textChanged(const QString &arg1)
{
    ui->lineEdit_29->setText(arg1);
    int Level = arg1.toInt(nullptr,10);
    QString Level_Equals = QString("%1").arg(Level,2,16,QLatin1Char('0')).toUpper(); //pad zeros
    ui->lineEdit_26->setText(Level_Equals);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->lineEdit_24->setText("803F");
    ui->lineEdit_37->setText("803F");
    on_pushButton_48_clicked();
}



void MainWindow::on_lineEdit_NPC_Name_textChanged(const QString &arg1)
{
    QByteArray arg2 = arg1.toUtf8().toHex();
    int Mysize = arg2.size() /2; //divide by two for bytes
    int numzeros = 24 - Mysize;
    for(int x = 0; x < numzeros; x++)
    {
        arg2.append("00");
    }
    ui->lineEdit_NPC_Name2->setText(arg2.toUpper());

}



//Add ALL
void MainWindow::on_pushButton_61_clicked()
{

    packetparsing::packetvars IN_ADD_ALL;
    IN_ADD_ALL = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QVector<QString> TableNames =
    {
        "NPCS","NPC_CHANGES"
    };

    for(int t = 0; t< TableNames.size(); t++)
    {

        db.transaction();

        Table_Name = TableNames.at(t);


        packetid = ui->lineEdit_72->text().toInt(nullptr,10);
        ui->pushButton_61->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");


        QByteArray Column_value7 = ui->lineEdit_NPC_Name->text().toUtf8();


        QByteArray NewName = Column_value7;


        QSqlQuery query;

        rowline.clear();



        if(IN_ADD_ALL.Target_ID == IN_ADD_ALL.CharSelectID_Main && ui->checkBox_5->isChecked() == true)
        {
            Table_Name = "MAINTOON";
            packetid = ui->lineEdit_72->text().toInt(nullptr,10); //decimal order
        }

        if((IN_ADD_ALL.Target_ID != IN_ADD_ALL.CharSelectID_Main &&
            ui->checkBox_5->isChecked() == false &&
            ui->checkBox_7->isChecked() == true &&
            ui->checkBox_14->isChecked() == false) ||
                (ui->checkBox_6->isChecked() == true))
        {
            packetid = ui->lineEdit_72->text().toInt(nullptr,10);



            Column_Name = "Packet (8)";
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",packetid);
            query.exec();

            if(!query.exec())
            {
                ui->lineEdit_20->setText(query.lastError().text());
                return;
            }
        }



        int packetNumber = 0;
        int ZoneNumber = 0;
        QByteArray NPCID = ui->lineEdit_130->text().toUtf8();
        QByteArray New_NPC = "";
        QString NewNPCS = "";


        if(ui->checkBox_14->isChecked() == true)
        {
            if(PacketIDnewVector.isEmpty() == false && Table_Name == "NPCS")
            {
                packetNumber = PacketIDnewVector.at(0);
                ZoneNumber = MergerZoneNumber.at(0);
                New_NPC = NPCsNewIDVector.at(0).toUtf8();
                //qDebug() << "packetNumber2" << packetNumber;
                NPCID = New_NPC;
                //qDebug() << "NPCID2" << NPCID;

                NewName = NPCsNewNameVector.at(0).toUtf8();
                ui->lineEdit_NPC_Name->setText(NewName);
            }

            if(PacketIDnewVector.isEmpty() == false && Table_Name == "NPC_CHANGES")
            {
                packetNumber = PacketIDnewVector.takeAt(0);
                ZoneNumber = MergerZoneNumber.takeAt(0);
                New_NPC = NPCsNewIDVector.takeAt(0).toUtf8();
                //qDebug() << "packetNumber2" << packetNumber;
                NPCID = New_NPC;
                //qDebug() << "NPCID2" << NPCID;

                NewName = NPCsNewNameVector.takeAt(0).toUtf8();
                ui->lineEdit_NPC_Name->setText(NewName);
            }

            ui->textEdit_13->append("Table_Name " + Table_Name);
            ui->textEdit_13->append("packetNumber2 " + QString::number(packetNumber));
            ui->textEdit_13->append("NPCID2 " + NPCID);



            if(Opcodes::ID_PacketNumber_Map.contains(NPCID))
            {
                packetid = packetNumber;
            }
            else
            {
                packetid = ui->lineEdit_72->text().toInt(nullptr,10);
            }

            ui->textEdit_13->append("packetid_DB_ADD " + QString::number(packetid));

            //qDebug() << "packetid" << packetid;
            //qDebug() << "packetid" << NPCID;

            Column_Name = "Packet (8)";
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",packetid);
            query.exec();

            if(!query.exec())
            {
                ui->lineEdit_20->setText(query.lastError().text());
                return;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        QString Column_Name0 = "Packet (8)";


        //ui->textEdit_12->append("NPCs Name " + NewName);

        Column_Name = "Name (24 Max)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",NewName);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            if(ui->checkBox_6->isChecked() == true)
            {
                ui->lineEdit_20->setText("NPC \"" + NewName + "\" was successfully added to the database.");
            }
            else
            {
                ui->lineEdit_20->setText("NPC \"" + NewName + "\" was updated successfully");
            }
        }

        if(ui->checkBox_14->isChecked() == false)
        {
            ZoneNumber = ui->lineEdit_NPC_Zone_Number->text().toInt(nullptr,10);
        }

        Column_Name = "Zone";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",ZoneNumber);
        query.bindValue(":id",packetid);
        query.exec();






        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "01";

        Column_Name = "Unk-a (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        if(!Opcodes::ID_PacketNumber_Map.contains(NPCID))
        {
            NPCID = ui->lineEdit_130->text().toUtf8();
        }




        QString NewID = "";


        if(IN_ADD_ALL.Target_ID == IN_ADD_ALL.CharSelectID_Main && ui->checkBox_5->isChecked() == true)
        {
            rowline.append(IN_ADD_ALL.CharSelectID);
        }
        else
        {
            if(reSpawnIDsMap.isEmpty() == false && reSpawnIDsMap.contains(NPCID))
            {
                NPCID = reSpawnIDsMap.value(NPCID).toUtf8();
            }

            if(ui->checkBox_14->isChecked() == true && ui->checkBox_8->isChecked() == true && Table_Name == "NPCS")
            {
                NewNPCS = "NO";
            }
            else
            {
                int index = EndingIDXZYF.indexOf(NPCID);



                if(index == -1)
                {
                    NewNPCS = "YES";
                    //file.write("IsItNew- = " + NewNPCS.toUtf8());
                    //file.write("\n");
                }
                else
                {
                    NewNPCS = IsItNew.at(index);
                    //file.write("IsItNew+ = " + NewNPCS.toUtf8());
                    //file.write("\n");

                }

                //file.close();
            }


            if(Table_Name != "MAINTOON")
            {
                if(ui->checkBox_8->isChecked() == true && Table_Name == "NPCS")
                {
                    NewNPCS = "NO";
                }

                //file.write("NewNPCS = " + NewNPCS.toUtf8());
                //file.write("\n");

                Column_Name = "New_NPC";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
                query.bindValue(":val",NewNPCS);
                query.bindValue(":id",packetid);
                query.exec();
            }

            //file.write("NPCID3 " + NPCID);
            //file.write("\n");

            Column_Name = "ObjectID (4)";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
            query.bindValue(":val",NPCID);
            query.bindValue(":id",packetid);
            query.exec();

            if(!query.exec())
            {
                ui->lineEdit_20->setText(query.lastError().text());
                ui->textEdit_13->append(query.lastError().text());
                ui->textEdit_13->append("NPCID " + NPCID);
                ui->textEdit_13->append("packetid " + QString::number(packetid));
                ui->textEdit_13->append("");
                return;
            }
            else
            {
                rowline.append(NPCID);
            }
        }




        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "82";

        Column_Name = "Unk-b (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }


        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_45->text().toUtf8();
        QString NewX = "";

        Column_Name = "X (3)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            NewX = Column_value;
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_53->text().toUtf8();
        QString NewZ = "";

        Column_Name = "Z (3)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            NewZ = Column_value;
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_74->text().toUtf8();
        QString NewY = "";

        Column_Name = "Y (3)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            NewY = Column_value;
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_50->text().toUtf8();

        Column_Name = "Facing (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00";

        Column_Name = "V Facing (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        QString Column_valuew = ui->lineEdit_71->text();

        //file.write("World " + Column_valuew.toUtf8());
        //file.write("\n");

        Column_Name = "World (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_valuew);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_valuew);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "0000000000000000";

        Column_Name = "Date/Time Kill (8)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_66->text().toUtf8();

        Column_Name = "Hp (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_51->text().toUtf8();

        Column_Name = "Hp % (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_54->text().toUtf8();

        Column_Name = "Model ID (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "U Model ID (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        QString Column_value1 = ui->lineEdit_80->text().toUtf8();
        QString Column_value2 = ui->lineEdit_37->text().toUtf8();

        Column_Name = "Size (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value1 + Column_value2);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value1);
            rowline.append(Column_value2);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "0000";

        Column_Name = "W/E Form (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "0000";

        Column_Name = "N/S Form (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00";

        Column_Name = "Unk-d (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "0000";

        Column_Name = "W/E Cam (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////


        Column_value = "0000";

        Column_Name = "N/S Cam (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00";

        Column_Name = "Unk-f (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "Z Coord (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "Facing (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_35->text().toUtf8();

        Column_Name = "Animation (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFFFFFF";

        Column_Name = "Target (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "Unk-g (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_62->text().toUtf8();

        Column_Name = "MH Weapon (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_63->text().toUtf8();

        Column_Name = "OH Weapon (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_64->text().toUtf8();

        Column_Name = "Shield (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "Primary MH (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "Primary OH (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "Primary Shield (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "0000";

        Column_Name = "Unk-h (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_39->text().toUtf8();

        Column_Name = "Torso (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_43->text().toUtf8();

        Column_Name = "Forearm (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_48->text().toUtf8();

        Column_Name = "Gloves (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_27->text().toUtf8();

        Column_Name = "Legs (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_49->text().toUtf8();

        Column_Name = "Feet (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_47->text().toUtf8();

        Column_Name = "Head (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFF";

        Column_Name = "Chest Color (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFF";

        Column_Name = "Bracer Color (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFF";

        Column_Name = "Glove Color (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFF";

        Column_Name = "Pant Color (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFF";

        Column_Name = "Boot Color (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFF";

        Column_Name = "Helm Color (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_34->text().toUtf8();

        Column_Name = "Chest Rbga (5)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_28->text().toUtf8();

        Column_Name = "Bracer Rbga (5)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_52->text().toUtf8();

        Column_Name = "Glove Rbga (5)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_76->text().toUtf8();

        Column_Name = "Pant Rbga (5)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_32->text().toUtf8();

        Column_Name = "Boot Rbga (5)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_41->text().toUtf8();

        Column_Name = "Helm Rbga (5)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_33->text().toUtf8();

        Column_Name = "Robe Rbga (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_128->text().toUtf8();

        Column_Name = "Hair Color (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_127->text().toUtf8();

        Column_Name = "Hair Length (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_126->text().toUtf8();

        Column_Name = "Hair Style (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_125->text().toUtf8();

        Column_Name = "Face (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_124->text().toUtf8();

        Column_Name = "Robe Style (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_90->text().toUtf8();

        Column_Name = "Race-A (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00000000";

        Column_Name = "Unk-j (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_NPC_Name2->text().toUtf8();

        Column_Name = "Character Name (24 Max)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_79->text().toUtf8();

        Column_Name = "Level (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        if(IN_ADD_ALL.Target_ID == IN_ADD_ALL.CharSelectID_Main && ui->checkBox_5->isChecked() == true)
        {
            Column_value = "01";
        }
        else
        {
            Column_value = "00";
        }


        Column_Name = "Player/NPC (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        if(IN_ADD_ALL.Target_ID == IN_ADD_ALL.CharSelectID_Main && ui->checkBox_5->isChecked() == true)
        {
            Column_value = "02";
        }
        else
        {
            Column_value = "00";
        }

        Column_Name = "Con (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "00";

        Column_Name = "Target (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_90->text().toUtf8();

        Column_Name = "Race (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_122->text().toUtf8();

        Column_Name = "Class (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_73->text().toUtf8();

        Column_Name = "Npc Type (2)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "FFFFFFFF";

        Column_Name = "Npc ID (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_95->text().toUtf8();

        Column_Name = "Unk-k (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_96->text().toUtf8();

        Column_Name = "Unk-l (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_97->text().toUtf8();

        Column_Name = "PDI Icon (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_98->text().toUtf8();

        Column_Name = "Unk-m (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_99->text().toUtf8();

        Column_Name = "Unk-n (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = ui->lineEdit_100->text().toUtf8();

        Column_Name = "Unk-o (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = "74737271";

        Column_Name = "Message End (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
        else
        {
            rowline.append(Column_value);
        }

        //file.close();


        if((NPCID != IN_ADD_ALL.CharSelectID && NPCID != IN_ADD_ALL.CharSelectID_Main &&
            ui->checkBox_5->isChecked() == false &&
            Table_Name != "NPC_CHANGES" && ui->checkBox_14->isChecked() == false) ||
                (ui->checkBox_6->isChecked() == true &&
                 Table_Name != "NPC_CHANGES" && Table_Name != "MAINTOON"))
        {

            objectpacket::Master_Map.insert(NPCID,rowline.toUtf8());

            if(IN_ADD_ALL.holdid2.contains(NPCID))
            {
                int index = IN_ADD_ALL.holdid2.indexOf(NPCID);

                //file.write("objectpacket::holdid2 index =  " + QString::number(index).toUtf8());
                //file.write("\n");

                IN_ADD_ALL.holdid2.replace(index,NPCID);

                IN_ADD_ALL.holdx2.replace(index,NewX);
                IN_ADD_ALL.holdz2.replace(index,NewZ);
                IN_ADD_ALL.holdy2.replace(index,NewY);
            }

            if(!objectpacket::MasterMap2.contains(NPCID))
            {
                objectpacket::MasterMap2.insert(NPCID,rowline.toUtf8());

                if(!IN_ADD_ALL.holdid2.contains(NPCID))
                {
                    //file.write("objectpacket::holdid2 does not contain ID");
                    //file.write("\n");
                    IN_ADD_ALL.holdid1.append(NPCID);

                    IN_ADD_ALL.holdx.append(NewX);
                    IN_ADD_ALL.holdz.append(NewZ);
                    IN_ADD_ALL.holdy.append(NewY);

                    IN_ADD_ALL.holdid2.append(NPCID);

                    IN_ADD_ALL.holdx2.append(NewX);
                    IN_ADD_ALL.holdz2.append(NewZ);
                    IN_ADD_ALL.holdy2.append(NewY);
                }




                QMap <QString,QVector <QString>> ZoneLocationsIDsVectorMap = checkthezone::VectorOFWorldsZones.value(IN_ADD_ALL.masterworld);

                QVector <QString> tempWorldZoneNamesVector = checkthezone::WorldZoneNamesVector.at(IN_ADD_ALL.masterworld);

                int ZoneNumber = tempWorldZoneNamesVector.indexOf(IN_ADD_ALL.LastZone);

                checkthezone::IDandZoneNumber.insert(NPCID,ZoneNumber);

                Opcodes::ID_PacketNumber_Map.insert(NPCID,QString::number(packetid));

                Name_PacketNumber_Map.insert(NewName,QString::number(packetid));

                checkthezone::IDsAndWorlds.insert(NPCID,IN_ADD_ALL.masterworld);

                checkthezone::NPCsNames.insert(NPCID,NewName);

                NPC_Map.insert(packetid,NewName);
            }


            QString ZonesName = IN_ADD_ALL.LastZone;

            ui->textEdit_13->append("NewName " + NewName);
            ui->textEdit_13->append("NPC_ID " + NPCID);
            ui->textEdit_13->append("packetid " + QString::number(packetid));
            ui->textEdit_13->append("World " + QString::number(IN_ADD_ALL.masterworld));
            ui->textEdit_13->append("ZoneNumber " + QString::number(ZoneNumber));
            ui->textEdit_13->append("ZonesName " + ZonesName);
            ui->textEdit_13->append("");


            QVector<QString> Subzone =
            {
                "(C)","(N)","(NE)","(NW)",
                "(S)","(SE)","(SW)","(W)","(E)"
            };

            for(int i = 0; i < Subzone.size(); i++)
            {
                QString ChopEnd = Subzone.at(i);

                if(ZonesName.contains(ChopEnd))
                {
                    int index = ZonesName.indexOf(ChopEnd);
                    ZonesName.remove(index-1,ChopEnd.size()+1);
                    break;
                }
            }

            Quests::NPCsName_ZoneMap.insert(NewName,ZonesName);


            qDebug() << "{" << NewName << "," << ZonesName << "},";


            QSqlQuery query;



            QString Table_Name = "ZONES_NAMES";

            Column_Name = "Packet (8)";
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",packetid);
            query.exec();

            if(!query.exec())
            {
                ui->lineEdit_20->setText(query.lastError().text());
                return;
            }


            QString Column_Name0 = "Packet (8)";


            Column_Name = "Name (24 Max)";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
            query.bindValue(":val",NewName);
            query.bindValue(":id",packetid);
            query.exec();

            if(!query.exec())
            {
                ui->lineEdit_20->setText(query.lastError().text());
                return;
            }

            Column_Name = "Location";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(Column_Name0));
            query.bindValue(":val",ZonesName);
            query.bindValue(":id",packetid);
            query.exec();

            if(!query.exec())
            {
                ui->lineEdit_20->setText(query.lastError().text());
                return;
            }


            QVector <QStringList> TempHoldsVector = checkthezone::Zones_IDXZYvectorMap.value(ZonesName);

            //file.write("TempHoldsVector.size() =  " + QString::number(TempHoldsVector.size()).toUtf8());
            //file.write("\n");

            QStringList holdid1;
            QStringList holdx;
            QStringList holdz;
            QStringList holdy;

            if(TempHoldsVector.isEmpty() == false)
            {
                holdid1 = TempHoldsVector.at(0);
                holdx = TempHoldsVector.at(1);
                holdz = TempHoldsVector.at(2);
                holdy = TempHoldsVector.at(3);
            }

            QVector <QString> LocationsIDsVector = checkthezone::ZoneLocationsIDsVectorMap.value(ZonesName);

            if(!LocationsIDsVector.contains(NPCID) && !reSpawnIDsMap.contains(NPCID))
            {
                LocationsIDsVector.append(NPCID);
                checkthezone::ZoneLocationsIDsVectorMap.insert(ZonesName,LocationsIDsVector);
                //qDebug() << "Did we get here12";
                checkthezone::VectorOFWorldsZones.replace(IN_ADD_ALL.masterworld,checkthezone::ZoneLocationsIDsVectorMap);
            }




            if(!holdid1.contains(NPCID))
            {
                holdid1.append(NPCID);
                holdx.append(NewX);
                holdz.append(NewZ);
                holdy.append(NewY);

                TempHoldsVector.append(holdid1);
                TempHoldsVector.append(holdx);
                TempHoldsVector.append(holdz);
                TempHoldsVector.append(holdy);

                checkthezone::Zones_IDXZYvectorMap.insert(ZonesName,TempHoldsVector);
            }
            else
            {
                int index = holdid1.indexOf(NPCID);

                //file.write("holdid1.indexOf(NPCID) =  " + QString::number(index).toUtf8());
                //file.write("\n");

                holdid1.replace(index,NPCID);
                holdx.replace(index,NewX);
                holdz.replace(index,NewZ);
                holdy.replace(index,NewY);


                if(TempHoldsVector.isEmpty() == false)
                {
                    TempHoldsVector.replace(0,holdid1);
                    TempHoldsVector.replace(1,holdx);
                    TempHoldsVector.replace(2,holdz);
                    TempHoldsVector.replace(3,holdy);
                }
                else
                {
                    TempHoldsVector.append(holdid1);
                    TempHoldsVector.append(holdx);
                    TempHoldsVector.append(holdz);
                    TempHoldsVector.append(holdy);
                }


                checkthezone::Zones_IDXZYvectorMap.insert(ZonesName,TempHoldsVector);
            }

            //file.write("\n");
            //file.close();
        }


        db.commit();

        packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_ADD_ALL);


        if(IN_ADD_ALL.Target_ID == IN_ADD_ALL.CharSelectID_Main && ui->checkBox_5->isChecked() == true)
        {
            break;
        }
    }
}

void MainWindow::on_pushButton_47_clicked()
{
    packetparsing::packetvars IN_pushButton_47;
    IN_pushButton_47 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    SpawnDefault = true;

    QString X_Val = ui->lineEdit_14->text().toUpper();
    QString Z_Val = ui->lineEdit_16->text().toUpper();
    QString Y_Val = ui->lineEdit_15->text().toUpper();
    QString F_Val = ui->lineEdit_17->text().toUpper();

    ui->X_4->setText(X_Val);
    ui->Z_4->setText(Z_Val);
    ui->Y_4->setText(Y_Val);
    ui->lineEdit_133->setText(F_Val);

    ui->lineEdit_45->setText(X_Val);
    ui->lineEdit_53->setText(Z_Val);
    ui->lineEdit_74->setText(Y_Val);
    ui->lineEdit_50->setText(F_Val);

    ui->lineEdit_9->setText("1");
    ui->lineEdit_125->setText("00");
    ui->lineEdit_126->setText("00");
    ui->lineEdit_127->setText("00");
    ui->lineEdit_128->setText("00");
    ui->lineEdit_24->setText("803F");
    ui->lineEdit_37->setText("803F");
    ui->lineEdit_26->setText("02");
    ui->lineEdit_79->setText("02");
    ui->lineEdit_54->setText("DF3ECA61");


    QString NewWorld = QString("%1").arg(IN_pushButton_47.masterworld,2,16,QLatin1Char('0'));
    ui->lineEdit_71->setText(NewWorld);

    ui->lineEdit_NPC_Name2->setText("4E6577204E50430000000000000000000000000000000000");
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_6->setCurrentIndex(IN_pushButton_47.masterworld);
    ui->comboBox_34->setCurrentIndex(0);

    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider_2->setValue(0);
    ui->horizontalSlider_3->setValue(0);
    ui->horizontalSlider_4->setValue(0);


    on_pushButton_65_clicked();
    on_pushButton_62_clicked();
    on_pushButton_76_clicked();
    on_pushButton_61_clicked();

}

void MainWindow::on_pushButton_48_clicked()
{
    packetparsing::packetvars IN_pushButton_48;
    IN_pushButton_48 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    if(ui->checkBox_40->isChecked() == true)
    {

        counter1++;

        QString Update_Value0 = ui->lineEdit_72->text();
        QString Update_Value1 = ui->lineEdit_39->text();
        QString Update_Value2 = ui->lineEdit_43->text();
        QString Update_Value3 = ui->lineEdit_48->text();
        QString Update_Value4 = ui->lineEdit_27->text();
        QString Update_Value5 = ui->lineEdit_49->text();
        QString Update_Value6 = ui->lineEdit_47->text();
        QString Update_Value7 = ui->lineEdit_124->text();
        QString Update_Value8 = ui->lineEdit_45->text();
        QString Update_Value9 = ui->lineEdit_53->text();
        QString Update_Value10 = ui->lineEdit_74->text();
        QString Update_Value11 = ui->lineEdit_50->text();
        QString Update_Value12 = ui->lineEdit_90->text();
        QString Update_Value13 = ui->lineEdit_130->text();
        QString Update_Value14_1 = ui->lineEdit_34->text();
        QString Update_Value14 = Update_Value14_1.mid(0,8);
        QString Update_Value15_1 = ui->lineEdit_28->text();
        QString Update_Value15 = Update_Value15_1.mid(0,8);
        QString Update_Value16_1 = ui->lineEdit_52->text();
        QString Update_Value16 = Update_Value16_1.mid(0,8);
        QString Update_Value17_1 = ui->lineEdit_76->text();
        QString Update_Value17 = Update_Value17_1.mid(0,8);
        QString Update_Value18_1 = ui->lineEdit_32->text();
        QString Update_Value18 = Update_Value18_1.mid(0,8);
        QString Update_Value19_1 = ui->lineEdit_41->text();
        QString Update_Value19 = Update_Value19_1.mid(0,8);
        QString Update_Value20 = ui->lineEdit_33->text();
        QString Update_Value21 = ui->lineEdit_125->text();
        QString Update_Value22 = ui->lineEdit_126->text();
        QString Update_Value23 = ui->lineEdit_127->text();
        QString Update_Value24 = ui->lineEdit_128->text();
        QString Update_Value25 = ui->lineEdit_122->text();

        QString NPC_Name = ui->lineEdit_NPC_Name2->text();

        QString NPC_Name1 = NPC_Name.mid(0,8);
        QString NPC_Name2 = NPC_Name.mid(8,8);
        QString NPC_Name3 = NPC_Name.mid(16,8);
        QString NPC_Name4 = NPC_Name.mid(24,8);
        QString NPC_Name5 = NPC_Name.mid(32,8);
        QString NPC_Name6 = NPC_Name.mid(40,8);

        QString Update_Value27 = ui->lineEdit_66->text();
        QString Update_Value28 = ui->lineEdit_79->text();
        QString Update_Value29 = ui->lineEdit_37->text();
        QString Update_Value30 = ui->lineEdit_73->text();
        QString Update_Value31 = ui->lineEdit_54->text();
        QString Update_Value32 = ui->lineEdit_62->text();
        QString Update_Value33 = ui->lineEdit_64->text();
        QString Update_Value34 = ui->lineEdit_63->text();
        QString Update_Value35 = ui->lineEdit_71->text();

        QString Update_Value95 = ui->lineEdit_95->text();
        QString Update_Value96 = ui->lineEdit_96->text();
        QString Update_Value97 = ui->lineEdit_97->text();
        QString Update_Value98 = ui->lineEdit_98->text();
        QString Update_Value99 = ui->lineEdit_99->text();
        QString Update_Value100 = ui->lineEdit_100->text();


        if(IN_pushButton_48.Target_ID == IN_pushButton_48.CharSelectID_Main && ui->checkBox_5->isChecked() == true)
        {
            IN_pushButton_48.current_c9 = generator::Players_Map.value(IN_pushButton_48.CharSelectID.toUtf8());
        }
        else
        {
            IN_pushButton_48.current_c9 = objectpacket::Master_Map.value(IN_pushButton_48.Target_ID);
        }

        QString OBjectID = IN_pushButton_48.current_c9.mid(2,8);
        QString X_OldVal1 = IN_pushButton_48.current_c9.mid(12,6);
        QString Z_OldVal1 = IN_pushButton_48.current_c9.mid(18,6);
        QString Y_OldVal1 = IN_pushButton_48.current_c9.mid(24,6);
        QString Facing_OldVal1 = IN_pushButton_48.current_c9.mid(30,2);
        QString World_OldVal1 = IN_pushButton_48.current_c9.mid(34,2);
        QString HP_OldVal1 = IN_pushButton_48.current_c9.mid(52,2);
        QString ModelID_OldVal1 = IN_pushButton_48.current_c9.mid(56,8);
        QString Size_OldVal1 = IN_pushButton_48.current_c9.mid(76,4);

        QString Primary_OldVal1 = IN_pushButton_48.current_c9.mid(134,8);
        QString Secondary_OldVal1 = IN_pushButton_48.current_c9.mid(142,8);
        QString Shield_OldVal1 = IN_pushButton_48.current_c9.mid(150,8);

        QString Torso_OldVal1 = IN_pushButton_48.current_c9.mid(186,2);
        QString Forearms_OldVal1 = IN_pushButton_48.current_c9.mid(188,2);
        QString Gloves_OldVal1 = IN_pushButton_48.current_c9.mid(190,2);
        QString Legs_OldVal1 = IN_pushButton_48.current_c9.mid(192,2);
        QString Feet_OldVal1 = IN_pushButton_48.current_c9.mid(194,2);
        QString Head_OldVal1 = IN_pushButton_48.current_c9.mid(196,2);

        QString TorsoC_OldVal1 = IN_pushButton_48.current_c9.mid(222,8);
        QString ForearmsC_OldVal1 = IN_pushButton_48.current_c9.mid(232,8);
        QString GlovesC_OldVal1 = IN_pushButton_48.current_c9.mid(242,8);
        QString LegsC_OldVal1 = IN_pushButton_48.current_c9.mid(252,8);
        QString FeetC_OldVal1 = IN_pushButton_48.current_c9.mid(262,8);
        QString HeadC_OldVal1 = IN_pushButton_48.current_c9.mid(272,8);
        QString RobeC_OldVal1 = IN_pushButton_48.current_c9.mid(282,8);

        QString HairColor_OldVal1 = IN_pushButton_48.current_c9.mid(290,2);//hair color
        QString HairLength_OldVal1 = IN_pushButton_48.current_c9.mid(292,2);//hair length
        QString HairStyle_OldVal1 = IN_pushButton_48.current_c9.mid(294,2);//hair style
        QString Face_OldVal1 = IN_pushButton_48.current_c9.mid(296,2);//face

        QString RobeType_OldVal1 = IN_pushButton_48.current_c9.mid(298,2);//robe type

        QString Race_OldVal1 = IN_pushButton_48.current_c9.mid(300,2);//race

        QString Name24Hex_OldVal = IN_pushButton_48.current_c9.mid(310,48);//name

        QString Name24Hex_OldVal1 = Name24Hex_OldVal.mid(0,8);
        QString Name24Hex_OldVal2 = Name24Hex_OldVal.mid(8,8);
        QString Name24Hex_OldVal3 = Name24Hex_OldVal.mid(16,8);
        QString Name24Hex_OldVal4 = Name24Hex_OldVal.mid(24,8);
        QString Name24Hex_OldVal5 = Name24Hex_OldVal.mid(32,8);
        QString Name24Hex_OldVal6 = Name24Hex_OldVal.mid(40,8);

        QString Level_OldVal1 = IN_pushButton_48.current_c9.mid(358,2);//level
        QString Class_OldVal1 = IN_pushButton_48.current_c9.mid(368,2);//class
        QString NPC_Type_OldVal1 = IN_pushButton_48.current_c9.mid(370,4);//NPC Type


        QString Unk1 = IN_pushButton_48.current_c9.mid(382,2);
        QString Unk2 = IN_pushButton_48.current_c9.mid(384,2);
        QString Unk3 = IN_pushButton_48.current_c9.mid(386,2);
        QString Unk4 = IN_pushButton_48.current_c9.mid(388,2);
        QString Unk5 = IN_pushButton_48.current_c9.mid(390,2);
        QString Unk6 = IN_pushButton_48.current_c9.mid(392,2);

        QByteArray Old_C9 = IN_pushButton_48.current_c9;
        QByteArray New_C9 = New_NPC_c9;


        Old_value = X_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value8.toUtf8();//--------------------------------X
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,6,16,QLatin1Char('0'));
        New_C9.replace(12,6,Output_Xor_2.toUtf8());//-----------------------X

        Old_value = Z_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value9.toUtf8();//--------------------------------Z
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,6,16,QLatin1Char('0'));
        New_C9.replace(18,6,Output_Xor_2.toUtf8());//-----------------------Z

        Old_value = Y_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value10.toUtf8();//--------------------------------Y
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,6,16,QLatin1Char('0'));
        New_C9.replace(24,6,Output_Xor_2.toUtf8());//-----------------------Y

        Old_value = Facing_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value11.toUtf8();//--------------------------------Facing
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(30,2,Output_Xor_2.toUtf8());//-----------------------Facing

        Old_value = World_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value35.toUtf8();//--------------------------------World
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(34,2,Output_Xor_2.toUtf8());//-----------------------World

        Old_value = HP_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value27.toUtf8();//--------------------------------HP
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(52,2,Output_Xor_2.toUtf8());//-----------------------HP

        Old_value = ModelID_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value31.toUtf8();//--------------------------------ModelID
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(56,8,Output_Xor_2.toUtf8());//-----------------------ModelID

        Old_value = Size_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value29.toUtf8();//--------------------------------Size
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,4,16,QLatin1Char('0'));
        New_C9.replace(76,4,Output_Xor_2.toUtf8());//-----------------------Size

        Old_value = Primary_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value32.toUtf8();//--------------------------------Primary
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(134,8,Output_Xor_2.toUtf8());//-----------------------Primary

        Old_value = Secondary_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value34.toUtf8();//--------------------------------Secondary
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(142,8,Output_Xor_2.toUtf8());//-----------------------Secondary

        Old_value = Shield_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value33.toUtf8();//--------------------------------Shield
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(150,8,Output_Xor_2.toUtf8());//-----------------------Shield

        Old_value = Torso_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value1.toUtf8();//--------------------------------Torso
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(186,2,Output_Xor_2.toUtf8());//-----------------------Torso

        Old_value = Forearms_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value2.toUtf8();//--------------------------------Forearms
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(188,2,Output_Xor_2.toUtf8());//-----------------------Forearms

        Old_value = Gloves_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value3.toUtf8();//--------------------------------Gloves
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(190,2,Output_Xor_2.toUtf8());//-----------------------Gloves

        Old_value = Legs_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value4.toUtf8();//--------------------------------Legs
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(192,2,Output_Xor_2.toUtf8());//-----------------------Legs

        Old_value = Feet_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value5.toUtf8();//--------------------------------Feet
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(194,2,Output_Xor_2.toUtf8());//-----------------------Feet

        Old_value = Head_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value6.toUtf8();//--------------------------------Head
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(196,2,Output_Xor_2.toUtf8());//-----------------------Head

        Old_value = TorsoC_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value14.toUtf8();//--------------------------------TorsoC
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(222,8,Output_Xor_2.toUtf8());//-----------------------TorsoC

        Old_value = ForearmsC_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value15.toUtf8();//--------------------------------ForearmsC
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(232,8,Output_Xor_2.toUtf8());//-----------------------ForearmsC

        Old_value = GlovesC_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value16.toUtf8();//--------------------------------GlovesC
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(242,8,Output_Xor_2.toUtf8());//-----------------------GlovesC

        Old_value = LegsC_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value17.toUtf8();//--------------------------------LegsC
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(252,8,Output_Xor_2.toUtf8());//-----------------------LegsC

        Old_value = FeetC_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value18.toUtf8();//--------------------------------FeetC
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(262,8,Output_Xor_2.toUtf8());//-----------------------FeetC

        Old_value = HeadC_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value19.toUtf8();//--------------------------------HeadC
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(272,8,Output_Xor_2.toUtf8());//-----------------------HeadC

        Old_value = RobeC_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value20.toUtf8();//--------------------------------RobeC
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(282,8,Output_Xor_2.toUtf8());//-----------------------RobeC

        Old_value = HairColor_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value24.toUtf8();//--------------------------------HairColor
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(290,2,Output_Xor_2.toUtf8());//-----------------------HairColor

        Old_value = HairLength_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value23.toUtf8();//--------------------------------HairLength
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(292,2,Output_Xor_2.toUtf8());//-----------------------HairLength

        Old_value = HairStyle_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value22.toUtf8();//--------------------------------HairStyle
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(294,2,Output_Xor_2.toUtf8());//-----------------------HairStyle

        Old_value = Face_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value21.toUtf8();//--------------------------------Face
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(296,2,Output_Xor_2.toUtf8());//-----------------------Face

        Old_value = RobeType_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value7.toUtf8();//--------------------------------RobeType
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(298,2,Output_Xor_2.toUtf8());//-----------------------RobeType

        Old_value = Race_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value12.toUtf8();//--------------------------------Race
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(300,2,Output_Xor_2.toUtf8());//-----------------------Race
        New_C9.replace(366,2,Output_Xor_2.toUtf8());//-----------------------Race

        // //////////////////////////////////////////////////////////////////////////////////////////////
        //       ///////////// Name sections //////////////////// ///////////////////////////////////////

        Old_value = Name24Hex_OldVal1.toLongLong(nullptr,16);
        New_value = NPC_Name1.toUtf8();//--------------------------------Name24Hex
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(310,8,Output_Xor_2.toUtf8());//-----------------------Name24Hex

        Old_value = Name24Hex_OldVal2.toLongLong(nullptr,16);
        New_value = NPC_Name2.toUtf8();//--------------------------------Name24Hex
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(318,8,Output_Xor_2.toUtf8());//-----------------------Name24Hex

        Old_value = Name24Hex_OldVal3.toLongLong(nullptr,16);
        New_value = NPC_Name3.toUtf8();//--------------------------------Name24Hex
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(326,8,Output_Xor_2.toUtf8());//-----------------------Name24Hex

        Old_value = Name24Hex_OldVal4.toLongLong(nullptr,16);
        New_value = NPC_Name4.toUtf8();//--------------------------------Name24Hex
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(334,8,Output_Xor_2.toUtf8());//-----------------------Name24Hex

        Old_value = Name24Hex_OldVal5.toLongLong(nullptr,16);
        New_value = NPC_Name5.toUtf8();//--------------------------------Name24Hex
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(342,8,Output_Xor_2.toUtf8());//-----------------------Name24Hex

        Old_value = Name24Hex_OldVal6.toLongLong(nullptr,16);
        New_value = NPC_Name6.toUtf8();//--------------------------------Name24Hex
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        New_C9.replace(350,8,Output_Xor_2.toUtf8());//-----------------------Name24Hex



        // //////////////////////////////////////////////////////////////////////////////////////////////
        //       ///////////// Name sections //////////////////// ///////////////////////////////////////

        Old_value = Level_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value28.toUtf8();//--------------------------------Level
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(358,2,Output_Xor_2.toUtf8());//-----------------------Level

        Old_value = Class_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value25.toUtf8();//--------------------------------Class
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(368,2,Output_Xor_2.toUtf8());//-----------------------Class



        Old_value = NPC_Type_OldVal1.toLongLong(nullptr,16);
        New_value = Update_Value30.toUtf8();//--------------------------------NPC_Type
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,4,16,QLatin1Char('0'));
        New_C9.replace(370,4,Output_Xor_2.toUtf8());//-----------------------NPC_Type

        Old_value = Update_Value95.toLongLong(nullptr,16);
        New_value = Unk1.toUtf8();//--------------------------------unk1
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(382,2,Output_Xor_2.toUtf8());//-----------------------Class

        Old_value = Update_Value96.toLongLong(nullptr,16);
        New_value = Unk2.toUtf8();//--------------------------------Class
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(384,2,Output_Xor_2.toUtf8());//-----------------------Class

        Old_value = Update_Value97.toLongLong(nullptr,16);
        New_value = Unk3.toUtf8();//--------------------------------Class
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(386,2,Output_Xor_2.toUtf8());//-----------------------Class

        Old_value = Update_Value98.toLongLong(nullptr,16);
        New_value = Unk4.toUtf8();//--------------------------------Class
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(388,2,Output_Xor_2.toUtf8());//-----------------------Class

        Old_value = Update_Value99.toLongLong(nullptr,16);
        New_value = Unk5.toUtf8();//--------------------------------Class
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(390,2,Output_Xor_2.toUtf8());//-----------------------Class

        Old_value = Update_Value100.toLongLong(nullptr,16);
        New_value = Unk6.toUtf8();//--------------------------------Class
        New_value2 = New_value.toLongLong(nullptr,16);
        Output_Xor = Old_value ^ New_value2;
        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
        New_C9.replace(392,2,Output_Xor_2.toUtf8());//-----------------------Class


        Old_C9.replace(12,6,Update_Value8.toUtf8());//x
        Old_C9.replace(18,6,Update_Value9.toUtf8());//z
        Old_C9.replace(24,6,Update_Value10.toUtf8());//y
        Old_C9.replace(30,2,Update_Value11.toUtf8());//facing
        Old_C9.replace(34,2,Update_Value35.toUtf8());//world
        Old_C9.replace(52,2,Update_Value27.toUtf8());//hp
        Old_C9.replace(56,8,Update_Value31.toUtf8());//modelid
        Old_C9.replace(76,4,Update_Value29.toUtf8());//size
        Old_C9.replace(134,8,Update_Value32.toUtf8());//primary
        Old_C9.replace(142,8,Update_Value34.toUtf8());//secondary
        Old_C9.replace(150,8,Update_Value33.toUtf8());//shield
        Old_C9.replace(186,2,Update_Value1.toUtf8());//torso
        Old_C9.replace(188,2,Update_Value2.toUtf8());//forearms
        Old_C9.replace(190,2,Update_Value3.toUtf8());//gloves
        Old_C9.replace(192,2,Update_Value4.toUtf8());//legs
        Old_C9.replace(194,2,Update_Value5.toUtf8());//feet
        Old_C9.replace(196,2,Update_Value6.toUtf8());//head
        Old_C9.replace(222,8,Update_Value14.toUtf8());//torsocolor
        Old_C9.replace(232,8,Update_Value15.toUtf8());//forearmscolor
        Old_C9.replace(242,8,Update_Value16.toUtf8());//glovescolor
        Old_C9.replace(252,8,Update_Value17.toUtf8());//legscolor
        Old_C9.replace(262,8,Update_Value18.toUtf8());//feetcolor
        Old_C9.replace(272,8,Update_Value19.toUtf8());//headcolor
        Old_C9.replace(282,8,Update_Value20.toUtf8());//robecolor
        Old_C9.replace(290,2,Update_Value24.toUtf8());//haircolor
        Old_C9.replace(292,2,Update_Value23.toUtf8());//hairlength
        Old_C9.replace(294,2,Update_Value22.toUtf8());//hairstyle
        Old_C9.replace(296,2,Update_Value21.toUtf8());//face
        Old_C9.replace(298,2,Update_Value7.toUtf8());//robetype
        Old_C9.replace(300,2,Update_Value12.toUtf8());//race


        Old_C9.replace(310,8,NPC_Name1.toUtf8());//name
        Old_C9.replace(318,8,NPC_Name2.toUtf8());//name
        Old_C9.replace(326,8,NPC_Name3.toUtf8());//name
        Old_C9.replace(334,8,NPC_Name4.toUtf8());//name
        Old_C9.replace(342,8,NPC_Name5.toUtf8());//name
        Old_C9.replace(350,8,NPC_Name6.toUtf8());//name

        Old_C9.replace(358,2,Update_Value28.toUtf8());//level
        Old_C9.replace(366,2,Update_Value12.toUtf8());//race2
        Old_C9.replace(368,2,Update_Value25.toUtf8());//class
        Old_C9.replace(370,4,Update_Value30.toUtf8());//npctype
        Old_C9.replace(382,2,Update_Value95.toUtf8());
        Old_C9.replace(382,2,Update_Value96.toUtf8());
        Old_C9.replace(382,2,Update_Value97.toUtf8());
        Old_C9.replace(382,2,Update_Value98.toUtf8());
        Old_C9.replace(382,2,Update_Value99.toUtf8());
        Old_C9.replace(382,2,Update_Value100.toUtf8());


        xorpacket packet2;
        QByteArray Recompressed2 = packet2.packetencrypt(New_C9);


        if(IN_pushButton_48.Target_ID == IN_pushButton_48.CharSelectID_Main && ui->checkBox_5->isChecked() == true)
        {
            generator::Players_Map.insert(IN_pushButton_48.CharSelectID.toUtf8(),Old_C9);

            QString mainid4 = IN_pushButton_48.CharSelectID;
            generator packet4;
            QByteArray holdergen = packet4.maintoonswitch(mainid4,"",IN_pushButton_48.CharSelectID_Main); //send the id we want to get a 00c9
            holdergen.insert(0,"00c9030000");

            IN_pushButton_48.SendZeroChannelVector.append(holdergen);
        }
        else
        {

            ////////////_______NPC_Updated_______/////////////////


            QString Current_channel = IN_pushButton_48.Map_Channel_ID.key(IN_pushButton_48.Target_ID);

            holderDespawn = "01c9xxxx01" + Recompressed2;

            holderDespawn.replace(0,2,Current_channel.toUtf8().toUpper());

            //qDebug() << "MapOfChannelVectors5" << MapOfChannelVectors;


            QByteArray Channel = holderDespawn.mid(0,2);
            QVector <QByteArray> CurrenChannelVector = IN_pushButton_48.MapOfChannelVectors.value(Channel);
            CurrenChannelVector.append(holderDespawn);
            IN_pushButton_48.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

            //qDebug() << "MapOfChannelVectors5" << MapOfChannelVectors;



            ////////////_______NPC_Updated_______/////////////////





            objectpacket::Master_Map.insert(IN_pushButton_48.Target_ID,Old_C9);

            int removid = objectpacket::holdid1.indexOf(IN_pushButton_48.Target_ID);
            int removid2 = IN_pushButton_48.holdid2.indexOf(IN_pushButton_48.Target_ID);

            if(removid != -1)
            {
                objectpacket::holdid1.replace(removid,IN_pushButton_48.Target_ID);
                objectpacket::holdx.replace(removid,Update_Value8);
                objectpacket::holdz.replace(removid,Update_Value9);
                objectpacket::holdy.replace(removid,Update_Value10);
            }


            if(removid2 != -1)
            {
                IN_pushButton_48.holdid2.replace(removid2,IN_pushButton_48.Target_ID);
                IN_pushButton_48.holdx2.replace(removid2,Update_Value8);
                IN_pushButton_48.holdz2.replace(removid2,Update_Value9);
                IN_pushButton_48.holdy2.replace(removid2,Update_Value10);
            }
        }

        ui->pushButton_61->setStyleSheet("background-color: blue;" "color: white;");
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_pushButton_48);


}



//Edit mode
void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    if(arg1 == 2)
    {

        ui->tabWidget->setCurrentIndex(4);
        ui->tabWidget_2->setCurrentIndex(0);
        ui->tabWidget_3->setCurrentIndex(4);

        ui->pushButton_25->setDisabled(true);
        ui->checkBox_9->setChecked(false);
        ui->checkBox_6->setChecked(false);
        ui->pushButton_47->setDisabled(true);
        ui->pushButton_17->setDisabled(true);
        ui->pushButton_48->setDisabled(false);
        ui->pushButton_61->setDisabled(false);
        ui->pushButton_26->setDisabled(false);
        ui->pushButton_27->setDisabled(false);


    }
    else
    {
        ui->checkBox_5->setChecked(false);
    }
}

//Creation mode
void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->tabWidget->setCurrentIndex(4);
        ui->tabWidget_2->setCurrentIndex(0);
        ui->tabWidget_3->setCurrentIndex(4);
        ui->pushButton_25->setDisabled(false);
        ui->checkBox_9->setChecked(false);
        ui->checkBox_7->setChecked(false);
        ui->checkBox_5->setChecked(false);
        ui->pushButton_47->setDisabled(false);
        ui->pushButton_17->setDisabled(false);
        ui->pushButton_48->setDisabled(true);
        ui->pushButton_61->setDisabled(false);
        ui->pushButton_26->setDisabled(true);
        ui->pushButton_27->setDisabled(true);

    }
}


void MainWindow::on_lineEdit_68_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->lineEdit_83->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));

        ui->lineEdit_83->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}

void MainWindow::on_lineEdit_75_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->lineEdit_84->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));

        ui->lineEdit_84->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}

void MainWindow::on_lineEdit_81_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->lineEdit_85->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));

        ui->lineEdit_85->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}

void MainWindow::on_lineEdit_78_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->lineEdit_86->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));

        ui->lineEdit_86->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}

void MainWindow::on_lineEdit_67_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->lineEdit_87->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));

        ui->lineEdit_87->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}

void MainWindow::on_lineEdit_77_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->lineEdit_88->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));

        ui->lineEdit_88->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}

void MainWindow::on_lineEdit_82_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->lineEdit_89->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));

        ui->lineEdit_89->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}



void MainWindow::on_pushButton_56_clicked()
{
    ui->lineEdit_7->setText("00");
    ui->lineEdit_39->setText("00");

    ArmorPositionVector.replace(0,0);

    int Index = ui->horizontalSlider_7->value();

    if(Index == 0)
    {
        ui->verticalSlider_6->setValue(0);
    }
    else
    {
        ui->horizontalSlider_7->setValue(0);
        ui->verticalSlider_6->setValue(0);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_57_clicked()
{
    ui->lineEdit_36->setText("00");
    ui->lineEdit_43->setText("00");

    ArmorPositionVector.replace(1,0);

    int Index = ui->horizontalSlider_7->value();

    if(Index == 1)
    {
        ui->verticalSlider_6->setValue(0);
    }
    else
    {
        ui->horizontalSlider_7->setValue(1);
        ui->verticalSlider_6->setValue(0);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_58_clicked()
{
    ui->lineEdit_38->setText("00");
    ui->lineEdit_48->setText("00");

    ArmorPositionVector.replace(2,0);

    int Index = ui->horizontalSlider_7->value();

    if(Index == 2)
    {
        ui->verticalSlider_6->setValue(0);
    }
    else
    {
        ui->horizontalSlider_7->setValue(2);
        ui->verticalSlider_6->setValue(0);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_59_clicked()
{
    ui->lineEdit_46->setText("00");
    ui->lineEdit_27->setText("00");

    ArmorPositionVector.replace(3,0);

    int Index = ui->horizontalSlider_7->value();

    if(Index == 3)
    {
        ui->verticalSlider_6->setValue(0);
    }
    else
    {
        ui->horizontalSlider_7->setValue(3);
        ui->verticalSlider_6->setValue(0);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_60_clicked()
{
    ui->lineEdit_40->setText("00");
    ui->lineEdit_49->setText("00");

    ArmorPositionVector.replace(4,0);

    int Index = ui->horizontalSlider_7->value();

    if(Index == 4)
    {
        ui->verticalSlider_6->setValue(0);
    }
    else
    {
        ui->horizontalSlider_7->setValue(4);
        ui->verticalSlider_6->setValue(0);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_63_clicked()
{
    ui->lineEdit_42->setText("00");
    ui->lineEdit_47->setText("00");

    ArmorPositionVector.replace(5,0);

    int Index = ui->horizontalSlider_7->value();

    if(Index == 5)
    {
        ui->verticalSlider_6->setValue(0);
    }
    else
    {
        ui->horizontalSlider_7->setValue(5);
        ui->verticalSlider_6->setValue(0);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_64_clicked()
{
    ui->lineEdit_44->setText("FF");
    ui->lineEdit_124->setText("FF");

    ArmorPositionVector.replace(6,0);

    int Index = ui->horizontalSlider_7->value();

    if(Index == 6)
    {
        ui->verticalSlider_6->setValue(0);
    }
    else
    {
        ui->horizontalSlider_7->setValue(6);
        ui->verticalSlider_6->setValue(0);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_31_clicked()
{
    ui->lineEdit_39->setText("00");
    ui->lineEdit_43->setText("00");
    ui->lineEdit_48->setText("00");
    ui->lineEdit_27->setText("00");
    ui->lineEdit_49->setText("00");
    ui->lineEdit_47->setText("00");
    ui->lineEdit_124->setText("FF");

    ui->lineEdit_7->setText("00");
    ui->lineEdit_36->setText("00");
    ui->lineEdit_38->setText("00");
    ui->lineEdit_46->setText("00");
    ui->lineEdit_40->setText("00");
    ui->lineEdit_42->setText("00");
    ui->lineEdit_44->setText("FF");

    ui->horizontalSlider_7->setValue(0);
    ui->verticalSlider_6->setValue(0);

    ArmorPositionVector =
    {
        0,0,0,0,0,0,0
    };

    if(ui->radioButton_41->isChecked() == false)
    {
        ui->radioButton_41->setChecked(true);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->lineEdit_34->setText("FFFFFFFF");
    ui->lineEdit_28->setText("FFFFFFFF");
    ui->lineEdit_52->setText("FFFFFFFF");
    ui->lineEdit_76->setText("FFFFFFFF");
    ui->lineEdit_32->setText("FFFFFFFF");
    ui->lineEdit_41->setText("FFFFFFFF");
    ui->lineEdit_33->setText("FFFFFFFF");

    ui->lineEdit_68->setText("FFFFFFFF");
    ui->lineEdit_75->setText("FFFFFFFF");
    ui->lineEdit_81->setText("FFFFFFFF");
    ui->lineEdit_78->setText("FFFFFFFF");
    ui->lineEdit_67->setText("FFFFFFFF");
    ui->lineEdit_77->setText("FFFFFFFF");
    ui->lineEdit_82->setText("FFFFFFFF");

    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_65_clicked()
{
    ui->lineEdit_39->setText("00");
    ui->lineEdit_43->setText("00");
    ui->lineEdit_48->setText("00");
    ui->lineEdit_27->setText("00");
    ui->lineEdit_49->setText("00");
    ui->lineEdit_47->setText("00");
    ui->lineEdit_124->setText("FF");

    ui->lineEdit_7->setText("00");
    ui->lineEdit_36->setText("00");
    ui->lineEdit_38->setText("00");
    ui->lineEdit_46->setText("00");
    ui->lineEdit_40->setText("00");
    ui->lineEdit_42->setText("00");
    ui->lineEdit_44->setText("FF");

    if(ui->radioButton_41->isChecked() == false)
    {
        ui->radioButton_41->setChecked(true);
    }

    ui->lineEdit_34->setText("FFFFFFFF");
    ui->lineEdit_28->setText("FFFFFFFF");
    ui->lineEdit_52->setText("FFFFFFFF");
    ui->lineEdit_76->setText("FFFFFFFF");
    ui->lineEdit_32->setText("FFFFFFFF");
    ui->lineEdit_41->setText("FFFFFFFF");
    ui->lineEdit_33->setText("FFFFFFFF");

    ui->lineEdit_68->setText("FFFFFFFF");
    ui->lineEdit_75->setText("FFFFFFFF");
    ui->lineEdit_81->setText("FFFFFFFF");
    ui->lineEdit_78->setText("FFFFFFFF");
    ui->lineEdit_67->setText("FFFFFFFF");
    ui->lineEdit_77->setText("FFFFFFFF");
    ui->lineEdit_82->setText("FFFFFFFF");


    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_33_clicked()
{
    ui->lineEdit_7->setText("01");
    ui->lineEdit_36->setText("01");
    ui->lineEdit_38->setText("01");
    ui->lineEdit_46->setText("01");
    ui->lineEdit_40->setText("01");
    ui->lineEdit_42->setText("01");

    ui->lineEdit_39->setText("01");
    ui->lineEdit_43->setText("01");
    ui->lineEdit_48->setText("01");
    ui->lineEdit_27->setText("01");
    ui->lineEdit_49->setText("01");
    ui->lineEdit_47->setText("01");

    ArmorPositionVector.replace(0,1);
    ArmorPositionVector.replace(1,1);
    ArmorPositionVector.replace(2,1);
    ArmorPositionVector.replace(3,1);
    ArmorPositionVector.replace(4,1);
    ArmorPositionVector.replace(5,1);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(1);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_34_clicked()
{
    ui->lineEdit_7->setText("02");
    ui->lineEdit_36->setText("02");
    ui->lineEdit_38->setText("02");
    ui->lineEdit_46->setText("02");
    ui->lineEdit_40->setText("02");
    ui->lineEdit_42->setText("02");

    ui->lineEdit_39->setText("02");
    ui->lineEdit_43->setText("02");
    ui->lineEdit_48->setText("02");
    ui->lineEdit_27->setText("02");
    ui->lineEdit_49->setText("02");
    ui->lineEdit_47->setText("02");

    ArmorPositionVector.replace(0,2);
    ArmorPositionVector.replace(1,2);
    ArmorPositionVector.replace(2,2);
    ArmorPositionVector.replace(3,2);
    ArmorPositionVector.replace(4,2);
    ArmorPositionVector.replace(5,2);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(2);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_35_clicked()
{
    ui->lineEdit_7->setText("03");
    ui->lineEdit_36->setText("03");
    ui->lineEdit_38->setText("03");
    ui->lineEdit_46->setText("03");
    ui->lineEdit_40->setText("03");
    ui->lineEdit_42->setText("03");

    ui->lineEdit_39->setText("03");
    ui->lineEdit_43->setText("03");
    ui->lineEdit_48->setText("03");
    ui->lineEdit_27->setText("03");
    ui->lineEdit_49->setText("03");
    ui->lineEdit_47->setText("03");

    ArmorPositionVector.replace(0,3);
    ArmorPositionVector.replace(1,3);
    ArmorPositionVector.replace(2,3);
    ArmorPositionVector.replace(3,3);
    ArmorPositionVector.replace(4,3);
    ArmorPositionVector.replace(5,3);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(3);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_37_clicked()
{
    ui->lineEdit_7->setText("04");
    ui->lineEdit_36->setText("04");
    ui->lineEdit_38->setText("04");
    ui->lineEdit_46->setText("04");
    ui->lineEdit_40->setText("04");
    ui->lineEdit_42->setText("04");

    ui->lineEdit_39->setText("04");
    ui->lineEdit_43->setText("04");
    ui->lineEdit_48->setText("04");
    ui->lineEdit_27->setText("04");
    ui->lineEdit_49->setText("04");
    ui->lineEdit_47->setText("04");

    ArmorPositionVector.replace(0,4);
    ArmorPositionVector.replace(1,4);
    ArmorPositionVector.replace(2,4);
    ArmorPositionVector.replace(3,4);
    ArmorPositionVector.replace(4,4);
    ArmorPositionVector.replace(5,4);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(4);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_38_clicked()
{
    ui->lineEdit_7->setText("05");
    ui->lineEdit_36->setText("05");
    ui->lineEdit_38->setText("05");
    ui->lineEdit_46->setText("05");
    ui->lineEdit_40->setText("05");
    ui->lineEdit_42->setText("05");

    ui->lineEdit_39->setText("05");
    ui->lineEdit_43->setText("05");
    ui->lineEdit_48->setText("05");
    ui->lineEdit_27->setText("05");
    ui->lineEdit_49->setText("05");
    ui->lineEdit_47->setText("05");

    ArmorPositionVector.replace(0,5);
    ArmorPositionVector.replace(1,5);
    ArmorPositionVector.replace(2,5);
    ArmorPositionVector.replace(3,5);
    ArmorPositionVector.replace(4,5);
    ArmorPositionVector.replace(5,5);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(5);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_36_clicked()
{
    ui->lineEdit_7->setText("06");
    ui->lineEdit_36->setText("06");
    ui->lineEdit_38->setText("06");
    ui->lineEdit_46->setText("06");
    ui->lineEdit_40->setText("06");
    ui->lineEdit_42->setText("06");

    ui->lineEdit_39->setText("06");
    ui->lineEdit_43->setText("06");
    ui->lineEdit_48->setText("06");
    ui->lineEdit_27->setText("06");
    ui->lineEdit_49->setText("06");
    ui->lineEdit_47->setText("06");

    ArmorPositionVector.replace(0,6);
    ArmorPositionVector.replace(1,6);
    ArmorPositionVector.replace(2,6);
    ArmorPositionVector.replace(3,6);
    ArmorPositionVector.replace(4,6);
    ArmorPositionVector.replace(5,6);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(6);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_39_clicked()
{
    ui->lineEdit_7->setText("07");
    ui->lineEdit_36->setText("07");
    ui->lineEdit_38->setText("07");
    ui->lineEdit_46->setText("07");
    ui->lineEdit_40->setText("07");
    ui->lineEdit_42->setText("07");

    ui->lineEdit_39->setText("07");
    ui->lineEdit_43->setText("07");
    ui->lineEdit_48->setText("07");
    ui->lineEdit_27->setText("07");
    ui->lineEdit_49->setText("07");
    ui->lineEdit_47->setText("07");

    ArmorPositionVector.replace(0,7);
    ArmorPositionVector.replace(1,7);
    ArmorPositionVector.replace(2,7);
    ArmorPositionVector.replace(3,7);
    ArmorPositionVector.replace(4,7);
    ArmorPositionVector.replace(5,7);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(7);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_40_clicked()
{
    ui->lineEdit_7->setText("08");
    ui->lineEdit_36->setText("08");
    ui->lineEdit_38->setText("08");
    ui->lineEdit_46->setText("08");
    ui->lineEdit_40->setText("08");
    ui->lineEdit_42->setText("08");

    ui->lineEdit_39->setText("08");
    ui->lineEdit_43->setText("08");
    ui->lineEdit_48->setText("08");
    ui->lineEdit_27->setText("08");
    ui->lineEdit_49->setText("08");
    ui->lineEdit_47->setText("08");

    ArmorPositionVector.replace(0,8);
    ArmorPositionVector.replace(1,8);
    ArmorPositionVector.replace(2,8);
    ArmorPositionVector.replace(3,8);
    ArmorPositionVector.replace(4,8);
    ArmorPositionVector.replace(5,8);

    if(ui->horizontalSlider_7->value() != 6)
    {
        ui->verticalSlider_6->setValue(8);
    }

    on_pushButton_48_clicked();
}

void MainWindow::on_radioButton_41_clicked()
{
    on_pushButton_31_clicked();
}

void MainWindow::on_pushButton_66_clicked()
{
    ui->lineEdit_34->setText("FFFFFFFF00");
    ui->lineEdit_68->setText("FFFFFFFF");
    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_67_clicked()
{
    ui->lineEdit_28->setText("FFFFFFFF00");
    ui->lineEdit_75->setText("FFFFFFFF");
    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_68_clicked()
{
    ui->lineEdit_52->setText("FFFFFFFF00");
    ui->lineEdit_81->setText("FFFFFFFF");
    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_69_clicked()
{
    ui->lineEdit_76->setText("FFFFFFFF00");
    ui->lineEdit_78->setText("FFFFFFFF");
    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_70_clicked()
{
    ui->lineEdit_32->setText("FFFFFFFF00");
    ui->lineEdit_67->setText("FFFFFFFF");
    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_71_clicked()
{
    ui->lineEdit_41->setText("FFFFFFFF00");
    ui->lineEdit_77->setText("FFFFFFFF");
    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_77_clicked()
{
    ui->lineEdit_33->setText("FFFFFFFF00");
    ui->lineEdit_82->setText("FFFFFFFF");
    on_pushButton_48_clicked();
}






void MainWindow::on_lineEdit_34_textChanged(const QString &arg1)
{
    if(arg1.size() <= 8)
    {
        ui->lineEdit_34->setText(arg1 + "00");
    }
}

void MainWindow::on_lineEdit_28_textChanged(const QString &arg1)
{
    if(arg1.size() <= 8)
    {
        ui->lineEdit_28->setText(arg1 + "00");
    }
}

void MainWindow::on_lineEdit_52_textChanged(const QString &arg1)
{
    if(arg1.size() <= 8)
    {
        ui->lineEdit_52->setText(arg1 + "00");
    }
}

void MainWindow::on_lineEdit_76_textChanged(const QString &arg1)
{
    if(arg1.size() <= 8)
    {
        ui->lineEdit_76->setText(arg1 + "00");
    }
}

void MainWindow::on_lineEdit_32_textChanged(const QString &arg1)
{
    if(arg1.size() <= 8)
    {
        ui->lineEdit_32->setText(arg1 + "00");
    }
}

void MainWindow::on_lineEdit_41_textChanged(const QString &arg1)
{
    if(arg1.size() <= 8)
    {
        ui->lineEdit_41->setText(arg1 + "00");
    }
}

void MainWindow::on_checkBox_9_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->pushButton_25->setDisabled(true);
        ui->checkBox_6->setChecked(false);
        ui->checkBox_5->setChecked(false);
        ui->checkBox_7->setChecked(false);
        ui->pushButton_47->setDisabled(true);
        ui->pushButton_48->setDisabled(true);
        ui->pushButton_61->setDisabled(true);
        ui->pushButton_26->setDisabled(true);
        ui->pushButton_27->setDisabled(true);
    }
}

void MainWindow::on_pushButton_76_clicked()
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////




    QSqlQuery query ("SELECT COUNT (*) FROM NPCS");

    while(query.next())
    {
        ui->lineEdit_72->setText(query.value(0).toString());
    }

    Packet_ID = ui->lineEdit_72->text().toUtf8();

    //qDebug() << "Packet_ID" << Packet_ID;

    int Packet_ID2 = Packet_ID.toInt(nullptr,10);
    int Packet_ID3 = Packet_ID2 + 1;
    QByteArray Packet_ID4 = Packet_ID4.number(Packet_ID3,10);
    ui->lineEdit_72->setText(Packet_ID4);


    ui->lineEdit_130->setText(NewspawnID.toUpper());


    QByteArray NPCID = "";

    QString NewNPC = "";


    if(ui->checkBox_14->isChecked() == true)
    {
        NewNPC = NPCsNewOrNotVector.at(0);

        if(NewNPC == "YES")
        {
            NPCID = "XXXXXXXX";
            NPCsNewIDVector.replace(0,NPCID);

        }

    }
    else
    {
        NPCID = ui->lineEdit_130->text().toUtf8().toUpper();
    }
    QByteArray New_Char_ID = "";

    if(SpawnClone == false && SpawnDBClone == false && SpawnDefault == false)
    {

    }

    if(SpawnClone == true || SpawnDBClone == true || SpawnDefault == true || NPCID == "XXXXXXXX")
    {
        SpawnClone = false;
        SpawnDBClone = false;
        SpawnDefault = false;

        NPCID = ui->lineEdit_130->text().toUtf8().toUpper();

        QByteArray split1 = NPCID; //AAAABBBB

        QByteArray first_4_digits = split1.mid(0,4); //AAAA
        QByteArray last_4_digits = split1.mid(4,4); //BBBB

        increment first1; //get class object
        QByteArray firstresult1 = first1.count(first_4_digits).toUpper(); //ABAA

        if(firstresult1 == "0000")
        {
            first_4_digits = "0000";

            increment second1; //get class object
            QByteArray secondresult1 = second1.count(last_4_digits).toUpper(); //if first is FFFF this will be BCBB //secondresult is bytearray in header
            New_Char_ID = firstresult1 + secondresult1.toUpper();
            NewspawnID = New_Char_ID;
            ui->lineEdit_130->setText(New_Char_ID);
        }
        else
        {
            New_Char_ID = firstresult1 + last_4_digits.toUpper();
            NewspawnID = New_Char_ID;
            ui->lineEdit_130->setText(New_Char_ID);
        }

        if(Opcodes::ID_PacketNumber_Map.contains(New_Char_ID))
        {
            do
            {
                QByteArray FirstHalf = New_Char_ID.mid(0,4);

                increment Sendto;
                QByteArray FirstHalf1 = Sendto.count(FirstHalf);

                New_Char_ID.replace(0,4,FirstHalf1);
                NewspawnID = New_Char_ID;
                ui->lineEdit_130->setText(New_Char_ID);

            }while(Opcodes::ID_PacketNumber_Map.contains(New_Char_ID));
        }

        StartingIDXZYF.append(New_Char_ID);
        EndingIDXZYF.append(New_Char_ID);
        IsItNew.append("YES");
    }

}



void MainWindow::on_pushButton_80_clicked()
{
    packetparsing::packetvars IN_pushButton_80;
    IN_pushButton_80 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray current_c9 = generator::Players_Map.value(IN_pushButton_80.CharSelectID.toUtf8());
    QString Animation = ui->lineEdit_101->text().toUpper();

    current_c9.replace(182,4,Animation.toUtf8());

    generator::Players_Map.insert(IN_pushButton_80.CharSelectID.toUtf8(),current_c9);

    generator packet4;
    QByteArray holdergen1 = packet4.maintoonswitch(IN_pushButton_80.CharSelectID,"",IN_pushButton_80.CharSelectID_Main);
    QByteArray holdergen2 = "00C9030000" + holdergen1;

    IN_pushButton_80.SendZeroChannelVector.append(holdergen2);

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_pushButton_80);

}


void MainWindow::on_lineEdit_NPC_Name2_textChanged(const QString &arg1)
{


    QByteArray arg2 = arg1.toUtf8();

    int Mysize = arg1.size();
    QByteArray backtotext = arg2.mid(0,Mysize * 2);
    QString textout = backtotext.fromHex(backtotext);
    ui->lineEdit_NPC_Name_2->setText(textout);
    ui->lineEdit_NPC_Name->setText(textout);
}



void MainWindow::on_Mob_Models_3_textChanged(const QString &arg1)
{
    ui->Mob_Models_3->setText(arg1);

    if(ui->checkBox_3->isChecked() == true)
    {
        ui->Mob_model->setText(arg1);
    }

    if(SliderUsed == "NO")
    {
        if(MobBox1_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(0);
            int Index = MobBox1_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox2_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(1);
            int Index = MobBox2_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox3_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(2);
            int Index = MobBox3_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox4_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(3);
            int Index = MobBox4_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox5_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(4);
            int Index = MobBox5_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox6_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(5);
            int Index = MobBox6_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox7_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(6);
            int Index = MobBox7_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox8_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(7);
            int Index = MobBox8_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox9_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(8);
            int Index = MobBox9_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox10_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(9);
            int Index = MobBox10_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox11_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(10);
            int Index = MobBox11_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox12_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(11);
            int Index = MobBox12_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox13_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(12);
            int Index = MobBox13_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }

        if(MobBox14_Index.contains(arg1))
        {
            ui->horizontalSlider_5->setValue(13);
            int Index = MobBox14_Index.indexOf(arg1);
            ui->verticalSlider->setValue(Index);
        }
    }

    if(ui->tabWidget->currentIndex() == 3)
    {
        ui->lineEdit_54->setText(arg1);

        on_pushButton_48_clicked();
    }
}







void MainWindow::on_pushButton_14_clicked()
{
    color = QColorDialog::getColor(Qt::white,this);

    ui->lineEdit_68->setText(color.name().toUpper());
    QString Gear_Color = ui->lineEdit_68->text().toUpper();
    Gear_Color.remove(0,1);
    Gear_Color.append("FF");


    ui->lineEdit_34->setText(Gear_Color);
    ui->lineEdit_28->setText(Gear_Color);
    ui->lineEdit_52->setText(Gear_Color);
    ui->lineEdit_76->setText(Gear_Color);
    ui->lineEdit_32->setText(Gear_Color);
    ui->lineEdit_41->setText(Gear_Color);
    ui->lineEdit_34->setText(Gear_Color);

    ui->lineEdit_68->setText(Gear_Color);
    ui->lineEdit_75->setText(Gear_Color);
    ui->lineEdit_81->setText(Gear_Color);
    ui->lineEdit_78->setText(Gear_Color);
    ui->lineEdit_67->setText(Gear_Color);
    ui->lineEdit_77->setText(Gear_Color);
    ui->lineEdit_82->setText(Gear_Color);

    on_pushButton_48_clicked();
}



void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->tabWidget_3->currentIndex() == 0)
    {
        ui->horizontalSlider->setValue(0);
        ui->horizontalSlider_2->setValue(4);
        ui->horizontalSlider_3->setValue(8);
        ui->horizontalSlider_4->setValue(12);
        ui->verticalSlider_5->setValue(0);

        ui->lineEdit_54->setText(arg1.toUpper());
        ui->lineEdit_8->setText(arg1.toUpper());
        on_pushButton_48_clicked();
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    on_pushButton_48_clicked();
}

void MainWindow::on_lineEdit_26_textChanged(const QString &arg1)
{
    if(ui->tabWidget_3->currentIndex() == 0)
    {
        ui->lineEdit_79->setText(arg1);
    }
    else
    {
        int temp = arg1.toInt(nullptr,16);
        QString value = QString("%1").arg(temp,1,10,QLatin1Char('0')).toUpper();
        ui->lineEdit_9->setText(value);
    }


}

void MainWindow::on_pushButton_16_clicked()
{
    packetparsing::packetvars IN_pushButton_16;
    IN_pushButton_16 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    QString X_Val = ui->lineEdit_14->text().toUpper();
    QString Z_Val = ui->lineEdit_16->text().toUpper();
    QString Y_Val = ui->lineEdit_15->text().toUpper();
    QString F_Val = ui->lineEdit_17->text().toUpper();

    ui->X_4->setText(X_Val);
    ui->Z_4->setText(Z_Val);
    ui->Y_4->setText(Y_Val);
    ui->lineEdit_133->setText(F_Val);

    ui->lineEdit_45->setText(X_Val);
    ui->lineEdit_53->setText(Z_Val);
    ui->lineEdit_74->setText(Y_Val);
    ui->lineEdit_50->setText(F_Val);

    QString NewWorld = QString("%1").arg(IN_pushButton_16.masterworld,2,16,QLatin1Char('0'));
    ui->lineEdit_71->setText(NewWorld);

    on_pushButton_48_clicked();
}

void MainWindow::on_lineEdit_44_textChanged(const QString &arg1)
{
    if(arg1 == "FF")
    {
        ui->lineEdit_82->setText("FFFFFFFF");
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    packetparsing::packetvars IN_pushButton_17;
    IN_pushButton_17 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    SpawnClone = true;
    on_pushButton_76_clicked();


    QString X_Val = ui->lineEdit_14->text().toUpper();
    QString Z_Val = ui->lineEdit_16->text().toUpper();
    QString Y_Val = ui->lineEdit_15->text().toUpper();
    QString F_Val = ui->lineEdit_17->text().toUpper();

    ui->X_4->setText(X_Val);
    ui->Z_4->setText(Z_Val);
    ui->Y_4->setText(Y_Val);
    ui->lineEdit_133->setText(F_Val);

    ui->lineEdit_45->setText(X_Val);
    ui->lineEdit_53->setText(Z_Val);
    ui->lineEdit_74->setText(Y_Val);
    ui->lineEdit_50->setText(F_Val);

    QString NewWorld = QString("%1").arg(IN_pushButton_17.masterworld,2,16,QLatin1Char('0'));
    ui->lineEdit_71->setText(NewWorld);

    QString New_Char_ID = ui->lineEdit_130->text().toUpper();

    on_pushButton_61_clicked();
}

void MainWindow::on_tableView_5_clicked(const QModelIndex &index)
{
    packetparsing::packetvars IN_tableView_5;
    IN_tableView_5 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QString val1 = ui->tableView_5->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Packet (8)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"' or [X (3)] = '"+val1+"' or [Z (3)] = '"+val1+"' or [Y (3)] = '"+val1+"'"));
    model1->setFilter(QString("[Packet (8)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"' or [X (3)] = '"+val1+"' or [Z (3)] = '"+val1+"' or [Y (3)] = '"+val1+"'"));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    if(query1.exec())
    {
        // QString success1 = "Query success\n";
        //ui->textEdit->append(val1);

        while(query1.next())
        {


            //Packet #
            ui->Packet_Search_2->setText(query1.value(0).toString());

            //Name tableView_3
            ui->Name_Search_LE_2->setText(query1.value(1).toString());


            //X
            QString hex1 = query1.value(7).toString();

            int hex2 = hex1.toInt(nullptr,16);
            float numtofloat = hex2 / 128.0;
            QByteArray array (reinterpret_cast<const char*>(&numtofloat), sizeof(numtofloat));
            IN_tableView_5.tele_x = array.toHex().toUpper();

            //Z
            QString hex3 = query1.value(8).toString();

            int hex4 = hex3.toInt(nullptr,16);
            float numtofloat2 = hex4 / 128.0;

            if(numtofloat2 > 130000.0) //neg z fix leave this in!
            {
                float smallsub2 = numtofloat2 - 131072.00195193;
                numtofloat2 = smallsub2;

            }

            QByteArray array3 (reinterpret_cast<const char*>(&numtofloat2), sizeof(numtofloat2));
            IN_tableView_5.tele_z = array3.toHex().toUpper();

            //Y
            QString hex5 = query1.value(9).toString();

            int hex6 = hex5.toInt(nullptr,16);
            float numtofloat3 = hex6 / 128.0;
            QByteArray array2 (reinterpret_cast<const char*>(&numtofloat3), sizeof(numtofloat3));
            IN_tableView_5.tele_y = array2.toHex().toUpper();

            IN_tableView_5.LastTeleportWorld = IN_tableView_5.masterworld;

            IN_tableView_5.tele_world = query1.value(12).toString();

            IN_tableView_5.masterworld = IN_tableView_5.tele_world.toInt(nullptr,16);

            //qDebug() << "IN_tableView_5.masterworld" << IN_tableView_5.masterworld;
            //qDebug() << "IN_tableView_5.tele_world" << IN_tableView_5.tele_world;

        }
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_tableView_5);

    model1->setTable("NPCS");
    model1->select();
    ui->tableView_5->setModel(model1);
}

void MainWindow::on_tableView_6_clicked(const QModelIndex &index)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    packetparsing::packetvars IN_tableView_6;
    IN_tableView_6 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QString val1 = ui->tableView_6->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Packet (8)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"' or [X (3)] = '"+val1+"' or [Z (3)] = '"+val1+"' or [Y (3)] = '"+val1+"'"));


    if(query1.exec())
    {
        // QString success1 = "Query success\n";
        //ui->textEdit->append(val1);

        while(query1.next())
        {


            //Packet #
            ui->Packet_Search_2->setText(query1.value(0).toString());

            //Name tableView_3
            ui->Name_Search_LE_2->setText(query1.value(1).toString());

            ui->lineEdit_191->setText(query1.value(5).toString());


            //X
            QString hex1 = query1.value(7).toString();

            int hex2 = hex1.toInt(nullptr,16);
            float numtofloat = hex2 / 128.0;
            QByteArray array (reinterpret_cast<const char*>(&numtofloat), sizeof(numtofloat));
            IN_tableView_6.tele_x = array.toHex().toUpper();

            //Z
            QString hex3 = query1.value(8).toString();

            int hex4 = hex3.toInt(nullptr,16);
            float numtofloat2 = hex4 / 128.0;
            if(numtofloat2 > 130000)
            {
                numtofloat2 = numtofloat2 - 131072.00195193;
            }

            QByteArray array3 (reinterpret_cast<const char*>(&numtofloat2), sizeof(numtofloat2));
            IN_tableView_6.tele_z = array3.toHex().toUpper();

            //Y
            QString hex5 = query1.value(9).toString();

            int hex6 = hex5.toInt(nullptr,16);
            float numtofloat3 = hex6 / 128.0;
            QByteArray array2 (reinterpret_cast<const char*>(&numtofloat3), sizeof(numtofloat3));
            IN_tableView_6.tele_y = array2.toHex().toUpper();
            IN_tableView_6.LastTeleportWorld = IN_tableView_6.masterworld;
            IN_tableView_6.tele_world = query1.value(12).toString();



            //qDebug() << "IN_tableView_6.masterworld" << IN_tableView_6.masterworld;
            //qDebug() << "IN_tableView_6.tele_world" << IN_tableView_6.tele_world;
        }
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_tableView_6);

    model1->setTable("NPCS");
    model1->select();
    ui->tableView_6->setModel(model1);
}

void MainWindow::on_NPC_Location_PB_3_clicked()
{
    packetparsing::packetvars IN_NPC_Location_PB_3;
    IN_NPC_Location_PB_3 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    QByteArray NPC_X = IN_NPC_Location_PB_3.tele_x.toUtf8();
    QByteArray NPC_Z = IN_NPC_Location_PB_3.tele_z.toUtf8();
    QByteArray NPC_Y = IN_NPC_Location_PB_3.tele_y.toUtf8();

    NPC_Location_XZY_2 = NPC_Location_XZY;

    NPC_Location_XZY_2.replace(4,2,IN_NPC_Location_PB_3.tele_world.toUtf8());
    NPC_Location_XZY_2.replace(6,8,NPC_X);
    NPC_Location_XZY_2.replace(14,8,NPC_Z);
    NPC_Location_XZY_2.replace(22,8,NPC_Y);



    IN_NPC_Location_PB_3.teleport_destination = NPC_Location_XZY_2;

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_NPC_Location_PB_3);


    //qDebug() << "teleport_destination" << teleport_destination;
    on_pushButton_4_clicked();
}


void MainWindow::on_pushButton_73_clicked()
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QString Mystring2 = ui->Packet_Search_2->text();
    model1->setFilter(QString("[Packet (8)] = '%1'").arg(Mystring2));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_6->setModel(model1);
}

void MainWindow::on_AS_Name_Search_PB_2_clicked()
{

    //Search Items by name
    QString NPCs_Name = ui->Name_Search_LE_2->text();

    QString Packet_Number = Name_PacketNumber_Map.value(NPCs_Name);

    //qDebug() << "Name_PacketNumber_Map.count()" << Name_PacketNumber_Map.count();
    //qDebug() << "Opcodes::ID_PacketNumber_Map.count()" << Opcodes::ID_PacketNumber_Map.count();
    int Packet_Number2 = Packet_Number.toInt(nullptr,10);

    ui->Packet_Search_2->setText(Packet_Number);

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Name (24 Max)] = '"+NPCs_Name+"'"));
    model1->setFilter(QString("[Name (24 Max)] = '%1'").arg(NPCs_Name));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_5->selectRow(Packet_Number2 - 1);
    //QModelIndex index2 = ui->tableView_5->currentIndex();
    //ui->tableView_5->scrollTo(index2);

    ui->tableView_6->setModel(model1);

}

void MainWindow::on_pushButton_18_clicked()
{
    QString arg1 = "00";

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [World (1)] = '"+arg1+"'"));
    model1->setFilter(QString("[World (1)] = '%1'").arg(arg1));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_6->setModel(model1);
    ui->tableView_8->setModel(model1);

    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->tableView_6->setModel(model1);
        ui->tableView_8->setModel(model1);
    }

}

void MainWindow::on_tableView_8_clicked(const QModelIndex &index)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QString val1 = ui->tableView_8->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Packet (8)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"' or [X (3)] = '"+val1+"' or [Z (3)] = '"+val1+"' or [Y (3)] = '"+val1+"'"));


    if(query1.exec())
    {
        // QString success1 = "Query success\n";
        //ui->textEdit->append(val1);

        while(query1.next())
        {


            //Packet #
            ui->Packet_Search_3->setText(query1.value(0).toString());

            //Name tableView_3
            ui->Name_Search_LE_3->setText(query1.value(1).toString());

            RemoveObjectID = query1.value(5).toString();

            ui->pushButton_25->setDisabled(false);
        }
    }

    model1->setTable("NPCS");
    model1->select();
    ui->tableView_8->setModel(model1);
}

void MainWindow::on_tableView_7_clicked(const QModelIndex &index)
{
    index2 = index;
    QString val1 = ui->tableView_7->model()->data(index).toString();

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Packet (8)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"' or [X (3)] = '"+val1+"' or [Z (3)] = '"+val1+"' or [Y (3)] = '"+val1+"'"));
    model1->setFilter(QString("[Packet (8)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"' or [X (3)] = '"+val1+"' or [Z (3)] = '"+val1+"' or [Y (3)] = '"+val1+"'"));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();



    ui->tableView_8->setModel(model1);


    if(query1.exec())
    {
        // QString success1 = "Query success\n";
        //ui->textEdit->append(val1);

        while(query1.next())
        {


            //Packet #
            ui->Packet_Search_3->setText(query1.value(0).toString());

            //Name tableView_3
            ui->Name_Search_LE_3->setText(query1.value(1).toString());

            ui->pushButton_25->setDisabled(false);

        }
    }

    model1->setTable("NPCS");
    model1->select();
    ui->tableView_7->setModel(model1);
}

void MainWindow::on_pushButton_74_clicked()
{
    QString Mystring2 = ui->Packet_Search_3->text();

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    model1->setFilter(QString("[Packet (8)] = '%1'").arg(Mystring2));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_8->setModel(model1);
}

void MainWindow::on_AS_Name_Search_PB_3_clicked()
{
    //Search Items by name
    QString NPCs_Name = ui->Name_Search_LE_3->text();

    QString Packet_Number = Name_PacketNumber_Map.value(NPCs_Name);

    int Packet_Number2 = Packet_Number.toInt(nullptr,10);

    ui->Packet_Search_3->setText(Packet_Number);

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Name (24 Max)] = '"+NPCs_Name+"'"));
    model1->setFilter(QString("[Name (24 Max)] = '%1'").arg(NPCs_Name));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_7->selectRow(Packet_Number2 - 1);
    //QModelIndex index2 = ui->tableView_5->currentIndex();
    //ui->tableView_5->scrollTo(index2);

    ui->tableView_8->setModel(model1);

}



void MainWindow::on_pushButton_20_clicked()
{





}

void MainWindow::on_lineEdit_NPC_Name_2_textChanged(const QString &arg1)
{
    ui->lineEdit_347->setText(arg1);
    ui->Name_Search_LE_2->setText(arg1);
    ui->Name_Search_LE_3->setText(arg1);
    ui->lineEdit_206->setText(arg1);
}

void MainWindow::on_lineEdit_72_textChanged(const QString &arg1)
{
    ui->Packet_Search_2->setText(arg1);
    ui->Packet_Search_3->setText(arg1);
}


void MainWindow::on_pushButton_19_clicked()
{
    packetparsing::packetvars IN_slow;
    IN_slow = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    //slow
    IN_slow.SendFBsVector.append("F80000003940");
    IN_slow.FBReplyOrNotVector.append("00");
    IN_slow.FBPacketDescriptionVector.append("Slow_Speed, ");

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_slow);

}

void MainWindow::on_pushButton_21_clicked()
{
    packetparsing::packetvars IN_normal;
    IN_normal = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    //normal
    IN_normal.SendFBsVector.append("F80000004041");
    IN_normal.FBReplyOrNotVector.append("00");
    IN_normal.FBPacketDescriptionVector.append("Normal_Speed, ");

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_normal);

}

void MainWindow::on_pushButton_22_clicked()
{
    packetparsing::packetvars IN_sow;
    IN_sow = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    //sow
    IN_sow.SendFBsVector.append("F80000009841");
    IN_sow.FBReplyOrNotVector.append("00");
    IN_sow.FBPacketDescriptionVector.append("SoW_Speed, ");

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_sow);

}

void MainWindow::on_pushButton_23_clicked()
{
    packetparsing::packetvars IN_Superslow;
    IN_Superslow = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    //super sow
    IN_Superslow.SendFBsVector.append("F80000008042");
    IN_Superslow.FBReplyOrNotVector.append("00");
    IN_Superslow.FBPacketDescriptionVector.append("SuperSoW_Speed, ");

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_Superslow);

}


void MainWindow::on_pushButton_24_clicked()
{
    packetparsing::packetvars IN_pushButton_24;
    IN_pushButton_24 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    /////////////////////////Save Location///////////////////////////

    QSqlQuery querytlpt2;
    QString tablesel2 = "MAINTOON";
    QString objecttlpt2 = "ObjectID (4)";
    QString worldtlpt = "World (1)";
    QString xtlpt = "X (3)";
    QString ztlpt = "Z (3)";
    QString ytlpt = "Y (3)";
    QString facing1 = "Facing (1)";

    QString tlptid2 = IN_pushButton_24.CharSelectID;
    QString chosenworld = QString("%1").arg(IN_pushButton_24.masterworld,2,16,QLatin1Char('0')).toUpper();
    QString facing = IN_pushButton_24.masterf;
    QString x1 = QString::fromUtf8(IN_pushButton_24.masterx);
    QString z1 = QString::fromUtf8(IN_pushButton_24.masterz);
    QString y1 = QString::fromUtf8(IN_pushButton_24.mastery);



    if(chosenworld.isEmpty() == false && facing.isEmpty() == false && x1.isEmpty() == false &&
            z1.isEmpty() == false && y1.isEmpty() == false)
    {
        db.transaction();

        querytlpt2.prepare(QStringLiteral("UPDATE %1 SET [%2] = :val2,[%3] = :val3,[%4] = :val4,[%5] = :val5,[%6] = :val6 WHERE [%7] = :val").arg(tablesel2).arg(xtlpt).arg(ytlpt).arg(ztlpt).arg(worldtlpt).arg(facing1).arg(objecttlpt2));

        querytlpt2.bindValue(":val",tlptid2);
        querytlpt2.bindValue(":val2",x1.toUpper());
        querytlpt2.bindValue(":val3",y1.toUpper());
        querytlpt2.bindValue(":val4",z1.toUpper());
        querytlpt2.bindValue(":val5",chosenworld.toUpper());
        querytlpt2.bindValue(":val6",facing.toUpper());

        querytlpt2.exec();
        db.commit();
    }

    ///////////////////////////////////////////////////////////



}

void MainWindow::on_pushButton_25_clicked()
{
    packetparsing::packetvars IN_pushButton_25;
    IN_pushButton_25 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->pushButton_25->setDisabled(true);
    SpawnDBClone = true;

    IN_pushButton_25.current_c9.clear();


    QString packetid3 = ui->Packet_Search_3->text();

    int CopyPacket_ID = packetid3.toInt(nullptr,10);

    QSqlQuery  query3 (QString("SELECT * FROM NPCS WHERE rowid=%2").arg(CopyPacket_ID));

    while(query3.next())
    {
        QSqlRecord record2 = query3.record();

        for(int j = 4; j < record2.count(); j++)
        {
            IN_pushButton_25.current_c9.append(record2.value(j).toString().toUtf8());

        }
    }


    QString NewWorld = QString("%1").arg(IN_pushButton_25.masterworld,2,16,QLatin1Char('0'));
    ui->lineEdit_71->setText(NewWorld);

    QString World_OldVal1 = NewWorld;
    QString HP_OldVal1 = IN_pushButton_25.current_c9.mid(52,2);
    QString ModelID_OldVal1 = IN_pushButton_25.current_c9.mid(56,8);
    QString Size_OldVal1 = IN_pushButton_25.current_c9.mid(76,4);
    QString Primary_OldVal1 = IN_pushButton_25.current_c9.mid(134,8);
    QString Secondary_OldVal1 = IN_pushButton_25.current_c9.mid(142,8);
    QString Shield_OldVal1 = IN_pushButton_25.current_c9.mid(150,8);
    QString Torso_OldVal1 = IN_pushButton_25.current_c9.mid(186,2);
    QString Forearms_OldVal1 = IN_pushButton_25.current_c9.mid(188,2);
    QString Gloves_OldVal1 = IN_pushButton_25.current_c9.mid(190,2);
    QString Legs_OldVal1 = IN_pushButton_25.current_c9.mid(192,2);
    QString Feet_OldVal1 = IN_pushButton_25.current_c9.mid(194,2);
    QString Head_OldVal1 = IN_pushButton_25.current_c9.mid(196,2);
    QString TorsoC_OldVal1 = IN_pushButton_25.current_c9.mid(222,8);
    QString ForearmsC_OldVal1 = IN_pushButton_25.current_c9.mid(232,8);
    QString GlovesC_OldVal1 = IN_pushButton_25.current_c9.mid(242,8);
    QString LegsC_OldVal1 = IN_pushButton_25.current_c9.mid(252,8);
    QString FeetC_OldVal1 = IN_pushButton_25.current_c9.mid(262,8);
    QString HeadC_OldVal1 = IN_pushButton_25.current_c9.mid(272,8);
    QString RobeC_OldVal1 = IN_pushButton_25.current_c9.mid(282,8);
    QString HairColor_OldVal1 = IN_pushButton_25.current_c9.mid(290,2);//hair color
    QString HairLength_OldVal1 = IN_pushButton_25.current_c9.mid(292,2);//hair length
    QString HairStyle_OldVal1 = IN_pushButton_25.current_c9.mid(294,2);//hair style
    QString Face_OldVal1 = IN_pushButton_25.current_c9.mid(296,2);//face
    QString RobeType_OldVal1 = IN_pushButton_25.current_c9.mid(298,2);//robe type
    QString Race_OldVal1 = IN_pushButton_25.current_c9.mid(300,2);//race
    QString Name24Hex_OldVal1 = IN_pushButton_25.current_c9.mid(310,48);//name
    QString Level_OldVal1 = IN_pushButton_25.current_c9.mid(358,2);//level
    QString Class_OldVal1 = IN_pushButton_25.current_c9.mid(368,2);//class
    QString NPC_Type_OldVal1 = IN_pushButton_25.current_c9.mid(370,4);//npc type





    QString X_Val = ui->lineEdit_14->text().toUpper();
    QString Z_Val = ui->lineEdit_16->text().toUpper();
    QString Y_Val = ui->lineEdit_15->text().toUpper();
    QString F_Val = ui->lineEdit_17->text().toUpper();

    ui->X_4->setText(X_Val);
    ui->Z_4->setText(Z_Val);
    ui->Y_4->setText(Y_Val);
    ui->lineEdit_133->setText(F_Val);

    ui->lineEdit_45->setText(X_Val);
    ui->lineEdit_53->setText(Z_Val);
    ui->lineEdit_74->setText(Y_Val);
    ui->lineEdit_50->setText(F_Val);

    ui->lineEdit_39->setText(Torso_OldVal1.toUpper());//torso
    ui->lineEdit_43->setText(Forearms_OldVal1.toUpper());//forearms
    ui->lineEdit_48->setText(Gloves_OldVal1.toUpper());//gloves
    ui->lineEdit_27->setText(Legs_OldVal1.toUpper());//legs
    ui->lineEdit_49->setText(Feet_OldVal1.toUpper());//feet
    ui->lineEdit_47->setText(Head_OldVal1.toUpper());//head
    ui->lineEdit_124->setText(RobeType_OldVal1.toUpper());//RobeType

    ui->lineEdit_7->setText(Torso_OldVal1.toUpper());//torso
    ui->lineEdit_36->setText(Forearms_OldVal1.toUpper());//forearms
    ui->lineEdit_38->setText(Gloves_OldVal1.toUpper());//gloves
    ui->lineEdit_46->setText(Legs_OldVal1.toUpper());//legs
    ui->lineEdit_40->setText(Feet_OldVal1.toUpper());//feet
    ui->lineEdit_42->setText(Head_OldVal1.toUpper());//head
    ui->lineEdit_44->setText(RobeType_OldVal1.toUpper());//RobeType


    ui->lineEdit_90->setText(Race_OldVal1.toUpper());//race

    ui->lineEdit_34->setText(TorsoC_OldVal1.toUpper());//torsoC
    ui->lineEdit_28->setText(ForearmsC_OldVal1.toUpper());//forearmC
    ui->lineEdit_52->setText(GlovesC_OldVal1.toUpper());//GlovesC
    ui->lineEdit_76->setText(LegsC_OldVal1.toUpper());//LegsC
    ui->lineEdit_32->setText(FeetC_OldVal1.toUpper());//FeetC
    ui->lineEdit_41->setText(HeadC_OldVal1.toUpper());//HeadC
    ui->lineEdit_33->setText(RobeC_OldVal1.toUpper());//RobeC

    ui->lineEdit_68->setText(TorsoC_OldVal1.toUpper());//torsoC
    ui->lineEdit_75->setText(ForearmsC_OldVal1.toUpper());//forearmC
    ui->lineEdit_81->setText(GlovesC_OldVal1.toUpper());//GlovesC
    ui->lineEdit_78->setText(LegsC_OldVal1.toUpper());//LegsC
    ui->lineEdit_67->setText(FeetC_OldVal1.toUpper());//FeetC
    ui->lineEdit_77->setText(HeadC_OldVal1.toUpper());//HeadC
    ui->lineEdit_82->setText(RobeC_OldVal1.toUpper());//RobeC



    ui->lineEdit_125->setText(Face_OldVal1.toUpper());//face
    ui->lineEdit_126->setText(HairStyle_OldVal1.toUpper());//hairStyle
    ui->lineEdit_127->setText(HairLength_OldVal1.toUpper());//HairLength
    ui->lineEdit_128->setText(HairColor_OldVal1.toUpper());//HairColor

    ui->lineEdit_55->setText(Face_OldVal1.toUpper());//face
    ui->lineEdit_56->setText(HairStyle_OldVal1.toUpper());//hairStyle
    ui->lineEdit_57->setText(HairLength_OldVal1.toUpper());//HairLength
    ui->lineEdit_58->setText(HairColor_OldVal1.toUpper());//HairColor

    ui->lineEdit_122->setText(Class_OldVal1.toUpper());//Class
    ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name
    ui->lineEdit_66->setText(HP_OldVal1.toUpper());//hp

    ui->lineEdit_79->setText(Level_OldVal1.toUpper());//Level
    ui->lineEdit_37->setText(Size_OldVal1.toUpper());//Size
    ui->lineEdit_26->setText(Level_OldVal1.toUpper());//Level
    ui->lineEdit_24->setText(Size_OldVal1.toUpper());//Size

    ui->lineEdit_73->setText(NPC_Type_OldVal1.toUpper());//NPC_Type
    ui->lineEdit_54->setText(ModelID_OldVal1.toUpper());//ModelID
    ui->lineEdit_8->setText(ModelID_OldVal1.toUpper());//ModelID

    ui->lineEdit_62->setText(Primary_OldVal1.toUpper());//Primary
    ui->lineEdit_63->setText(Secondary_OldVal1.toUpper());//Secondary
    ui->lineEdit_64->setText(Shield_OldVal1.toUpper());//Shield

    ui->lineEdit_324->setText(Primary_OldVal1.toUpper());//Primary
    ui->lineEdit_325->setText(Secondary_OldVal1.toUpper());//Secondary
    ui->lineEdit_326->setText(Shield_OldVal1.toUpper());//Shield

    ui->lineEdit_71->setText(World_OldVal1.toUpper());//World


    on_pushButton_76_clicked();
    on_pushButton_61_clicked();

}

void MainWindow::on_pushButton_30_clicked()
{
    ui->checkBox_7->setChecked(true);

    Torso_Value1 = ui->lineEdit_39->text();
    Forearms_Value2 = ui->lineEdit_43->text();
    Gloves_Value3 = ui->lineEdit_48->text();
    Legs_Value4 = ui->lineEdit_27->text();
    Feet_Value5 = ui->lineEdit_49->text();
    Head_Value6 = ui->lineEdit_47->text();
    Robe_Value7 = ui->lineEdit_124->text();

    X_Value8 = ui->lineEdit_45->text();
    Z_Value9 = ui->lineEdit_53->text();
    Y_Value10 = ui->lineEdit_74->text();
    Facing_Value11 = ui->lineEdit_50->text();
    Race_Value12 = ui->lineEdit_90->text();

    Torso_Value14 = ui->lineEdit_34->text();
    Forearms_Value15 = ui->lineEdit_28->text();
    Gloves_Value16 = ui->lineEdit_52->text();
    Legs_Value17 = ui->lineEdit_76->text();
    Feet_Value18 = ui->lineEdit_32->text();
    Head_Value19 = ui->lineEdit_41->text();
    Robe_Value20 = ui->lineEdit_33->text();

    Face_Value21 = ui->lineEdit_125->text();
    HairStyle_Value22 = ui->lineEdit_126->text();
    HairLength_Value23 = ui->lineEdit_127->text();
    HairColor_Value24 = ui->lineEdit_128->text();
    Class_Value25 = ui->lineEdit_122->text();

    NPC_Name_Hex = ui->lineEdit_NPC_Name2->text();

    Level_Value28 = ui->lineEdit_79->text();
    Size_Value29 = ui->lineEdit_37->text();
    ModelID_Value31 = ui->lineEdit_54->text();
    Primary_Value32 = ui->lineEdit_62->text();
    Secondary_Value33 = ui->lineEdit_63->text();
    Shield_Value34 = ui->lineEdit_64->text();
}
void MainWindow::on_pushButton_26_clicked()
{
    if(ui->checkBox_7->isChecked() == true)
    {
        ui->lineEdit_39->setText(Torso_Value1);
        ui->lineEdit_43->setText(Forearms_Value2);
        ui->lineEdit_48->setText(Gloves_Value3);
        ui->lineEdit_27->setText(Legs_Value4);
        ui->lineEdit_49->setText(Feet_Value5);
        ui->lineEdit_47->setText(Head_Value6);
        ui->lineEdit_124->setText(Robe_Value7);

        ui->lineEdit_90->setText(Race_Value12);

        ui->lineEdit_34->setText(Torso_Value14);
        ui->lineEdit_28->setText(Forearms_Value15);
        ui->lineEdit_52->setText(Gloves_Value16);
        ui->lineEdit_76->setText(Legs_Value17);
        ui->lineEdit_32->setText(Feet_Value18);
        ui->lineEdit_41->setText(Head_Value19);
        ui->lineEdit_33->setText(Robe_Value20);

        ui->lineEdit_125->setText(Face_Value21);
        ui->lineEdit_126->setText(HairStyle_Value22);
        ui->lineEdit_127->setText(HairLength_Value23);
        ui->lineEdit_128->setText(HairColor_Value24);
        ui->lineEdit_122->setText(Class_Value25);

        ui->lineEdit_NPC_Name2->setText(NPC_Name_Hex);

        ui->lineEdit_79->setText(Level_Value28);
        ui->lineEdit_37->setText(Size_Value29);
        ui->lineEdit_54->setText(ModelID_Value31);
        ui->lineEdit_62->setText(Primary_Value32);
        ui->lineEdit_63->setText(Secondary_Value33);
        ui->lineEdit_64->setText(Shield_Value34);

        on_pushButton_48_clicked();
    }
}

void MainWindow::on_pushButton_27_clicked()
{
    if(ui->checkBox_7->isChecked() == true)
    {
        ui->lineEdit_39->setText("00");
        ui->lineEdit_43->setText("00");
        ui->lineEdit_48->setText("00");
        ui->lineEdit_27->setText("00");
        ui->lineEdit_49->setText("00");
        ui->lineEdit_47->setText("00");
        ui->lineEdit_124->setText("FF");

        ui->lineEdit_90->setText("00");

        ui->lineEdit_34->setText("FFFFFFFF00");
        ui->lineEdit_28->setText("FFFFFFFF00");
        ui->lineEdit_52->setText("FFFFFFFF00");
        ui->lineEdit_76->setText("FFFFFFFF00");
        ui->lineEdit_32->setText("FFFFFFFF00");
        ui->lineEdit_41->setText("FFFFFFFF00");
        ui->lineEdit_33->setText("FFFFFFFF");

        ui->lineEdit_125->setText("00");
        ui->lineEdit_126->setText("00");
        ui->lineEdit_127->setText("00");
        ui->lineEdit_128->setText("00");
        ui->lineEdit_122->setText("00");

        ui->lineEdit_NPC_Name2->setText("4E6577204E50430000000000000000000000000000000000");

        ui->lineEdit_79->setText("02");
        ui->lineEdit_37->setText("803F");
        ui->lineEdit_73->setText("0000");
        ui->lineEdit_54->setText("DF3ECA61");
        ui->lineEdit_62->setText("00000000");
        ui->lineEdit_63->setText("00000000");
        ui->lineEdit_64->setText("00000000");

        on_pushButton_48_clicked();
    }
}



void MainWindow::on_comboBox_38_currentIndexChanged(int index)
{
    QString value = QString("%1").arg(index,2,16,QLatin1Char('0')).toUpper();
    ui->lineEdit_91->setText(value);
    ui->lineEdit_92->setText(value);
}

void MainWindow::on_comboBox_39_currentIndexChanged(int index)
{
    QString value = QString("%1").arg(index,2,16,QLatin1Char('0')).toUpper();
    ui->lineEdit_91->setText(value);
    ui->lineEdit_92->setText(value);
}

void MainWindow::on_tabWidget_4_currentChanged()
{
    //    on_pushButton_18_clicked();
    //    on_pushButton_20_clicked();
}

void MainWindow::on_lineEdit_92_textChanged(const QString &arg1)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [World (1)] = '"+arg1+"'"));
    model1->setFilter(QString("[World (1)] = '%1'").arg(arg1));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_6->setModel(model1);
    ui->tableView_8->setModel(model1);

    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->tableView_6->setModel(model1);
        ui->tableView_8->setModel(model1);
    }

}

void MainWindow::on_lineEdit_91_textChanged(const QString &arg1)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [World (1)] = '"+arg1+"'"));
    model1->setFilter(QString("[World (1)] = '%1'").arg(arg1));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_6->setModel(model1);
    ui->tableView_8->setModel(model1);

    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->tableView_6->setModel(model1);
        ui->tableView_8->setModel(model1);
    }

}

void MainWindow::on_lineEdit_65_textChanged(const QString &arg1)
{
    int arg2 = arg1.toInt(nullptr,10);
    ui->comboBox_6->setCurrentIndex(arg2);
}

void MainWindow::on_lineEdit_69_textChanged(const QString &arg1)
{
    if(ui->tabWidget_3->currentIndex() !=0)
    {
        int arg2 = arg1.toInt(nullptr,10);
        ui->comboBox_8->setCurrentIndex(arg2);
    }
}

void MainWindow::on_lineEdit_8_textChanged(const QString &arg1)
{
    if(Race_AND_Gender.contains(arg1))
    {
        int RaceGen = Race_AND_Gender.value(arg1);
        ui->comboBox->setCurrentIndex(RaceGen);
    }
    else
    {
        ui->comboBox->setCurrentIndex(14);
    }

}

void MainWindow::on_lineEdit_25_textChanged(const QString &arg1)
{
    int NPC_Type2 = NPC_Type.key(arg1);
    ui->comboBox_34->setCurrentIndex(NPC_Type2);
}






void MainWindow::on_Name_Search_LE_3_textChanged(const QString &arg1)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setFilter(QString("[Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_8->setModel(model1);
    ui->tableView_6->setModel(model1);

    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->tableView_8->setModel(model1);
        ui->tableView_6->setModel(model1);
    }

}

void MainWindow::on_Name_Search_LE_2_textChanged(const QString &arg1)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setFilter(QString("[Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();

    ui->tableView_8->setModel(model1);
    ui->tableView_6->setModel(model1);

    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->tableView_8->setModel(model1);
        ui->tableView_6->setModel(model1);
    }
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->checkBox_7->setChecked(true);
    }
}

void MainWindow::on_checkBox_14_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->pushButton_32->setDisabled(false);
        ui->pushButton_34->setDisabled(false);
        ui->pushButton_33->setDisabled(false);
        DB_Trip = "false";
    }
    else
    {
        ui->pushButton_32->setDisabled(true);
        ui->pushButton_34->setDisabled(true);
        ui->pushButton_33->setDisabled(true);
        DB_Trip = "";
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    db.close();
    QString m_FileName = QFileDialog::getOpenFileName(this,tr("Open File"),"/",tr("DB Files (*.db)")); //Open File Dialog

    if(!m_FileName.isEmpty()) //If Cancel Is Not Pressed
    {
        ui->textEdit_11->clear();
        ui->textEdit_11->setText(m_FileName + " is open"); //Show Path and Filename

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(m_FileName);
        db.open();

        if(!db.open())
        {
            QString error1 = "Error Opening Database";
            ui->textEdit_11->setText(error1);
            ui->textEdit_11->setText(db.lastError().text());
            return;


        }
    }
}

void MainWindow::on_pushButton_34_clicked()
{
    QSqlQuery query(QString("SELECT * FROM NPC_CHANGES"));

    while(query.next())
    {
        QSqlRecord record = query.record();
        rowline2.clear();

        int packetnumber = query.value(0).toInt();
        QString NewNPCsName = query.value(1).toString();
        int ZoneNumber = query.value(2).toInt();
        QString NewNPC = query.value(3).toString();
        QString NPCID = query.value(5).toString();

        NPCsNewNameVector.append(NewNPCsName);
        PacketIDnewVector.append(packetnumber);
        NPCsNewOrNotVector.append(NewNPC);
        NPCsNewIDVector.append(NPCID);
        MergerZoneNumber.append(ZoneNumber);


        //qDebug() << "packetnumber1" << packetnumber;
        //qDebug() << "NPCID1" << NPCID;

        //ui->textEdit_12->append("packetNumber1 " + QString::number(packetnumber));
        //ui->textEdit_12->append("NPCID1 " + NPCID);

        for(int i = 4; i < record.count(); i++)
        {
            rowline2.append(record.value(i).toString());
        }

        ui->plainTextEdit_4->appendPlainText(rowline2);
    }

}

void MainWindow::on_pushButton_33_clicked()
{
    packetparsing::packetvars IN_pushButton_33;
    IN_pushButton_33 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    if(DB_Trip == "false")
    {

        ui->textEdit_11->clear();
        DB_Trip = "true";

        QString largestring = ui->plainTextEdit_4->toPlainText().toUpper();



        if(largestring.isEmpty() == false)
        {
            NPC_List = largestring.split("\n");

            SizeMylist = QString("%1").arg(NPC_List.size(),1,10,QLatin1Char('0')).toUpper();
            ui->textEdit_11->append(SizeMylist + " New NPCS Found");

        }
    }




    if(DB_Trip == "true" && ui->checkBox_18->isChecked() == false)
    {
        if(NPC_List.size() > 0)
        {
            //qDebug() << "NPC_List.size()" << NPC_List.size();
            QString firststring = NPC_List.takeAt(0);

            on_pushButton_76_clicked();



            IN_pushButton_33.current_c9 = firststring.toUtf8();

            QString X_OldVal1 = IN_pushButton_33.current_c9.mid(12,6);
            QString Z_OldVal1 = IN_pushButton_33.current_c9.mid(18,6);
            QString Y_OldVal1 = IN_pushButton_33.current_c9.mid(24,6);
            QString Facing_OldVal1 = IN_pushButton_33.current_c9.mid(30,2);
            QString World_OldVal1 = IN_pushButton_33.current_c9.mid(34,2);

            QString HP_OldVal1 = IN_pushButton_33.current_c9.mid(52,2);

            QString ModelID_OldVal1 = IN_pushButton_33.current_c9.mid(56,8);
            QString Size_OldVal1 = IN_pushButton_33.current_c9.mid(76,4);
            QString Primary_OldVal1 = IN_pushButton_33.current_c9.mid(134,8);
            QString Secondary_OldVal1 = IN_pushButton_33.current_c9.mid(142,8);
            QString Shield_OldVal1 = IN_pushButton_33.current_c9.mid(150,8);
            QString Torso_OldVal1 = IN_pushButton_33.current_c9.mid(186,2);
            QString Forearms_OldVal1 = IN_pushButton_33.current_c9.mid(188,2);
            QString Gloves_OldVal1 = IN_pushButton_33.current_c9.mid(190,2);
            QString Legs_OldVal1 = IN_pushButton_33.current_c9.mid(192,2);
            QString Feet_OldVal1 = IN_pushButton_33.current_c9.mid(194,2);
            QString Head_OldVal1 = IN_pushButton_33.current_c9.mid(196,2);
            QString TorsoC_OldVal1 = IN_pushButton_33.current_c9.mid(222,8);
            QString ForearmsC_OldVal1 = IN_pushButton_33.current_c9.mid(232,8);
            QString GlovesC_OldVal1 = IN_pushButton_33.current_c9.mid(242,8);
            QString LegsC_OldVal1 = IN_pushButton_33.current_c9.mid(252,8);
            QString FeetC_OldVal1 = IN_pushButton_33.current_c9.mid(262,8);
            QString HeadC_OldVal1 = IN_pushButton_33.current_c9.mid(272,8);
            QString RobeC_OldVal1 = IN_pushButton_33.current_c9.mid(282,8);
            QString HairColor_OldVal1 = IN_pushButton_33.current_c9.mid(290,2);//hair color
            QString HairLength_OldVal1 = IN_pushButton_33.current_c9.mid(292,2);//hair length
            QString HairStyle_OldVal1 = IN_pushButton_33.current_c9.mid(294,2);//hair style
            QString Face_OldVal1 = IN_pushButton_33.current_c9.mid(296,2);//face
            QString RobeType_OldVal1 = IN_pushButton_33.current_c9.mid(298,2);//robe type
            QString Race_OldVal1 = IN_pushButton_33.current_c9.mid(300,2);//race
            //QString Name24Hex_OldVal1 = IN_pushButton_33.current_c9.mid(310,48);//name
            QString Level_OldVal1 = IN_pushButton_33.current_c9.mid(358,2);//level
            QString Class_OldVal1 = IN_pushButton_33.current_c9.mid(368,2);//class
            QString NPC_Type_OldVal1 = IN_pushButton_33.current_c9.mid(370,4);//npc type



            ui->lineEdit_39->setText(Torso_OldVal1.toUpper());//torso
            ui->lineEdit_43->setText(Forearms_OldVal1.toUpper());//forearms
            ui->lineEdit_48->setText(Gloves_OldVal1.toUpper());//gloves
            ui->lineEdit_27->setText(Legs_OldVal1.toUpper());//legs
            ui->lineEdit_49->setText(Feet_OldVal1.toUpper());//feet
            ui->lineEdit_47->setText(Head_OldVal1.toUpper());//head
            ui->lineEdit_124->setText(RobeType_OldVal1.toUpper());//RobeType

            ui->lineEdit_7->setText(Torso_OldVal1.toUpper());//torso
            ui->lineEdit_36->setText(Forearms_OldVal1.toUpper());//forearms
            ui->lineEdit_38->setText(Gloves_OldVal1.toUpper());//gloves
            ui->lineEdit_46->setText(Legs_OldVal1.toUpper());//legs
            ui->lineEdit_40->setText(Feet_OldVal1.toUpper());//feet
            ui->lineEdit_42->setText(Head_OldVal1.toUpper());//head
            ui->lineEdit_44->setText(RobeType_OldVal1.toUpper());//RobeType

            ui->X_4->setText(X_OldVal1.toUpper());//x
            ui->Z_4->setText(Z_OldVal1.toUpper());//z
            ui->Y_4->setText(Y_OldVal1.toUpper());//y
            ui->lineEdit_45->setText(X_OldVal1.toUpper());//x
            ui->lineEdit_53->setText(Z_OldVal1.toUpper());//z
            ui->lineEdit_74->setText(Y_OldVal1.toUpper());//y

            ui->lineEdit_133->setText(Facing_OldVal1.toUpper());//facing
            ui->lineEdit_50->setText(Facing_OldVal1.toUpper());//facing

            ui->lineEdit_90->setText(Race_OldVal1.toUpper());//race

            ui->lineEdit_34->setText(TorsoC_OldVal1.toUpper());//torsoC
            ui->lineEdit_28->setText(ForearmsC_OldVal1.toUpper());//forearmC
            ui->lineEdit_52->setText(GlovesC_OldVal1.toUpper());//GlovesC
            ui->lineEdit_76->setText(LegsC_OldVal1.toUpper());//LegsC
            ui->lineEdit_32->setText(FeetC_OldVal1.toUpper());//FeetC
            ui->lineEdit_41->setText(HeadC_OldVal1.toUpper());//HeadC
            ui->lineEdit_33->setText(RobeC_OldVal1.toUpper());//RobeC

            ui->lineEdit_68->setText(TorsoC_OldVal1.toUpper());//torsoC
            ui->lineEdit_75->setText(ForearmsC_OldVal1.toUpper());//forearmC
            ui->lineEdit_81->setText(GlovesC_OldVal1.toUpper());//GlovesC
            ui->lineEdit_78->setText(LegsC_OldVal1.toUpper());//LegsC
            ui->lineEdit_67->setText(FeetC_OldVal1.toUpper());//FeetC
            ui->lineEdit_77->setText(HeadC_OldVal1.toUpper());//HeadC
            ui->lineEdit_82->setText(RobeC_OldVal1.toUpper());//RobeC

            ui->lineEdit_125->setText(Face_OldVal1.toUpper());//face
            ui->lineEdit_126->setText(HairStyle_OldVal1.toUpper());//hairStyle
            ui->lineEdit_127->setText(HairLength_OldVal1.toUpper());//HairLength
            ui->lineEdit_128->setText(HairColor_OldVal1.toUpper());//HairColor

            ui->lineEdit_122->setText(Class_OldVal1.toUpper());//Class
            //ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name
            ui->lineEdit_66->setText(HP_OldVal1.toUpper());//hp

            ui->lineEdit_79->setText(Level_OldVal1.toUpper());//Level
            ui->lineEdit_37->setText(Size_OldVal1.toUpper());//Size
            ui->lineEdit_26->setText(Level_OldVal1.toUpper());//Level
            ui->lineEdit_24->setText(Size_OldVal1.toUpper());//Size

            ui->lineEdit_73->setText(NPC_Type_OldVal1.toUpper());//NPC_Type
            ui->lineEdit_54->setText(ModelID_OldVal1.toUpper());//ModelID

            ui->lineEdit_62->setText(Primary_OldVal1.toUpper());//Primary
            ui->lineEdit_63->setText(Secondary_OldVal1.toUpper());//Secondary
            ui->lineEdit_64->setText(Shield_OldVal1.toUpper());//Shield

            ui->lineEdit_324->setText(Primary_OldVal1.toUpper());//Primary
            ui->lineEdit_325->setText(Secondary_OldVal1.toUpper());//Secondary
            ui->lineEdit_326->setText(Shield_OldVal1.toUpper());//Shield

            ui->lineEdit_71->setText(World_OldVal1.toUpper());//World
            ui->lineEdit_65->setText(World_OldVal1.toUpper());//World

            int Face_OldVal2 = Face_OldVal1.toInt(nullptr,10);
            ui->horizontalSlider->setValue(Face_OldVal2);//face
            int HairStyle_OldVal2 = HairStyle_OldVal1.toInt(nullptr,10);
            ui->horizontalSlider_2->setValue(HairStyle_OldVal2);//hairStyle
            int HairLength_OldVal2 = HairLength_OldVal1.toInt(nullptr,10);
            ui->horizontalSlider_3->setValue(HairLength_OldVal2);//HairLength
            int HairColor_OldVal2 = HairColor_OldVal1.toInt(nullptr,10);
            ui->horizontalSlider_4->setValue(HairColor_OldVal2);//HairColor




            on_pushButton_61_clicked();

            //qDebug() << "New_ID" << New_ID;


            NPC_Counter = NPC_Counter + 1;
            QString Item_counter2 = QString("%1").arg(NPC_Counter,1,10,QLatin1Char('0')).toUpper();
            ui->textEdit_11->append("Number of PacketIDs used " + Packet_ID);
            ui->textEdit_11->append("NPC " + Item_counter2 + " of " + SizeMylist + " has been Merged");

            ui->plainTextEdit_4->clear();

            foreach(QString value1,NPC_List)
            {
                ui->plainTextEdit_4->appendPlainText(value1);
            }

        }
        else
        {
            if(ui->checkBox_18->isChecked() == false)
            {
                NPC_List.clear();
                ui->textEdit_11->append("Merger Completed..");
                DB_Trip = "";
            }
        }
    }

    if(DB_Trip == "true" && ui->checkBox_18->isChecked() == true)
    {
        if(NPC_List.size() > 0)
        {
            do
            {
                //qDebug() << "NPC_List.size()" << NPC_List.size();
                QString firststring = NPC_List.takeAt(0);

                on_pushButton_76_clicked();



                IN_pushButton_33.current_c9 = firststring.toUtf8();

                QString X_OldVal1 = IN_pushButton_33.current_c9.mid(12,6);
                QString Z_OldVal1 = IN_pushButton_33.current_c9.mid(18,6);
                QString Y_OldVal1 = IN_pushButton_33.current_c9.mid(24,6);
                QString Facing_OldVal1 = IN_pushButton_33.current_c9.mid(30,2);
                QString World_OldVal1 = IN_pushButton_33.current_c9.mid(34,2);

                QString HP_OldVal1 = IN_pushButton_33.current_c9.mid(52,2);

                QString ModelID_OldVal1 = IN_pushButton_33.current_c9.mid(56,8);
                QString Size_OldVal1 = IN_pushButton_33.current_c9.mid(76,4);
                QString Primary_OldVal1 = IN_pushButton_33.current_c9.mid(134,8);
                QString Secondary_OldVal1 = IN_pushButton_33.current_c9.mid(142,8);
                QString Shield_OldVal1 = IN_pushButton_33.current_c9.mid(150,8);
                QString Torso_OldVal1 = IN_pushButton_33.current_c9.mid(186,2);
                QString Forearms_OldVal1 = IN_pushButton_33.current_c9.mid(188,2);
                QString Gloves_OldVal1 = IN_pushButton_33.current_c9.mid(190,2);
                QString Legs_OldVal1 = IN_pushButton_33.current_c9.mid(192,2);
                QString Feet_OldVal1 = IN_pushButton_33.current_c9.mid(194,2);
                QString Head_OldVal1 = IN_pushButton_33.current_c9.mid(196,2);
                QString TorsoC_OldVal1 = IN_pushButton_33.current_c9.mid(222,8);
                QString ForearmsC_OldVal1 = IN_pushButton_33.current_c9.mid(232,8);
                QString GlovesC_OldVal1 = IN_pushButton_33.current_c9.mid(242,8);
                QString LegsC_OldVal1 = IN_pushButton_33.current_c9.mid(252,8);
                QString FeetC_OldVal1 = IN_pushButton_33.current_c9.mid(262,8);
                QString HeadC_OldVal1 = IN_pushButton_33.current_c9.mid(272,8);
                QString RobeC_OldVal1 = IN_pushButton_33.current_c9.mid(282,8);
                QString HairColor_OldVal1 = IN_pushButton_33.current_c9.mid(290,2);//hair color
                QString HairLength_OldVal1 = IN_pushButton_33.current_c9.mid(292,2);//hair length
                QString HairStyle_OldVal1 = IN_pushButton_33.current_c9.mid(294,2);//hair style
                QString Face_OldVal1 = IN_pushButton_33.current_c9.mid(296,2);//face
                QString RobeType_OldVal1 = IN_pushButton_33.current_c9.mid(298,2);//robe type
                QString Race_OldVal1 = IN_pushButton_33.current_c9.mid(300,2);//race
                //QString Name24Hex_OldVal1 = IN_pushButton_33.current_c9.mid(310,48);//name
                QString Level_OldVal1 = IN_pushButton_33.current_c9.mid(358,2);//level
                QString Class_OldVal1 = IN_pushButton_33.current_c9.mid(368,2);//class
                QString NPC_Type_OldVal1 = IN_pushButton_33.current_c9.mid(370,4);//npc type



                ui->lineEdit_39->setText(Torso_OldVal1.toUpper());//torso
                ui->lineEdit_43->setText(Forearms_OldVal1.toUpper());//forearms
                ui->lineEdit_48->setText(Gloves_OldVal1.toUpper());//gloves
                ui->lineEdit_27->setText(Legs_OldVal1.toUpper());//legs
                ui->lineEdit_49->setText(Feet_OldVal1.toUpper());//feet
                ui->lineEdit_47->setText(Head_OldVal1.toUpper());//head
                ui->lineEdit_124->setText(RobeType_OldVal1.toUpper());//RobeType

                ui->lineEdit_7->setText(Torso_OldVal1.toUpper());//torso
                ui->lineEdit_36->setText(Forearms_OldVal1.toUpper());//forearms
                ui->lineEdit_38->setText(Gloves_OldVal1.toUpper());//gloves
                ui->lineEdit_46->setText(Legs_OldVal1.toUpper());//legs
                ui->lineEdit_40->setText(Feet_OldVal1.toUpper());//feet
                ui->lineEdit_42->setText(Head_OldVal1.toUpper());//head
                ui->lineEdit_44->setText(RobeType_OldVal1.toUpper());//RobeType

                ui->X_4->setText(X_OldVal1.toUpper());//x
                ui->Z_4->setText(Z_OldVal1.toUpper());//z
                ui->Y_4->setText(Y_OldVal1.toUpper());//y
                ui->lineEdit_45->setText(X_OldVal1.toUpper());//x
                ui->lineEdit_53->setText(Z_OldVal1.toUpper());//z
                ui->lineEdit_74->setText(Y_OldVal1.toUpper());//y

                ui->lineEdit_133->setText(Facing_OldVal1.toUpper());//facing
                ui->lineEdit_50->setText(Facing_OldVal1.toUpper());//facing

                ui->lineEdit_90->setText(Race_OldVal1.toUpper());//race

                ui->lineEdit_34->setText(TorsoC_OldVal1.toUpper());//torsoC
                ui->lineEdit_28->setText(ForearmsC_OldVal1.toUpper());//forearmC
                ui->lineEdit_52->setText(GlovesC_OldVal1.toUpper());//GlovesC
                ui->lineEdit_76->setText(LegsC_OldVal1.toUpper());//LegsC
                ui->lineEdit_32->setText(FeetC_OldVal1.toUpper());//FeetC
                ui->lineEdit_41->setText(HeadC_OldVal1.toUpper());//HeadC
                ui->lineEdit_33->setText(RobeC_OldVal1.toUpper());//RobeC

                ui->lineEdit_68->setText(TorsoC_OldVal1.toUpper());//torsoC
                ui->lineEdit_75->setText(ForearmsC_OldVal1.toUpper());//forearmC
                ui->lineEdit_81->setText(GlovesC_OldVal1.toUpper());//GlovesC
                ui->lineEdit_78->setText(LegsC_OldVal1.toUpper());//LegsC
                ui->lineEdit_67->setText(FeetC_OldVal1.toUpper());//FeetC
                ui->lineEdit_77->setText(HeadC_OldVal1.toUpper());//HeadC
                ui->lineEdit_82->setText(RobeC_OldVal1.toUpper());//RobeC

                ui->lineEdit_125->setText(Face_OldVal1.toUpper());//face
                ui->lineEdit_126->setText(HairStyle_OldVal1.toUpper());//hairStyle
                ui->lineEdit_127->setText(HairLength_OldVal1.toUpper());//HairLength
                ui->lineEdit_128->setText(HairColor_OldVal1.toUpper());//HairColor

                ui->lineEdit_122->setText(Class_OldVal1.toUpper());//Class
                //ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name
                ui->lineEdit_66->setText(HP_OldVal1.toUpper());//hp

                ui->lineEdit_79->setText(Level_OldVal1.toUpper());//Level
                ui->lineEdit_37->setText(Size_OldVal1.toUpper());//Size
                ui->lineEdit_26->setText(Level_OldVal1.toUpper());//Level
                ui->lineEdit_24->setText(Size_OldVal1.toUpper());//Size

                ui->lineEdit_73->setText(NPC_Type_OldVal1.toUpper());//NPC_Type
                ui->lineEdit_54->setText(ModelID_OldVal1.toUpper());//ModelID

                ui->lineEdit_62->setText(Primary_OldVal1.toUpper());//Primary
                ui->lineEdit_63->setText(Secondary_OldVal1.toUpper());//Secondary
                ui->lineEdit_64->setText(Shield_OldVal1.toUpper());//Shield

                ui->lineEdit_324->setText(Primary_OldVal1.toUpper());//Primary
                ui->lineEdit_325->setText(Secondary_OldVal1.toUpper());//Secondary
                ui->lineEdit_326->setText(Shield_OldVal1.toUpper());//Shield

                ui->lineEdit_71->setText(World_OldVal1.toUpper());//World
                ui->lineEdit_65->setText(World_OldVal1.toUpper());//World

                int Face_OldVal2 = Face_OldVal1.toInt(nullptr,10);
                ui->horizontalSlider->setValue(Face_OldVal2);//face
                int HairStyle_OldVal2 = HairStyle_OldVal1.toInt(nullptr,10);
                ui->horizontalSlider_2->setValue(HairStyle_OldVal2);//hairStyle
                int HairLength_OldVal2 = HairLength_OldVal1.toInt(nullptr,10);
                ui->horizontalSlider_3->setValue(HairLength_OldVal2);//HairLength
                int HairColor_OldVal2 = HairColor_OldVal1.toInt(nullptr,10);
                ui->horizontalSlider_4->setValue(HairColor_OldVal2);//HairColor




                on_pushButton_61_clicked();

                //qDebug() << "New_ID" << New_ID;


                NPC_Counter = NPC_Counter + 1;
                QString Item_counter2 = QString("%1").arg(NPC_Counter,1,10,QLatin1Char('0')).toUpper();
                ui->textEdit_11->append("Number of PacketIDs used " + Packet_ID);
                ui->textEdit_11->append("NPC " + Item_counter2 + " of " + SizeMylist + " has been Merged");

            }while(NPC_List.size() > 0);
        }
    }
}

void MainWindow::on_pushButton_35_clicked()
{
    on_pushButton_48_clicked();
}

void MainWindow::on_pushButton_36_clicked()
{
    packetparsing::packetvars IN_pushButton_36;
    IN_pushButton_36 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_pushButton_36.CharSelectID);
    QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);
    QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

    increment GrpOut;
    QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
    Servers_Last_MessageNumber = GrpOut_a.toUpper();

    increment Arrange;
    QByteArray Arrange2 = Arrange.count(Servers_Last_MessageNumber);
    Servers_Last_MessageNumber = Arrange2.toUpper(); //replace new count
    ui->lineEdit_5->setText(Arrange2.toUpper());

    QByteArray Send_FB = IN_pushButton_36.serverid1 + IN_pushButton_36.clientid1 + SizeAndSession + IN_pushButton_36.SessionID + "##" +
            Servers_Last_MessageNumber;

    QByteArray Next_Opcode = ui->plainTextEdit_5->toPlainText().toUtf8().toUpper();

    QString NewFB = CurrentItem.FBSize(Next_Opcode);
    increment Text;
    QByteArray Text2 = Text.count(Servers_Last_FB_MessageNumber);
    int index = NewFB.indexOf("XXXX");
    NewFB.replace(index,4,Text2);
    Servers_Last_FB_MessageNumber = Text2.toUpper();

    MessNumbVect.replace(0,Servers_Last_MessageNumber);
    MessNumbVect.replace(1,Servers_Last_FB_MessageNumber);

    Opcodes::CharID_ServerMessageNumbers.insert(IN_pushButton_36.CharSelectID,MessNumbVect);

    Send_FB.append(NewFB.toUtf8());

    index = Send_FB.indexOf("##");

    if(ui->check_Box_FF->isChecked() == true)
    {
        Send_FB.replace(index,4,"00");
    }
    else
    {
        Send_FB.replace(index,4,"03");
        Send_FB.append(IN_pushButton_36.Clients_Last_MessageNumber);
        Send_FB.append(IN_pushButton_36.Clients_Last_FB_MessageNumber);
    }

    packetsize ResizePacket; //call size class
    QByteArray ResizePacket2 = ResizePacket.switchsize(Send_FB); //get new size
    Send_FB.replace(8,4,ResizePacket2);

    ui->plainTextEdit_5->setPlainText(Next_Opcode.toUpper());

    crc sendcrc;
    QByteArray outcrc =  sendcrc.elcrc(Send_FB);
    Send_FB.append(outcrc);

    QByteArray Arrange_out = Send_FB.fromHex(Send_FB);

    QHostAddress current_client_address;
    current_client_address.setAddress(QString::fromUtf8(IN_pushButton_36.ClientsIP));
    quint16 current_client_port = IN_pushButton_36.ClientsPort.toUShort(nullptr,10);
    QString changeIP = current_client_address.toString();

    QHostAddress newsender = QHostAddress(changeIP);
    worldthread::udpsocket3->writeDatagram(Arrange_out,newsender,current_client_port);

}



void MainWindow::on_pushButton_38_clicked()
{
    ui->plainTextEdit_5->clear();
}

// Delete All items
void MainWindow::on_pushButton_39_clicked()
{


    QByteArray Send_FB;// = "d37c5ae7a0c101bf543213" + SessionID + "002800";

    //    Send_FB.replace(0,4,serverid1);
    //    Send_FB.replace(4,4,clientid1);

    //    increment Arrange;
    //    QByteArray Arrange2 = Arrange.count(Servers_Last_MessageNumber); //packet increment //packet increment
    //    Send_FB.replace(30,4,Arrange2); //replace new count at 30
    //    Servers_Last_MessageNumber = Arrange2.toUpper(); //replace new count
    //    ui->lineEdit_5->setText(Arrange2.toUpper());

    //    for(int i = 0; i < 39; i++)
    //    {
    //        QByteArray Next_Opcode = "FB04xxxx3E000000";

    //        Arrange2 = Arrange.count(Servers_Last_FB_MessageNumber); //first opcode increment
    //        Next_Opcode.replace(4,4,Arrange2); //replace new count at 46
    //        Servers_Last_FB_MessageNumber = Arrange2.toUpper(); //replace new count
    //        ui->lineEdit_10->setText(Arrange2.toUpper());

    //        Send_FB.append(Next_Opcode);
    //    }

    //    packetsize ResizePacket; //call size class
    //    QByteArray ResizePacket2 = ResizePacket.switchsize(Send_FB); //get new size
    //    Send_FB.replace(8,4,ResizePacket2);

    crc sendcrc;
    QByteArray outcrc =  sendcrc.elcrc(Send_FB);
    Send_FB.append(outcrc);


    //    //qDebug() << "Send_FB_Delete_Items" << Send_FB;

    //    elcrc(byte1);
    //    Send_FB.append(outcrc);

    //    QByteArray Arrange_out = Send_FB.fromHex(Send_FB);

    //    QHostAddress current_client_address;
    //    current_client_address.setAddress(QString::fromUtf8(IN_WelcomeGreetings.ClientsIP));
    //    quint16 current_client_port = IN_WelcomeGreetings.ClientsPort.toUShort(nullptr,10);
    //    QString changeIP = current_client_address.toString();

    //    QHostAddress newsender = QHostAddress(changeIP);
    //    worldthread::udpsocket3->writeDatagram(Damage_out,newsender,current_client_port);


    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->appendPlainText("Server-Send_FB-");
    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->appendPlainText(Send_FB.toUpper());
    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->appendPlainText("Server-Send_FB-");
    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->moveCursor(QTextCursor::End);

    //    on_SwingTimerStarted();
}



//Add all items back
void MainWindow::on_pushButton_41_clicked()
{
    //qDebug() << "Counter" << Counter;

    //    QVector <QByteArray> TempVect = GroupsOf7.at(Counter2);
    //    Counter2 = Counter2 + 1;

    //    //qDebug() << "Counter2" << Counter2;

    //    if(Counter2 >= 7)
    //    {
    //        ItemsDeleted2 = "Finished";
    //        SwingTimer->stop();
    //        Counter2 = 0;
    //        Counter = 0;
    //        //qDebug() << "SwingTimer stop1";
    //    }

    QByteArray Send_FB;// = "d37c5ae7a0c101bf543213" + SessionID + "002800";

    //    Send_FB.replace(0,4,serverid1);
    //    Send_FB.replace(4,4,clientid1);

    //    increment Arrange;
    //    QByteArray Arrange2 = Arrange.count(Servers_Last_MessageNumber);
    //    Send_FB.replace(30,4,Arrange2);
    //    Servers_Last_MessageNumber = Arrange2.toUpper();
    //    ui->lineEdit_5->setText(Arrange2.toUpper());

    //    foreach(QByteArray Next_Opcode,TempVect)
    //    {
    //        Arrange2 = Arrange.count(Servers_Last_FB_MessageNumber);
    //        int Size_Position = Next_Opcode.indexOf("xxxx");
    //        Next_Opcode.replace(Size_Position,4,Arrange2);
    //        Servers_Last_FB_MessageNumber = Arrange2.toUpper();
    //        ui->lineEdit_10->setText(Arrange2.toUpper());

    //        Send_FB.append(Next_Opcode);
    //    }


    //    packetsize ResizePacket;
    //    QByteArray ResizePacket2 = ResizePacket.switchsize(Send_FB);
    //    Send_FB.replace(8,4,ResizePacket2.toUpper());

    crc sendcrc;
    QByteArray outcrc =  sendcrc.elcrc(Send_FB);
    Send_FB.append(outcrc);

    //    //qDebug() << "Send_FB_add_Items" << Send_FB;

    //    elcrc(byte1);
    //    Send_FB.append(outcrc);

    //    QByteArray Arrange_out = Send_FB.fromHex(Send_FB);

    //    QHostAddress current_client_address;
    //    current_client_address.setAddress(QString::fromUtf8(IN_WelcomeGreetings.ClientsIP));
    //    quint16 current_client_port = IN_WelcomeGreetings.ClientsPort.toUShort(nullptr,10);
    //    QString changeIP = current_client_address.toString();

    //    QHostAddress newsender = QHostAddress(changeIP);
    //    worldthread::udpsocket3->writeDatagram(Damage_out,newsender,current_client_port);


    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->appendPlainText("Server-Send_FB-");
    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->appendPlainText(Send_FB.toUpper());
    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->appendPlainText("Server-Send_FB-");
    //    ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
    //    ui->plainTextEdit->moveCursor(QTextCursor::End);

}




void MainWindow::on_comboBox_40_currentIndexChanged(const QString &arg1)
{
    int index = ui->comboBox_40->currentIndex();
    QString Description = GraphicDescription.at(index);

    ui->lineEdit_102->setText(Description);
    ui->lineEdit_103->setText(arg1);

}

void MainWindow::on_lineEdit_104_textChanged(const QString &arg1)
{
    int CastTime = arg1.toInt(nullptr,10);

    QString CastTime2 = QString("%1").arg(CastTime,4,16,QLatin1Char('0')).toUpper();

    QString Byte1 = CastTime2.mid(0,2);
    QString Byte2 = CastTime2.mid(2,4);

    QString CastTime3 = Byte2 + Byte1;

    ui->lineEdit_101->setText(CastTime3);
}

void MainWindow::on_lineEdit_105_textChanged(const QString &arg1)
{
    QString DecVal = arg1.toUpper();
    Convert Send;
    QString ConvertedValue = Send.ConvertTo(DecVal);
    ui->lineEdit_106->setText(ConvertedValue);

    QString ifNegVal = DecVal.mid(0,1);

    if(ifNegVal == "-")
    {
        DecVal = DecVal.remove(0,1);

        Convert Send;
        ConvertedValue = Send.ConvertTo(DecVal);

        ADD_OR_SUB Change;
        QString ToNeg = Change.SubforNeg(ConvertedValue);

        ConvertedValue = ToNeg;
        ui->lineEdit_106->setText(ConvertedValue);
    }
    else
    {
        Convert Send;
        ConvertedValue = Send.ConvertTo(DecVal);
        ui->lineEdit_106->setText(ConvertedValue);
    }
}

void MainWindow::on_lineEdit_103_textChanged(const QString &arg1)
{
    int index = GraphicValue.indexOf(arg1);

    ui->comboBox_40->setCurrentIndex(index);
}


void MainWindow::on_dial_2_valueChanged(int value)
{
    if(value == 100)
    {
        ui->dial_2->setValue(0);
    }
    if(value < 0)
    {
        ui->dial_2->setValue(99);
    }

    int Hundreds = ui->dial_2->value();
    QString Hundreds1 = QString("%1").arg(Hundreds,1,10,QLatin1Char('0')).toUpper();
    Hundreds1 = Hundreds1 + "00";
    int Hundreds2 = Hundreds1.toInt(nullptr,10);

    int Tens = ui->dial_3->value();

    int Total = Hundreds2 + Tens;

    QString Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

    ui->lineEdit_107->setText(Total1);

}

void MainWindow::on_dial_3_valueChanged(int value)
{
    int Hundreds = ui->dial_2->value();

    if(value == 100)
    {
        ui->dial_3->setValue(0);
        Hundreds = Hundreds + 1;
        ui->dial_2->setValue(Hundreds);
    }
    if(value < 0)
    {
        ui->dial_3->setValue(99);
        Hundreds = Hundreds - 1;
        ui->dial_2->setValue(Hundreds);
    }

    Hundreds = ui->dial_2->value();

    QString Hundreds1 = QString("%1").arg(Hundreds,1,10,QLatin1Char('0')).toUpper();
    Hundreds1 = Hundreds1 + "00";
    int Hundreds2 = Hundreds1.toInt(nullptr,10);

    int Tens = ui->dial_3->value();

    int Total = Hundreds2 + Tens;

    QString Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

    ui->lineEdit_107->setText(Total1);
}



void MainWindow::on_pushButton_44_clicked()
{
    int Hundreds = ui->dial_2->value();
    Hundreds = Hundreds - 1;

    ui->dial_2->setValue(Hundreds);
}

void MainWindow::on_pushButton_45_clicked()
{
    int Hundreds = ui->dial_2->value();
    Hundreds = Hundreds + 1;

    ui->dial_2->setValue(Hundreds);
}

void MainWindow::on_pushButton_72_clicked()
{
    int Tens = ui->dial_3->value();
    Tens = Tens - 1;

    ui->dial_3->setValue(Tens);
}

void MainWindow::on_pushButton_55_clicked()
{
    int Tens = ui->dial_3->value();
    Tens = Tens + 1;

    ui->dial_3->setValue(Tens);
}

void MainWindow::on_dial_4_valueChanged(int value)
{
    if(value == 100)
    {
        ui->dial_4->setValue(0);
    }
    if(value < 0)
    {
        ui->dial_4->setValue(99);
    }

    int Hundreds = ui->dial_4->value();
    QString Hundreds1 = QString("%1").arg(Hundreds,1,10,QLatin1Char('0')).toUpper();
    Hundreds1 = Hundreds1 + "00";
    int Hundreds2 = Hundreds1.toInt(nullptr,10);

    int Tens = ui->dial_5->value();

    int Total = Hundreds2 + Tens;

    QString Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

    ui->lineEdit_110->setText(Total1);
}

void MainWindow::on_dial_5_valueChanged(int value)
{
    int Hundreds = ui->dial_4->value();

    if(value == 100)
    {
        ui->dial_5->setValue(0);
        Hundreds = Hundreds + 1;
        ui->dial_4->setValue(Hundreds);
    }
    if(value < 0)
    {
        ui->dial_5->setValue(99);
        Hundreds = Hundreds - 1;
        ui->dial_4->setValue(Hundreds);
    }

    Hundreds = ui->dial_4->value();

    QString Hundreds1 = QString("%1").arg(Hundreds,1,10,QLatin1Char('0')).toUpper();
    Hundreds1 = Hundreds1 + "00";
    int Hundreds2 = Hundreds1.toInt(nullptr,10);

    int Tens = ui->dial_5->value();

    int Total = Hundreds2 + Tens;

    QString Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

    ui->lineEdit_110->setText(Total1);
}


void MainWindow::on_pushButton_79_clicked()
{
    int Hundreds = ui->dial_4->value();
    Hundreds = Hundreds - 1;

    ui->dial_4->setValue(Hundreds);
}

void MainWindow::on_pushButton_83_clicked()
{
    int Hundreds = ui->dial_4->value();
    Hundreds = Hundreds + 1;

    ui->dial_4->setValue(Hundreds);
}

void MainWindow::on_pushButton_82_clicked()
{
    int Tens = ui->dial_5->value();
    Tens = Tens - 1;

    ui->dial_5->setValue(Tens);
}

void MainWindow::on_pushButton_75_clicked()
{
    int Tens = ui->dial_5->value();
    Tens = Tens + 1;

    ui->dial_5->setValue(Tens);
}

void MainWindow::Mob_DMG_Sent()
{
    qDebug() << "";
    qDebug() << "";
    qDebug() << "";
    qDebug() << "IN_Mob_DMG_Sent";

    auto* SendingFBsTimer = qobject_cast<QTimer*>(sender());
    QString  ID_IP_PORT = SendingFBsTimer->objectName();

    QString ObjectID = ID_IP_PORT.mid(0,8);

    ID_IP_PORT.remove(0,8);

    if(MobSwingTimersVector.contains(SendingFBsTimer))
    {
        MobSwingTimersVector.removeOne(SendingFBsTimer);
    }

    SendingFBsTimer->deleteLater();

    packetparsing::packetvars IN_Mob_DMG_Sent;
    IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    int timerMSec1 = 0;//ui->lineEdit_107->text().toInt(nullptr,10);
    int timerMSec2 = 0;//ui->lineEdit_110->text().toInt(nullptr,10);

    QVector <QString> MyValuesVector = IN_Mob_DMG_Sent.CombatAllValuesMap.value(IN_Mob_DMG_Sent.CharSelectID_Main);
    int CurrentSwing = 0;
    QString CurrentHP = "";



    Combat AllValues;
    Convert Send;
    ADD_OR_SUB Change;
    increment MeleeDMG;
    packetsize ResizePacket;
    xorpacket packet2;

    QString FBsizeOpcode = "";
    QByteArray MyCurrent_c9 = "";
    QByteArray MobCurrent_c9 = "";
    QByteArray New_C9 = New_NPC_c9;
    QByteArray Send_FB = "";




    ///////////////////////////////////////////////////////////
    MyCurrent_c9 = generator::Players_Map.value(IN_Mob_DMG_Sent.CharSelectID.toUtf8());
    QString MyHP_OldVal1 = MyCurrent_c9.mid(52,2);//HP1
    QString MyHP_OldVal2 = MyCurrent_c9.mid(54,2);//HP2
    QString MyOldAnimation1 = MyCurrent_c9.mid(116,2);
    QString MyLevel1 = MyCurrent_c9.mid(358,2);//level
    QString MyClass1 = MyCurrent_c9.mid(368,2);//class

    QString MyStr1 = IN_Mob_DMG_Sent.StatsChange.mid(0,4);
    QString MyStrA = MyStr1.mid(0,2);
    QString MyStrB = MyStr1.mid(2,2);
    QString revMyStr = MyStrB + MyStrA;
    int MyStr2 = revMyStr.toInt(nullptr,16);
    QString MyStr = QString("%1").arg(MyStr2,1,10,QLatin1Char('0'));

    QString MySta1 = IN_Mob_DMG_Sent.StatsChange.mid(8,4);
    QString MyStaA = MySta1.mid(0,2);
    QString MyStaB = MySta1.mid(2,2);
    QString revMySta = MyStaB + MyStaA;
    int MySta2 = revMySta.toInt(nullptr,16);
    QString MySta = QString("%1").arg(MySta2,1,10,QLatin1Char('0'));

    QString MyAGI1 = IN_Mob_DMG_Sent.StatsChange.mid(16,4);
    QString MyAGIA = MyAGI1.mid(0,2);
    QString MyAGIB = MyAGI1.mid(2,2);
    QString revMyAGI = MyAGIB + MyAGIA;
    int MyAGI2 = revMyAGI.toInt(nullptr,16);
    QString MyAGI = QString("%1").arg(MyAGI2,1,10,QLatin1Char('0'));

    QString MyDex1 = IN_Mob_DMG_Sent.StatsChange.mid(24,4);
    QString MyDexA = MyDex1.mid(0,2);
    QString MyDexB = MyDex1.mid(2,2);
    QString revMyDex = MyDexB + MyDexA;
    int MyDex2 = revMyDex.toInt(nullptr,16);
    QString MyDex = QString("%1").arg(MyDex2,1,10,QLatin1Char('0'));


    bool KillYou = false;

    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    MobCurrent_c9 = objectpacket::Master_Map.value(ObjectID.toUtf8());
    QString MobHP_OldVal1 = MobCurrent_c9.mid(52,2);//HP1
    QString MobHP_OldVal2 = MobCurrent_c9.mid(54,2);//HP2
    QString MobOldAnimation1 = MobCurrent_c9.mid(116,2);
    QString MobLevel1 = MobCurrent_c9.mid(358,2);//level
    QString MobClass1 = MobCurrent_c9.mid(368,2);//class
    QString MobX = MobCurrent_c9.mid(12,6);
    QString MobZ = MobCurrent_c9.mid(18,6);
    QString MobY = MobCurrent_c9.mid(24,6);
    QString MobFacing = MobCurrent_c9.mid(30,2);
    ///////////////////////////////////////////////////////////

    CurrentHP = MobHP_OldVal2;

    if(MobOldAnimation1 != "0E" && CurrentHP != "00")
    {


        QStringList holdid;
        QStringList holdx;
        QStringList holdz;
        QStringList holdy;

        if(IN_Mob_DMG_Sent.holdid2.contains(ObjectID))
        {
            holdid = IN_Mob_DMG_Sent.holdid2;
            holdx = IN_Mob_DMG_Sent.holdx2;
            holdz = IN_Mob_DMG_Sent.holdz2;
            holdy = IN_Mob_DMG_Sent.holdy2;
        }
        else
        {
            holdid = objectpacket::holdid1;
            holdx = objectpacket::holdx;
            holdz = objectpacket::holdz;
            holdy = objectpacket::holdy;
        }

        int Index = holdid.indexOf(ObjectID);

        ADD_OR_SUB sendto;
        float DistanceCheck = sendto.DistanceCheck(IN_Mob_DMG_Sent.masterx,IN_Mob_DMG_Sent.masterz,IN_Mob_DMG_Sent.mastery,holdx.at(Index).toUtf8(),holdz.at(Index).toUtf8(),holdy.at(Index).toUtf8());

        IN_Mob_DMG_Sent.MobSwingRadius = DistanceCheck;

        if(IN_Mob_DMG_Sent.CombatAllValuesMap.contains(ObjectID) && IN_Mob_DMG_Sent.MobSwingRadius <= 4.5)
        {
            QVector <QString> MobValuesVector = IN_Mob_DMG_Sent.CombatAllValuesMap.value(ObjectID);

            int MobSwingType = MobValuesVector.at(0).toInt(nullptr,10);
            int MobSwing = MobValuesVector.at(1).toInt(nullptr,10);

            qDebug() << "MobSwingType" << MobSwingType;
            qDebug() << "MobSwingA" << MobSwing;


            if(MobSwing == 0)
            {
                MobSwing = MobSwingType;
            }

            qDebug() << "MobSwingB" << MobSwing;


            QString SpellEffect = "";

            if(MobSwingType == 4)
            {
                timerMSec1 = 475;
                timerMSec2 = 1200;
                SpellEffect = "14EA9BDA";
            }

            if(MobSwingType == 2)
            {
                timerMSec1 = 950;
                timerMSec2 = 3100;
                SpellEffect = "12EA9BDA";
            }

            if(MobSwingType == 1)
            {
                timerMSec1 = 3100;
                timerMSec2 = 3100;
                SpellEffect = "11EA9BDA";
            }

            QString DefendersID = MainWindow::MobsAggroTargetMap.value(ObjectID);

            QMap <QString,int> ClassACMap =
            {
                {"00",40},{"01",25},{"02",40},{"03",40},
                {"04",25},{"05",25},{"06",25},{"07",30},
                {"08",30},{"09",30},{"0A",15},{"0B",15},
                {"0C",15},{"0D",15},{"0E",15}
            };

            int MyAC = ClassACMap.value(IN_Mob_DMG_Sent.Class);
            int MyAC1 = IN_Mob_DMG_Sent.Level * MyAC;

            QString MyAC2 = QString("%1").arg(MyAC1,1,10,QLatin1Char('0'));


            QByteArray AGIold = IN_Mob_DMG_Sent.StatsChange.mid(16,4);
            QByteArray AGIoldA = AGIold.mid(0,2);
            QByteArray AGIoldB = AGIold.mid(2,2);
            QByteArray revAGIold = AGIoldB + AGIoldA;
            int AGIold1 = revAGIold.toInt(nullptr,16);

            IN_Mob_DMG_Sent.Defender_AGI = AGIold1;
            IN_Mob_DMG_Sent.Defender_AC = MyAC1;

            int Value = MobLevel1.toUInt(nullptr,16);

            MobLevel1 = QString::number(Value);

            QString mobSTR = "";
            QString mobDEX = "";

            qDebug() << "MobsLevel" << Value;

            if(Value * 10 < 65)
            {
                mobSTR = QString::number(65);
                mobDEX = QString::number(65);
            }
            else
            {
                mobSTR = QString::number(Value * 10);
                mobDEX = QString::number(Value * 10);
            }

            qDebug() << "mobSTR" << mobSTR;
            qDebug() << "mobDEX" << mobDEX;

            qDebug() << "ObjectID" << ObjectID;
            qDebug() << "DefendersID" << DefendersID;

            QVector<QString> MobMeleeDMGVect = objectpacket::IDs_DamageVectorMap.value(ObjectID);
            qDebug() << "MobMeleeDMGVect.size()A" << MobMeleeDMGVect.size();
            qDebug() << "objectpacket::IDs_DamageVectorMap.size()A" << objectpacket::IDs_DamageVectorMap.size();

            if(MobMeleeDMGVect.isEmpty() == true)
            {
                packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

                AllValues.SendToMAXMeleeDMG(IN_Mob_DMG_Sent.ClientsID, IN_Mob_DMG_Sent.ClientsIP, IN_Mob_DMG_Sent.ClientsPort, ObjectID, MobLevel1, DefendersID, QString::number(IN_Mob_DMG_Sent.Level), mobSTR, mobDEX, "0", QString::number(AGIold1), MyAC2, QString::number(IN_Mob_DMG_Sent.Defender_Defmods));

                MobMeleeDMGVect = objectpacket::IDs_DamageVectorMap.value(ObjectID);

                IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
            }

            QString MobMeleeDMG1 = MobMeleeDMGVect.takeAt(0);

            qDebug() << "MobMeleeDMGVect.size()B" << MobMeleeDMGVect.size();


            objectpacket::IDs_DamageVectorMap.insert(ObjectID,MobMeleeDMGVect);

            qDebug() << "objectpacket::IDs_DamageVectorMap.size()B" << objectpacket::IDs_DamageVectorMap.size();


            if(ui->checkBox_4->isChecked() == true && MobLevel1 != "63")
            {
                MobMeleeDMG1 = "1";
            }

            QString MobMeleeDMG2 = Send.ConvertTo(MobMeleeDMG1);
            QString MobMeleeDMG3 = Change.SubforNeg(MobMeleeDMG2);

            QString Current_channel = IN_Mob_DMG_Sent.Map_Channel_ID.key(ObjectID);

            if(IN_Mob_DMG_Sent.Map_Channel_ID.contains(Current_channel))
            {
                if(MobSwing == MobSwingType)//2
                {
                    StopMovementVector.append(ObjectID);

                    IN_Mob_DMG_Sent.Xor_Object_ID2 = IN_Mob_DMG_Sent.Xor_Object_ID;

                    if(MobOldAnimation1 != "00")
                    {
                        QString Animation_New = "00";//---------------------------------Animation
                        int AGGRO_Animation_Old1 = MobOldAnimation1.toInt(nullptr,16);
                        int Animation_New1 = Animation_New.toInt(nullptr,16);
                        int Animation_New2 = AGGRO_Animation_Old1 ^ Animation_New1;
                        QString Output_New = QString("%1").arg(Animation_New2,2,16,QLatin1Char('0'));
                        IN_Mob_DMG_Sent.Xor_Object_ID2.replace(116,2,Output_New.toUpper().toUtf8());

                        MobCurrent_c9.replace(116,2,Animation_New.toUtf8().toUpper());
                        objectpacket::Master_Map.insert(ObjectID.toUtf8(),MobCurrent_c9);

                        QByteArray Recompressed2 = packet2.packetencrypt(IN_Mob_DMG_Sent.Xor_Object_ID2);

                        QByteArray holderXorC9 = "01c9xxxx01" + Recompressed2;

                        holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());

                        QByteArray Channel = holderXorC9.mid(0,2);
                        QVector <QByteArray> CurrenChannelVector = IN_Mob_DMG_Sent.MapOfChannelVectors.value(Channel);
                        CurrenChannelVector.append(holderXorC9);
                        IN_Mob_DMG_Sent.MapOfChannelVectors.insert(Channel,CurrenChannelVector);
                    }


                    FBsizeOpcode = "7607" + ObjectID  + IN_Mob_DMG_Sent.CharSelectID_Main + SpellEffect; // Add opcode

                    IN_Mob_DMG_Sent.SendFBsVector.append(FBsizeOpcode.toUtf8());
                    IN_Mob_DMG_Sent.FBReplyOrNotVector.append("00");
                    IN_Mob_DMG_Sent.FBPacketDescriptionVector.append("Mob_Attack, ");

                    FBsizeOpcode = "DB00" + ObjectID  + MobMeleeDMG3 + IN_Mob_DMG_Sent.CharSelectID_Main; // Add opcode

                    IN_Mob_DMG_Sent.SendFBsVector.append(FBsizeOpcode.toUtf8());
                    IN_Mob_DMG_Sent.FBReplyOrNotVector.append("00");
                    IN_Mob_DMG_Sent.FBPacketDescriptionVector.append("Mob_DMG, ");

                    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

                    IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

                    QTimer *StopMovementTimers  = new QTimer(this);
                    StopMovementTimers->setInterval(600);
                    StopMovementTimers->setSingleShot(true);
                    StopMovementTimers->setObjectName(ObjectID);
                    StopAllMovementsTimersVector.append(StopMovementTimers);
                    StopMovementTimers->start();

                    connect(StopMovementTimers, SIGNAL(timeout()), this, SLOT(StopAllMovement()));
                }
                else
                {
                    FBsizeOpcode = "DB00" + ObjectID  + MobMeleeDMG3 + IN_Mob_DMG_Sent.CharSelectID_Main; // Add opcode

                    IN_Mob_DMG_Sent.SendFBsVector.append(FBsizeOpcode.toUtf8());
                    IN_Mob_DMG_Sent.FBReplyOrNotVector.append("00");
                    IN_Mob_DMG_Sent.FBPacketDescriptionVector.append("Mob_DMG, ");

                    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

                    IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
                }
            }

            MobSwing = MobSwing - 1;

            qDebug() << "MobSwingC" << MobSwing;

            CurrentSwing = MobSwing;

            qDebug() << "CurrentSwing" << CurrentSwing;

            QString MyOldHP0 = IN_Mob_DMG_Sent.StatsChange.mid(56,4);

            QString Byte1 = MyOldHP0.mid(0,2);
            QString Byte2 = MyOldHP0.mid(2,2);
            QString MyOldHP2 = Byte2 + Byte1;
            int MyOldHP = MyOldHP2.toInt(nullptr,16);

            int NewCurrentHP = 0;
            int NewCurrentPOW = 0;
            int MobDMG = MobMeleeDMG1.toInt(nullptr,10);
            int MyNewHP = MyOldHP - MobDMG;

            QString MyMaxHP0 = IN_Mob_DMG_Sent.StatsChange.mid(64,4);

            Byte1 = MyMaxHP0.mid(0,2);
            Byte2 = MyMaxHP0.mid(2,2);
            QString MyMaxHP2 = Byte2 + Byte1;
            int MyMaxHP = MyMaxHP2.toInt(nullptr,16);
            QString MyMaxHP1 = QString("%1").arg(MyMaxHP,1,10,QLatin1Char('0')).toUpper();
            MyMaxHP = MyMaxHP1.toInt(nullptr,10);

            qDebug() << "MyNewHP_A" << MyNewHP;

            if(MyNewHP <= 0)
            {
                IN_Mob_DMG_Sent.Death = true;
                MyNewHP = 0;
            }

            qDebug() << "MyNewHP_B" << MyNewHP;

            QString CurrentPOW1 = IN_Mob_DMG_Sent.StatsChange.mid(72,4);
            QString POWByte1 = CurrentPOW1.mid(0,2);
            QString POWByte2 = CurrentPOW1.mid(2,2);
            QString reversePOW = POWByte2 + POWByte1;
            int CurrentPOW = reversePOW.toInt(nullptr,16);

            QString MaxPOW1 = IN_Mob_DMG_Sent.StatsChange.mid(80,4);
            POWByte1 = MaxPOW1.mid(0,2);
            POWByte2 = MaxPOW1.mid(2,2);
            QString reverseMaxPOW = POWByte2 + POWByte1;
            int MaxPOW = reverseMaxPOW.toInt(nullptr,16);

            QString MyNewC9_hp3 = "";

            QString Current_HPMAX = QString("%1").arg(MyMaxHP,1,10,QLatin1Char('0')).toUpper();

            QString Current_HP = QString("%1").arg(MyNewHP,1,10,QLatin1Char('0')).toUpper();

            QString Current_POWMAX = QString("%1").arg(MaxPOW,1,10,QLatin1Char('0')).toUpper();

            QString Current_POW = QString("%1").arg(CurrentPOW,1,10,QLatin1Char('0')).toUpper();


            xorpacket SendTo42;
            QString New42ec = SendTo42.Recompress42EC(IN_Mob_DMG_Sent.ClientsID,IN_Mob_DMG_Sent.ClientsIP,IN_Mob_DMG_Sent.ClientsPort,IN_Mob_DMG_Sent.mylist,IN_Mob_DMG_Sent.CharSelectID,IN_Mob_DMG_Sent.StatsChange,IN_Mob_DMG_Sent.HoldOldHP,NewCurrentHP,NewCurrentPOW,MyNewHP);

            QByteArray StatHeader = "42ECxxxx01";

            IN_Mob_DMG_Sent.Send42ECsVector.append(StatHeader + New42ec.toUtf8());

            int MyCurrentHP = 0;
            double MySubHP1 = 0;
            double MyNewC9_hp1 = 0;

            if(MyNewHP != 0)
            {
                MyCurrentHP = MyNewHP * 100;
                MySubHP1 =  MyCurrentHP / MyMaxHP;
                MyNewC9_hp1 = MySubHP1 * 2.55;
            }

            packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

            IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

            if(MyNewHP == 0)
            {
                for(int cc = 0; cc < MySwingTimersVector.size(); cc++) //clear all timers
                {
                    auto* SendingFBsTimer = MySwingTimersVector.at(cc);

                    QString  ident = SendingFBsTimer->objectName();

                    if(IN_Mob_DMG_Sent.CombatAllValuesMap.contains(ident))
                    {
                        SendingFBsTimer->stop();
                        SendingFBsTimer->deleteLater();
                        int index = MySwingTimersVector.indexOf(SendingFBsTimer);
                        MySwingTimersVector.removeAt(index);
                    }
                }

                for(int cc = 0; cc < MobSwingTimersVector.size(); cc++) //clear all timers
                {
                    auto* SendingFBsTimer = MobSwingTimersVector.at(cc);

                    QString  ident = SendingFBsTimer->objectName();

                    if(IN_Mob_DMG_Sent.CombatAllValuesMap.contains(ident))
                    {
                        SendingFBsTimer->stop();
                        SendingFBsTimer->deleteLater();
                        int index = MobSwingTimersVector.indexOf(SendingFBsTimer);
                        MobSwingTimersVector.removeAt(index);
                    }
                }

                qlonglong Old_value = 0;
                QByteArray New_value = "";
                qlonglong New_value2 = 0;
                qlonglong Output_Xor = 0;
                QString Output_Xor_2 = "";

                QMapIterator<QString,QVector<QString>> iter (IN_Mob_DMG_Sent.CombatAllValuesMap); //go thru map to get ids and ranges
                while (iter.hasNext())
                {
                    iter.next();
                    QString CurrentID = iter.key();


                    //qDebug() << "CurrentID" << CurrentID;

                    QString Current_channel = IN_Mob_DMG_Sent.Map_Channel_ID.key(CurrentID);

                    if(CurrentID != IN_Mob_DMG_Sent.CharSelectID_Main && IN_Mob_DMG_Sent.Map_Channel_ID.contains(Current_channel))
                    {
                        Old_value = MobHP_OldVal2.toInt(nullptr,16);
                        New_value = "FF";//--------------------------------HP
                        New_value2 = New_value.toInt(nullptr,16);
                        Output_Xor = Old_value ^ New_value2;
                        Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
                        MobCurrent_c9.replace(54,2,"FF");//-----------------------HP
                        New_C9.replace(54,2,Output_Xor_2.toUtf8());//-----------------------HP


                        objectpacket::Master_Map.insert(CurrentID.toUtf8().toUpper(),MobCurrent_c9);

                        QByteArray Recompressed2 = packet2.packetencrypt(New_C9);

                        QByteArray holderXorC9 = "01c9xxxx01" + Recompressed2;

                        holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());


                        QByteArray Channel = holderXorC9.mid(0,2);
                        QVector <QByteArray> CurrenChannelVector = IN_Mob_DMG_Sent.MapOfChannelVectors.value(Channel);
                        CurrenChannelVector.append(holderXorC9);
                        IN_Mob_DMG_Sent.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

                        packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

                        IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
                    }
                }

                IN_Mob_DMG_Sent.CombatAllValuesMap.clear();

                MyCurrent_c9.replace(54,2,"00");//-----------------------HP

                KillYou = true;

                packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

                IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

            }
            else
            {
                QString MobSwing1 = QString("%1").arg(MobSwing,1,10,QLatin1Char('0')).toUpper();
                QString MyNewHP1 = QString("%1").arg(MyNewHP,1,10,QLatin1Char('0')).toUpper();

                MobValuesVector.replace(1,MobSwing1);
                MyValuesVector.replace(4,MyNewHP1);

                IN_Mob_DMG_Sent.CombatAllValuesMap.insert(IN_Mob_DMG_Sent.CharSelectID_Main,MyValuesVector);
                IN_Mob_DMG_Sent.CombatAllValuesMap.insert(ObjectID,MobValuesVector);

                int MyNewC9_hp4 = MyNewC9_hp1;
                MyNewC9_hp3 = QString("%1").arg(MyNewC9_hp4,2,16,QLatin1Char('0')).toUpper();

                //qDebug() << "MyNewHPFF" << MyNewC9_hp3;

                MyCurrent_c9.replace(54,2,MyNewC9_hp3.toUtf8());//-----------------------HP2

                packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

                IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
            }

            //qDebug() << "MyCurrent_c9" << MyCurrent_c9;

            generator::Players_Map.insert(IN_Mob_DMG_Sent.CharSelectID.toUtf8(),MyCurrent_c9);



            QString mainid4 = IN_Mob_DMG_Sent.CharSelectID;
            generator packet4;
            QByteArray holdergen = packet4.maintoonswitch(mainid4,"",IN_Mob_DMG_Sent.CharSelectID_Main);
            holdergen.insert(0,"00c9xxxx00");

            IN_Mob_DMG_Sent.SendZeroChannelVector.append(holdergen);

            packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

            IN_Mob_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

        }

        packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_Mob_DMG_Sent);

        if(KillYou == true)
        {
            KillYourSelf(ID_IP_PORT);
        }

        flipped sento;
        sento.SendOut(IN_Mob_DMG_Sent.ClientsID, IN_Mob_DMG_Sent.ClientsIP, IN_Mob_DMG_Sent.ClientsPort);

        qDebug() << "CurrentHP" << CurrentHP;

        if((CurrentSwing == 0 && CurrentHP != "00" && IN_Mob_DMG_Sent.CombatAllValuesMap.contains(ObjectID) && IN_Mob_DMG_Sent.FullHealth == false) || (IN_Mob_DMG_Sent.MobSwingRadius > 4.5))
        {

            QTimer *PauseTimers  = new QTimer(this);
            PauseTimers->setInterval(timerMSec2);
            PauseTimers->setSingleShot(true);
            PauseTimers->setObjectName(ObjectID+ID_IP_PORT);
            MobSwingTimersVector.append(PauseTimers);
            PauseTimers->start();

            connect(PauseTimers, SIGNAL(timeout()), this, SLOT(Mob_DMG_Sent()));
        }

        if(CurrentSwing > 0 && CurrentHP != "00" && IN_Mob_DMG_Sent.CombatAllValuesMap.contains(ObjectID) && IN_Mob_DMG_Sent.FullHealth == false)
        {

            QTimer *SwingTimers  = new QTimer(this);
            SwingTimers->setInterval(timerMSec1);
            SwingTimers->setSingleShot(true);
            SwingTimers->setObjectName(ObjectID+ID_IP_PORT);
            MobSwingTimersVector.append(SwingTimers);
            SwingTimers->start();

            connect(SwingTimers, SIGNAL(timeout()), this, SLOT(Mob_DMG_Sent()));
        }
    }
}


void MainWindow::KillYourSelf(QString ID_IP_PORT)
{
    packetparsing::packetvars IN_KillYourSelf;
    IN_KillYourSelf = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());


    QString FBsizeOpcode = "";

    FBsizeOpcode = "5E00"; // Add opcode

    IN_KillYourSelf.SendFBsVector.append(FBsizeOpcode.toUtf8());

    if(IN_KillYourSelf.Reply == "03")
    {
        IN_KillYourSelf.Reply = "";
        IN_KillYourSelf.FBReplyOrNotVector.append("03");
    }
    else
    {
        IN_KillYourSelf.FBReplyOrNotVector.append("00");
    }

    IN_KillYourSelf.FBPacketDescriptionVector.append("kill, ");

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_KillYourSelf);

    flipped sento;
    sento.SendOut(IN_KillYourSelf.ClientsID, IN_KillYourSelf.ClientsIP, IN_KillYourSelf.ClientsPort);


    QTimer *ReviveTimers  = new QTimer(this);
    ReviveTimers->setInterval(8000);
    ReviveTimers->setSingleShot(true);
    ReviveTimers->setObjectName(ID_IP_PORT);
    ReviveTimersVector.append(ReviveTimers);
    ReviveTimers->start();

    connect(ReviveTimers, SIGNAL(timeout()), this, SLOT(ReviveYourSelf()));


}

void MainWindow::ReviveYourSelf()
{
    auto* ReviveTimer = qobject_cast<QTimer*>(sender());
    QString ID_IP_PORT = ReviveTimer->objectName();

    if(ReviveTimersVector.contains(ReviveTimer))
    {
        ReviveTimersVector.removeOne(ReviveTimer);
    }

    ReviveTimer->deleteLater();

    packetparsing::packetvars IN_ReviveYourSelf;
    IN_ReviveYourSelf = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    IN_ReviveYourSelf.teleport_destination = "5cecc5460080584288117646";
    QByteArray Teleport_Code = IN_ReviveYourSelf.teleport_destination;
    QByteArray Teleport_Code_X = Teleport_Code.mid(0,8);
    QByteArray Teleport_Code_Z = Teleport_Code.mid(8,8);
    QByteArray Teleport_Code_Y = Teleport_Code.mid(16,8);

    QByteArray numinput1 = Teleport_Code_X;
    qlonglong outnum1 = numinput1.toLongLong(nullptr,16);
    quint32 reversenum5 = ((outnum1 & 0xFF) << 24) | ((outnum1 & 0xFF00) << 8) | ((outnum1 >> 8) & 0xFF00) | (outnum1 >> 24);
    QString outhex5 = QString("%1").arg(reversenum5,8,16,QLatin1Char('0'));
    qlonglong outnum2 = outhex5.toLongLong(nullptr,16); //adding union code instead of punning

    union
    {
        qlonglong outnum2;
        float array6;
    }

    xresult = {outnum2};

    qlonglong smallhex1 = xresult.array6 * 128.0;

    //float array6  = *reinterpret_cast<float*>(&outnum2);
    // qlonglong smallhex1 = array6 * 128.0;

    QString outaxo2 = QString("%1").arg(smallhex1,6,16,QLatin1Char('0'));
    ui->lineEdit_14->setText(outaxo2.toUpper()); //3 byte X
    IN_ReviveYourSelf.masterx = outaxo2.toUtf8().toUpper(); //send to radius code
    IN_ReviveYourSelf.holdmasterx = outaxo2.toUtf8().toUpper();

    ///////////////////////////////X/////////////////////////////////


    QByteArray numinput3 = Teleport_Code_Z;
    qlonglong outnum5 = numinput3.toLongLong(nullptr,16);
    quint32 reversenum7 = ((outnum5 & 0xFF) << 24) | ((outnum5 & 0xFF00) << 8) | ((outnum5 >> 8) & 0xFF00) | (outnum5 >> 24);
    QString outhex7 = QString("%1").arg(reversenum7,8,16,QLatin1Char('0'));
    qlonglong outnum6 = outhex7.toLongLong(nullptr,16);

    union
    {
        qlonglong outnum6;
        float array8;
    }

    zresult = {outnum6};

    qlonglong smallhex3 = zresult.array8 * 128.0;
    // float array8  = *reinterpret_cast<float*>(&outnum6);
    //qlonglong smallhex3 = array8 * 128.0;
    QString outazo4 = QString("%1").arg(smallhex3,6,16,QLatin1Char('0'));


    if(smallhex3 < 0)
    {

        QByteArray neg1 = neg1.number(smallhex3,16).toUpper();
        QByteArray neg2 = neg1.mid(neg1.size() - 6,6);
        IN_ReviveYourSelf.masterz = neg2.toUpper();
        IN_ReviveYourSelf.holdmasterz = QString::fromUtf8(neg2.toUpper()); //save teleport z

    }
    else
    {
        outazo4 = QString("%1").arg(smallhex3,6,16,QLatin1Char('0'));
        IN_ReviveYourSelf.masterz = outazo4.toUtf8().toUpper();
        IN_ReviveYourSelf.holdmasterz = outazo4.toUpper(); //save teleport z
    }

    /////////////////////////////////Z//////////////////////////////////




    QByteArray numinput2 = Teleport_Code_Y;
    qlonglong outnum3 = numinput2.toLongLong(nullptr,16);
    quint32 reversenum6 = ((outnum3 & 0xFF) << 24) | ((outnum3 & 0xFF00) << 8) | ((outnum3 >> 8) & 0xFF00) | (outnum3 >> 24);
    QString outhex6 = QString("%1").arg(reversenum6,8,16,QLatin1Char('0'));
    qlonglong outnum4 = outhex6.toLongLong(nullptr,16);

    union {
        qlonglong outnum4;
        float array7;
    } yresult = {outnum4};

    qlonglong smallhex2 = yresult.array7 * 128.0;
    //float array7  = *reinterpret_cast<float*>(&outnum4);
    // qlonglong smallhex2 = array7 * 128.0;
    QString outayo3 = QString("%1").arg(smallhex2,6,16,QLatin1Char('0'));
    IN_ReviveYourSelf.mastery = outayo3.toUtf8().toUpper(); //send to radius code
    IN_ReviveYourSelf.holdmastery = outayo3.toUtf8().toUpper();

    int time = 0;

    if(IN_ReviveYourSelf.masterworld != 0)
    {
        time = 100;//ui->lineEdit_195->text().toInt(nullptr,10);
    }
    else
    {
        time = 100;
    }


    IN_ReviveYourSelf.tele_world = "00";

    IN_ReviveYourSelf.masterworld = IN_ReviveYourSelf.tele_world.toInt(nullptr,16);

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_ReviveYourSelf);

    checkthezone sendto;
    sendto.CheckTheZone(IN_ReviveYourSelf.masterx,IN_ReviveYourSelf.masterz,IN_ReviveYourSelf.mastery);

    IN_ReviveYourSelf = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    //////////////////////////Y///////////4 Byte to 3 Byte///////////////////////////////////////////////////////

    QByteArray newc91 = generator::Players_Map.value(IN_ReviveYourSelf.CharSelectID.toUtf8());
    newc91.replace(12,6,IN_ReviveYourSelf.holdmasterx.toUtf8());
    newc91.replace(18,6,IN_ReviveYourSelf.holdmasterz.toUtf8());
    newc91.replace(24,6,IN_ReviveYourSelf.holdmastery.toUtf8());
    QString chosenworld2 = QString("%1").arg(IN_ReviveYourSelf.masterworld,2,16,QLatin1Char('0')).toUpper();
    newc91.replace(34,2,chosenworld2.toUtf8());
    generator::Players_Map.insert(IN_ReviveYourSelf.CharSelectID.toUtf8(),newc91); //replace the new coordinates in the map!!!

    /////////////////////////////9007/////////////////////////////////
    //ip

    QString hexip = QString("%1").arg(QHostAddress(mainip).toIPv4Address(), 8, 16, QLatin1Char( '0' )); //make sure we get a 8 byte ip

    QByteArray teleport_ip = hexip.toUtf8(); //move ip to array

    QByteArray nineoseven = "9007D37C5727280a6cc7030000005ae73b1d69776218";
    nineoseven.replace(4,4,IN_ReviveYourSelf.serverid1);
    QByteArray ourip1 = teleport_ip; //get current ip
    QByteArray first4 =  ourip1.mid(0,2); //reverse it
    QByteArray second4 = ourip1.mid(2,2);
    QByteArray third4 =  ourip1.mid(4,2);
    QByteArray fourth4 = ourip1.mid(6,2);

    QByteArray revip4 = fourth4 += third4 += second4 += first4;
    nineoseven.replace(12,8,revip4);

    //end count
    increment packetcount4; //get class
    QByteArray newcount4 = packetcount4.count(IN_ReviveYourSelf.C_9007_endcount); //end of packet count
    nineoseven.replace(20,4,newcount4); //replace new count at 62
    IN_ReviveYourSelf.C_9007_endcount = newcount4.toUpper();

    IN_ReviveYourSelf.SendFBsVector.append(nineoseven);
    IN_ReviveYourSelf.FBReplyOrNotVector.append("00");
    IN_ReviveYourSelf.FBPacketDescriptionVector.append("C_9007, ");



    /////////////////////////Save Location///////////////////////////


    QSqlQuery querytlpt2;
    QString tablesel2 = "MAINTOON";
    QString objecttlpt2 = "ObjectID (4)";
    QString worldtlpt = "World (1)";
    QString xtlpt = "X (3)";
    QString ztlpt = "Z (3)";
    QString ytlpt = "Y (3)";
    QString facing1 = "Facing (1)";

    QString tlptid2 = IN_ReviveYourSelf.CharSelectID;
    QString chosenworld = QString("%1").arg(IN_ReviveYourSelf.masterworld,2,16,QLatin1Char('0')).toUpper();
    QString facing = IN_ReviveYourSelf.masterf;
    QString x1 = QString::fromUtf8(IN_ReviveYourSelf.masterx);
    QString z1 = QString::fromUtf8(IN_ReviveYourSelf.masterz);
    QString y1 = QString::fromUtf8(IN_ReviveYourSelf.mastery);



    if(chosenworld.isEmpty() == false && facing.isEmpty() == false && x1.isEmpty() == false &&
            z1.isEmpty() == false && y1.isEmpty() == false)
    {
        db.transaction();

        querytlpt2.prepare(QStringLiteral("UPDATE %1 SET [%2] = :val2,[%3] = :val3,[%4] = :val4,[%5] = :val5,[%6] = :val6 WHERE [%7] = :val").arg(tablesel2).arg(xtlpt).arg(ytlpt).arg(ztlpt).arg(worldtlpt).arg(facing1).arg(objecttlpt2));

        querytlpt2.bindValue(":val",tlptid2);
        querytlpt2.bindValue(":val2",x1.toUpper());
        querytlpt2.bindValue(":val3",y1.toUpper());
        querytlpt2.bindValue(":val4",z1.toUpper());
        querytlpt2.bindValue(":val5",chosenworld.toUpper());
        querytlpt2.bindValue(":val6",facing.toUpper());

        querytlpt2.exec();
        db.commit();
    }

    ///////////////////////////////////////////////////////////


    QByteArray HolderXorDespawn = "";

    QMapIterator<QString,QString> iter (IN_ReviveYourSelf.Map_Channel_ID);
    while (iter.hasNext())
    {
        iter.next();
        QString Current_channel = iter.key();

        QString FreeORUsed = IN_ReviveYourSelf.channelmap.value(Current_channel);

        if(FreeORUsed == "used")// no reason to xor if the channel is empty..
        {
            QByteArray holderXorC9 = "XXc9xxxx01100180c800";

            holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());

            QByteArray Channel = holderXorC9.mid(0,2);
            QVector <QByteArray> CurrenChannelVector = IN_ReviveYourSelf.MapOfChannelVectors.value(Channel);
            CurrenChannelVector.append(holderXorC9);
            IN_ReviveYourSelf.MapOfChannelVectors.insert(Channel,CurrenChannelVector);
        }
    }





    if(IN_ReviveYourSelf.LastTeleportWorld != IN_ReviveYourSelf.masterworld)//only xor 00 channel if the last world is not where you are going
    {
        QByteArray holdergen2 = "00c9xxxx01100180c800";

        IN_ReviveYourSelf.SendZeroChannelVector.append(holdergen2);

    }


    QMapIterator<QString,QString> iter2 (IN_ReviveYourSelf.channelmap); //go thru map to get ids and ranges
    while (iter2.hasNext())
    {

        iter2.next();
        QString chkey1 = iter2.key();
        QString mapval1 = "free";
        IN_ReviveYourSelf.channelmap.insert(chkey1,mapval1);

    }


    IN_ReviveYourSelf.sent_ids_map.clear(); //clear sent ids
    IN_ReviveYourSelf.keptlist1.clear(); //clear keptlist

    IN_ReviveYourSelf.teleporting = true; //set teleport flag to true
    IN_ReviveYourSelf.teleportmainswitch = true; //turn on fc02d007 sender


    QString FBsizeOpcode = "";

    FBsizeOpcode = "0d000010000000646174615c74756e617269612e657366888480020600000044444444444400060c808080800000ff00808000a200a006005cecc54600805842881176469bebc5bf000000000000000000000000000000000000000000000000000001010000000001010000000001010000000001010000000000000000000000000055550d41000000000000000001000000000000000000000001000000010000000000000000000000020000000100000000000000000000000300000001000000000000000000000004000000010000000000000000000000050000000100000000000000000000000000000000a00fae984c0055550d41e6019601789601000000de02de0200fa01000000e807005a000004000c4f000000000000de02de0200fa01000000"; // Add opcode



    IN_ReviveYourSelf.SendFBsVector.append(FBsizeOpcode.toUtf8());

    if(IN_ReviveYourSelf.Reply == "03")
    {
        IN_ReviveYourSelf.Reply = "";
        IN_ReviveYourSelf.FBReplyOrNotVector.append("03");
    }
    else
    {
        IN_ReviveYourSelf.FBReplyOrNotVector.append("00");
    }

    IN_ReviveYourSelf.FBPacketDescriptionVector.append("Revive, ");

    IN_ReviveYourSelf.Death = false;
    IN_ReviveYourSelf.FullHealth = true;


    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_ReviveYourSelf);

    flipped sento;
    sento.SendOut(IN_ReviveYourSelf.ClientsID, IN_ReviveYourSelf.ClientsIP, IN_ReviveYourSelf.ClientsPort);

    QTimer *ReviveTimers  = new QTimer(this);
    ReviveTimers->setInterval(time);
    ReviveTimers->setSingleShot(true);
    ReviveTimers->setObjectName(ID_IP_PORT);
    ReviveTimersVector.append(ReviveTimers);
    ReviveTimers->start();

    connect(ReviveTimers, SIGNAL(timeout()), this, SLOT(StandUp()));


}

void MainWindow::StandUp()
{
    auto* SendingFBsTimer = qobject_cast<QTimer*>(sender());
    QString ID_IP_PORT = SendingFBsTimer->objectName();

    if(StandUpTimersVector.contains(SendingFBsTimer))
    {
        StandUpTimersVector.removeOne(SendingFBsTimer);
    }

    SendingFBsTimer->deleteLater();

    packetparsing::packetvars IN_StandUp;
    IN_StandUp = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    QByteArray holdergen2 = "00c9xxxx01100180c800";

    IN_StandUp.SendZeroChannelVector.append(holdergen2);

    IN_StandUp.LastWorld = IN_StandUp.masterworld;

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_StandUp);

    flipped sento;
    sento.SendOut(IN_StandUp.ClientsID, IN_StandUp.ClientsIP, IN_StandUp.ClientsPort);

}

void MainWindow::My_DMG_Sent()
{
    qDebug() << "";
    qDebug() << "";
    qDebug() << "";
    qDebug() << "IN_My_DMG_Sent";

    auto* SendingFBsTimer = qobject_cast<QTimer*>(sender());
    QString  ID_IP_PORT = SendingFBsTimer->objectName();

    if(MySwingTimersVector.contains(SendingFBsTimer))
    {
        MySwingTimersVector.removeOne(SendingFBsTimer);
    }

    SendingFBsTimer->deleteLater();

    packetparsing::packetvars IN_My_DMG_Sent;
    IN_My_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    int timerMSec1 = 0; //ui->lineEdit_107->text().toInt(nullptr,10);
    int timerMSec2 = 0; //ui->lineEdit_112->text().toInt(nullptr,10);

    QVector <QString> MyValuesVector = IN_My_DMG_Sent.CombatAllValuesMap.value(IN_My_DMG_Sent.CharSelectID_Main);
    int CurrentSwing = 0;
    QString CurrentHP = "";



    Combat AllValues;
    Convert Send;
    ADD_OR_SUB Change;
    increment MeleeDMG;
    packetsize ResizePacket;
    xorpacket packet2;

    QString FBsizeOpcode = "";
    QByteArray MyCurrent_c9 = "";
    QByteArray MobCurrent_c9 = "";
    QByteArray New_C9 = New_NPC_c9;
    int MySwingType = 0;
    int MySwing = 0;




    ///////////////////////////////////////////////////////////



    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    MobCurrent_c9 = objectpacket::Master_Map.value(IN_My_DMG_Sent.OldTarget_ID);
    QString MobHP_OldVal1 = MobCurrent_c9.mid(52,2);//HP1
    QString MobHP_OldVal2 = MobCurrent_c9.mid(54,2);//HP2
    QString MobOldAnimation1 = MobCurrent_c9.mid(116,2);
    QString MobLevel1 = MobCurrent_c9.mid(358,2);//level
    QString MobClass1 = MobCurrent_c9.mid(368,2);//class
    QString MobX = MobCurrent_c9.mid(12,6);
    QString MobZ = MobCurrent_c9.mid(18,6);
    QString MobY = MobCurrent_c9.mid(24,6);
    QString MobFacing = MobCurrent_c9.mid(30,2);

    qDebug() << "MobHP_OldVal1" << MobHP_OldVal1;//HP1
    qDebug() << "MobHP_OldVal2" << MobHP_OldVal2;//HP2
    qDebug() << "MobOldAnimation1" << MobOldAnimation1;
    qDebug() << "MobLevel1" << MobLevel1;//level
    qDebug() << "MobClass1" << MobClass1;//class
    qDebug() << "MobX1" << MobX;
    qDebug() << "MobZ1" << MobZ;
    qDebug() << "MobY1" << MobY;
    qDebug() << "MobFacing1" << MobFacing;
    ///////////////////////////////////////////////////////////


    qDebug() << "IN_My_DMG_Sent.OldTarget_ID1" << IN_My_DMG_Sent.OldTarget_ID;

    bool DeadMob = false;


    QStringList holdid;
    QStringList holdx;
    QStringList holdz;
    QStringList holdy;

    if(IN_My_DMG_Sent.holdid2.contains(IN_My_DMG_Sent.OldTarget_ID))
    {
        holdid = IN_My_DMG_Sent.holdid2;
        holdx = IN_My_DMG_Sent.holdx2;
        holdz = IN_My_DMG_Sent.holdz2;
        holdy = IN_My_DMG_Sent.holdy2;
    }
    else
    {
        holdid = objectpacket::holdid1;
        holdx = objectpacket::holdx;
        holdz = objectpacket::holdz;
        holdy = objectpacket::holdy;
    }

    int Index = holdid.indexOf(IN_My_DMG_Sent.OldTarget_ID);

    ADD_OR_SUB sendto;
    float DistanceCheck = sendto.DistanceCheck(IN_My_DMG_Sent.masterx,IN_My_DMG_Sent.masterz,IN_My_DMG_Sent.mastery,holdx.at(Index).toUtf8(),holdz.at(Index).toUtf8(),holdy.at(Index).toUtf8());


    IN_My_DMG_Sent.MySwingRadius = DistanceCheck;

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_My_DMG_Sent);
    IN_My_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());


    /////////////////////////////////////////////////////////////////////////////////////////
    if(IN_My_DMG_Sent.CombatAllValuesMap.contains(IN_My_DMG_Sent.OldTarget_ID) && IN_My_DMG_Sent.MySwingRadius <= 4.5)//Attacking_Mob
    {
        QVector <QString> MobValuesVector = IN_My_DMG_Sent.CombatAllValuesMap.value(IN_My_DMG_Sent.OldTarget_ID);

        MySwingType = MyValuesVector.at(0).toInt(nullptr,10);
        MySwing = MyValuesVector.at(1).toInt(nullptr,10);

        if(MySwing <= 0)
        {
            MySwing = MySwingType;
        }

        QByteArray STRold = IN_My_DMG_Sent.StatsChange.mid(0,4);
        QByteArray STRoldA = STRold.mid(0,2);
        QByteArray STRoldB = STRold.mid(2,2);
        QByteArray revSTRold = STRoldB + STRoldA;
        int STRold1 = revSTRold.toInt(nullptr,16);

        QString STR = QString::number(STRold1);

        QByteArray DEXold = IN_My_DMG_Sent.StatsChange.mid(24,4);
        QByteArray DEXoldA = DEXold.mid(0,2);
        QByteArray DEXoldB = DEXold.mid(2,2);
        QByteArray revDEXold = DEXoldB + DEXoldA;
        int DEXold1 = revDEXold.toInt(nullptr,16);

        QString DEX = QString::number(DEXold1);

        int MobsLevel = MobLevel1.toInt(nullptr,16);
        int MobsAGI = MobsLevel * 10;

        if(MobsAGI < 65)
        {
            MobsAGI = 65;
        }

        QMap <QString,int> ClassACMap =
        {
            {"00",40},{"01",25},{"02",40},{"03",40},
            {"04",25},{"05",25},{"06",25},{"07",30},
            {"08",30},{"09",30},{"0A",15},{"0B",15},
            {"0C",15},{"0D",15},{"0E",15}
        };

        int MobsAC = ClassACMap.value(MobClass1);
        int MobsAC1 = MobsLevel * MobsAC;

        QString MobsAGI1 = QString("%1").arg(MobsAGI,1,10,QLatin1Char('0'));
        QString MobsAC2 = QString("%1").arg(MobsAC1,1,10,QLatin1Char('0'));

        MobLevel1 = QString("%1").arg(MobsLevel,1,10,QLatin1Char('0'));

        QString MyLevel = QString("%1").arg(IN_My_DMG_Sent.Level,1,10,QLatin1Char('0'));

        if(IN_My_DMG_Sent.DamageVector.isEmpty() == true)
        {

            AllValues.SendToMAXMeleeDMG(IN_My_DMG_Sent.ClientsID, IN_My_DMG_Sent.ClientsIP, IN_My_DMG_Sent.ClientsPort, IN_My_DMG_Sent.CharSelectID, MyLevel, IN_My_DMG_Sent.OldTarget_ID, MobLevel1, STR, DEX, IN_My_DMG_Sent.AttackersOffMods, MobsAGI1, MobsAC2, "0");

            IN_My_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
        }

        QString MyMeleeDMG1 = IN_My_DMG_Sent.DamageVector.takeAt(0);

        int MyMeleeDMGx = MyMeleeDMG1.toInt(nullptr,10);

        QVector<QString> ExtraDamageIDsVector =
        {
            "01012000","02012000","03012000","04012000",
            "05012000","06012000","07012000"
        };

        int MyDamage3 = MyMeleeDMGx;

        QString MobOld_hp = MobValuesVector.at(4);

        qDebug() << "MobOld_hp" << MobOld_hp;

        QString MobMaxHP = MobValuesVector.at(5);
        QString MobXP = MobValuesVector.at(7);

        int MobOld_hp1 = MobOld_hp.toInt(nullptr,10);
        int MobMaxHP1 = MobMaxHP.toInt(nullptr,10);
        int MyCurrentDMG1 = MyDamage3;

        qDebug() << "MobOld_hp1" << MobOld_hp1;
        qDebug() << "MobMaxHP1" << MobMaxHP1;
        qDebug() << "MyCurrentDMG1" << MyCurrentDMG1;

        if(ExtraDamageIDsVector.contains(IN_My_DMG_Sent.CharSelectID))
        {
            MyDamage3 = MyDamage3 + Combat::ExtraDamage;

            MyCurrentDMG1 = MyCurrentDMG1 + Combat::ExtraDamage;
        }

        qDebug() << "MyDamage3" << MyDamage3;


        int MobXP1 = MobXP.toInt(nullptr,10);

        if(IN_My_DMG_Sent.boon == true)
        {
            MobXP1 = MobXP1 * 4;
        }

        qDebug() << "MobXP1" << MobXP1;

        IN_My_DMG_Sent.XPperKill = MobXP1;

        int MobCurrentHP = 0;
        int MobCurrentHP2 = 0;
        float MobSubHP1 = 0;
        float MobNewC9_hp1 = 0;

        MobCurrentHP = MobOld_hp1 - MyCurrentDMG1;

        qDebug() << "MobCurrentHP" << MobCurrentHP;

        if(MobCurrentHP < 0)
        {
            MobCurrentHP = 0;
        }

        MobCurrentHP2 = MobCurrentHP * 100;
        MobSubHP1 =  MobCurrentHP2 / MobMaxHP1;
        MobNewC9_hp1 = MobSubHP1 * 2.55;


        qDebug() << "MobCurrentHP2" << MobCurrentHP2;
        qDebug() << "MobSubHP1" << MobSubHP1;
        qDebug() << "MobNewC9_hexVal" << MobNewC9_hp1;

        QString HevVal = QString::number(MobNewC9_hp1);


        HevVal = QString("%1").arg(HevVal.toInt(nullptr,16),2,16,QLatin1Char('0'));

        qDebug() << "HevVal =" << HevVal;

        MyMeleeDMG1 = QString("%1").arg(MyDamage3,1,10,QLatin1Char('0'));

        qDebug() << "MyMeleeDMG1" << MyMeleeDMG1;

        if(MySwingType == 4)
        {
            timerMSec1 = 475;
            timerMSec2 = 1200;
        }

        if(MySwingType == 2)
        {
            timerMSec1 = 950;
            timerMSec2 = 3100;
        }

        if(MySwingType == 1)
        {
            timerMSec1 = 3100;
            timerMSec2 = 3100;
        }


        MySwing = MySwing - 1;
        QString MyMeleeDMG2 = Send.ConvertTo(MyMeleeDMG1);
        QString MyMeleeDMG3 = Change.SubforNeg(MyMeleeDMG2);

        FBsizeOpcode = "DB00" + IN_My_DMG_Sent.CharSelectID_Main.toUtf8() + MyMeleeDMG3 + IN_My_DMG_Sent.OldTarget_ID; // Add opcode

        IN_My_DMG_Sent.SendFBsVector.append(FBsizeOpcode.toUtf8());

        if(IN_My_DMG_Sent.Reply == "03")
        {
            IN_My_DMG_Sent.Reply = "";
            IN_My_DMG_Sent.FBReplyOrNotVector.append("03");
        }
        else
        {
            IN_My_DMG_Sent.FBReplyOrNotVector.append("00");
        }

        IN_My_DMG_Sent.FBPacketDescriptionVector.append("My_DMG, ");

        CurrentSwing = MySwing;


        qDebug() << "MobCurrentHP" << MobCurrentHP;

        // if mob has no hp
        if(MobCurrentHP < 1 || MobNewC9_hp1 < 1)
        {


            IN_My_DMG_Sent.CombatAllValuesMap.remove(IN_My_DMG_Sent.OldTarget_ID);

            for(int cc = 0; cc < MySwingTimersVector.size(); cc++) //clear all timers
            {
                auto* SendingFBsTimer = MySwingTimersVector.at(cc);

                QString  ident = SendingFBsTimer->objectName();

                if(IN_My_DMG_Sent.OldTarget_ID == ident)
                {
                    SendingFBsTimer->stop();
                    SendingFBsTimer->deleteLater();
                    int index = MySwingTimersVector.indexOf(SendingFBsTimer);
                    MySwingTimersVector.removeAt(index);
                    break;

                }
            }

            MobCurrentHP = 0;
            MobNewC9_hp1 = 0;

            QString Update_HP = "00";
            CurrentHP = "00";

            QString Death = "01";

            int Old_value = Death.toInt(nullptr,16);
            QString New_value = "03";//--------------------------------HP
            int New_value2 = New_value.toInt(nullptr,16);
            int Output_Xor = Old_value ^ New_value2;
            QString Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
            MobCurrent_c9.replace(52,2,New_value.toUpper().toUtf8());//-----------------------HP
            New_C9.replace(52,2,Output_Xor_2.toUpper().toUtf8());//-----------------------HP

            Old_value = MobHP_OldVal2.toInt(nullptr,16);
            New_value = Update_HP;//--------------------------------HP
            New_value2 = New_value.toInt(nullptr,16);
            Output_Xor = Old_value ^ New_value2;
            Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
            MobCurrent_c9.replace(54,2,Update_HP.toUpper().toUtf8());//-----------------------HP
            New_C9.replace(54,2,Output_Xor_2.toUpper().toUtf8());//-----------------------HP

            QString Update_Animation = "0E";//death animation

            Old_value = MobOldAnimation1.toInt(nullptr,16);
            New_value = Update_Animation.toUtf8();//--------------------------------Animation
            New_value2 = New_value.toInt(nullptr,16);
            Output_Xor = Old_value ^ New_value2;
            Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0'));
            MobCurrent_c9.replace(116,2,Update_Animation.toUpper().toUtf8());//-----------------------Animation
            New_C9.replace(116,2,Output_Xor_2.toUpper().toUtf8());//-----------------------Animation

            objectpacket::Master_Map.insert(IN_My_DMG_Sent.OldTarget_ID,MobCurrent_c9);




            //ui->textEdit_12->append("xp_out " + xp_out);

            if(IN_My_DMG_Sent.CombatAllValuesMap.size() <= 1)
            {
                IN_My_DMG_Sent.CombatAllValuesMap.remove(IN_My_DMG_Sent.CharSelectID_Main);
            }

            DeadMob = true;

            packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_My_DMG_Sent);
            IN_My_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
        }
        else
        {
            //qDebug() << "Did we get here3";


            int MobNewC9_hp4 = MobNewC9_hp1;

            qDebug() << "MobNewC9_hp4" << MobNewC9_hp4;

            QString MySwing1 = QString("%1").arg(MySwing,1,10,QLatin1Char('0')).toUpper();
            QString MobNewCurrentHP2 = QString("%1").arg(MobCurrentHP,1,10,QLatin1Char('0')).toUpper();

            MyValuesVector.replace(1,MySwing1);
            MobValuesVector.replace(4,MobNewCurrentHP2);

            IN_My_DMG_Sent.CombatAllValuesMap.insert(IN_My_DMG_Sent.CharSelectID_Main,MyValuesVector);
            IN_My_DMG_Sent.CombatAllValuesMap.insert(IN_My_DMG_Sent.OldTarget_ID,MobValuesVector);

            QString MobNewC9_hp3 = QString("%1").arg(MobNewC9_hp4,2,16,QLatin1Char('0')).toUpper();

            int Old_value = MobHP_OldVal2.toInt(nullptr,16);
            QString New_value = MobNewC9_hp3;//--------------------------------HP
            int New_value2 = New_value.toInt(nullptr,16);
            int Output_Xor = Old_value ^ New_value2;

            QString Output_Xor_2 = QString("%1").arg(Output_Xor,2,16,QLatin1Char('0')).toUpper();
            MobCurrent_c9.replace(54,2,MobNewC9_hp3.toUtf8());//-----------------------HP2
            New_C9.replace(54,2,Output_Xor_2.toUpper().toUtf8());

            FacingDirection::HPxorMap.insert(IN_My_DMG_Sent.OldTarget_ID,Output_Xor_2.toUtf8());

            qDebug() << "MobCurrent_c9.size(402) = " << MobCurrent_c9.size();

            objectpacket::Master_Map.insert(IN_My_DMG_Sent.OldTarget_ID,MobCurrent_c9);

            packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_My_DMG_Sent);
            IN_My_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());


        }

        QString Current_channel = IN_My_DMG_Sent.Map_Channel_ID.key(IN_My_DMG_Sent.OldTarget_ID);

        if(New_C9 != New_NPC_c9)
        {

            qDebug() << "New_C9.size() = " << New_C9.size();
            qDebug() << "New_NPC_c9.size() = " << New_NPC_c9.size();

            QByteArray Recompressed2 = packet2.packetencrypt(New_C9);

            QByteArray holderXorC9 = "01c9xxxx01" + Recompressed2;


            holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());

            qDebug() << "holderXorC9" << holderXorC9;

            QByteArray Channel = holderXorC9.mid(0,2);
            QVector <QByteArray> CurrenChannelVector = IN_My_DMG_Sent.MapOfChannelVectors.value(Channel);
            CurrenChannelVector.append(holderXorC9);
            IN_My_DMG_Sent.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

            qDebug() << "Channel" << Channel;
            qDebug() << "CurrenChannelVector" << CurrenChannelVector;
            qDebug() << "IN_My_DMG_Sent.MapOfChannelVectors" << IN_My_DMG_Sent.MapOfChannelVectors;

        }
    }

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_My_DMG_Sent);

    if(DeadMob == true)
    {
        GenerateXP(ID_IP_PORT);
    }

    IN_My_DMG_Sent = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    flipped sento;
    sento.SendOut(IN_My_DMG_Sent.ClientsID, IN_My_DMG_Sent.ClientsIP, IN_My_DMG_Sent.ClientsPort);

    qDebug() << "IN_My_DMG_Sent.OldTarget_ID2" << IN_My_DMG_Sent.OldTarget_ID;

    if(CurrentSwing > 0 && IN_My_DMG_Sent.CombatAllValuesMap.contains(IN_My_DMG_Sent.OldTarget_ID) && IN_My_DMG_Sent.MySwingRadius < 4.5 && IN_My_DMG_Sent.CurrentCombat == "01")
    {
        QTimer *SwingTimers  = new QTimer(this);
        SwingTimers->setInterval(timerMSec1);
        SwingTimers->setSingleShot(true);
        SwingTimers->setObjectName(ID_IP_PORT);
        MySwingTimersVector.append(SwingTimers);
        SwingTimers->start();

        connect(SwingTimers, SIGNAL(timeout()), this, SLOT(My_DMG_Sent()));
    }

    if((IN_My_DMG_Sent.MySwingRadius > 4.5 && IN_My_DMG_Sent.CombatAllValuesMap.contains(IN_My_DMG_Sent.OldTarget_ID)) ||
            (CurrentSwing == 0 && IN_My_DMG_Sent.CombatAllValuesMap.contains(IN_My_DMG_Sent.OldTarget_ID)) ||
            (IN_My_DMG_Sent.CurrentCombat != "01" && IN_My_DMG_Sent.CombatAllValuesMap.contains(IN_My_DMG_Sent.OldTarget_ID)))
    {
        QTimer *PauseTimers  = new QTimer(this);
        PauseTimers->setInterval(timerMSec2);
        PauseTimers->setSingleShot(true);
        PauseTimers->setObjectName(ID_IP_PORT);
        MySwingTimersVector.append(PauseTimers);
        PauseTimers->start();

        connect(PauseTimers, SIGNAL(timeout()), this, SLOT(My_DMG_Sent()));
    }
}

//Receive XP
QByteArray MainWindow::GenerateXP(QString ID_IP_PORT)
{
    packetparsing::packetvars IN_GenerateXP;
    IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    int Total = 0;

    IN_GenerateXP.Level = IN_GenerateXP.CurrentLevel.toInt(nullptr,16)/2;

    QString XPperKill1 = QString("%1").arg(IN_GenerateXP.XPperKill,1,10,QLatin1Char('0'));

    Total = IN_GenerateXP.XPperKill + IN_GenerateXP.XPBar;

    QString Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

    IN_GenerateXP.XPBar = Total;

    ////////////////////////////////////////////////////////////////


    QByteArray dumMy1 = "";

    Convert SendTo;

    Total1 = SendTo.ConvertTo(Total1);



    QString CurrentXP = QString("%1").arg(IN_GenerateXP.XPperKill,1,10,QLatin1Char('0')).toUpper();

    QString FBsizeOpcode = "You receive " + CurrentXP + " XP.";

    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_GenerateXP.CharSelectID);
    QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

    ADD_OR_SUB SendToText;
    QString EQuipText = FBsizeOpcode;
    QString FBText =  SendToText.TextSize(IN_GenerateXP.ClientsID,IN_GenerateXP.ClientsIP,IN_GenerateXP.ClientsPort,EQuipText,true,"7A0A",Servers_Last_FB_MessageNumber);

    IN_GenerateXP.SendFBsVector.append(FBText.toUtf8());
    IN_GenerateXP.FBReplyOrNotVector.append("00");
    IN_GenerateXP.FBPacketDescriptionVector.append("XP, ");

    IN_GenerateXP.XPNextLevel = XPtoNextLevelMap.value(IN_GenerateXP.Level);

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

    IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    if(IN_GenerateXP.XPBar >= IN_GenerateXP.XPNextLevel)
    {
        QString New42ec = "";
        do
        {
            IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

            Total = IN_GenerateXP.XPBar - IN_GenerateXP.XPNextLevel;
            IN_GenerateXP.XPBar = Total;


            QString Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

            int Level1 = IN_GenerateXP.Level + 1;
            IN_GenerateXP.Level = Level1;


            //send to hp and pow... adjust c9 for hp FF and update 42EC..

            QString Level2 = QString("%1").arg(Level1,1,10,QLatin1Char('0')).toUpper();

            IN_GenerateXP.XPNextLevel = XPtoNextLevelMap.value(IN_GenerateXP.Level);

            QString XPNextLevel1 = QString("%1").arg(IN_GenerateXP.XPNextLevel,1,10,QLatin1Char('0')).toUpper();


            QString CurrentLevel1 = QString("%1").arg(Level1,1,10,QLatin1Char('0')).toUpper();

            FBsizeOpcode = "You have reached level " + CurrentLevel1 + "!";

            QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_GenerateXP.CharSelectID);
            QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

            ADD_OR_SUB SendToText;
            QString EQuipText = FBsizeOpcode;
            QString FBText =  SendToText.TextSize(IN_GenerateXP.ClientsID,IN_GenerateXP.ClientsIP,IN_GenerateXP.ClientsPort,EQuipText,true,"7A0A",Servers_Last_FB_MessageNumber);

            IN_GenerateXP.SendFBsVector.append(FBText.toUtf8());
            IN_GenerateXP.FBReplyOrNotVector.append("00");
            IN_GenerateXP.FBPacketDescriptionVector.append("Level_Up_Text, ");

            Convert SendTo;
            IN_GenerateXP.CurrentLevel = SendTo.ConvertTo(CurrentLevel1);
            Total1 = SendTo.ConvertTo(Total1);

            FBsizeOpcode = "2000" + IN_GenerateXP.CurrentLevel + Total1;
            IN_GenerateXP.SendFBsVector.append(FBsizeOpcode.toUtf8());
            IN_GenerateXP.FBReplyOrNotVector.append("00");
            IN_GenerateXP.FBPacketDescriptionVector.append("Update_XP, ");

            QByteArray current_c9 = generator::Players_Map.value(IN_GenerateXP.CharSelectID.toUtf8());
            QString Level3 = QString("%1").arg(Level1,2,16,QLatin1Char('0')).toUpper();
            current_c9.replace(358,2,Level3.toUtf8());



            generator::Players_Map.insert(IN_GenerateXP.CharSelectID.toUtf8(),current_c9);

            QString MyOldHPHexC9 = current_c9.mid(54,2);

            QString MyOldHP0 = IN_GenerateXP.StatsChange.mid(56,4);

            QString Byte1 = MyOldHP0.mid(0,2);
            QString Byte2 = MyOldHP0.mid(2,2);
            QString MyOldHP2 = Byte2 + Byte1;
            int MyOldHP = MyOldHP2.toInt(nullptr,16);
            QString MyOldHP1 = QString("%1").arg(MyOldHP,1,10,QLatin1Char('0')).toUpper();
            MyOldHP = MyOldHP1.toInt(nullptr,10);

            int NewCurrentHP = 0;
            int NewCurrentPOW = 0;
            int MyNewHP = -1;

            QString CurrentPOW1 = IN_GenerateXP.StatsChange.mid(72,4);
            QString POWByte1 = CurrentPOW1.mid(0,2);
            QString POWByte2 = CurrentPOW1.mid(2,2);
            QString reversePOW = POWByte2 + POWByte1;
            int CurrentPOW = reversePOW.toInt(nullptr,16);

            QString MaxPOW1 = IN_GenerateXP.StatsChange.mid(80,4);
            POWByte1 = MaxPOW1.mid(0,2);
            POWByte2 = MaxPOW1.mid(2,2);
            QString reverseMaxPOW = POWByte2 + POWByte1;
            int MaxPOW = reverseMaxPOW.toInt(nullptr,16);

            QString MyNewC9_hp3 = "";



            QString Current_HP = QString("%1").arg(MyNewHP,1,10,QLatin1Char('0')).toUpper();

            QString Current_POWMAX = QString("%1").arg(MaxPOW,1,10,QLatin1Char('0')).toUpper();

            QString Current_POW = QString("%1").arg(CurrentPOW,1,10,QLatin1Char('0')).toUpper();


            IN_GenerateXP.HoldOldHP = "YES";
            xorpacket SendTo42;
            New42ec = SendTo42.Recompress42EC(IN_GenerateXP.ClientsID, IN_GenerateXP.ClientsIP, IN_GenerateXP.ClientsPort, IN_GenerateXP.mylist,IN_GenerateXP.CharSelectID,IN_GenerateXP.StatsChange,IN_GenerateXP.HoldOldHP,NewCurrentHP,NewCurrentPOW,MyNewHP);

            QByteArray StatHeader = "42ECxxxx01";



            IN_GenerateXP.Send42ECsVector.append(StatHeader + New42ec.toUtf8());


            QString MyMaxHP0 = IN_GenerateXP.StatsChange.mid(64,4);
            Byte1 = MyMaxHP0.mid(0,2);
            Byte2 = MyMaxHP0.mid(2,2);
            QString MyMaxHP2 = Byte2 + Byte1;
            int MyMaxHP = MyMaxHP2.toInt(nullptr,16);
            QString MyMaxHP1 = QString("%1").arg(MyMaxHP,1,10,QLatin1Char('0')).toUpper();
            MyMaxHP = MyMaxHP1.toInt(nullptr,10);

            QString Current_HPMAX = QString("%1").arg(MyMaxHP,1,10,QLatin1Char('0')).toUpper();

            int MyCurrentHP = 0;
            double MySubHP1 = 0;
            double MyNewC9_hp1 = 0;

            MyCurrentHP = MyOldHP * 100;
            MySubHP1 =  MyCurrentHP / MyMaxHP;
            MyNewC9_hp1 = MySubHP1 * 2.55;

            int MyNewC9_hp4 = MyNewC9_hp1;

            MyNewC9_hp3 = QString("%1").arg(MyNewC9_hp4,2,16,QLatin1Char('0')).toUpper();


            current_c9 = generator::Players_Map.value(IN_GenerateXP.CharSelectID.toUtf8());
            current_c9.replace(54,2,MyNewC9_hp3.toUtf8());//-----------------------HP2

            generator::Players_Map.insert(IN_GenerateXP.CharSelectID.toUtf8(),current_c9);

            packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

            IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

        }while(IN_GenerateXP.XPBar >= IN_GenerateXP.XPNextLevel);

        IN_GenerateXP.HoldOldHP = "";


        QString mainid4 = IN_GenerateXP.CharSelectID;
        generator packet4;
        QByteArray holdergen = packet4.maintoonswitch(mainid4,"",IN_GenerateXP.CharSelectID_Main);
        holdergen.insert(0,"00c9xxxx00");

        IN_GenerateXP.SendZeroChannelVector.append(holdergen);

        packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

        IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
    }
    else
    {
        FBsizeOpcode = "2000" + IN_GenerateXP.CurrentLevel + Total1;
        IN_GenerateXP.SendFBsVector.append(FBsizeOpcode.toUtf8());
        IN_GenerateXP.FBReplyOrNotVector.append("00");
        IN_GenerateXP.FBPacketDescriptionVector.append("Update_XP, ");

        packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

        IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
    }


    Total = IN_GenerateXP.XPperKill + IN_GenerateXP.TotalXp;
    IN_GenerateXP.TotalXp = Total;

    Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

    QString NextVal = "";

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

    IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    for(int tp = 0; tp < ToltalXPperTPsVector.size(); tp++)
    {
        QString lastVal = ToltalXPperTPsVector.at(tp);
        int lastVal1 = 0;
        lastVal1 = lastVal.toInt(nullptr,10);
        qlonglong lastVal2 = 0;

        if(lastVal1 == 0)
        {
            lastVal2 = lastVal.toLongLong(nullptr,10);
        }

        if(tp < 461)
        {
            NextVal = ToltalXPperTPsVector.at(tp + 1);
            int NextVal1 = 0;
            NextVal1 = NextVal.toInt(nullptr,10);
            qlonglong NextVal2 = 0;

            if(NextVal1 == 0)
            {
                NextVal2 = NextVal.toLongLong(nullptr,10);
            }

            if((IN_GenerateXP.TotalXp >= lastVal1 && IN_GenerateXP.TotalXp < NextVal1 && NextVal1 !=0) ||
                    (IN_GenerateXP.TotalXp >= lastVal2 && IN_GenerateXP.TotalXp < NextVal2 && lastVal2 != 0) ||
                    (IN_GenerateXP.TotalXp >= lastVal1 && IN_GenerateXP.TotalXp < NextVal2 && NextVal2 != 0 && lastVal1 != 0))
            {
                //send to hp and pow... adjust c9 for hp FF and update 42EC..

                int nextTPtotal = TPsPerToltalXPVector.at(tp);

                QString Total1 = QString("%1").arg(nextTPtotal,1,10,QLatin1Char('0')).toUpper();

                Total = IN_GenerateXP.UnSpentTPs + IN_GenerateXP.SpentTPs;

                int Total2 = nextTPtotal - Total;

                if(Total2 > 0)
                {
                    QString NewTP = QString("%1").arg(Total2,1,10,QLatin1Char('0')).toUpper();

                    if(Total2 > 1)
                    {
                        FBsizeOpcode = "You have received " + NewTP + " training points!";
                    }
                    else
                    {
                        FBsizeOpcode = "You have received " + NewTP + " training point!";
                    }

                    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_GenerateXP.CharSelectID);
                    QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

                    ADD_OR_SUB SendToText;
                    QString EQuipText = FBsizeOpcode;
                    QString FBText =  SendToText.TextSize(IN_GenerateXP.ClientsID,IN_GenerateXP.ClientsIP,IN_GenerateXP.ClientsPort,EQuipText,true,"460001000000",Servers_Last_FB_MessageNumber);

                    IN_GenerateXP.SendFBsVector.append(FBText.toUtf8());
                    IN_GenerateXP.FBReplyOrNotVector.append("00");
                    IN_GenerateXP.FBPacketDescriptionVector.append("Training_Point_Pop_Up, ");

                    int Total3 = Total2 + IN_GenerateXP.UnSpentTPs;

                    IN_GenerateXP.UnSpentTPs = Total3;

//                    Total1 = QString("%1").arg(Total3,1,10,QLatin1Char('0')).toUpper();

//                    Total1 = QString("%1").arg(Total,1,10,QLatin1Char('0')).toUpper();

                    Convert SendTo;
                    Total1 = SendTo.ConvertTo(NewTP);

                    ADD_OR_SUB Change;
                    QString ToNeg = Change.SubforNeg(Total1);

                    FBsizeOpcode = "1D00" + ToNeg;
                    IN_GenerateXP.SendFBsVector.append(FBsizeOpcode.toUtf8());
                    IN_GenerateXP.FBReplyOrNotVector.append("00");
                    IN_GenerateXP.FBPacketDescriptionVector.append("Receive_Training_Point(s), ");

                    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

                    IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
                }

                break;
            }
        }
        else
        {
            if(IN_GenerateXP.TotalXp >= lastVal2)
            {
                int nextTPtotal = TPsPerToltalXPVector.at(tp);
                QString Total1 = QString("%1").arg(nextTPtotal,1,10,QLatin1Char('0')).toUpper();

                Total = IN_GenerateXP.UnSpentTPs + IN_GenerateXP.SpentTPs;

                int Total2 = nextTPtotal - Total;

                if(Total2 > 0)
                {
                    QString NewTP = QString("%1").arg(Total2,1,10,QLatin1Char('0')).toUpper();

                    if(Total2 > 1)
                    {
                        FBsizeOpcode = "You have received " + NewTP + " training points.";
                    }
                    else
                    {
                        FBsizeOpcode = "You have received " + NewTP + " training point.";
                    }


                    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_GenerateXP.CharSelectID);
                    QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

                    ADD_OR_SUB SendToText;
                    QString EQuipText = FBsizeOpcode;
                    QString FBText =  SendToText.TextSize(IN_GenerateXP.ClientsID,IN_GenerateXP.ClientsIP,IN_GenerateXP.ClientsPort,EQuipText,true,"460001000000",Servers_Last_FB_MessageNumber);

                    IN_GenerateXP.SendFBsVector.append(FBText.toUtf8());
                    IN_GenerateXP.FBReplyOrNotVector.append("00");
                    IN_GenerateXP.FBPacketDescriptionVector.append("Training_Point_Pop_Up, ");


                    int Total3 = Total2 + IN_GenerateXP.UnSpentTPs;

                    IN_GenerateXP.UnSpentTPs = Total3;

                    Total1 = QString("%1").arg(Total3,1,10,QLatin1Char('0')).toUpper();

                    Convert SendTo;
                    Total1 = SendTo.ConvertTo(Total1);

                    ADD_OR_SUB Change;
                    QString ToNeg = Change.SubforNeg(NewTP);

                    FBsizeOpcode = "1D00" + ToNeg;
                    IN_GenerateXP.SendFBsVector.append(FBsizeOpcode.toUtf8());
                    IN_GenerateXP.FBReplyOrNotVector.append("00");
                    IN_GenerateXP.FBPacketDescriptionVector.append("Receive_Training_Point(s), ");

                    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

                    IN_GenerateXP = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

                }

                break;
            }
        }
    }



    //update db

    QString PacketNumber = Opcodes::ID_PacketNumber_Map.value(IN_GenerateXP.CharSelectID);
    int PacketNumber2 = PacketNumber.toInt(nullptr,10);
    IN_GenerateXP.packetid = PacketNumber2;

    IN_GenerateXP.StartXPbar = QString::number(IN_GenerateXP.XPBar);
    IN_GenerateXP.StartTotalXP = QString::number(IN_GenerateXP.TotalXp);

    IN_GenerateXP.StartLevel = QString("%1").arg(IN_GenerateXP.Level,2,16,QLatin1Char('0')).toUpper();

    db.transaction();

    QSqlQuery query;

    QString Table_Name = "MAINTOON";

    QString RemainingTPs1 = QString("%1").arg(IN_GenerateXP.UnSpentTPs,1,10,QLatin1Char('0')).toUpper();
    Convert SendToHex;
    QString RemainingTPs2 = SendToHex.ConvertTo(RemainingTPs1);

    QString Column_Name = "RemainingTPs";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",RemainingTPs2);
    query.bindValue(":id",IN_GenerateXP.packetid);
    query.exec();

    IN_GenerateXP.StartUnSpentTPs = RemainingTPs2;

    ////////////////////////////////////////////////////////////////////////////////////////////

    QString TotalTPSpent1 = QString("%1").arg(IN_GenerateXP.SpentTPs,1,10,QLatin1Char('0')).toUpper();
    QString TotalTPSpent2 = SendToHex.ConvertTo(TotalTPSpent1);

    Column_Name = "TotalTPSpent";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",TotalTPSpent2);
    query.bindValue(":id",IN_GenerateXP.packetid);
    query.exec();

    IN_GenerateXP.StartSpentTPs = TotalTPSpent2;

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_GenerateXP);

    flipped sento;
    sento.SendOut(IN_GenerateXP.ClientsID, IN_GenerateXP.ClientsIP, IN_GenerateXP.ClientsPort);

    ////////////////////////////////////////////////////////////////////////////////////////////

    QString Column_value = IN_GenerateXP.Cash_on_hand.toUtf8();
    Column_Name = "TunarOnPlayer";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Column_value);
    query.bindValue(":id",IN_GenerateXP.packetid);
    query.exec();


    Column_value = IN_GenerateXP.Current_Available_balance.toUtf8();
    Column_Name = "TunarInBank";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Column_value);
    query.bindValue(":id",IN_GenerateXP.packetid);
    query.exec();


    ////////////////////////////////////////////////////////////////////////////////////////////

    QString StartXPbar2 = SendToHex.ConvertTo(IN_GenerateXP.StartXPbar);

    Column_value = StartXPbar2.toUtf8();
    Column_Name = "XPbar";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Column_value);
    query.bindValue(":id",IN_GenerateXP.packetid);
    query.exec();


    ////////////////////////////////////////////////////////////////////////////////////////////

    QString StartTotalXP2 = SendToHex.ConvertTo(IN_GenerateXP.StartTotalXP);

    Column_value = StartTotalXP2.toUtf8();
    Column_Name = "TotalXP";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Column_value);
    query.bindValue(":id",IN_GenerateXP.packetid);
    query.exec();

    ////////////////////////////////////////////////////////////////////////////////////////////

    Column_value = IN_GenerateXP.StartLevel.toUtf8();
    Column_Name = "Level (1)";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Column_value);
    query.bindValue(":id",IN_GenerateXP.packetid);
    query.exec();


    //    ////////////////////////////////////////////////////////////////////////////////////////////

    //    Column_value = "00";
    //    Column_Name = "TotalCMxp";
    //    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    //    query.bindValue(":val",Column_value);
    //    query.bindValue(":id",packetid);
    //    query.exec();


    //    ////////////////////////////////////////////////////////////////////////////////////////////

    //    Column_value = "00";
    //    Column_Name = "UnSpentCMs";
    //    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    //    query.bindValue(":val",Column_value);
    //    query.bindValue(":id",packetid);
    //    query.exec();


    //    ////////////////////////////////////////////////////////////////////////////////////////////

    //    Column_value = "00";
    //    Column_Name = "SpentCMs";
    //    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    //    query.bindValue(":val",Column_value);
    //    query.bindValue(":id",packetid);
    //    query.exec();



    db.commit();

    return dumMy1;
}

void MainWindow::AggroMovement()
{
    auto* CheckForAggroMovementTimer = qobject_cast<QTimer*>(sender());
    QString  CheckMovement = CheckForAggroMovementTimer->objectName();

    if(CheckForAggroMovementTimersVector.contains(CheckForAggroMovementTimer))
    {
        CheckForAggroMovementTimersVector.removeOne(CheckForAggroMovementTimer);
    }

    if(TestStatus == "Start")
    {
        packetparsing::packetvars IN_MainWindow;
        IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID+MastersClientsIP+MastersClientsPort);

        FacingDirection New_Movement1; //get class

        QString MOB_Master_c9 = objectpacket::Master_Map.value(Lock_Targets_ID.toUpper());
        QString MobX = MOB_Master_c9.mid(12,6);
        QString MobZ = MOB_Master_c9.mid(18,6);
        QString MobY = MOB_Master_c9.mid(24,6);

        QString xorC9 = New_Movement1.AGGRO_Radius_Movement
                ( IN_MainWindow.ClientsID,IN_MainWindow.ClientsIP,IN_MainWindow.ClientsPort,
                  Lock_X, Lock_Z, Lock_Y,Lock_Targets_ID,
                  MobX, MobZ, MobY);




        if(xorC9.isEmpty() == false)
        {
            QString  myx1 = Lock_X;
            int xfromhex1 = myx1.toInt(nullptr,16);
            float maintoonx1 = xfromhex1 / 128.0;

            QString  myz1 = Lock_Z;
            int zfromhex1 = myz1.toInt(nullptr,16);
            float maintoonz1 = zfromhex1 / 128.0;

            if(maintoonz1 > 130000)
            {
                maintoonz1 = maintoonz1 - 131072.00195193;
            }


            QString  myy1 = Lock_Y;
            int yfromhex1 = myy1.toInt(nullptr,16);
            float maintoony1 = yfromhex1 / 128.0;

            QString NewMobX = xorC9.mid(0,6);
            QString NewMobZ = xorC9.mid(6,6);
            QString NewMobY = xorC9.mid(12,6);




            QString tempstrx = NewMobX;
            int tempint1 = tempstrx.toInt(nullptr,16);
            float xinterlude = tempint1 / 128.0;

            QString tempstrz = NewMobZ;
            int tempint2 = tempstrz.toInt(nullptr,16);
            float  zinterlude = tempint2 / 128.0;

            if(zinterlude > 130000)
            {
                zinterlude = zinterlude - 131072.00195193;
            }

            QString tempstry = NewMobY;
            int tempint3 = tempstry.toInt(nullptr,16);
            float yinterlude = tempint3 / 128.0;


            float sub1 = maintoonx1 - xinterlude;
            float sub2 = maintoonz1 - zinterlude;
            float sub3 = maintoony1 - yinterlude;

            float power1 = qPow(sub1,2);
            float power2 = qPow(sub2,2);
            float power3 = qPow(sub3,2);

            float firstresult = power1 + power2 + power3;
            float result = qSqrt(firstresult);





            if(IN_MainWindow.holdid2.contains(Lock_Targets_ID))
            {
                int index = IN_MainWindow.holdid2.indexOf(Lock_Targets_ID);

                IN_MainWindow.holdx2.replace(index,NewMobX);
                IN_MainWindow.holdz2.replace(index,NewMobZ);
                IN_MainWindow.holdy2.replace(index,NewMobY);
            }

            if(!IN_MainWindow.holdid2.contains(Lock_Targets_ID))
            {
                IN_MainWindow.holdid2.append(Lock_Targets_ID);
                IN_MainWindow.holdx2.append(NewMobX);
                IN_MainWindow.holdz2.append(NewMobZ);
                IN_MainWindow.holdy2.append(NewMobY);
            }

            QByteArray TestC9 = objectpacket::Master_Map.value(Lock_Targets_ID);

            TestC9.replace(12,6,NewMobX.toUtf8());
            TestC9.replace(18,6,NewMobZ.toUtf8());
            TestC9.replace(24,6,NewMobY.toUtf8());


            objectpacket::Master_Map.insert(Lock_Targets_ID,TestC9);

            QString Channel = IN_MainWindow.Map_Channel_ID.key(Lock_Targets_ID);

            if(IN_MainWindow.Map_Channel_ID.contains(Channel))
            {
                QByteArray Holder = "0A1Fxxxx87C001BF543213" + IN_MainWindow.SessionID + "00xxxx";

                xorpacket packet2;
                QByteArray Recompressed2 = packet2.packetencrypt(TestC9);

                QByteArray Combined1 = Channel.toUtf8() + "c9xxxx00" + Recompressed2;

                Holder.replace(0,4,IN_MainWindow.serverid1);
                Holder.replace(4,4,IN_MainWindow.clientid1);

                QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_MainWindow.CharSelectID);
                QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

                increment GrpOut;
                QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
                Holder.replace(30,4,GrpOut_a);
                Servers_Last_MessageNumber = GrpOut_a.toUpper();

                MessNumbVect.replace(0,Servers_Last_MessageNumber);

                Opcodes::CharID_ServerMessageNumbers.insert(IN_MainWindow.CharSelectID,MessNumbVect);


                QByteArray ChanCount = IN_MainWindow.incrementmap.value(Channel);

                increment otherChannels;
                QByteArray ChansNewCount = otherChannels.count(ChanCount);
                Combined1.replace(4,4,ChansNewCount);

                IN_MainWindow.incrementmap.insert(Channel,ChansNewCount);

                Holder.append(Combined1);

                int index = SortChanelsNumbersVector.indexOf(Channel.toUtf8());
                SortChanelsValuesVector.replace(index,ChansNewCount);

                IN_MainWindow.ServersCheckChannelConfirm.clear();

                for(int re = 0; re < SortChanelsValuesVector.size(); re++)
                {
                    QByteArray ChannelsValue = SortChanelsValuesVector.at(re);
                    QByteArray Channel = SortChanelsNumbersVector.at(re);

                    if(ChannelsValue != "0000")
                    {
                        IN_MainWindow.ServersCheckChannelConfirm.append(Channel + ChannelsValue);
                        SortChanelsValuesVector.replace(re,"0000");
                    }
                }

                packetsize ResizePacket;
                QByteArray ResizePacket2 = ResizePacket.switchsize(Holder);
                Holder.replace(8,4,ResizePacket2.toUpper());

                crc sendcrc;
                QByteArray outcrc =  sendcrc.elcrc(Holder);
                Holder.append(outcrc);

                QHostAddress current_client_address;
                current_client_address.setAddress(QString::fromUtf8(IN_MainWindow.ClientsIP));
                quint16 current_client_port = IN_MainWindow.ClientsPort.toUShort(nullptr,10);
                QString changeIP = current_client_address.toString();

                QByteArray UpdateTheChannel = Holder.fromHex(Holder);


                QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);

                QDateTime dateTime = dateTime.currentDateTime();
                QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

                qDebug() << "";
                qDebug() << "";
                qDebug() << "----------------------------------------------------------";
                qDebug() << dateTimeString;
                qDebug() << "Aggro: ";
                qDebug() << "To Client: " + MainToon;
                qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
                qDebug() << "IP: " + IN_MainWindow.ClientsIP;
                qDebug() << "Port: " + IN_MainWindow.ClientsPort;
                qDebug() << "From Server: ";
                qDebug() << Holder;
                qDebug() << "----------------------------------------------------------";
                qDebug() << "";

                emit outgoingdata_game2(UpdateTheChannel,changeIP,current_client_port);
            }


            packetparsing::IPandPort_AllvariablesMap.insert(IN_MainWindow.ClientsID+IN_MainWindow.ClientsIP+IN_MainWindow.ClientsPort,IN_MainWindow);

            if(result < 2)
            {
                TestStatus = "";
            }
        }
    }





    int Values = 0;//ui->lineEdit_MovementChack->text().toUInt(nullptr,10);

    if(TestStatus == "Start")
    {
        QTimer *CheckForAggroMovementTimers  = new QTimer(this);
        CheckForAggroMovementTimers->setInterval(Values);
        CheckForAggroMovementTimers->setSingleShot(true);
        CheckForAggroMovementTimers->setObjectName(CheckMovement);
        CheckForAggroMovementTimersVector.append(CheckForAggroMovementTimers);
        CheckForAggroMovementTimers->start();

        connect(CheckForAggroMovementTimers, SIGNAL(timeout()), this, SLOT(AggroMovement()));
    }
}




void MainWindow::ResendingChannels()
{
    auto* SendingChannelsTimer = qobject_cast<QTimer*>(sender());
    QString  ID_IP_PORT = SendingChannelsTimer->objectName();

    if(reSendChannelsTimersVector.contains(SendingChannelsTimer))
    {
        reSendChannelsTimersVector.removeOne(SendingChannelsTimer);
    }

    packetparsing::packetvars IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_MainWindow.CharSelectID);


    qDebug() << "";
    qDebug() << "";
    qDebug() << "";
    qDebug() << "in ResendingChannels";

    if(IN_MainWindow.StopSending == false)
    {

        QMapIterator<QByteArray,QByteArray> iter (IN_MainWindow.ResendAllChannelsMap);
        while(iter.hasNext())
        {
            iter.next();
            QByteArray ServersCheckChannelConfirm1 = iter.key();
            QByteArray Packet = iter.value();

            qDebug() << "";
            qDebug() << "ServersCheckChannelConfirm1 = " << ServersCheckChannelConfirm1;

            if(Packet.size() > 0)
            {
                int iter2 = 0;

                IN_MainWindow.ConfirmRemove = true;

                do
                {
                    QByteArray serversChannel = ServersCheckChannelConfirm1.mid(iter2,2);
                    iter2 += 2;
                    QByteArray serversChannelsCount = ServersCheckChannelConfirm1.mid(iter2,4);
                    iter2 += 4;

                    qDebug() << "serversChannel = " << serversChannel;
                    qDebug() << "serversChannelsCount = " << serversChannelsCount;


                    QByteArray clientsChannelsCount = IN_MainWindow.Client_incrementmap.value(serversChannel);

                    qDebug() << "clientsChannelsCount = " << clientsChannelsCount;

                    QByteArray sByte1 = serversChannelsCount.mid(0,2);
                    QByteArray sByte2 = serversChannelsCount.mid(2,2);
                    QByteArray sByteReverse = sByte2 + sByte1;
                    int sByte = sByteReverse.toInt(nullptr,16);

                    qDebug() << "Servers count to int = " << sByte;

                    QByteArray cByte1 = clientsChannelsCount.mid(0,2);
                    QByteArray cByte2 = clientsChannelsCount.mid(2,2);
                    QByteArray cByteReverse = cByte2 + cByte1;
                    int cByte = cByteReverse.toInt(nullptr,16);

                    qDebug() << "Clients count to int = " << sByte;

                    if(sByte <= cByte)
                    {
                        IN_MainWindow.RemoveResendChannels = true;
                    }
                    else
                    {
                        IN_MainWindow.RemoveResendChannels = false;
                        IN_MainWindow.ConfirmRemove = false;
                    }

                }while(iter2 < ServersCheckChannelConfirm1.size());

                if(IN_MainWindow.RemoveResendChannels == true)
                {
                    IN_MainWindow.RemoveResendChannels = false;

                    if(IN_MainWindow.ConfirmRemove == true)
                    {
                        IN_MainWindow.ConfirmRemove = false;

                        IN_MainWindow.ResendAllChannelsMap.remove(ServersCheckChannelConfirm1);

                    }
                }
            }
        }


        if(IN_MainWindow.ResendAllChannelsMap.contains(IN_MainWindow.ServersCheckChannelConfirm))// if any left and the timer is up for it
        {
            IN_MainWindow.resendingChannelCounter++;


            QByteArray ResendingChannel = "";
            QByteArray ServersCheckChannelConfirm2 = "";

            ResendingChannel = IN_MainWindow.ResendAllChannelsMap.value(IN_MainWindow.ServersCheckChannelConfirm);

            ServersCheckChannelConfirm2 = IN_MainWindow.ResendAllChannelsMap.key(ResendingChannel);

            qDebug() << "ServersCheckChannelConfirm2 = " << ServersCheckChannelConfirm2;

            QVector<QByteArray> tempVect = Opcodes::CharID_CLientID_IP_PORT_Map.value(IN_MainWindow.CharSelectID);
            IN_MainWindow.ClientsID = tempVect.at(0);
            IN_MainWindow.ClientsIP = tempVect.at(1);
            IN_MainWindow.ClientsPort = tempVect.at(2);

            QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

            increment GrpOut;
            QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
            ResendingChannel.replace(30,4,GrpOut_a);
            Servers_Last_MessageNumber = GrpOut_a.toUpper();

            MessNumbVect.replace(0,Servers_Last_MessageNumber);

            Opcodes::CharID_ServerMessageNumbers.insert(IN_MainWindow.CharSelectID,MessNumbVect);

            int index = ResendingChannel.indexOf(IN_MainWindow.SessionID);
            int SessionSize = IN_MainWindow.SessionID.size();

            increment Resending;
            QByteArray Resending2 = Resending.count(Servers_Last_MessageNumber);
            ResendingChannel.replace(index+SessionSize,4,Resending2);
            Servers_Last_MessageNumber = Resending2.toUpper();

            crc sendcrc;
            QByteArray outcrc =  sendcrc.elcrc(ResendingChannel);
            ResendingChannel.append(outcrc);

            QHostAddress current_client_address;
            current_client_address.setAddress(QString::fromUtf8(IN_MainWindow.ClientsIP));
            quint16 current_client_port = IN_MainWindow.ClientsPort.toUShort(nullptr,10);
            QString changeIP = current_client_address.toString();

            QByteArray resending = ResendingChannel.fromHex(ResendingChannel);
            QHostAddress newsender = QHostAddress(changeIP);
            worldthread::udpsocket3->writeDatagram(resending,newsender,current_client_port);

            QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);

            QDateTime dateTime = dateTime.currentDateTime();
            QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

            qDebug() << "";
            qDebug() << "";
            qDebug() << "----------------------------------------------------------";
            qDebug() << dateTimeString;
            qDebug() << "Resending Channels: " << IN_MainWindow.resendingChannelCounter;
            qDebug() << "To Client: " + MainToon;
            qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
            qDebug() << "IP: " + changeIP;
            qDebug() << "Port: " + IN_MainWindow.ClientsPort;
            qDebug() << "From Server: ";
            qDebug() << ResendingChannel;
            qDebug() << "----------------------------------------------------------";
            qDebug() << "";



            //if it was resent leave it in just incase it is missed again
            //            int Value = ui->lineEdit_137->text().toInt(nullptr,10);
            //            QTimer *SendChannelsTimers  = new QTimer(this);
            //            SendChannelsTimers->setInterval(Value);
            //            SendChannelsTimers->setSingleShot(true);
            //            SendChannelsTimers->setObjectName(ID_IP_PORT);
            //            reSendChannelsTimersVector.append(SendChannelsTimers);
            //            SendChannelsTimers->start();

            //            connect(SendChannelsTimers, SIGNAL(timeout()), this, SLOT(ResendingChannels()));
        }
        else
        {
            qDebug() << "Did not resend the channel ";
        }
    }
}

void MainWindow::ResendingFBs()
{
    qDebug() << "in Resending FBs ";

    auto* SendingFBsTimer = qobject_cast<QTimer*>(sender());
    QString  ID_IP_PORT = SendingFBsTimer->objectName();

    if(reSendFBsTimersVector.contains(SendingFBsTimer))
    {
        reSendFBsTimersVector.removeOne(SendingFBsTimer);
    }

    packetparsing::packetvars IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());



    QMapIterator<QByteArray,QByteArray> iter (IN_MainWindow.ResendFBsMap);// removing all that have been confirmed by the client
    while(iter.hasNext())
    {
        iter.next();
        QByteArray LastFB = iter.key();
        QByteArray ResendingFB = iter.value();

        QByteArray ByteFB1 = LastFB.mid(0,2);
        QByteArray ByteFB2 = LastFB.mid(2,2);
        QByteArray reverseFB2Bytes = ByteFB2 + ByteFB1;

        int LastFBToInt = reverseFB2Bytes.toInt(nullptr,16);

        QByteArray ClientsFB2Bytes = IN_MainWindow.ClientsLastFBConfirm;
        QByteArray Byte_FB1 = ClientsFB2Bytes.mid(0,2);
        QByteArray Byte_FB2 = ClientsFB2Bytes.mid(2,2);
        QByteArray reverse_FB2Bytes = Byte_FB2 + Byte_FB1;

        int ClientsFBToInt = reverse_FB2Bytes.toInt(nullptr,16);

        if(LastFBToInt <= ClientsFBToInt)
        {
            IN_MainWindow.ResendFBsMap.remove(LastFB);
        }

        if(IN_MainWindow.ResendAllFBs == true)
        {
            IN_MainWindow.resendingFBCounter++;

            int index = ResendingFB.indexOf(IN_MainWindow.SessionID);
            int SessionSize = IN_MainWindow.SessionID.size();


            QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_MainWindow.CharSelectID);

            QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

            increment GrpOut;
            QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
            ResendingFB.replace(30,4,GrpOut_a);
            Servers_Last_MessageNumber = GrpOut_a.toUpper();

            MessNumbVect.replace(0,Servers_Last_MessageNumber);

            Opcodes::CharID_ServerMessageNumbers.insert(IN_MainWindow.CharSelectID,MessNumbVect);


            crc sendcrc;
            QByteArray outcrc =  sendcrc.elcrc(ResendingFB);
            ResendingFB.append(outcrc);

            QHostAddress current_client_address;
            current_client_address.setAddress(QString::fromUtf8(IN_MainWindow.ClientsIP));
            quint16 current_client_port = IN_MainWindow.ClientsPort.toUShort(nullptr,10);
            QString changeIP = current_client_address.toString();

            QByteArray resending = ResendingFB.fromHex(ResendingFB);
            QHostAddress newsender = QHostAddress(changeIP);
            worldthread::udpsocket3->writeDatagram(resending,newsender,current_client_port);

            QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);

            QDateTime dateTime = dateTime.currentDateTime();
            QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

            qDebug() << "";
            qDebug() << "";
            qDebug() << "----------------------------------------------------------";
            qDebug() << dateTimeString;
            qDebug() << "Resending_All_FBs: " << IN_MainWindow.resendingFBCounter;
            qDebug() << "To Client: " + MainToon;
            qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
            qDebug() << "IP: " + changeIP;
            qDebug() << "Port: " + IN_MainWindow.ClientsPort;
            qDebug() << "From Server: ";
            qDebug() << ResendingFB;
            qDebug() << "----------------------------------------------------------";
            qDebug() << "";

        }
    }

    if(IN_MainWindow.ResendAllFBs == true)
    {
        IN_MainWindow.ResendAllFBs = false;
    }

    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_MainWindow.CharSelectID);
    QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

    if(IN_MainWindow.ResendFBsMap.contains(Servers_Last_FB_MessageNumber))// if any left and the timer is up for it
    {
        QByteArray ClientsFB2Bytes = IN_MainWindow.ClientsLastFBConfirm;
        QByteArray Byte_FB1 = ClientsFB2Bytes.mid(0,2);
        QByteArray Byte_FB2 = ClientsFB2Bytes.mid(2,2);
        QByteArray reverse_FB2Bytes = Byte_FB2 + Byte_FB1;

        int ClientsFBToInt = reverse_FB2Bytes.toInt(nullptr,16);


        QByteArray LastFBBytes = Servers_Last_FB_MessageNumber;
        QByteArray ByteFB1 = LastFBBytes.mid(0,2);
        QByteArray ByteFB2 = LastFBBytes.mid(2,2);
        QByteArray reverseFB2Bytes = ByteFB2 + ByteFB1;

        int LastFBToInt = reverseFB2Bytes.toInt(nullptr,16);


        if(LastFBToInt > ClientsFBToInt)// if ours is greater than the clients, then it has not been confirmed
        {
            IN_MainWindow.resendingFBCounter++;


            QByteArray ResendingFB = "";

            ResendingFB = IN_MainWindow.ResendFBsMap.value(Servers_Last_FB_MessageNumber);

            int index = ResendingFB.indexOf(IN_MainWindow.SessionID);
            int SessionSize = IN_MainWindow.SessionID.size();

            int index2 = ResendingFB.indexOf("xxXXxxXX");

            if(index != -1)
            {
                if(IN_MainWindow.Server_2A00_reply == true)
                {
                    ResendingFB.replace(index2,8,"BF543213");
                }
                else
                {
                    ResendingFB.replace(index2,8,"F1463213");
                }
            }

            QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

            increment Resending;
            QByteArray Resending2 = Resending.count(Servers_Last_MessageNumber);
            ResendingFB.replace(index+SessionSize + 2,4,Resending2);
            Servers_Last_MessageNumber = Resending2.toUpper();

            MessNumbVect.replace(0,Servers_Last_MessageNumber);

            Opcodes::CharID_ServerMessageNumbers.insert(IN_MainWindow.CharSelectID,MessNumbVect);

            crc sendcrc;
            QByteArray outcrc =  sendcrc.elcrc(ResendingFB);
            ResendingFB.append(outcrc);

            QHostAddress current_client_address;
            current_client_address.setAddress(QString::fromUtf8(IN_MainWindow.ClientsIP));
            quint16 current_client_port = IN_MainWindow.ClientsPort.toUShort(nullptr,10);
            QString changeIP = current_client_address.toString();

            QByteArray resending = ResendingFB.fromHex(ResendingFB);
            QHostAddress newsender = QHostAddress(changeIP);
            worldthread::udpsocket3->writeDatagram(resending,newsender,current_client_port);

            QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);

            QDateTime dateTime = dateTime.currentDateTime();
            QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

            qDebug() << "";
            qDebug() << "";
            qDebug() << "----------------------------------------------------------";
            qDebug() << dateTimeString;
            qDebug() << "Resending FBs: " << IN_MainWindow.resendingFBCounter;
            qDebug() << "To Client: " + MainToon;
            qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
            qDebug() << "IP: " + changeIP;
            qDebug() << "Port: " + IN_MainWindow.ClientsPort;
            qDebug() << "From Server: ";
            qDebug() << ResendingFB;
            qDebug() << "----------------------------------------------------------";
            qDebug() << "";

            //            //if it was resent leave it in just incase it is missed again
            //            QTimer *SendFBTimers  = new QTimer(this);
            //            SendFBTimers->setInterval(400);
            //            SendFBTimers->setSingleShot(true);
            //            SendFBTimers->setObjectName(ID_IP_PORT);
            //            reSendFBsTimersVector.append(SendFBTimers);
            //            SendFBTimers->start();

            //            connect(SendFBTimers, SIGNAL(timeout()), this, SLOT(ResendingFBs()));
        }
        else
        {
            qDebug() << "Did not resend the FB ";

            IN_MainWindow.ResendFBsMap.remove(Servers_Last_FB_MessageNumber);// remove it once its confirmed if the iter dont get it first
        }
    }

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_MainWindow);

}

void MainWindow::Resending42ECs()
{
    auto* Sending42sTimer = qobject_cast<QTimer*>(sender());
    QString  ID_IP_PORT = Sending42sTimer->objectName();

    if(reSend42ecTimersVector.contains(Sending42sTimer))
    {
        reSend42ecTimersVector.removeOne(Sending42sTimer);
    }

    packetparsing::packetvars IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    QMapIterator<QByteArray,QByteArray> iter (IN_MainWindow.Resend42ecsMap);// removing all that have been confirmed by the client
    while(iter.hasNext())
    {
        iter.next();
        QByteArray LastS42ec = iter.key();
        QByteArray ByteS1 = LastS42ec.mid(0,2);
        QByteArray ByteS2 = LastS42ec.mid(2,2);
        QByteArray reverseS2Bytes = ByteS2 + ByteS1;

        int Last42ecToInt = reverseS2Bytes.toInt(nullptr,16);

        QByteArray ByteC1 = IN_MainWindow.Clients42EC.mid(0,2);
        QByteArray ByteC2 = IN_MainWindow.Clients42EC.mid(2,2);
        QByteArray reverseC2Bytes = ByteC2 + ByteC1;

        int Clients42ecToInt = reverseC2Bytes.toInt(nullptr,16);

        if(Last42ecToInt <= Clients42ecToInt)
        {
            IN_MainWindow.Resend42ecsMap.remove(LastS42ec);
        }
    }

    if(IN_MainWindow.Resend42ecsMap.contains(IN_MainWindow.Channel42messnum))// if any left and the timer is up for it
    {
        QByteArray ByteC1 = IN_MainWindow.Clients42EC.mid(0,2);
        QByteArray ByteC2 = IN_MainWindow.Clients42EC.mid(2,2);
        QByteArray reverseC2Bytes = ByteC2 + ByteC1;

        int Clients42ecToInt = reverseC2Bytes.toInt(nullptr,16);

        QByteArray Last42ec2Bytes = IN_MainWindow.Channel42messnum;
        QByteArray ByteS1 = Last42ec2Bytes.mid(0,2);
        QByteArray ByteS2 = Last42ec2Bytes.mid(2,2);
        QByteArray reverseS2Bytes = ByteS2 + ByteS1;

        int Last42ecToInt = reverseS2Bytes.toInt(nullptr,16);

        if(Last42ecToInt > Clients42ecToInt)// if ours is greater than the clients, then it has not been confirmed
        {
            IN_MainWindow.resending42ecCounter++;


            QByteArray Resening42EC = "";

            Resening42EC = IN_MainWindow.Resend42ecsMap.value(IN_MainWindow.Channel42messnum);

            int index = Resening42EC.indexOf(IN_MainWindow.SessionID);
            int SessionSize = IN_MainWindow.SessionID.size();

            QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_MainWindow.CharSelectID);
            QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

            increment Resening;
            QByteArray Resening2 = Resening.count(Servers_Last_MessageNumber);
            Resening42EC.replace(index+SessionSize,4,Resening2);
            Servers_Last_MessageNumber = Resening2.toUpper();

            crc sendcrc;
            QByteArray outcrc =  sendcrc.elcrc(Resening42EC);
            Resening42EC.append(outcrc);

            QHostAddress current_client_address;
            current_client_address.setAddress(QString::fromUtf8(IN_MainWindow.ClientsIP));
            quint16 current_client_port = IN_MainWindow.ClientsPort.toUShort(nullptr,10);
            QString changeIP = current_client_address.toString();

            QByteArray resending = Resening42EC.fromHex(Resening42EC);
            QHostAddress newsender = QHostAddress(changeIP);
            worldthread::udpsocket3->writeDatagram(resending,newsender,current_client_port);

            QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);

            QDateTime dateTime = dateTime.currentDateTime();
            QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

            qDebug() << "";
            qDebug() << "";
            qDebug() << "----------------------------------------------------------";
            qDebug() << dateTimeString;
            qDebug() << "Resending 42ECs: " << IN_MainWindow.resending42ecCounter;
            qDebug() << "To Client: " + MainToon;
            qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
            qDebug() << "IP: " + changeIP;
            qDebug() << "Port: " + IN_MainWindow.ClientsPort;
            qDebug() << "From Server: ";
            qDebug() << Resening42EC;
            qDebug() << "----------------------------------------------------------";
            qDebug() << "";


            //            //if it was resent leave it in just incase it is missed again
            //            QTimer *Send42ecTimers  = new QTimer(this);
            //            Send42ecTimers->setInterval(400);
            //            Send42ecTimers->setSingleShot(true);
            //            Send42ecTimers->setObjectName(ID_IP_PORT);
            //            reSend42ecTimersVector.append(Send42ecTimers);
            //            Send42ecTimers->start();

            //            connect(Send42ecTimers, SIGNAL(timeout()), this, SLOT(Resending42ECs()));
        }
        else
        {
            qDebug() << "Did not resend the 42ec ";

            IN_MainWindow.Resend42ecsMap.remove(IN_MainWindow.Channel42messnum);// remove it once its confirmed if the iter dont get it first
        }
    }

    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_MainWindow);
}


void MainWindow::on_StandingStill()
{
    auto* StandingStillTimer = qobject_cast<QTimer*>(sender());
    QString  ID_IP_PORT = StandingStillTimer->objectName();
    if(StandingStillTimersVector.contains(StandingStillTimer))
    {
        StandingStillTimersVector.removeOne(StandingStillTimer);
    }

    StandingStillTimer->deleteLater();

    if(packetparsing::IPandPort_AllvariablesMap.contains(ID_IP_PORT.toUtf8()))
    {
        packetparsing::packetvars IN_StandingStill;
        IN_StandingStill = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

        QByteArray Disconnect_or_KeepAlive = "";

        if(IN_StandingStill.Disconnected == false)
        {
            if(ui->checkBox_35->isChecked() == true && ID_IP_PORT.toUtf8() == MastersClientsID+MastersClientsIP+MastersClientsPort)
            {
                reDoGreeting = true;
                IN_StandingStill.WorldGreetingFlag = true;
            }

            qDebug() << "";

            if(reDoGreeting == true)
            {
                reDoGreeting = false;
                IN_StandingStill.Quest = true;
                ui->checkBox_35->setChecked(false);

                packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_StandingStill);

                Quests sendto;
                QByteArray YoMama = sendto.WelcomeGreetings(ID_IP_PORT.toUtf8());

                qDebug() << "Yo Mama" << YoMama;

                IN_StandingStill = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());
            }

            qDebug() << "IN_StandingStill.CurrentQuestMenuID_2" << IN_StandingStill.CurrentQuestMenuID;

            qDebug() << "IN_StandingStill.WorldGreetingFlag" << IN_StandingStill.WorldGreetingFlag;
            qDebug() << "IN_StandingStill.Quest" << IN_StandingStill.Quest;
            qDebug() << "";

            if(Opcodes::CharID_ServerMessageNumbers.contains(IN_StandingStill.CharSelectID))
            {
                QByteArray Holder = "0A1Fxxxx88C001BF543213" + IN_StandingStill.SessionID + "00xxxx";

                Holder.replace(0,4,IN_StandingStill.serverid1);
                Holder.replace(4,4,IN_StandingStill.clientid1);

                QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_StandingStill.CharSelectID);
                QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

                QString NewFB = "F901XXXX12";

                QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

                increment Text;
                QByteArray Text2 = Text.count(Servers_Last_FB_MessageNumber);
                int index = NewFB.indexOf("XXXX");
                NewFB.replace(index,4,Text2);
                Servers_Last_FB_MessageNumber = Text2.toUpper();

                MessNumbVect.replace(1,Servers_Last_FB_MessageNumber);

                Holder.append(NewFB.toUtf8());

                increment GrpOut;
                QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
                Holder.replace(30,4,GrpOut_a);
                Servers_Last_MessageNumber = GrpOut_a.toUpper();

                MessNumbVect.replace(0,Servers_Last_MessageNumber);

                Opcodes::CharID_ServerMessageNumbers.insert(IN_StandingStill.CharSelectID,MessNumbVect);

                packetsize ResizePacket;
                QByteArray ResizePacket2 = ResizePacket.switchsize(Holder);
                Holder.replace(8,4,ResizePacket2.toUpper());

                crc sendcrc;
                QByteArray outcrc =  sendcrc.elcrc(Holder);
                Holder.append(outcrc);

                QHostAddress current_client_address;
                current_client_address.setAddress(QString::fromUtf8(IN_StandingStill.ClientsIP));
                quint16 current_client_port = IN_StandingStill.ClientsPort.toUShort(nullptr,10);
                QString changeIP = current_client_address.toString();

                QByteArray KeepAlive1 = Holder.fromHex(Holder);

                QString MainToon = checkthezone::NPCsNames.value(IN_StandingStill.CharSelectID);

                QDateTime dateTime = dateTime.currentDateTime();
                QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

                qDebug() << "";
                qDebug() << "";
                qDebug() << "----------------------------------------------------------";
                qDebug() << dateTimeString;
                qDebug() << "Standing_Still: ";
                qDebug() << "To Client: " + MainToon;
                qDebug() << "IN_StandingStill.CharSelectID = " << IN_StandingStill.CharSelectID;
                qDebug() << "IP: " + changeIP;
                qDebug() << "Port: " + IN_StandingStill.ClientsPort;
                qDebug() << "From Server: ";
                qDebug() << Holder;
                qDebug() << "----------------------------------------------------------";
                qDebug() << "";


                if(IN_StandingStill.disconnectCount == 0)
                {
                    IN_StandingStill.OldConnectionCount = Servers_Last_FB_MessageNumber;
                }

                IN_StandingStill.disconnectCount++;

                qDebug() << "IN_StandingStill.ReplyConfirm = " << IN_StandingStill.ReplyConfirm.mid(4,4);
                qDebug() << "IN_StandingStill.OldConnectionCount = " << IN_StandingStill.OldConnectionCount;
                qDebug() << "IN_StandingStill.disconnectCount1 = " << IN_StandingStill.disconnectCount;

                if(IN_StandingStill.disconnectCount == 6)
                {
                    qDebug() << "sendto.DisconnectCheck";

                    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_StandingStill);

                    Opcodes sendto;
                    Disconnect_or_KeepAlive = sendto.DisconnectCheck(IN_StandingStill.ClientsID, IN_StandingStill.ClientsIP, IN_StandingStill.ClientsPort);

                    IN_StandingStill = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

                    qDebug() << "IN_StandingStill.CurrentQuestMenuID_3" << IN_StandingStill.CurrentQuestMenuID;
                }

                if(Disconnect_or_KeepAlive != "Disconnect")
                {
                    QHostAddress newsender = QHostAddress(changeIP);

                    worldthread::udpsocket3->writeDatagram(KeepAlive1,newsender,current_client_port);

                    /////////////////////////Save Location///////////////////////////


                    QSqlQuery querytlpt2;
                    QString tablesel2 = "MAINTOON";
                    QString objecttlpt2 = "ObjectID (4)";
                    QString worldtlpt = "World (1)";
                    QString xtlpt = "X (3)";
                    QString ztlpt = "Z (3)";
                    QString ytlpt = "Y (3)";
                    QString facing1 = "Facing (1)";

                    QString tlptid2 = IN_StandingStill.CharSelectID;
                    QString chosenworld = QString("%1").arg(IN_StandingStill.masterworld,2,16,QLatin1Char('0')).toUpper();
                    QString facing = IN_StandingStill.masterf;
                    QString x1 = QString::fromUtf8(IN_StandingStill.masterx);
                    QString z1 = QString::fromUtf8(IN_StandingStill.masterz);
                    QString y1 = QString::fromUtf8(IN_StandingStill.mastery);



                    if(chosenworld.isEmpty() == false && facing.isEmpty() == false && x1.isEmpty() == false &&
                            z1.isEmpty() == false && y1.isEmpty() == false)
                    {
                        db.transaction();

                        querytlpt2.prepare(QStringLiteral("UPDATE %1 SET [%2] = :val2,[%3] = :val3,[%4] = :val4,[%5] = :val5,[%6] = :val6 WHERE [%7] = :val").arg(tablesel2).arg(xtlpt).arg(ytlpt).arg(ztlpt).arg(worldtlpt).arg(facing1).arg(objecttlpt2));

                        querytlpt2.bindValue(":val",tlptid2);
                        querytlpt2.bindValue(":val2",x1.toUpper());
                        querytlpt2.bindValue(":val3",y1.toUpper());
                        querytlpt2.bindValue(":val4",z1.toUpper());
                        querytlpt2.bindValue(":val5",chosenworld.toUpper());
                        querytlpt2.bindValue(":val6",facing.toUpper());

                        querytlpt2.exec();
                        db.commit();
                    }
                }

                if((Disconnect_or_KeepAlive == "KeepAlive" && IN_StandingStill.disconnectCount == 6) ||
                        (IN_StandingStill.disconnectCount <= 5))
                {
                    if(IN_StandingStill.disconnectCount == 6)
                    {
                        IN_StandingStill.disconnectCount = 0;
                    }

                    packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT.toUtf8(),IN_StandingStill);

                    QTimer *StandingTimers  = new QTimer(this);
                    StandingTimers->setInterval(3500);
                    StandingTimers->setSingleShot(true);
                    StandingTimers->setObjectName(ID_IP_PORT);
                    StandingStillTimersVector.append(StandingTimers);
                    StandingTimers->start();

                    connect(StandingTimers ,SIGNAL (timeout()),this,SLOT(on_StandingStill()));
                }
            }
            else
            {
                Disconnect_or_KeepAlive = "Disconnect";
            }
        }
        else
        {
            Disconnect_or_KeepAlive = "Disconnect";
        }

        if(Disconnect_or_KeepAlive == "Disconnect")
        {
            Opcodes sendto;
            sendto.RemoveFromGame(IN_StandingStill.ClientsID, IN_StandingStill.ClientsIP, IN_StandingStill.ClientsPort);

            QString MainToon = checkthezone::NPCsNames.value(IN_StandingStill.CharSelectID);

            qDebug() << "Player: " + MainToon + " has disconnected or logged out";

            packetparsing::IPandPort_AllvariablesMap.remove(IN_StandingStill.ClientsID + IN_StandingStill.ClientsIP + IN_StandingStill.ClientsPort);
        }

        qDebug() << "IN_StandingStill.disconnectCount2 = " << IN_StandingStill.disconnectCount;

        qDebug() << "Disconnect_or_KeepAlive " << Disconnect_or_KeepAlive;

        qDebug() << "IN_StandingStill.CurrentQuestMenuID_4" << IN_StandingStill.CurrentQuestMenuID;

    }


}


QByteArray MainWindow::UpdateChannelMaps(QByteArray ClientID, QByteArray ClientsIP, QByteArray ClientsPort)
{
    qDebug() << "inside UpdateChannelMaps ";

    packetparsing::packetvars IN_MainWindow;
    IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientID + ClientsIP + ClientsPort);

    qDebug() << "ClientID " << ClientID;
    qDebug() << "ClientsIP " << ClientsIP;
    qDebug() << "ClientsPort " << ClientsPort;

    QByteArray hex3 = IN_MainWindow.masterz;

    int hexz = hex3.toInt(nullptr,16);
    float numtofloatz = hexz / 128.0;

    if(numtofloatz > 130000.0) //neg z fix leave this in!
    {
        float smallsub2 = numtofloatz - 131072.00195193;
        numtofloatz = smallsub2;
    }

    QByteArray array3 (reinterpret_cast<const char*>(&numtofloatz), sizeof(numtofloatz));
    QByteArray New4z = array3.toHex().toUpper();



    QString NewFacing4 = IN_MainWindow.facing_map.value(IN_MainWindow.masterf.toUpper()).toUpper();

    //xor new x z y facing and animation
    IN_MainWindow.Dial_ALL_Values2 = IN_MainWindow.Dial_ALL_Values;
    IN_MainWindow.Xor_Object_ID2 = IN_MainWindow.Xor_Object_ID;

    QByteArray CurrentC9 = objectpacket::Master_Map.value(IN_MainWindow.CharSelectID.toUtf8()).toUpper();

    QByteArray OldX = CurrentC9.mid(12,6);
    QByteArray OldZ = CurrentC9.mid(18,6);
    QByteArray OldY = CurrentC9.mid(24,6);
    QByteArray OldFacing = CurrentC9.mid(30,2);

    QByteArray Oldz4 = CurrentC9.mid(100,8);
    QByteArray OldFacing4 = CurrentC9.mid(108,8);

    QByteArray OldAnimation = CurrentC9.mid(116,2);
    QByteArray OldTarget = CurrentC9.mid(118,8);

    if(OldTarget != IN_MainWindow.Target_ID.toUpper() && IN_MainWindow.Target_ID.isEmpty() == false)
    {
        qlonglong OldTargetxor = OldTarget.toLongLong(nullptr,16);
        qlonglong NewTarget_IDxor = IN_MainWindow.Target_ID.toLongLong(nullptr,16);
        qlonglong Output_Xor = NewTarget_IDxor ^ OldTargetxor;
        QString Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(118,8,Output_Xor_2.toUtf8());//-----------------------X

        CurrentC9.replace(118,8,New4z.toUpper());
    }

    if(Oldz4 != New4z.toUpper() && New4z.isEmpty() == false)
    {
        qlonglong Oldz4xor = Oldz4.toLongLong(nullptr,16);
        qlonglong Newz4xor = New4z.toLongLong(nullptr,16);
        qlonglong Output_Xor = Newz4xor ^ Oldz4xor;
        QString Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(100,8,Output_Xor_2.toUtf8());//-----------------------X

        CurrentC9.replace(100,8,New4z.toUpper());
    }

    if(NewFacing4 != OldFacing4.toUpper() && OldFacing4.isEmpty() == false)
    {
        qlonglong OldFacing4xor = OldFacing4.toLongLong(nullptr,16);
        qlonglong NewFacing4xor = NewFacing4.toLongLong(nullptr,16);
        qlonglong Output_Xor = NewFacing4xor ^ OldFacing4xor;
        QString Output_Xor_2 = QString("%1").arg(Output_Xor,8,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(108,8,Output_Xor_2.toUtf8());//-----------------------X

        CurrentC9.replace(108,8,NewFacing4.toUtf8().toUpper());
    }

    //--------------------------------X

    if(OldX != IN_MainWindow.masterx.toUpper() && IN_MainWindow.masterx.isEmpty() == false)
    {
        qlonglong OldXxor = OldX.toLongLong(nullptr,16);
        qlonglong NewXxor = IN_MainWindow.masterx.toLongLong(nullptr,16);
        qlonglong Output_Xor = NewXxor ^ OldXxor;
        QString Output_Xor_2 = QString("%1").arg(Output_Xor,6,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(12,6,Output_Xor_2.toUtf8());//-----------------------X

        CurrentC9.replace(12,6,IN_MainWindow.masterx.toUpper());
    }


    //---------------------------Z

    if(OldZ != IN_MainWindow.masterz.toUpper() && IN_MainWindow.masterz.isEmpty() == false)
    {
        qlonglong OldZxor = OldZ.toLongLong(nullptr,16);
        qlonglong NewZxor = IN_MainWindow.masterz.toLongLong(nullptr,16);
        qlonglong Output_Xor_Z_1 = NewZxor ^ OldZxor;
        QString Output_Xor_Z = QString("%1").arg(Output_Xor_Z_1,6,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(18,6,Output_Xor_Z.toUtf8());//----------------------Z

        CurrentC9.replace(18,6,IN_MainWindow.masterz.toUpper());
    }


    //--------------------------------Y

    if(OldY != IN_MainWindow.mastery.toUpper() && IN_MainWindow.mastery.isEmpty() == false)
    {
        qlonglong OldYxor = OldY.toLongLong(nullptr,16);
        qlonglong NewYxor = IN_MainWindow.mastery.toLongLong(nullptr,16);
        qlonglong Output_X_Y = NewYxor ^ OldYxor;
        QString Output_Xor_Y_2 = QString("%1").arg(Output_X_Y,6,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(24,6,Output_Xor_Y_2.toUtf8());

        CurrentC9.replace(24,6,IN_MainWindow.mastery.toUpper());
    }

    //--------------------------------Facing

    if(OldFacing != IN_MainWindow.masterf.toUpper() && IN_MainWindow.masterf.isEmpty() == false)
    {
        int OldFacing1 = OldFacing.toInt(nullptr,16);
        int NewFacing1 = IN_MainWindow.masterf.toInt(nullptr,16);
        int Output_Xor1 = OldFacing1 ^ NewFacing1;
        QString Output_Xor2 = QString("%1").arg(Output_Xor1,2,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(30,2,Output_Xor2.toUtf8().toUpper());//----------------facing

        CurrentC9.replace(30,2,IN_MainWindow.masterf.toUpper());
    }


    //---------------------------------Animation

    if(OldAnimation != IN_MainWindow.myAnimation.toUpper() && IN_MainWindow.myAnimation.isEmpty() == false)
    {
        int AGGRO_Animation_Old1 = OldAnimation.toInt(nullptr,16);
        int Animation_New1 = IN_MainWindow.myAnimation.toInt(nullptr,16);
        int Animation_New2 = AGGRO_Animation_Old1 ^ Animation_New1;
        QString Output_New = QString("%1").arg(Animation_New2,2,16,QLatin1Char('0'));
        IN_MainWindow.Xor_Object_ID2.replace(116,2,Output_New.toUpper().toUtf8());

        CurrentC9.replace(116,2,IN_MainWindow.myAnimation.toUpper());
    }

    objectpacket::Master_Map.insert(IN_MainWindow.CharSelectID.toUtf8(),CurrentC9);
    //generator::Players_Map.insert(IN_MainWindow.CharSelectID.toUtf8(),CurrentC9);



    packetparsing::IPandPort_AllvariablesMap.insert(ClientID+ClientsIP+ClientsPort,IN_MainWindow);

    QMapIterator<QByteArray,struct packetparsing::packetvars> StructIter (packetparsing::IPandPort_AllvariablesMap);
    while(StructIter.hasNext())
    {
        packetparsing::packetvars IN_MainWindow_Switch;

        StructIter.next();
        QByteArray ID_IP_PORT = StructIter.key();
        IN_MainWindow_Switch = StructIter.value();//all other players structs

        if(IN_MainWindow_Switch.CharSelectID.isEmpty() == false && IN_MainWindow_Switch.flipped == true && IN_MainWindow_Switch.CharSelectID != IN_MainWindow.CharSelectID)
        {
            if(IN_MainWindow_Switch.holdid2.contains(IN_MainWindow.CharSelectID))
            {
                int index = IN_MainWindow_Switch.holdid2.indexOf(IN_MainWindow.CharSelectID);

                IN_MainWindow_Switch.holdx2.replace(index,IN_MainWindow.masterx);
                IN_MainWindow_Switch.holdz2.replace(index,IN_MainWindow.masterz);
                IN_MainWindow_Switch.holdy2.replace(index,IN_MainWindow.mastery);
            }

            if(!IN_MainWindow_Switch.holdid2.contains(IN_MainWindow.CharSelectID) && IN_MainWindow_Switch.CharSelectID != IN_MainWindow.CharSelectID)
            {
                IN_MainWindow_Switch.holdid2.append(IN_MainWindow.CharSelectID);
                IN_MainWindow_Switch.holdx2.append(IN_MainWindow.masterx);
                IN_MainWindow_Switch.holdz2.append(IN_MainWindow.masterz);
                IN_MainWindow_Switch.holdy2.append(IN_MainWindow.mastery);
            }

            QString Channel = IN_MainWindow_Switch.Map_Channel_ID.key(IN_MainWindow.CharSelectID);

            if(Channel.isEmpty() == false)
            {
                if(IN_MainWindow_Switch.Map_Channel_ID.contains(Channel))//check if i am in their spawned channels.
                {
                    if(IN_MainWindow.Xor_Object_ID2 != IN_MainWindow.Xor_Object_ID)
                    {
                        xorpacket packet2;
                        QByteArray Recompressed2 = packet2.packetencrypt(CurrentC9);

                        QByteArray Combined1 = Channel.toUtf8() + "c9xxxx00" + Recompressed2;

                        //file.write("Updating Channel = " + Channel.toUtf8());
                        //file.write("\n");

                        fortytwentyninedec::UpdateMapsVector.append(IN_MainWindow_Switch.CharSelectID.toUtf8());
                        fortytwentyninedec::UpdateMapsVector.append(Combined1);
                    }
                }
            }
            else
            {



                if(IN_MainWindow_Switch.AllChannelsFull == true)
                {
                    objectpacket Spawning;

                    packetparsing::IPandPort_AllvariablesMap.insert(IN_MainWindow_Switch.ClientsID + IN_MainWindow_Switch.ClientsIP + IN_MainWindow_Switch.ClientsPort,IN_MainWindow_Switch);

                    QByteArray Status = Spawning.packetswitch(IN_MainWindow_Switch.ClientsID,IN_MainWindow_Switch.ClientsIP,IN_MainWindow_Switch.ClientsPort);

                    IN_MainWindow_Switch = packetparsing::IPandPort_AllvariablesMap.value(IN_MainWindow_Switch.ClientsID + IN_MainWindow_Switch.ClientsIP + IN_MainWindow_Switch.ClientsPort);

                    qDebug() << "IN_MainWindow_Switch.Map_Channel_ID1" << IN_MainWindow_Switch.Map_Channel_ID;

                    int VectSize = IN_MainWindow_Switch.ActivateOP.size();

                    if(IN_MainWindow_Switch.ActivateOP.isEmpty() == false)// if i am in range and need a channel
                    {
                        for(int ld = 0; ld < IN_MainWindow_Switch.ActivateOP.size(); ld++)
                        {
                            QByteArray Fullc9 = IN_MainWindow_Switch.ActivateOP.at(ld);

                            fortytwentyninedec::UpdateMapsVector.append(IN_MainWindow_Switch.CharSelectID.toUtf8());
                            fortytwentyninedec::UpdateMapsVector.append(Fullc9);
                        }



                        for(int i = 0; i < VectSize; i ++)
                        {
                            IN_MainWindow_Switch.ActivateOP.removeAt(0);
                        }

                        //file.write("ActivateOP.size()2 = " + QString::number(IN_MainWindow.ActivateOP.size()).toUtf8());
                        //file.write("\n");

                        packetparsing::IPandPort_AllvariablesMap.insert(IN_MainWindow_Switch.ClientsID + IN_MainWindow_Switch.ClientsIP + IN_MainWindow_Switch.ClientsPort,IN_MainWindow_Switch);
                        IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(IN_MainWindow_Switch.ClientsID + IN_MainWindow_Switch.ClientsIP + IN_MainWindow_Switch.ClientsPort);
                    }
                }
                else
                {
                    //file.write("IN_MainWindow.AllChannelsFull = false");
                    //file.write("\n");
                    //file.write("IN_MainWindow.comparelist1.size()2 = " + QString::number(IN_MainWindow.comparelist1.size()).toUtf8());
                    //file.write("\n");
                }
            }

            packetparsing::IPandPort_AllvariablesMap.insert(IN_MainWindow_Switch.ClientsID+IN_MainWindow_Switch.ClientsIP+IN_MainWindow_Switch.ClientsPort,IN_MainWindow_Switch);
        }
        else
        {
            if(IN_MainWindow_Switch.CharSelectID.isEmpty() == true)
            {
                packetparsing::IPandPort_AllvariablesMap.remove(ID_IP_PORT);
            }
        }
    }

    int VecSize = fortytwentyninedec::UpdateMapsVector.size();



    if(fortytwentyninedec::UpdateMapsVector.isEmpty() == false)
    {
        for(int re = 0; re < fortytwentyninedec::UpdateMapsVector.size(); re+=2)
        {
            QByteArray CharSlectionID = fortytwentyninedec::UpdateMapsVector.at(re);
            QByteArray UpdatePacket = fortytwentyninedec::UpdateMapsVector.at(re + 1);

            QVector<QByteArray> TempVect = Opcodes::CharID_CLientID_IP_PORT_Map.value(CharSlectionID);


            QByteArray ClientsID = "";
            QByteArray ClientsIP = "";
            QByteArray ClientsPort = "";

            if(TempVect.isEmpty() == false)
            {
                ClientsID = TempVect.at(0);
                ClientsIP = TempVect.at(1);
                ClientsPort = TempVect.at(2);

                packetparsing::packetvars IN_MainWindow = packetparsing::IPandPort_AllvariablesMap.value(ClientsID+ClientsIP+ClientsPort);

                QByteArray Holder = "0A1Fxxxx87C001BF543213" + IN_MainWindow.SessionID + "00xxxx";

                Holder.replace(0,4,IN_MainWindow.serverid1);
                Holder.replace(4,4,IN_MainWindow.clientid1);

                QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_MainWindow.CharSelectID);
                QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

                increment GrpOut;
                QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
                Holder.replace(30,4,GrpOut_a);
                Servers_Last_MessageNumber = GrpOut_a.toUpper();

                MessNumbVect.replace(0,Servers_Last_MessageNumber);

                Opcodes::CharID_ServerMessageNumbers.insert(IN_MainWindow.CharSelectID,MessNumbVect);

                QString Current_Channel = UpdatePacket.mid(0,2).toUpper();

                QByteArray ChanCount = IN_MainWindow.incrementmap.value(Current_Channel);

                increment otherChannels;
                QByteArray ChansNewCount = otherChannels.count(ChanCount);
                UpdatePacket.replace(4,4,ChansNewCount);

                IN_MainWindow.incrementmap.insert(Current_Channel,ChansNewCount);

                Holder.append(UpdatePacket);

                int index = IN_MainWindow.SortChanelsNumbersVector.indexOf(Current_Channel.toUtf8());
                IN_MainWindow.SortChanelsValuesVector.replace(index,ChansNewCount);

                IN_MainWindow.ServersCheckChannelConfirm.clear();

                for(int re = 0; re < IN_MainWindow.SortChanelsValuesVector.size(); re++)
                {
                    QByteArray ChannelsValue = IN_MainWindow.SortChanelsValuesVector.at(re);
                    QByteArray Channel = IN_MainWindow.SortChanelsNumbersVector.at(re);

                    if(ChannelsValue != "0000")
                    {
                        IN_MainWindow.ServersCheckChannelConfirm.append(Channel + ChannelsValue);
                        IN_MainWindow.SortChanelsValuesVector.replace(re,"0000");
                    }
                }

                packetsize ResizePacket;
                QByteArray ResizePacket2 = ResizePacket.switchsize(Holder);
                Holder.replace(8,4,ResizePacket2.toUpper());

                crc sendcrc;
                QByteArray outcrc =  sendcrc.elcrc(Holder);
                Holder.append(outcrc);

                QHostAddress current_client_address;
                current_client_address.setAddress(QString::fromUtf8(IN_MainWindow.ClientsIP));
                quint16 current_client_port = IN_MainWindow.ClientsPort.toUShort(nullptr,10);
                QString changeIP = current_client_address.toString();


                QString MainToon = checkthezone::NPCsNames.value(IN_MainWindow.CharSelectID);


                QDateTime dateTime = dateTime.currentDateTime();
                QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zz:a");

                qDebug() << "";
                qDebug() << "";
                qDebug() << "----------------------------------------------------------";
                qDebug() << dateTimeString;
                qDebug() << "Update_Channel_Maps: ";
                qDebug() << "To Client: " + MainToon;
                qDebug() << "IN_MainWindow.CharSelectID = " << IN_MainWindow.CharSelectID;
                qDebug() << "IP: " + changeIP;
                qDebug() << "Port: " + IN_MainWindow.ClientsPort;
                qDebug() << "From Server: ";
                qDebug() << Holder;
                qDebug() << "----------------------------------------------------------";
                qDebug() << "";

                QByteArray gameout2 = Holder.fromHex(Holder);

                QHostAddress newsender = QHostAddress(changeIP);
                worldthread::udpsocket3->writeDatagram(gameout2,newsender,current_client_port);

                packetparsing::IPandPort_AllvariablesMap.insert(ClientsID+ClientsIP+ClientsPort,IN_MainWindow);
            }
        }
    }

    for(int i = 0; i < VecSize; i++)
    {
        fortytwentyninedec::UpdateMapsVector.removeAt(0);
    }


    return "Update_Channel_Maps";
}





void MainWindow::on_pushButton_88_clicked()
{
    QString FourByte = ui->lineEdit_134->text().toUpper();
    QString Byte1 = FourByte.mid(0,2);
    QString Byte2 = FourByte.mid(2,2);
    QString Byte3 = FourByte.mid(4,2);
    QString Byte4 = FourByte.mid(6,2);
    QString Reverse = Byte4 + Byte3 + Byte2 + Byte1;

    int FourByte1 = Reverse .toInt(nullptr,16);

    QString FourByte2 = QString("%1").arg(FourByte1,1,10,QLatin1Char('0'));
    ui->lineEdit_135->setText(FourByte2.toUpper());

    QString DecVal = ui->lineEdit_135->text().toUpper();
    Convert Sendto;
    QString ConvertedValue = Sendto.ConvertTo(DecVal);

    ui->lineEdit_136->setText(ConvertedValue.toUpper());

    ConvertedValue = Sendto.Bytes4to5(FourByte);

    ui->lineEdit_259->setText(ConvertedValue.toUpper());
}

void MainWindow::on_pushButton_89_clicked()
{
    QString HexVal = ui->lineEdit_139->text().toUpper();
    ADD_OR_SUB Sendto;
    QString ConvertedValue = Sendto.BackToDec(HexVal);

    ui->lineEdit_140->setText(ConvertedValue.toUpper());
    QString FourByte = ui->lineEdit_140->text();

    int FourByte1 = ConvertedValue.toInt(nullptr,10);
    QString FourByte2 = QString("%1").arg(FourByte1,8,16,QLatin1Char('0'));
    QString Byte1 = FourByte2.mid(0,2);
    QString Byte2 = FourByte2.mid(2,2);
    QString Byte3 = FourByte2.mid(4,2);
    QString Byte4 = FourByte2.mid(6,2);
    QString Reverse = Byte4 + Byte3 + Byte2 + Byte1;

    ui->lineEdit_141->setText(Reverse.toUpper());


}



void MainWindow::on_pushButton_90_clicked()
{
    QString FourByte = ui->lineEdit_142->text().toUpper();
    QString Byte1 = FourByte.mid(0,2);
    QString Byte2 = FourByte.mid(2,2);
    QString Byte3 = FourByte.mid(4,2);
    QString Byte4 = FourByte.mid(6,2);
    QString Reverse = Byte4 + Byte3 + Byte2 + Byte1;

    int FourByte1 = Reverse .toInt(nullptr,16);
    int plus1 = FourByte1 + 1;

    QString FourByte2 = QString("%1").arg(plus1,1,10,QLatin1Char('0'));
    ui->lineEdit_143->setText(FourByte2.toUpper());

    QString DecVal = ui->lineEdit_143->text().toUpper();
    Convert SendtoHex;
    QString ConvertedValue = SendtoHex.ConvertTo(DecVal);
    ui->lineEdit_144->setText(ConvertedValue.toUpper());

    QString HexVal = ConvertedValue.toUpper();
    ADD_OR_SUB SendtoDec;
    ConvertedValue = SendtoDec.BackToDec(HexVal);

    FourByte = ConvertedValue.toUpper();

    FourByte1 = ConvertedValue.toInt(nullptr,10);
    FourByte2 = QString("%1").arg(FourByte1,8,16,QLatin1Char('0'));
    Byte1 = FourByte2.mid(0,2);
    Byte2 = FourByte2.mid(2,2);
    Byte3 = FourByte2.mid(4,2);
    Byte4 = FourByte2.mid(6,2);
    Reverse = Byte4 + Byte3 + Byte2 + Byte1;

    ui->lineEdit_142->setText(Reverse.toUpper());
}

void MainWindow::on_pushButton_91_clicked()
{
    QByteArray Name24 = ui->lineEdit_145->text().toUtf8();//test with 24bytes with 00's from UI

    QString textout = Name24.fromHex(Name24);
    ui->lineEdit_146->setText(textout);//Send actual Name to UI to see

    QByteArray NameHex = textout.toUtf8().toHex();//Change back to Hex without 00's
    ui->lineEdit_147->setText(NameHex.toUpper());//Send Hex value to UI to see
}

void MainWindow::on_pushButton_92_clicked()
{
    QString Byte5Total = "";

    QString FourByte = ui->lineEdit_134->text().toUpper();
    QString Byte_1st = FourByte.mid(0,2);
    QString Byte_2nd = FourByte.mid(2,2);
    QString Byte_3rd = FourByte.mid(4,2);
    QString Byte_4th = FourByte.mid(6,2);
    QString Reverse = Byte_4th + Byte_3rd + Byte_2nd + Byte_1st;

    int FourByte1 = Reverse.toInt(nullptr,16);

    if(FourByte1 == 0)
    {
        int Byte1st1 = Byte_1st.toInt(nullptr,16);
        int xorValue = Byte1st1 ^ 0xFF;
        QString Byte1st2 = QString("%1").arg(xorValue,2,16,QLatin1Char('0'));

        int Byte2nd1 = Byte_2nd.toInt(nullptr,16);
        xorValue = Byte2nd1 ^ 0xFF;
        QString Byte2nd2 = QString("%1").arg(xorValue,2,16,QLatin1Char('0'));

        int Byte3rd1 = Byte_3rd.toInt(nullptr,16);
        xorValue = Byte3rd1 ^ 0xFF;
        QString Byte3rd2 = QString("%1").arg(xorValue,2,16,QLatin1Char('0'));

        int Byte4th1 = Byte_4th.toInt(nullptr,16);
        xorValue = Byte4th1 ^ 0xFF;
        QString Byte4th2 = QString("%1").arg(xorValue,2,16,QLatin1Char('0'));

        Reverse = Byte4th2 + Byte3rd2 + Byte2nd2 + Byte1st2;

        FourByte1 = Reverse.toInt(nullptr,16);

        Plus1 = "Plus1";
        ui->lineEdit_134->setText(Reverse.toUpper());
    }

    //qDebug() << "FourByte1" << FourByte1;
    QString FourByte2 = QString("%1").arg(FourByte1,1,10,QLatin1Char('0'));
    ui->lineEdit_135->setText(FourByte2.toUpper());


    int Byte5th = 0;
    int Byte4th = 0;
    int Byte3rd = 0;
    int Byte2nd = 0;
    int Byte1st = 0;
    int Total = 0;
    int Difference = 0;

    Byte5th = FourByte1 / 134217728;

    //qDebug() << "Byte5th" << Byte5th;
    if(Byte5th > 0)
    {
        Total = Byte5th * 134217728;
        Difference = FourByte1 - Total;
        FourByte1 = Difference;
        //qDebug() << "Difference5" << FourByte1;

        QString Byte5th1 = QString("%1").arg(Byte5th,2,16,QLatin1Char('0'));
        //qDebug() << "Byte5th1" << Byte5th1.toUpper();
        Byte5Total.prepend(Byte5th1);
    }

    Byte4th = FourByte1 / 1048576;
    //qDebug() << "Byte4th" << Byte4th;

    if(Byte4th > 0)
    {
        Total = Byte4th * 1048576;
        Difference = FourByte1 - Total;
        FourByte1 = Difference;
        //qDebug() << "Difference4" << Difference;

        if(Byte4th < 128 && Byte5th > 0)
        {
            Byte4th = Byte4th + 128;
            QString Byte4th1 = QString("%1").arg(Byte4th,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte4th1);
            //qDebug() << "Byte4th1" << Byte4th1.toUpper();
        }
        else
        {
            QString Byte4th1 = QString("%1").arg(Byte4th,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte4th1);
            //qDebug() << "Byte4th1" << Byte4th1.toUpper();
        }
    }

    if(Byte4th == 0 && Byte5th > 0)
    {
        Byte4th = 128;
        QString Byte4th1 = QString("%1").arg(Byte4th,2,16,QLatin1Char('0'));
        Byte5Total.prepend(Byte4th1);
        //qDebug() << "Byte4th1" << Byte4th1.toUpper();
    }

    Byte3rd = FourByte1 / 8192;
    //qDebug() << "Byte3rd" << Byte3rd;

    if(Byte3rd > 0)
    {
        Total = Byte3rd * 8192;
        Difference = FourByte1 - Total;
        FourByte1 = Difference;
        //qDebug() << "Difference3" << Difference;

        if(Byte3rd < 128 && Byte4th > 0)
        {
            Byte3rd = Byte3rd + 128;
            QString Byte3rd1 = QString("%1").arg(Byte3rd,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte3rd1);
            //qDebug() << "Byte3rd1" << Byte3rd1.toUpper();
        }
        else
        {
            QString Byte3rd1 = QString("%1").arg(Byte3rd,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte3rd1);
            //qDebug() << "Byte3rd1" << Byte3rd1.toUpper();
        }
    }

    if(Byte3rd == 0 && Byte4th > 0)
    {
        Byte3rd = 128;
        QString Byte3rd1 = QString("%1").arg(Byte3rd,2,16,QLatin1Char('0'));
        Byte5Total.prepend(Byte3rd1);
        //qDebug() << "Byte3rd1" << Byte3rd1.toUpper();
    }

    Byte2nd = FourByte1 / 64;
    //qDebug() << "Byte2nd" << Byte2nd;

    if(Byte2nd > 0)
    {
        Total = Byte2nd * 64;
        Difference = FourByte1 - Total;
        FourByte1 = Difference;
        //qDebug() << "Difference2" << Difference;

        if(Byte2nd < 128 && Byte3rd > 0)
        {
            Byte2nd = Byte2nd + 128;
            QString Byte2nd1 = QString("%1").arg(Byte2nd,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte2nd1);
            //qDebug() << "Byte2nd1" << Byte2nd1.toUpper();
        }
        else
        {
            QString Byte2nd1 = QString("%1").arg(Byte2nd,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte2nd1);
            //qDebug() << "Byte2nd1" << Byte2nd1.toUpper();
        }
    }

    if(Byte2nd == 0 && Byte3rd > 0)
    {
        Byte2nd = 128;
        QString Byte2nd1 = QString("%1").arg(Byte2nd,2,16,QLatin1Char('0'));
        Byte5Total.prepend(Byte2nd1);
        //qDebug() << "Byte2nd1" << Byte2nd1.toUpper();
    }

    Byte1st = FourByte1 * 2;
    //qDebug() << "Byte1st" << Byte1st;

    if(Byte1st > 0)
    {
        if(Byte1st < 128 && Byte2nd > 0)
        {
            if(Plus1 == "Plus1")
            {
                Byte1st = Byte1st + 129;
            }
            else
            {
                Byte1st = Byte1st + 128;
            }
            QString Byte1st1 = QString("%1").arg(Byte1st,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte1st1);
            //qDebug() << "Byte1st1" << Byte1st1.toUpper();
        }
        else
        {
            QString Byte1st1 = QString("%1").arg(Byte1st,2,16,QLatin1Char('0'));
            Byte5Total.prepend(Byte1st1);
            //qDebug() << "Byte1st1" << Byte1st1.toUpper();
        }
    }

    if(Byte1st == 0 && Byte2nd > 0)
    {

        if(Plus1 == "Plus1")
        {
            Byte1st = 129;
        }
        else
        {
            Byte1st = 128;
        }
        QString Byte1st1 = QString("%1").arg(Byte1st,2,16,QLatin1Char('0'));
        Byte5Total.prepend(Byte1st1);
        //qDebug() << "Byte1st1" << Byte1st1.toUpper();
    }

    Plus1 = "";
    //qDebug() << "Byte5Total" << Byte5Total;
    ui->lineEdit_136->setText(Byte5Total.toUpper());

}



void MainWindow::on_pushButton_93_clicked()
{
    packetparsing::packetvars IN_pushButton_93;
    IN_pushButton_93 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_pushButton_93.CharSelectID);
    QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

    increment GrpOut;
    QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
    Servers_Last_MessageNumber = GrpOut_a.toUpper();

    MessNumbVect.replace(0,Servers_Last_MessageNumber);

    Opcodes::CharID_ServerMessageNumbers.insert(IN_pushButton_93.CharSelectID,MessNumbVect);



    QByteArray dumMy1 = IN_pushButton_93.serverid1 + IN_pushButton_93.clientid1 + SizeAndSession + IN_pushButton_93.SessionID + "00" +
            Servers_Last_MessageNumber;

    QString Opcode = ui->lineEdit_148->text();
    QString Counter = ui->lineEdit_149->text();
    QString Text = ui->lineEdit_109->text();

    if(ui->checkBox_19->isChecked() == true)
    {

        QByteArray text_1 = Text.toUtf8();
        QByteArray textascii2 = text_1.toHex();
        QByteArray textascii = textascii2;


        for (int cc = 0; cc < textascii2.size() * 2; cc+=2)
        {
            textascii.insert(cc + 2,"00");
            cc += 2;
        }

        int mysize = textascii.size() / 4;
        QString sizeout3 = QString("%1").arg(mysize,8,16,QLatin1Char('0')).toUpper();

        QByteArray switch_it = sizeout3.toUtf8();
        QByteArray First_Byte  = switch_it.mid(0,2);
        QByteArray Second_Byte = switch_it.mid(2,2);
        QByteArray Third_Byte  = switch_it.mid(4,2);
        QByteArray Fourth_Byte = switch_it.mid(6,2);

        QByteArray Text_Size_rev = Fourth_Byte + Third_Byte + Second_Byte + First_Byte;


        Text = Text_Size_rev + textascii;


        for(int i = 0; i < 4; i++)
        {
            increment outto1;
            QByteArray BackFrom1 = outto1.count(IncThis);
            IncThis = BackFrom1;

            ui->lineEdit_149->setText(IncThis + "0000");

            QString FB_Out = Opcode + IncThis + "0000" + Text;

            QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_pushButton_93.CharSelectID);
            QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

            increment GrpOut;
            QByteArray GrpOut_a = GrpOut.count(Servers_Last_FB_MessageNumber);
            Servers_Last_FB_MessageNumber = GrpOut_a.toUpper();

            QString NewFB = CurrentItem.FBSize(FB_Out);

            int index = NewFB.indexOf("xxxx");
            NewFB.replace(index,4,Servers_Last_FB_MessageNumber);

            MessNumbVect.replace(1,Servers_Last_FB_MessageNumber);


            Opcodes::CharID_ServerMessageNumbers.insert(IN_pushButton_93.CharSelectID,MessNumbVect);
        }
    }
    else
    {
        QString FB_Out = "";

        if(ui->checkBox_TestText->isChecked() == true)
        {
            increment outto1;
            QByteArray BackFrom1 = outto1.count(IncThis);
            IncThis = BackFrom1;

            ui->lineEdit_149->setText(IncThis + "0000");

            FB_Out = Opcode + IncThis + "0000" + Text;
        }
        else
        {
            FB_Out = Text;
        }

        if(ui->checkBox_47->isChecked() == true)
        {
            QString Items_ID = "BCBC808000";

            QString ItemsInfo = merchants::Items_Map.value(Items_ID);

            int index = ItemsInfo.indexOf("XXXXXXXX");
            ItemsInfo.replace(index,8,"00000000");

            FB_Out.append(ItemsInfo);
        }

        QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_pushButton_93.CharSelectID);
        QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

        increment GrpOut;
        QByteArray GrpOut_a = GrpOut.count(Servers_Last_FB_MessageNumber);
        Servers_Last_FB_MessageNumber = GrpOut_a.toUpper();

        QString NewFB = CurrentItem.FBSize(FB_Out);

        int index = NewFB.indexOf("XXXX");
        NewFB.replace(index,4,Servers_Last_FB_MessageNumber);

        MessNumbVect.replace(1,Servers_Last_FB_MessageNumber);


        Opcodes::CharID_ServerMessageNumbers.insert(IN_pushButton_93.CharSelectID,MessNumbVect);

        dumMy1.append(NewFB.toUtf8());
    }



    packetsize ResizePacket; //call size class
    QByteArray ResizePacket2 = ResizePacket.switchsize(dumMy1); //get new size
    dumMy1.replace(8,4,ResizePacket2);

    ui->textEdit_40->append(dumMy1);
    ui->textEdit_40->append("");

    crc sendcrc;
    QByteArray outcrc =  sendcrc.elcrc(dumMy1);
    dumMy1.append(outcrc);

    QByteArray custom5out = dumMy1.fromHex(dumMy1);


    QHostAddress current_client_address;
    current_client_address.setAddress(QString::fromUtf8(IN_pushButton_93.ClientsIP));
    quint16 current_client_port = IN_pushButton_93.ClientsPort.toUShort(nullptr,10);
    QString changeIP = current_client_address.toString();

    QHostAddress newsender = QHostAddress(changeIP);
    worldthread::udpsocket3->writeDatagram(custom5out,newsender,current_client_port);



}

void MainWindow::on_pushButton_43_clicked()
{
    packetparsing::packetvars IN_pushButton_43;
    IN_pushButton_43 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QString BuffUpdate = ui->plainTextEdit_6->toPlainText().toUtf8().toUpper();

    QVector <QString> temp;

    QStringList Mylist = BuffUpdate.split("\n");
    QString firststring = "";

    for(int i = 0; i < Mylist.size(); i++)
    {
        firststring = Mylist.value(i);
        QString firststring1 = firststring.mid(0,8);
        temp.append(firststring1);
    }

    BuffUpdate.clear();

    for(int i = 0; i < temp.size(); i++)
    {
        firststring = temp.value(i);
        BuffUpdate.append(firststring);
    }


    xorpacket Compress;
    QByteArray New42 = Compress.packetencrypt(BuffUpdate.toUtf8());

    QByteArray BuffHeader = "42ECxxxx00";

    IN_pushButton_43.Send42ECsVector.append(BuffHeader + New42);

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_pushButton_43);


}


void MainWindow::on_pushButton_94_clicked()
{
    packetparsing::packetvars IN_pushButton_94;
    IN_pushButton_94 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);


    QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_pushButton_94.CharSelectID);
    QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);
    QByteArray Servers_Last_FB_MessageNumber = MessNumbVect.at(1);

    increment GrpOut;
    QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
    Servers_Last_MessageNumber = GrpOut_a.toUpper();

    QString FBText = "";

    increment outto3;
    QByteArray BackFrom3 = outto3.count(Servers_Last_MessageNumber);
    Servers_Last_MessageNumber = BackFrom3;

    QByteArray dumMy1 = IN_pushButton_94.serverid1 + IN_pushButton_94.clientid1 + SizeAndSession + IN_pushButton_94.SessionID + "00" +
            Servers_Last_MessageNumber;

    QString BuffUpdate = ui->plainTextEdit_9->toPlainText().toUtf8().toUpper();

    QVector <QString> temp;

    QStringList Mylist = BuffUpdate.split("\n");
    QString firststring = "";

    for(int i = 0; i < Mylist.size(); i++)
    {
        firststring = Mylist.value(i);
        int firststring1 = firststring.indexOf(" ");
        firststring = firststring.mid(0,firststring1);
        //qDebug() << "firststring" << firststring;
        temp.append(firststring);
    }

    BuffUpdate.clear();

    for(int i = 0; i < temp.size(); i++)
    {
        firststring = temp.value(i);
        BuffUpdate.append(firststring);
    }

    //qDebug() << "BuffUpdate" << BuffUpdate;

    QString FBsizeOpcode = BuffUpdate.toUpper();

    GrpOut_a = GrpOut.count(Servers_Last_FB_MessageNumber);
    Servers_Last_FB_MessageNumber = GrpOut_a.toUpper();

    QString NewFB = CurrentItem.FBSize(FBsizeOpcode);

    int index = NewFB.indexOf("xxxx");
    NewFB.replace(index,4,Servers_Last_FB_MessageNumber);

    MessNumbVect.replace(0,Servers_Last_MessageNumber);
    MessNumbVect.replace(1,Servers_Last_FB_MessageNumber);

    Opcodes::CharID_ServerMessageNumbers.insert(IN_pushButton_94.CharSelectID,MessNumbVect);

    dumMy1.append(NewFB.toUtf8());

    packetsize ResizePacket; //call size class
    QByteArray ResizePacket2 = ResizePacket.switchsize(dumMy1); //get new size
    dumMy1.replace(8,4,ResizePacket2);

    //qDebug() << "55550d41" << dumMy1.toUpper();

    crc sendcrc;
    QByteArray outcrc =  sendcrc.elcrc(dumMy1);
    dumMy1.append(outcrc);
    QByteArray custom5out = dumMy1.fromHex(dumMy1);

    QHostAddress current_client_address;
    current_client_address.setAddress(QString::fromUtf8(IN_pushButton_94.ClientsIP));
    quint16 current_client_port = IN_pushButton_94.ClientsPort.toUShort(nullptr,10);
    QString changeIP = current_client_address.toString();

    QHostAddress newsender = QHostAddress(changeIP);
    worldthread::udpsocket3->writeDatagram(custom5out,newsender,current_client_port);
}




void MainWindow::on_Regenerate()
{
    auto* SendingRegeneration = qobject_cast<QTimer*>(sender());
    QString  ID_IP_PORT = SendingRegeneration->objectName();

    if(RegenTimersVector.contains(SendingRegeneration))
    {
        RegenTimersVector.removeOne(SendingRegeneration);
    }

    SendingRegeneration->deleteLater();

    packetparsing::packetvars IN_Regenerate;
    IN_Regenerate = packetparsing::IPandPort_AllvariablesMap.value(ID_IP_PORT.toUtf8());

    int NewCurrentHP = 0;
    int NewCurrentPOW = 0;

    QString CurrentHP1 = "";
    QString HPByte1 = "";
    QString HPByte2 = "";
    QString reverseCurrentHP = "";
    int CurrentHP = 0;

    QString MaxHP1 = "";
    QString reverseMaxHP = "";
    int MaxHP = 0;

    QString CurrentPOW1 = "";
    QString POWByte1 = "";
    QString POWByte2 = "";
    QString reverseCurrentPOW = "";
    int CurrentPOW = 0;

    QString MaxPOW1 = "";
    QString reverseMaxPOW = "";
    int MaxPOW = 0;




    if(IN_Regenerate.Death == false)
    {


        CurrentHP1 = IN_Regenerate.StatsChange.mid(56,4);
        HPByte1 = CurrentHP1.mid(0,2);
        HPByte2 = CurrentHP1.mid(2,2);
        reverseCurrentHP = HPByte2 + HPByte1;
        CurrentHP = reverseCurrentHP.toInt(nullptr,16);

        MaxHP1 = IN_Regenerate.StatsChange.mid(64,4);
        HPByte1 = MaxHP1.mid(0,2);
        HPByte2 = MaxHP1.mid(2,2);
        reverseMaxHP = HPByte2 + HPByte1;
        MaxHP = reverseMaxHP.toInt(nullptr,16);

        ui->textEdit_14->append("CurrentHP " + QString::number(CurrentHP));
        ui->textEdit_14->append("MaxHP " + QString::number(MaxHP));

        QString HoT = "";

        if((CurrentHP1 != MaxHP1 && IN_Regenerate.HPLowOrPOWLow == "LowHP") || (IN_Regenerate.FullHealth == true))
        {
            QString HoT1 = IN_Regenerate.StatsChange.mid(96,4);
            QString HoTByte1 = HoT1.mid(0,2);
            QString HoTByte2 = HoT1.mid(2,2);
            QString ReverseHoT = HoTByte2 + HoTByte1;
            int HoT2 = ReverseHoT.toInt(nullptr,16);

            if(ui->checkBox_11->isChecked() == true)
            {
                int Cheating = ui->lineEdit_152->text().toInt(nullptr,10);
                HoT2 = HoT2 + Cheating;
            }



            if(IN_Regenerate.FullHealth == false)
            {
                HoT = QString("%1").arg(HoT2,1,10,QLatin1Char('0')).toUpper();

                Convert SendToHeal;
                QString Healing = SendToHeal.ConvertTo(HoT);

                QString HealHeader = "DB00" + IN_Regenerate.CharSelectID_Main + Healing + IN_Regenerate.CharSelectID_Main;

                IN_Regenerate.SendFBsVector.append(HealHeader.toUtf8());
                IN_Regenerate.FBReplyOrNotVector.append("00");
                IN_Regenerate.FBPacketDescriptionVector.append("HoT_received, ");
            }

            if(IN_Regenerate.FullHealth == true)
            {
                HoT2 = MaxHP - CurrentHP;
                HoT = QString("%1").arg(HoT2,1,10,QLatin1Char('0')).toUpper();

            }

            ui->textEdit_14->append("HoT = " + HoT);

            NewCurrentHP = HoT2;
        }



        CurrentPOW1 = IN_Regenerate.StatsChange.mid(72,4);
        POWByte1 = CurrentPOW1.mid(0,2);
        POWByte2 = CurrentPOW1.mid(2,2);
        reverseCurrentPOW = POWByte2 + POWByte1;
        CurrentPOW = reverseCurrentPOW.toInt(nullptr,16);

        MaxPOW1 = IN_Regenerate.StatsChange.mid(80,4);
        POWByte1 = MaxPOW1.mid(0,2);
        POWByte2 = MaxPOW1.mid(2,2);
        reverseMaxPOW = POWByte2 + POWByte1;
        MaxPOW = reverseMaxPOW.toInt(nullptr,16);

        if((CurrentPOW1 != MaxPOW1 && IN_Regenerate.HPLowOrPOWLow == "LowPOW") || (IN_Regenerate.FullHealth == true))
        {
            QString PoT1 = IN_Regenerate.StatsChange.mid(104,4);
            QString PoTByte1 = PoT1.mid(0,2);
            QString PoTByte2 = PoT1.mid(2,2);
            QString ReversePoT = PoTByte2 + PoTByte1;
            int PoT2 = ReversePoT.toInt(nullptr,16);

            if(ui->checkBox_11->isChecked() == true)
            {
                int Cheating = ui->lineEdit_152->text().toInt(nullptr,10);
                PoT2 = PoT2 + Cheating;
            }

            if(IN_Regenerate.FullHealth == true)
            {
                PoT2 = MaxPOW - CurrentPOW;
            }

            QString PoT = QString("%1").arg(PoT2,1,10,QLatin1Char('0')).toUpper();

            NewCurrentPOW = PoT2;
        }

        int MyNewHP = -1;

        if(IN_Regenerate.FullHealth == true)
        {
            IN_Regenerate.FullHealth = false;
            ui->label_FullHealth->setText("FullHealth = False");
        }


        QString Current_HPMAX = QString("%1").arg(MaxHP,1,10,QLatin1Char('0')).toUpper();
        ui->label_CurrentHPMAX->setText("Current HP MAX = " + Current_HPMAX);

        QString Current_HP = QString("%1").arg(NewCurrentHP,1,10,QLatin1Char('0')).toUpper();
        ui->label_CurrentHP->setText("Current HP = " + Current_HP);

        QString Current_POWMAX = QString("%1").arg(MaxPOW,1,10,QLatin1Char('0')).toUpper();
        ui->label_CurrentPOWMAX->setText("Current POW MAX = " + Current_POWMAX);

        QString Current_POW = QString("%1").arg(NewCurrentPOW,1,10,QLatin1Char('0')).toUpper();
        ui->label_CurrentPOW->setText("Current POW = " + Current_POW);

        xorpacket SendTo42;
        QString New42ec = SendTo42.Recompress42EC(IN_Regenerate.ClientsID,IN_Regenerate.ClientsIP,IN_Regenerate.ClientsPort,IN_Regenerate.mylist,IN_Regenerate.CharSelectID,IN_Regenerate.StatsChange,IN_Regenerate.HoldOldHP,NewCurrentHP,NewCurrentPOW,MyNewHP);

        QByteArray StatHeader = "42ECxxxx01";

        IN_Regenerate.Send42ECsVector.append(StatHeader + New42ec.toUtf8());


        if((CurrentHP1 != MaxHP1 && IN_Regenerate.HPLowOrPOWLow == "LowHP"))
        {
            IN_Regenerate.current_c9 = generator::Players_Map.value(IN_Regenerate.CharSelectID.toUtf8());

            QString MyOldHP0 = IN_Regenerate.StatsChange.mid(56,4);

            QString Byte1 = MyOldHP0.mid(0,2);
            QString Byte2 = MyOldHP0.mid(2,2);
            QString MyOldHP2 = Byte2 + Byte1;
            int MyOldHP = MyOldHP2.toInt(nullptr,16);
            QString MyOldHP1 = QString("%1").arg(MyOldHP,1,10,QLatin1Char('0')).toUpper();
            MyOldHP = MyOldHP1.toInt(nullptr,10);
            QString MyMaxHP0 = IN_Regenerate.StatsChange.mid(64,4);
            Byte1 = MyMaxHP0.mid(0,2);
            Byte2 = MyMaxHP0.mid(2,2);
            QString MyMaxHP2 = Byte2 + Byte1;
            int MyMaxHP = MyMaxHP2.toInt(nullptr,16);
            QString MyMaxHP1 = QString("%1").arg(MyMaxHP,1,10,QLatin1Char('0')).toUpper();
            MyMaxHP = MyMaxHP1.toInt(nullptr,10);

            int MyCurrentHP = 0;
            double MySubHP1 = 0;
            double MyNewC9_hp1 = 0;

            MyCurrentHP = MyOldHP * 100;
            MySubHP1 =  MyCurrentHP / MyMaxHP;
            MyNewC9_hp1 = MySubHP1 * 2.55;

            if(MyNewC9_hp1 >= 254)
            {
                MyNewC9_hp1 = 255;
            }

            int MyNewC9_hp4 = MyNewC9_hp1;

            QString MyNewC9_hp3 = QString("%1").arg(MyNewC9_hp4,2,16,QLatin1Char('0')).toUpper();


            IN_Regenerate.current_c9 = generator::Players_Map.value(IN_Regenerate.CharSelectID.toUtf8());
            IN_Regenerate.current_c9.replace(54,2,MyNewC9_hp3.toUtf8());//-----------------------HP2

            generator::Players_Map.insert(IN_Regenerate.CharSelectID.toUtf8(),IN_Regenerate.current_c9);

            generator packet4;
            QByteArray holdergen = packet4.maintoonswitch(IN_Regenerate.CharSelectID,"",IN_Regenerate.CharSelectID_Main);
            holdergen.insert(0,"00c9xxxx00");

            IN_Regenerate.SendZeroChannelVector.append(holdergen);

            ui->label_HPBar->setText("HP Bar = " + MyNewC9_hp3);

        }


    }





    if(CurrentHP1 == MaxHP1)
    {
        IN_Regenerate.RegenerateHP = "";
    }

    if(CurrentPOW1 == MaxPOW1)
    {
        IN_Regenerate.RegeneratePOW = "";
    }

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_Regenerate);


    if(CurrentHP1 != MaxHP1 && IN_Regenerate.HPLowOrPOWLow == "LowHP")
    {
        QTimer *SwingTimers  = new QTimer(this);
        SwingTimers->setInterval(4000);
        SwingTimers->setSingleShot(true);
        SwingTimers->setObjectName("LowHP");
        RegenTimersVector.append(SwingTimers);
        SwingTimers->start();

        connect(SwingTimers ,SIGNAL(timeout()),this,SLOT(on_Regenerate()));
    }

    if(CurrentPOW1 != MaxPOW1 && IN_Regenerate.HPLowOrPOWLow == "LowPOW")
    {
        QTimer *SwingTimers  = new QTimer(this);
        SwingTimers->setInterval(4000);
        SwingTimers->setSingleShot(true);
        SwingTimers->setObjectName("LowPOW");
        RegenTimersVector.append(SwingTimers);
        SwingTimers->start();

        connect(SwingTimers ,SIGNAL(timeout()),this,SLOT(on_Regenerate()));
    }

}

void MainWindow::on_DespawnMob()
{
    auto* RespawningMob = qobject_cast<QTimer*>(sender());
    QString RespawnID1 = RespawningMob->objectName();

    if(SpawningTimersVector.contains(RespawningMob))
    {
        SpawningTimersVector.removeOne(RespawningMob);
        RespawningMob->deleteLater();
    }

    QByteArray split1 = Opcodes::RespawnID.toUtf8();

    QByteArray first_4_digits = split1.mid(0,4);
    QByteArray last_4_digits = split1.mid(4,4);

    increment first1;
    QByteArray firstresult1 = first1.count(first_4_digits).toUpper();

    if(firstresult1 == "0000")
    {
        first_4_digits = "0000";

        increment second1; //get class object
        QByteArray secondresult1 = second1.count(last_4_digits).toUpper();
        Opcodes::RespawnID = firstresult1.toUpper() + secondresult1.toUpper();
    }

    else
    {
        Opcodes::RespawnID = firstresult1.toUpper() + last_4_digits.toUpper();
    }

    bool respawnContained = false;

    if(RandomSpawns.contains(RespawnID1))
    {
        respawnContained = true;

        QVector <QString> ReplaceMob = RandomSpawns.value(RespawnID1);// object ids to spawn
        RandomSpawns.insert(Opcodes::RespawnID,ReplaceMob);//add new id and original vector

        int ThisMob = RandomSpawnValues.value(RespawnID1);

        int MaxMobSize = ReplaceMob.size();

        if(ThisMob >= MaxMobSize)
        {
            ThisMob = 0;
        }

        RandomSpawnValues.remove(RespawnID1);

        SpawnThisMob = ReplaceMob.at(ThisMob);// id that was picked

        QByteArray NewMobC9 = objectpacket::MasterMap2.value(SpawnThisMob.toUtf8());// that npcs id untouched

        ThisLevel = RandomSpawnLevels.value(RespawnID1);

        RandomSpawnLevels.remove(RespawnID1);

        QString NewLevel = QString("%1").arg(ThisLevel,2,16,QLatin1Char('0')).toUpper();

        index = Opcodes::EndingIDXZYF.indexOf(RespawnID1);// get index of old id

        QString StartingID = Opcodes::StartingIDXZYF.at(index);

        Opcodes::EndingIDXZYF.replace(index,Opcodes::RespawnID);

        QByteArray NewMobC91 = objectpacket::MasterMap2.value(StartingID.toUtf8());

        XZYandFacing = NewMobC91.mid(12,20);// get Spawn Location

        NewMobC9.replace(2,8,Opcodes::RespawnID.toUtf8());//replace new id
        NewMobC9.replace(12,20,XZYandFacing);//replace xzy and facing with spawn location
        NewMobC9.replace(358,2,NewLevel.toUtf8());//replace original level with new level

        objectpacket::Master_Map.remove(RespawnID1.toUtf8());// remove old id and c9
        objectpacket::Master_Map.insert(Opcodes::RespawnID.toUtf8(),NewMobC9);//add new id and new c9


    }
    else
    {
        int index = Opcodes::EndingIDXZYF.indexOf(RespawnID1);// get index of old id

        QString StartingID = Opcodes::StartingIDXZYF.at(index);

        Opcodes::EndingIDXZYF.replace(index,Opcodes::RespawnID);

        NewMobC9 = objectpacket::MasterMap2.value(StartingID.toUtf8());

        NewMobC9.replace(2,8,Opcodes::RespawnID.toUtf8());//replace new id

        objectpacket::Master_Map.remove(RespawnID1.toUtf8());
        objectpacket::Master_Map.insert(Opcodes::RespawnID.toUtf8(),NewMobC9);//add new id and new c9

    }

    if(FacingDirection::Path_Maps.contains(RespawnID1))
    {
        QMap <int,QString> PathMap = FacingDirection::Path_Maps.value(RespawnID1);

        FacingDirection::Path_Maps.remove(RespawnID1);
        FacingDirection::Path_Maps.insert(Opcodes::RespawnID,PathMap);
        objectpacket::Roamers_List.remove(RespawnID1);
        objectpacket::Roamers_List.insert(Opcodes::RespawnID,"Roaming");
        FacingDirection::Path_CounterMap.remove(RespawnID1);
        FacingDirection::Path_CounterMap.insert(Opcodes::RespawnID,1);
        FacingDirection::Facing_Lock2_Map.remove(RespawnID1);
        FacingDirection::Facing_Lock2_Map.insert(Opcodes::RespawnID,"00");
    }

    int index1 = objectpacket::DeadListVector.indexOf(RespawnID1);

    if(index1 != -1)
    {
        objectpacket::DeadListVector.removeAt(index1);
    }



    QMapIterator<QByteArray,struct packetparsing::packetvars> StructIter (packetparsing::IPandPort_AllvariablesMap);
    while(StructIter.hasNext())
    {
        packetparsing::packetvars IN_StandUp;

        StructIter.next();
        QByteArray ID_IP_PORT = StructIter.key();
        IN_StandUp = StructIter.value();//all other players structs

        QStringList holdid;
        QStringList holdx;
        QStringList holdz;
        QStringList holdy;
        QString NewX = "";
        QString NewZ = "";
        QString NewY = "";

        holdid = IN_StandUp.holdid2;
        holdx = IN_StandUp.holdx2;
        holdz = IN_StandUp.holdz2;
        holdy = IN_StandUp.holdy2;

        if(respawnContained == true)
        {
            NewX = XZYandFacing.mid(0,6);
            NewZ = XZYandFacing.mid(6,6);
            NewY = XZYandFacing.mid(12,6);

            holdid.replace(index,Opcodes::RespawnID);// replace old id with new id
            holdx.replace(index,NewX);// replace old X with new X
            holdz.replace(index,NewZ);// replace old Z with new Z
            holdy.replace(index,NewY);// replace old Y with new Y

            IN_StandUp.holdid2 = holdid;
            IN_StandUp.holdx2 = holdx;
            IN_StandUp.holdz2 = holdz;
            IN_StandUp.holdy2 = holdy;
        }
        else
        {
            NewX = NewMobC9.mid(12,6);
            NewZ = NewMobC9.mid(18,6);
            NewY = NewMobC9.mid(24,6);
        }

        QMap <QString,QVector <QString>> ZoneLocationsIDsVectorMap = checkthezone::VectorOFWorldsZones.value(IN_StandUp.masterworld);
        QVector <QString> tempWorldZoneNamesVector = checkthezone::WorldZoneNamesVector.at(IN_StandUp.masterworld);

        int ZoneNumber = checkthezone::IDandZoneNumber.value(RespawnID1);
        checkthezone::IDandZoneNumber.remove(RespawnID1);
        checkthezone::IDandZoneNumber.insert(Opcodes::RespawnID,ZoneNumber);

        QString PacketNumber = Opcodes::ID_PacketNumber_Map.value(RespawnID1);
        Opcodes::ID_PacketNumber_Map.remove(RespawnID1);
        Opcodes::ID_PacketNumber_Map.insert(Opcodes::RespawnID,PacketNumber);

        QString NewName = Opcodes::Name_PacketNumber_Map.key(PacketNumber);
        Opcodes::Name_PacketNumber_Map.remove(NewName);
        Opcodes::Name_PacketNumber_Map.insert(NewName,PacketNumber);

        int World = checkthezone::IDsAndWorlds.value(RespawnID1);
        checkthezone::IDsAndWorlds.remove(RespawnID1);
        checkthezone::IDsAndWorlds.insert(Opcodes::RespawnID,World);

        checkthezone::NPCsNames.remove(RespawnID1);
        checkthezone::NPCsNames.insert(Opcodes::RespawnID,NewName);

        Opcodes::NPC_Map.remove(PacketNumber.toInt(nullptr,10));
        Opcodes::NPC_Map.insert(PacketNumber.toInt(nullptr,10),NewName);


        QString ZonesName = tempWorldZoneNamesVector.at(ZoneNumber);

        QStringList holdid0;
        QStringList holdx0;
        QStringList holdz0;
        QStringList holdy0;

        QVector <QStringList> TempHoldsVector = checkthezone::Zones_IDXZYvectorMap.value(ZonesName);

        if(TempHoldsVector.isEmpty() == false)
        {
            holdid0 = TempHoldsVector.at(0);
            holdx0 = TempHoldsVector.at(1);
            holdz0 = TempHoldsVector.at(2);
            holdy0 = TempHoldsVector.at(3);
        }

        QVector <QString> LocationsIDsVector = ZoneLocationsIDsVectorMap.value(ZonesName);

        if(LocationsIDsVector.contains(RespawnID1))
        {
            int index = LocationsIDsVector.indexOf(RespawnID1);
            LocationsIDsVector.replace(index,Opcodes::RespawnID);

            ZoneLocationsIDsVectorMap.insert(ZonesName,LocationsIDsVector);
            checkthezone::VectorOFWorldsZones.replace(IN_StandUp.masterworld,ZoneLocationsIDsVectorMap);
        }

        int index = holdid0.indexOf(RespawnID1);

        holdid0.replace(index,Opcodes::RespawnID);
        holdx0.replace(index,NewX);
        holdz0.replace(index,NewZ);
        holdy0.replace(index,NewY);

        TempHoldsVector.replace(0,holdid0);
        TempHoldsVector.replace(1,holdx0);
        TempHoldsVector.replace(2,holdz0);
        TempHoldsVector.replace(3,holdy0);

        checkthezone::Zones_IDXZYvectorMap.insert(ZonesName,TempHoldsVector);

        int index2 = IN_StandUp.holdid2.indexOf(RespawnID1);

        if(index2 != -1)
        {
            IN_StandUp.holdid2.replace(index2,Opcodes::RespawnID);
            IN_StandUp.holdx2.replace(index2,NewX);
            IN_StandUp.holdz2.replace(index2,NewZ);
            IN_StandUp.holdy2.replace(index2,NewY);
        }
        else
        {
            IN_StandUp.holdid2.append(Opcodes::RespawnID);
            IN_StandUp.holdx2.append(NewX);
            IN_StandUp.holdz2.append(NewZ);
            IN_StandUp.holdy2.append(NewY);
        }


        if(IN_StandUp.fortyexist == false && IN_StandUp.CheckingTheZone == false)
        {
            objectpacket Spawning;// activates object packet so the roamers get a channel
            // when you are standing still

            packetparsing::IPandPort_AllvariablesMap.insert(IN_StandUp.ClientsID + IN_StandUp.ClientsIP + IN_StandUp.ClientsPort,IN_StandUp);

            QByteArray Status = Spawning.packetswitch(IN_StandUp.ClientsID,IN_StandUp.ClientsIP,IN_StandUp.ClientsPort);

            IN_StandUp = packetparsing::IPandPort_AllvariablesMap.value(IN_StandUp.ClientsID + IN_StandUp.ClientsIP + IN_StandUp.ClientsPort);

            qDebug() << "IN_StandUp.Map_Channel_ID2" << IN_StandUp.Map_Channel_ID;


            if(IN_StandUp.ActivateOP.isEmpty() == false)
            {
                for(int ld = 0; ld < IN_StandUp.ActivateOP.size(); ld++)
                {
                    QByteArray Fullc9 = IN_StandUp.ActivateOP.at(ld);

                    QByteArray Channel = Fullc9.mid(0,2);
                    QVector <QByteArray> CurrenChannelVector = IN_StandUp.MapOfChannelVectors.value(Channel);
                    CurrenChannelVector.append(Fullc9);
                    IN_StandUp.MapOfChannelVectors.insert(Channel,CurrenChannelVector);
                }
            }
        }

        packetparsing::IPandPort_AllvariablesMap.insert(ID_IP_PORT,IN_StandUp);

        flipped sento;
        sento.SendOut(IN_StandUp.ClientsID, IN_StandUp.ClientsIP, IN_StandUp.ClientsPort);
    }
}

void MainWindow::On_Create_Pet()
{

}



void MainWindow::on_lineEdit_153_textChanged(const QString &arg1)
{
    Combat::ExtraDamage = arg1.toInt(nullptr,10);
}

void MainWindow::Activate_Roaming()
{
    //    if(FacingDirection::Now_Roaming == "YES")
    //    {
    //        ui->lineEdit_156->setText("ON");
    //    }

    //    auto* RoamingMob = qobject_cast<QTimer*>(sender());
    //    QString RoamingNow = RoamingMob->objectName();



    //    int Freq = ui->lineEdit_157->text().toInt(nullptr,10);

    //    if(fortyexist == false && objectpacket::CheckingTheZone == false)
    //    {
    //        objectpacket SendForRoaming;// activates object packet so the roamers get a channel
    //        // when you are standing still

    //        QVector<QByteArray> ActivateOP;

    //        ActivateOP = SendForRoaming.packetswitch(masterx,mastery,masterz);

    //        if(ActivateOP.isEmpty() == false)
    //        {
    //            for(int ld = 0; ld < ActivateOP.size(); ld++)
    //            {
    //                QByteArray Fullc9 = ActivateOP.at(ld);

    //                //qDebug() << "MapOfChannelVectors14" << MapOfChannelVectors;

    //                QByteArray Channel = Fullc9.mid(0,2);
    //                QVector <QByteArray> CurrenChannelVector = MapOfChannelVectors.value(Channel);
    //                CurrenChannelVector.append(Fullc9);
    //                MapOfChannelVectors.insert(Channel,CurrenChannelVector);

    //                //qDebug() << "MapOfChannelVectors14" << MapOfChannelVectors;

    //            }
    //        }
    //    }


    //    QVector<QByteArray> FromRoaming;

    //    FacingDirection SendTo;
    //    FromRoaming = SendTo.SendToRoaming(masterx, masterz, mastery);

    //    if(FromRoaming.isEmpty() == false)
    //    {
    //        if(FromRoaming.isEmpty() == false)
    //        {
    //            for(int ld = 0; ld < FromRoaming.size(); ld++)
    //            {
    //                QByteArray Fullc9 = FromRoaming.at(ld);

    //                //qDebug() << "MapOfChannelVectors15" << MapOfChannelVectors;

    //                QByteArray Channel = Fullc9.mid(0,2);
    //                QVector <QByteArray> CurrenChannelVector = MapOfChannelVectors.value(Channel);
    //                CurrenChannelVector.append(Fullc9);
    //                MapOfChannelVectors.insert(Channel,CurrenChannelVector);

    //                //qDebug() << "MapOfChannelVectors15" << MapOfChannelVectors;

    //            }
    //        }
    //    }

    //    if(RoamingTimersVector.contains(RoamingMob))
    //    {
    //        RoamingTimersVector.removeOne(RoamingMob);
    //        RoamingMob->deleteLater();
    //    }

    //    if(FacingDirection::Now_Roaming == "YES")
    //    {
    //        QTimer *RoamTimers  = new QTimer(this);
    //        RoamTimers->setInterval(Freq);
    //        RoamTimers->setSingleShot(true);
    //        RoamTimers->setObjectName("RoamNow");
    //        RoamingTimersVector.append(RoamTimers);
    //        RoamTimers->start();

    //        connect(RoamTimers ,SIGNAL(timeout()),this,SLOT(Activate_Roaming()));
    //    }

}

void MainWindow::on_pushButton_97_clicked()
{
    if(ui->UseThisPath->isChecked() == true)
    {
        ui->UseThisPath->setChecked(false);
    }

    if(ui->UseThisPath_2->isChecked() == true)
    {
        ui->UseThisPath_2->setChecked(false);
    }

    ui->pushButton_97->setDisabled(true);


    FacingDirection::Now_Roaming = "01";
    FacingDirection::UseThisMap = "NO";

    if(FacingDirection::Now_Roaming == "01")
    {
        FacingDirection::Now_Roaming = "YES";

        ui->lineEdit_184->setText(FacingDirection::Now_Roaming);
        ui->lineEdit_185->setText(FacingDirection::UseThisMap);


        QTimer *RoamTimers  = new QTimer(this);
        RoamTimers->setInterval(150);
        RoamTimers->setSingleShot(true);
        RoamTimers->setObjectName("RoamNow");
        RoamingTimersVector.append(RoamTimers);
        RoamTimers->start();

        connect(RoamTimers ,SIGNAL(timeout()),this,SLOT(Activate_Roaming()));
    }
}

void MainWindow::on_pushButton_98_clicked()
{
    ui->pushButton_97->setDisabled(false);
    FacingDirection::Now_Roaming = "NO";
    ui->lineEdit_156->setText("OFF");

    ui->lineEdit_184->setText(FacingDirection::Now_Roaming);
    ui->lineEdit_185->setText(FacingDirection::UseThisMap);
}

void MainWindow::on_pushButton_99_clicked()
{


    ui->textEdit_12->append("");

    QMapIterator<QByteArray,QByteArray> iter2 (ResendAllChannelsMap);
    while (iter2.hasNext())
    {
        iter2.next();
        QByteArray ServersCheckChannelConfirm3 = iter2.key();
        QByteArray Packet = iter2.value();

        ui->textEdit_12->append("");
        ui->textEdit_12->append("ServersCheckChannelConfirm3 " + ServersCheckChannelConfirm3);
        ui->textEdit_12->append("Packet " + Packet);
        ui->textEdit_12->append("");
    }

}

void MainWindow::on_Print_XZY_clicked()
{
    packetparsing::packetvars IN_Print_XZY;
    IN_Print_XZY = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->pushButton_100->setEnabled(true);
    ui->pushButton_102->setEnabled(true);
    ui->pushButton_103->setEnabled(true);
    ui->RemoveMarker->setEnabled(true);
    ui->RemoveALLMarkers->setEnabled(true);

    ++MarkerINC;
    QString replace_id = ui->Count->text().toUpper();
    QString replace_id2 = replace_id.mid(0,4);
    QString replace_id3 = replace_id.mid(4,8);

    increment recover1; //get class
    QByteArray recovercount2 = recover1.count(replace_id2.toUtf8()); //packet increment

    ui->Count->setText(recovercount2.toUpper() + replace_id3.toUpper());
    //                       01FAF20400823181FA001B101E38ED400000000000000000000001FFC698D870000000000000803F00000000000000000000000000000000000000FFFFFFFF000000000000000000000000000000000000000000000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF04020000FF0000000000

    QString Marker_c9 = "01DF001000823181FA001B101E38ED000000000000000000000001FFD7CF4155000000000000003F00000000000000000000000000000000000000FFFFFFFF000000000000000000000000000000000000000000000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF00FFFFFFFF00000000FF000000000050617468204D61726B6572000000000000000000000000000100000000008100FFFFFFFF00150000010074737271";

    QString replace_id4 = ui->Count->text().toUpper();

    QString tempx1 = ui->lineEdit_14->text().toUpper();
    QString tempz1 = ui->lineEdit_16->text().toUpper();
    QString tempy1 = ui->lineEdit_15->text().toUpper();
    QString tempf1 = ui->lineEdit_17->text().toUpper();


    QString Mob_size2 = ui->Mob_size->text().toUpper();
    QString Mob_model1 = ui->Mob_model->text().toUpper();

    Marker_c9.replace(2,8,replace_id4);
    Marker_c9.replace(12,6,tempx1);
    Marker_c9.replace(18,6,tempz1);
    Marker_c9.replace(24,6,tempy1);
    Marker_c9.replace(30,2,tempf1);
    QString Masterworld2 = QString("%1").arg(IN_Print_XZY.masterworld,2,16,QLatin1Char('0'));
    Marker_c9.replace(34,2,Masterworld2);
    Marker_c9.replace(56,8,Mob_model1);
    Marker_c9.replace(76,4,Mob_size2);



    objectpacket::Master_Map.insert(replace_id4.toUtf8(),Marker_c9.toUtf8());


    IN_Print_XZY.holdid2.append(replace_id4);
    IN_Print_XZY.holdx2.append(tempx1);
    IN_Print_XZY.holdz2.append(tempz1);
    IN_Print_XZY.holdy2.append(tempy1);

    ui->plainTextEdit_12->appendPlainText("{\"" + replace_id4 + "\",\"" + Marker_c9 + "\"},");

    PathMaker.insert(MarkerINC,IN_Print_XZY.masterx.toUpper() + IN_Print_XZY.masterz.toUpper() + IN_Print_XZY.mastery.toUpper());

    MarkerLocations.insert(replace_id4,MarkerINC);

    QString RoamerID = ui->lineEdit_160->text().toUpper();

    FacingDirection::TempPathMaps.insert(RoamerID,PathMaker);

    QString Increment1 = QString("%1").arg(MarkerINC,10).toUpper();
    ui->Marker_List->append("{" + Increment1 + ",\"" + IN_Print_XZY.masterx.toUpper() + IN_Print_XZY.masterz.toUpper() + IN_Print_XZY.mastery.toUpper() + "\"},");


    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_Print_XZY);


}








void MainWindow::on_RemoveMarker_clicked()
{
    packetparsing::packetvars IN_RemoveMarker;
    IN_RemoveMarker = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->plainTextEdit_12->clear();

    objectpacket::Master_Map.remove(IN_RemoveMarker.Target_ID);

    int index = IN_RemoveMarker.holdid2.indexOf(IN_RemoveMarker.Target_ID);

    if(index != -1)
    {
        IN_RemoveMarker.holdid2.removeAt(index);
        IN_RemoveMarker.holdx2.removeAt(index);
        IN_RemoveMarker.holdz2.removeAt(index);
        IN_RemoveMarker.holdy2.removeAt(index);
    }


    QString Current_channel = IN_RemoveMarker.Map_Channel_ID.key(IN_RemoveMarker.Target_ID);

    //Despawn
    QByteArray holderXorC9 = "01c9xxxx01100180c800";

    holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());

    //qDebug() << "MapOfChannelVectors16" << MapOfChannelVectors;

    QByteArray Channel = holderXorC9.mid(0,2);
    QVector <QByteArray> CurrenChannelVector = IN_RemoveMarker.MapOfChannelVectors.value(Channel);
    CurrenChannelVector.append(holderXorC9);
    IN_RemoveMarker.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

    //qDebug() << "MapOfChannelVectors16" << MapOfChannelVectors;


    objectpacket::DeadListVector.append(IN_RemoveMarker.Target_ID);

    IN_RemoveMarker.channelmap.insert(Current_channel,"free");



    QString RoamerID = ui->lineEdit_160->text().toUpper();

    int removeThis = MarkerLocations.value(IN_RemoveMarker.Target_ID);

    PathMaker = FacingDirection::TempPathMaps.value(RoamerID);

    PathMaker.remove(0);

    PathMaker.remove(removeThis);

    int incThis = 0;

    QMap <int,QString> TempMap;

    MarkerINC = 0;
    ui->Marker_List->clear();



    QMapIterator<int,QString> iter (PathMaker);
    while (iter.hasNext())
    {

        iter.next();

        int MakerNumber = incThis;
        incThis++;
        QString NextMarker = iter.value();

        TempMap.insert(MakerNumber,NextMarker);

        ++MarkerINC;
        QString Increment1 = QString("%1").arg(MarkerINC,10).toUpper();
        ui->Marker_List->append("{" + Increment1 + ",\"" + NextMarker + "\"},");

    }

    PathMaker = TempMap;

    PathMaker.insert(0,"");

    FacingDirection::TempPathMaps.insert(RoamerID,PathMaker);
    //FacingDirection::Path_Maps.insert(RoamerID,PathMaker);
    objectpacket::Roamers_List.insert(RoamerID,"Roaming");
    FacingDirection::Path_CounterMap.insert(RoamerID,1);
    FacingDirection::Facing_Lock2_Map.insert(RoamerID,"00");

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_RemoveMarker);

}

void MainWindow::on_RemoveALLMarkers_clicked()
{
    packetparsing::packetvars IN_RemoveALLMarkers;
    IN_RemoveALLMarkers = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->plainTextEdit_12->clear();


    QString RoamerID = ui->lineEdit_160->text().toUpper();



    PathMaker = FacingDirection::TempPathMaps.value(RoamerID);

    if(PathMaker.contains(0))
    {
        PathMaker.remove(0);
    }

    QMapIterator<int,QString> iter (PathMaker);
    while (iter.hasNext())
    {

        iter.next();

        int removeNumber = iter.key();

        QString RemoveID = MarkerLocations.key(removeNumber);

        objectpacket::Master_Map.remove(RemoveID.toUtf8());

        int index = IN_RemoveALLMarkers.holdid2.indexOf(RemoveID);

        if(index != -1)
        {
            IN_RemoveALLMarkers.holdid2.removeAt(index);
            IN_RemoveALLMarkers.holdx2.removeAt(index);
            IN_RemoveALLMarkers.holdz2.removeAt(index);
            IN_RemoveALLMarkers.holdy2.removeAt(index);

            QString Current_channel = IN_RemoveALLMarkers.Map_Channel_ID.key(RemoveID);

            if(Current_channel.isEmpty() == false)
            {
                objectpacket::DeadListVector.append(RemoveID);

                IN_RemoveALLMarkers.channelmap.insert(Current_channel,"free");

                //Despawn
                QByteArray holderXorC9 = "01c9xxxx01100180c800";

                holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());

                //qDebug() << "MapOfChannelVectors17" << MapOfChannelVectors;

                QByteArray Channel = holderXorC9.mid(0,2);
                QVector <QByteArray> CurrenChannelVector = IN_RemoveALLMarkers.MapOfChannelVectors.value(Channel);
                CurrenChannelVector.append(holderXorC9);
                IN_RemoveALLMarkers.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

                //qDebug() << "MapOfChannelVectors17" << MapOfChannelVectors;

            }
        }
    }

    PathMaker.clear();

    PathMaker.insert(0,"");

    MarkerLocations.clear();
    MarkerINC = 0;
    ui->Marker_List->clear();
    FacingDirection::TempPathMaps.clear();

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_RemoveALLMarkers);


}

void MainWindow::on_SetCurrentRoamerID_clicked()
{
    packetparsing::packetvars IN_SetCurrentRoamerID;
    IN_SetCurrentRoamerID = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->lineEdit_160->setText(IN_SetCurrentRoamerID.Target_ID);
}

void MainWindow::on_pushButton_100_clicked()
{
    if(ui->UseThisPath->isChecked() == true)
    {
        ui->pushButton_100->setDisabled(true);
        QString RoamerID = ui->lineEdit_160->text().toUpper();

        if(RoamerID.isEmpty() == false)
        {
            FacingDirection::Now_Roaming = "01";

            if(FacingDirection::Now_Roaming == "01")
            {
                FacingDirection::Now_Roaming = "YES";

                QTimer *RoamTimers  = new QTimer(this);
                RoamTimers->setInterval(150);
                RoamTimers->setSingleShot(true);
                RoamTimers->setObjectName("RoamNow");
                RoamingTimersVector.append(RoamTimers);
                RoamTimers->start();

                connect(RoamTimers ,SIGNAL(timeout()),this,SLOT(Activate_Roaming()));
            }

            //FacingDirection::Path_Maps.insert(RoamerID,PathMaker);
            objectpacket::Roamers_List.insert(RoamerID,"Roaming");
            FacingDirection::Path_CounterMap.insert(RoamerID,1);
            FacingDirection::Facing_Lock2_Map.insert(RoamerID,"00");
        }
    }

    ui->lineEdit_184->setText(FacingDirection::Now_Roaming);
    ui->lineEdit_185->setText(FacingDirection::UseThisMap);
}

void MainWindow::on_UseThisPath_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->UseThisPath_2->setChecked(false);
        FacingDirection::UseThisMap = "YES";
    }
    else
    {
        if(ui->UseThisPath->isChecked() == false)
        {
            FacingDirection::UseThisMap = "NO";
        }
    }
}

void MainWindow::on_UseThisPath_2_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->UseThisPath->setChecked(false);
        FacingDirection::UseThisMap = "YES";
    }
    else
    {

        if(ui->UseThisPath_2->isChecked() == false)
        {
            FacingDirection::UseThisMap = "NO";
        }
    }
}

void MainWindow::on_pushButton_101_clicked()
{

    ui->pushButton_100->setDisabled(false);

    FacingDirection::Now_Roaming = "NO";
    ui->lineEdit_156->setText("OFF");

    ui->lineEdit_184->setText(FacingDirection::Now_Roaming);
    ui->lineEdit_185->setText(FacingDirection::UseThisMap);
}

void MainWindow::on_pushButton_102_clicked()
{


    QString RoamerID = ui->lineEdit_160->text().toUpper();

    if(RoamerID.isEmpty() == false)
    {



        QSqlQuery query;
        QSqlRecord record = query.record();

        int packetid = 0;

        db.transaction();



        QString PacketID = "PacketID";
        QString TableName = "PATHS";
        QString ObjectID = "ObjectID";

        query.prepare(QString ("SELECT [%1] FROM [%2] WHERE [%3] = :val").arg(PacketID).arg(TableName).arg(ObjectID));
        query.bindValue(":val",RoamerID);
        query.exec();

        while(query.next())
        {
            packetid = query.value(0).toInt();
        }

        if(packetid == 0)
        {
            QSqlQuery query ("SELECT COUNT (*) FROM PATHS");

            while(query.next())
            {
                packetid = query.value(0).toInt();
                packetid = packetid + 1;
            }
        }



        QByteArray current_c9 = objectpacket::Master_Map.value(RoamerID.toUtf8());

        QString Name24Hex_OldVal1 = current_c9.mid(310,48);//name

        ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name

        Table_Name = "PATHS";
        Column_Name = "PacketID";
        query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
        query.bindValue(":id",packetid);
        query.exec();


        QString Name = ui->lineEdit_NPC_Name->text();

        QString Column_value = Name;


        Column_Name = "Name";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();


        Column_Name = "Roaming";

        QString RoamVal = "";

        if(FacingDirection::RandomIDsMAP.contains(RoamerID))
        {
            RoamVal = "01";
        }
        else
        {
            RoamVal = "00";
        }

        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",RoamVal);
        query.bindValue(":id",packetid);
        query.exec();

        Column_Name = "ObjectID";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",RoamerID);
        query.bindValue(":id",packetid);
        query.exec();


        QMapIterator<int,QString> iter (PathMaker);
        while (iter.hasNext())
        {
            iter.next();

            int MakerNumber = iter.key();
            QString NextMarker = iter.value();

            if(PathMaker.contains(0))
            {
                PathMaker.remove(0);
            }

            QString place1 = QString::number(MakerNumber);

            query.prepare(QString("UPDATE PATHS SET [%1] = :val WHERE [%2] = :val2").arg(place1).arg(Column_Name));

            query.bindValue(":val",NextMarker);
            query.bindValue(":val2",RoamerID);
            query.exec();
        }

        int BlanksNULL = 100 - PathMaker.size();

        if(BlanksNULL > 0)
        {
            for(int i = PathMaker.size()+1; i < 100; i++)
            {
                QString place1 = QString::number(i);

                query.prepare(QString("UPDATE PATHS SET [%1] = :val WHERE [%2] = :val2").arg(place1).arg(Column_Name));

                query.bindValue(":val","");
                query.bindValue(":val2",RoamerID);
                query.exec();
            }
        }


        db.commit();



        ui->lineEdit_160->clear();
    }
}

void MainWindow::on_pushButton_103_clicked()
{
    QString RoamerID = ui->lineEdit_160->text().toUpper();

    if(PathMaker.contains(0))
    {
        PathMaker.remove(0);
    }

    FacingDirection::Path_Maps.insert(RoamerID,PathMaker);


}

void MainWindow::on_CheckForMobs_clicked()
{
    packetparsing::packetvars IN_CheckForMobs;
    IN_CheckForMobs = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    float Radius = ui->MyRadius->text().toFloat();

    if(Radius >= 1)
    {

        int Counter = 0;
        ui->RoamingRadius->clear();
        ui->RoamingRadius2->clear();
        ui->RoamingRadius3->clear();
        ui->RoamingRadius4->clear();
        ui->RoamingRadius5->clear();
        SpawnMarkersMap.clear();
        Counters_IDsMap.clear();
        Multi_PathMaps.clear();

        QByteArray  myx1 = IN_CheckForMobs.masterx; //send as 3 byte hex
        int xfromhex1 = myx1.toInt(nullptr,16);
        float maintoonx1 = xfromhex1 / 128.0;

        QByteArray  myz1 = IN_CheckForMobs.masterz;
        int zfromhex1 = myz1.toInt(nullptr,16);
        float maintoonz1 = zfromhex1 / 128.0;

        if(maintoonz1 > 130000)
        {
            maintoonz1 = maintoonz1 - 131072.00195193;
        }

        QByteArray  myy1 = IN_CheckForMobs.mastery;
        int yfromhex1 = myy1.toInt(nullptr,16);
        float maintoony1 = yfromhex1 / 128.0;

        for(int q = 0; q < IN_CheckForMobs.holdid2.size(); q++)
        {
            QString tempid1 = IN_CheckForMobs.holdid2.at(q);

            QString tempstrx = IN_CheckForMobs.holdx2.at(q);
            int tempint1 = tempstrx.toInt(nullptr,16);
            float xinterlude = tempint1 / 128.0;

            QString tempstrz = IN_CheckForMobs.holdz2.at(q);
            int tempint2 = tempstrz.toInt(nullptr,16);
            float  zinterlude = tempint2 / 128.0;

            if(zinterlude > 130000)
            {
                zinterlude = zinterlude - 131072.00195193;
            }

            QString tempstry = IN_CheckForMobs.holdy2.at(q);
            int tempint3 = tempstry.toInt(nullptr,16);
            float yinterlude = tempint3 / 128.0;

            float sub1 = maintoonx1 - xinterlude;
            float sub2 = maintoonz1 - zinterlude;
            float sub3 = maintoony1 - yinterlude;

            float power1 = qPow(sub1,2);
            float power2 = qPow(sub2,2);
            float power3 = qPow(sub3,2);

            float firstresult = power1 + power2 + power3;
            float result = qSqrt(firstresult);

            QString output1 = QString("%1").arg(result,0,'g',10,QLatin1Char('0')); //float result to string

            float distancecheck1 = ui->MyRadius->text().toFloat();

            QString output2 = QString("%1").arg(distancecheck1,0,'g',10,QLatin1Char('0'));

            int dcheck = distancecheck1;



            if(result <= distancecheck1 && !AlreadyInRoamersVector.contains(tempid1))
            {
                QVector<QString> AllZoneNames = checkthezone::WorldZoneNamesVector.at(IN_CheckForMobs.masterworld);

                int MyZoneNumber = AllZoneNames.indexOf(IN_CheckForMobs.LastZone);
                int MobZoneNumber = checkthezone::IDandZoneNumber.value(tempid1);

                if(MobZoneNumber == MyZoneNumber)
                {
                    if(!FacingDirection::Path_Maps.contains(tempid1) || ui->MultiMarkers->isChecked() == true)
                    {
                        QString MOB_Master_c9 = objectpacket::Master_Map.value(tempid1.toUtf8().toUpper());

                        MOB_Master_c9 = MOB_Master_c9.toUpper();

                        QString MOB_X_val = MOB_Master_c9.mid(12,6);//      Last X value
                        QString MOB_Z_val = MOB_Master_c9.mid(18,6);//      Last Z value
                        QString MOB_Y_val = MOB_Master_c9.mid(24,6);//      Last Y value
                        QString ModelID = MOB_Master_c9.mid(56,8);

                        QString MobLevel1 = MOB_Master_c9.mid(358,2);//level
                        int MobLevel2 = MobLevel1.toInt(nullptr,16);

                        int LowLevel = ui->Low->text().toInt(nullptr,10);
                        int HighLevel = ui->High->text().toInt(nullptr,10);

                        if(MobLevel2 >= LowLevel && MobLevel2 <= HighLevel)
                        {
                            if(ui->ModelBlock->isChecked() == true)
                            {
                                if(!BlockModels.contains(ModelID.toUpper()))
                                {
                                    QString MarkerXZY = MOB_X_val + MOB_Z_val + MOB_Y_val;

                                    Counter++;

                                    SpawnMarkersMap.insert(Counter,MarkerXZY.toUpper());
                                    Counters_IDsMap.insert(Counter,tempid1);

                                    QString Counter1 = QString("%1").arg(Counter,2,10,QLatin1Char('0')).toUpper();

                                    QString Name24Hex_OldVal1 = MOB_Master_c9.mid(310,48);//name

                                    ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name

                                    QString Name = ui->lineEdit_NPC_Name->text();


                                    ui->RoamingRadius->appendPlainText(tempid1);
                                    ui->RoamingRadius->moveCursor(QTextCursor::End);
                                    ui->RoamingRadius2->appendPlainText(Counter1);
                                    ui->RoamingRadius2->moveCursor(QTextCursor::End);
                                    ui->RoamingRadius3->appendPlainText(MarkerXZY.toUpper());
                                    ui->RoamingRadius3->moveCursor(QTextCursor::End);
                                    ui->RoamingRadius4->appendPlainText(Name);
                                    ui->RoamingRadius4->moveCursor(QTextCursor::End);
                                    ui->RoamingRadius5->appendPlainText(output1);
                                    ui->RoamingRadius5->moveCursor(QTextCursor::End);
                                }
                            }
                            else
                            {

                                QString MarkerXZY = MOB_X_val + MOB_Z_val + MOB_Y_val;

                                Counter++;

                                SpawnMarkersMap.insert(Counter,MarkerXZY.toUpper());
                                Counters_IDsMap.insert(Counter,tempid1);

                                QString Counter1 = QString("%1").arg(Counter,2,10,QLatin1Char('0')).toUpper();

                                QString Name24Hex_OldVal1 = MOB_Master_c9.mid(310,48);//name

                                ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name

                                QString Name = ui->lineEdit_NPC_Name->text();


                                ui->RoamingRadius->appendPlainText(tempid1);
                                ui->RoamingRadius->moveCursor(QTextCursor::End);
                                ui->RoamingRadius2->appendPlainText(Counter1);
                                ui->RoamingRadius2->moveCursor(QTextCursor::End);
                                ui->RoamingRadius3->appendPlainText(MarkerXZY.toUpper());
                                ui->RoamingRadius3->moveCursor(QTextCursor::End);
                                ui->RoamingRadius4->appendPlainText(Name);
                                ui->RoamingRadius4->moveCursor(QTextCursor::End);
                                ui->RoamingRadius5->appendPlainText(output1);
                                ui->RoamingRadius5->moveCursor(QTextCursor::End);
                            }
                        }
                    }
                }
            }
        }

        if(ui->MultiMarkers->isChecked() == false)
        {

            QMapIterator<int,QString> iter (Counters_IDsMap);
            while (iter.hasNext())
            {
                iter.next();

                QString RoamerIDs = iter.value();

                Multi_PathMaps.insert(RoamerIDs, SpawnMarkersMap);

                std::uniform_int_distribution <int> distribution2(1, Counters_IDsMap.size());
                int Roaming_Counter = distribution2(*QRandomGenerator::global());

                FacingDirection::RandomIDsMAP.insert(RoamerIDs,Counters_IDsMap.size());
                objectpacket::Roamers_List.insert(RoamerIDs,"Roaming");
                FacingDirection::Path_CounterMap.insert(RoamerIDs,Roaming_Counter);
                FacingDirection::Facing_Lock2_Map.insert(RoamerIDs,"00");
            }
        }
        else
        {

            Multi_PathMaps.insert(IN_CheckForMobs.Target_ID, SpawnMarkersMap);

            std::uniform_int_distribution <int> distribution2(1, Counters_IDsMap.size());
            int Roaming_Counter = distribution2(*QRandomGenerator::global());

            FacingDirection::RandomIDsMAP.insert(IN_CheckForMobs.Target_ID,Counters_IDsMap.size());
            objectpacket::Roamers_List.insert(IN_CheckForMobs.Target_ID,"Roaming");
            FacingDirection::Path_CounterMap.insert(IN_CheckForMobs.Target_ID,Roaming_Counter);
            FacingDirection::Facing_Lock2_Map.insert(IN_CheckForMobs.Target_ID,"00");
            FacingDirection::Path_Maps.insert(IN_CheckForMobs.Target_ID,SpawnMarkersMap);
        }



        FacingDirection::TempPathMaps = Multi_PathMaps;


    }

}



void MainWindow::on_pushButton_104_clicked()
{
    if(ui->MultiMarkers->isChecked() == false)
    {
        QMapIterator<int,QString> iter (Counters_IDsMap);
        while (iter.hasNext())
        {
            iter.next();

            QString RoamerIDs = iter.value();

            Multi_PathMaps.insert(RoamerIDs, SpawnMarkersMap);

            std::uniform_int_distribution <int> distribution2(1, Counters_IDsMap.size());
            int Roaming_Counter = distribution2(*QRandomGenerator::global());

            objectpacket::Roamers_List.insert(RoamerIDs,"Roaming");
            FacingDirection::Path_CounterMap.insert(RoamerIDs,Roaming_Counter);
            FacingDirection::Facing_Lock2_Map.insert(RoamerIDs,"00");

            FacingDirection::Path_Maps.insert(RoamerIDs,SpawnMarkersMap);
            FacingDirection::RandomIDsMAP.insert(RoamerIDs,Counters_IDsMap.size());
        }
    }
}


void MainWindow::on_pushButton_105_clicked()
{
    if(ui->UseThisPath_2->isCheckable() == true)
    {
        ui->pushButton_105->setDisabled(true);

        QString RoamerID = ui->lineEdit_160->text().toUpper();

        FacingDirection::Now_Roaming = "01";

        if(FacingDirection::Now_Roaming == "01")
        {
            FacingDirection::Now_Roaming = "YES";

            QTimer *RoamTimers  = new QTimer(this);
            RoamTimers->setInterval(150);
            RoamTimers->setSingleShot(true);
            RoamTimers->setObjectName("RoamNow");
            RoamingTimersVector.append(RoamTimers);
            RoamTimers->start();

            connect(RoamTimers ,SIGNAL(timeout()),this,SLOT(Activate_Roaming()));
        }
    }

    ui->lineEdit_184->setText(FacingDirection::Now_Roaming);
    ui->lineEdit_185->setText(FacingDirection::UseThisMap);
}

void MainWindow::on_pushButton_106_clicked()
{
    ui->pushButton_105->setDisabled(false);

    FacingDirection::Now_Roaming = "NO";
    ui->lineEdit_156->setText("OFF");
    ui->lineEdit_184->setText(FacingDirection::Now_Roaming);
    ui->lineEdit_185->setText(FacingDirection::UseThisMap);
}

void MainWindow::on_pushButton_107_clicked()
{
    QString RoamerID = ui->lineEdit_160->text().toUpper();

    QSqlQuery query;
    QSqlRecord record = query.record();

    int packetid = 0;

    db.transaction();



    QString PacketID = "PacketID";
    QString TableName = "PATHS";
    QString ObjectID = "ObjectID";

    query.prepare(QString ("SELECT [%1] FROM [%2] WHERE [%3] = :val").arg(PacketID).arg(TableName).arg(ObjectID));
    query.bindValue(":val",RoamerID);
    query.exec();

    while(query.next())
    {
        packetid = query.value(0).toInt();
    }

    if(packetid == 0)
    {
        QSqlQuery query ("SELECT COUNT (*) FROM PATHS");

        while(query.next())
        {
            packetid = query.value(0).toInt();
            packetid++;
        }
    }





    QMapIterator<QString, QMap<int,QString>> iter (Multi_PathMaps);
    while (iter.hasNext())
    {
        iter.next();

        QString RoamerID = iter.key();
        QMap<int,QString> PathMap = iter.value();

        QByteArray current_c9 = objectpacket::Master_Map.value(RoamerID.toUtf8());

        QString Name24Hex_OldVal1 = current_c9.mid(310,48);//name

        ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name

        Table_Name = "PATHS";
        Column_Name = "PacketID";
        query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
        query.bindValue(":id",packetid);
        query.exec();


        QString Name = ui->lineEdit_NPC_Name->text();

        QString Column_value = Name;


        Column_Name = "Name";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();


        Column_Name = "ObjectID";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",RoamerID);
        query.bindValue(":id",packetid);
        query.exec();


        Column_Name = "Roaming";

        QString RoamVal = "";

        if(FacingDirection::RandomIDsMAP.contains(RoamerID))
        {
            RoamVal = "01";
        }
        else
        {
            RoamVal = "00";
        }

        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",RoamVal);
        query.bindValue(":id",packetid);
        query.exec();



        QMapIterator<int,QString> iter (PathMap);
        while (iter.hasNext())
        {
            iter.next();

            int MarkerNumber = iter.key();
            QString NextMarker = iter.value();

            QString place1 = QString::number(MarkerNumber);

            Column_Name = "ObjectID";
            query.prepare(QString("UPDATE PATHS SET [%1] = :val WHERE [%2] = :val2").arg(place1).arg(Column_Name));

            query.bindValue(":val",NextMarker);
            query.bindValue(":val2",RoamerID);
            query.exec();
        }


        int BlanksNULL = 100 - PathMap.size();

        if(BlanksNULL > 0)
        {
            for(int i = PathMap.size()+1; i < 100; i++)
            {
                QString place1 = QString::number(i);

                query.prepare(QString("UPDATE PATHS SET [%1] = :val WHERE [%2] = :val2").arg(place1).arg(Column_Name));

                query.bindValue(":val","");
                query.bindValue(":val2",RoamerID);
                query.exec();
            }
        }

        packetid++;
    }






    db.commit();
}






void MainWindow::on_lineEdit_73_textChanged(const QString &arg1)
{
    ui->lineEdit_25->setText(arg1);
}

void MainWindow::on_pushButton_110_clicked()
{

    QString LastString = "";
    QString Sortstring = ui->textEdit_2->toPlainText();

    do
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        Sortstring = ui->textEdit_2->toPlainText();

        LastString = Sortstring;

        int index = Sortstring.indexOf("\n");

        if(index == -1)
        {
            Sortstring = LastString;
        }
        else
        {
            Sortstring.remove(index,1);

            ui->textEdit_2->setText(Sortstring);
        }


    }while(Sortstring != LastString);


    int increment = 0;
    QVector <QString> tempVector;

    do
    {
        Sortstring = ui->textEdit_2->toPlainText();

        QCoreApplication::processEvents(QEventLoop::AllEvents);

        int indexStart = Sortstring.indexOf("QVector <float> ");
        Sortstring.remove(0,indexStart + 16);
        indexStart = -1;

        int indexEnd = Sortstring.indexOf(" =");
        increment = indexEnd + 1;

        int EndName = indexEnd;
        QString ZoneName = Sortstring.mid(0,EndName);

        Sortstring.remove(0,increment);

        if(indexStart == -1 && indexEnd == -1)
        {
            ui->textEdit_2->clear();
            increment = Sortstring.size();
        }
        else
        {
            //qDebug() << "ZoneName" << ZoneName;

            tempVector.append(ZoneName);
        }

        ui->textEdit_2->setText(Sortstring);

    }while(increment < Sortstring.size());

    ui->textEdit_2->clear();

    for(int i = 0; i < tempVector.size(); i++)
    {
        QString ZoneName = tempVector.at(i);
        ui->plainTextEdit_11->appendPlainText(ZoneName + ",");
    }

    for(int i = 0; i < tempVector.size(); i++)
    {
        QString ZoneName = tempVector.at(i);
        ui->textEdit_2->append("\"" + ZoneName + "\",");
    }
}

void MainWindow::on_pushButton_111_clicked()
{
    QString Sortstring = "";

    QString largestring2 = ui->textEdit_2->toPlainText();
    ui->textEdit_2->clear();

    QStringList PageList = largestring2.split("\n");
    QStringList LineList;
    QString FirstString = "";
    QString SecondString = "";
    QVector <QString> LineVector;
    QVector <QString> LastLineVector;
    QVector <QString> FinalLineVector;

    do
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        QString largestring2 = ui->textEdit_2->toPlainText();
        LineList = largestring2.split("\n");

        for(int re = 0; re < PageList.size(); re++)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents);

            Sortstring = PageList.at(re);

            if(Sortstring.contains("NE\","))
            {
                do
                {
                    int index = Sortstring.indexOf("NE\",");
                    Sortstring.replace(index,4," (NE)\",");

                }while(Sortstring.contains("NE\","));
            }

            if(Sortstring.contains("NW\","))
            {
                int index = Sortstring.indexOf("NW\",");
                Sortstring.replace(index,4," (NW)\",");
            }

            if(Sortstring.contains("SE\","))
            {
                int index = Sortstring.indexOf("SE\",");
                Sortstring.replace(index,4," (SE)\",");
            }

            if(Sortstring.contains("SW\","))
            {
                int index = Sortstring.indexOf("SW\",");
                Sortstring.replace(index,4," (SW)\",");
            }

            if(Sortstring.contains("C\","))
            {
                int index = Sortstring.indexOf("C\",");
                Sortstring.replace(index,3," (C)\",");
            }

            if(Sortstring.contains("N\","))
            {
                int index = Sortstring.indexOf("N\",");
                Sortstring.replace(index,3," (N)\",");
            }

            if(Sortstring.contains("S\","))
            {
                int index = Sortstring.indexOf("S\",");
                Sortstring.replace(index,3," (S)\",");
            }

            if(Sortstring.contains("E\","))
            {
                int index = Sortstring.indexOf("E\",");
                Sortstring.replace(index,3," (E)\",");
            }

            if(Sortstring.contains("W\","))
            {
                int index = Sortstring.indexOf("W\",");
                Sortstring.replace(index,3," (W)\",");
            }

            PageList.replace(re,Sortstring);

            ui->textEdit_2->clear();

            for(int ir = 0; ir < PageList.size(); ir++)
            {
                QCoreApplication::processEvents(QEventLoop::AllEvents);

                QString NewSortString = PageList.at(ir);

                ui->textEdit_2->append(NewSortString);
            }
        }

    }while(LineList != PageList);
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{

    //qDebug() << "horizontalSlider_5_value" << value;



    QVector <QString> MobValuesIndexesVector = ModelComboBoxIDsVectors.at(value);

    QString ModelID = MobValuesIndexesVector.at(0);



    ui->verticalSlider->setMaximum(MobValuesIndexesVector.size() - 1);

    int MaxValue = ui->verticalSlider->maximum();

    //qDebug() << "MaxValue1" << MaxValue;

    if(ui->tabWidget->currentIndex() == 3)
    {
        int newIndex = ui->verticalSlider->value();

        //qDebug() << "newIndex" << newIndex;

        if(SliderUsed == "YES")
        {
            if(newIndex != 0)
            {
                ui->verticalSlider->setValue(0);
            }
            else
            {
                QString Index = QString("%1").arg(1,1,10,QLatin1Char('0'));

                QString Folder = MobFolder.at(value);

                QString filename = "C:/Customize/Forms/" + Folder + "/" + Index + ".jpg";

                ui->label_213->setPixmap(filename);

                if(ModelID.isEmpty() == false)
                {
                    ui->Mob_Models_3->setText(ModelID);
                }
            }
        }
    }

    SliderUsed = "YES";
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{

    QString Index = QString("%1").arg(value + 1,1,10,QLatin1Char('0'));

    int index1 = ui->horizontalSlider_5->value();

    QString Folder = MobFolder.at(index1);

    QString filename = "C:/Customize/Forms/" + Folder + "/" + Index + ".jpg";

    ui->label_213->setPixmap(filename);



    QVector <QString> MobValuesIndexesVector = ModelComboBoxIDsVectors.at(index1);

    QString ModelID = MobValuesIndexesVector.at(value);

    if(ModelID.isEmpty() == false)
    {
        ui->Mob_Models_3->setText(ModelID);

    }
}

void MainWindow::on_pushButton_113_clicked()
{
    int value = ui->verticalSlider->value();

    int maxInt = ui->verticalSlider->maximum();

    if(value < maxInt)
    {
        value++;
        ui->verticalSlider->setValue(value);
    }
}

void MainWindow::on_pushButton_112_clicked()
{
    int value = ui->verticalSlider->value();

    int minInt = ui->verticalSlider->minimum();

    if(value > minInt)
    {
        value--;
        ui->verticalSlider->setValue(value);
    }
}

void MainWindow::on_pushButton_114_clicked()
{
    int value = ui->horizontalSlider_5->value();

    if(value != 0)
    {
        value--;
        ui->horizontalSlider_5->setValue(value);
    }
}

void MainWindow::on_pushButton_115_clicked()
{
    int value = ui->horizontalSlider_5->value();

    if(value != 13)
    {
        value++;
        ui->horizontalSlider_5->setValue(value);
    }
}



void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    if(value == 0)
    {
        ui->verticalSlider_2->setDisabled(false);

        int index2 = ui->verticalSlider_2->value();

        QString WeaponModel = RH_LH_IndexVector.at(index2);

        int index1 = ui->horizontalSlider_6->value();

        QString Folder = WeaponHeldShieldFolder.at(index1);

        QString filename = "C:/Customize/" + Folder + "/" + WeaponModel + ".jpg";

        ui->label_214->setPixmap(filename);

        ui->verticalSlider_4->setDisabled(true);
        ui->verticalSlider_3->setDisabled(true);
    }

    if(value == 1)
    {
        ui->verticalSlider_3->setDisabled(false);

        int index2 = ui->verticalSlider_3->value();

        QString WeaponModel = RH_LH_IndexVector.at(index2);

        int index1 = ui->horizontalSlider_6->value();

        QString Folder = WeaponHeldShieldFolder.at(index1);

        QString filename = "C:/Customize/" + Folder + "/" + WeaponModel + ".jpg";

        ui->label_214->setPixmap(filename);

        ui->verticalSlider_2->setDisabled(true);
        ui->verticalSlider_4->setDisabled(true);
    }

    if(value == 2)
    {
        ui->verticalSlider_4->setDisabled(false);

        int index2 = ui->verticalSlider_4->value();

        QString ShieldModel = Shield_IndexVector.at(index2);

        int index1 = ui->horizontalSlider_6->value();

        QString Folder = WeaponHeldShieldFolder.at(index1);

        QString filename = "C:/Customize/" + Folder + "/" + ShieldModel + ".jpg";

        ui->label_214->setPixmap(filename);

        ui->verticalSlider_2->setDisabled(true);
        ui->verticalSlider_3->setDisabled(true);
    }
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    QString WeaponModel = RH_LH_IndexVector.at(value);
    ui->lineEdit_324->setText(WeaponModel);
    ui->lineEdit_62->setText(WeaponModel);

    int index1 = ui->horizontalSlider_6->value();

    QString Folder = WeaponHeldShieldFolder.at(index1);

    QString filename = "C:/Customize/" + Folder + "/" + WeaponModel + ".jpg";



    if(ui->tabWidget->currentIndex() == 4 && ui->tabWidget_2->currentIndex() == 0 && ui->tabWidget_3->currentIndex() == 3)
    {
        ui->label_214->setPixmap(filename);
        on_pushButton_48_clicked();
    }
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    int index = ui->verticalSlider_4->value();

    if(index > 0)
    {
        ui->lineEdit_326->setText("00000000");
        ui->lineEdit_64->setText("00000000");
        ui->verticalSlider_4->setValue(0);
    }

    QString WeaponModel = RH_LH_IndexVector.at(value);
    ui->lineEdit_325->setText(WeaponModel);
    ui->lineEdit_63->setText(WeaponModel);

    int index1 = ui->horizontalSlider_6->value();

    QString Folder = WeaponHeldShieldFolder.at(index1);

    QString filename = "C:/Customize/" + Folder + "/" + WeaponModel + ".jpg";

    if(ui->tabWidget->currentIndex() == 4 && ui->tabWidget_2->currentIndex() == 0 && ui->tabWidget_3->currentIndex() == 3)
    {
        if(index1 != 2)
        {
            ui->label_214->setPixmap(filename);
            on_pushButton_48_clicked();
        }
    }
}

void MainWindow::on_verticalSlider_4_valueChanged(int value)
{
    int index = ui->verticalSlider_3->value();

    if(index > 0)
    {
        ui->lineEdit_325->setText("00000000");
        ui->lineEdit_63->setText("00000000");
        ui->verticalSlider_3->setValue(0);
    }

    QString ShieldsModel = Shield_IndexVector.at(value);

    ui->lineEdit_326->setText(ShieldsModel);
    ui->lineEdit_64->setText(ShieldsModel);

    int index1 = ui->horizontalSlider_6->value();

    QString Folder = WeaponHeldShieldFolder.at(index1);

    QString filename = "C:/Customize/" + Folder + "/" + ShieldsModel + ".jpg";

    if(ui->tabWidget->currentIndex() == 4 && ui->tabWidget_2->currentIndex() == 0 && ui->tabWidget_3->currentIndex() == 3)
    {
        if(index1 != 1)
        {
            ui->label_214->setPixmap(filename);
            on_pushButton_48_clicked();
        }
    }
}

void MainWindow::on_pushButton_78_clicked()
{
    ui->verticalSlider_4->setValue(0);
    int Index = ui->verticalSlider_2->value();
    ui->verticalSlider_3->setValue(Index);
    ui->horizontalSlider_6->setValue(0);
}

//Bare Hands
void MainWindow::on_pushButton_62_clicked()
{
    ui->lineEdit_324->setText("00000000");
    ui->lineEdit_325->setText("00000000");
    ui->lineEdit_326->setText("00000000");

    ui->lineEdit_62->setText("00000000");
    ui->lineEdit_63->setText("00000000");
    ui->lineEdit_64->setText("00000000");

    ui->horizontalSlider_6->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);
    ui->verticalSlider_4->setValue(0);


    ui->verticalSlider_3->setDisabled(true);
    ui->verticalSlider_4->setDisabled(true);



    on_pushButton_48_clicked();

}

//up
void MainWindow::on_pushButton_230_clicked()
{
    int value = 0;
    int maxInt = 0; //

    int index = ui->horizontalSlider_6->value();

    if(index == 0)
    {
        maxInt = ui->verticalSlider_2->maximum();

        if(value < maxInt)
        {
            value = ui->verticalSlider_2->value();
            value++;
            ui->verticalSlider_2->setValue(value);
        }
    }

    if(index == 1)
    {
        maxInt = ui->verticalSlider_3->maximum();

        if(value < maxInt)
        {
            value = ui->verticalSlider_3->value();
            value++;
            ui->verticalSlider_3->setValue(value);
        }
    }

    if(index == 2)
    {
        maxInt = ui->verticalSlider_4->maximum();

        if(value < maxInt)
        {
            value = ui->verticalSlider_4->value();
            value++;
            ui->verticalSlider_4->setValue(value);
        }
    }
}

void MainWindow::on_pushButton_228_clicked()
{
    int value = 0;
    int minInt = 0; //

    int index = ui->horizontalSlider_6->value();

    if(index == 0)
    {
        value = ui->verticalSlider_2->value();

        if(value > minInt)
        {
            value--;
            ui->verticalSlider_2->setValue(value);
        }
    }

    if(index == 1)
    {
        value = ui->verticalSlider_3->value();

        if(value > minInt)
        {
            value--;
            ui->verticalSlider_3->setValue(value);
        }
    }

    if(index == 2)
    {
        value = ui->verticalSlider_4->value();

        if(value > minInt)
        {
            value--;
            ui->verticalSlider_4->setValue(value);
        }
    }
}

void MainWindow::on_pushButton_231_clicked()
{
    int value = ui->horizontalSlider_6->value();

    if(value != 0)
    {
        value--;
        ui->horizontalSlider_6->setValue(value);
    }
}

void MainWindow::on_pushButton_229_clicked()
{
    int value = ui->horizontalSlider_6->value();

    if(value != 2)
    {
        value++;
        ui->horizontalSlider_6->setValue(value);
    }
}

//up
void MainWindow::on_pushButton_6_clicked()
{
    int value = 0;
    int maxInt = 3; //

    value = ui->verticalSlider_5->value();

    if(value < maxInt)
    {
        value++;
        ui->verticalSlider_5->setValue(value);
    }
}

//down
void MainWindow::on_pushButton_5_clicked()
{
    int value = 0;
    int minInt = 0; //

    value = ui->verticalSlider_5->value();

    if(value > minInt)
    {
        value--;
        ui->verticalSlider_5->setValue(value);
    }
}

//Left
void MainWindow::on_pushButton_81_clicked()
{
    int value = 0;
    int minInt = 0; //

    int index = ui->verticalSlider_5->value();

    if(index == 0)
    {
        value = ui->horizontalSlider->value();
        minInt = ui->horizontalSlider->minimum();

        if(value > minInt)
        {
            value--;
            ui->horizontalSlider->setValue(value);
        }
    }

    if(index == 1)
    {
        value = ui->horizontalSlider_2->value();
        minInt = ui->horizontalSlider_2->minimum();

        if(value > minInt)
        {
            value--;
            ui->horizontalSlider_2->setValue(value);
        }
    }

    if(index == 2)
    {
        value = ui->horizontalSlider_3->value();
        minInt = ui->horizontalSlider_3->minimum();

        if(value > minInt)
        {
            value--;
            ui->horizontalSlider_3->setValue(value);
        }
    }

    if(index == 3)
    {
        value = ui->horizontalSlider_4->value();
        minInt = ui->horizontalSlider_4->minimum();

        if(value > minInt)
        {
            value--;
            ui->horizontalSlider_4->setValue(value);
        }
    }
}

//Right
void MainWindow::on_pushButton_116_clicked()
{
    int value = 0;
    int maxInt = 0; //

    int index = ui->verticalSlider_5->value();

    if(index == 0)
    {
        value = ui->horizontalSlider->value();
        maxInt = ui->horizontalSlider->maximum();

        if(value < maxInt)
        {
            value++;
            ui->horizontalSlider->setValue(value);
        }
    }

    if(index == 1)
    {
        value = ui->horizontalSlider_2->value();
        maxInt = ui->horizontalSlider_2->maximum();

        if(value < maxInt)
        {
            value++;
            ui->horizontalSlider_2->setValue(value);
        }
    }

    if(index == 2)
    {
        value = ui->horizontalSlider_3->value();
        maxInt = ui->horizontalSlider_3->maximum();

        if(value < maxInt)
        {
            value++;
            ui->horizontalSlider_3->setValue(value);
        }
    }

    if(index == 3)
    {
        value = ui->horizontalSlider_4->value();
        maxInt = ui->horizontalSlider_4->maximum();

        if(value < maxInt)
        {
            value++;
            ui->horizontalSlider_4->setValue(value);
        }
    }
}

//Face
void MainWindow::on_horizontalSlider_valueChanged(int Index)
{
    int Race_GenderIndex = ui->comboBox->currentIndex();

    QString Folder = RaceAndGenderFolder.at(Race_GenderIndex);

    QString filename = "C:/Customize/Forms/" + Folder + "/" + QString::number(Index + 1) + ".jpg";

    ui->label_216->setPixmap(filename);

    QString Index2 = QString("%1").arg(Index,2,16,QLatin1Char('0'));
    ui->lineEdit_125->setText(Index2.toUpper());
    ui->lineEdit_55->setText(Index2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }

}

//Hair Style
void MainWindow::on_horizontalSlider_2_valueChanged(int Index)
{
    int Race_GenderIndex = ui->comboBox->currentIndex();

    QString Folder = RaceAndGenderFolder.at(Race_GenderIndex);

    QString filename = "C:/Customize/Forms/" + Folder + "/" + QString::number(Index + 1) + ".jpg";

    ui->label_216->setPixmap(filename);

    QString Index2 = QString("%1").arg(Index - 4,2,16,QLatin1Char('0'));
    ui->lineEdit_126->setText(Index2.toUpper());
    ui->lineEdit_56->setText(Index2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}

//Hair Length
void MainWindow::on_horizontalSlider_3_valueChanged(int Index)
{
    int Race_GenderIndex = ui->comboBox->currentIndex();

    QString Folder = RaceAndGenderFolder.at(Race_GenderIndex);

    QString filename = "C:/Customize/Forms/" + Folder + "/" + QString::number(Index + 1) + ".jpg";

    ui->label_216->setPixmap(filename);

    QString Index2 = QString("%1").arg(Index - 8,2,16,QLatin1Char('0'));
    ui->lineEdit_127->setText(Index2.toUpper());
    ui->lineEdit_57->setText(Index2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}

//Hair Color
void MainWindow::on_horizontalSlider_4_valueChanged(int Index)
{
    int Race_GenderIndex = ui->comboBox->currentIndex();

    QString Folder = RaceAndGenderFolder.at(Race_GenderIndex);

    QString filename = "C:/Customize/Forms/" + Folder + "/" + QString::number(Index + 1) + ".jpg";

    ui->label_216->setPixmap(filename);

    QString Index2 = QString("%1").arg(Index - 12,2,16,QLatin1Char('0'));
    ui->lineEdit_128->setText(Index2.toUpper());
    ui->lineEdit_58->setText(Index2.toUpper());

    if(ui->tabWidget_3->currentIndex() == 1)
    {
        on_pushButton_48_clicked();
    }
}


void MainWindow::on_verticalSlider_5_valueChanged(int value)
{
    int Index = 0;

    if(value == 0)
    {
        Index = ui->horizontalSlider->value();
    }

    if(value == 1)
    {
        Index = ui->horizontalSlider_2->value();
    }

    if(value == 2)
    {
        Index = ui->horizontalSlider_3->value();
    }

    if(value == 3)
    {
        Index = ui->horizontalSlider_4->value();
    }


    int Race_GenderIndex = ui->comboBox->currentIndex();

    QString Folder = RaceAndGenderFolder.at(Race_GenderIndex);
    QString filename = "C:/Customize/Forms/" + Folder + "/" + QString::number(Index + 1) + ".jpg";

    ui->label_216->setPixmap(filename);

}

void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    int Index = ui->verticalSlider_6->value();
    int LastIndex = 0;

    //qDebug() << "hor_horizontalSlider_7 value" << value;
    //qDebug() << "hor_verticalSlider_6 Index" << Index;

    if(value == 6)
    {
        LastIndex = ArmorPositionVector.at(6);
        //qDebug() << "hor_LastIndex" << LastIndex;
        ui->verticalSlider_6->setValue(LastIndex);

        int Index = ui->verticalSlider_6->value();
        //qDebug() << "hor_Current_value1" << Index;
        ui->verticalSlider_6->setMaximum(4);
        ui->label_218->setGeometry(120,93,166,320);
        //ui->label_218->setScaledContents(true);

        int Index2 = ui->verticalSlider_6->value();

        //qDebug() << "hor_Current_value2" << Index2;

        //qDebug() << "hor_ArmorPositionVector" << ArmorPositionVector;

    }
    else
    {
        if(value == 0)//torso
        {
            ui->label_218->setGeometry(120,93,322,280);
        }

        if(value == 1)//forearms
        {
            ui->label_218->setGeometry(120,93,240,280);
        }

        if(value == 2)//gloves
        {
            ui->label_218->setGeometry(120,93,260,300);
        }

        if(value == 3)//legs
        {
            ui->label_218->setGeometry(120,93,240,300);
        }

        if(value == 4)//feet
        {
            ui->label_218->setGeometry(120,93,240,270);
        }

        if(value == 5)//head
        {
            ui->label_218->setGeometry(120,93,300,230);
        }


        ui->verticalSlider_6->setMaximum(8);
        //ui->label_218->setScaledContents(true);
        LastIndex = ArmorPositionVector.at(value);
        ui->verticalSlider_6->setValue(LastIndex);

        //qDebug() << "hor_LastIndex" << LastIndex;
        //qDebug() << "hor_ArmorPositionVector" << ArmorPositionVector;
    }

    QString Folder = ArmorFolders.at(value);
    QString filename = "C:/Customize/" + Folder + "/" + QString::number(LastIndex) + ".jpg";

    ui->label_218->setPixmap(filename);




    //qDebug() << "";
}

void MainWindow::on_pushButton_118_clicked()
{
    int value = ui->verticalSlider_6->value();

    int maxInt = 8;

    int Index = ui->horizontalSlider_7->value();

    if(Index == 6)
    {
        maxInt = 4;
    }

    if(value < maxInt)
    {
        value++;
        ui->verticalSlider_6->setValue(value);
    }
}

void MainWindow::on_pushButton_119_clicked()
{
    int value = ui->verticalSlider_6->value();

    int minInt = 0;

    if(value > minInt)
    {
        value--;
        ui->verticalSlider_6->setValue(value);
    }
}

void MainWindow::on_pushButton_120_clicked()
{
    int value = ui->horizontalSlider_7->value();

    if(value != 0)
    {
        value--;
        ui->horizontalSlider_7->setValue(value);
    }
}

QByteArray MainWindow::SendOutLoS(QPixmap currentImage, QByteArray NPCID,
                                  QByteArray AGGRO_Starting_X, QByteArray AGGRO_Starting_Z, QByteArray AGGRO_Starting_Y,
                                  QString LoS_Counter_X, QString LoS_Counter_Z, QString LoS_Counter_Y)
{



}



void MainWindow::on_pushButton_117_clicked()
{
    int value = ui->horizontalSlider_7->value();

    if(value != 6)
    {
        value++;
        ui->horizontalSlider_7->setValue(value);
    }
}

void MainWindow::on_verticalSlider_6_valueChanged(int value)
{

    int Index = ui->horizontalSlider_7->value();

    //qDebug() << "ver_horizontalSlider_7 Index" << Index;
    //qDebug() << "ver_verticalSlider_6 value" << value;

    ArmorPositionVector.replace(Index,value);

    int LastIndex = ArmorPositionVector.at(Index);
    //qDebug() << "ver_LastIndex" << LastIndex;

    //qDebug() << "ver_ArmorPositionVector" << ArmorPositionVector;


    QString Folder = ArmorFolders.at(Index);
    QString filename = "C:/Customize/" + Folder + "/" + QString::number(value) + ".jpg";



    ui->label_218->setPixmap(filename);



    QString SendOut = "";

    if(Index == 0)
    {
        SendOut = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();
        ui->lineEdit_7->setText(SendOut);
        ui->lineEdit_39->setText(SendOut);
    }

    if(Index == 1)
    {
        SendOut = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();
        ui->lineEdit_36->setText(SendOut);
        ui->lineEdit_43->setText(SendOut);
    }

    if(Index == 2)
    {
        SendOut = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();
        ui->lineEdit_38->setText(SendOut);
        ui->lineEdit_48->setText(SendOut);
    }

    if(Index == 3)
    {
        SendOut = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();
        ui->lineEdit_46->setText(SendOut);
        ui->lineEdit_27->setText(SendOut);
    }

    if(Index == 4)
    {
        SendOut = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();
        ui->lineEdit_40->setText(SendOut);
        ui->lineEdit_49->setText(SendOut);
    }

    if(Index == 5)
    {
        SendOut = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();
        ui->lineEdit_42->setText(SendOut);
        ui->lineEdit_47->setText(SendOut);
    }

    if(Index == 6)
    {
        if(value == 0)
        {
            value = 255;
            SendOut = QString("%1").arg(value,2,16,QLatin1Char('0')).toUpper();
            ui->lineEdit_44->setText(SendOut);
            ui->lineEdit_124->setText(SendOut);
        }
        else
        {
            SendOut = QString("%1").arg(value - 1,2,16,QLatin1Char('0')).toUpper();
            ui->lineEdit_44->setText(SendOut);
            ui->lineEdit_124->setText(SendOut);
        }
    }

    on_pushButton_48_clicked();

    //qDebug() << "";
}



void MainWindow::on_pushButton_121_clicked()
{
    for(int WZ = 0; WZ < 6; WZ++)
    {
        QVector <QVector<float>> CurrentZoneCentralVector = checkthezone::VectorOfWorlds.at(WZ);

        //qDebug() << "";

        QString CurrentWorld = WorldNameVector.at(WZ);
        //qDebug() << "World: " << CurrentWorld;

        for(int CZ = 0; CZ < ZonesNamesVector.size(); CZ++)
        {
            //            QVector <QString> tempWorldZoneNamesVector = checkthezone::WorldZoneNamesVector.at(WZ);

            //            QVector <float> CurrentZone = CurrentZoneCentralVector.at(CZ);
            //            QString ZonesName = tempWorldZoneNamesVector.at(CZ);




            //            QVector <QStringList> TempHoldsVector = checkthezone::Zones_IDXZYvectorMap.value(ZonesName);

            QString  ZonesName = ZonesNamesVector.at(CZ);
            int ZoneNumber = ZonesNumbersVector.at(CZ);

            //qDebug() << "ZonesName: " << ZonesName << " ZoneNumber = " << ZoneNumber;
            //            //qDebug() << "TempHoldsVector" << TempHoldsVector;
            //            //qDebug() << "";
        }
    }

    //qDebug() << "";

    QMapIterator<QString,int> iter (ZoneNames_NumbersMap);
    while (iter.hasNext())
    {
        iter.next();

        QString ZonesName = iter.key();
        int ZoneNumber = iter.value();

        //qDebug() << "Zones Name: " << ZonesName << " Zones Number = " << ZoneNumber;
    }
}

void MainWindow::on_pushButton_122_clicked()
{
    ui->textEdit_2->selectAll();
    ui->textEdit_2->copy();
}

void MainWindow::on_pushButton_123_clicked()
{
    ui->plainTextEdit_11->selectAll();
    ui->plainTextEdit_11->copy();
}

void MainWindow::on_pushButton_124_clicked()
{
    float value = ui->lineEdit_155->text().toFloat();
    int value1 = value + 1;
    ui->MyRadius->setText(QString::number(value1));
}

void MainWindow::on_pushButton_125_clicked()
{
    ui->textEdit_12->clear();
}

void MainWindow::on_lineEdit_160_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() == true)
    {
        ui->pushButton_102->setDisabled(true);
        ui->pushButton_103->setDisabled(true);
        ui->Print_XZY->setEnabled(true);
    }
    else
    {
        if(ui->Print_XZY->isEnabled() == false)
        {
            ui->Print_XZY->setEnabled(true);
        }
    }
}

void MainWindow::on_pushButton_126_clicked()
{
    ui->plainTextEdit->selectAll();
    ui->plainTextEdit->copy();
}

void MainWindow::on_lineEdit_130_textChanged(const QString &arg1)
{
    ui->lineEdit_59->setText(arg1);
    ui->lineEdit_191->setText(arg1);
}

//cull
void MainWindow::on_pushButton_127_clicked()
{

    packetparsing::packetvars IN_pushButton_127;
    IN_pushButton_127 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->textEdit_10->clear();

    QString ReuseID = ui->lineEdit_191->text().toUpper();

    if(!ReUseNPCsVector.contains(ReuseID))
    {
        ReUseNPCsVector.append(ReuseID);

        QByteArray HolderReplace = "";

        QString Current_channel = IN_pushButton_127.Map_Channel_ID.key(ReuseID);

        increment SendOut;
        QByteArray holderXorC9 = "XXc9xxxx01100180c800";
        QByteArray pull20 = IN_pushButton_127.incrementmap.value(Current_channel);
        QByteArray result20 = SendOut.count(pull20);
        IN_pushButton_127.incrementmap.insert(Current_channel,result20);

        holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());
        holderXorC9.replace(4,4,result20);

        HolderReplace.append(holderXorC9.toUpper());

        objectpacket::DeadListVector.append(ReuseID);
        IN_pushButton_127.channelmap.insert(Current_channel,"free");

        HolderReplace.insert(0,"d37c5ae792c001bf543213" + IN_pushButton_127.SessionID + "00xxxx");

        HolderReplace.replace(0,4,IN_pushButton_127.serverid1);
        HolderReplace.replace(4,4,IN_pushButton_127.clientid1);

        QVector <QByteArray> MessNumbVect = Opcodes::CharID_ServerMessageNumbers.value(IN_pushButton_127.CharSelectID);
        QByteArray Servers_Last_MessageNumber = MessNumbVect.at(0);

        increment GrpOut;
        QByteArray GrpOut_a = GrpOut.count(Servers_Last_MessageNumber);
        HolderReplace.append(GrpOut_a);
        Servers_Last_MessageNumber = GrpOut_a.toUpper();

        MessNumbVect.replace(0,Servers_Last_MessageNumber);

        Opcodes::CharID_ServerMessageNumbers.insert(IN_pushButton_127.CharSelectID,MessNumbVect);

        packetsize ResizePacket;
        QByteArray ResizePacket2 = ResizePacket.switchsize(HolderReplace);
        HolderReplace.replace(8,4,ResizePacket2);

        crc sendcrc;
        QByteArray outcrc =  sendcrc.elcrc(HolderReplace);
        HolderReplace.append(outcrc);

        QByteArray custom5out = HolderReplace.fromHex(HolderReplace);

        QHostAddress current_client_address;
        current_client_address.setAddress(QString::fromUtf8(IN_pushButton_127.ClientsIP));
        quint16 current_client_port = IN_pushButton_127.ClientsPort.toUShort(nullptr,10);
        QString changeIP = current_client_address.toString();

        QHostAddress newsender = QHostAddress(changeIP);
        worldthread::udpsocket3->writeDatagram(custom5out,newsender,current_client_port);

        QDateTime dateTime = dateTime.currentDateTime();
        QString dateTimeString = dateTime.toString("MM-dd-yy hh:mm:ss.zzzzzzzzz:a");
        ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
        ui->plainTextEdit->appendPlainText("Server_HolderReplace " + dateTimeString);
        ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
        ui->plainTextEdit->appendPlainText(HolderReplace.toUpper());
        ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
        ui->plainTextEdit->appendPlainText("Server_HolderReplace " + dateTimeString);
        ui->plainTextEdit->appendPlainText("_________________________________________________________________________");
        ui->plainTextEdit->moveCursor(QTextCursor::End);

    }
    else
    {
        int index = ReUseNPCsVector.indexOf(ReuseID);
        ReUseNPCsVector.replace(index,ReuseID);
    }

    for(int i = 0; i < ReUseNPCsVector.size(); i++)
    {
        QString IDsLeft = ReUseNPCsVector.at(i);

        QString MOB_Master_c9 = objectpacket::Master_Map.value(IDsLeft.toUtf8().toUpper());
        QString Name24Hex_OldVal1 = MOB_Master_c9.mid(310,48);//name

        ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name

        QString Name = ui->lineEdit_NPC_Name->text();

        ui->textEdit_10->append(IDsLeft + " " + Name);
    }

    ui->lineEdit_192->setText(QString::number(ReUseNPCsVector.size()));

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_pushButton_127);

}

//re-place-npc
void MainWindow::on_pushButton_128_clicked()
{

    ui->textEdit_10->clear();
    if(ReUseNPCsVector.isEmpty() == false)
    {

        packetparsing::packetvars IN_pushButton_128;
        IN_pushButton_128 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);\

        QString ReuseID = ReUseNPCsVector.takeAt(0);

        //ui->textEdit_12->append("ReuseID " + ReuseID);

        ui->lineEdit_193->setText(ReuseID);
        QString world10 = QString("%1").arg(IN_pushButton_128.masterworld,1,10,QLatin1Char('0')).toUpper();

        //ui->textEdit_12->append("World0 " + world10);

        int masterworld2 = world10.toInt(nullptr,10);
        //ui->textEdit_12->append("masterworld2 " + QString::number(masterworld2));

        QVector<QString> AllZoneNames = checkthezone::WorldZoneNamesVector.at(masterworld2);

        int MyZoneNumber = AllZoneNames.indexOf(IN_pushButton_128.LastZone);
        //ui->textEdit_12->append("MyZoneNumber " + QString::number(MyZoneNumber));
        checkthezone::IDandZoneNumber.insert(ReuseID,MyZoneNumber);
        checkthezone::IDsAndWorlds.insert(ReuseID,masterworld2);

        //remove from old zone

        QMap <QString,QVector <QString>> ZoneLocationsIDsVectorMap = checkthezone::VectorOFWorldsZones.value(masterworld2);
        QVector <QString> tempWorldZoneNamesVector = checkthezone::WorldZoneNamesVector.at(masterworld2);

        int ZoneNumber = checkthezone::IDandZoneNumber.value(ReuseID);

        //ui->textEdit_12->append("ZoneNumber " + QString::number(ZoneNumber));
        //ui->textEdit_12->append("");

        if(ZoneNumber != -1)
        {
            QString ZonesName = tempWorldZoneNamesVector.at(ZoneNumber);

            QVector <QStringList> TempHoldsVector = checkthezone::Zones_IDXZYvectorMap.value(ZonesName);
            QStringList holdid0 = TempHoldsVector.at(0);
            QStringList holdx0 = TempHoldsVector.at(1);
            QStringList holdz0 = TempHoldsVector.at(2);
            QStringList holdy0 = TempHoldsVector.at(3);


            int index = holdid0.indexOf(ReuseID);

            if(index != -1)
            {
                holdid0.removeAt(index);
                holdx0.removeAt(index);
                holdz0.removeAt(index);
                holdy0.removeAt(index);
            }

            TempHoldsVector.replace(0,holdid0);
            TempHoldsVector.replace(1,holdx0);
            TempHoldsVector.replace(2,holdz0);
            TempHoldsVector.replace(3,holdy0);

            checkthezone::Zones_IDXZYvectorMap.insert(ZonesName,TempHoldsVector);

            //reload into new zone
            ZonesName = tempWorldZoneNamesVector.at(MyZoneNumber);

            TempHoldsVector = checkthezone::Zones_IDXZYvectorMap.value(ZonesName);

            QVector <QString> LocationsIDsVector = ZoneLocationsIDsVectorMap.value(ZonesName);


            holdid0.append(ReuseID);
            holdx0.append(IN_pushButton_128.masterx.toUpper());
            holdz0.append(IN_pushButton_128.masterz.toUpper());
            holdy0.append(IN_pushButton_128.mastery.toUpper());

            TempHoldsVector.replace(0,holdid0);
            TempHoldsVector.replace(1,holdx0);
            TempHoldsVector.replace(2,holdz0);
            TempHoldsVector.replace(3,holdy0);

            checkthezone::Zones_IDXZYvectorMap.insert(ZonesName,TempHoldsVector);
        }
        QString World1 = QString("%1").arg(IN_pushButton_128.masterworld,2,16,QLatin1Char('0')).toUpper();

        QByteArray MobC9 = objectpacket::Master_Map.value(ReuseID.toUtf8());
        MobC9.replace(12,6,IN_pushButton_128.masterx.toUpper());
        MobC9.replace(18,6,IN_pushButton_128.masterz.toUpper());
        MobC9.replace(24,6,IN_pushButton_128.mastery.toUpper());
        MobC9.replace(30,2,IN_pushButton_128.masterf.toUpper());
        MobC9.replace(34,2,World1.toUtf8().toUpper());

        objectpacket::Master_Map.insert(ReuseID.toUtf8(),MobC9);

        int index2 = IN_pushButton_128.holdid2.indexOf(ReuseID);

        if(index2 != -1)
        {
            IN_pushButton_128.holdid2.replace(index2,ReuseID);
            IN_pushButton_128.holdx2.replace(index2,IN_pushButton_128.masterx.toUpper());
            IN_pushButton_128.holdz2.replace(index2,IN_pushButton_128.masterz.toUpper());
            IN_pushButton_128.holdy2.replace(index2,IN_pushButton_128.mastery.toUpper());
        }
        else
        {
            IN_pushButton_128.holdid2.append(ReuseID);
            IN_pushButton_128.holdx2.append(IN_pushButton_128.masterx.toUpper());
            IN_pushButton_128.holdz2.append(IN_pushButton_128.masterz.toUpper());
            IN_pushButton_128.holdy2.append(IN_pushButton_128.mastery.toUpper());
        }

        int indexR = objectpacket::DeadListVector.indexOf(ReuseID);

        if(indexR != -1)
        {
            objectpacket::DeadListVector.removeAt(indexR);
        }

        int PacketNumber = Opcodes::ID_PacketNumber_Map.value(ReuseID).toInt(nullptr,10);


        QSqlQuery query;
        Table_Name = "NPCS";

        db.transaction();

        Column_Name = "Zone";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",MyZoneNumber);
        query.bindValue(":id",PacketNumber);
        query.exec();




        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = IN_pushButton_128.masterx.toUpper();

        Column_Name = "X (3)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",PacketNumber);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = IN_pushButton_128.masterz.toUpper();

        Column_Name = "Z (3)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",PacketNumber);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = IN_pushButton_128.mastery.toUpper();

        Column_Name = "Y (3)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",PacketNumber);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        Column_value = IN_pushButton_128.masterf.toUpper();

        Column_Name = "Facing (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",PacketNumber);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        Column_value = World1.toUtf8();

        Column_Name = "World (1)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",PacketNumber);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        db.commit();

        for(int i = 0; i < ReUseNPCsVector.size(); i++)
        {
            QString IDsLeft = ReUseNPCsVector.at(i);

            QString MOB_Master_c9 = objectpacket::Master_Map.value(IDsLeft.toUtf8().toUpper());
            QString Name24Hex_OldVal1 = MOB_Master_c9.mid(310,48);//name

            ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name

            QString Name = ui->lineEdit_NPC_Name->text();

            ui->textEdit_10->append(IDsLeft + " " + Name);
        }

        packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_pushButton_128);

    }


    ui->lineEdit_192->setText(QString::number(ReUseNPCsVector.size()));

}

void MainWindow::on_pushButton_129_clicked()
{
    QMessageBox::StandardButton ret =
            QMessageBox::warning(
                this,
                "WARNING!!",
                tr("Are you sure you would like to delete all"
                   "\n"
                   "changes and New NPCs from the edit list?"),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if(ret == QMessageBox::Yes)
    {
        db.transaction();

        QSqlQuery query ("DELETE FROM NPC_CHANGES");

        db.commit();
    }
    else if(ret == QMessageBox::Cancel)
    {

    }
    else if(ret == QMessageBox::No)
    {

    }

}

void MainWindow::on_pushButton_108_clicked()
{

}

void MainWindow::on_pushButton_95_clicked()
{

}

void MainWindow::on_pushButton_130_clicked()
{
    ui->textEdit_12->selectAll();
    ui->textEdit_12->copy();

    //    QString FileName = "C:/PCSX2/" + QString::number(0) + ".txt";

    //    QFile file(FileName);
    //    if(!file.open(QIODevice::Append))
    //    {
    //        //qDebug() << "error opening file: " << file.error();
    //    }


    QString text = ui->textEdit_12->toPlainText();
    QStringList NewLine = text.split("\n");

    for(int i = 0; i < NewLine.size(); i++)
    {
        //file.write(NewLine.at(i).toUtf8());
        //file.write("\n");
    }

    //file.close();
}



void MainWindow::on_pushButton_84_clicked()
{
    ui->textEdit_14->clear();
}








void MainWindow::on_pushButton_42_clicked()
{
    on_pushButton_16_clicked();
}



void MainWindow::on_pushButton_87_clicked()
{

}

QByteArray MainWindow::CheckForLoS(QByteArray NPCID)
{
    packetparsing::packetvars IN_CheckForLoS;
    IN_CheckForLoS = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QString LoS_Master_c9 = objectpacket::Master_Map.value(NPCID);
    QString LoSX = LoS_Master_c9.mid(12,6);
    QString LoSZ = LoS_Master_c9.mid(18,6);
    QString LoSY = LoS_Master_c9.mid(24,6);

    QString tempstrz99 = LoSZ;
    int tempint99 = tempstrz99.toInt(nullptr,16);

    tempint99 = tempint99 + 5;

    LoSZ = QString("%1").arg(tempint99,6,16,QLatin1Char('0')).toUpper();


    QByteArray LoS_Status = "Checking for Line of Sight";

    QString LoS_Counter_X1 = "";
    QString LoS_Counter_Z1 = LoSZ;
    QString LoS_Counter_Y1 = "";

    QByteArray MainLastX = IN_CheckForLoS.masterx;
    QByteArray MainLastZ = IN_CheckForLoS.masterz;
    QByteArray MainLastY = IN_CheckForLoS.mastery;

    QString tempstrz77 = MainLastZ;
    int tempint77 = tempstrz77.toInt(nullptr,16);

    tempint77 = tempint77 + 5;

    MainLastZ = QString("%1").arg(tempint77,6,16,QLatin1Char('0')).toUtf8().toUpper();

    float tx = 0.0;
    float tz = 0.0;
    float ty = 0.0;
    float Z_Difference;

    qlonglong LoS_X = 0;
    qlonglong LoS_Z = 0;
    qlonglong LoS_Y = 0;



    do
    {

        qlonglong Main_LoS_X = MainLastX.toLongLong(nullptr,16);
        qlonglong LoS_Counter_X_EAST = 0x000000;
        qlonglong LoS_Counter_X_WEST = 0x000000;
        LoS_X = LoSX.toLongLong(nullptr,16);

        qlonglong Main_LoS_Z = MainLastZ.toLongLong(nullptr,16);
        qlonglong LoS_Counter_Z_Ground_Z = 0x000000;
        LoS_Z = LoSZ.toLongLong(nullptr,16);

        qlonglong Main_LoS_Y = MainLastY.toLongLong(nullptr,16);
        qlonglong LoS_Counter_Y_South = 0x000000;
        qlonglong LoS_Counter_Y_North = 0x000000;
        LoS_Y = LoSY.toLongLong(nullptr,16);

        QByteArray  myx1 = MainLastX; //send as 3 byte hex
        int xfromhex1 = myx1.toInt(nullptr,16);
        float maintoonx1 = xfromhex1 / 128.0;

        QByteArray  myz1 = MainLastZ;
        int zfromhex1 = myz1.toInt(nullptr,16);
        float maintoonz1 = zfromhex1 / 128.0;

        if(maintoonz1 > 130000)
        {
            maintoonz1 = maintoonz1 - 131072.00195193;
        }

        QByteArray  myy1 = MainLastY;
        int yfromhex1 = myy1.toInt(nullptr,16);
        float maintoony1 = yfromhex1 / 128.0;

        // ///////////////////////////////////////////////////////

        QString tempstrx = LoSX;
        int tempint1 = tempstrx.toInt(nullptr,16);
        float xinterlude = tempint1 / 128.0;

        QString tempstrz = LoSZ;
        int tempint3 = tempstrz.toInt(nullptr,16);
        float  zinterlude = tempint3 / 128.0;

        if(zinterlude > 130000)
        {
            zinterlude = zinterlude - 131072.00195193;
        }

        QString tempstry = LoSY;
        int tempint2 = tempstry.toInt(nullptr,16);
        float yinterlude = tempint2 / 128.0;

        float sub1 = maintoonx1 - xinterlude;
        float sub2 = maintoonz1 - zinterlude;
        float sub3 = maintoony1 - yinterlude;

        float power1 = qPow(sub1,2);
        float power2 = qPow(sub2,2);
        float power3 = qPow(sub3,2);

        float firstresult = power1 + power2 + power3;

        float result2 = qSqrt(firstresult);



        int LoS_Speed = ui->lineEdit_LoS_Speed_2->text().toInt(nullptr,10);

        //EAST
        if(LoS_X > Main_LoS_X && LoS_Y == Main_LoS_Y) // East only
        {
            float east = LoS_X - Main_LoS_X;
            tx = east;
            float dist = qSqrt(tx*tx);
            float speed = LoS_Speed;
            float velX = (tx/dist)*speed;
            LoS_Counter_X_EAST = LoS_X - velX;
            LoS_Counter_X1 = QString("%1").arg(LoS_Counter_X_EAST,6,16,QLatin1Char('0')).toUpper();
        }

        if(LoS_X > Main_LoS_X && LoS_Y > Main_LoS_Y) // East south
        {
            float east = LoS_X - Main_LoS_X;
            float south = LoS_Y - Main_LoS_Y;
            tx = east;
            ty = south;
            float dist = qSqrt(tx * tx + ty * ty);
            float speed = LoS_Speed;
            float velx = (tx/dist)*speed;
            float vely = (ty/dist)*speed;
            LoS_Counter_X_EAST = LoS_X - velx;
            LoS_Counter_Y_South = LoS_Y - vely;
            LoS_Counter_X1 = QString("%1").arg(LoS_Counter_X_EAST,6,16,QLatin1Char('0')).toUpper();
            LoS_Counter_Y1 = QString("%1").arg(LoS_Counter_Y_South,6,16,QLatin1Char('0')).toUpper();
        }

        if(LoS_X > Main_LoS_X && LoS_Y < Main_LoS_Y) // East North
        {
            float east = LoS_X - Main_LoS_X;
            float north = Main_LoS_Y - LoS_Y;
            tx = east;
            ty = north;
            float dist = qSqrt(tx * tx + ty * ty);
            float speed = LoS_Speed;
            float velx = (tx/dist)*speed;
            float vely = (ty/dist)*speed;
            LoS_Counter_X_EAST = LoS_X - velx;
            LoS_Counter_Y_North = LoS_Y + vely;
            LoS_Counter_X1 = QString("%1").arg(LoS_Counter_X_EAST,6,16,QLatin1Char('0')).toUpper();
            LoS_Counter_Y1 = QString("%1").arg(LoS_Counter_Y_North,6,16,QLatin1Char('0')).toUpper();
        }

        //west
        if(LoS_X < Main_LoS_X && LoS_Y == Main_LoS_Y) // west only
        {
            float west = Main_LoS_X - LoS_X;
            tx = west;
            float dist = qSqrt(tx*tx);
            float speed = LoS_Speed;
            float velX = (tx/dist)*speed;
            LoS_Counter_X_WEST = LoS_X + velX;
            LoS_Counter_X1 = QString("%1").arg(LoS_Counter_X_WEST,6,16,QLatin1Char('0')).toUpper();
        }

        if(LoS_X < Main_LoS_X && LoS_Y > Main_LoS_Y) // west south
        {
            float west = Main_LoS_X - LoS_X;//---------West
            float south = LoS_Y - Main_LoS_Y;

            tx = west;
            ty = south;
            float dist = qSqrt(tx * tx + ty * ty);

            float speed = LoS_Speed;

            float velx = (tx/dist)*speed;
            float vely = (ty/dist)*speed;

            LoS_Counter_X_WEST = LoS_X + velx;
            LoS_Counter_Y_South = LoS_Y - vely;

            LoS_Counter_X1 = QString("%1").arg(LoS_Counter_X_WEST,6,16,QLatin1Char('0')).toUpper();
            LoS_Counter_Y1 = QString("%1").arg(LoS_Counter_Y_South,6,16,QLatin1Char('0')).toUpper();
        }


        if(LoS_X < Main_LoS_X && LoS_Y < Main_LoS_Y) // west north
        {
            float west = Main_LoS_X - LoS_X;
            float north = Main_LoS_Y - LoS_Y;
            tx = west;
            ty = north;
            float dist = qSqrt(tx * tx + ty * ty);
            float speed = LoS_Speed;
            float velx = (tx/dist)*speed;
            float vely = (ty/dist)*speed;
            LoS_Counter_X_WEST = LoS_X + velx;
            LoS_Counter_Y_North = LoS_Y + vely;
            LoS_Counter_X1 = QString("%1").arg(LoS_Counter_X_WEST,6,16,QLatin1Char('0')).toUpper();
            LoS_Counter_Y1 = QString("%1").arg(LoS_Counter_Y_North,6,16,QLatin1Char('0')).toUpper();
        }

        //south
        if(LoS_Y > Main_LoS_Y && LoS_X == Main_LoS_X)
        {
            float south = LoS_Y - Main_LoS_Y;
            ty = south;
            float dist = qSqrt(ty*ty);
            float speed = LoS_Speed;
            float vely = (ty/dist)*speed;
            LoS_Counter_Y_South = LoS_Y - vely;
            LoS_Counter_Y1 = QString("%1").arg(LoS_Counter_Y_South,6,16,QLatin1Char('0')).toUpper();
        }

        //north
        if(LoS_Y < Main_LoS_Y && LoS_X == Main_LoS_X)
        {
            float north = Main_LoS_Y - LoS_Y;
            ty = north;
            float dist = qSqrt(ty*ty);
            float speed = LoS_Speed;
            float vely = (ty/dist)*speed;
            LoS_Counter_Y_North = LoS_Y + vely;
            LoS_Counter_Y1 = QString("%1").arg(LoS_Counter_Y_North,6,16,QLatin1Char('0')).toUpper();
        }

        // ////////// Z ///////////// ////

        if(LoS_Z < Main_LoS_Z)
        {
            Z_Difference = Main_LoS_Z - LoS_Z;

            tz = Z_Difference;
            float dist = qSqrt(tx * tx + ty * ty + tz * tz);
            float speed = LoS_Speed;
            float velz = (tz/dist)*speed;
            LoS_Counter_Z_Ground_Z = LoS_Z + velz;

            LoS_Counter_Z1 = QString("%1").arg(LoS_Counter_Z_Ground_Z,6,16,QLatin1Char('0')).toUpper();
        }

        if(LoS_Z > Main_LoS_Z)
        {
            Z_Difference = LoS_Z - Main_LoS_Z;

            tz = Z_Difference;
            float dist = qSqrt(tx * tx + ty * ty + tz * tz);
            float speed = LoS_Speed;
            float velz = (tz/dist)*speed;
            LoS_Counter_Z_Ground_Z = LoS_Z - velz;

            LoS_Counter_Z1 = QString("%1").arg(LoS_Counter_Z_Ground_Z,6,16,QLatin1Char('0')).toUpper();
        }

        if(LoS_X == Main_LoS_X || LoS_Counter_X1.isEmpty() == true)
        {
            LoS_Counter_X1 = LoSX;
        }

        if(LoS_Z == Main_LoS_Z || LoS_Counter_Z1.isEmpty() == true)
        {
            LoS_Counter_Z1 = LoSZ;
        }

        if(LoS_Y == Main_LoS_Y || LoS_Counter_Y1.isEmpty() == true)
        {
            LoS_Counter_Y1 = LoSY;
        }

        LoSX = LoS_Counter_X1;
        LoSZ = LoS_Counter_Z1;
        LoSY = LoS_Counter_Y1;




        QString imagex = LoS_Counter_X1;
        int imagex3 = imagex.toInt(nullptr,16);
        float  X = imagex3 / 128.0;

        QString imagey = LoS_Counter_Y1;
        int imagey3 = imagey.toInt(nullptr,16);
        float  Y = imagey3 / 128.0;


        int West = IN_CheckForLoS.MyZoneCentralX - 1000;
        int East = IN_CheckForLoS.MyZoneCentralX + 1000;
        int North = IN_CheckForLoS.MyZoneCentralY - 1000;
        int South = IN_CheckForLoS.MyZoneCentralY + 1000;

        if (X >= West && X <= East)
        {
            X = X - West;
        }


        if (Y >= North && Y <= South)
        {
            Y = Y - North;
        }

        currentImage = FacingDirection::CurrentImageMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

        qDebug() << "IN_CheckForLoS.FacingDirection::CurrentImageMap" << FacingDirection::CurrentImageMap;

        QImage image2 = currentImage.toImage();

        QColor pixel = image2.pixelColor(X,Y); //ask qcolor what the triplet is


        int pixr = pixel.red(); //get red
        int pixg = pixel.green(); //get green
        int pixb = pixel.blue(); //get blue

        pixr >>= 3; //convert to 0-65535
        pixg >>=2;
        pixb >>=3;

        int fullint1 = (pixr << 11) | (pixg << 5) | pixb;

        fullint1 = fullint1 - 32767;

        QString tempstrz9 = LoSZ;
        int tempint9 = tempstrz9.toInt(nullptr,16);
        float  zinterlude9 = tempint9 / 128.0;

        if(zinterlude9 > 130000)
        {
            zinterlude9 = zinterlude9 - 131072.00195193;
        }


        if(zinterlude9 < fullint1)
        {
            LoS_Status = "You have no Line of Sight";
        }
        else
        {
            LoS_Status = "Checking for Line of Sight";
        }

        if(result2 < 1.5)// LoS location reached
        {
            LoS_Status = "You do have Line of Sight";
        }


    }while(LoS_Status == "Checking for Line of Sight");


    FacingDirection::LoS_StatusMap.insert(NPCID,LoS_Status);

    qDebug() << "CheckForLoS.FacingDirection::CurrentImageMap" << FacingDirection::CurrentImageMap;

    return LoS_Status;
}

//north
void MainWindow::on_pushButton_86_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_115->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_133_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_116->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_131_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_117->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_132_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_118->setText(QString::number(Objx2));
}

//Z high
void MainWindow::on_pushButton_135_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterz; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    if(Objx2 > 130000)
    {
        Objx2 = Objx2 - 131072.00195193;
    }

    ui->lineEdit_113->setText(QString::number(Objx2));
}

//Z Low

void MainWindow::on_pushButton_136_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterz; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    if(Objx2 > 130000)
    {
        Objx2 = Objx2 - 131072.00195193;
    }

    ui->lineEdit_114->setText(QString::number(Objx2));
}



void MainWindow::on_X_4_textChanged(const QString &arg1)
{
    ui->lineEdit_132->setText(arg1);
}

void MainWindow::on_Y_4_textChanged(const QString &arg1)
{
    ui->lineEdit_131->setText(arg1);
}



//add object to the map
void MainWindow::on_pushButton_134_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QString Packet_ID = "";
    QString OBJ_ID = "";
    QByteArray New_OBJ_ID = "";
    int Packet_ID1 = 0;

    if(ui->checkBox_15->isChecked() == false)
    {
        QSqlQuery query ("SELECT COUNT (*) FROM OBJECTS");

        while(query.next())
        {
            Packet_ID = query.value(0).toString();
        }


        int Packet_ID2 = Packet_ID.toInt(nullptr,10);
        Packet_ID1 = Packet_ID.toInt(nullptr,10);
        Packet_ID1++;

        ui->lineEdit_120->setText(QString::number(Packet_ID1));

        QString Object_ID = "ObjectID (4)";
        QSqlQuery query6;
        query6.prepare (QString ("SELECT [%1] FROM OBJECTS WHERE rowid = :val").arg(Object_ID));
        query6.bindValue(":val",Packet_ID2);
        query6.exec();

        while (query6.next())
        {
            ui->lineEdit_119->setText(query6.value(0).toString().toUpper());

            OBJ_ID = query6.value(0).toString().toUpper();
        }

        QByteArray split1 = OBJ_ID.toUtf8(); //AAAABBBB

        QByteArray first_4_digits = split1.mid(0,4); //AAAA
        QByteArray last_4_digits = split1.mid(4,4); //BBBB

        increment first1; //get class object
        QByteArray firstresult1 = first1.count(first_4_digits).toUpper(); //ABAA

        if(firstresult1 == "0000")
        {
            first_4_digits = "0000";

            increment second1; //get class object
            QByteArray secondresult1 = second1.count(last_4_digits).toUpper(); //if first is FFFF this will be BCBB //secondresult is bytearray in header
            New_OBJ_ID = firstresult1 + secondresult1.toUpper();

            if(New_OBJ_ID.size() == 4)
            {
                New_OBJ_ID.append("0000");
            }

            ui->lineEdit_119->setText(New_OBJ_ID);
        }
        else
        {
            New_OBJ_ID = firstresult1 + last_4_digits.toUpper();

            if(New_OBJ_ID.size() == 4)
            {
                New_OBJ_ID.append("0000");
            }

            ui->lineEdit_119->setText(New_OBJ_ID);
        }

    }
    else
    {
        Packet_ID1 = ui->lineEdit_120->text().toInt(nullptr,10);
    }

    QVector<QString> XZYsVector;

    QString World = ui->lineEdit_World->text();

    QString CurrentZonesCentral = ui->lineEdit_CurrentZoneCentral->text();

    QString BuildingsName = ui->lineEdit_219->text();

    QString X4 = ui->X_4->text().toUpper();
    QString Z4 = ui->Z_4->text().toUpper();
    QString Y4 = ui->Y_4->text().toUpper();

    QString North = ui->lineEdit_115->text();
    QString West = ui->lineEdit_116->text();
    QString East = ui->lineEdit_117->text();
    QString South = ui->lineEdit_118->text();



    QString North_L1 = ui->lineEdit_North_L1->text();
    QString West_L1 = ui->lineEdit_West_L1->text();
    QString East_L1 = ui->lineEdit_East_L1->text();
    QString South_L1 = ui->lineEdit_South_L1->text();
    QString High_Z1 = ui->lineEdit_High_Z1->text();
    QString Low_Z1 = ui->lineEdit_Low_Z1->text();
    QString LevelsName_L1_ = ui->lineEdit_LevelsName_L1->text();

    QString North_L2 = ui->lineEdit_North_L2->text();
    QString West_L2 = ui->lineEdit_West_L2->text();
    QString East_L2 = ui->lineEdit_East_L2->text();
    QString South_L2 = ui->lineEdit_South_L2->text();
    QString High_Z2 = ui->lineEdit_High_Z2->text();
    QString Low_Z2 = ui->lineEdit_Low_Z2->text();
    QString LevelsName_L2_ = ui->lineEdit_LevelsName_L2->text();

    QString North_L3 = ui->lineEdit_North_L3->text();
    QString West_L3 = ui->lineEdit_West_L3->text();
    QString East_L3 = ui->lineEdit_East_L3->text();
    QString South_L3 = ui->lineEdit_South_L3->text();
    QString High_Z3 = ui->lineEdit_High_Z3->text();
    QString Low_Z3 = ui->lineEdit_Low_Z3->text();
    QString LevelsName_L3_ = ui->lineEdit_LevelsName_L3->text();

    QString North_L4 = ui->lineEdit_North_L4->text();
    QString West_L4 = ui->lineEdit_West_L4->text();
    QString East_L4 = ui->lineEdit_East_L4->text();
    QString South_L4 = ui->lineEdit_South_L4->text();
    QString High_Z4 = ui->lineEdit_High_Z4->text();
    QString Low_Z4 = ui->lineEdit_Low_Z4->text();
    QString LevelsName_L4_ = ui->lineEdit_LevelsName_L4->text();

    QString North_L5 = ui->lineEdit_North_L5->text();
    QString West_L5 = ui->lineEdit_West_L5->text();
    QString East_L5 = ui->lineEdit_East_L5->text();
    QString South_L5 = ui->lineEdit_South_L5->text();
    QString High_Z5 = ui->lineEdit_High_Z5->text();
    QString Low_Z5 = ui->lineEdit_Low_Z5->text();
    QString LevelsName_L5_ = ui->lineEdit_LevelsName_L5->text();

    QString North_L6 = ui->lineEdit_North_L6->text();
    QString West_L6 = ui->lineEdit_West_L6->text();
    QString East_L6 = ui->lineEdit_East_L6->text();
    QString South_L6 = ui->lineEdit_South_L6->text();
    QString High_Z6 = ui->lineEdit_High_Z6->text();
    QString Low_Z6 = ui->lineEdit_Low_Z6->text();
    QString LevelsName_L6_ = ui->lineEdit_LevelsName_L6->text();

    QString North_L7 = ui->lineEdit_North_L7->text();
    QString West_L7 = ui->lineEdit_West_L7->text();
    QString East_L7 = ui->lineEdit_East_L7->text();
    QString South_L7 = ui->lineEdit_South_L7->text();
    QString High_Z7 = ui->lineEdit_High_Z7->text();
    QString Low_Z7 = ui->lineEdit_Low_Z7->text();
    QString LevelsName_L7_ = ui->lineEdit_LevelsName_L7->text();

    QString North_GZ = ui->lineEdit_North_GZ->text();
    QString West_GZ = ui->lineEdit_West_GZ->text();
    QString East_GZ = ui->lineEdit_East_GZ->text();
    QString South_GZ = ui->lineEdit_South_GZ->text();

    QString Ground_Zero_GZ = ui->lineEdit_Ground_Zero_Z->text();

    QString North_GZ_2 = ui->lineEdit_North_GZ_2->text();
    QString West_GZ_2 = ui->lineEdit_West_GZ_2->text();
    QString East_GZ_2 = ui->lineEdit_East_GZ_2->text();
    QString South_GZ_2 = ui->lineEdit_South_GZ_2->text();

    QString Ground_Zero_GZ_2 = ui->lineEdit_Ground_Zero_Z_2->text();



    XZYsVector.append(QString::number(Packet_ID1));
    XZYsVector.append(IN_pushButton.CurrentCentralZone);
    XZYsVector.append(World);
    XZYsVector.append(BuildingsName);
    XZYsVector.append(X4);
    XZYsVector.append(Z4);
    XZYsVector.append(Y4);
    XZYsVector.append(North);
    XZYsVector.append(West);
    XZYsVector.append(East);
    XZYsVector.append(South);

    XZYsVector.append(North_L1);
    XZYsVector.append(West_L1);
    XZYsVector.append(East_L1);
    XZYsVector.append(South_L1);
    XZYsVector.append(High_Z1);
    XZYsVector.append(Low_Z1);
    XZYsVector.append(LevelsName_L1_);

    XZYsVector.append(North_L2);
    XZYsVector.append(West_L2);
    XZYsVector.append(East_L2);
    XZYsVector.append(South_L2);
    XZYsVector.append(High_Z2);
    XZYsVector.append(Low_Z2);
    XZYsVector.append(LevelsName_L2_);

    XZYsVector.append(North_L3);
    XZYsVector.append(West_L3);
    XZYsVector.append(East_L3);
    XZYsVector.append(South_L3);
    XZYsVector.append(High_Z3);
    XZYsVector.append(Low_Z3);
    XZYsVector.append(LevelsName_L3_);

    XZYsVector.append(North_L4);
    XZYsVector.append(West_L4);
    XZYsVector.append(East_L4);
    XZYsVector.append(South_L4);
    XZYsVector.append(High_Z4);
    XZYsVector.append(Low_Z4);
    XZYsVector.append(LevelsName_L4_);

    XZYsVector.append(North_L5);
    XZYsVector.append(West_L5);
    XZYsVector.append(East_L5);
    XZYsVector.append(South_L5);
    XZYsVector.append(High_Z5);
    XZYsVector.append(Low_Z5);
    XZYsVector.append(LevelsName_L5_);

    XZYsVector.append(North_L6);
    XZYsVector.append(West_L6);
    XZYsVector.append(East_L6);
    XZYsVector.append(South_L6);
    XZYsVector.append(High_Z6);
    XZYsVector.append(Low_Z6);
    XZYsVector.append(LevelsName_L6_);

    XZYsVector.append(North_L7);
    XZYsVector.append(West_L7);
    XZYsVector.append(East_L7);
    XZYsVector.append(South_L7);
    XZYsVector.append(High_Z7);
    XZYsVector.append(Low_Z7);
    XZYsVector.append(LevelsName_L7_);

    XZYsVector.append(North_GZ);
    XZYsVector.append(West_GZ);
    XZYsVector.append(East_GZ);
    XZYsVector.append(South_GZ);

    XZYsVector.append(Ground_Zero_GZ);

    XZYsVector.append(North_GZ_2);
    XZYsVector.append(West_GZ_2);
    XZYsVector.append(East_GZ_2);
    XZYsVector.append(South_GZ_2);

    XZYsVector.append(Ground_Zero_GZ_2);

    QString Zone = XZYsVector.at(1);
    Magnify_North = XZYsVector.at(7).toFloat();
    Magnify_West = XZYsVector.at(8).toFloat();
    Magnify_East = XZYsVector.at(9).toFloat();
    Magnify_South = XZYsVector.at(10).toFloat();

    LevelsNorth_L1 = XZYsVector.at(11);
    LevelsWest_L1 = XZYsVector.at(12);
    LevelsEast_L1 = XZYsVector.at(13);
    LevelsSouth_L1 = XZYsVector.at(14);
    Levels_High_Z1 = XZYsVector.at(15);
    Levels_Low_Z1 = XZYsVector.at(16);
    LevelsName_L1 = XZYsVector.at(17);

    LevelsNorth_L2 = XZYsVector.at(18);
    LevelsWest_L2 = XZYsVector.at(19);
    LevelsEast_L2 = XZYsVector.at(20);
    LevelsSouth_L2 = XZYsVector.at(21);
    Levels_High_Z2 = XZYsVector.at(22);
    Levels_Low_Z2 = XZYsVector.at(23);
    LevelsName_L2 = XZYsVector.at(24);

    LevelsNorth_L3 = XZYsVector.at(25);
    LevelsWest_L3 = XZYsVector.at(26);
    LevelsEast_L3 = XZYsVector.at(27);
    LevelsSouth_L3 = XZYsVector.at(28);
    Levels_High_Z3 = XZYsVector.at(29);
    Levels_Low_Z3 = XZYsVector.at(30);
    LevelsName_L3 = XZYsVector.at(31);

    LevelsNorth_L4 = XZYsVector.at(32);
    LevelsWest_L4 = XZYsVector.at(33);
    LevelsEast_L4 = XZYsVector.at(34);
    LevelsSouth_L4 = XZYsVector.at(35);
    Levels_High_Z4 = XZYsVector.at(36);
    Levels_Low_Z4 = XZYsVector.at(37);
    LevelsName_L4 = XZYsVector.at(38);

    LevelsNorth_L5 = XZYsVector.at(39);
    LevelsWest_L5 = XZYsVector.at(40);
    LevelsEast_L5 = XZYsVector.at(41);
    LevelsSouth_L5 = XZYsVector.at(42);
    Levels_High_Z5 = XZYsVector.at(43);
    Levels_Low_Z5 = XZYsVector.at(44);
    LevelsName_L5 = XZYsVector.at(45);

    LevelsNorth_L6 = XZYsVector.at(46);
    LevelsWest_L6 = XZYsVector.at(47);
    LevelsEast_L6 = XZYsVector.at(48);
    LevelsSouth_L6 = XZYsVector.at(49);
    Levels_High_Z6 = XZYsVector.at(50);
    Levels_Low_Z6 = XZYsVector.at(51);
    LevelsName_L6 = XZYsVector.at(52);

    LevelsNorth_L7 = XZYsVector.at(53);
    LevelsWest_L7 = XZYsVector.at(54);
    LevelsEast_L7 = XZYsVector.at(55);
    LevelsSouth_L7 = XZYsVector.at(56);
    Levels_High_Z7 = XZYsVector.at(57);
    Levels_Low_Z7 = XZYsVector.at(58);
    LevelsName_L7 = XZYsVector.at(59);

    Entrance_1_North_GZ = XZYsVector.at(60).toFloat();
    Entrance_1_West_GZ = XZYsVector.at(61).toFloat();
    Entrance_1_East_GZ = XZYsVector.at(62).toFloat();
    Entrance_1_South_GZ = XZYsVector.at(63).toFloat();

    Entrance_1_GZ = XZYsVector.at(64).toFloat();

    Entrance_2_North_GZ = XZYsVector.at(65).toFloat();
    Entrance_2_West_GZ = XZYsVector.at(66).toFloat();
    Entrance_2_East_GZ = XZYsVector.at(67).toFloat();
    Entrance_2_South_GZ = XZYsVector.at(68).toFloat();

    Entrance_2_GZ = XZYsVector.at(69).toFloat();


    QMap<QString,QMap<QString,QVector<QString>>> ZoneForOBJvectorsmaps = checkthezone::WorldsVectorOFObjectZonesMaps.at(IN_pushButton.masterworld);

    QMap<QString,QVector<QString>> OBJ_XZYsVectorMap = ZoneForOBJvectorsmaps.value(IN_pushButton.CurrentCentralZone);

    OBJ_XZYsVectorMap.insert(New_OBJ_ID,XZYsVector);

    ZoneForOBJvectorsmaps.insert(IN_pushButton.CurrentCentralZone,OBJ_XZYsVectorMap);
    checkthezone::WorldsVectorOFObjectZonesMaps.replace(IN_pushButton.masterworld,ZoneForOBJvectorsmaps);
}

//update the db
void MainWindow::on_pushButton_85_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QVector<QString> TableNames =
    {
        "OBJECTS","Object_Changes"
    };

    db.transaction();

    for(int tb = 0; tb < TableNames.size(); tb ++)
    {

        QSqlQuery query;

        Table_Name = TableNames.at(tb);

        int packetid = ui->lineEdit_120->text().toInt(nullptr,10);

        Column_Name = "PacketID";
        query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText("PacketID " + query.lastError().text());
            return;
        }

        QString Column_value = ui->lineEdit_119->text().toUpper();

        Column_Name = "ObjectID (4)";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Column_value);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText("ObjectID " + query.lastError().text());
            return;
        }

        Column_Name = "Zone";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",IN_pushButton.CurrentCentralZone);
        query.bindValue(":id",packetid);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText("ZoneName " + query.lastError().text());
            return;
        }

        QVector<QString> tempVect;

        QString World = ui->lineEdit_World->text();

        tempVect.append(World);
        tempVect.append("World");

        QString Zone = ui->lineEdit_CurrentZoneCentral->text();

        tempVect.append(Zone);
        tempVect.append("Zone");

        QString BuildingsName = ui->lineEdit_219->text();

        tempVect.append(BuildingsName);
        tempVect.append("BuildingsName");

        QString X4 = ui->X_4->text().toUpper();
        tempVect.append(X4);
        tempVect.append("X (3)");

        QString Z4 = ui->Z_4->text().toUpper();
        tempVect.append(Z4);
        tempVect.append("Z (3)");

        QString Y4 = ui->Y_4->text().toUpper();
        tempVect.append(Y4);
        tempVect.append("Y (3)");

        QString North = ui->lineEdit_115->text();
        tempVect.append(North);
        tempVect.append("North");

        QString West = ui->lineEdit_116->text();
        tempVect.append(West);
        tempVect.append("West");

        QString East = ui->lineEdit_117->text();
        tempVect.append(East);
        tempVect.append("East");

        QString South = ui->lineEdit_118->text();
        tempVect.append(South);
        tempVect.append("South");

        QString North_L1 = ui->lineEdit_North_L1->text();
        tempVect.append(North_L1);
        tempVect.append("North_L1");

        QString West_L1 = ui->lineEdit_West_L1->text();
        tempVect.append(West_L1);
        tempVect.append("West_L1");

        QString East_L1 = ui->lineEdit_East_L1->text();
        tempVect.append(East_L1);
        tempVect.append("East_L1");

        QString South_L1 = ui->lineEdit_South_L1->text();
        tempVect.append(South_L1);
        tempVect.append("South_L1");

        QString High_Z1 = ui->lineEdit_High_Z1->text();
        tempVect.append(High_Z1);
        tempVect.append("High_Z1");

        QString Low_Z1 = ui->lineEdit_Low_Z1->text();
        tempVect.append(Low_Z1);
        tempVect.append("Low_Z1");

        QString LevelsName_L1 = ui->lineEdit_LevelsName_L1->text();
        tempVect.append(LevelsName_L1);
        tempVect.append("LevelsName_L1");

        QString North_L2 = ui->lineEdit_North_L2->text();
        tempVect.append(North_L2);
        tempVect.append("North_L2");

        QString West_L2 = ui->lineEdit_West_L2->text();
        tempVect.append(West_L2);
        tempVect.append("West_L2");

        QString East_L2 = ui->lineEdit_East_L2->text();
        tempVect.append(East_L2);
        tempVect.append("East_L2");

        QString South_L2 = ui->lineEdit_South_L2->text();
        tempVect.append(South_L2);
        tempVect.append("South_L2");

        QString High_Z2 = ui->lineEdit_High_Z2->text();
        tempVect.append(High_Z2);
        tempVect.append("High_Z2");

        QString Low_Z2 = ui->lineEdit_Low_Z2->text();
        tempVect.append(Low_Z2);
        tempVect.append("Low_Z2");

        QString LevelsName_L2 = ui->lineEdit_LevelsName_L2->text();
        tempVect.append(LevelsName_L2);
        tempVect.append("LevelsName_L2");

        QString North_L3 = ui->lineEdit_North_L3->text();
        tempVect.append(North_L3);
        tempVect.append("North_L3");

        QString West_L3 = ui->lineEdit_West_L3->text();
        tempVect.append(West_L3);
        tempVect.append("West_L3");

        QString East_L3 = ui->lineEdit_East_L3->text();
        tempVect.append(East_L3);
        tempVect.append("East_L3");

        QString South_L3 = ui->lineEdit_South_L3->text();
        tempVect.append(South_L3);
        tempVect.append("South_L3");

        QString High_Z3 = ui->lineEdit_High_Z3->text();
        tempVect.append(High_Z3);
        tempVect.append("High_Z3");

        QString Low_Z3 = ui->lineEdit_Low_Z3->text();
        tempVect.append(Low_Z3);
        tempVect.append("Low_Z3");

        QString LevelsName_L3 = ui->lineEdit_LevelsName_L3->text();
        tempVect.append(LevelsName_L3);
        tempVect.append("LevelsName_L3");

        QString North_L4 = ui->lineEdit_North_L4->text();
        tempVect.append(North_L4);
        tempVect.append("North_L4");

        QString West_L4 = ui->lineEdit_West_L4->text();
        tempVect.append(West_L4);
        tempVect.append("West_L4");

        QString East_L4 = ui->lineEdit_East_L4->text();
        tempVect.append(East_L4);
        tempVect.append("East_L4");

        QString South_L4 = ui->lineEdit_South_L4->text();
        tempVect.append(South_L4);
        tempVect.append("South_L4");

        QString High_Z4 = ui->lineEdit_High_Z4->text();
        tempVect.append(High_Z4);
        tempVect.append("High_Z4");

        QString Low_Z4 = ui->lineEdit_Low_Z4->text();
        tempVect.append(Low_Z4);
        tempVect.append("Low_Z4");

        QString LevelsName_L4 = ui->lineEdit_LevelsName_L4->text();
        tempVect.append(LevelsName_L4);
        tempVect.append("LevelsName_L4");

        QString North_L5 = ui->lineEdit_North_L5->text();
        tempVect.append(North_L5);
        tempVect.append("North_L5");

        QString West_L5 = ui->lineEdit_West_L5->text();
        tempVect.append(West_L5);
        tempVect.append("West_L5");

        QString East_L5 = ui->lineEdit_East_L5->text();
        tempVect.append(East_L5);
        tempVect.append("East_L5");

        QString South_L5 = ui->lineEdit_South_L5->text();
        tempVect.append(South_L5);
        tempVect.append("South_L5");

        QString High_Z5 = ui->lineEdit_High_Z5->text();
        tempVect.append(High_Z5);
        tempVect.append("High_Z5");

        QString Low_Z5 = ui->lineEdit_Low_Z5->text();
        tempVect.append(Low_Z5);
        tempVect.append("Low_Z5");

        QString LevelsName_L5 = ui->lineEdit_LevelsName_L5->text();
        tempVect.append(LevelsName_L5);
        tempVect.append("LevelsName_L5");

        QString North_L6 = ui->lineEdit_North_L6->text();
        tempVect.append(North_L6);
        tempVect.append("North_L6");

        QString West_L6 = ui->lineEdit_West_L6->text();
        tempVect.append(West_L6);
        tempVect.append("West_L6");

        QString East_L6 = ui->lineEdit_East_L6->text();
        tempVect.append(East_L6);
        tempVect.append("East_L6");

        QString South_L6 = ui->lineEdit_South_L6->text();
        tempVect.append(South_L6);
        tempVect.append("South_L6");

        QString High_Z6 = ui->lineEdit_High_Z6->text();
        tempVect.append(High_Z6);
        tempVect.append("High_Z6");

        QString Low_Z6 = ui->lineEdit_Low_Z6->text();
        tempVect.append(Low_Z6);
        tempVect.append("Low_Z6");

        QString LevelsName_L6 = ui->lineEdit_LevelsName_L6->text();
        tempVect.append(LevelsName_L6);
        tempVect.append("LevelsName_L6");

        QString North_L7 = ui->lineEdit_North_L7->text();
        tempVect.append(North_L7);
        tempVect.append("North_L7");

        QString West_L7 = ui->lineEdit_West_L7->text();
        tempVect.append(West_L7);
        tempVect.append("West_L7");

        QString East_L7 = ui->lineEdit_East_L7->text();
        tempVect.append(East_L7);
        tempVect.append("East_L7");

        QString South_L7 = ui->lineEdit_South_L7->text();
        tempVect.append(South_L7);
        tempVect.append("South_L7");

        QString High_Z7 = ui->lineEdit_High_Z7->text();
        tempVect.append(High_Z7);
        tempVect.append("High_Z7");

        QString Low_Z7 = ui->lineEdit_Low_Z7->text();
        tempVect.append(Low_Z7);
        tempVect.append("Low_Z7");

        QString LevelsName_L7 = ui->lineEdit_LevelsName_L7->text();
        tempVect.append(LevelsName_L7);
        tempVect.append("LevelsName_L7");

        QString North_GZ = ui->lineEdit_North_GZ->text();
        tempVect.append(North_GZ);
        tempVect.append("North_GZ");

        QString West_GZ = ui->lineEdit_West_GZ->text();
        tempVect.append(West_GZ);
        tempVect.append("West_GZ");

        QString East_GZ = ui->lineEdit_East_GZ->text();
        tempVect.append(East_GZ);
        tempVect.append("East_GZ");

        QString South_GZ = ui->lineEdit_South_GZ->text();
        tempVect.append(South_GZ);
        tempVect.append("South_GZ");

        QString Ground_Zero_GZ = ui->lineEdit_Ground_Zero_Z->text();
        tempVect.append(Ground_Zero_GZ);
        tempVect.append("Ground_Zero_GZ");

        QString North_GZ_2 = ui->lineEdit_North_GZ_2->text();
        tempVect.append(North_GZ_2);
        tempVect.append("North_GZ_2");

        QString West_GZ_2 = ui->lineEdit_West_GZ_2->text();
        tempVect.append(West_GZ_2);
        tempVect.append("West_GZ_2");

        QString East_GZ_2 = ui->lineEdit_East_GZ_2->text();
        tempVect.append(East_GZ_2);
        tempVect.append("East_GZ_2");

        QString South_GZ_2 = ui->lineEdit_South_GZ_2->text();
        tempVect.append(South_GZ_2);
        tempVect.append("South_GZ_2");

        QString Ground_Zero_GZ_2 = ui->lineEdit_Ground_Zero_Z_2->text();
        tempVect.append(Ground_Zero_GZ_2);
        tempVect.append("Ground_Zero_GZ_2");

        for(int ww = 0; ww < tempVect.size(); ww+=2)
        {
            Column_value = tempVect.at(ww);
            Column_Name = tempVect.at(ww+1);

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Column_value);
            query.bindValue(":id",packetid);
            query.exec();

            if(!query.exec())
            {
                ui->lineEdit_20->setText(Column_Name + " " + query.lastError().text());
                return;
            }
        }
    }

    db.commit();

}

void MainWindow::on_pushButton_148_clicked()
{
    ui->textEdit_22->clear();
}

void MainWindow::on_pushButton_144_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->lineEdit_131->setText(IN_pushButton.mastery.toUpper());
    ui->lineEdit_132->setText(IN_pushButton.masterx.toUpper());
}

void MainWindow::on_pushButton_Set_Z1_clicked()
{
    QString High = ui->lineEdit_113->text();
    ui->lineEdit_High_Z1->setText(High);

    QString Low = ui->lineEdit_114->text();
    ui->lineEdit_Low_Z1->setText(Low);

}

void MainWindow::on_pushButton_Set_Z2_clicked()
{
    QString High = ui->lineEdit_113->text();
    ui->lineEdit_High_Z2->setText(High);

    QString Low = ui->lineEdit_114->text();
    ui->lineEdit_Low_Z2->setText(Low);

}

void MainWindow::on_pushButton_Set_Z3_clicked()
{
    QString High = ui->lineEdit_113->text();
    ui->lineEdit_High_Z3->setText(High);

    QString Low = ui->lineEdit_114->text();
    ui->lineEdit_Low_Z3->setText(Low);

}


void MainWindow::on_pushButton_Set_Z4_clicked()
{
    QString High = ui->lineEdit_113->text();
    ui->lineEdit_High_Z4->setText(High);

    QString Low = ui->lineEdit_114->text();
    ui->lineEdit_Low_Z4->setText(Low);

}

void MainWindow::on_pushButton_Set_Z5_clicked()
{
    QString High = ui->lineEdit_113->text();
    ui->lineEdit_High_Z5->setText(High);

    QString Low = ui->lineEdit_114->text();
    ui->lineEdit_Low_Z5->setText(Low);

}

void MainWindow::on_pushButton_Set_Z6_clicked()
{
    QString High = ui->lineEdit_113->text();
    ui->lineEdit_High_Z6->setText(High);

    QString Low = ui->lineEdit_114->text();
    ui->lineEdit_Low_Z6->setText(Low);

}

void MainWindow::on_pushButton_Set_Z7_clicked()
{
    QString High = ui->lineEdit_113->text();
    ui->lineEdit_High_Z7->setText(High);

    QString Low = ui->lineEdit_114->text();
    ui->lineEdit_Low_Z7->setText(Low);

}


void MainWindow::on_pushButton_137_clicked()
{
    if(ui->comboBox_2->count() > 0)
    {
        packetparsing::packetvars IN_pushButton;
        IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

        QMap<QString,QMap<QString,QVector<QString>>> ZoneForOBJvectorsmaps = checkthezone::WorldsVectorOFObjectZonesMaps.at(IN_pushButton.masterworld);

        QString ZoneName = ui->comboBox_2->currentText();

        QMap<QString,QVector<QString>> OBJ_XZYsVectorMap = ZoneForOBJvectorsmaps.value(ZoneName);

        QString ObjectsID = ui->comboBox_3->currentText();

        QVector<QString> XZYsVector =  OBJ_XZYsVectorMap.value(ObjectsID);

        QString Packet_ID = XZYsVector.at(0);
        QString World = XZYsVector.at(2);

        QString BuildingsName = ui->comboBox_4->currentText();

        QString X4 = XZYsVector.at(4);
        QString Z4 = XZYsVector.at(5);
        QString Y4 = XZYsVector.at(6);

        QString North = XZYsVector.at(7);
        QString West = XZYsVector.at(8);
        QString East = XZYsVector.at(9);
        QString South = XZYsVector.at(10);


        QString North_L1 = XZYsVector.at(11);
        QString West_L1 = XZYsVector.at(12);
        QString East_L1 = XZYsVector.at(13);
        QString South_L1 = XZYsVector.at(14);
        QString High_Z1 = XZYsVector.at(15);
        QString Low_Z1 = XZYsVector.at(16);
        QString LevelsName_L1 = XZYsVector.at(17);

        QString North_L2 = XZYsVector.at(18);
        QString West_L2 = XZYsVector.at(19);
        QString East_L2 = XZYsVector.at(20);
        QString South_L2 = XZYsVector.at(21);
        QString High_Z2 = XZYsVector.at(22);
        QString Low_Z2 = XZYsVector.at(23);
        QString LevelsName_L2 = XZYsVector.at(24);

        QString North_L3 = XZYsVector.at(25);
        QString West_L3 = XZYsVector.at(26);
        QString East_L3 = XZYsVector.at(27);
        QString South_L3 = XZYsVector.at(28);
        QString High_Z3 = XZYsVector.at(29);
        QString Low_Z3 = XZYsVector.at(30);
        QString LevelsName_L3 = XZYsVector.at(31);

        QString North_L4 = XZYsVector.at(32);
        QString West_L4 = XZYsVector.at(33);
        QString East_L4 = XZYsVector.at(34);
        QString South_L4 = XZYsVector.at(35);
        QString High_Z4 = XZYsVector.at(36);
        QString Low_Z4 = XZYsVector.at(37);
        QString LevelsName_L4 = XZYsVector.at(38);

        QString North_L5 = XZYsVector.at(39);
        QString West_L5 = XZYsVector.at(40);
        QString East_L5 = XZYsVector.at(41);
        QString South_L5 = XZYsVector.at(42);
        QString High_Z5 = XZYsVector.at(43);
        QString Low_Z5 = XZYsVector.at(44);
        QString LevelsName_L5 = XZYsVector.at(45);

        QString North_L6 = XZYsVector.at(46);
        QString West_L6 = XZYsVector.at(47);
        QString East_L6 = XZYsVector.at(48);
        QString South_L6 = XZYsVector.at(49);
        QString High_Z6 = XZYsVector.at(50);
        QString Low_Z6 = XZYsVector.at(51);
        QString LevelsName_L6 = XZYsVector.at(52);

        QString North_L7 = XZYsVector.at(53);
        QString West_L7 = XZYsVector.at(54);
        QString East_L7 = XZYsVector.at(55);
        QString South_L7 = XZYsVector.at(56);
        QString High_Z7 = XZYsVector.at(57);
        QString Low_Z7 = XZYsVector.at(58);
        QString LevelsName_L7 = XZYsVector.at(59);

        QString North_GZ = XZYsVector.at(60);
        QString West_GZ = XZYsVector.at(61);
        QString East_GZ = XZYsVector.at(62);
        QString South_GZ = XZYsVector.at(63);

        QString Ground_Zero_GZ = XZYsVector.at(64);

        QString North_GZ_2 = XZYsVector.at(65);
        QString West_GZ_2 = XZYsVector.at(66);
        QString East_GZ_2 = XZYsVector.at(67);
        QString South_GZ_2 = XZYsVector.at(68);

        QString Ground_Zero_GZ_2 = XZYsVector.at(69);

        ui->lineEdit_120->setText(Packet_ID);
        ui->lineEdit_CurrentZoneCentral->setText(ZoneName);
        ui->lineEdit_World->setText(World);
        ui->lineEdit_119->setText(ObjectsID);

        ui->lineEdit_219->setText(BuildingsName);

        ui->X_4->setText(X4);
        ui->Z_4->setText(Z4);
        ui->Y_4->setText(Y4);

        ui->lineEdit_115->setText(North);
        ui->lineEdit_116->setText(West);
        ui->lineEdit_117->setText(East);
        ui->lineEdit_118->setText(South);

        ui->lineEdit_North_L1->setText(North_L1);
        ui->lineEdit_West_L1->setText(West_L1);
        ui->lineEdit_East_L1->setText(East_L1);
        ui->lineEdit_South_L1->setText(South_L1);
        ui->lineEdit_High_Z1->setText(High_Z1);
        ui->lineEdit_Low_Z1->setText(Low_Z1);
        ui->lineEdit_LevelsName_L1->setText(LevelsName_L1);

        ui->lineEdit_North_L2->setText(North_L2);
        ui->lineEdit_West_L2->setText(West_L2);
        ui->lineEdit_East_L2->setText(East_L2);
        ui->lineEdit_South_L2->setText(South_L2);
        ui->lineEdit_High_Z2->setText(High_Z2);
        ui->lineEdit_Low_Z2->setText(Low_Z2);
        ui->lineEdit_LevelsName_L2->setText(LevelsName_L2);

        ui->lineEdit_North_L3->setText(North_L3);
        ui->lineEdit_West_L3->setText(West_L3);
        ui->lineEdit_East_L3->setText(East_L3);
        ui->lineEdit_South_L3->setText(South_L3);
        ui->lineEdit_High_Z3->setText(High_Z3);
        ui->lineEdit_Low_Z3->setText(Low_Z3);
        ui->lineEdit_LevelsName_L3->setText(LevelsName_L3);

        ui->lineEdit_North_L4->setText(North_L4);
        ui->lineEdit_West_L4->setText(West_L4);
        ui->lineEdit_East_L4->setText(East_L4);
        ui->lineEdit_South_L4->setText(South_L4);
        ui->lineEdit_High_Z4->setText(High_Z4);
        ui->lineEdit_Low_Z4->setText(Low_Z4);
        ui->lineEdit_LevelsName_L4->setText(LevelsName_L4);


        ui->lineEdit_North_L5->setText(North_L5);
        ui->lineEdit_West_L5->setText(West_L5);
        ui->lineEdit_East_L5->setText(East_L5);
        ui->lineEdit_South_L5->setText(South_L5);
        ui->lineEdit_High_Z5->setText(High_Z5);
        ui->lineEdit_Low_Z5->setText(Low_Z5);
        ui->lineEdit_LevelsName_L5->setText(LevelsName_L5);

        ui->lineEdit_North_L6->setText(North_L6);
        ui->lineEdit_West_L6->setText(West_L6);
        ui->lineEdit_East_L6->setText(East_L6);
        ui->lineEdit_South_L6->setText(South_L6);
        ui->lineEdit_High_Z6->setText(High_Z6);
        ui->lineEdit_Low_Z6->setText(Low_Z6);
        ui->lineEdit_LevelsName_L6->setText(LevelsName_L6);

        ui->lineEdit_North_L7->setText(North_L7);
        ui->lineEdit_West_L7->setText(West_L7);
        ui->lineEdit_East_L7->setText(East_L7);
        ui->lineEdit_South_L7->setText(South_L7);
        ui->lineEdit_High_Z7->setText(High_Z7);
        ui->lineEdit_Low_Z7->setText(Low_Z7);
        ui->lineEdit_LevelsName_L7->setText(LevelsName_L7);

        ui->lineEdit_North_GZ->setText(North_GZ);
        ui->lineEdit_West_GZ->setText(West_GZ);
        ui->lineEdit_East_GZ->setText(East_GZ);
        ui->lineEdit_South_GZ->setText(South_GZ);

        ui->lineEdit_Ground_Zero_Z->setText(Ground_Zero_GZ);

        ui->lineEdit_North_GZ_2->setText(North_GZ_2);
        ui->lineEdit_West_GZ_2->setText(West_GZ_2);
        ui->lineEdit_East_GZ_2->setText(East_GZ_2);
        ui->lineEdit_South_GZ_2->setText(South_GZ_2);

        ui->lineEdit_Ground_Zero_Z_2->setText(Ground_Zero_GZ_2);
    }
}

void MainWindow::on_checkBox_15_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        packetparsing::packetvars IN_checkBox_15;
        IN_checkBox_15 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

        ui->comboBox_2->clear();

        QMap<QString,QMap<QString,QVector<QString>>> ZoneForOBJvectorsmaps = checkthezone::WorldsVectorOFObjectZonesMaps.at(IN_checkBox_15.masterworld);


        QMapIterator<QString,QMap<QString,QVector<QString>>> iter (ZoneForOBJvectorsmaps);
        while (iter.hasNext())
        {
            iter.next();

            QString ZonesName = iter.key();
            QMap<QString,QVector<QString>> OBJ_XZYsVectorMap = iter.value();

            ui->comboBox_2->addItem(ZonesName);


            QString ObjectsID = "";
            QString BuildingsName = "";

            QMapIterator<QString,QVector<QString>> iter (OBJ_XZYsVectorMap);
            while (iter.hasNext())
            {
                iter.next();

                ObjectsID = iter.key();
                QVector<QString> XZYsVector = iter.value();

                BuildingsName = XZYsVector.at(3);

                ui->comboBox_3->addItem(ObjectsID);
                ui->comboBox_4->addItem(BuildingsName);

            }
        }
    }
}




/////////////////////////////////////////////////////
//north
void MainWindow::on_pushButton_North_L1_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_L1->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_L1_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_L1->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_L1_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_L1->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_L1_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_L1->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////
//north
void MainWindow::on_pushButton_North_L2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_L2->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_L2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_L2->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_L2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_L2->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_L2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_L2->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////
//north
void MainWindow::on_pushButton_North_L3_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_L3->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_L3_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_L3->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_L3_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_L3->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_L3_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_L3->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////
//north
void MainWindow::on_pushButton_North_L4_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_L4->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_L4_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_L4->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_L4_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_L4->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_L4_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_L4->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////
//north
void MainWindow::on_pushButton_North_L5_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_L5->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_L5_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_L5->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_L5_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_L5->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_L5_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_L5->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////
//north
void MainWindow::on_pushButton_North_L6_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_L6->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_L6_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_L6->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_L6_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_L6->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_L6_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_L6->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////
//north
void MainWindow::on_pushButton_North_L7_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_L7->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_L7_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_L7->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_L7_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_L7->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_L7_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_L7->setText(QString::number(Objx2));
}

void MainWindow::on_pushButton_Ground_Zero_Z_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterz; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    if(Objx2 > 130000)
    {
        Objx2 = Objx2 - 131072.00195193;
    }

    ui->lineEdit_Ground_Zero_Z->setText(QString::number(Objx2));
}

void MainWindow::on_pushButton_Ground_Zero_Z_2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterz; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;
    if(Objx2 > 130000)
    {
        Objx2 = Objx2 - 131072.00195193;
    }

    ui->lineEdit_Ground_Zero_Z_2->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////////////////////

//north
void MainWindow::on_pushButton_North_GZ_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_GZ->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_GZ_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_GZ->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_GZ_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_GZ->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_GZ_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_GZ->setText(QString::number(Objx2));
}

/////////////////////////////////////////////////////////////////////

//north
void MainWindow::on_pushButton_North_GZ_2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_North_GZ_2->setText(QString::number(Objx2));
}

//west
void MainWindow::on_pushButton_West_GZ_2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_West_GZ_2->setText(QString::number(Objx2));
}

//east
void MainWindow::on_pushButton_East_GZ_2_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.masterx; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_East_GZ_2->setText(QString::number(Objx2));
}

//south
void MainWindow::on_pushButton_South_GZ_2_clicked()
{    
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray  Objx1 = IN_pushButton.mastery; //send as 3 byte hex
    int Objxfromhex1 = Objx1.toInt(nullptr,16);
    float Objx2 = Objxfromhex1 / 128.0;

    ui->lineEdit_South_GZ_2->setText(QString::number(Objx2));
}

void MainWindow::on_pushButton_29_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    if(IN_pushButton.Target_ID != IN_pushButton.CharSelectID_Main)
    {
        QString Current_channel = IN_pushButton.Map_Channel_ID.key(IN_pushButton.Target_ID);

        QByteArray holderXorC9 = "01c9xxxx01100180c800";

        holderXorC9.replace(0,2,Current_channel.toUtf8().toUpper());

        //qDebug() << "MapOfChannelVectors18" << MapOfChannelVectors;

        QByteArray Channel = holderXorC9.mid(0,2);
        QVector <QByteArray> CurrenChannelVector = IN_pushButton.MapOfChannelVectors.value(Channel);
        CurrenChannelVector.append(holderXorC9);
        IN_pushButton.MapOfChannelVectors.insert(Channel,CurrenChannelVector);

        //qDebug() << "MapOfChannelVectors18" << MapOfChannelVectors;


        objectpacket::DeadListVector.append(IN_pushButton.Target_ID);

        IN_pushButton.channelmap.insert(Current_channel,"free");

        QTimer *SpawningTimers  = new QTimer(this);
        SpawningTimers->setInterval(10);
        SpawningTimers->setSingleShot(true);
        SpawningTimers->setObjectName(IN_pushButton.Target_ID);
        reSpawningTimersVector.append(SpawningTimers);
        SpawningTimers->start();

        connect(SpawningTimers ,SIGNAL (timeout()),this,SLOT(on_RespawnMob()));
    }
}

void MainWindow::on_RespawnMob()
{
    packetparsing::packetvars IN_RespawnMob;
    IN_RespawnMob = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    auto* RespawningMob = qobject_cast<QTimer*>(sender());
    QString RespawnID1 = RespawningMob->objectName();

    if(reSpawningTimersVector.contains(RespawningMob))
    {
        reSpawningTimersVector.removeOne(RespawningMob);
        RespawningMob->deleteLater();
    }

    QByteArray split1 = RespawnID.toUtf8();

    QByteArray first_4_digits = split1.mid(0,4);
    QByteArray last_4_digits = split1.mid(4,4);

    increment first1;
    QByteArray firstresult1 = first1.count(first_4_digits).toUpper();

    if(firstresult1 == "0000")
    {
        first_4_digits = "0000";

        increment second1; //get class object
        QByteArray secondresult1 = second1.count(last_4_digits).toUpper();
        RespawnID = firstresult1.toUpper() + secondresult1.toUpper();
    }

    else
    {
        RespawnID = firstresult1.toUpper() + last_4_digits.toUpper();
    }

    QByteArray NewMobC9 = "";



    int index = EndingIDXZYF.indexOf(RespawnID1);

    QString StartingID = StartingIDXZYF.at(index);

    QString EndingID = EndingIDXZYF.at(index);

    reSpawnIDsMap.insert(RespawnID,StartingID);

    if(reSpawnIDsMap.contains(RespawnID1))
    {
        reSpawnIDsMap.remove(RespawnID1);
    }

    EndingIDXZYF.replace(index,RespawnID);

    NewMobC9 = objectpacket::Master_Map.value(EndingID.toUtf8());


    NewMobC9.replace(2,8,RespawnID.toUtf8());

    objectpacket::Master_Map.remove(EndingID.toUtf8());
    objectpacket::Master_Map.insert(RespawnID.toUtf8(),NewMobC9);



    int index2 = IN_RespawnMob.holdid2.indexOf(RespawnID1);

    if(index2 != -1)
    {
        IN_RespawnMob.holdid2.replace(index2,RespawnID);
    }
    else
    {
        IN_RespawnMob.holdid2.append(RespawnID);
    }

    int index1 = objectpacket::DeadListVector.indexOf(RespawnID1);

    if(index1 != -1)
    {
        objectpacket::DeadListVector.removeAt(index1);
    }
}






void MainWindow::on_pushButton_138_clicked()
{
    if(ui->checkBox_20->isChecked() == false)
    {
        ui->lineEdit->setText("192.168.001.112");
    }

    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(false);

    QString ip2 = ui->lineEdit->text(); //get ip from ui
    bool getit =  mainip.setAddress(ip2); //set ip address in hostadress

    if(getit == false)
    {
        QMessageBox msgBox3; //something bad happened
        msgBox3.setText("Please Enter IP");
        msgBox3.exec();
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setDisabled(true);
        ui->lineEdit->setDisabled(false);
        return;
    }
    else
    {



        //maploading

        QThread::currentThread()->setObjectName("Main_Thread");
        qDebug() << "MainWindow" << QThread::currentThread();




        connect(test->watcher,SIGNAL(progressValueChanged(int)),this,SLOT(mapprogress(int)));
        test->MapStart();




    }


    /////UI//////
    ui->actionAbout_Hagley2->setDisabled(true);
    ui->actionLoad_Database->setDisabled(true);
    ui->lineEdit->setDisabled(true);

    ui->pushButton_2->setDisabled(false);
    ui->pushButton->setDisabled(true);
    ui->pushButton_138->setDisabled(true);
    ui->textEdit_5->append("Started UDP Server...");
    ui->textEdit_5->append("Started TCP Server...");
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_17->clear();



}





void MainWindow::on_checkBox_13_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        CheckTheAggro = "NO";
    }
    else
    {
        CheckTheAggro = "YES";
    }
}


void MainWindow::StopAllMovement()
{
    auto* StopAllMovementsTimer = qobject_cast<QTimer*>(sender());
    QString  ObjectID = StopAllMovementsTimer->objectName();

    if(StopAllMovementsTimersVector.contains(StopAllMovementsTimer))
    {
        StopAllMovementsTimersVector.removeOne(StopAllMovementsTimer);
    }

    StopAllMovementsTimer->deleteLater();

    if(StopMovementVector.isEmpty() == false)
    {
        int index = StopMovementVector.indexOf(ObjectID);

        if(index != -1)
        {
            StopMovementVector.remove(index);
        }
    }
}

void MainWindow::on_pushButton_141_clicked()
{
    ui->graphicsView_2->resetTransform();
}

void MainWindow::on_pushButton_145_clicked()
{
    ui->graphicsView_2->scale(2,2);
}

void MainWindow::on_pushButton_142_clicked()
{
    ui->graphicsView_2->scale(3,3);
}

void MainWindow::on_pushButton_143_clicked()
{
    ui->graphicsView_2->scale(0.50,0.50);
}

void MainWindow::on_pushButton_147_clicked()
{
    ui->graphicsView_2->scale(0.99,0.99);
}

void MainWindow::on_pushButton_146_clicked()
{
    ui->graphicsView_2->scale(1/0.99,1/0.99);
}

void MainWindow::on_pushButton_149_clicked()
{
    QString largestring2 = ui->textEdit_23->toPlainText().toUpper();

    QStringList PageList = largestring2.split("\n");

    db.transaction();
    int packetid = 0;

    QString TableName = "HOTKEYS";
    QSqlQuery query2;
    query2.prepare(QString("SELECT COUNT (*) FROM %1").arg(TableName));
    query2.exec();

    while (query2.next())
    {
        packetid =  query2.value(0).toInt(nullptr);
    }

    packetid++;

    QString Column_Name = "PacketID";
    query2.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(TableName).arg(Column_Name));
    query2.bindValue(":id",packetid);
    query2.exec();

    if(!query2.exec())
    {
        ui->lineEdit_20->setText("PacketID " + query2.lastError().text());
        return;
    }

    QString Column_value = "01012000";

    Column_Name = "ObjectID (4)";
    query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
    query2.bindValue(":val",Column_value);
    query2.bindValue(":id",packetid);
    query2.exec();

    if(!query2.exec())
    {
        ui->lineEdit_20->setText("ObjectID " + query2.lastError().text());
        return;
    }

    for(int ld = 0; ld < PageList.size(); ld+=5)
    {
        QString ID = PageList.at(ld).toUpper();
        QString Button_00 = PageList.at(ld+1).toUpper();
        QString Button_02 = PageList.at(ld+2).toUpper();
        QString Button_04 = PageList.at(ld+3).toUpper();
        QString Button_06 = PageList.at(ld+4).toUpper();

        Column_Name = "ID_" + ID;
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",ID);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText("ID_" + ID + " " + query2.lastError().text());
            return;
        }

        Column_Name = ID + "_00";
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",Button_00);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText(ID + "00 " + query2.lastError().text());
            return;
        }

        Column_Name = ID + "_02";
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",Button_02);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText(ID + "02 " + query2.lastError().text());
            return;
        }

        Column_Name = ID + "_04";
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",Button_04);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText(ID + "04 " + query2.lastError().text());
            return;
        }

        Column_Name = ID + "_06";
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",Button_06);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText(ID + "06 " + query2.lastError().text());
            return;
        }
    }

    db.commit();

    ui->textEdit_23->clear();
}

void MainWindow::on_pushButton_150_clicked()
{


    db.transaction();
    int packetid = 0;

    QString TableName = "PLAYER_SPELLS";
    QSqlQuery query2;
    query2.prepare(QString("SELECT COUNT (*) FROM %1").arg(TableName));
    query2.exec();

    while (query2.next())
    {
        packetid =  query2.value(0).toInt(nullptr);
    }

    packetid++;

    QString Column_Name = "PacketID";
    query2.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(TableName).arg(Column_Name));
    query2.bindValue(":id",packetid);
    query2.exec();

    if(!query2.exec())
    {
        ui->lineEdit_20->setText("PacketID " + query2.lastError().text());
        return;
    }

    QString Column_value = "01012000";

    Column_Name = "ObjectID (4)";
    query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
    query2.bindValue(":val",Column_value);
    query2.bindValue(":id",packetid);
    query2.exec();

    if(!query2.exec())
    {
        ui->lineEdit_20->setText("ObjectID " + query2.lastError().text());
        return;
    }

    for(int i = 0; i < SpellSlotsVector.size(); i++)
    {
        QString Slot = SpellSlotsVector.at(i);
        QString ID = SpellIDsVector.at(i).toUpper();
        QString HB_Values = HB_ValuesVector.at(i);
        QString Is_It_On_HB = HB_Values.mid(0,2);
        QString HB_Location = HB_Values.mid(2,2);
        QString Show_Hide = "02";



        Column_Name = "SlotID_" + Slot;
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",ID);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText("ID_" + ID + " " + query2.lastError().text());
            return;
        }

        Column_Name = "Is_It_On_HB_" + Slot;
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",Is_It_On_HB);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText("Is_It_On_HB_" + Slot + " " + query2.lastError().text());
            return;
        }

        Column_Name = "HB_Location_" + Slot;
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",HB_Location);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText("HB_Location_" + Slot + " " + query2.lastError().text());
            return;
        }

        Column_Name = "Show_Hide_" + Slot;
        query2.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(TableName).arg(Column_Name));
        query2.bindValue(":val",Show_Hide);
        query2.bindValue(":id",packetid);
        query2.exec();

        if(!query2.exec())
        {
            ui->lineEdit_20->setText("Show_Hide_" + Slot + " " + query2.lastError().text());
            return;
        }


    }

    db.commit();

}

void MainWindow::on_pushButton_151_clicked()
{

    for(int count = 0; count < 100; count++)
    {
        QString Slot = QString("%1").arg(count,1,10,QLatin1Char('0')).toUpper();

        Convert Send;
        QString Slot2 = Send.ConvertTo(Slot).toUpper();

        ui->textEdit_23->append("SlotID_"+ Slot2 + " BLOB,");
        ui->textEdit_23->append("Is_It_On_HB_"+ Slot2 + " BLOB,");
        ui->textEdit_23->append("HB_Location_"+ Slot2 + " BLOB,");
        ui->textEdit_23->append("Show_Hide_"+ Slot2 + " BLOB,");
    }
}

void MainWindow::on_lineEdit_150_textChanged(const QString &arg1)
{
    packetparsing::packetvars IN_lineEdit_150;
    IN_lineEdit_150 = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    IN_lineEdit_150.FirstLogin = arg1.toInt(nullptr,10);

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_lineEdit_150);

}

void MainWindow::on_A_pushButton_31_clicked()
{
    ui->A_lineEdit_58->setText(Class_string.toUpper());

    ui->A_plainTextEdit_5->clear();

    QString largestring = ui->A_lineEdit_58->text().toUpper();
    QStringList mylist = largestring.split(" ");
    QString firststring = "";

    for(int i = 0; i < largestring.size(); i++)
    {
        firststring = mylist.value(i);

        QMapIterator<int,QString> iter1 (Class_Order);
        while (iter1.hasNext())
        {

            iter1.next();
            int order_key = iter1.key();
            QString Class_val = iter1.value();

            if(firststring == Class_val)
            {
                Class_Order2.insert(order_key,firststring);
            }
        }
    }

    QMapIterator<int,QString> iter2 (Class_Order2);
    while (iter2.hasNext())
    {
        iter2.next();

        QString Class_val2 = iter2.value();
        ui->A_plainTextEdit_5->appendPlainText(Class_val2);
    }

    QString largestring2 = ui->A_plainTextEdit_5->toPlainText();
    QStringList mylist2 = largestring2.split("\n");
    QString firststring2 = "";


    QString Line01 = mylist2.value(0);
    QString Line02 = mylist2.value(1);
    QString Line03 = mylist2.value(2);
    QString Line04 = mylist2.value(3);
    QString Line05 = mylist2.value(4);
    QString Line06 = mylist2.value(5);
    QString Line07 = mylist2.value(6);
    QString Line08 = mylist2.value(7);
    QString Line09 = mylist2.value(8);
    QString Line10 = mylist2.value(9);
    QString Line11 = mylist2.value(10);
    QString Line12 = mylist2.value(11);
    QString Line13 = mylist2.value(12);
    QString Line14 = mylist2.value(13);
    QString Line15 = mylist2.value(14);




    if(mylist2.size() == 1)
    {
        ui->A_lineEdit_58->setText(Line01);
    }
    if(mylist2.size() == 2)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02);
    }
    if(mylist2.size() == 3)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03);
    }
    if(mylist2.size() == 4)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04);
    }
    if(mylist2.size() == 5)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05);
    }
    if(mylist2.size() == 6)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06);
    }
    if(mylist2.size() == 7)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07
                                   );
    }
    if(mylist2.size() == 8)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08
                                   );
    }
    if(mylist2.size() == 9)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09
                                   );
    }
    if(mylist2.size() == 10)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09 + " " + Line10
                                   );
    }
    if(mylist2.size() == 11)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09 + " " + Line10 + " " + Line11
                                   );
    }
    if(mylist2.size() == 12)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09 + " " + Line10 + " " + Line11
                                   + " " + Line12
                                   );
    }
    if(mylist2.size() == 13)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09 + " " + Line10 + " " + Line11
                                   + " " + Line12 + " " + Line13
                                   );
    }
    if(mylist2.size() == 14)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09 + " " + Line10 + " " + Line11
                                   + " " + Line12 + " " + Line13 + " " + Line14
                                   );
    }
    if(mylist2.size() == 15)
    {
        ui->A_lineEdit_58->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09 + " " + Line10 + " " + Line11
                                   + " " + Line12 + " " + Line13 + " " + Line14 + " " + Line15
                                   );
    }

    Class_Order2.clear();


    QString Class_Search = ui->A_lineEdit_58->text().toUpper();


    ui->lineEdit_222->setText(Class_Search);


    on_A_pushButton_63_clicked();
}

void MainWindow::on_A_pushButton_62_clicked()
{
    ui->A_lineEdit_87->setText(Race_string);

    ui->A_plainTextEdit_5->clear();

    QString largestring = ui->A_lineEdit_87->text().toUpper();
    QStringList mylist = largestring.split(" ");
    QString firststring = "";

    for(int i = 0; i < largestring.size(); i++)
    {
        firststring = mylist.value(i);

        QMapIterator<int,QString> iter1 (Race_Order);
        while (iter1.hasNext())
        {

            iter1.next();
            int order_key = iter1.key();
            QString Race_val = iter1.value();

            if(firststring == Race_val)
            {
                Race_Order2.insert(order_key,firststring);
            }
        }
    }

    QMapIterator<int,QString> iter2 (Race_Order2);
    while (iter2.hasNext())
    {
        iter2.next();

        QString Race_val2 = iter2.value();
        ui->A_plainTextEdit_5->appendPlainText(Race_val2);
    }

    QString largestring2 = ui->A_plainTextEdit_5->toPlainText();
    QStringList mylist2 = largestring2.split("\n");
    QString firststring2 = "";


    QString Line01 = mylist2.value(0);
    QString Line02 = mylist2.value(1);
    QString Line03 = mylist2.value(2);
    QString Line04 = mylist2.value(3);
    QString Line05 = mylist2.value(4);
    QString Line06 = mylist2.value(5);
    QString Line07 = mylist2.value(6);
    QString Line08 = mylist2.value(7);
    QString Line09 = mylist2.value(8);
    QString Line10 = mylist2.value(9);




    if(mylist2.size() == 1)
    {
        ui->A_lineEdit_87->setText(Line01);
    }
    if(mylist2.size() == 2)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02);
    }
    if(mylist2.size() == 3)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03);
    }
    if(mylist2.size() == 4)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04);
    }
    if(mylist2.size() == 5)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05);
    }
    if(mylist2.size() == 6)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06);
    }
    if(mylist2.size() == 7)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07
                                   );
    }
    if(mylist2.size() == 8)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08
                                   );
    }
    if(mylist2.size() == 9)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09
                                   );
    }
    if(mylist2.size() == 10)
    {
        ui->A_lineEdit_87->setText(Line01 + " " + Line02 + " " + Line03 + " " + Line04 + " " + Line05 + " " + Line06
                                   + " " + Line07 + " " + Line08 + " " + Line09 + " " + Line10
                                   );
    }

    Race_Order2.clear();

    QString RaceString = ui->A_lineEdit_87->text();


    ui->lineEdit_223->setText(RaceString);



}

void MainWindow::on_A_pushButton_39_clicked()
{
    ui->A_lineEdit_115->setText("X");
}

void MainWindow::on_A_pushButton_40_clicked()
{
    ui->A_lineEdit_111->setText("X");
}

void MainWindow::on_A_pushButton_29_clicked()
{
    ui->A_lineEdit_110->setText("X");
}

void MainWindow::on_A_pushButton_33_clicked()
{
    ui->A_lineEdit_114->setText("X");
}

void MainWindow::on_A_pushButton_30_clicked()
{
    ui->A_lineEdit_108->setText("X");
}

void MainWindow::on_A_pushButton_23_clicked()
{
    ui->A_lineEdit_103->setText("X");
}

void MainWindow::on_A_pushButton_36_clicked()
{
    ui->A_lineEdit_112->setText("X");
}

void MainWindow::on_A_pushButton_34_clicked()
{
    ui->A_lineEdit_105->setText("X");
}

void MainWindow::on_A_pushButton_32_clicked()
{
    ui->A_lineEdit_113->setText("X");
}

void MainWindow::on_A_pushButton_35_clicked()
{
    ui->A_lineEdit_104->setText("X");
}

void MainWindow::on_A_pushButton_26_clicked()
{
    ui->A_lineEdit_107->setText("X");
}

void MainWindow::on_A_pushButton_28_clicked()
{
    ui->A_lineEdit_109->setText("X");
}

void MainWindow::on_A_pushButton_25_clicked()
{
    ui->A_lineEdit_106->setText("X");
}

void MainWindow::on_A_pushButton_48_clicked()
{
    ui->A_lineEdit_116->setText("X");
}

void MainWindow::on_A_pushButton_24_clicked()
{
    ui->A_lineEdit_102->setText("X");
}

void MainWindow::on_A_lineEdit_102_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("ALC ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_103_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("BRD ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_104_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("CL ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_105_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("DRD ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_106_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("ENC ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_107_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("MAG ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_108_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("MNK ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_109_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("NEC ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_110_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("PAL ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_111_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("RAN ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_112_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("RGE ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_113_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("SHA ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_114_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("SK ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_115_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("WAR ");
        on_A_pushButton_31_clicked();
    }
}

void MainWindow::on_A_lineEdit_116_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Class_string.append("WIZ ");
        on_A_pushButton_31_clicked();
    }
}



void MainWindow::on_A_pushButton_22_clicked()
{
    ui->A_plainTextEdit_5->clear();
    ui->A_lineEdit_58->setText("WAR RAN PAL SK MNK BRD RGE DRD SHA CL MAG NEC ENC WIZ ALC");


    ui->A_lineEdit_115->setText("X");
    ui->A_lineEdit_111->setText("X");
    ui->A_lineEdit_110->setText("X");
    ui->A_lineEdit_114->setText("X");
    ui->A_lineEdit_108->setText("X");
    ui->A_lineEdit_103->setText("X");
    ui->A_lineEdit_112->setText("X");
    ui->A_lineEdit_105->setText("X");
    ui->A_lineEdit_113->setText("X");
    ui->A_lineEdit_104->setText("X");
    ui->A_lineEdit_107->setText("X");
    ui->A_lineEdit_109->setText("X");
    ui->A_lineEdit_106->setText("X");
    ui->A_lineEdit_116->setText("X");
    ui->A_lineEdit_102->setText("X");
}

void MainWindow::on_A_pushButton_27_clicked()
{

    on_A_pushButton_56_clicked();
    ui->A_lineEdit_102->clear();
    ui->A_lineEdit_103->clear();
    ui->A_lineEdit_104->clear();
    ui->A_lineEdit_105->clear();
    ui->A_lineEdit_106->clear();
    ui->A_lineEdit_107->clear();
    ui->A_lineEdit_108->clear();
    ui->A_lineEdit_109->clear();
    ui->A_lineEdit_110->clear();
    ui->A_lineEdit_111->clear();
    ui->A_lineEdit_112->clear();
    ui->A_lineEdit_113->clear();
    ui->A_lineEdit_114->clear();
    ui->A_lineEdit_115->clear();
    ui->A_lineEdit_116->clear();
    ui->A_lineEdit_58->clear();

    Class_string.clear();



    on_A_pushButton_56_clicked();

}



void MainWindow::on_A_pushButton_63_clicked()
{
    if(tankONLY == true || priestONLY == true || meleeONLY == true || casterONLY == true)
    {


        QString ClassNames = ui->A_lineEdit_58->text().toUpper();

        if(ClassNames == "WAR PAL SK")
        {
            tankONLY = false;
        }

        if(ClassNames == "DRD SHA CL")
        {
            priestONLY = false;
        }

        if(ClassNames == "RAN MNK BRD RGE")
        {
            meleeONLY = false;
        }

        if(ClassNames == "MAG NEC ENC WIZ ALC")
        {
            casterONLY = false;
        }
    }
    else
    {

        QString ClassNames = ui->A_lineEdit_58->text().toUpper();
    }

}

void MainWindow::on_A_pushButton_64_clicked()
{
    tankONLY = true;
    on_A_pushButton_27_clicked();
    on_A_pushButton_39_clicked();
    on_A_pushButton_29_clicked();
    on_A_pushButton_33_clicked();
}

void MainWindow::on_A_pushButton_65_clicked()
{
    priestONLY = true;
    on_A_pushButton_27_clicked();
    on_A_pushButton_34_clicked();
    on_A_pushButton_32_clicked();
    on_A_pushButton_35_clicked();
}

void MainWindow::on_A_pushButton_66_clicked()
{
    meleeONLY = true;
    on_A_pushButton_27_clicked();
    on_A_pushButton_40_clicked();
    on_A_pushButton_30_clicked();
    on_A_pushButton_23_clicked();
    on_A_pushButton_36_clicked();
}

void MainWindow::on_A_pushButton_67_clicked()
{
    casterONLY = true;
    on_A_pushButton_27_clicked();
    on_A_pushButton_26_clicked();
    on_A_pushButton_28_clicked();
    on_A_pushButton_25_clicked();
    on_A_pushButton_48_clicked();
    on_A_pushButton_24_clicked();
}

void MainWindow::on_A_pushButton_60_clicked()
{
    ui->A_lineEdit_classBox1_2->setText("X");
}

void MainWindow::on_A_pushButton_50_clicked()
{
    ui->A_lineEdit_classBox2_2->setText("X");
}

void MainWindow::on_A_pushButton_52_clicked()
{
    ui->A_lineEdit_classBox3_2->setText("X");
}

void MainWindow::on_A_pushButton_58_clicked()
{
    ui->A_lineEdit_classBox4_2->setText("X");
}

void MainWindow::on_A_pushButton_51_clicked()
{
    ui->A_lineEdit_classBox5_2->setText("X");
}

void MainWindow::on_A_pushButton_61_clicked()
{
    ui->A_lineEdit_classBox6_2->setText("X");
}

void MainWindow::on_A_pushButton_57_clicked()
{
    ui->A_lineEdit_classBox7_2->setText("X");
}

void MainWindow::on_A_pushButton_55_clicked()
{
    ui->A_lineEdit_classBox8_2->setText("X");
}

void MainWindow::on_A_pushButton_49_clicked()
{
    ui->A_lineEdit_classBox9->setText("X");
}

void MainWindow::on_A_pushButton_59_clicked()
{
    ui->A_lineEdit_classBox10->setText("X");
}

void MainWindow::on_A_pushButton_56_clicked()
{

    // on_A_pushButton_27_clicked();
    ui->A_lineEdit_classBox1_2->clear();
    ui->A_lineEdit_classBox2_2->clear();
    ui->A_lineEdit_classBox3_2->clear();
    ui->A_lineEdit_classBox4_2->clear();
    ui->A_lineEdit_classBox5_2->clear();
    ui->A_lineEdit_classBox6_2->clear();
    ui->A_lineEdit_classBox7_2->clear();
    ui->A_lineEdit_classBox8_2->clear();
    ui->A_lineEdit_classBox9->clear();
    ui->A_lineEdit_classBox10->clear();
    ui->A_lineEdit_87->clear();

    Race_string.clear();

}

void MainWindow::on_A_pushButton_53_clicked()
{
    ui->A_plainTextEdit_5->clear();
    ui->A_lineEdit_87->setText("HUM ELF DELF GNO DWF TRL BAR HLF ERU OGR");

    ui->A_lineEdit_classBox1_2->setText("X");
    ui->A_lineEdit_classBox2_2->setText("X");
    ui->A_lineEdit_classBox3_2->setText("X");
    ui->A_lineEdit_classBox4_2->setText("X");
    ui->A_lineEdit_classBox5_2->setText("X");
    ui->A_lineEdit_classBox6_2->setText("X");
    ui->A_lineEdit_classBox7_2->setText("X");
    ui->A_lineEdit_classBox8_2->setText("X");
    ui->A_lineEdit_classBox9->setText("X");
    ui->A_lineEdit_classBox10->setText("X");
}

void MainWindow::on_A_lineEdit_classBox1_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("HUM ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox2_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("ELF ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox3_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("DELF ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox4_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("GNO ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox5_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("DWF ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox6_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("TRL ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox7_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("BAR ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox8_2_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("HLF ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox9_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("ERU ");
        on_A_pushButton_62_clicked();
    }
}

void MainWindow::on_A_lineEdit_classBox10_textChanged(const QString &arg1)
{
    if(arg1 == "X" || arg1 == "x")
    {
        Race_string.append("OGR ");
        on_A_pushButton_62_clicked();
    }
}


void MainWindow::on_lineEdit_206_textChanged(const QString &arg1)
{
    QString NPCS_Names = arg1;

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Name (24 Max)] LIKE '%"+NPCS_Names+"%'"));
    model1->setFilter(QString("[Name (24 Max)] LIKE '%"+NPCS_Names+"%'"));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();
    ui->A_tableView_5->setModel(model1);



    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->A_tableView_5->setModel(model1);
        ui->A_tableView_5->setColumnWidth(1,300);
    }


}

void MainWindow::on_A_tableView_5_clicked(const QModelIndex &index)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QString val1 = ui->A_tableView_5->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Packet (8)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"'"));

    ui->lineEdit_151->setText(val1);

    if(query1.exec())
    {
        while(query1.next())
        {
            ui->lineEdit_206->setText(query1.value(1).toString());

            QString NPCsName = query1.value(1).toString();
            QString ZonesName = Quests::NPCsName_ZoneMap.value(NPCsName);

            ui->lineEdit_221->setText(ZonesName);

            ui->lineEdit_207->setText(query1.value(5).toString());
        }
    }

    model1->setTable("NPCS");
    model1->select();
    ui->tableView_5->setModel(model1);
}

void MainWindow::on_lineEdit_224_textChanged(const QString &arg1)
{
    int arg2 = arg1.toInt(nullptr,10);
    QString arg3 = QString("%1").arg(arg2,2,16,QLatin1Char('0')).toUpper();

    ui->lineEdit_225->setText(arg3);
}

void MainWindow::on_pushButton_109_clicked()
{

    QString largestring = ui->plainTextEdit_3->toPlainText();

    QStringList MyList = largestring.split("\n");

    db.transaction();

    for(int i = 0; i < MyList.size(); i++)
    {
        QString Text = MyList.at(i);

        if(Text.isEmpty() == false)
        {
            if(!All_Text.contains(Text))
            {
                All_Text.append(Text);

                db.transaction();

                Table_Name = "QUEST_TEXT";
                Column_Name = "PacketID";
                QSqlQuery query;
                query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
                query.bindValue(":id",Quests::PacketID_Text);
                query.exec();

                Column_Name = "Text_ID";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Quests::Text_ID);
                query.bindValue(":id",Quests::PacketID_Text);
                query.exec();

                Column_Name = "Text";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Text);
                query.bindValue(":id",Quests::PacketID_Text);
                query.exec();




                db.commit();

                increment send;

                QByteArray Byte1 = Quests::Text_ID.mid(0,4).toUtf8();
                QByteArray Byte2 = Quests::Text_ID.mid(4,4).toUtf8();

                Quests::Text_ID = send.count(Byte1);
                Quests::Text_ID.append(Byte2);

                Quests::PacketID_Text++;

                ui->lineEdit_226->setText(Quests::Text_ID);
                ui->lineEdit_220->setText(Quests::Text_ID);
            }
        }
    }


    db.commit();






}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();


    QString val1 = ui->tableView->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [PacketID] = '"+val1+"' or [Text_ID] = '"+val1+"' or [Text] = '"+val1+"'"));


    if(query1.exec())
    {
        while(query1.next())
        {
            ui->lineEdit_163->setText(query1.value(1).toString());
            ui->lineEdit_164->setText(query1.value(2).toString());
        }
    }

    model6->setTable("QUEST_TEXT");
    model6->select();
    ui->tableView_2->setModel(model6);
}

void MainWindow::on_lineEdit_151_textChanged(const QString &arg1)
{
    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_2->setModel(model6);

}

void MainWindow::on_pushButton_96_clicked()
{


    Table_Name = "QUESTGIVERS_IDS";
    Column_Name = "PacketID";
    QString Name = ui->lineEdit_206->text();
    QSqlQuery query;
    int PacketIDq = 0;

    ui->textEdit_24->append("Name = " + Name);

    ui->textEdit_24->append("Quest_Givers_PacketID = " + QString::number(Quests::Quest_Givers_PacketID));

    if(!Quests::QuestGiversNames_IDS_Map.contains(Name))
    {
        ui->textEdit_24->append("Did not contain NPC " + Name);

        Quests::QuestGiversNames_IDS_Map.insert(Name,Quests::Quest_Givers_PacketID);

        PacketIDq = Quests::Quest_Givers_PacketID;

        query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
        query.bindValue(":id",PacketIDq);
        query.exec();

        db.transaction();

        Column_Name = "NPCs_Name";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Name);
        query.bindValue(":id",PacketIDq);
        query.exec();

        QString NPCsID = ui->lineEdit_207->text().toUpper();

        Column_Name = "NPCs_ID";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",NPCsID);
        query.bindValue(":id",PacketIDq);
        query.exec();

        db.commit();


        Quests::Quest_Givers_PacketID++;
        ui->lineEdit_239->setText(QString::number(Quests::Quest_Givers_PacketID));

    }
    else
    {
        ui->textEdit_24->append("Does contain NPC " + Name);

        PacketIDq = Quests::QuestGiversNames_IDS_Map.value(Name);

        ui->lineEdit_239->setText(QString::number(PacketIDq));

    }


    ui->textEdit_24->append("PacketIDq = " + QString::number(PacketIDq));


    db.transaction();

    QSqlQuery  query3 (QString("SELECT * FROM %1 WHERE rowid = %2").arg(Table_Name).arg(PacketIDq));

    QVector <QString> TempVect;

    while(query3.next())
    {
        QSqlRecord record = query3.record();

        for(int b = 3; b < record.count(); b++)
        {
            QString Value = record.value(b).toString();

            if(Value.isEmpty() == false)
            {
                ui->textEdit_24->append("Value = " + Value);

                TempVect.append(record.value(b).toString());
            }
            else
            {
                ui->textEdit_24->append("Value = End of list.");

                break;
            }
        }
    }

    db.commit();

    QString TempVect_Size = QString("%1").arg((TempVect.size()/7),2,10,QLatin1Char('0')).toUpper();

    ui->textEdit_24->append("");



    db.transaction();

    QSqlQuery queryQr ("SELECT COUNT (*) FROM QUEST_ID_RESULTS");

    while(queryQr.next())
    {
        Quests::PacketID_Quests = queryQr.value(0).toInt();
    }
    qDebug() << "Quests::PacketID_Questsx1" << Quests::PacketID_Quests;



    QString Table_Name1 = "QUEST_ID_RESULTS";

    QSqlQuery  queryq (QString("SELECT * FROM %1 WHERE rowid = %2").arg(Table_Name1).arg(Quests::PacketID_Quests));

    while(queryq.next())
    {
        Quests::QuestsID = queryq.value(1).toString();
    }

    qDebug() << "Quests::QuestsIDx1" << Quests::QuestsID;

    if(Quests::QuestsID.isEmpty() == true)
    {
        Quests::QuestsID = "Q_00000000";
    }

    Quests::QuestsID.remove(0,2);

    QString First4 = Quests::QuestsID.mid(0,4);
    QString Last4 = Quests::QuestsID.mid(4,4);

    QString both = "";

    if(First4 == "FFFF")
    {
        First4 = "0000";

        increment sendto;
        both = sendto.count(Last4.toUtf8());
        both.insert(0,First4);//00000100
    }
    else
    {
        increment sendto;
        both = sendto.count(First4.toUtf8());
        both.append(Last4);
    }

    Quests::PacketID_Quests++;

    qDebug() << "Quests::PacketID_Questsx2" << Quests::PacketID_Quests;

    Quests::QuestsID = "Q_" + both;

    qDebug() << "Quests::QuestsIDx2" << Quests::QuestsID;


    Column_Name = "Quest_ID_" + TempVect_Size;

    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Quests::QuestsID);
    query.bindValue(":id",PacketIDq);
    query.exec();

    QString Description = ui->lineEdit_227->text();

    ui->textEdit_24->append("Description = " + Description);

    Column_Name = "Description_" + TempVect_Size;
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Description);
    query.bindValue(":id",PacketIDq);
    query.exec();

    QString StartingCity = ui->lineEdit_221->text();

    ui->textEdit_24->append("StartingCity = " + StartingCity);

    Column_Name = "Starting_City_" + TempVect_Size;
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",StartingCity);
    query.bindValue(":id",PacketIDq);
    query.exec();

    Column_Name = "Faction_" + TempVect_Size;
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",200);
    query.bindValue(":id",PacketIDq);
    query.exec();

    QString Race = ui->lineEdit_223->text();

    ui->textEdit_24->append("Race = " + Race);

    Column_Name = "Race_" + TempVect_Size;
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Race);
    query.bindValue(":id",PacketIDq);
    query.exec();

    QString Class = ui->lineEdit_222->text();

    ui->textEdit_24->append("Class = " + Class);

    Column_Name = "Class_" + TempVect_Size;
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Class);
    query.bindValue(":id",PacketIDq);
    query.exec();

    QString Level = ui->lineEdit_225->text();

    ui->textEdit_24->append("Level = " + Level);

    Column_Name = "Level_" + TempVect_Size;
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Level);
    query.bindValue(":id",PacketIDq);
    query.exec();

    //------------------------------------------------------------------------------------//



    Table_Name1 = "QUEST_ID_RESULTS";
    Column_Name = "PacketID";

    qDebug() << "Quests::PacketID_Questsx3" << Quests::PacketID_Quests;

    query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name1).arg(Column_Name));
    query.bindValue(":id",Quests::PacketID_Quests);
    query.exec();

    Column_Name = "QuestID";

    qDebug() << "Quests::QuestsIDx3" << Quests::QuestsID;

    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name1).arg(Column_Name));
    query.bindValue(":val",Quests::QuestsID);
    query.bindValue(":id",Quests::PacketID_Quests);
    query.exec();

    Column_Name = "Description";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name1).arg(Column_Name));
    query.bindValue(":val",Description);
    query.bindValue(":id",Quests::PacketID_Quests);
    query.exec();



    db.commit();

    increment send;



    Quests::PacketID_Quests++;


    ui->textEdit_24->append("");

    db.commit();
}









void MainWindow::on_pushButton_155_clicked()
{
    ui->textEdit_25->clear();

    QString largestring = ui->textEdit_Chat->toPlainText();


    QStringList NPC_List;


    if(largestring.isEmpty() == false)
    {
        NPC_List = largestring.split("\n");

        for(int i = 0; i < NPC_List.size(); i++)
        {

            QString Line = NPC_List.at(i);

            int index = Line.indexOf("#$#");
            if(index != -1)
            {

                QString Name = Line.mid(0,index);
                QString Text = Line.mid(index+3,-1);

                Text.insert(0,Name + ": ");

                if(Text.size() > 220)
                {
                    ui->textEdit_25->append(Name);
                    ui->textEdit_25->append(Text);
                    ui->textEdit_25->append("");
                }

                QVector<QString> tempvect;

                //qDebug() << "";

                //qDebug() << "Name" << Name;
                QString NPCsID = checkthezone::NPCsNames.key(Name);
                //qDebug() << "NPCsID" << NPCsID;


                do
                {
                    int index = Text.indexOf("@!@");


                    //qDebug() << "index" << index;

                    if(index == -1)
                    {
                        tempvect.append(Text);

                        //qDebug() << Text;
                    }
                    else
                    {
                        if(index == 0)
                        {
                            Text.remove(0,3);
                        }

                        QString Popup1 = Text.mid(0,index);
                        tempvect.append(Popup1);
                        Text.remove(0,index);
                        //qDebug() << Popup1;

                        int index = Text.indexOf("@!@");

                        if(index != -1)
                        {
                            if(index == 0)
                            {
                                Text.remove(0,3);
                            }

                            tempvect.append(Text);
                            //qDebug() << Text;
                        }
                        else
                        {
                            tempvect.append(Text);
                            //qDebug() << Text;
                        }
                    }


                }while (Text.contains("@!@"));


                //qDebug() << "tempvect.size()" << tempvect.size();


                QVector<QString> tempvect2;

                for(int i = 0; i < tempvect.size(); i++)
                {

                    QString Text = tempvect.at(i);

                    QByteArray text_1 = Text.toUtf8();
                    QByteArray textascii2 = text_1.toHex();
                    QByteArray textascii = textascii2;


                    for (int cc = 0; cc < textascii2.size() * 2; cc+=2)
                    {
                        textascii.insert(cc + 2,"00");
                        cc += 2;
                    }

                    int mysize = textascii.size() / 4;
                    QString sizeout3 = QString("%1").arg(mysize,8,16,QLatin1Char('0')).toUpper();

                    QByteArray switch_it = sizeout3.toUtf8();
                    QByteArray First_Byte  = switch_it.mid(0,2);
                    QByteArray Second_Byte = switch_it.mid(2,2);
                    QByteArray Third_Byte  = switch_it.mid(4,2);
                    QByteArray Fourth_Byte = switch_it.mid(6,2);

                    QByteArray Text_Size_rev = Fourth_Byte + Third_Byte + Second_Byte + First_Byte;


                    Text = Text_Size_rev + textascii;

                    tempvect2.append(Text);

                    //qDebug() << "Utext" << Text;

                }


                NPCsID_DialogVectorMap.insert(NPCsID,tempvect2);
            }

        }

        //checkthezone::NPCsNames
        //        increment outto1;
        //         QByteArray BackFrom1 = outto1.count(IncThis);
        //         IncThis = BackFrom1;

        //         ui->lineEdit_149->setText(IncThis + "0000");

        //         FB_Out = Opcode + IncThis + "0000" + Text;

    }

    ui->lineEdit_161->setText("Finished");



}

void MainWindow::on_lineEdit_162_textChanged(const QString &arg1)
{
    ui->lineEdit_231->setText(arg1);

    if(ui->tabWidget_14->currentIndex() != 0)
    {
        ui->tabWidget_14->setCurrentIndex(0);
    }

    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == false)
    {
        ui->pushButton_172->setDisabled(false);
        ui->pushButton_191->setDisabled(false);

        if(ui->checkBox_25->isChecked() == false)
        {
            ui->checkBox_25->setChecked(true);
        }

    }
    else
    {
        ui->pushButton_172->setDisabled(true);
        ui->pushButton_191->setDisabled(true);

        if(ui->checkBox_25->isChecked() == true)
        {
            ui->checkBox_25->setChecked(false);
        }

        if(ui->checkBox_22->isChecked() == true)
        {
            ui->checkBox_22->setChecked(false);
        }

        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}

void MainWindow::on_lineEdit_230_textChanged(const QString &arg1)
{
    ui->lineEdit_232->setText(arg1);

    if(ui->tabWidget_14->currentIndex() != 1)
    {
        ui->tabWidget_14->setCurrentIndex(1);
    }

    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == false)
    {
        ui->pushButton_165->setDisabled(false);
        ui->pushButton_173->setDisabled(false);
        ui->pushButton_156->setDisabled(false);

        if(ui->checkBox_26->isChecked() == false)
        {
            ui->checkBox_26->setChecked(true);
        }
    }
    else
    {
        ui->pushButton_165->setDisabled(true);
        ui->pushButton_173->setDisabled(true);
        ui->pushButton_156->setDisabled(true);

        if(ui->checkBox_26->isChecked() == true)
        {
            ui->checkBox_26->setChecked(false);
        }

        if(ui->checkBox_23->isChecked() == true)
        {
            ui->checkBox_23->setChecked(false);
        }

        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}




void MainWindow::on_lineEdit_233_textChanged(const QString &arg1)
{
    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == true)
    {
        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }


}

void MainWindow::on_lineEdit_234_textChanged(const QString &arg1)
{
    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == true)
    {
        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}


void MainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    QString val1 = ui->tableView_3->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [PacketID] = '"+val1+"' or [Text_ID] = '"+val1+"' or [Text] = '"+val1+"'"));


    if(query1.exec())
    {
        while(query1.next())
        {

            Current_Text_ID = query1.value(1).toString();
            DB_Text = query1.value(2).toString();

            if(ui->checkBox_26->isChecked() == true)
            {
                ui->lineEdit_230->setText(DB_Text);
            }

            if(ui->checkBox_25->isChecked() == true)
            {
                ui->lineEdit_162->setText(DB_Text);
            }

            if(ui->checkBox_27->isChecked() == true)
            {
                ui->lineEdit_236->setText(DB_Text);
            }

            if(ui->checkBox_53->isChecked() == true)
            {
                ui->textEdit_30->setText(DB_Text);
                ui->lineEdit_201->setText(DB_Text);

                ui->lineEdit_272->setText(Current_Text_ID);
            }

            if(ui->checkBox_55->isChecked() == true)
            {
                ui->lineEdit_202->setText(DB_Text);

                ui->lineEdit_272->setText(Current_Text_ID);
            }
        }
    }
}





void MainWindow::on_pushButton_158_clicked()
{
    QString MerchantsName = ui->lineEdit_347->text();
    ui->lineEdit_205->setText(MerchantsName + " has been cleared.");

    ui->lineEdit_347->clear();
    ui->lineEdit_108->clear();
    ui->lineEdit_59->clear();
    ui->lineEdit_137->clear();
    ui->lineEdit_348->clear();
    ui->textEdit_28->clear();
    ItemsIDs_ItemsNamesVector.clear();
    ui->ShoppinglistWidget1->clear();
    ui->ShoppinglistWidget2->clear();
    CopyMyList.clear();


    ui->pushButton_139->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    ui->pushButton_3->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    ui->pushButton_154->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    ui->pushButton_184->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    ui->pushButton_186->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
}



void MainWindow::on_pushButton_164_clicked()
{
    ui->lineEdit_161->clear();
    ui->lineEdit_162->clear();
    ui->lineEdit_243->clear();
    ui->lineEdit_261->clear();

    ui->lineEdit_261->setText(QString::number(Quests::PacketID_Menu));
    ui->lineEdit_243->setText(Quests::Menu_ID);
}

void MainWindow::on_pushButton_165_clicked()
{
    QString Text = ui->lineEdit_230->text();

    if(Text.isEmpty() == false)
    {
        if(!All_Text.contains(Text))
        {
            All_Text.append(Text);

            db.transaction();

            Table_Name = "QUEST_TEXT";
            Column_Name = "PacketID";
            QSqlQuery query;
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text_ID";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Quests::Text_ID);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();




            db.commit();

            increment send;

            QByteArray Byte1 = Quests::Text_ID.mid(0,4).toUtf8();
            QByteArray Byte2 = Quests::Text_ID.mid(4,4).toUtf8();

            Quests::Text_ID = send.count(Byte1);
            Quests::Text_ID.append(Byte2);

            Quests::PacketID_Text++;

            ui->lineEdit_245->setText(QString::number(Quests::PacketID_Text));
            ui->lineEdit_226->setText(Quests::Text_ID);

        }
    }
}







void MainWindow::on_pushButton_172_clicked()
{
    QString Text = ui->lineEdit_162->text();

    if(Text.isEmpty() == false)
    {
        if(!All_Text.contains(Text))
        {
            All_Text.append(Text);

            db.transaction();

            Table_Name = "QUEST_TEXT";
            Column_Name = "PacketID";
            QSqlQuery query;
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text_ID";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Quests::Text_ID);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();




            db.commit();

            increment send;

            QByteArray Byte1 = Quests::Text_ID.mid(0,4).toUtf8();
            QByteArray Byte2 = Quests::Text_ID.mid(4,4).toUtf8();

            Quests::Text_ID = send.count(Byte1);
            Quests::Text_ID.append(Byte2);

            Quests::PacketID_Text++;

            ui->lineEdit_245->setText(QString::number(Quests::PacketID_Text));
            ui->lineEdit_226->setText(Quests::Text_ID);

        }
    }
}













void MainWindow::on_pushButton_176_clicked()
{
    ui->textEdit_10->clear();

    QString ReuseID = ui->lineEdit_191->text().toUpper();


    if(!ReUseNPCsVector.contains(ReuseID))
    {
        ReUseNPCsVector.append(ReuseID);

        objectpacket::DeadListVector.append(ReuseID);

    }
    else
    {
        int index = ReUseNPCsVector.indexOf(ReuseID);
        ReUseNPCsVector.replace(index,ReuseID);
        objectpacket::DeadListVector.append(ReuseID);
    }

    for(int i = 0; i < ReUseNPCsVector.size(); i++)
    {
        QString IDsLeft = ReUseNPCsVector.at(i);

        QString MOB_Master_c9 = objectpacket::Master_Map.value(IDsLeft.toUtf8().toUpper());
        QString Name24Hex_OldVal1 = MOB_Master_c9.mid(310,48);//name

        ui->lineEdit_NPC_Name2->setText(Name24Hex_OldVal1.toUpper());//Name

        QString Name = ui->lineEdit_NPC_Name->text();

        ui->textEdit_10->append(IDsLeft + " " + Name);
    }

    ui->lineEdit_192->setText(QString::number(ReUseNPCsVector.size()));
}

void MainWindow::on_pushButton_152_clicked()
{
    //LoginStarted = "Revive";
}

void MainWindow::on_pushButton_177_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    QByteArray holdergen2 = "00c9xxxx01100180c800";

    IN_pushButton.SendZeroChannelVector.append(holdergen2);

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_pushButton);

}

void MainWindow::on_pushButton_178_clicked()
{
    packetparsing::packetvars IN_pushButton;
    IN_pushButton = packetparsing::IPandPort_AllvariablesMap.value(MastersClientsID + MastersClientsIP + MastersClientsPort);

    ui->textEdit_26->append("");

    QString MyLevel1 = ui->lineEdit_248->text();
    QString MobLevel1 = ui->lineEdit_249->text();

    QByteArray fullnpcc9h  = MobLevel1.toUtf8();
    QString npclevel1h = fullnpcc9h;
    int mob_levelh = npclevel1h.toInt(nullptr,16);

    QByteArray fullmainc9h = MyLevel1.toUtf8();
    QString mainlevel1h = fullmainc9h;
    int main_levelh = mainlevel1h.toInt(nullptr,16);

    //qDebug() << "";
    //qDebug() << "main_levelh" << main_levelh;
    //qDebug() << "mob_levelh" << mob_levelh;
    //qDebug() << "main_levelhQS" << QString::number(main_levelh);
    //qDebug() << "mob_levelhQS" << QString::number(mob_levelh);



    QByteArray fullnpcc9  = MobLevel1.toUtf8();
    QString npclevel1 = fullnpcc9;
    int mob_level = npclevel1.toInt(nullptr,10);

    QByteArray fullmainc9 = MyLevel1.toUtf8();
    QString mainlevel1 = fullmainc9;
    int main_level = mainlevel1.toInt(nullptr,10);

    //qDebug() << "main_levelD" << main_level;
    //qDebug() << "mob_levelD" << mob_level;

    int diff_a = main_level - mob_level;

    QVector<QString> tempvect;
    QString tempString = "";


    if (diff_a < 0) //Mob is Greater
    {
        diff_a = mob_level - main_level;

        if (diff_a >= 3) //red
        {
            QString redcolor = "00";
            tempvect.append(redcolor);
            tempvect.append(QString::number(diff_a));

            if(tempString.isEmpty() == true)
            {
                tempString = "No options.";
            }

            tempvect.append(tempString);
        }

        if (diff_a >= 1 && diff_a <=2) //yellow
        {
            QString yellowcolor = "01";
            tempvect.append(yellowcolor);
            tempvect.append(QString::number(diff_a));

            if(tempString.isEmpty() == true)
            {
                tempString = "No options.";
            }

            tempvect.append(tempString);
        }
    }
    else
    {
        if (diff_a == 0) //white
        {
            QString whitecolor = "02";

            tempvect.append(whitecolor);
            tempvect.append(QString::number(diff_a));

            if(tempString.isEmpty() == true)
            {
                tempString = "No options.";
            }

            tempvect.append(tempString);
        }
        else //Maintoon is Greater
        {
            if (diff_a >= 1 && diff_a <= 2)//Dark Blue
            {
                QString darkbluecolor = "03";
                tempvect.append(darkbluecolor);
                tempvect.append(QString::number(diff_a));

                if(tempString.isEmpty() == true)
                {
                    tempString = "No options.";
                }

                tempvect.append(tempString);
            }
            else
            {
                QVector<QString> possible_list;

                possible_list = Quests::light_blue_map.value(main_level); //Light Blue

                if (possible_list.contains(QString("%1").arg(diff_a,2,10,QLatin1Char('0'))))
                {
                    QString lightbluecolor = "04";
                    tempvect.append(lightbluecolor);
                    tempvect.append(QString::number(diff_a));

                    for(int i = 0; i < possible_list.size(); i++)
                    {
                        tempString.append(possible_list.at(i) + ",");
                    }

                    if(tempString.isEmpty() == true)
                    {
                        tempString = "No options.";
                    }

                    tempvect.append(tempString);
                }
                else
                {
                    QString greencolor = "05";
                    tempvect.append(greencolor);
                    tempvect.append(QString::number(diff_a));

                    for(int i = 0; i < possible_list.size(); i++)
                    {
                        tempString.append(possible_list.at(i) + ",");
                    }

                    if(tempString.isEmpty() == true)
                    {
                        tempString = "No options.";
                    }

                    tempvect.append(tempString);
                }
            }
        }
    }



    QString Diff = "";
    QString Possibles = "";

    QString ColorVal = "";

    if(tempvect.isEmpty() == false)
    {
        IN_pushButton.returnedcolor = tempvect.at(0).toUtf8();
        Diff = tempvect.at(1);
        Possibles = tempvect.at(2);

        ColorVal = ColorMap.value(IN_pushButton.returnedcolor);
    }

    ui->lineEdit_250->setText(Diff);

    if(IN_pushButton.returnedcolor == "05")
    {
        IN_pushButton.IsTargetGreen = "YES";
    }
    else
    {
        IN_pushButton.IsTargetGreen = "NO";
    }


    QString main_level1 = QString("%1").arg(main_level,2,16,QLatin1Char('0')).toUpper();
    QString mob_level1 = QString("%1").arg(mob_level,2,16,QLatin1Char('0')).toUpper();

    //qDebug() << "main_level1" << main_level1;
    //qDebug() << "mob_level1" << mob_level1;

    Combat AllValues;
    QString MobXP = AllValues.SendToXP(MastersClientsID,MastersClientsIP,MastersClientsPort,MyLevel1, MobLevel1, IN_pushButton.IsTargetGreen);

    ui->lineEdit_253->setText(MobXP);

    int MobXP1 = MobXP.toInt(nullptr,10);
    int MobXPx4 = MobXP1*4;

    ui->lineEdit_254->setText(QString::number(MobXPx4));

    ui->textEdit_26->append("MyLevel1_Dec = " + MyLevel1);
    ui->textEdit_26->append("MobLevel1_Dec = " + MobLevel1);
    ui->textEdit_26->append("main_level1_Hex = " + main_level1);
    ui->textEdit_26->append("mob_level1_Hex = " + mob_level1);
    ui->textEdit_26->append("Level Difference = " + Diff);
    ui->textEdit_26->append("Mob XP = " + MobXP);
    ui->textEdit_26->append("Mob XP x4 = " + QString::number(MobXPx4));
    ui->textEdit_26->append("Mob Color Value = " + ColorVal);
    ui->textEdit_26->append("LightB Possibles = " + Possibles);
    ui->textEdit_26->append("Is Target Green = " + IN_pushButton.IsTargetGreen);

    packetparsing::IPandPort_AllvariablesMap.insert(MastersClientsID + MastersClientsIP + MastersClientsPort,IN_pushButton);


}

void MainWindow::on_lineEdit_248_textChanged(const QString &arg1)
{
    int val = arg1.toInt(nullptr,10);

    ui->spinBox_2->setValue(val);
}

void MainWindow::on_lineEdit_249_textChanged(const QString &arg1)
{
    int val = arg1.toInt(nullptr,10);

    ui->spinBox_3->setValue(val);
}

void MainWindow::on_pushButton_179_clicked()
{
    //qDebug() << "";
    //qDebug() << "";
    //qDebug() << "";



    QMap<QString,QVector<QString>> PacketID_NameDistIDVectMap;


    QVector<QString> BlockIDvector;

    for(int i = 0; i < NPCsNameVect.size(); i ++)
    {
        QString Name1 = NPCsNameVect.at(i);
        QString PacketID1 = PacketIDVect.at(i);

        QString XYZs = XYZVect.at(i);

        QString Xval1 = XYZs.mid(0,6);
        QString Zval1 = XYZs.mid(6,6);
        QString Yval1 = XYZs.mid(12,6);

        BlockIDvector.append(PacketID1);

        for(int d = 0; d < NPCsNameVect.size(); d++)
        {
            if(i != d)
            {
                QString Name2 = NPCsNameVect.at(d);
                QString PacketID2 = PacketIDVect.at(d);
                QString XYZs = XYZVect.at(d);

                if(Name1 == Name2)
                {
                    QString Xval2 = XYZs.mid(0,6);
                    QString Zval2 = XYZs.mid(6,6);
                    QString Yval2 = XYZs.mid(12,6);

                    //Maintoon xzy
                    QByteArray  myx1 = Xval1.toUtf8(); //send as 3 byte hex
                    int xfromhex1 = myx1.toInt(nullptr,16);
                    float maintoonx1 = xfromhex1 / 128.0;

                    QByteArray  myz1 = Zval1.toUtf8();
                    int zfromhex1 = myz1.toInt(nullptr,16);
                    float maintoonz1 = zfromhex1 / 128.0;

                    if(maintoonz1 > 130000)
                    {
                        maintoonz1 = maintoonz1 - 131072.00195193;
                    }

                    QByteArray  myy1 = Yval1.toUtf8();
                    int yfromhex1 = myy1.toInt(nullptr,16);
                    float maintoony1 = yfromhex1 / 128.0;


                    //mob xzy
                    QString tempstrx = Xval2;
                    int tempint1 = tempstrx.toInt(nullptr,16);
                    float xinterlude = tempint1 / 128.0;

                    QString tempstrz = Zval2;
                    int tempint3 = tempstrz.toInt(nullptr,16);
                    float  zinterlude = tempint3 / 128.0;

                    if(zinterlude > 130000)
                    {
                        zinterlude = zinterlude - 131072.00195193;
                    }

                    QString tempstry = Yval2;
                    int tempint2 = tempstry.toInt(nullptr,16);
                    float yinterlude = tempint2 / 128.0;

                    float sub1 = maintoonx1 - xinterlude;
                    float sub2 = maintoony1 - yinterlude;
                    float sub3 = maintoonz1 - zinterlude;

                    float power1 = qPow(sub1,2);
                    float power2 = qPow(sub2,2);
                    float power3 = qPow(sub3,2);

                    float firstresult = power1 + power2 + power3;
                    float result = qSqrt(firstresult);



                    QVector<QString> Block2vect =
                    {
                        "10145","10152","10168",
                        "10278","14368","10804",
                        "2165","15616","1238",
                        "8863","14199","3183",
                        "3193","17090","17809",
                        "2975","18973","5914",
                        "5812","5998","6370",
                        "7430","7570","10277",
                        "7595"
                    };

                    float Diff = result;

                    if(Diff > 1)
                    {
                        if(!BlockIDvector.contains(PacketID2) && Name1 != "ReUseNPC" && Name2 != "ReUseNPC" && Block2vect.contains(PacketID2))
                        {
                            BlockIDvector.append(PacketID2);

                            QVector<QString> TempVect;

                            if(PacketID_NameDistIDVectMap.contains(PacketID1))
                            {
                                TempVect = PacketID_NameDistIDVectMap.value(PacketID1);

                                TempVect.append(Name2);
                                TempVect.append(QString::number(Diff));
                                TempVect.append(PacketID2);

                                PacketID_NameDistIDVectMap.insert(PacketID1,TempVect);
                            }
                            else
                            {
                                TempVect.append(Name2);
                                TempVect.append(QString::number(Diff));
                                TempVect.append(PacketID2);

                                PacketID_NameDistIDVectMap.insert(PacketID1,TempVect);
                            }


                            Table_Name = "NPCS";

                            QString ColumnName = "Packet (8)";

                            int PacketID = PacketID2.toInt(nullptr,10);

                            QSqlQuery  query;
                            QString NewName = "ReUseNPC";
                            Column_Name = "Name (24 Max)";
                            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(ColumnName));
                            query.bindValue(":val",NewName);
                            query.bindValue(":id",PacketID);
                            query.exec();

                            if(!query.exec())
                            {
                                ui->lineEdit_20->setText(query.lastError().text());
                                return;
                            }



                            QString Column_value = "52655573654E504300000000000000000000000000000000";

                            Column_Name = "Character Name (24 Max)";
                            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE [%3] = :id").arg(Table_Name).arg(Column_Name).arg(ColumnName));
                            query.bindValue(":val",Column_value);
                            query.bindValue(":id",PacketID);
                            query.exec();

                            if(!query.exec())
                            {
                                ui->lineEdit_20->setText(query.lastError().text());
                                return;
                            }
                        }
                    }
                }
            }
        }
    }


    QMapIterator<QString,QVector<QString>> Sort_Iter2 (PacketID_NameDistIDVectMap);
    while (Sort_Iter2.hasNext())
    {
        Sort_Iter2.next();
        QString PacketID = Sort_Iter2.key();
        QVector<QString> NameVector = Sort_Iter2.value();

        int index = PacketIDVect.indexOf(PacketID);

        if(index != -1)
        {
            if(NameVector.size()/3 < 4 && NameVector.size()/3 >= 1)
            {
                QString Name = NPCsNameVect.at(index);

                //qDebug() << "";
                //qDebug() << "NPCs Name" << Name << "PacketID = " + PacketID << "NameVector.size() = " << NameVector.size()/3;

                for(int i = 0; i < NameVector.size(); i+=3)
                {
                    //qDebug() << "Close NPCs Name" << NameVector.at(i) << "PacketID = " << NameVector.at(i+2) << "Distance = " << NameVector.at(i+1);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_181_clicked()
{
    //qDebug() << "";

    //qDebug() << "SessionID to ObjectID";


    QByteArray fromedit = ui->lineEdit_257->text().toUtf8(); //this needs to be input in normal order (d9bc0d)
    QByteArray session = QByteArray::fromHex(fromedit);
    QByteArray test3;
    int arraysize = session.size();
    long val = 0;
    uint shift = 0;
    uint negshift = 0;
    uint size = 32;
    uchar b;
    int position = 0;

    while (arraysize  > position)
    {
        b = session[position];
        position++;
        val |= (b & 0x7f) << shift; //binary shift left

        if (shift < size && (b & 0x40) == 0) //is value negative?
        {
            shift += 7;
            negshift += 8;
            val = 0;
            val |= (b << shift);
            long high=(val >>negshift) & 0xff; //mask and only return highbyte
            val = high;
        }

        QString Value = QString::number(val,16);

        if(Value.size() == 1)
        {
            Value = "0" + Value;
        }

        test3.append(Value.toUtf8());

        //qDebug() << "val" << val;
        //qDebug() << "Value" << Value.toUpper();


        if ((b & 0x80) == 0)
        {
            break;
        }
    }

    //qDebug() << "test3" << test3.toUpper();
    ui->lineEdit_258->setText(test3.toUpper());
}

void MainWindow::on_pushButton_180_clicked()
{
    //qDebug() << "";
    //qDebug() << "ObjectID to SessionID";


    QString CharSelectID = ui->lineEdit_255->text();

    QString byte1 = CharSelectID.mid(0,2);
    QString byte2 = CharSelectID.mid(2,2);
    QString byte3 = CharSelectID.mid(4,2);
    QString byte4 = CharSelectID.mid(6,2);

    QString CharSelectID_rev = byte4 + byte3 + byte2 + byte1;

    QByteArray objectid = CharSelectID_rev.toUtf8();

    int object1;

    object1 = objectid.toInt(nullptr,16); //this needs to be input as reversed byte order ( dudderz 035e59)

    QByteArray test2;
    QByteArray test3;

    do
    {
        //qDebug() << "object1" << object1;

        uchar lower7bits = (uchar)(object1 & 0x7f);
        object1 >>= 7;

        if (object1 > 0)

            lower7bits |= 128;
        uchar add(lower7bits);
        test2.append(add);

        //qDebug() << "add" << add;
        //qDebug() << "Val" << test2.toHex().toUpper();
        //qDebug() << "lower7bits" << lower7bits;


        test3.append(lower7bits);


    } while (object1 > 0);

    //qDebug() << "test3" << test3.toHex().toUpper();

    ui->lineEdit_256->setText(test2.toHex().toUpper());
}







void MainWindow::on_lineEdit_164_textChanged(const QString &arg1)
{
    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView->setModel(model6);

    if(arg1.isEmpty() == true)
    {
        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}





void MainWindow::on_pushButton_191_clicked()
{
    model9 = new QSqlTableModel(this);
    model9->setTable("QUEST_MENUS");
    model9->select();

    QString MenusText = "";
    QString Menu_ID = "";

    QString Next_Menu_ID = "";

    MenusText = ui->lineEdit_162->text();
    Menu_ID = ui->lineEdit_243->text();

    if(Menu_ID.isEmpty() == false && MenusText.isEmpty() == false)
    {
        Quests::Menu_ID = Menu_ID;
    }

    if(ui->checkBox_22->isChecked() == false)
    {
        if((Quests::MenuTextCheckVector.contains(MenusText) && !Quests::MenuID_MenuText_Map.contains(Quests::Menu_ID) && ui->checkBox_24->isChecked() == true) ||
                !Quests::MenuTextCheckVector.contains(MenusText))
        {
            if(MenusText.isEmpty() == false)
            {
                QSqlQuery query ("SELECT COUNT (*) FROM QUEST_MENUS");

                while(query.next())
                {
                    Quests::PacketID_Menu = query.value(0).toInt();
                }


                query.prepare (QString ("SELECT * FROM QUEST_MENUS WHERE rowid = :val"));
                query.bindValue(":val",Quests::PacketID_Menu);
                query.exec();

                while(query.next())
                {
                    Quests::Menu_ID = query.value(1).toString();
                }

                if(Quests::Menu_ID.size() < 10)
                {
                    do
                    {
                        Quests::Menu_ID.append("0");

                    }while(Quests::Menu_ID.size() < 10);
                }

                Quests::Menu_ID.remove(0,2);

                QString Byte1st_half = Quests::Menu_ID.mid(0,4);
                QString Byte2nd_half = Quests::Menu_ID.mid(4,8);

                increment sendto;

                if(Byte1st_half == "FFFF")
                {
                    Byte1st_half = "0000";
                    Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
                    Quests::Menu_ID = Byte1st_half;
                }
                else
                {
                    Quests::Menu_ID = sendto.count(Byte1st_half.toUtf8());
                    Quests::Menu_ID.append(Byte2nd_half);
                }

                Next_Menu_ID = sendto.count(Quests::Menu_ID.mid(0,4).toUtf8());
                Next_Menu_ID.append(Byte2nd_half);

                Quests::PacketID_Menu++;

                Quests::Menu_ID.insert(0,"M_");

                ui->lineEdit_261->setText(QString::number(Quests::PacketID_Menu));
                ui->lineEdit_243->setText(Quests::Menu_ID);
            }
        }
    }
    else
    {
        Quests::PacketID_Menu = ui->lineEdit_261->text().toInt(nullptr,10);
        Quests::Menu_ID = ui->lineEdit_243->text();
    }



    if((Quests::MenuTextCheckVector.contains(MenusText) && !Quests::MenuID_MenuText_Map.contains(Menu_ID) && ui->checkBox_24->isChecked() == true) ||
            !Quests::MenuTextCheckVector.contains(MenusText) || (ui->checkBox_22->isChecked() == true))
    {
        if(MenusText.isEmpty() == false)
        {
            Quests::MenuTextCheckVector.append(MenusText);
            Quests::MenuID_MenuText_Map.insert(Quests::Menu_ID,MenusText);

            db.transaction();

            QSqlQuery query;

            Table_Name = "QUEST_MENUS";

            if(ui->checkBox_22->isChecked() == false)//if you are editing the header text
            {
                Column_Name = "PacketID";

                query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
                query.bindValue(":id",Quests::PacketID_Menu);
                query.exec();

                Column_Name = "Menu_ID";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Quests::Menu_ID);
                query.bindValue(":id",Quests::PacketID_Menu);
                query.exec();

                Quests::Menu_ID = "M_" + Next_Menu_ID;
            }

            Column_Name = "Menu_Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",MenusText);
            query.bindValue(":id",Quests::PacketID_Menu);
            query.exec();

            db.commit();



            ui->checkBox_24->setChecked(false);
        }
    }

    model9->setTable("QUEST_MENUS");
    model9->select();
    ui->tableView_4->setModel(model9);
    ui->tableView_4->setColumnWidth(2,300);
}

void MainWindow::on_pushButton_173_clicked()
{
    model10 = new QSqlTableModel(this);
    model10->setTable("QUEST_MENUS_OPTIONS");
    model10->select();

    bool check = false;

    QString PacketsIDs = ui->lineEdit_261->text();
    QString MenusIDs = ui->lineEdit_243->text();

    QString Next_Options_ID = "";

    if(PacketsIDs.isEmpty() == true || MenusIDs.isEmpty() == true)
    {
        check = true;
    }

    QString Text = ui->lineEdit_230->text();

    QString OptionsIDCheck = Quests::OptionID_OptionText_Map.key(Text);

    if(check == false)
    {
        if(ui->checkBox_23->isChecked() == false)
        {
            if(!Quests::OptionID_OptionText_Map.contains(OptionsIDCheck) || ui->checkBox_31->isChecked() == true)
            {
                QSqlQuery query ("SELECT COUNT (*) FROM QUEST_MENUS_OPTIONS");

                while(query.next())
                {
                    Quests::PacketID_Menu_Option = query.value(0).toInt();
                }

                qDebug() << "Quests::PacketID_Menu_Option1 =" << Quests::PacketID_Menu_Option;

                query.prepare (QString ("SELECT * FROM QUEST_MENUS_OPTIONS WHERE rowid = :val"));
                query.bindValue(":val",Quests::PacketID_Menu_Option);
                query.exec();

                while(query.next())
                {
                    Quests::Menu_Option_ID = query.value(2).toString();
                }

                qDebug() << "Quests::Menu_Option_ID1 =" << Quests::Menu_Option_ID;

                Quests::PacketID_Menu_Option++;

                qDebug() << "Quests::PacketID_Menu_Option2 =" << Quests::PacketID_Menu_Option;

                if(Quests::Menu_Option_ID.size() < 10)
                {
                    do
                    {
                        Quests::Menu_Option_ID.append("0");

                    }while(Quests::Menu_Option_ID.size() < 10);
                }

                Quests::Menu_Option_ID.remove(0,2);

                QString Byte1st_half = Quests::Menu_Option_ID.mid(0,4);
                QString Byte2nd_half = Quests::Menu_Option_ID.mid(4,8);

                increment sendto;

                if(Byte1st_half == "FFFF")
                {
                    Byte1st_half = "0000";
                    Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
                    Quests::Menu_Option_ID = Byte1st_half;
                }
                else
                {
                    Quests::Menu_Option_ID = sendto.count(Byte1st_half.toUtf8());
                    Quests::Menu_Option_ID.append(Byte2nd_half);
                }

                Next_Options_ID = sendto.count(Quests::Menu_Option_ID.mid(0,4).toUtf8());
                Next_Options_ID.append(Byte2nd_half);

                Quests::Menu_Option_ID.insert(0,"O_");

                ui->lineEdit_233->setText(QString::number(Quests::PacketID_Menu_Option));
                ui->lineEdit_165->setText(Quests::Menu_Option_ID);

                qDebug() << "Quests::Menu_Option_ID2" << Quests::Menu_Option_ID;
            }

        }
        else
        {
            Quests::PacketID_Menu_Option = ui->lineEdit_233->text().toInt(nullptr,10);
            Quests::Menu_Option_ID = ui->lineEdit_165->text();
        }



        if(!Quests::OptionID_OptionText_Map.contains(OptionsIDCheck) || ui->checkBox_31->isChecked() == true)
        {
            if(Text.isEmpty() == false)
            {
                Quests::OptionID_OptionText_Map.insert(Quests::Menu_Option_ID,Text);

                db.transaction();

                QSqlQuery query;

                Table_Name = "QUEST_MENUS_OPTIONS";

                if(ui->checkBox_23->isChecked() == false)//if you are editing the OPTI text
                {
                    Column_Name = "PacketID";

                    query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
                    query.bindValue(":id",Quests::PacketID_Menu_Option);
                    query.exec();

                    Column_Name = "Menu_ID";

                    //qDebug() << "Column_Name_ID" << Column_Name;

                    QString MenusID = ui->lineEdit_243->text();

                    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                    query.bindValue(":val",MenusID);
                    query.bindValue(":id",Quests::PacketID_Menu_Option);
                    query.exec();

                    Column_Name = "Option_ID";
                    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                    query.bindValue(":val",Quests::Menu_Option_ID);
                    query.bindValue(":id",Quests::PacketID_Menu_Option);
                    query.exec();

                    Quests::Menu_Option_ID = "O_" + Next_Options_ID;

                }

                Column_Name = "Option_Text";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Text);
                query.bindValue(":id",Quests::PacketID_Menu_Option);
                query.exec();

                db.commit();

                ui->checkBox_31->setChecked(false);
            }
        }

        model10->setTable("QUEST_MENUS_OPTIONS");
        model10->select();
        ui->tableView_9->setModel(model10);
        ui->tableView_9->setColumnWidth(3,300);
    }
}


void MainWindow::on_lineEdit_231_textChanged(const QString &arg1)
{
    QString Text = arg1;

    ui->lineEdit_162->setText(arg1);

    model9 = new QSqlTableModel(this);
    model9->setTable("QUEST_MENUS");
    model9->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_MENUS WHERE [Menu_Text] LIKE '%"+Text+"%'"));
    model9->setFilter(QString("[Menu_Text] LIKE '%"+Text+"%'"));
    model9->setSort(2, Qt::DescendingOrder);
    model9->select();
    ui->tableView_4->setModel(model9);

    if(arg1.isEmpty() == true)
    {
        if(ui->checkBox_25->isChecked() == true)
        {
            ui->checkBox_25->setChecked(false);
        }

        model9->setTable("QUEST_MENUS");
        model9->select();
        ui->tableView_4->setModel(model9);
        ui->tableView_4->setColumnWidth(2,300);
    }
}

void MainWindow::on_lineEdit_232_textChanged(const QString &arg1)
{
    QString Text = arg1;

    ui->lineEdit_230->setText(arg1);

    model10 = new QSqlTableModel(this);
    model10->setTable("QUEST_MENUS_OPTIONS");
    model10->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_MENUS_OPTIONS WHERE [Option_Text] LIKE '%"+Text+"%'"));
    model10->setFilter(QString("[Option_Text] LIKE '%"+Text+"%'"));
    model10->setSort(2, Qt::DescendingOrder);
    model10->select();
    ui->tableView_9->setModel(model10);

    if(arg1.isEmpty() == true)
    {
        if(ui->checkBox_26->isChecked() == true)
        {
            ui->checkBox_26->setChecked(false);
        }

        model10->setTable("QUEST_MENUS_OPTIONS");
        model10->select();
        ui->tableView_9->setModel(model10);
        ui->tableView_9->setColumnWidth(3,300);
    }
}


void MainWindow::on_tableView_4_clicked(const QModelIndex &index)
{
    model9 = new QSqlTableModel(this);
    model9->setTable("QUEST_MENUS");
    model9->select();

    QString val1 = ui->tableView_4->model()->data(index).toString();
    QSqlQuery query;
    query.exec(QString("SELECT * FROM QUEST_MENUS WHERE [PacketID] = '"+val1+"'"));

    ui->textEdit_29->clear();

    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_261->setText(query.value(0).toString());
            ui->lineEdit_243->setText(query.value(1).toString());
            ui->lineEdit_231->setText(query.value(2).toString());
            ui->lineEdit_162->setText(query.value(2).toString());

            ui->lineEdit_264->setText(query.value(0).toString());
            ui->lineEdit_260->setText(query.value(1).toString());
            ui->lineEdit_278->setText(query.value(2).toString());

            ui->textEdit_29->append(query.value(1).toString());
            ui->textEdit_29->append(query.value(2).toString());

            ui->checkBox_22->setChecked(true);

            QSqlRecord record = query.record();

            for(int fd = 3; fd < record.count(); fd+=2)
            {
                QString OptionsID = record.value(fd).toString();
                QString OptionsText = record.value(fd+1).toString();

                if(OptionsID.isEmpty() == false)
                {
                    ui->textEdit_29->append(OptionsID);
                }
                else
                {
                    break;
                }
            }
        }

        if(ui->checkBox_50->isChecked() == true)
        {
            ui->tabWidget_14->setCurrentIndex(7);
            ui->tabWidget_15->setCurrentIndex(0);

            M_ids = false;
            M_text = false;
        }
    }

    model9->setTable("QUEST_MENUS");
    model9->select();
    ui->tableView_4->setModel(model9);
    ui->tableView_4->setColumnWidth(2,300);

    //----------------------------------------------------------------------------------------------
    QString LargeString = ui->textEdit_29->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ui->textEdit_29->clear();

    ui->Menu_ListWidget_1->clear();
    ui->Menu_ListWidget_2->clear();

    for(int add = 0; add < MyList.size(); add++)
    {
        QString NewLine = MyList.at(add);

        if(NewLine.isEmpty() == false)
        {
            ui->textEdit_29->append(NewLine);
            ui->Menu_ListWidget_1->addItem(NewLine);

            if(add >= 2)
            {
                QSqlQuery query1;
                query1.exec(QString("SELECT * FROM QUEST_MENUS_OPTIONS WHERE [Option_ID] = '"+NewLine+"'"));

                if(query1.exec())
                {
                    while(query1.next())
                    {
                        NewLine = query1.value(3).toString();
                    }
                }

                ui->Menu_ListWidget_2->addItem(NewLine);
            }
            else
            {
                ui->Menu_ListWidget_2->addItem(NewLine);
            }
        }
    }
}


void MainWindow::on_tableView_9_clicked(const QModelIndex &index)
{
    model10 = new QSqlTableModel(this);
    model10->setTable("QUEST_MENUS_OPTIONS");
    model10->select();

    QString val1 = ui->tableView_9->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_MENUS_OPTIONS WHERE [PacketID] = '"+val1+"'"));

    ui->textEdit_32->clear();

    if(query1.exec())
    {
        while(query1.next())
        {

            ui->lineEdit_271->setText(query1.value(0).toString());
            ui->lineEdit_267->setText(query1.value(2).toString());
            ui->lineEdit_233->setText(query1.value(0).toString());
            ui->lineEdit_165->setText(query1.value(2).toString());
            ui->lineEdit_232->setText(query1.value(3).toString());
            ui->lineEdit_230->setText(query1.value(3).toString());
            ui->lineEdit_279->setText(query1.value(3).toString());

            ui->textEdit_32->append(query1.value(1).toString());
            ui->textEdit_32->append(query1.value(2).toString());
            ui->textEdit_32->append(query1.value(3).toString());

            ui->checkBox_23->setChecked(true);

            QSqlRecord record = query1.record();

            for(int fd = 4; fd < record.count(); fd++)
            {
                QString ResultID = record.value(fd).toString();

                if(ResultID.isEmpty() == false)
                {
                    ui->textEdit_32->append(ResultID);
                }
                else
                {
                    break;
                }
            }
        }

        if(ui->checkBox_50->isChecked() == true)
        {
            ui->tabWidget_14->setCurrentIndex(7);
            ui->tabWidget_15->setCurrentIndex(1);
        }
    }


    model10->setTable("QUEST_MENUS_OPTIONS");
    model10->select();
    ui->tableView_9->setModel(model10);
    ui->tableView_9->setColumnWidth(3,300);


    //----------------------------------------------------------------------------------------------
    QString LargeString = ui->textEdit_32->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ui->textEdit_32->clear();

    ui->Option_ListWidget_1->clear();
    ui->Option_ListWidget_2->clear();

    for(int add = 0; add < MyList.size(); add++)
    {
        QString NewLine = MyList.at(add);

        if(NewLine.isEmpty() == false)
        {
            QString Table = "";
            QString Column = "";
            int value = 0;

            if(add != 2)
            {
                ui->textEdit_32->append(NewLine);
                ui->Option_ListWidget_1->addItem(NewLine);
            }

            if(add >= 2)
            {
                if(NewLine.contains("M_") || NewLine.contains("P_") || NewLine.contains("QL_"))
                {
                    if(NewLine.contains("M_"))
                    {
                        Table = "QUEST_MENUS";
                        Column = "Menu_ID";
                        value = 2;
                    }

                    if(NewLine.contains("P_"))
                    {
                        Table = "QUEST_POPUPS";
                        Column = "Popup_ID";
                        value = 2;
                    }

                    if(NewLine.contains("QL_"))
                    {
                        Table = "QUEST_LOGS";
                        Column = "Log_Text_ID";
                        value = 2;

                        NewLine.remove(0,4);
                    }

                    query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
                    query1.bindValue(":val",NewLine);
                    query1.exec();

                    if(!query1.exec())
                    {
                        qDebug() << "query1.lastError()" << query1.lastError();
                    }

                    while(query1.next())
                    {
                        NewLine = query1.value(value).toString();
                    }
                }

                //IC_98F2808000#1
                if(NewLine.contains("IC_") || NewLine.contains("IT_") || NewLine.contains("IG_"))
                {
                    NewLine = Opcodes::ItemsID_ItemsName_Map.value(NewLine.mid(3,10));
                }

                //TS_279E0D00#55B9F308
                if(NewLine.contains("TS_"))
                {
                    NewLine = checkthezone::NPCsNames.value(NewLine.mid(3,8));
                }

                ui->Option_ListWidget_2->addItem(NewLine);
            }
            else
            {
                if(add != 1)
                {
                    if(NewLine.contains("M_"))
                    {
                        Table = "QUEST_MENUS";
                        Column = "Menu_ID";
                        value = 2;

                        query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
                        query1.bindValue(":val",NewLine);
                        query1.exec();

                        if(query1.exec())
                        {
                            while(query1.next())
                            {
                                NewLine = query1.value(value).toString();
                            }
                        }
                    }

                    ui->Option_ListWidget_2->addItem(NewLine);
                }
            }
        }
    }
}


void MainWindow::on_pushButton_166_clicked()
{
    ui->lineEdit_165->clear();
    ui->lineEdit_230->clear();
    ui->lineEdit_233->clear();
    ui->lineEdit_233->setText(QString::number(Quests::PacketID_Menu_Option));
    ui->lineEdit_165->setText(Quests::Menu_Option_ID);
}

void MainWindow::on_checkBox_22_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 0)
        {
            ui->tabWidget_14->setCurrentIndex(0);
        }
    }
}

void MainWindow::on_checkBox_23_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 1)
        {
            ui->tabWidget_14->setCurrentIndex(1);
        }
    }
}

void MainWindow::on_checkBox_28_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 2)
        {
            ui->tabWidget_14->setCurrentIndex(2);
        }
    }
}



void MainWindow::on_checkBox_25_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 0)
        {
            ui->tabWidget_14->setCurrentIndex(0);
        }

        ui->checkBox_55->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_27->setChecked(false);
        ui->checkBox_53->setChecked(false);
    }
    else
    {
        ui->checkBox_24->setChecked(false);
    }
}

void MainWindow::on_checkBox_26_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 1)
        {
            ui->tabWidget_14->setCurrentIndex(1);
        }

        ui->checkBox_55->setChecked(false);
        ui->checkBox_25->setChecked(false);
        ui->checkBox_27->setChecked(false);
        ui->checkBox_53->setChecked(false);
    }
    else
    {
        ui->checkBox_31->setChecked(false);
    }
}

void MainWindow::on_checkBox_27_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 2)
        {
            ui->tabWidget_14->setCurrentIndex(2);
        }

        ui->checkBox_55->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_25->setChecked(false);
        ui->checkBox_53->setChecked(false);
    }
    else
    {
        ui->checkBox_43->setChecked(false);
    }
}




void MainWindow::on_tableView_10_clicked(const QModelIndex &index)
{
    model3 = new QSqlTableModel(this);
    model3->setTable("QUEST_POPUPS");
    model3->select();

    QString val1 = ui->tableView_10->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_POPUPS WHERE [PacketID] = '"+val1+"'"));


    ui->textEdit_33->clear();

    if(query1.exec())
    {
        while(query1.next())
        {
            ui->lineEdit_285->setText(query1.value(0).toString());
            ui->lineEdit_284->setText(query1.value(1).toString());
            ui->lineEdit_274->setText(query1.value(0).toString());
            ui->lineEdit_273->setText(query1.value(1).toString());
            ui->lineEdit_275->setText(query1.value(2).toString());
            ui->lineEdit_280->setText(query1.value(2).toString());


            ui->lineEdit_237->setText(query1.value(2).toString());
            ui->checkBox_27->setChecked(true);
            ui->checkBox_28->setChecked(true);

            ui->textEdit_33->append(query1.value(1).toString());
            ui->textEdit_33->append(query1.value(2).toString());

            QSqlRecord record = query1.record();

            for(int fd = 3; fd < record.count(); fd++)
            {
                QString ResultID = record.value(fd).toString();

                if(ResultID.isEmpty() == false)
                {
                    ui->textEdit_33->append(ResultID);
                }
                else
                {
                    break;
                }
            }

            if(ui->checkBox_49->isChecked() == false)
            {
                ui->lineEdit_235->setText(query1.value(0).toString());
                ui->lineEdit_229->setText(query1.value(1).toString());
                ui->lineEdit_236->setText(query1.value(2).toString());
            }
        }

        if(ui->checkBox_50->isChecked() == true)
        {
            ui->tabWidget_14->setCurrentIndex(7);
            ui->tabWidget_15->setCurrentIndex(2);
        }
    }


    model3->setTable("QUEST_POPUPS");
    model3->select();
    ui->tableView_10->setModel(model3);
    ui->tableView_10->setColumnWidth(2,300);

    //----------------------------------------------------------------------------------------------
    QString LargeString = ui->textEdit_33->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ui->textEdit_33->clear();

    ui->PopUp_ListWidget_1->clear();
    ui->PopUp_ListWidget_2->clear();

    for(int add = 0; add < MyList.size(); add++)
    {
        QString NewLine = MyList.at(add);

        if(NewLine.isEmpty() == false)
        {
            QString Table = "";
            QString Column = "";
            int value = 0;

            if(add != 1)
            {
                ui->textEdit_33->append(NewLine);
                ui->PopUp_ListWidget_1->addItem(NewLine);
            }

            if(add >= 1)
            {
                if(NewLine.contains("M_") || NewLine.contains("P_") || NewLine.contains("QL_"))
                {
                    if(NewLine.contains("M_"))
                    {
                        Table = "QUEST_MENUS";
                        Column = "Menu_ID";
                        value = 2;
                    }

                    if(NewLine.contains("P_"))
                    {
                        Table = "QUEST_POPUPS";
                        Column = "Popup_ID";
                        value = 2;
                    }

                    if(NewLine.contains("QL_"))
                    {
                        Table = "QUEST_LOGS";
                        Column = "Log_Text_ID";
                        value = 2;

                        NewLine.remove(0,4);
                    }

                    query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
                    query1.bindValue(":val",NewLine);
                    query1.exec();

                    if(!query1.exec())
                    {
                        qDebug() << "query1.lastError()" << query1.lastError();
                    }

                    while(query1.next())
                    {
                        NewLine = query1.value(value).toString();
                    }
                }

                //IC_98F2808000#1
                if(NewLine.contains("IC_") || NewLine.contains("IT_") || NewLine.contains("IG_"))
                {
                    NewLine = Opcodes::ItemsID_ItemsName_Map.value(NewLine.mid(3,10));
                }

                //TS_279E0D00#55B9F308
                if(NewLine.contains("TS_"))
                {
                    NewLine = checkthezone::NPCsNames.value(NewLine.mid(3,8));
                }

                ui->PopUp_ListWidget_2->addItem(NewLine);
            }
            else
            {
                if(add != 0)
                {
                    if(NewLine.contains("M_"))
                    {
                        Table = "QUEST_MENUS";
                        Column = "Menu_ID";
                        value = 2;

                        query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
                        query1.bindValue(":val",NewLine);
                        query1.exec();

                        if(query1.exec())
                        {
                            while(query1.next())
                            {
                                NewLine = query1.value(value).toString();
                            }
                        }
                    }

                    ui->PopUp_ListWidget_2->addItem(NewLine);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_168_clicked()
{
    ui->lineEdit_235->clear();
    ui->lineEdit_229->clear();
    ui->lineEdit_236->clear();
    ui->lineEdit_237->clear();
    ui->lineEdit_235->setText(QString::number(Quests::PacketID_Popup));
    ui->lineEdit_229->setText(Quests::Popup_ID);
}

void MainWindow::on_lineEdit_236_textChanged(const QString &arg1)
{
    ui->lineEdit_237->setText(arg1);

    if(ui->tabWidget_14->currentIndex() != 2)
    {
        ui->tabWidget_14->setCurrentIndex(2);
    }

    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == false)
    {
        ui->pushButton_167->setDisabled(false);
        ui->pushButton_187->setDisabled(false);

        if(ui->checkBox_27->isChecked() == false)
        {
            ui->checkBox_27->setChecked(true);
        }
    }
    else
    {
        ui->pushButton_167->setDisabled(true);
        ui->pushButton_187->setDisabled(true);

        if(ui->checkBox_27->isChecked() == true)
        {
            ui->checkBox_27->setChecked(false);
        }

        if(ui->checkBox_28->isChecked() == true)
        {
            ui->checkBox_28->setChecked(false);
        }

        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}

void MainWindow::on_pushButton_187_clicked()
{
    model3 = new QSqlTableModel(this);
    model3->setTable("QUEST_POPUPS");
    model3->select();

    QString Text = ui->lineEdit_236->text();
    QString PopUpIDCheck = Quests::PopUpID_PopUpText_Map.key(Text);

    qDebug() << "PopUpIDCheck" << PopUpIDCheck;

    QString NextPopUpID = "";

    if(ui->checkBox_28->isChecked() == false)
    {
        if(!Quests::PopUpID_PopUpText_Map.contains(PopUpIDCheck) || ui->checkBox_43->isChecked() == true)
        {
            QSqlQuery query ("SELECT COUNT (*) FROM QUEST_POPUPS");

            while(query.next())
            {
                Quests::PacketID_Popup = query.value(0).toInt();
                qDebug() << "Quests::PacketID_Popup1" << Quests::PacketID_Popup;
            }

            query.prepare (QString ("SELECT * FROM QUEST_POPUPS WHERE rowid = :val"));
            query.bindValue(":val",Quests::PacketID_Popup);
            query.exec();

            while(query.next())
            {
                Quests::Popup_ID = query.value(1).toString();

                qDebug() << "Quests::Popup_ID1" << Quests::Popup_ID;
            }

            Quests::PacketID_Popup++;

            qDebug() << "Quests::PacketID_Popup2" << Quests::PacketID_Popup;

            if(Quests::Popup_ID.size() < 10)
            {
                do
                {
                    Quests::Popup_ID.append("0");

                }while(Quests::Popup_ID.size() < 10);
            }

            Quests::Popup_ID.remove(0,2);

            QString Byte1st_half = Quests::Popup_ID.mid(0,4);
            QString Byte2nd_half = Quests::Popup_ID.mid(4,8);

            increment sendto;

            if(Byte1st_half == "FFFF")
            {
                Byte1st_half = "0000";
                Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
                Quests::Popup_ID = Byte1st_half;
            }
            else
            {
                Quests::Popup_ID = sendto.count(Byte1st_half.toUtf8());
                Quests::Popup_ID.append(Byte2nd_half);
            }

            NextPopUpID = sendto.count(Quests::Popup_ID.mid(0,4).toUtf8());
            NextPopUpID.append(Byte2nd_half);

            Quests::Popup_ID.insert(0,"P_");

            ui->lineEdit_235->setText(QString::number(Quests::PacketID_Popup));
            ui->lineEdit_229->setText(Quests::Popup_ID);

            qDebug() << "Quests::Popup_ID2" << Quests::Popup_ID;

        }
    }
    else
    {
        Quests::PacketID_Popup = ui->lineEdit_235->text().toInt(nullptr,10);
        Quests::Popup_ID = ui->lineEdit_229->text();
    }


    if(!Quests::PopUpID_PopUpText_Map.contains(PopUpIDCheck) || ui->checkBox_43->isChecked() == true)
    {
        if(Text.isEmpty() == false)
        {
            Quests::PopUpID_PopUpText_Map.insert(Quests::Popup_ID,Text);

            db.transaction();

            QSqlQuery query;

            Table_Name = "QUEST_POPUPS";

            if(ui->checkBox_28->isChecked() == false)//if you are editing the OPTI text
            {
                Column_Name = "PacketID";

                query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
                query.bindValue(":id",Quests::PacketID_Popup);
                query.exec();


                Column_Name = "Popup_ID";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Quests::Popup_ID);
                query.bindValue(":id",Quests::PacketID_Popup);
                query.exec();

                Quests::Popup_ID = "P_" + NextPopUpID;
            }

            Column_Name = "Popup_Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Popup);
            query.exec();

            db.commit();

            ui->checkBox_43->setChecked(false);
        }
    }

    model3->setTable("QUEST_POPUPS");
    model3->select();
    ui->tableView_10->setModel(model3);
    ui->tableView_10->setColumnWidth(2,300);
}

void MainWindow::on_pushButton_167_clicked()
{
    QString Text = ui->lineEdit_236->text();

    if(Text.isEmpty() == false)
    {
        if(!All_Text.contains(Text))
        {
            All_Text.append(Text);

            db.transaction();

            qDebug() << "Text" << Text;
            qDebug() << "Quests::PacketID_Text" << Quests::PacketID_Text;
            qDebug() << "Quests::Text_ID" << Quests::Text_ID;

            Table_Name = "QUEST_TEXT";
            Column_Name = "PacketID";
            QSqlQuery query;
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            if(!query.exec())
            {
                qDebug() << Column_Name << query.lastError();
            }

            Column_Name = "Text_ID";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Quests::Text_ID);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            if(!query.exec())
            {
                qDebug() << Column_Name << query.lastError();
            }

            Column_Name = "Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            if(!query.exec())
            {
                qDebug() << Column_Name << query.lastError();
            }



            db.commit();

            increment send;

            QByteArray Byte1 = Quests::Text_ID.mid(0,4).toUtf8();
            QByteArray Byte2 = Quests::Text_ID.mid(4,4).toUtf8();

            Quests::Text_ID = send.count(Byte1);
            Quests::Text_ID.append(Byte2);

            Quests::PacketID_Text++;

            ui->lineEdit_245->setText(QString::number(Quests::PacketID_Text));
            ui->lineEdit_226->setText(Quests::Text_ID);

        }
    }
}

void MainWindow::on_pushButton_156_clicked()
{
    model9 = new QSqlTableModel(this);
    model9->setTable("QUEST_MENUS");
    model9->select();

    if(ui->checkBox_22->isChecked() == true)
    {
        int Packet_ID2 = ui->lineEdit_261->text().toInt(nullptr,10);

        QSqlQuery query;
        query.prepare (QString ("SELECT * FROM QUEST_MENUS WHERE rowid = :val"));
        query.bindValue(":val",Packet_ID2);
        query.exec();

        //qDebug() << "Packet_ID2" << Packet_ID2;

        QVector<QString> tempOptionIDVect;
        QVector<QString> tempOptionTextVect;


        while(query.next())
        {
            QSqlRecord record = query.record();

            for(int fd = 3; fd < record.count(); fd+=2)
            {
                QString OptionsID = record.value(fd).toString();
                QString OptionsText = record.value(fd+1).toString();

                //qDebug() << "OptionsID" << OptionsID;
                //qDebug() << "OptionsText" << OptionsText;

                if(OptionsID.isEmpty() == false)
                {
                    tempOptionIDVect.append(OptionsID);
                    tempOptionTextVect.append(OptionsText);
                }
                else
                {
                    break;
                }
            }
        }

        //qDebug() << "tempOptionIDVect.size()" << tempOptionIDVect.size();
        //qDebug() << "tempOptionTextVect.size()" << tempOptionTextVect.size();

        QString NewOptionText = ui->lineEdit_230->text();
        QString NewOptionID = ui->lineEdit_165->text();

        //qDebug() << "NewOptionText" << NewOptionText;
        //qDebug() << "NewOptionID" << NewOptionID;

        tempOptionIDVect.append(NewOptionID);
        tempOptionTextVect.append(NewOptionText);

        for(int add = 0; add < tempOptionIDVect.size(); add++)
        {
            QString optionid = tempOptionIDVect.at(add);
            QString optiontext = tempOptionTextVect.at(add);

            db.transaction();

            QString Num1 = QString("%1").arg(add+1,2,10,QLatin1Char('0')).toUpper();

            Table_Name = "QUEST_MENUS";

            Column_Name = "Option_ID_" + Num1;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",optionid);
            query.bindValue(":id",Packet_ID2);
            query.exec();

            Column_Name = "Option_Text_" + Num1;


            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",optiontext);
            query.bindValue(":id",Packet_ID2);
            query.exec();

            db.commit();

        }
    }


    model9 = new QSqlTableModel(this);
    model9->setTable("QUEST_MENUS");
    model9->select();
    ui->tableView_4->setModel(model9);
    ui->tableView_4->setColumnWidth(2,300);

    ui->tabWidget_14->setCurrentIndex(0);
}







void MainWindow::on_Icon_ItemsID_5_textChanged(const QString &arg1)
{
    ui->lineEdit_238->setText(arg1);
}

void MainWindow::on_Icon_ItemsID_6_textChanged(const QString &arg1)
{
    ui->lineEdit_265->setText(arg1);
}

void MainWindow::on_lineEdit_240_textChanged(const QString &arg1)
{
    QString NPCS_Names = arg1;

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setFilter(QString("[Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();
    ui->tableView_11->setModel(model1);

    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->tableView_11->setModel(model1);
    }
}

void MainWindow::on_tableView_11_clicked(const QModelIndex &index)
{
    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QString val1 = ui->tableView_11->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Packet (8)] = '"+val1+"' or [ObjectID (4)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"'"));


    if(query1.exec())
    {
        while(query1.next())
        {

            ui->lineEdit_240->setText(query1.value(1).toString());
            ui->lineEdit_241->setText(query1.value(5).toString());
            ui->lineEdit_269->setText(query1.value(1).toString());
            ui->lineEdit_262->setText(query1.value(5).toString());
        }
    }

    model1->setTable("NPCS");
    model1->select();
    ui->tableView_11->setModel(model1);
}

void MainWindow::on_Icon_tableView_5_clicked(const QModelIndex &index)
{
    QString val1 = ui->Icon_tableView_5->model()->data(index).toString();

    model = new QSqlTableModel(this);
    model->setTable("ITEMS");
    model->select();

    QSqlQuery query;
    query.exec(QString("SELECT * FROM ITEMS WHERE [PacketID (8)] = '"+val1+"' or [Name] = '"+val1+"'"));
    model->setFilter(QString("[PacketID (8)] = '"+val1+"'  or [Name] = '"+val1+"'"));
    model->select();

    if(query.exec())
    {
        while(query.next())
        {

            QSqlRecord record = query.record();

            ui->Icon_lineEdit_Item_Name_4->setText(record.value(1).toString());

            ui->Icon_lineEdit_Items_Color_4->setText(record.value(2).toString());

            QByteArray textascii = record.value(38).toString().toUtf8();

            for (int cc = 0; cc < textascii.size() * 2; cc+=2)

            {
                textascii.remove(cc + 2,2);
            }

            QByteArray textascii3 = textascii.fromHex(textascii);
            ui->Icon_textEdit_7->setText(QString::fromUtf8(textascii3));

            QString Bytes5 = record.value(15).toString();

            QString Bytes4 = Icon_5Byte_Map.key(Bytes5);

            ui->Icon_ItemsID_5->setText(record.value(12).toString());

            int index = Icon_4_Index_Map.key(Bytes4);

            QString Icon_val = Icon_Map.value(index);

            ui->Icon_label_63->setPixmap(Icon_val);
        }
    }


    model->setTable("ITEMS");
    model->select();
    ui->Icon_tableView_5->setModel(model);
}

void MainWindow::on_Icon_lineEdit_Items_Color_4_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->Icon_Color_widget_4->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));


        ui->Icon_Color_widget_4->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}

void MainWindow::on_Icon_lineEdit_Item_Name_4_textChanged(const QString &arg1)
{
    QString NPCS_Names = arg1;

    model = new QSqlTableModel(this);
    model->setTable("ITEMS");
    model->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM ITEMS WHERE [Name] LIKE '%"+arg1+"%'"));
    model->setFilter(QString("[Name] LIKE '%"+arg1+"%'"));
    model->setSort(2, Qt::DescendingOrder);
    model->select();
    ui->Icon_tableView_5->setModel(model);

    ui->lineEdit_270->setText(arg1);


    if(arg1.isEmpty() == true)
    {
        model->setTable("ITEMS");
        model->select();
        ui->Icon_tableView_5->setModel(model);
    }
}

void MainWindow::on_checkBox_30_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(7,"M_");
        ui->checkBox_29->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(7,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_29_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(9,"P_");
        ui->checkBox_30->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(9,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_38_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(11,"IT_");
        ui->checkBox_39->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(11,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_39_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(13,"IG_");
        ui->checkBox_38->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(13,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_37_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(15,"TT_");
        ui->checkBox_36->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(15,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_36_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(17,"TG_");
        ui->checkBox_37->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(17,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_32_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(5,"xp_");
    }
    else
    {
        QuestCodeVector.replace(5,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_33_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(19,"sp_");
    }
    else
    {
        QuestCodeVector.replace(19,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_34_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(21,"QLa_");
        ui->checkBox_42->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(21,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_42_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(23,"QLr_");
        ui->checkBox_34->setChecked(false);
    }
    else
    {
        QuestCodeVector.replace(23,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_textEdit_30_textChanged()
{
    QString Text = ui->textEdit_30->toPlainText();

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_3->setModel(model6);

    if(Text.isEmpty() == true)
    {
        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}

void MainWindow::on_pushButton_161_clicked()
{
    model10 = new QSqlTableModel(this);
    model10->setTable("QUEST_MENUS_OPTIONS");
    model10->select();

    QuestCode = ui->lineEdit_242->text();

    int Packet_ID2 = ui->lineEdit_233->text().toInt(nullptr,10);

    QSqlQuery query;
    query.prepare (QString ("SELECT * FROM QUEST_MENUS_OPTIONS WHERE rowid = :val"));
    query.bindValue(":val",Packet_ID2);
    query.exec();

    if(!query.exec())
    {
        qDebug() << "query.lastError()" << query.lastError();
    }

    qDebug() << "Packet_ID2" << Packet_ID2;

    QVector<QString> tempOptionResultVect;

    while(query.next())
    {
        QSqlRecord record = query.record();

        for(int fd = 4; fd < record.count(); fd++)
        {
            QString OptionsResult = record.value(fd).toString();

            qDebug() << "OptionsResult" << OptionsResult;

            if(OptionsResult.isEmpty() == false)
            {
                tempOptionResultVect.append(OptionsResult);
            }
            else
            {
                break;
            }
        }
    }


    QVector<QString> QuestCodeValuesVector =
    {
        "IC_","","TC_","","xp_","","M_","","P_","","IT_","","IG_","","TT_","","TG_","","sp_","","QLa_","","QLr_","","TS_",""
    };

    QString MenusID = ui->lineEdit_243->text();

    QString PopUPsID = ui->lineEdit_273->text();

    QString ItemsID1 = ui->lineEdit_238->text();

    QString ItemsID2 = ui->lineEdit_238->text();

    QString Tunar1 = ui->lineEdit_268->text();

    QString Tunar2 = ui->lineEdit_268->text();

    QString XP = ui->lineEdit_266->text();

    QString NPCsID = ui->lineEdit_262->text();

    QString QuestLogTextID = ui->lineEdit_297->text();

    QString QuestLogText = ui->textEdit_30->toPlainText();
    // /////////////////////////////////////////////////////////////

    if(QuestCode.contains("IC_"))
    {
        QString ItemsID = ui->lineEdit_238->text();
        QString ItemsQty = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(1,"IC_" + ItemsID + "#" + ItemsQty);
    }

    if(QuestCode.contains("TC_"))
    {
        QString TunarQty = ui->lineEdit_268->text();

        QuestCodeValuesVector.replace(3,"TC_" + TunarQty);
    }

    if(QuestCode.contains("xp_"))
    {
        QuestCodeValuesVector.replace(5,"xp_" + XP);

        qDebug() << "You have received" << XP << "xp.";
    }

    if(QuestCode.contains("M_"))
    {
        QuestCodeValuesVector.replace(7,MenusID);

        qDebug() << "MenusID" << MenusID;
    }

    if(QuestCode.contains("P_"))
    {
        QuestCodeValuesVector.replace(9,PopUPsID);

        qDebug() << "PopUPsID" << PopUPsID;
    }

    if(QuestCode.contains("IT_"))
    {
        QString Quantity = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(11,"IT_" + ItemsID1 + "#" + Quantity);
        QString ItemsName = Opcodes::ItemsID_ItemsName_Map.value(ItemsID1);

        qDebug() << "ItemsID1" << ItemsID1;
        qDebug() << "You have given away" << ItemsName;
    }

    if(QuestCode.contains("IG_"))
    {
        QString Quantity = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(13,"IG_" + ItemsID2 + "#" + Quantity);
        QString ItemsName = Opcodes::ItemsID_ItemsName_Map.value(ItemsID2);

        qDebug() << "ItemsID2" << ItemsID2;
        qDebug() << "You have received" << ItemsName;
    }

    if(QuestCode.contains("TT_"))
    {
        QuestCodeValuesVector.replace(15,"TT_" + Tunar1);

        qDebug() << "You have received" << Tunar1 << "tunar.";
    }

    if(QuestCode.contains("TG_"))
    {
        QuestCodeValuesVector.replace(17,"TG_" + Tunar2);

        qDebug() << "You have given away" << Tunar2 << "tunar.";
    }

    if(QuestCode.contains("sp_"))
    {
        QuestCodeValuesVector.replace(19,"sp_" + NPCsID);
        QString NPCsName1 = checkthezone::NPCsNames.value(NPCsID);

        qDebug() << "You have spawned" << NPCsName1 << ".";
    }

    if(QuestCode.contains("QLa_"))
    {
        QuestCodeValuesVector.replace(21,"QLa_" + QuestLogTextID);
    }

    if(QuestCode.contains("QLr_"))
    {
        QuestCodeValuesVector.replace(23,"QLr_" + QuestLogTextID);
    }

    if(QuestCode.contains("TS_"))
    {
        QString TargetsID = ui->lineEdit_276->text();
        QString SpellGraphic = ui->lineEdit_277->text();

        QuestCodeValuesVector.replace(25,"TS_" + TargetsID + "#" + SpellGraphic);
    }


    Table_Name = "QUEST_MENUS_OPTIONS";


    db.transaction();

    for(int add = 0; add < QuestCodeValuesVector.size(); add+=2)
    {
        QString Result = QuestCodeValuesVector.at(add+1);

        qDebug() << "Result2" << Result;

        if(Result.isEmpty() == false)
        {
            tempOptionResultVect.append(Result);
        }
    }

    qDebug() << "tempOptionResultVect" << tempOptionResultVect;

    for(int add = 0; add < tempOptionResultVect.size(); add++)
    {
        QString Result = tempOptionResultVect.at(add);

        qDebug() << "Result3" << Result;

        QString Num1 = QString("%1").arg(add+1,2,10,QLatin1Char('0')).toUpper();

        Column_Name = "Option_Result_" + Num1;

        qDebug() << "Column_Name" << Column_Name;

        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Result);
        query.bindValue(":id",Packet_ID2);
        query.exec();

        if(!query.exec())
        {
            qDebug() << Column_Name << query.lastError();
        }
    }

    db.commit();

    ui->tabWidget_14->setCurrentIndex(1);

    model10->setTable("QUEST_MENUS_OPTIONS");
    model10->select();
    ui->tableView_9->setModel(model10);
    ui->tableView_9->setColumnWidth(3,300);
}









void MainWindow::on_pushButton_162_clicked()
{
    QMap<QString,QVector<QString>> OptionsIDs_ResultsVectorMap = Quests::MenuID_OptionsIDs_ResultsVectorMap.value("M_01000000");

    QVector<QString> ResultsVector;

    QVector<QString> tempMenuVect = Quests::InGame_MenuesVectorMap.value("M_01000000");

    qDebug() << "tempMenuVect" << tempMenuVect;

    QMap<int,QVector<QString>> tempvectmap;

    int counter = 0;

    if(tempMenuVect.isEmpty() == false)
    {
        for(int re = 1; re < tempMenuVect.size(); re+=2)
        {
            QString OptionID = tempMenuVect.at(re);
            qDebug() << "OptionID" << OptionID;
            ResultsVector = OptionsIDs_ResultsVectorMap.value(OptionID);

            tempvectmap.insert(counter,ResultsVector);
            counter++;
        }
    }

    for(int re = 0; re < tempvectmap.size(); re++)
    {
        ResultsVector = tempvectmap.value(re);
        qDebug() << "ResultsVector" << ResultsVector;

        QVector<QString> ResultTextVector;

        for(int re = 0; re < ResultsVector.size(); re++)
        {
            QString PopUpID = ResultsVector.at(re);

            QString PopUpText = Quests::PopUpID_PopUpText_Map.value(PopUpID);

            qDebug() << "PopUpText" << PopUpText;

            ResultTextVector.append(PopUpText);
        }



    }



    //    QString LargeString = "";

    //    QVector<QString>MenuTextVect;

    //    MenuTextVect = Quests::InGame_MenuesVectorMap.value("M_01000000");

    //    if(MenuTextVect.isEmpty() == false)
    //    {
    //        LargeString = MenuTextVect.at(0);
    //    }

    //    QByteArray Send_FB = "";

    //    QString HeaderText = LargeString;

    //    increment Resending;
    //    QByteArray Resending2 = Resending.count(Servers_Last_MessageNumber);
    //    Servers_Last_MessageNumber = Resending2.toUpper();

    //    increment send;
    //    Quests::QuestMenuCounter = send.count(Quests::QuestMenuCounter);

    //    QString Opcode = "3400" + Quests::QuestMenuCounter + "0000";

    //    Quests sendto;
    //    QByteArray ConvertedHeader = sendto.MenuHeaderConverter(HeaderText);

    //    //qDebug() << "HeaderText" << HeaderText;
    //    //qDebug() << "ConvertedHeaderText" << ConvertedHeader;

    //    QString OptionCount = QString("%1").arg((MenuTextVect.size()-1)/2,2,16,QLatin1Char('0')).toUpper();

    //    //qDebug() << "OptionCount" << OptionCount;

    //    Send_FB.append(Opcode.toUtf8() + ConvertedHeader + OptionCount.toUtf8());

    //    for(int send = 1; send < MenuTextVect.size(); send+=2)
    //    {
    //        QString OptionText = MenuTextVect.at(send+1);

    //        //qDebug() << "OptionText" << OptionText;

    //        QByteArray ConvertedText = sendto.MenuHeaderConverter(OptionText);

    //        //qDebug() << "ConvertedOptionsText" << ConvertedText;

    //        Send_FB.append(ConvertedText);
    //    }

    //    QByteArray ConvertedText = sendto.TestingMenus(Send_FB);

    //    //qDebug() << "TestingMenus" << ConvertedText;

    //    int index = ConvertedText.indexOf("yyyy");
    //    ConvertedText.replace(index,4,"XxxX");

    //    Send_FB.clear();

    //    Send_FB = "SSSSCCCCSIZE01BF543213SISISI00SLMN" + ConvertedText;

    //    packetsize ResizePacket; //call size class
    //    QByteArray ResizePacket2 = ResizePacket.switchsize(Send_FB); //get new size
    //    Send_FB.replace(8,4,ResizePacket2);

    //qDebug() << "popup text" << Send_FB;

    //    crc sendcrc;
    //    QByteArray outcrc =  sendcrc.elcrc(Send_FB);
    //    Send_FB.append(outcrc);
    //    byte1 = Send_FB;

    //    elcrc(byte1);
    //    Send_FB.append(outcrc);

    //    QByteArray Damage_out = Send_FB.fromHex(Send_FB);

    //    QHostAddress current_client_address;
    //    current_client_address.setAddress(QString::fromUtf8(IN_WelcomeGreetings.ClientsIP));
    //    quint16 current_client_port = IN_WelcomeGreetings.ClientsPort.toUShort(nullptr,10);
    //    QString changeIP = current_client_address.toString();

    //    QHostAddress newsender = QHostAddress(changeIP);
    //    worldthread::udpsocket3->writeDatagram(Damage_out,newsender,current_client_port);
}



void MainWindow::on_pushButton_163_clicked()
{
    model3 = new QSqlTableModel(this);
    model3->setTable("QUEST_POPUPS");
    model3->select();

    QuestCode = ui->lineEdit_242->text();

    int Packet_ID2 = ui->lineEdit_235->text().toInt(nullptr,10);

    QSqlQuery query;
    query.prepare (QString ("SELECT * FROM QUEST_POPUPS WHERE rowid = :val"));
    query.bindValue(":val",Packet_ID2);
    query.exec();

    qDebug() << "";

    qDebug() << "Packet_ID2" << Packet_ID2;

    QVector<QString> tempOptionResultVect;

    while(query.next())
    {
        QSqlRecord record = query.record();

        for(int fd = 3; fd < record.count(); fd++)
        {
            QString PopUpResult = record.value(fd).toString();

            qDebug() << "PopUpResult" << PopUpResult;

            if(PopUpResult.isEmpty() == false)
            {
                tempOptionResultVect.append(PopUpResult);
            }
            else
            {
                break;
            }
        }
    }


    QVector<QString> QuestCodeValuesVector =
    {
        "IC_","","TC_","","xp_","","M_","","P_","","IT_","","IG_","","TT_","","TG_","","sp_","","QLa_","","QLr_","","TS_",""
    };

    QString MenusID = ui->lineEdit_243->text();
    QString PopUPsID = ui->lineEdit_273->text();
    QString ItemsID1 = ui->lineEdit_238->text();
    QString ItemsID2 = ui->lineEdit_238->text();
    QString Tunar1 = ui->lineEdit_268->text();
    QString Tunar2 = ui->lineEdit_268->text();
    QString XP = ui->lineEdit_266->text();
    QString NPCsID = ui->lineEdit_262->text();
    QString QuestLogTextID = ui->lineEdit_272->text();
    QString QuestLogText = ui->textEdit_30->toPlainText();

    // /////////////////////////////////////////////////////////////

    if(QuestCode.contains("IC_"))
    {
        QString ItemsID = ui->lineEdit_238->text();
        QString ItemsQty = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(1,"IC_" + ItemsID + "#" + ItemsQty);
    }

    if(QuestCode.contains("TC_"))
    {
        QString TunarQty = ui->lineEdit_268->text();

        QuestCodeValuesVector.replace(3,"TC_" + TunarQty);
    }

    if(QuestCode.contains("xp_"))
    {
        QuestCodeValuesVector.replace(5,"xp_" + XP);

        qDebug() << "You have received" << XP << "xp.";
    }

    if(QuestCode.contains("M_"))
    {
        QuestCodeValuesVector.replace(7,MenusID);

        qDebug() << "MenusID" << MenusID;
    }

    if(QuestCode.contains("P_"))
    {
        QuestCodeValuesVector.replace(9,PopUPsID);

        qDebug() << "PopUPsID" << PopUPsID;
    }

    if(QuestCode.contains("IT_"))
    {
        QString Quantity = ui->lineEdit_265->text();
        QuestCodeValuesVector.replace(11,"IT_" + ItemsID1 + "#" + Quantity);
        QString ItemsName = Opcodes::ItemsID_ItemsName_Map.value(ItemsID1);

        qDebug() << "ItemsID1" << ItemsID1;
        qDebug() << "You have given away" << ItemsName;
    }

    if(QuestCode.contains("IG_"))
    {
        QString Quantity = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(13,"IG_" + ItemsID2 + "#" + Quantity);
        QString ItemsName = Opcodes::ItemsID_ItemsName_Map.value(ItemsID2);

        qDebug() << "ItemsID2" << ItemsID2;
        qDebug() << "You have received" << ItemsName;
    }

    if(QuestCode.contains("TT_"))
    {
        QuestCodeValuesVector.replace(15,"TT_" + Tunar1);

        qDebug() << "You have received" << Tunar1 << "tunar.";
    }

    if(QuestCode.contains("TG_"))
    {
        QuestCodeValuesVector.replace(17,"TG_" + Tunar2);

        qDebug() << "You have given away" << Tunar2 << "tunar.";
    }

    if(QuestCode.contains("sp_"))
    {
        QuestCodeValuesVector.replace(19,"sp_" + NPCsID);
        QString NPCsName1 = checkthezone::NPCsNames.value(NPCsID);

        qDebug() << "You have spawned" << NPCsName1 << ".";
    }

    if(QuestCode.contains("QLa_"))
    {
        QuestCodeValuesVector.replace(21,"QLa_" + QuestLogTextID);
    }

    if(QuestCode.contains("QLr_"))
    {
        QuestCodeValuesVector.replace(23,"QLr_" + QuestLogTextID);
    }

    if(QuestCode.contains("TS_"))
    {
        QString CastersID = ui->lineEdit_276->text();
        QString SpellGraphic = ui->lineEdit_277->text();

        QuestCodeValuesVector.replace(25,"TS_" + CastersID + "#" + SpellGraphic);
    }

    Table_Name = "QUEST_POPUPS";

    db.transaction();

    for(int add = 0; add < QuestCodeValuesVector.size(); add+=2)
    {
        QString Result = QuestCodeValuesVector.at(add+1);

        qDebug() << "Result2" << Result;

        if(Result.isEmpty() == false)
        {
            tempOptionResultVect.append(Result);
        }
    }

    qDebug() << "tempOptionResultVect: " << tempOptionResultVect;

    for(int add = 0; add < tempOptionResultVect.size(); add++)
    {
        QString Result = tempOptionResultVect.at(add);

        qDebug() << "Result3" << Result;

        QString Num1 = QString("%1").arg(add+1,2,10,QLatin1Char('0')).toUpper();

        Column_Name = "Popup_Result_" + Num1;

        qDebug() << "Column_Name: " << Column_Name;

        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Result);
        query.bindValue(":id",Packet_ID2);
        query.exec();

        if(!query.exec())
        {
            qDebug() << "error: " << query.lastError();
        }
    }

    db.commit();

    ui->tabWidget_14->setCurrentIndex(2);

    model3->setTable("QUEST_POPUPS");
    model3->select();
    ui->tableView_10->setModel(model3);
    ui->tableView_10->setColumnWidth(2,300);
}

void MainWindow::on_pushButton_373_clicked()
{
    QString LargeString = ui->textEdit_2->toPlainText();

    ui->textEdit_2->clear();

    QStringList MyList = LargeString.split("\n");

    int counter = 0;

    for(int re = 0; re < MyList.size(); re++)
    {
        QString Newline = MyList.at(re);

        if(Newline.contains("Description"))
        {
            counter++;

            int index = Newline.indexOf("Description");
            QString counter1 = QString("%1").arg(counter,2,10,QLatin1Char('0'));
            Newline.insert(index+11,"_" + counter1);
        }

        ui->textEdit_2->append(Newline);
    }
}

void MainWindow::on_tableView_16_clicked(const QModelIndex &index)
{
    model16 = new QSqlTableModel(this);
    model16->setTable("QUEST_LOGS");
    model16->select();

    QString val1 = ui->tableView_16->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_LOGS WHERE [PacketID] = '"+val1+"'"));

    ui->textEdit_34->clear();

    if(query1.exec())
    {
        while(query1.next())
        {
            ui->lineEdit_287->setText(query1.value(0).toString());
            ui->lineEdit_286->setText(query1.value(1).toString());
            ui->lineEdit_296->setText(query1.value(0).toString());
            ui->lineEdit_297->setText(query1.value(1).toString());
            ui->lineEdit_201->setText(query1.value(2).toString());
            ui->lineEdit_272->setText(query1.value(1).toString());
            ui->textEdit_30->setText(query1.value(2).toString());
            ui->lineEdit_295->setText(query1.value(2).toString());
            ui->lineEdit_281->setText(query1.value(2).toString());
            ui->checkBox_53->setChecked(true);

            ui->textEdit_34->append(query1.value(1).toString());
            ui->textEdit_34->append(query1.value(2).toString());
        }

        if(ui->checkBox_50->isChecked() == true)
        {
            ui->tabWidget_14->setCurrentIndex(7);
            ui->tabWidget_15->setCurrentIndex(3);
        }
    }


    model16->setTable("QUEST_LOGS");
    model16->select();
    ui->tableView_16->setModel(model16);
    ui->tableView_16->setColumnWidth(2,300);

    QString LargeString = ui->textEdit_34->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ui->textEdit_34->clear();

    ui->QuestLog_ListWidget_1->clear();
    ui->QuestLog_ListWidget_2->clear();

    QString NewLine = MyList.at(0);
    ui->textEdit_34->append(NewLine);
    ui->QuestLog_ListWidget_1->addItem(NewLine);
    NewLine = MyList.at(1);
    ui->QuestLog_ListWidget_2->addItem(NewLine);


}

void MainWindow::on_lineEdit_295_textChanged(const QString &arg1)
{
    QString Text = arg1;

    model16 = new QSqlTableModel(this);
    model16->setTable("QUEST_LOGS");
    model16->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_LOGS WHERE [Log_Text] LIKE '%"+Text+"%'"));
    model16->setFilter(QString("[Log_Text] LIKE '%"+Text+"%'"));
    model16->setSort(2, Qt::DescendingOrder);
    model16->select();
    ui->tableView_16->setModel(model16);

    if(Text.isEmpty() == true)
    {
        model16->setTable("QUEST_LOGS");
        model16->select();
        ui->tableView_16->setModel(model16);
        ui->tableView_16->setColumnWidth(2,300);
    }
}

void MainWindow::on_pushButton_193_clicked()
{
    QString Text = ui->lineEdit_201->text();

    if(Text.isEmpty() == false)
    {
        if(!All_Text.contains(Text))
        {
            All_Text.append(Text);

            db.transaction();

            Table_Name = "QUEST_TEXT";
            Column_Name = "PacketID";
            QSqlQuery query;
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text_ID";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Quests::Text_ID);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            db.commit();

            increment send;

            QByteArray Byte1 = Quests::Text_ID.mid(0,4).toUtf8();
            QByteArray Byte2 = Quests::Text_ID.mid(4,4).toUtf8();

            Quests::Text_ID = send.count(Byte1);
            Quests::Text_ID.append(Byte2);

            Quests::PacketID_Text++;

            ui->lineEdit_245->setText(QString::number(Quests::PacketID_Text));
            ui->lineEdit_226->setText(Quests::Text_ID);

        }
    }
}

void MainWindow::on_pushButton_192_clicked()
{
    model16 = new QSqlTableModel(this);
    model16->setTable("QUEST_LOGS");
    model16->select();

    QString Text = ui->lineEdit_201->text();

    QString New_Logs_ID = "";


    if(ui->checkBox_54->isChecked() == false)
    {
        if(!Quests::LogTextID_Text.contains(Text))
        {
            if(Text.isEmpty() == false)
            {
                QSqlQuery query ("SELECT COUNT (*) FROM QUEST_LOGS");

                while(query.next())
                {
                    Quests::PacketID_Logs = query.value(0).toInt();
                    //qDebug() << "PacketID_Logs1" << PacketID_Logs;
                }

                query.prepare (QString ("SELECT * FROM QUEST_LOGS WHERE rowid = :val"));
                query.bindValue(":val",Quests::PacketID_Logs);
                query.exec();

                while(query.next())
                {
                    Quests::Logs_ID = query.value(1).toString();

                    qDebug() << "Logs_ID1" << Quests::Logs_ID;
                }

                Quests::PacketID_Logs++;

                qDebug() << "PacketID_Logs2" << Quests::PacketID_Logs;

                if(Quests::Logs_ID.size() < 11)
                {
                    do
                    {
                        Quests::Logs_ID.append("0");

                    }while(Quests::Logs_ID.size() < 11);
                }

                Quests::Logs_ID.remove(0,3);

                QString Byte1st_half = Quests::Logs_ID.mid(0,4);
                QString Byte2nd_half = Quests::Logs_ID.mid(4,8);

                increment sendto;

                if(Byte1st_half == "FFFF")
                {
                    Byte1st_half = "0000";
                    Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
                    Quests::Logs_ID = Byte1st_half;
                }
                else
                {
                    Quests::Logs_ID = sendto.count(Byte1st_half.toUtf8());
                    Quests::Logs_ID.append(Byte2nd_half);
                }

                New_Logs_ID = sendto.count(Quests::Logs_ID.mid(0,4).toUtf8());
                New_Logs_ID.append(Byte2nd_half);

                Quests::Logs_ID.insert(0,"QL_");

                ui->lineEdit_296->setText(QString::number(Quests::PacketID_Logs));
                ui->lineEdit_297->setText(Quests::Logs_ID);

                qDebug() << "Logs_ID2" << Quests::Logs_ID;

            }
        }

    }

    else
    {
        Quests::PacketID_Logs = ui->lineEdit_296->text().toInt(nullptr,10);
        Quests::Logs_ID = ui->lineEdit_297->text();
    }

    if(!Quests::LogTextID_Text.contains(Text))
    {
        if(Text.isEmpty() == false)
        {
            Quests::LogTextID_Text.insert(Quests::Logs_ID,Text);

            db.transaction();

            QSqlQuery query;

            Table_Name = "QUEST_LOGS";

            if(ui->checkBox_54->isChecked() == false)//if you are editing the OPTI text
            {
                Column_Name = "PacketID";

                query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
                query.bindValue(":id",Quests::PacketID_Logs);
                query.exec();


                Column_Name = "Log_Text_ID";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Quests::Logs_ID);
                query.bindValue(":id",Quests::PacketID_Logs);
                query.exec();


                Quests::Logs_ID = "QL_" + New_Logs_ID;
            }

            Column_Name = "Log_Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Logs);
            query.exec();

            db.commit();

        }
    }

    model16->setTable("QUEST_LOGS");
    model16->select();
    ui->tableView_16->setModel(model16);
    ui->tableView_16->setColumnWidth(2,300);
}

void MainWindow::on_pushButton_194_clicked()
{
    ui->lineEdit_201->clear();
    ui->lineEdit_296->clear();
    ui->lineEdit_297->clear();
    ui->lineEdit_296->setText(QString::number(Quests::PacketID_Logs));
    ui->lineEdit_297->setText(Quests::Logs_ID);
}

void MainWindow::on_lineEdit_201_textChanged(const QString &arg1)
{
    ui->lineEdit_295->setText(arg1);

    if(ui->tabWidget_14->currentIndex() != 3)
    {
        ui->tabWidget_14->setCurrentIndex(3);
    }

    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();

    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == false)
    {
        ui->pushButton_193->setDisabled(false);
        ui->pushButton_192->setDisabled(false);

        if(ui->checkBox_53->isChecked() == false)
        {
            ui->checkBox_53->setChecked(true);
        }
    }
    else
    {
        ui->pushButton_193->setDisabled(true);
        ui->pushButton_192->setDisabled(true);

        if(ui->checkBox_53->isChecked() == true)
        {
            ui->checkBox_53->setChecked(false);
        }

        if(ui->checkBox_54->isChecked() == true)
        {
            ui->checkBox_54->setChecked(false);
        }

        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}

void MainWindow::on_checkBox_53_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 3)
        {
            ui->tabWidget_14->setCurrentIndex(3);
        }

        ui->checkBox_55->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_27->setChecked(false);
        ui->checkBox_25->setChecked(false);
    }
}





void MainWindow::on_pushButton_169_clicked()
{
    model18 = new QSqlTableModel(this);
    model18->setTable("QUEST_ID_RESULTS");
    model18->select();

    QuestCode = ui->lineEdit_242->text();

    int Packet_ID2 = ui->lineEdit_298->text().toInt(nullptr,10);//change

    QSqlQuery query;
    query.prepare (QString ("SELECT * FROM QUEST_ID_RESULTS WHERE rowid = :val"));
    query.bindValue(":val",Packet_ID2);
    query.exec();

    qDebug() << "Packet_ID2" << Packet_ID2;

    QVector<QString> tempOptionResultVect;

    while(query.next())
    {
        QSqlRecord record = query.record();

        for(int fd = 3; fd < record.count(); fd++)
        {
            QString OptionsResult = record.value(fd).toString();

            qDebug() << "OptionsResult" << OptionsResult;

            if(OptionsResult.isEmpty() == false)
            {
                tempOptionResultVect.append(OptionsResult);
            }
            else
            {
                break;
            }
        }
    }


    QVector<QString> QuestCodeValuesVector =
    {
        "IC_","","TC_","","xp_","","M_","","P_","","IT_","","IG_","","TT_","","TG_","","sp_","","QLa_","","QLr_","","TS_",""
    };

    QString MenusID = ui->lineEdit_243->text();

    QString PopUPsID = ui->lineEdit_229->text();

    QString ItemsID1 = ui->lineEdit_238->text();

    QString ItemsID2 = ui->lineEdit_238->text();

    QString Tunar1 = ui->lineEdit_268->text();

    QString Tunar2 = ui->lineEdit_268->text();

    QString XP = ui->lineEdit_266->text();

    QString NPCsID = ui->lineEdit_262->text();

    QString QuestLogTextID = ui->lineEdit_272->text();

    QString QuestLogText = ui->textEdit_30->toPlainText();
    // /////////////////////////////////////////////////////////////

    if(QuestCode.contains("IC_"))
    {
        QString ItemsID = ui->lineEdit_238->text();
        QString ItemsQty = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(1,"IC_" + ItemsID + "#" + ItemsQty);
    }

    if(QuestCode.contains("TC_"))
    {
        QString TunarQty = ui->lineEdit_268->text();

        QuestCodeValuesVector.replace(3,"TC_" + TunarQty);
    }

    if(QuestCode.contains("xp_"))
    {
        QuestCodeValuesVector.replace(5,"xp_" + XP);

        qDebug() << "You have received" << XP << "xp.";
    }

    if(QuestCode.contains("M_"))
    {
        QuestCodeValuesVector.replace(7,MenusID);

        qDebug() << "MenusID" << MenusID;
    }

    if(QuestCode.contains("P_"))
    {
        QuestCodeValuesVector.replace(9,PopUPsID);

        qDebug() << "PopUPsID" << PopUPsID;
    }

    if(QuestCode.contains("IT_"))
    {
        QString Quantity = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(11,"IT_" + ItemsID1 + "#" + Quantity);
        QString ItemsName = Opcodes::ItemsID_ItemsName_Map.value(ItemsID1);

        qDebug() << "ItemsID1" << ItemsID1;
        qDebug() << "You have given away" << ItemsName;
    }

    if(QuestCode.contains("IG_"))
    {
        QString Quantity = ui->lineEdit_265->text();

        QuestCodeValuesVector.replace(13,"IG_" + ItemsID2 + "#" + Quantity);
        QString ItemsName = Opcodes::ItemsID_ItemsName_Map.value(ItemsID2);

        qDebug() << "ItemsID2" << ItemsID2;
        qDebug() << "You have received" << ItemsName;
    }

    if(QuestCode.contains("TT_"))
    {
        QuestCodeValuesVector.replace(15,"TT_" + Tunar1);

        qDebug() << "You have received" << Tunar1 << "tunar.";
    }

    if(QuestCode.contains("TG_"))
    {
        QuestCodeValuesVector.replace(17,"TG_" + Tunar2);

        qDebug() << "You have given away" << Tunar2 << "tunar.";
    }

    if(QuestCode.contains("sp_"))
    {
        QuestCodeValuesVector.replace(19,"sp_" + NPCsID);
        QString NPCsName1 = checkthezone::NPCsNames.value(NPCsID);

        qDebug() << "You have spawned" << NPCsName1 << ".";
    }

    if(QuestCode.contains("QLa_"))
    {
        QuestCodeValuesVector.replace(21,"QLa_" + QuestLogTextID);

        qDebug() << "You have added QuestLog" << QuestLogTextID << ".";
    }

    if(QuestCode.contains("QLr_"))
    {
        QuestCodeValuesVector.replace(23,"QLr_" + QuestLogTextID);

        qDebug() << "You have removed QuestLog" << QuestLogTextID << ".";
    }

    if(QuestCode.contains("TS_"))
    {
        QString TargetsID = ui->lineEdit_276->text();
        QString SpellGraphic = ui->lineEdit_277->text();

        QuestCodeValuesVector.replace(25,"TS_" + TargetsID + "#" + SpellGraphic);
    }

    Table_Name = "QUEST_ID_RESULTS";


    db.transaction();

    for(int add = 0; add < QuestCodeValuesVector.size(); add+=2)
    {
        QString Result = QuestCodeValuesVector.at(add+1);

        qDebug() << "Result2" << Result;

        if(Result.isEmpty() == false)
        {
            tempOptionResultVect.append(Result);
        }
    }

    qDebug() << "tempOptionResultVect" << tempOptionResultVect;

    for(int add = 0; add < tempOptionResultVect.size(); add++)
    {
        QString Result = tempOptionResultVect.at(add);

        qDebug() << "Result3" << Result;

        QString Num1 = QString("%1").arg(add+1,2,10,QLatin1Char('0')).toUpper();

        Column_Name = "QuestID_Result_" + Num1;

        qDebug() << "Column_Name" << Column_Name;

        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Result);
        query.bindValue(":id",Packet_ID2);
        query.exec();
    }

    db.commit();

    ui->tabWidget_14->setCurrentIndex(5);

    model18->setTable("QUEST_ID_RESULTS");
    model18->select();
    ui->tableView_18->setModel(model18);
    ui->tableView_18->setColumnWidth(2,300);
}

void MainWindow::on_checkBox_55_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 4)
        {
            ui->tabWidget_14->setCurrentIndex(4);
        }

        ui->checkBox_53->setChecked(false);
        ui->checkBox_26->setChecked(false);
        ui->checkBox_27->setChecked(false);
        ui->checkBox_25->setChecked(false);
    }
}

void MainWindow::on_pushButton_197_clicked()
{
    QString Text = ui->lineEdit_202->text();

    if(Text.isEmpty() == false)
    {
        if(!All_Text.contains(Text))
        {
            All_Text.append(Text);

            db.transaction();

            Table_Name = "QUEST_TEXT";
            Column_Name = "PacketID";
            QSqlQuery query;
            query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text_ID";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Quests::Text_ID);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();

            Column_Name = "Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Text);
            query.exec();




            db.commit();

            increment send;

            QByteArray Byte1 = Quests::Text_ID.mid(0,4).toUtf8();
            QByteArray Byte2 = Quests::Text_ID.mid(4,4).toUtf8();

            Quests::Text_ID = send.count(Byte1);
            Quests::Text_ID.append(Byte2);

            Quests::PacketID_Text++;

            ui->lineEdit_245->setText(QString::number(Quests::PacketID_Text));
            ui->lineEdit_226->setText(Quests::Text_ID);

        }
    }
}

void MainWindow::on_pushButton_196_clicked()
{
    ui->lineEdit_202->clear();
    ui->lineEdit_298->clear();
    ui->lineEdit_299->clear();
    ui->lineEdit_298->setText(QString::number(Quests::PacketID_Decription));
    ui->lineEdit_299->setText(Quests::Decription_ID);
}

void MainWindow::on_lineEdit_202_textChanged(const QString &arg1)
{
    ui->lineEdit_300->setText(arg1);

    if(ui->tabWidget_14->currentIndex() != 4)
    {
        ui->tabWidget_14->setCurrentIndex(4);
    }

    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();

    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == false)
    {
        ui->pushButton_197->setDisabled(false);
        ui->pushButton_195->setDisabled(false);

        if(ui->checkBox_55->isChecked() == false)
        {
            ui->checkBox_55->setChecked(true);
        }

        ui->lineEdit_227->setText(arg1);
        ui->lineEdit_204->setText(arg1);
    }
    else
    {
        ui->pushButton_197->setDisabled(true);
        ui->pushButton_195->setDisabled(true);

        if(ui->checkBox_55->isChecked() == true)
        {
            ui->checkBox_55->setChecked(false);
        }

        if(ui->checkBox_56->isChecked() == true)
        {
            ui->checkBox_56->setChecked(false);
        }


        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
}



void MainWindow::on_pushButton_195_clicked()
{
    model17 = new QSqlTableModel(this);
    model17->setTable("QUEST_DESCRIPTIONS");
    model17->select();

    QString Text = ui->lineEdit_202->text();

    QString New_Decription_ID = "";

    if(ui->checkBox_56->isChecked() == false)
    {
        if(!Quests::DescriptionTextID_Text.contains(Text))
        {
            if(Text.isEmpty() == false)
            {
                QSqlQuery query ("SELECT COUNT (*) FROM QUEST_DESCRIPTIONS");

                while(query.next())
                {
                    Quests::PacketID_Decription = query.value(0).toInt();
                    //qDebug() << "PacketID_Decription1" << PacketID_Decription;
                }

                query.prepare (QString ("SELECT * FROM QUEST_DESCRIPTIONS WHERE rowid = :val"));
                query.bindValue(":val",Quests::PacketID_Decription);
                query.exec();

                while(query.next())
                {
                    Quests::Decription_ID = query.value(1).toString();

                    qDebug() << "Decription_ID1" << Quests::Decription_ID;
                }

                Quests::PacketID_Decription++;

                qDebug() << "PacketID_Decription2" << Quests::PacketID_Decription;

                if(Quests::Decription_ID.size() < 11)
                {
                    do
                    {
                        Quests::Decription_ID.append("0");

                    }while(Quests::Decription_ID.size() < 11);
                }

                Quests::Decription_ID.remove(0,3);

                QString Byte1st_half = Quests::Decription_ID.mid(0,4);
                QString Byte2nd_half = Quests::Decription_ID.mid(4,8);

                increment sendto;

                if(Byte1st_half == "FFFF")
                {
                    Byte1st_half = "0000";
                    Byte1st_half.append(sendto.count(Byte2nd_half.toUtf8()));
                    Quests::Decription_ID = Byte1st_half;
                }
                else
                {
                    Quests::Decription_ID = sendto.count(Byte1st_half.toUtf8());
                    Quests::Decription_ID.append(Byte2nd_half);
                }

                New_Decription_ID = sendto.count(Quests::Decription_ID.mid(0,4).toUtf8());
                New_Decription_ID.append(Byte2nd_half);

                Quests::Decription_ID.insert(0,"QD_");

                ui->lineEdit_298->setText(QString::number(Quests::PacketID_Decription));
                ui->lineEdit_299->setText(Quests::Decription_ID);

                qDebug() << "Decription_ID2" << Quests::Decription_ID;

            }
        }
    }
    else
    {
        Quests::PacketID_Decription = ui->lineEdit_298->text().toInt(nullptr,10);
        Quests::Decription_ID = ui->lineEdit_299->text();
    }

    if(!Quests::DescriptionTextID_Text.contains(Text))
    {
        if(Text.isEmpty() == false)
        {
            Quests::DescriptionTextID_Text.insert(Quests::Decription_ID,Text);

            db.transaction();

            QSqlQuery query;

            Table_Name = "QUEST_DESCRIPTIONS";

            if(ui->checkBox_56->isChecked() == false)//if you are editing the OPTI text
            {
                Column_Name = "PacketID";

                query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
                query.bindValue(":id",Quests::PacketID_Decription);
                query.exec();


                Column_Name = "Description_Text_ID";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Quests::Decription_ID);
                query.bindValue(":id",Quests::PacketID_Decription);
                query.exec();

                Quests::Decription_ID = "QD_" + New_Decription_ID;
            }

            Column_Name = "Description_Text";
            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",Text);
            query.bindValue(":id",Quests::PacketID_Decription);
            query.exec();

            db.commit();

        }
    }



    if(Quests::DescriptionTextID_Text.contains(Quests::Decription_ID))
    {
        if(ui->checkBox_56->isChecked() == true)//if you are editing the OPTI text
        {

            db.transaction();

            QSqlQuery query;

            int packetID = Description_PacketID.value(OldDescription);

            qDebug() << "packetID" << packetID;

            query.prepare (QString ("SELECT * FROM QUEST_ID_RESULTS WHERE rowid = :val"));
            query.bindValue(":val",packetID);
            query.exec();


            QString oldText = "";

            while(query.next())
            {
                oldText = query.value(2).toString();

                qDebug() << "oldText" << oldText;
            }

            qDebug() << "OldDesc" << OldDescription;

            if(oldText == OldDescription)
            {
                Table_Name = "QUEST_ID_RESULTS";

                Column_Name = "Description";
                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",Text);
                query.bindValue(":id",packetID);
                query.exec();

                db.commit();
            }


            //------------------------------------------------------------------------------------------------------------


            if(ui->checkBox->isChecked() == true)
            {
                QString NPCsName = ui->lineEdit_206->text();

                int PacketID = Quests::QuestGiversNames_IDS_Map.value(NPCsName);

                if(Quests::QuestValuesVectorMap.contains(PacketID))
                {
                    QVector<QString>tempvect = Quests::QuestValuesVectorMap.value(PacketID);

                    qDebug() << "tempvect" << tempvect;

                    if(tempvect.contains(OldDescription))
                    {
                        ui->checkBox->setChecked(false);

                        int index = tempvect.indexOf(OldDescription);

                        qDebug() << "index" << index;

                        db.transaction();

                        Table_Name = "QUESTGIVERS_IDS";

                        QString NPCsName = ui->lineEdit_206->text();
                        Column_Name = "NPCs_Name";

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",NPCsName);
                        query.bindValue(":id",PacketID);
                        query.exec();

                        QString NPCsID = ui->lineEdit_207->text();
                        Column_Name = "NPCs_ID";

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",NPCsID);
                        query.bindValue(":id",PacketID);
                        query.exec();

                        QString QuestID = ui->lineEdit_220->text();
                        Column_Name = QuestFieldNames.at(index-1);

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",QuestID);
                        query.bindValue(":id",PacketID);
                        query.exec();


                        QString Description = ui->lineEdit_227->text();
                        Column_Name = QuestFieldNames.at(index);

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",Description);
                        query.bindValue(":id",PacketID);
                        query.exec();

                        QString StartingCity = ui->lineEdit_221->text();
                        Column_Name = QuestFieldNames.at(index+1);

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",StartingCity);
                        query.bindValue(":id",PacketID);
                        query.exec();

                        QString Faction = ui->lineEdit_228->text();
                        Column_Name = QuestFieldNames.at(index+2);

                        int Faction2 = Faction.toInt(nullptr,10);

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",Faction2);
                        query.bindValue(":id",PacketID);
                        query.exec();

                        QString Race = ui->lineEdit_223->text();
                        Column_Name = QuestFieldNames.at(index+3);

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",Race);
                        query.bindValue(":id",PacketID);
                        query.exec();

                        QString Class = ui->lineEdit_222->text();
                        Column_Name = QuestFieldNames.at(index+4);

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",Class);
                        query.bindValue(":id",PacketID);
                        query.exec();

                        QString Level = ui->lineEdit_225->text();
                        Column_Name = QuestFieldNames.at(index+5);

                        qDebug() << "Column_Name" << Column_Name;

                        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                        query.bindValue(":val",Level);
                        query.bindValue(":id",PacketID);
                        query.exec();


                        db.commit();

                        on_pushButton_153_clicked();
                    }
                }
            }
        }
    }

    model17->setTable("QUEST_DESCRIPTIONS");
    model17->select();
    ui->tableView_17->setModel(model17);
    ui->tableView_17->setColumnWidth(2,300);
}

void MainWindow::on_tableView_17_clicked(const QModelIndex &index)
{
    model17 = new QSqlTableModel(this);
    model17->setTable("QUEST_DESCRIPTIONS");
    model17->select();

    ui->checkBox_56->setChecked(true);

    QString val1 = ui->tableView_17->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_DESCRIPTIONS WHERE [PacketID] = '"+val1+"'"));

    QString Text = "";

    ui->textEdit_35->clear();

    if(query1.exec())
    {
        while(query1.next())
        {
            ui->lineEdit_289->setText(query1.value(0).toString());
            ui->lineEdit_288->setText(query1.value(1).toString());
            ui->lineEdit_298->setText(query1.value(0).toString());
            ui->lineEdit_299->setText(query1.value(1).toString());
            ui->lineEdit_202->setText(query1.value(2).toString());
            Text = query1.value(2).toString();

            ui->lineEdit_227->setText(query1.value(2).toString());
            ui->lineEdit_282->setText(query1.value(2).toString());
            ui->lineEdit_300->setText(query1.value(2).toString());
            ui->checkBox_55->setChecked(true);

            ui->textEdit_35->append(query1.value(1).toString());
            ui->textEdit_35->append(query1.value(2).toString());

            if(ui->checkBox_56->isChecked() == true)
            {
                OldDescription = query1.value(2).toString();
            }
        }

        if(ui->checkBox_50->isChecked() == true)
        {
            ui->tabWidget_14->setCurrentIndex(7);
            ui->tabWidget_15->setCurrentIndex(4);
        }
    }



    QSqlQuery query;

    QMapIterator<int,QVector<QString>> iter (Quests::QuestValuesVectorMap);
    while (iter.hasNext())
    {
        iter.next();
        int PacketID = iter.key();
        QVector<QString>tempvect = iter.value();

        qDebug() << "tempvect" << tempvect;
        qDebug() << "OldDescription" << OldDescription;


        if(tempvect.contains(OldDescription))
        {
            int index = tempvect.indexOf(OldDescription);

            qDebug() << "index" << index;

            query.prepare (QString ("SELECT * FROM QUESTGIVERS_IDS WHERE rowid = :val"));
            query.bindValue(":val",PacketID);
            query.exec();

            index = index+3;

            while(query.next())
            {
                QString QuestID = query.value(index-1).toString();
                QString Description = query.value(index).toString();
                QString StartingCity = query.value(index+1).toString();
                QString Faction = query.value(index+2).toString();
                QString Race = query.value(index+3).toString();
                QString Class = query.value(index+4).toString();
                QString Level  = query.value(index+5).toString();

                ui->lineEdit_206->setText(query.value(1).toString());
                ui->lineEdit_207->setText(query.value(2).toString());
                ui->lineEdit_220->setText(QuestID);
                ui->lineEdit_227->setText(Description);
                ui->lineEdit_221->setText(StartingCity);
                ui->lineEdit_228->setText(Faction);
                ui->lineEdit_223->setText(Race);
                ui->lineEdit_222->setText(Class);
                ui->lineEdit_225->setText(Level);

                ui->checkBox->setChecked(true);
            }
        }
    }




    model17->setTable("QUEST_DESCRIPTIONS");
    model17->select();
    ui->tableView_17->setModel(model17);
    ui->tableView_17->setColumnWidth(2,300);

    if(ui->checkBox_57->isChecked() == true && ui->checkBox_50->isChecked() == false)
    {
        if(ui->tabWidget_14->currentIndex() != 5)
        {
            ui->tabWidget_14->setCurrentIndex(5);
        }

        ui->lineEdit_204->setText(Text);
        ui->lineEdit_301->setText(Text);
    }

    QString LargeString = ui->textEdit_35->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ui->textEdit_35->clear();

    ui->Description_ListWidget_1->clear();
    ui->Description_ListWidget_2->clear();

    QString NewLine = MyList.at(0);
    ui->textEdit_35->append(NewLine);
    ui->Description_ListWidget_1->addItem(NewLine);
    NewLine = MyList.at(1);
    ui->Description_ListWidget_2->addItem(NewLine);

}



void MainWindow::on_lineEdit_225_textChanged(const QString &arg1)
{
    int arg2 = arg1.toInt(nullptr,16);
    QString arg3 = QString("%1").arg(arg2,1,10,QLatin1Char('0')).toUpper();

    ui->lineEdit_224->setText(arg3);
}

void MainWindow::on_lineEdit_204_textChanged(const QString &arg1)
{
    ui->lineEdit_300->setText(arg1);

    if(ui->tabWidget_14->currentIndex() != 4)
    {
        ui->tabWidget_14->setCurrentIndex(4);
    }

    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();

    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == true)
    {
        if(ui->checkBox_57->isChecked() == true)
        {
            ui->checkBox_57->setChecked(false);
        }

        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
    else
    {
        if(ui->checkBox_57->isChecked() == false)
        {
            ui->checkBox_57->setChecked(true);
        }
    }
}

void MainWindow::on_lineEdit_301_textChanged(const QString &arg1)
{
    model18 = new QSqlTableModel(this);
    model18->setTable("QUEST_ID_RESULTS");
    model18->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_ID_RESULTS WHERE [Description] LIKE '%"+arg1+"%'"));
    model18->setFilter(QString("[Description] LIKE '%"+arg1+"%'"));
    model18->setSort(2, Qt::DescendingOrder);
    model18->select();

    ui->tableView_18->setModel(model18);

    if(arg1.isEmpty() == true)
    {
        if(ui->checkBox_57->isChecked() == true)
        {
            ui->checkBox_57->setChecked(false);
        }

        model18->setTable("QUEST_ID_RESULTS");
        model18->select();
        ui->tableView_18->setModel(model18);
        ui->tableView_18->setColumnWidth(2,300);
    }
}

void MainWindow::on_lineEdit_300_textChanged(const QString &arg1)
{
    model17 = new QSqlTableModel(this);
    model17->setTable("QUEST_DESCRIPTIONS");
    model17->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_DESCRIPTIONS WHERE [Description_Text] LIKE '%"+arg1+"%'"));
    model17->setFilter(QString("[Description_Text] LIKE '%"+arg1+"%'"));
    model17->setSort(2, Qt::DescendingOrder);
    model17->select();

    ui->tableView_17->setModel(model17);

    if(arg1.isEmpty() == true)
    {
        if(ui->checkBox_55->isChecked() == true)
        {
            ui->checkBox_55->setChecked(false);
        }

        model17->setTable("QUEST_DESCRIPTIONS");
        model17->select();
        ui->tableView_17->setModel(model17);
        ui->tableView_17->setColumnWidth(2,300);
    }
}

void MainWindow::on_lineEdit_237_textChanged(const QString &arg1)
{
    model3 = new QSqlTableModel(this);
    model3->setTable("QUEST_POPUPS");
    model3->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_POPUPS WHERE [Popup_Text] LIKE '%"+arg1+"%'"));
    model3->setFilter(QString("[Popup_Text] LIKE '%"+arg1+"%'"));
    model3->setSort(2, Qt::DescendingOrder);
    model3->select();

    ui->tableView_10->setModel(model3);

    if(arg1.isEmpty() == true)
    {
        if(ui->checkBox_27->isChecked() == true)
        {
            ui->checkBox_27->setChecked(false);
        }

        model3->setTable("QUEST_POPUPS");
        model3->select();
        ui->tableView_10->setModel(model3);
        ui->tableView_10->setColumnWidth(2,300);
    }
}

void MainWindow::on_pushButton_198_clicked()
{
    ui->checkBox_57->setChecked(false);
    ui->lineEdit_204->clear();
}

void MainWindow::on_checkBox_57_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        if(ui->tabWidget_14->currentIndex() != 4)
        {
            ui->tabWidget_14->setCurrentIndex(4);
        }
    }
}

void MainWindow::on_pushButton_170_clicked()
{
    ui->lineEdit_273->clear();
    ui->lineEdit_274->clear();
    ui->lineEdit_275->clear();
}

void MainWindow::on_lineEdit_275_textChanged(const QString &arg1)
{
    ui->lineEdit_237->setText(arg1);

    if(ui->tabWidget_14->currentIndex() != 2)
    {
        ui->tabWidget_14->setCurrentIndex(2);
    }

    QString Text = arg1;

    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_TEXT WHERE [Text] LIKE '%"+Text+"%'"));
    model6->setFilter(QString("[Text] LIKE '%"+Text+"%'"));
    model6->setSort(2, Qt::DescendingOrder);
    model6->select();
    ui->tableView_3->setModel(model6);

    if(arg1.isEmpty() == true)
    {
        if(ui->checkBox_41->isChecked() == true)
        {
            ui->checkBox_41->setChecked(false);
        }

        model6->setTable("QUEST_TEXT");
        model6->select();
        ui->tableView_3->setModel(model6);
        ui->tableView_3->setColumnWidth(2,1000);
    }
    else
    {
        if(ui->checkBox_41->isChecked() == false)
        {
            ui->checkBox_41->setChecked(true);
        }
    }
}

void MainWindow::on_pushButton_153_clicked()
{
    ui->lineEdit_206->clear();
    ui->lineEdit_207->clear();
    ui->lineEdit_220->clear();
    ui->lineEdit_221->clear();
    ui->lineEdit_224->clear();
    ui->lineEdit_225->clear();
    ui->lineEdit_227->clear();
    ui->lineEdit_223->clear();
    ui->lineEdit_222->clear();
    ui->lineEdit_228->clear();
    ui->textEdit_24->clear();
    ui->checkBox->setChecked(false);
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    Quests::FakeFlag = arg1;

    ui->lineEdit_247->setText(QString::number(Quests::FakeFlag));
}

void MainWindow::on_lineEdit_297_textChanged(const QString &arg1)
{
    ui->lineEdit_272->setText(arg1);
}

void MainWindow::on_Icon_lineEdit_Item_Name_7_textChanged(const QString &arg1)
{
    QString NPCS_Names = arg1;

    model = new QSqlTableModel(this);
    model->setTable("ITEMS");
    model->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM ITEMS WHERE [Name] LIKE '%"+arg1+"%'"));
    model->setFilter(QString("[Name] LIKE '%"+arg1+"%'"));
    model->setSort(2, Qt::DescendingOrder);
    model->select();
    ui->Icon_tableView_5->setModel(model);

    if(ui->checkBox_38->isChecked() == true)
    {
        ui->lineEdit_270->setText(arg1);
    }

    if(ui->checkBox_39->isChecked() == true)
    {
        ui->lineEdit_270->setText(arg1);
    }

    if(arg1.isEmpty() == true)
    {
        model->setTable("ITEMS");
        model->select();
        ui->Icon_tableView_5->setModel(model);
    }
}

void MainWindow::on_tableView_26_clicked(const QModelIndex &index)
{
    QString val1 = ui->tableView_26->model()->data(index).toString();

    model = new QSqlTableModel(this);
    model->setTable("ITEMS");
    model->select();

    QSqlQuery query;
    query.exec(QString("SELECT * FROM ITEMS WHERE [PacketID (8)] = '"+val1+"' or [Name] = '"+val1+"'"));
    model->setFilter(QString("[PacketID (8)] = '"+val1+"'  or [Name] = '"+val1+"'"));
    model->setSort(2, Qt::DescendingOrder);
    model->select();

    if(query.exec())
    {
        while(query.next())
        {

            QSqlRecord record = query.record();

            ui->lineEdit_111->setText(record.value(1).toString());

            ui->lineEdit_123->setText(record.value(2).toString());

            QByteArray textascii = record.value(38).toString().toUtf8();

            for (int cc = 0; cc < textascii.size() * 2; cc+=2)

            {
                textascii.remove(cc + 2,2);
            }

            QByteArray textascii3 = textascii.fromHex(textascii);
            ui->textEdit_27->setText(QString::fromUtf8(textascii3));

            QString Bytes5 = record.value(15).toString();

            QString Bytes4 = Icon_5Byte_Map.key(Bytes5);

            ui->lineEdit_129->setText(record.value(12).toString());

            int index = Icon_4_Index_Map.key(Bytes4);

            QString Icon_val = Icon_Map.value(index);

            ui->Icon_label_66->setPixmap(Icon_val);

        }
    }


    model->setTable("ITEMS");
    model->select();
    ui->tableView_26->setModel(model);
    ui->tableView_26->setColumnWidth(1,300);
}

void MainWindow::on_lineEdit_111_textChanged(const QString &arg1)
{
    if(!db.isOpen())
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(Opcodes::m_FileName);
        db.open();
    }


    model = new QSqlTableModel(this);
    model->setTable("ITEMS");
    model->select();

    ui->Icon_tableView_5->setModel(model);
    ui->tableView_26->setModel(model);
    ui->tableView_26->setColumnWidth(1,300);

    QString Items_Names = arg1;

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM ITEMS WHERE [Name] LIKE '%"+arg1+"%'"));
    model->setFilter(QString("[Name] LIKE '%"+arg1+"%'"));
    model->setSort(2, Qt::DescendingOrder);
    model->select();
    ui->tableView_26->setModel(model);

    if(arg1.isEmpty() == true)
    {
        model->setTable("ITEMS");
        model->select();
        ui->tableView_26->setModel(model);
        ui->tableView_26->setColumnWidth(1,300);
    }
}

void MainWindow::on_lineEdit_123_textChanged(const QString &arg1)
{
    if(arg1 == "FFFFFFFF")
    {
        ui->Icon_Color_widget_7->setStyleSheet("background-color: rgb(222, 222, 222);");
    }
    else
    {
        QString Byte_1st1 = arg1.mid(0,2);
        QString Byte_2nd1 = arg1.mid(2,2);
        QString Byte_3rd1 = arg1.mid(4,2);

        int Byte_1st2 = Byte_1st1.toInt(nullptr,16);
        int Byte_2nd2 = Byte_2nd1.toInt(nullptr,16);
        int Byte_3rd2 = Byte_3rd1.toInt(nullptr,16);

        Byte_1st1 = QString("%1").arg(Byte_1st2,1,10,QLatin1Char('0'));
        Byte_2nd1 = QString("%1").arg(Byte_2nd2,1,10,QLatin1Char('0'));
        Byte_3rd1 = QString("%1").arg(Byte_3rd2,1,10,QLatin1Char('0'));


        ui->Icon_Color_widget_7->setStyleSheet("background-color: rgb(" + Byte_1st1 + ", " +Byte_2nd1 + ", " + Byte_3rd1 + ");");
    }
}


void MainWindow::on_pushButton_157_clicked()
{
    ui->tabWidget_7->setCurrentIndex(1);
    QString ItemsID = ui->lineEdit_129->text();
    QString ItemsName = ui->lineEdit_111->text();

    ui->textEdit_28->clear();
    ui->ShoppinglistWidget1->clear();
    ui->ShoppinglistWidget2->clear();

    ItemsIDs_ItemsNamesVector.append(ItemsID);
    ItemsIDs_ItemsNamesVector.append(ItemsName);

    for(int add = 0; add < ItemsIDs_ItemsNamesVector.size(); add+=2)
    {
        ItemsID = ItemsIDs_ItemsNamesVector.at(add);
        ItemsName = ItemsIDs_ItemsNamesVector.at(add+1);

        ui->textEdit_28->append(ItemsID + " " + ItemsName);

        ui->ShoppinglistWidget1->addItem(ItemsName);
        ui->ShoppinglistWidget2->addItem(ItemsID);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString LargeString = ui->textEdit_28->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ItemsIDs_ItemsNamesVector.clear();
    ui->textEdit_28->clear();

    ui->ShoppinglistWidget1->clear();
    ui->ShoppinglistWidget2->clear();

    QVector<QString> FieldValues;

    for(int add = 0; add < MyList.size(); add++)
    {
        QString NewLine = MyList.at(add);

        if(NewLine.isEmpty() == false)
        {
            int index1 = NewLine.indexOf(" ");

            QString ItemsID = NewLine.mid(0,index1);
            QString ItemsName = NewLine.mid(index1+1,NewLine.size());

            qDebug() << "";
            qDebug() << "ItemsID" << ItemsID;
            qDebug() << "ItemsName" << ItemsName;

            if(merchants::Items_Map.contains(ItemsID))
            {
                FieldValues.append(ItemsID);

                ItemsIDs_ItemsNamesVector.append(ItemsID);
                ItemsIDs_ItemsNamesVector.append(ItemsName);

                ui->textEdit_28->append(ItemsID + " " + ItemsName);

                ui->ShoppinglistWidget1->addItem(ItemsName);
                ui->ShoppinglistWidget2->addItem(ItemsID);
            }
        }
    }

    QString NPCsID = ui->lineEdit_59->text();
    QString Greeting = ui->lineEdit_348->text();

    if((LargeString.isEmpty() == false && Greeting.isEmpty() == false && clicked == true) ||
            (LargeString.isEmpty() == false && Greeting.isEmpty() == false && merchants::MerchantIDs_PacketIDsMap.contains(NPCsID)))
    {
        ui->pushButton_3->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_184->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");

        ui->pushButton_154->setStyleSheet("background-color: blue;" "color: white;");
        QString MerchantsName = ui->lineEdit_347->text();
        ui->lineEdit_205->setText(MerchantsName + "'s has recently change.");
    }

    merchants changetext;
    QString returned_text = Greeting;
    Greeting = changetext.Text_to_Unicode(returned_text);

    merchants::Merchant_Text_Map.insert(NPCsID,Greeting);
    merchants::Merchant_List_Map.insert(NPCsID,FieldValues);
}

void MainWindow::on_pushButton_139_clicked()
{
    QString LargeString = ui->textEdit_28->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ItemsIDs_ItemsNamesVector.clear();
    ui->textEdit_28->clear();

    ui->ShoppinglistWidget1->clear();
    ui->ShoppinglistWidget2->clear();

    QVector<QString> FieldValues;

    for(int add = 0; add < MyList.size(); add++)
    {
        QString NewLine = MyList.at(add);

        if(NewLine.isEmpty() == false)
        {
            int index1 = NewLine.indexOf(" ");

            QString ItemsID = NewLine.mid(0,index1);
            QString ItemsName = NewLine.mid(index1+1,NewLine.size());

            qDebug() << "";
            qDebug() << "ItemsID" << ItemsID;
            qDebug() << "ItemsName" << ItemsName;

            if(merchants::Items_Map.contains(ItemsID))
            {
                FieldValues.append(ItemsID);

                ItemsIDs_ItemsNamesVector.append(ItemsID);
                ItemsIDs_ItemsNamesVector.append(ItemsName);

                ui->textEdit_28->append(ItemsID + " " + ItemsName);

                ui->ShoppinglistWidget1->addItem(ItemsName);
                ui->ShoppinglistWidget2->addItem(ItemsID);
            }
        }
    }

    QString NPCsID = ui->lineEdit_59->text();
    QString Greeting = ui->lineEdit_348->text();

    if(LargeString.isEmpty() == false && Greeting.isEmpty() == false)
    {
        clicked = true;
        ui->pushButton_139->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_154->setStyleSheet("background-color: blue;" "color: white;");
        QString MerchantsName = ui->lineEdit_347->text();
        ui->lineEdit_205->setText(MerchantsName + " was added to the merchant list.");
    }


    merchants changetext;
    QString returned_text = Greeting;
    Greeting = changetext.Text_to_Unicode(returned_text);

    merchants::Merchant_Text_Map.insert(NPCsID,Greeting);
    merchants::Merchant_List_Map.insert(NPCsID,FieldValues);


}

void MainWindow::on_lineEdit_347_textChanged(const QString &arg1)
{
    QString ZonesName = Quests::NPCsName_ZoneMap.value(arg1);
    ui->lineEdit_137->setText(ZonesName);
}

void MainWindow::on_lineEdit_59_textChanged(const QString &arg1)
{
    ui->tabWidget_7->setCurrentIndex(1);

    if(merchants::Merchant_Text_Map.contains(arg1))
    {
        QString Greeting = merchants::Merchant_Text_Map.value(arg1);

        Greeting.remove(0,8);

        QByteArray test1 = Greeting.toUtf8();
        QByteArray textascii = test1;

        for (int cc = 0; cc < textascii.size() * 2; cc+=2)
        {
            textascii.remove(cc + 2,2);
        }

        QByteArray textascii3 = textascii.fromHex(textascii);

        ui->lineEdit_348->setText(QString::fromUtf8(textascii3));

        if(merchants::Merchant_List_Map.contains(arg1))
        {
            QVector<QString>FieldValues = merchants::Merchant_List_Map.value(arg1);

            ui->textEdit_28->clear();
            ui->ShoppinglistWidget1->clear();
            ui->ShoppinglistWidget2->clear();

            ItemsIDs_ItemsNamesVector.clear();

            for(int add = 0; add < FieldValues.size(); add++)
            {
                QString ItemsID = FieldValues.at(add);
                QString ItemsName = Opcodes::ItemsID_ItemsName_Map.value(ItemsID);

                ui->textEdit_28->append(ItemsID + " " + ItemsName);

                ui->ShoppinglistWidget1->addItem(ItemsName);
                ui->ShoppinglistWidget2->addItem(ItemsID);

                ItemsIDs_ItemsNamesVector.append(ItemsID);
                ItemsIDs_ItemsNamesVector.append(ItemsName);
            }
        }
    }

    if(merchants::MerchantIDs_PacketIDsMap.contains(arg1))
    {
        int PacketID = merchants::MerchantIDs_PacketIDsMap.value(arg1);
        ui->lineEdit_108->setText(QString::number(PacketID));
    }
    else
    {
        ui->textEdit_28->clear();
        ui->ShoppinglistWidget1->clear();
        ui->ShoppinglistWidget2->clear();

        ItemsIDs_ItemsNamesVector.clear();
        ui->lineEdit_348->clear();
        ui->lineEdit_108->setText("NEW");
    }
}

void MainWindow::on_pushButton_140_clicked()
{
    QString LargeString = ui->textEdit_31->toPlainText();
    QStringList MyList = LargeString.split("\n");

    ui->textEdit_31->clear();

    QVector<QString> tempvect;

    for(int re = 0; re < MyList.size(); re++)
    {
        QString NewLine = MyList.at(re);

        if(NewLine.isEmpty() == false && NewLine != "Exit")
        {
            if(!tempvect.contains(NewLine))
            {
                tempvect.append(NewLine);
                qDebug() << "NewLine" << NewLine;
                ui->textEdit_31->append(NewLine);
            }
        }
    }

    qDebug() << "tempvect.size()" << tempvect.size();
}

void MainWindow::on_pushButton_154_clicked()
{
    ui->pushButton_154->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");

    clicked = false;

    QString NEWorNOT = ui->lineEdit_108->text();
    int PacketID = 0;

    QSqlQuery query;

    Table_Name = "MERCHANTS";

    db.transaction();

    if(NEWorNOT == "NEW")
    {
        QSqlQuery queryQr ("SELECT COUNT (*) FROM MERCHANTS");

        while(queryQr.next())
        {
            Merchants_PacketID = queryQr.value(0).toInt();
        }

        Merchants_PacketID++;

        PacketID = Merchants_PacketID;

        Column_Name = "PacketID";
        query.prepare(QString("INSERT OR IGNORE INTO [%1] ([%2])""VALUES(:id)").arg(Table_Name).arg(Column_Name));
        query.bindValue(":id",PacketID);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        QString Name = ui->lineEdit_347->text();

        Column_Name = "Name";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",Name);
        query.bindValue(":id",PacketID);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        QString NPCsID = ui->lineEdit_59->text();

        Column_Name = "ObjectID";
        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",NPCsID);
        query.bindValue(":id",PacketID);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }

        merchants::MerchantIDs_PacketIDsMap.insert(NPCsID,PacketID);

        QString MerchantsName = ui->lineEdit_347->text();
        ui->lineEdit_205->setText(MerchantsName + " has been added to the database.");
    }
    else
    {
        PacketID = ui->lineEdit_108->text().toInt(nullptr,10);

        QString MerchantsName = ui->lineEdit_347->text();
        ui->lineEdit_205->setText(MerchantsName + " has been updated in the database.");
    }

    QString Location = ui->lineEdit_137->text();

    Column_Name = "Location";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Location);
    query.bindValue(":id",PacketID);
    query.exec();

    if(!query.exec())
    {
        ui->lineEdit_20->setText(query.lastError().text());
        return;
    }

    QString Greeting = ui->lineEdit_348->text();

    Column_Name = "Greeting";
    query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
    query.bindValue(":val",Greeting);
    query.bindValue(":id",PacketID);
    query.exec();

    if(!query.exec())
    {
        ui->lineEdit_20->setText(query.lastError().text());
        return;
    }

    QVector<QString> tempVect;

    tempVect = ItemsIDs_ItemsNamesVector;

    ItemsIDs_ItemsNamesVector.clear();

    do
    {
        tempVect.append(nullptr);

    }while(tempVect.size() < MerchantFieldNames.size());

    int counter = 0;

    for(int add = 0; add < tempVect.size(); add+=2)
    {
        counter++;

        QString ItemsID = tempVect.at(add);
        QString ItemsName = tempVect.at(add+1);

        QString Num = QString("%1").arg(counter,2,10,QLatin1Char('0'));

        Column_Name = "ItemsName_" + Num;

        qDebug() << "Column_Name" << Column_Name;

        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",ItemsName);
        query.bindValue(":id",PacketID);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }



        Column_Name = "ItemID_" + Num;

        qDebug() << "Column_Name" << Column_Name;

        query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE rowid = :id").arg(Table_Name).arg(Column_Name));
        query.bindValue(":val",ItemsID);
        query.bindValue(":id",PacketID);
        query.exec();

        if(!query.exec())
        {
            ui->lineEdit_20->setText(query.lastError().text());
            return;
        }
    }



    db.commit();
}

void MainWindow::on_lineEdit_348_textChanged(const QString &arg1)
{
    QString NPCsID = ui->lineEdit_59->text();

    QString List = ui->textEdit_28->toPlainText();

    if(!merchants::MerchantIDs_PacketIDsMap.contains(NPCsID) && arg1.isEmpty() == false && List.isEmpty() == false && clicked == false)
    {
        ui->pushButton_139->setStyleSheet("background-color: blue;" "color: white;");
        ui->pushButton_184->setStyleSheet("background-color: blue;" "color: white;");
    }

    if((clicked == true && arg1.isEmpty() == false) || (merchants::MerchantIDs_PacketIDsMap.contains(NPCsID) && arg1.isEmpty() == false))
    {
        ui->pushButton_3->setStyleSheet("background-color: blue;" "color: white;");
        ui->pushButton_184->setStyleSheet("background-color: blue;" "color: white;");
    }

    if(arg1.isEmpty() == true)
    {
        ui->pushButton_3->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_184->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_139->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_154->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    }
}

void MainWindow::on_textEdit_28_textChanged()
{
    QString arg1 = ui->textEdit_28->toPlainText();

    QString NPCsID = ui->lineEdit_59->text();

    QString Greeting = ui->lineEdit_348->text();

    if(!merchants::MerchantIDs_PacketIDsMap.contains(NPCsID) && arg1.isEmpty() == false && Greeting.isEmpty() == false && clicked == false)
    {
        ui->pushButton_139->setStyleSheet("background-color: blue;" "color: white;");
        ui->pushButton_184->setStyleSheet("background-color: blue;" "color: white;");
    }

    if((clicked == true && arg1.isEmpty() == false && Greeting.isEmpty() == false) ||
            (merchants::MerchantIDs_PacketIDsMap.contains(NPCsID) && arg1.isEmpty() == false && Greeting.isEmpty() == false))
    {
        ui->pushButton_3->setStyleSheet("background-color: blue;" "color: white;");
        ui->pushButton_184->setStyleSheet("background-color: blue;" "color: white;");
    }

    if(arg1.isEmpty() == true)
    {
        ui->pushButton_3->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_184->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_139->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_154->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    }
}

void MainWindow::on_pushButton_171_clicked()
{
    int row = ui->ShoppinglistWidget1->currentRow();
    ui->ShoppinglistWidget1->takeItem(row);
    ui->ShoppinglistWidget2->takeItem(row);

    ItemsIDs_ItemsNamesVector.removeAt(row*2);
    ItemsIDs_ItemsNamesVector.removeAt(row*2);


    ui->textEdit_28->clear();

    for(int re = 0; re < ItemsIDs_ItemsNamesVector.size(); re+=2)
    {
        QString ItemsID = ItemsIDs_ItemsNamesVector.at(re);
        QString ItemsName = ItemsIDs_ItemsNamesVector.at(re+1);

        ui->textEdit_28->append(ItemsID + " " + ItemsName);
    }

    QString NPCsID = ui->lineEdit_59->text();

    QString Greeting = ui->lineEdit_348->text();

    if(!merchants::MerchantIDs_PacketIDsMap.contains(NPCsID) && ItemsIDs_ItemsNamesVector.isEmpty() == false && Greeting.isEmpty() == false && clicked == false)
    {
        ui->pushButton_139->setStyleSheet("background-color: blue;" "color: white;");
        ui->pushButton_184->setStyleSheet("background-color: blue;" "color: white;");
    }

    if((clicked == true && ItemsIDs_ItemsNamesVector.isEmpty() == false && Greeting.isEmpty() == false) ||
            (merchants::MerchantIDs_PacketIDsMap.contains(NPCsID) && ItemsIDs_ItemsNamesVector.isEmpty() == false && Greeting.isEmpty() == false))
    {
        ui->pushButton_3->setStyleSheet("background-color: blue;" "color: white;");
        ui->pushButton_184->setStyleSheet("background-color: blue;" "color: white;");
    }

    if(ItemsIDs_ItemsNamesVector.isEmpty() == true)
    {
        ui->pushButton_3->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_184->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_139->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
        ui->pushButton_154->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    }
}

void MainWindow::on_pushButton_174_clicked()
{
    int ListSize = ui->ShoppinglistWidget1->count();
    int row = ui->ShoppinglistWidget1->currentRow();

    if(row > 0)
    {
        qDebug() << "Oldrow1" << ListSize;

        CurrentRow = row;
        CurrentRow--;

        QListWidgetItem *itemsName1 = ui->ShoppinglistWidget1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->ShoppinglistWidget2->takeItem(row);

        ui->ShoppinglistWidget1->insertItem(row-1,itemsName1);
        ui->ShoppinglistWidget2->insertItem(row-1,itemsID1);

        QString itemsID = ItemsIDs_ItemsNamesVector.takeAt(row*2);
        QString itemsName = ItemsIDs_ItemsNamesVector.takeAt(row*2);


        ItemsIDs_ItemsNamesVector.insert(row*2-2,itemsName);
        ItemsIDs_ItemsNamesVector.insert(row*2-2,itemsID);


        ui->ShoppinglistWidget1->setCurrentRow(CurrentRow);

        qDebug() << "NewRow1" << row;

        ui->textEdit_28->clear();

        for(int re = 0; re < ItemsIDs_ItemsNamesVector.size(); re+=2)
        {
            QString ItemsID = ItemsIDs_ItemsNamesVector.at(re);
            QString ItemsName = ItemsIDs_ItemsNamesVector.at(re+1);

            ui->textEdit_28->append(ItemsID + " " + ItemsName);
        }
    }




    qDebug() << "ListSize" << ListSize;
    //CurrentRow
}

void MainWindow::on_pushButton_175_clicked()
{
    int ListSize = ui->ShoppinglistWidget1->count();
    int row = ui->ShoppinglistWidget1->currentRow();

    if(row < ListSize -1 && row != -1)
    {
        qDebug() << "Oldrow2" << row;

        CurrentRow = row;
        CurrentRow++;

        QListWidgetItem *itemsName1 = ui->ShoppinglistWidget1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->ShoppinglistWidget2->takeItem(row);

        ui->ShoppinglistWidget1->insertItem(row+1,itemsName1);
        ui->ShoppinglistWidget2->insertItem(row+1,itemsID1);

        QString itemsID = ItemsIDs_ItemsNamesVector.takeAt(row*2);
        QString itemsName = ItemsIDs_ItemsNamesVector.takeAt(row*2);

        ItemsIDs_ItemsNamesVector.insert(row*2+2,itemsName);
        ItemsIDs_ItemsNamesVector.insert(row*2+2,itemsID);

        ui->ShoppinglistWidget1->setCurrentRow(CurrentRow);

        int row = ui->ShoppinglistWidget1->currentRow();

        qDebug() << "NewRow2" << row;

        ui->textEdit_28->clear();

        for(int re = 0; re < ItemsIDs_ItemsNamesVector.size(); re+=2)
        {
            QString ItemsID = ItemsIDs_ItemsNamesVector.at(re);
            QString ItemsName = ItemsIDs_ItemsNamesVector.at(re+1);

            ui->textEdit_28->append(ItemsID + " " + ItemsName);
        }
    }




    qDebug() << "ListSize" << ListSize;
    //CurrentRow
}

void MainWindow::on_checkBox_44_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(1,"IC_");
    }
    else
    {
        QuestCodeVector.replace(1,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_checkBox_45_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(3,"TC_");
    }
    else
    {
        QuestCodeVector.replace(3,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->lineEdit_234->setText(arg1);
}

void MainWindow::on_tableView_18_clicked(const QModelIndex &index)
{
    model18 = new QSqlTableModel(this);
    model18->setTable("QUEST_ID_RESULTS");
    model18->select();

    QString val1 = ui->tableView_18->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM QUEST_ID_RESULTS WHERE [PacketID] = '"+val1+"'"));

    ui->textEdit_36->clear();

    if(query1.exec())
    {
        while(query1.next())
        {
            ui->lineEdit_291->setText(query1.value(0).toString());
            ui->lineEdit_290->setText(query1.value(1).toString());
            ui->lineEdit_301->setText(query1.value(2).toString());
            ui->lineEdit_283->setText(query1.value(2).toString());

            ui->textEdit_36->append(query1.value(1).toString());
            ui->textEdit_36->append(query1.value(2).toString());

            QSqlRecord record = query1.record();

            for(int fd = 3; fd < record.count(); fd++)
            {
                QString ResultID = record.value(fd).toString();

                if(ResultID.isEmpty() == false)
                {
                    ui->textEdit_36->append(ResultID);
                }
                else
                {
                    break;
                }
            }
        }

        if(ui->checkBox_50->isChecked() == true)
        {
            ui->tabWidget_14->setCurrentIndex(7);
            ui->tabWidget_15->setCurrentIndex(5);
        }
    }


    model18->setTable("QUEST_ID_RESULTS");
    model18->select();
    ui->tableView_18->setModel(model18);
    ui->tableView_18->setColumnWidth(2,300);

    //----------------------------------------------------------------------------------------------
    QString LargeString = ui->textEdit_36->toPlainText();

    QStringList MyList = LargeString.split("\n");

    ui->textEdit_36->clear();

    ui->QuestResults_ListWidget_1->clear();
    ui->QuestResults_ListWidget_2->clear();

    for(int add = 0; add < MyList.size(); add++)
    {
        QString NewLine = MyList.at(add);

        if(NewLine.isEmpty() == false)
        {
            QString Table = "";
            QString Column = "";
            int value = 0;

            if(add != 1)
            {
                ui->textEdit_36->append(NewLine);
                ui->QuestResults_ListWidget_1->addItem(NewLine);
            }

            if(add >= 1)
            {
                if(NewLine.contains("M_") || NewLine.contains("P_") || NewLine.contains("QL_"))
                {
                    if(NewLine.contains("M_"))
                    {
                        Table = "QUEST_MENUS";
                        Column = "Menu_ID";
                        value = 2;
                    }

                    if(NewLine.contains("P_"))
                    {
                        Table = "QUEST_POPUPS";
                        Column = "Popup_ID";
                        value = 2;
                    }

                    if(NewLine.contains("QL_"))
                    {
                        Table = "QUEST_LOGS";
                        Column = "Log_Text_ID";
                        value = 2;

                        NewLine.remove(0,4);
                    }

                    query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
                    query1.bindValue(":val",NewLine);
                    query1.exec();

                    if(!query1.exec())
                    {
                        qDebug() << "query1.lastError()" << query1.lastError();
                    }

                    while(query1.next())
                    {
                        NewLine = query1.value(value).toString();
                    }
                }

                //IC_98F2808000#1
                if(NewLine.contains("IC_") || NewLine.contains("IT_") || NewLine.contains("IG_"))
                {
                    NewLine = Opcodes::ItemsID_ItemsName_Map.value(NewLine.mid(3,10));
                }

                //TS_279E0D00#55B9F308
                if(NewLine.contains("TS_"))
                {
                    NewLine = checkthezone::NPCsNames.value(NewLine.mid(3,8));
                }

                ui->QuestResults_ListWidget_2->addItem(NewLine);
            }
            else
            {
                if(add != 0)
                {
                    if(NewLine.contains("M_"))
                    {
                        Table = "QUEST_MENUS";
                        Column = "Menu_ID";
                        value = 2;

                        query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
                        query1.bindValue(":val",NewLine);
                        query1.exec();

                        if(query1.exec())
                        {
                            while(query1.next())
                            {
                                NewLine = query1.value(value).toString();
                            }
                        }
                    }

                    ui->QuestResults_ListWidget_2->addItem(NewLine);
                }
            }
        }
    }
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    model6 = new QSqlTableModel(this);
    model6->setTable("QUEST_TEXT");
    model6->select();
    ui->tableView_2->setModel(model6);
    ui->tableView_2->setColumnWidth(2,300);
}

void MainWindow::on_lineEdit_207_textChanged(const QString &arg1)
{
    ui->lineEdit_276->setText(arg1);
}

void MainWindow::on_checkBox_46_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QuestCodeVector.replace(25,"TS_");
    }
    else
    {
        QuestCodeVector.replace(25,"");
    }

    QuestCode.clear();

    for(int re = 0; re < QuestCodeVector.size(); re+=2)
    {
        QString Code = QuestCodeVector.at(re+1);

        if(Code.isEmpty() == false)
        {
            QuestCode.append(Code);
        }
    }

    ui->lineEdit_242->setText(QuestCode);
}

void MainWindow::on_lineEdit_246_textChanged(const QString &arg1)
{
    QString NPCS_Names = arg1;

    ui->lineEdit_347->setText(arg1);

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setFilter(QString("[Name (24 Max)] LIKE '%"+arg1+"%'"));
    model1->setSort(2, Qt::DescendingOrder);
    model1->select();
    ui->tableView_12->setModel(model1);

    if(arg1.isEmpty() == true)
    {
        model1->setTable("NPCS");
        model1->select();
        ui->tableView_12->setModel(model1);
    }
}

void MainWindow::on_tableView_12_clicked(const QModelIndex &index)
{
    ui->tabWidget_7->setCurrentIndex(1);

    model1 = new QSqlTableModel(this);
    model1->setTable("NPCS");
    model1->select();

    QString val1 = ui->tableView_12->model()->data(index).toString();
    QSqlQuery query1;
    query1.exec(QString("SELECT * FROM NPCS WHERE [Packet (8)] = '"+val1+"' or [ObjectID (4)] = '"+val1+"' or [Name (24 Max)] = '"+val1+"'"));


    if(query1.exec())
    {
        while(query1.next())
        {

            ui->lineEdit_347->setText(query1.value(1).toString());
            ui->lineEdit_59->setText(query1.value(5).toString());
            ui->lineEdit_246->setText(query1.value(1).toString());
            ui->lineEdit_244->setText(query1.value(5).toString());
        }
    }

    model1->setTable("NPCS");
    model1->select();
    ui->tableView_12->setModel(model1);
}

void MainWindow::on_lineEdit_247_textChanged(const QString &arg1)
{
    int val = arg1.toInt(nullptr,10);
    ui->spinBox_4->setValue(val);
}


void MainWindow::on_pushButton_184_clicked()
{
    CopyMyGreeting = ui->lineEdit_348->text();

    QString LargeString = ui->textEdit_28->toPlainText();

    CopyMyList = LargeString.split("\n");

    ui->pushButton_184->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");
    ui->pushButton_186->setStyleSheet("background-color: blue;" "color: white;");
}


void MainWindow::on_pushButton_186_clicked()
{
    ui->pushButton_186->setStyleSheet("background-color: rgba(232, 232, 232);" "color: black;");

    ItemsIDs_ItemsNamesVector.clear();
    ui->textEdit_28->clear();

    ui->ShoppinglistWidget1->clear();
    ui->ShoppinglistWidget2->clear();

    QVector<QString> FieldValues;

    for(int add = 0; add < CopyMyList.size(); add++)
    {
        QString NewLine = CopyMyList.at(add);

        if(NewLine.isEmpty() == false)
        {
            int index1 = NewLine.indexOf(" ");

            QString ItemsID = NewLine.mid(0,index1);
            QString ItemsName = NewLine.mid(index1+1,NewLine.size());

            qDebug() << "";
            qDebug() << "ItemsID" << ItemsID;
            qDebug() << "ItemsName" << ItemsName;

            if(merchants::Items_Map.contains(ItemsID))
            {
                FieldValues.append(ItemsID);

                ItemsIDs_ItemsNamesVector.append(ItemsID);
                ItemsIDs_ItemsNamesVector.append(ItemsName);

                ui->textEdit_28->append(ItemsID + " " + ItemsName);

                ui->ShoppinglistWidget1->addItem(ItemsName);
                ui->ShoppinglistWidget2->addItem(ItemsID);
            }
        }
    }

    ui->lineEdit_348->setText(CopyMyGreeting);
}


void MainWindow::on_pushButton_188_clicked()
{
    on_pushButton_158_clicked();
}


void MainWindow::on_pushButton_189_clicked()
{
    int time = ui->lineEdit_AggroTimer->text().toInt(nullptr,10);
    aggroTimer.start(time);
}


void MainWindow::on_lineEdit_AggroTimer_textChanged(const QString &arg1)
{
    if(aggroTimer.isActive())
    {
        aggroTimer.stop();
    }

    int value = arg1.toInt(nullptr,10);

    ui->spinBox_5->setValue(value);
}


void MainWindow::on_spinBox_5_valueChanged(const QString &arg1)
{
    ui->lineEdit_AggroTimer->setText(arg1);
}


void MainWindow::on_pushButton_190_clicked()
{
    QString val1 = ui->lineEdit_235->text();
    QString val2 = ui->lineEdit_229->text();
    QString val3 = ui->lineEdit_236->text();

    ui->lineEdit_274->setText(val1);
    ui->lineEdit_273->setText(val2);
    ui->lineEdit_275->setText(val3);

    ui->checkBox_28->setChecked(true);
    ui->checkBox_41->setChecked(true);
}


void MainWindow::on_pushButton_200_clicked()
{
    int row = ui->Menu_ListWidget_2->currentRow();

    if(row > 2)
    {
        CurrentRow = row;
        CurrentRow--;

        QListWidgetItem *itemsName1 = ui->Menu_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->Menu_ListWidget_2->takeItem(row);

        ui->Menu_ListWidget_1->insertItem(row-1,itemsName1);
        ui->Menu_ListWidget_2->insertItem(row-1,itemsID1);


        ui->Menu_ListWidget_1->setCurrentRow(CurrentRow);
        ui->Menu_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_29->clear();

        for(int re = 0; re < ui->Menu_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->Menu_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_29->append(Text);
        }
    }
}


void MainWindow::on_pushButton_199_clicked()
{
    int ListSize = ui->Menu_ListWidget_2->count();
    int row = ui->Menu_ListWidget_2->currentRow();

    if(row < ListSize -1 && row != -1 && row > 1)
    {
        CurrentRow = row;
        CurrentRow++;

        QListWidgetItem *itemsName1 = ui->Menu_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->Menu_ListWidget_2->takeItem(row);

        ui->Menu_ListWidget_1->insertItem(row+1,itemsName1);
        ui->Menu_ListWidget_2->insertItem(row+1,itemsID1);

        ui->Menu_ListWidget_1->setCurrentRow(CurrentRow);
        ui->Menu_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_29->clear();

        for(int re = 0; re < ui->Menu_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->Menu_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_29->append(Text);
        }
    }
}


void MainWindow::on_pushButton_201_clicked()
{
    int row = ui->Menu_ListWidget_2->currentRow();
    ui->Menu_ListWidget_1->takeItem(row);
    ui->Menu_ListWidget_2->takeItem(row);

    ui->textEdit_29->clear();

    for(int re = 0; re < ui->Menu_ListWidget_2->count(); re++)
    {
        QListWidgetItem *itemsName1 = ui->Menu_ListWidget_1->item(re);

        QString Text = itemsName1->text();

        ui->textEdit_29->append(Text);
    }
}

void MainWindow::on_Menu_ListWidget_1_itemDoubleClicked()
{
    int currentRow = ui->Menu_ListWidget_1->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->Menu_ListWidget_1->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_278->setText(Text);
    }

    M_ids = true;

    if(M_text == true)
    {
        M_text = false;
    }

}

void MainWindow::on_Menu_ListWidget_2_itemDoubleClicked()
{
    int currentRow = ui->Menu_ListWidget_2->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->Menu_ListWidget_2->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_278->setText(Text);
    }


    M_text = true;

    if(M_ids == true)
    {
        M_ids = false;
    }

}

void MainWindow::on_pushButton_159_clicked()
{
    if(M_text == true)
    {
        QListWidgetItem *itemsName1 = ui->Menu_ListWidget_2->item(CurrentRow);

        QString Text = ui->lineEdit_278->text();

        itemsName1->setText(Text);

        M_text = false;
    }

    if(M_ids == true)
    {
        QListWidgetItem *itemsName1 = ui->Menu_ListWidget_1->item(CurrentRow);

        ui->Menu_ListWidget_2->setCurrentRow(CurrentRow);

        QString Text = ui->lineEdit_278->text();

        itemsName1->setText(Text);

        M_ids = false;

        QSqlQuery query1;
        query1.exec(QString("SELECT * FROM QUEST_MENUS_OPTIONS WHERE [Option_ID] = '"+Text+"'"));

        if(query1.exec())
        {
            while(query1.next())
            {
                Text = query1.value(3).toString();
            }
        }

        QListWidgetItem *itemsName2 = ui->Menu_ListWidget_2->item(CurrentRow);
        itemsName2->setText(Text);
    }
}

void MainWindow::on_pushButton_160_clicked()
{
    int count1 = ui->Menu_ListWidget_1->count();

    if(count1 > 0)
    {
        int Packet_ID2 = ui->lineEdit_264->text().toInt(nullptr,10);

        db.transaction();

        QSqlQuery query;
        query.prepare (QString ("SELECT * FROM QUEST_MENUS WHERE rowid = :val"));
        query.bindValue(":val",Packet_ID2);
        query.exec();

        QVector<QString> OldMenuVect;

        QString OldHeader = "";

        while(query.next())
        {
            QSqlRecord record = query.record();

            OldHeader = record.value(2).toString();

            for(int fd = 3; fd < record.count(); fd+=2)
            {
                QString OptionsID = record.value(fd).toString();
                QString OptionsText = record.value(fd+1).toString();

                if(OptionsID.isEmpty() == false)
                {
                    OldMenuVect.append(OptionsID);
                    OldMenuVect.append(OptionsText);
                }
                else
                {
                    break;
                }
            }
        }     

        ui->textEdit_29->clear();
        QVector<QString> NewMenuVect;

        for(int re = 2; re < ui->Menu_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsID = ui->Menu_ListWidget_1->item(re);
            QString items_ID = itemsID->text();

            QListWidgetItem *itemsText = ui->Menu_ListWidget_2->item(re);
            QString Items_Text = itemsText->text();

            NewMenuVect.append(items_ID);
            NewMenuVect.append(Items_Text);
        }

        if(NewMenuVect.size() < OldMenuVect.size())
        {
            do
            {
                NewMenuVect.append(nullptr);

            }while(NewMenuVect.size() < OldMenuVect.size());
        }

        if(NewMenuVect.size() > OldMenuVect.size())
        {
            do
            {
                OldMenuVect.append(nullptr);

            }while(NewMenuVect.size() > OldMenuVect.size());
        }

        int counter = 0;

        qDebug() << "";
        qDebug() << "OldMenuVect" << OldMenuVect;
        qDebug() << "NewMenuVect" << NewMenuVect;

        for(int add = 0; add < NewMenuVect.size(); add+=2)
        {
            QString OldOptionID = OldMenuVect.at(add);
            QString OldOptionText = OldMenuVect.at(add+1);

            QString NewOptionID = NewMenuVect.at(add);
            QString NewOptionText = NewMenuVect.at(add+1);

            qDebug() << "OldOptionID" << OldOptionID;
            qDebug() << "OldOptionText" << OldOptionText;

            qDebug() << "NewOptionID" << NewOptionID;
            qDebug() << "NewOptionText" << NewOptionText;


            counter++;

            QString Num1 = QString("%1").arg(counter,2,10,QLatin1Char('0')).toUpper();

            Table_Name = "QUEST_MENUS";

            if((NewOptionID != OldOptionID && NewOptionID.isEmpty() == false))
            {
                Column_Name = "Option_ID_" + Num1;

                qDebug() << "Column_Name" << Column_Name;

                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",NewOptionID);
                query.bindValue(":id",Packet_ID2);
                query.exec();

                Column_Name = "Option_Text_" + Num1;

                qDebug() << "Column_Name" << Column_Name;

                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",NewOptionText);
                query.bindValue(":id",Packet_ID2);
                query.exec();
            }

            db.commit();

        }
    }
}



void MainWindow::on_pushButton_204_clicked()
{
    int row = ui->Option_ListWidget_2->currentRow();

    if(row > 2)
    {
        CurrentRow = row;
        CurrentRow--;

        QListWidgetItem *itemsName1 = ui->Option_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->Option_ListWidget_2->takeItem(row);

        ui->Option_ListWidget_1->insertItem(row-1,itemsName1);
        ui->Option_ListWidget_2->insertItem(row-1,itemsID1);


        ui->Option_ListWidget_1->setCurrentRow(CurrentRow);
        ui->Option_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_32->clear();

        for(int re = 0; re < ui->Option_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->Option_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_32->append(Text);
        }
    }
}


void MainWindow::on_pushButton_203_clicked()
{
    int ListSize = ui->Option_ListWidget_2->count();
    int row = ui->Option_ListWidget_2->currentRow();

    if(row < ListSize -1 && row != -1 && row > 1)
    {
        CurrentRow = row;
        CurrentRow++;

        QListWidgetItem *itemsName1 = ui->Option_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->Option_ListWidget_2->takeItem(row);

        ui->Option_ListWidget_1->insertItem(row+1,itemsName1);
        ui->Option_ListWidget_2->insertItem(row+1,itemsID1);

        ui->Option_ListWidget_1->setCurrentRow(CurrentRow);
        ui->Option_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_32->clear();

        for(int re = 0; re < ui->Option_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->Option_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_32->append(Text);
        }
    }
}


void MainWindow::on_pushButton_202_clicked()
{
    int row = ui->Option_ListWidget_2->currentRow();
    ui->Option_ListWidget_1->takeItem(row);
    ui->Option_ListWidget_2->takeItem(row);

    ui->textEdit_32->clear();

    for(int re = 0; re < ui->Option_ListWidget_2->count(); re++)
    {
        QListWidgetItem *itemsName1 = ui->Option_ListWidget_1->item(re);

        QString Text = itemsName1->text();

        ui->textEdit_32->append(Text);
    }
}

void MainWindow::on_Option_ListWidget_1_itemDoubleClicked()
{
    int currentRow = ui->Option_ListWidget_1->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->Option_ListWidget_1->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_279->setText(Text);
    }

    O_ids = true;

    if(O_text == true)
    {
        O_text = false;
    }
}


void MainWindow::on_Option_ListWidget_2_itemDoubleClicked()
{
    int currentRow = ui->Option_ListWidget_2->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->Option_ListWidget_2->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_279->setText(Text);
    }

    O_text = true;

    if(O_ids == true)
    {
        O_ids = false;
    }
}


void MainWindow::on_pushButton_218_clicked()
{
    if(O_text == true)
    {
        QListWidgetItem *itemsName1 = ui->Option_ListWidget_2->item(CurrentRow);

        QString Text = ui->lineEdit_279->text();

        itemsName1->setText(Text);

        O_text = false;
    }

    if(O_ids == true)
    {
        QListWidgetItem *itemsName1 = ui->Option_ListWidget_1->item(CurrentRow);

        ui->Option_ListWidget_2->setCurrentRow(CurrentRow);

        QString NewLine = ui->lineEdit_279->text();

        itemsName1->setText(NewLine);

        O_ids = false;

        QSqlQuery query1;
        QString Table = "";
        QString Column = "";
        int value = 0;


        if(NewLine.contains("M_") || NewLine.contains("O_")  || NewLine.contains("P_") || NewLine.contains("QL_"))
        {
            if(NewLine.contains("M_"))
            {
                Table = "QUEST_MENUS";
                Column = "Menu_ID";
                value = 2;
            }

            if(NewLine.contains("O_"))
            {
                Table = "QUEST_MENUS_OPTIONS";
                Column = "Option_ID";
                value = 3;
            }

            if(NewLine.contains("P_"))
            {
                Table = "QUEST_POPUPS";
                Column = "Popup_ID";
                value = 2;
            }

            if(NewLine.contains("QL_"))
            {
                Table = "QUEST_LOGS";
                Column = "Log_Text_ID";
                value = 2;

                NewLine.remove(0,4);
            }

            query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
            query1.bindValue(":val",NewLine);
            query1.exec();

            if(!query1.exec())
            {
                qDebug() << "query1.lastError()" << query1.lastError();
            }

            while(query1.next())
            {
                NewLine = query1.value(value).toString();
            }
        }

        QListWidgetItem *itemsName2 = ui->Option_ListWidget_2->item(CurrentRow);
        itemsName2->setText(NewLine);
    }
}


void MainWindow::on_pushButton_217_clicked()
{
    int count1 = ui->Option_ListWidget_1->count();

    if(count1 > 0)
    {
        int Packet_ID2 = ui->lineEdit_271->text().toInt(nullptr,10);

        db.transaction();

        QSqlQuery query;
        query.prepare (QString ("SELECT * FROM QUEST_MENUS_OPTIONS WHERE rowid = :val"));
        query.bindValue(":val",Packet_ID2);
        query.exec();

        QVector<QString> OldResultVect;

        QString OldMenuID = "";
        QString OldOptionID = "";
        QString OldHeader = "";

        while(query.next())
        {
            QSqlRecord record = query.record();

            OldMenuID = record.value(1).toString();
            OldOptionID = record.value(2).toString();
            OldHeader = record.value(3).toString();

            for(int fd = 4; fd < record.count(); fd++)
            {
                QString ResultID = record.value(fd).toString();

                if(ResultID.isEmpty() == false)
                {
                    OldResultVect.append(ResultID);
                }
                else
                {
                    break;
                }
            }
        }

        QListWidgetItem *itemsID0 = ui->Option_ListWidget_1->item(0);
        QString NewMenuID = itemsID0->text();

        Table_Name = "QUEST_MENUS_OPTIONS";

        if(OldMenuID != NewMenuID && NewMenuID.isEmpty() == false)
        {
            Column_Name = "Menu_ID";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewMenuID);
            query.bindValue(":id",Packet_ID2);
            query.exec();

        }

        QListWidgetItem *itemsID1 = ui->Option_ListWidget_1->item(1);
        QString NewOptionID = itemsID1->text();

        if(OldOptionID != NewOptionID && NewOptionID.isEmpty() == false)
        {
            Column_Name = "Option_ID";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewOptionID);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        QListWidgetItem *itemsID2 = ui->Option_ListWidget_2->item(1);
        QString NewHeader = itemsID2->text();

        if(OldHeader != NewHeader && NewHeader.isEmpty() == false)
        {
            Column_Name = "Option_Text";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewHeader);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }



        ui->textEdit_32->clear();
        QVector<QString> NewResultVect;

        for(int re = 2; re < ui->Option_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsID = ui->Option_ListWidget_1->item(re);
            QString items_ID = itemsID->text();

            NewResultVect.append(items_ID);
        }

        if(NewResultVect.size() < OldResultVect.size())
        {
            do
            {
                NewResultVect.append(nullptr);

            }while(NewResultVect.size() < OldResultVect.size());
        }

        if(NewResultVect.size() > OldResultVect.size())
        {
            do
            {
                OldResultVect.append(nullptr);

            }while(NewResultVect.size() > OldResultVect.size());
        }

        qDebug() << "";
        qDebug() << "OldResultVect" << OldResultVect;
        qDebug() << "NewResultVect" << NewResultVect;

        for(int add = 0; add < NewResultVect.size(); add++)
        {
            QString OldResultID = OldResultVect.at(add);

            QString NewResultID = NewResultVect.at(add);

            qDebug() << "";
            qDebug() << "OldResultID" << OldResultID;

            qDebug() << "NewResultID" << NewResultID;


            if(OldResultID.isEmpty() == true && NewResultID.isEmpty() == true)
            {
                break;
            }

            QString Num1 = QString("%1").arg(add+1,2,10,QLatin1Char('0')).toUpper();

            if((NewResultID != OldResultID))
            {
                Column_Name = "Option_Result_" + Num1;

                qDebug() << "Column_Name" << Column_Name;

                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",NewResultID);
                query.bindValue(":id",Packet_ID2);
                query.exec();
            }

            db.commit();

        }
    }
}


void MainWindow::on_pushButton_206_clicked()
{
    int row = ui->PopUp_ListWidget_2->currentRow();

    if(row > 1)
    {
        CurrentRow = row;
        CurrentRow--;

        QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->PopUp_ListWidget_2->takeItem(row);

        ui->PopUp_ListWidget_1->insertItem(row-1,itemsName1);
        ui->PopUp_ListWidget_2->insertItem(row-1,itemsID1);


        ui->PopUp_ListWidget_1->setCurrentRow(CurrentRow);
        ui->PopUp_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_33->clear();

        for(int re = 0; re < ui->PopUp_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_33->append(Text);
        }
    }
}


void MainWindow::on_pushButton_205_clicked()
{
    int ListSize = ui->PopUp_ListWidget_2->count();
    int row = ui->PopUp_ListWidget_2->currentRow();

    if(row < ListSize -1 && row != -1 && row > 0)
    {
        CurrentRow = row;
        CurrentRow++;

        QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->PopUp_ListWidget_2->takeItem(row);

        ui->PopUp_ListWidget_1->insertItem(row+1,itemsName1);
        ui->PopUp_ListWidget_2->insertItem(row+1,itemsID1);

        ui->PopUp_ListWidget_1->setCurrentRow(CurrentRow);
        ui->PopUp_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_33->clear();

        for(int re = 0; re < ui->PopUp_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_33->append(Text);
        }
    }
}


void MainWindow::on_pushButton_207_clicked()
{
    int row = ui->PopUp_ListWidget_2->currentRow();
    ui->PopUp_ListWidget_1->takeItem(row);
    ui->PopUp_ListWidget_2->takeItem(row);

    ui->textEdit_33->clear();

    for(int re = 0; re < ui->PopUp_ListWidget_2->count(); re++)
    {
        QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_1->item(re);

        QString Text = itemsName1->text();

        ui->textEdit_33->append(Text);
    }
}


void MainWindow::on_PopUp_ListWidget_1_itemDoubleClicked()
{
    int currentRow = ui->PopUp_ListWidget_1->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_1->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_280->setText(Text);
    }

    P_ids = true;

    if(P_text == true)
    {
        P_text = false;
    }
}


void MainWindow::on_PopUp_ListWidget_2_itemDoubleClicked()
{
    int currentRow = ui->PopUp_ListWidget_2->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_2->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_280->setText(Text);
    }

    P_text = true;

    if(P_ids == true)
    {
        P_ids = false;
    }
}


void MainWindow::on_pushButton_220_clicked()
{
    if(P_text == true)
    {
        QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_2->item(CurrentRow);

        QString Text = ui->lineEdit_280->text();

        itemsName1->setText(Text);

        P_text = false;
    }

    if(P_ids == true)
    {
        QListWidgetItem *itemsName1 = ui->PopUp_ListWidget_1->item(CurrentRow);

        ui->PopUp_ListWidget_2->setCurrentRow(CurrentRow);

        QString NewLine = ui->lineEdit_280->text();

        itemsName1->setText(NewLine);

        P_ids = false;

        QSqlQuery query1;
        QString Table = "";
        QString Column = "";
        int value = 0;


        if(NewLine.contains("M_") || NewLine.contains("P_") || NewLine.contains("QL_"))
        {
            if(NewLine.contains("M_"))
            {
                Table = "QUEST_MENUS";
                Column = "Menu_ID";
                value = 2;
            }

            if(NewLine.contains("P_"))
            {
                Table = "QUEST_POPUPS";
                Column = "Popup_ID";
                value = 2;
            }

            if(NewLine.contains("QL_"))
            {
                Table = "QUEST_LOGS";
                Column = "Log_Text_ID";
                value = 2;

                NewLine.remove(0,4);
            }

            query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
            query1.bindValue(":val",NewLine);
            query1.exec();

            if(!query1.exec())
            {
                qDebug() << "query1.lastError()" << query1.lastError();
            }

            while(query1.next())
            {
                NewLine = query1.value(value).toString();
            }
        }

        QListWidgetItem *itemsName2 = ui->PopUp_ListWidget_2->item(CurrentRow);
        itemsName2->setText(NewLine);
    }
}


void MainWindow::on_pushButton_219_clicked()
{
    int count1 = ui->PopUp_ListWidget_1->count();

    if(count1 > 0)
    {
        int Packet_ID2 = ui->lineEdit_285->text().toInt(nullptr,10);

        db.transaction();

        QSqlQuery query;
        query.prepare (QString ("SELECT * FROM QUEST_POPUPS WHERE rowid = :val"));
        query.bindValue(":val",Packet_ID2);
        query.exec();

        QVector<QString> OldResultVect;

        QString OldPopUpID = "";
        QString OldHeader = "";

        while(query.next())
        {
            QSqlRecord record = query.record();

            OldPopUpID = record.value(1).toString();
            OldHeader = record.value(2).toString();

            for(int fd = 3; fd < record.count(); fd++)
            {
                QString ResultID = record.value(fd).toString();

                if(ResultID.isEmpty() == false)
                {
                    OldResultVect.append(ResultID);
                }
                else
                {
                    break;
                }
            }
        }

        Table_Name = "QUEST_POPUPS";

        QListWidgetItem *itemsID1 = ui->PopUp_ListWidget_1->item(0);
        QString NewPopUpID = itemsID1->text();

        if(OldPopUpID != NewPopUpID && NewPopUpID.isEmpty() == false)
        {
            Column_Name = "Popup_ID";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewPopUpID);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        QListWidgetItem *itemsID2 = ui->PopUp_ListWidget_2->item(0);
        QString NewHeader = itemsID2->text();

        if(OldHeader != NewHeader && NewHeader.isEmpty() == false)
        {
            Column_Name = "Popup_Text";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewHeader);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        ui->textEdit_33->clear();
        QVector<QString> NewResultVect;

        for(int re = 1; re < ui->PopUp_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsID = ui->PopUp_ListWidget_1->item(re);
            QString items_ID = itemsID->text();

            NewResultVect.append(items_ID);
        }

        if(NewResultVect.size() < OldResultVect.size())
        {
            do
            {
                NewResultVect.append(nullptr);

            }while(NewResultVect.size() < OldResultVect.size());
        }

        if(NewResultVect.size() > OldResultVect.size())
        {
            do
            {
                OldResultVect.append(nullptr);

            }while(NewResultVect.size() > OldResultVect.size());
        }

        qDebug() << "";
        qDebug() << "OldResultVect" << OldResultVect;
        qDebug() << "NewResultVect" << NewResultVect;

        for(int add = 0; add < NewResultVect.size(); add++)
        {
            QString OldResultID = OldResultVect.at(add);

            QString NewResultID = NewResultVect.at(add);

            qDebug() << "";
            qDebug() << "OldResultID" << OldResultID;

            qDebug() << "NewResultID" << NewResultID;


            if(OldResultID.isEmpty() == true && NewResultID.isEmpty() == true)
            {
                break;
            }

            QString Num1 = QString("%1").arg(add+1,2,10,QLatin1Char('0')).toUpper();

            if((NewResultID != OldResultID))
            {
                Column_Name = "Popup_Result_" + Num1;

                qDebug() << "Column_Name" << Column_Name;

                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",NewResultID);
                query.bindValue(":id",Packet_ID2);
                query.exec();
            }

            db.commit();

        }
    }
}


void MainWindow::on_QuestLog_ListWidget_1_itemDoubleClicked()
{
    int currentRow = ui->QuestLog_ListWidget_1->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->QuestLog_ListWidget_1->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_281->setText(Text);
    }

    QL_ids = true;

    if(QL_text == true)
    {
        QL_text = false;
    }
}


void MainWindow::on_QuestLog_ListWidget_2_itemDoubleClicked()
{
    int currentRow = ui->QuestLog_ListWidget_2->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->QuestLog_ListWidget_2->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_281->setText(Text);
    }

    QL_text = true;

    if(QL_ids == true)
    {
        QL_ids = false;
    }
}


void MainWindow::on_pushButton_222_clicked()
{
    if(QL_text == true)
    {
        QListWidgetItem *itemsName1 = ui->QuestLog_ListWidget_2->item(CurrentRow);

        QString Text = ui->lineEdit_281->text();

        itemsName1->setText(Text);

        QL_text = false;
    }

    if(QL_ids == true)
    {
        QListWidgetItem *itemsName1 = ui->QuestLog_ListWidget_1->item(CurrentRow);

        ui->QuestLog_ListWidget_2->setCurrentRow(CurrentRow);

        QString NewLine = ui->lineEdit_281->text();

        itemsName1->setText(NewLine);

        QL_ids = false;

        QSqlQuery query1;
        QString Table = "";
        QString Column = "";
        int value = 0;


        if(NewLine.contains("QL_"))
        {
            if(NewLine.contains("QL_"))
            {
                Table = "QUEST_LOGS";
                Column = "Log_Text_ID";
                value = 2;
            }

            query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
            query1.bindValue(":val",NewLine);
            query1.exec();

            if(!query1.exec())
            {
                qDebug() << "query1.lastError()" << query1.lastError();
            }

            while(query1.next())
            {
                NewLine = query1.value(value).toString();
            }
        }

        QListWidgetItem *itemsName2 = ui->QuestLog_ListWidget_2->item(CurrentRow);
        itemsName2->setText(NewLine);
    }
}


void MainWindow::on_pushButton_221_clicked()
{
    int count1 = ui->QuestLog_ListWidget_1->count();

    if(count1 > 0)
    {
        int Packet_ID2 = ui->lineEdit_287->text().toInt(nullptr,10);

        db.transaction();

        QSqlQuery query;
        query.prepare (QString ("SELECT * FROM QUEST_LOGS WHERE rowid = :val"));
        query.bindValue(":val",Packet_ID2);
        query.exec();

        QVector<QString> OldResultVect;

        QString OldQuestLogID = "";
        QString OldHeader = "";

        while(query.next())
        {
            QSqlRecord record = query.record();

            OldQuestLogID = record.value(1).toString();
            OldHeader = record.value(2).toString();
        }

        Table_Name = "QUEST_LOGS";

        QListWidgetItem *itemsID1 = ui->QuestLog_ListWidget_1->item(0);
        QString NewQuestLogID = itemsID1->text();

        if(OldQuestLogID != NewQuestLogID && NewQuestLogID.isEmpty() == false)
        {
            Column_Name = "Log_Text_ID";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewQuestLogID);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        QListWidgetItem *itemsID2 = ui->QuestLog_ListWidget_2->item(0);
        QString NewHeader = itemsID2->text();

        if(OldHeader != NewHeader && NewHeader.isEmpty() == false)
        {
            Column_Name = "Log_Text";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewHeader);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        db.commit();

        ui->textEdit_34->clear();


    }
}

//-------------------------------------------------------------------------

void MainWindow::on_Description_ListWidget_1_itemDoubleClicked()
{
    int currentRow = ui->Description_ListWidget_1->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->Description_ListWidget_1->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_282->setText(Text);
    }

    D_ids = true;

    if(D_text == true)
    {
        D_text = false;
    }
}


void MainWindow::on_Description_ListWidget_2_itemDoubleClicked()
{
    int currentRow = ui->Description_ListWidget_2->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->Description_ListWidget_2->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_282->setText(Text);
    }

    D_text = true;

    if(D_ids == true)
    {
        D_ids = false;
    }
}


void MainWindow::on_pushButton_224_clicked()
{
    if(D_text == true)
    {
        QListWidgetItem *itemsName1 = ui->Description_ListWidget_2->item(CurrentRow);

        QString Text = ui->lineEdit_282->text();

        itemsName1->setText(Text);

        D_text = false;
    }

    if(D_ids == true)
    {
        QListWidgetItem *itemsName1 = ui->Description_ListWidget_1->item(CurrentRow);

        ui->Description_ListWidget_2->setCurrentRow(CurrentRow);

        QString NewLine = ui->lineEdit_282->text();

        itemsName1->setText(NewLine);

        D_ids = false;

        QSqlQuery query1;
        QString Table = "";
        QString Column = "";
        int value = 0;


        if(NewLine.contains("QD_"))
        {
            if(NewLine.contains("QD_"))
            {
                Table = "QUEST_DESCRIPTIONS";
                Column = "Description_Text_ID";
                value = 2;
            }

            query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
            query1.bindValue(":val",NewLine);
            query1.exec();

            if(!query1.exec())
            {
                qDebug() << "query1.lastError()" << query1.lastError();
            }

            while(query1.next())
            {
                NewLine = query1.value(value).toString();
            }
        }

        QListWidgetItem *itemsName2 = ui->Description_ListWidget_2->item(CurrentRow);
        itemsName2->setText(NewLine);
    }
}


void MainWindow::on_pushButton_223_clicked()
{
    int count1 = ui->Description_ListWidget_1->count();

    if(count1 > 0)
    {
        int Packet_ID2 = ui->lineEdit_289->text().toInt(nullptr,10);

        db.transaction();

        QSqlQuery query;
        query.prepare (QString ("SELECT * FROM QUEST_DESCRIPTIONS WHERE rowid = :val"));
        query.bindValue(":val",Packet_ID2);
        query.exec();

        QVector<QString> OldResultVect;

        QString OldDescriptionID = "";
        QString OldHeader = "";

        while(query.next())
        {
            QSqlRecord record = query.record();

            OldDescriptionID = record.value(1).toString();
            OldHeader = record.value(2).toString();
        }

        Table_Name = "QUEST_DESCRIPTIONS";

        QListWidgetItem *itemsID1 = ui->Description_ListWidget_1->item(0);
        QString NewDescriptionID = itemsID1->text();

        if(OldDescriptionID != NewDescriptionID && NewDescriptionID.isEmpty() == false)
        {
            Column_Name = "Description_Text_ID";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewDescriptionID);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        QListWidgetItem *itemsID2 = ui->Description_ListWidget_2->item(0);
        QString NewHeader = itemsID2->text();

        if(OldHeader != NewHeader && NewHeader.isEmpty() == false)
        {
            Column_Name = "Description_Text";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewHeader);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        db.commit();

        ui->textEdit_35->clear();
    }
}


//-----------------------------------------------------------------------------------------

void MainWindow::on_pushButton_215_clicked()
{
    int row = ui->QuestResults_ListWidget_2->currentRow();

    if(row > 1)
    {
        CurrentRow = row;
        CurrentRow--;

        QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->QuestResults_ListWidget_2->takeItem(row);

        ui->QuestResults_ListWidget_1->insertItem(row-1,itemsName1);
        ui->QuestResults_ListWidget_2->insertItem(row-1,itemsID1);


        ui->QuestResults_ListWidget_1->setCurrentRow(CurrentRow);
        ui->QuestResults_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_36->clear();

        for(int re = 0; re < ui->QuestResults_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_36->append(Text);
        }
    }
}


void MainWindow::on_pushButton_214_clicked()
{
    int ListSize = ui->QuestResults_ListWidget_2->count();
    int row = ui->QuestResults_ListWidget_2->currentRow();

    if(row < ListSize -1 && row != -1 && row > 0)
    {
        CurrentRow = row;
        CurrentRow++;

        QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_1->takeItem(row);
        QListWidgetItem *itemsID1 = ui->QuestResults_ListWidget_2->takeItem(row);

        ui->QuestResults_ListWidget_1->insertItem(row+1,itemsName1);
        ui->QuestResults_ListWidget_2->insertItem(row+1,itemsID1);

        ui->QuestResults_ListWidget_1->setCurrentRow(CurrentRow);
        ui->QuestResults_ListWidget_2->setCurrentRow(CurrentRow);

        ui->textEdit_36->clear();

        for(int re = 0; re < ui->QuestResults_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_1->item(CurrentRow);

            QString Text = itemsName1->text();

            ui->textEdit_36->append(Text);
        }
    }
}


void MainWindow::on_pushButton_216_clicked()
{
    int row = ui->QuestResults_ListWidget_2->currentRow();
    ui->QuestResults_ListWidget_1->takeItem(row);
    ui->QuestResults_ListWidget_2->takeItem(row);

    ui->textEdit_36->clear();

    for(int re = 0; re < ui->QuestResults_ListWidget_2->count(); re++)
    {
        QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_1->item(re);

        QString Text = itemsName1->text();

        ui->textEdit_36->append(Text);
    }
}


void MainWindow::on_QuestResults_ListWidget_1_itemDoubleClicked()
{
    int currentRow = ui->QuestResults_ListWidget_1->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_1->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_283->setText(Text);
    }

    QR_ids = true;

    if(QR_text == true)
    {
        QR_text = false;
    }
}


void MainWindow::on_QuestResults_ListWidget_2_itemDoubleClicked()
{
    int currentRow = ui->QuestResults_ListWidget_2->currentRow();

    if(currentRow != -1)
    {
        CurrentRow = currentRow;

        QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_2->item(CurrentRow);

        QString Text = itemsName1->text();

        ui->lineEdit_283->setText(Text);
    }

    QR_text = true;

    if(QR_ids == true)
    {
        QR_ids = false;
    }
}


void MainWindow::on_pushButton_226_clicked()
{
    if(QR_text == true)
    {
        QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_2->item(CurrentRow);

        QString Text = ui->lineEdit_283->text();

        itemsName1->setText(Text);

        QR_text = false;
    }

    if(QR_ids == true)
    {
        QListWidgetItem *itemsName1 = ui->QuestResults_ListWidget_1->item(CurrentRow);

        ui->QuestResults_ListWidget_2->setCurrentRow(CurrentRow);

        QString NewLine = ui->lineEdit_283->text();

        itemsName1->setText(NewLine);

        QR_ids = false;

        QSqlQuery query1;
        QString Table = "";
        QString Column = "";
        int value = 0;


        if(NewLine.contains("M_") || NewLine.contains("P_") || NewLine.contains("QL_"))
        {
            if(NewLine.contains("M_"))
            {
                Table = "QUEST_MENUS";
                Column = "Menu_ID";
                value = 2;
            }

            if(NewLine.contains("P_"))
            {
                Table = "QUEST_POPUPS";
                Column = "Popup_ID";
                value = 2;
            }

            if(NewLine.contains("QL_"))
            {
                Table = "QUEST_LOGS";
                Column = "Log_Text_ID";
                value = 2;

                NewLine.remove(0,4);
            }

            query1.prepare (QString ("SELECT * FROM %1 WHERE %2 = :val").arg(Table).arg(Column));
            query1.bindValue(":val",NewLine);
            query1.exec();

            if(!query1.exec())
            {
                qDebug() << "query1.lastError()" << query1.lastError();
            }

            while(query1.next())
            {
                NewLine = query1.value(value).toString();
            }
        }

        QListWidgetItem *itemsName2 = ui->QuestResults_ListWidget_2->item(CurrentRow);
        itemsName2->setText(NewLine);
    }
}


void MainWindow::on_pushButton_225_clicked()
{
    int count1 = ui->QuestResults_ListWidget_1->count();

    if(count1 > 0)
    {
        int Packet_ID2 = ui->lineEdit_291->text().toInt(nullptr,10);

        db.transaction();

        QSqlQuery query;
        query.prepare (QString ("SELECT * FROM QUEST_ID_RESULTS WHERE rowid = :val"));
        query.bindValue(":val",Packet_ID2);
        query.exec();

        QVector<QString> OldResultVect;

        QString OldPopUpID = "";
        QString OldHeader = "";

        while(query.next())
        {
            QSqlRecord record = query.record();

            OldPopUpID = record.value(1).toString();
            OldHeader = record.value(2).toString();

            for(int fd = 3; fd < record.count(); fd++)
            {
                QString ResultID = record.value(fd).toString();

                if(ResultID.isEmpty() == false)
                {
                    OldResultVect.append(ResultID);
                }
                else
                {
                    break;
                }
            }
        }

        Table_Name = "QUEST_ID_RESULTS";

        QListWidgetItem *itemsID1 = ui->QuestResults_ListWidget_1->item(0);
        QString NewPopUpID = itemsID1->text();

        if(OldPopUpID != NewPopUpID && NewPopUpID.isEmpty() == false)
        {
            Column_Name = "QuestID";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewPopUpID);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        QListWidgetItem *itemsID2 = ui->QuestResults_ListWidget_2->item(0);
        QString NewHeader = itemsID2->text();

        if(OldHeader != NewHeader && NewHeader.isEmpty() == false)
        {
            Column_Name = "Description";

            qDebug() << "Column_Name" << Column_Name;

            query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
            query.bindValue(":val",NewHeader);
            query.bindValue(":id",Packet_ID2);
            query.exec();
        }

        ui->textEdit_36->clear();
        QVector<QString> NewResultVect;

        for(int re = 1; re < ui->QuestResults_ListWidget_2->count(); re++)
        {
            QListWidgetItem *itemsID = ui->QuestResults_ListWidget_1->item(re);
            QString items_ID = itemsID->text();

            NewResultVect.append(items_ID);
        }

        if(NewResultVect.size() < OldResultVect.size())
        {
            do
            {
                NewResultVect.append(nullptr);

            }while(NewResultVect.size() < OldResultVect.size());
        }

        if(NewResultVect.size() > OldResultVect.size())
        {
            do
            {
                OldResultVect.append(nullptr);

            }while(NewResultVect.size() > OldResultVect.size());
        }

        qDebug() << "";
        qDebug() << "OldResultVect" << OldResultVect;
        qDebug() << "NewResultVect" << NewResultVect;

        for(int add = 0; add < NewResultVect.size(); add++)
        {
            QString OldResultID = OldResultVect.at(add);

            QString NewResultID = NewResultVect.at(add);

            qDebug() << "";
            qDebug() << "OldResultID" << OldResultID;

            qDebug() << "NewResultID" << NewResultID;


            if(OldResultID.isEmpty() == true && NewResultID.isEmpty() == true)
            {
                break;
            }

            QString Num1 = QString("%1").arg(add+1,2,10,QLatin1Char('0')).toUpper();

            if((NewResultID != OldResultID))
            {
                Column_Name = "QuestID_Result_" + Num1;

                qDebug() << "Column_Name" << Column_Name;

                query.prepare(QString("UPDATE [%1] SET [%2] = :val WHERE ROWID = :id").arg(Table_Name).arg(Column_Name));
                query.bindValue(":val",NewResultID);
                query.bindValue(":id",Packet_ID2);
                query.exec();
            }

            db.commit();

        }
    }
}