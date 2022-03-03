#ifndef TARGETING_H
#define TARGETING_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QByteArray>
#include <QVector>

class targeting : public QObject
{
    Q_OBJECT
public:
    explicit targeting(QObject *parent = nullptr);


int main_level = 0;
int mob_level = 0;
int diff_a = 0;



QMap <int,QVector <QString>> green_map =
{
    {5,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {6,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {7,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {8,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {9,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {10,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {11,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {12,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {13,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {14,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {15,{"04","05","06","07","08","09","10","11","12","13","14"}},
    {16,{"05","06","07","08","09","10","11","12","13","14","15","16","17","18"}},
    {17,{"05","06","07","08","09","10","11","12","13","14","15","16","17","18"}},
    {18,{"05","06","07","08","09","10","11","12","13","14","15","16","17","18"}},
    {19,{"05","06","07","08","09","10","11","12","13","14","15","16","17","18"}},
    {20,{"06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22"}},
    {21,{"06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22"}},
    {22,{"06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22"}},
    {23,{"06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22"}},
    {24,{"07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26"}},
    {25,{"07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26"}},
    {26,{"07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26"}},
    {27,{"07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26"}},
    {28,{"08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30"}},
    {29,{"08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30"}},
    {30,{"08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30"}},
    {31,{"08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30"}},
    {32,{"09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34"}},
    {33,{"09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34"}},
    {34,{"09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34"}},
    {35,{"09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34"}},
    {36,{"10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38"}},
    {37,{"10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38"}},
    {38,{"10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38"}},
    {39,{"10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38"}},
    {40,{"11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42"}},
    {41,{"11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42"}},
    {42,{"11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42"}},
    {43,{"11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42"}},
    {44,{"12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46"}},
    {45,{"12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46"}},
    {46,{"12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46"}},
    {47,{"12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46"}},
    {48,{"13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50"}},
    {49,{"13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50"}},
    {50,{"13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50"}},
    {51,{"13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50"}},
    {52,{"14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54"}},
    {53,{"14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54"}},
    {54,{"14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54"}},
    {55,{"14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54"}},
    {56,{"15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58"}},
    {57,{"15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58"}},
    {58,{"15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58"}},
    {59,{"15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58"}},
    {60,{"16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60"}}
};




signals:

public slots:
QByteArray target(QByteArray ClientID,QByteArray ClientsIP, QByteArray ClientsPort,QByteArray target_id);


};

#endif // TARGETING_H
