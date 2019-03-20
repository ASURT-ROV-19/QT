#ifndef SENSORLABEL_H
#define SENSORLABEL_H
#include <QLabel>

class transparentLabel : public QLabel
{
public:
    transparentLabel(int x=0,int y=0,int width=120,int height=120,QString color="white",QString fontSize="22",Qt::AlignmentFlag vertical=Qt::AlignCenter,Qt::AlignmentFlag horizontal=Qt::AlignCenter);
    transparentLabel(QString color,QString fontSize,Qt::AlignmentFlag vertical,Qt::AlignmentFlag hotizontal);

};

#endif // SENSORLABEL_H
