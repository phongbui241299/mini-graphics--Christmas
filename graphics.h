#ifndef GRAPHICS_H
#define GRAPHICS_H
#define MAX_NB_STARS 30
#include <QWidget>
#include <QPainter>
class graphics : public QWidget
{
    Q_OBJECT
public:
    explicit graphics(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void bautroi(QPainter& painter);
    void coixaygio(QPainter& painter);
    void drawSanta(QPainter& painter);
    void gift(QPainter& painter);
    void mattrang(QPainter& painter);
    void veNhanhBong(QPainter& painter,QPointF diemBD,double BK,double xoay,double sc);
    void veBongTuyet(QPainter& painter);
    void nentuyet(QPainter& painter);
    void drawTree(QPainter& painter);
    void veNgoiSao(QPainter& painter,QPointF diemBD,double BK);
    void veNhieuSao(QPainter& painter);
    void veQua(QPainter& painter);
    void cloud(QPainter &painter);
    void drawEgde(QPainter& painter, QPointF center, int r, int n);


    int random(int n);
    QPointF dichuyen(QPointF p, double kc, int huong);
    QPointF rotate(QPointF p, QPointF c, int deg);
    double random01();
    double timerId;
    double w;
    double h;
    int position;
    double edge;
signals:
    
public slots:
    
};

#endif // GRAPHICS_H
