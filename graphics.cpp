#include "graphics.h"
#include "QPainter"
#include "QPixmap"
#include "QPointer"
#include "math.h"
#include <QPointF>
#include <QSound>

//int v = 9;

graphics::graphics(QWidget *parent) :
    QWidget(parent)
{
    w = width();
    h = height();
    position = 0;
    timerId = startTimer(10);
    edge = 0;

}

//hàm bắt sự kiện thời gian
void graphics::timerEvent(QTimerEvent *) {
    position+=1;
    edge+=2;
    repaint();
}

//hàm dùng vẽ bông tuyết
QPointF graphics::dichuyen(QPointF p, double kc, int huong){
    QPointF pnew;
    pnew.setX(p.x()+kc*cos(M_PI*huong/180));
    pnew.setY(p.y()+kc*sin(M_PI*huong/180));
    return pnew;
//    int c = v;
}

//hàm xoay (đồ họa con rùa)
QPointF graphics::rotate(QPointF p, QPointF c, int deg){
    QPoint newp;
    double rad = deg*M_PI/180;
    newp.setX(c.x() + (p.x() - c.x())*cos(rad) - (p.y() - c.y())*sin(rad));
    newp.setY(c.y() + (p.x() - c.x())*sin(rad) + (p.y() - c.y())*cos(rad));
    return newp;
}

// hàm random dùng để tự động qui định vị trí bất kỳ của bông tuyết rơi
int graphics::random(int n){
    return rand()%n;
}

//hàm vẽ bầu trời
void graphics::bautroi(QPainter &painter){
    QRect rect(0, 0, 2500, 400);
      QLinearGradient gradient(rect.x(), rect.y(), rect.x(), rect.y() + rect.height()); // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
      gradient.setColorAt(0.2, QColor("#08386E"));
      gradient.setColorAt(0.8, QColor("#415B79"));
      gradient.setSpread(QGradient::ReflectSpread); //Độ dốc được phản ánh bên ngoài khu vực gradient
         painter.setPen(Qt::NoPen);
         painter.setBrush(gradient);
         painter.drawRect(rect);
          for(int i = 1;i<=1000;i++){ // i càng tăng thì mật độ tuyết càng dày
             painter.setPen(Qt::NoPen);
             painter.setBrush(QColor(255,255,255));
             painter.drawEllipse(random(1500),random(2000),6,6);
          }
}

//hàm vẽ mây
void graphics::cloud(QPainter &painter){
    QRadialGradient radialGrad(QPointF(500, 300), 1000); // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
     radialGrad.setColorAt(0.2, QColor("#47476b"));
     radialGrad.setColorAt(0.4, QColor("#0066cc"));
     radialGrad.setColorAt(1, QColor("#c1c1d7"));
    QBrush brush(radialGrad);
    painter.setBrush(brush);
    QPen pen;
    pen.setStyle(Qt::NoPen);
    painter.setPen(pen);
    painter.drawEllipse(780,100,150,100);
    painter.drawEllipse(870,130,150,100);
    painter.drawEllipse(850,70,150,100);
    painter.drawEllipse(950,100,150,100);
    painter.drawEllipse(990,60,150,100);

    pen.setStyle(Qt::NoPen);
    painter.setPen(pen);
    painter.drawEllipse(1130,150,180,100);
    painter.drawEllipse(1220,180,180,100);
    painter.drawEllipse(1200,120,180,100);
    painter.drawEllipse(1300,150,180,100);
    painter.drawEllipse(1340,110,180,100);
}

//vẽ ngôi sao
void graphics::veNgoiSao(QPainter&  painter,QPointF diemBD,double BK){
    QPointF Goc=diemBD;
    //Tìm đa giác
    QPolygonF DaGiac;
    for(int i=0;i<5;i++)
        DaGiac<<dichuyen(Goc,BK,-90+i*360/5);
    for(int k=0;k<3;k++){
         painter.drawLine(DaGiac.value(k),DaGiac.value(k+2));
        if(k<2)  painter.drawLine(DaGiac.value(k),DaGiac.value(k+3));
    }
}

//vị trí ngôi sao
void graphics::veNhieuSao(QPainter& painter){
    painter.setPen(QPen(QBrush("#ffff00"), 2.5));
    painter.setBrush(QColor("#ffff00"));
     QPointF Goc_1(width()/2+160,height()/2-330);
     int step=30;
     veNgoiSao(painter,dichuyen(Goc_1,step*4,360/20+20*36),step/3);

     QPointF Goc_2(width()/2+10,height()/2-330);
     veNgoiSao(painter,dichuyen(Goc_2,step*4,360/20+20*36),step/3);

     QPointF Goc_3(width()/2+20,height()/2-280);
     veNgoiSao(painter,dichuyen(Goc_3,step*4,360/20+20*36),step/3);

     QPointF Goc_4(width()/2+180,height()/2-240);
     veNgoiSao(painter,dichuyen(Goc_4,step*4,360/20+20*36),step/3);

     QPointF Goc_5(width()/2-450,height()/2-450);
     veNgoiSao(painter,dichuyen(Goc_5,step*4,360/20+20*36),step/3);

     QPointF Goc_6(width()/2+50,height()/2-650);
     veNgoiSao(painter,dichuyen(Goc_6,step*4,360/20+20*36),step/3);

     QPointF Goc_7(width()/2-450,height()/2-650);
     veNgoiSao(painter,dichuyen(Goc_7,step*4,360/20+20*36),step/3);

     QPointF Goc_8(width()/2-600,height()/2-680);
     veNgoiSao(painter,dichuyen(Goc_8,step*4,360/20+20*36),step/3);

     QPointF Goc_9(width()/2-1000,height()/2-500);
     veNgoiSao(painter,dichuyen(Goc_9,step*4,360/20+20*36),step/3);

     QPointF Goc_10(width()/2-1100,height()/2-650);
     veNgoiSao(painter,dichuyen(Goc_10,step*4,360/20+20*36),step/3);

     QPointF Goc_11(width()/2-750,height()/2-650);
     veNgoiSao(painter,dichuyen(Goc_11,step*4,360/20+20*36),step/3);

}

//hàm vẽ mặt trăng
void graphics::mattrang(QPainter &painter){
    QRadialGradient radialGrad(QPointF(250, 100), 300);  // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
        radialGrad.setColorAt(0, QColor("#D5D8DC"));
        radialGrad.setColorAt(0.2, QColor("#EAECEE"));
        radialGrad.setColorAt(0.3, QColor("#ffff80"));
        radialGrad.setColorAt(0.7, QColor("#EAECEE"));
        radialGrad.setColorAt(0.2, QColor("#FDFEFE"));
        QBrush brush(radialGrad);
        painter.setBrush(brush);
        QPen pen;
        pen.setStyle(Qt::NoPen);
        painter.setPen(pen);
        painter.drawEllipse(150, 50, 150, 150);
}

void graphics::veQua(QPainter& painter){
    painter.setPen(QPen(QBrush("#804000"), 10));
    painter.setBrush(QColor("#804000"));
    int step=30;
     QPointF Goc_2(width()/2+200,height()/2-90);
     veNgoiSao(painter,dichuyen(Goc_2,step*4,360/20+20*36),step/3);

     QPointF Goc_3(width()/2+100,height()/2-85);
     veNgoiSao(painter,dichuyen(Goc_3,step*4,360/20+20*36),step/3);

     QPointF Goc_4(width()/2-20,height()/2-115);
     veNgoiSao(painter,dichuyen(Goc_4,step*4,360/20+20*36),step/3);

     QPointF Goc_5(width()/2-35,height()/2-180);
     veNgoiSao(painter,dichuyen(Goc_5,step*4,360/20+20*36),step/3);

     QPointF Goc_6(width()/2+50,height()/2-180);
     veNgoiSao(painter,dichuyen(Goc_6,step*4,360/20+20*36),step/3);

     QPointF Goc_7(width()/2+150,height()/2-160);
     veNgoiSao(painter,dichuyen(Goc_7,step*4,360/20+20*36),step/3);

     QPointF Goc_8(width()/2-35,height()/2-180);
     veNgoiSao(painter,dichuyen(Goc_8,step*4,360/20+20*36),step/3);
}
//hàm vẽ nền tuyết trắng
void graphics::nentuyet(QPainter &painter){
    QRadialGradient radialGrad2(QPointF(350, 1000), 800); // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
        radialGrad2.setColorAt(0.5, QColor("#AEBCCC"));
        radialGrad2.setColorAt(1, QColor("#FFFFFF"));
        QBrush brush2(radialGrad2);
        painter.setBrush(brush2);
        QPen pen2;
        pen2.setStyle(Qt::NoPen);
        painter.setPen(pen2);
        painter.drawEllipse(-500,350,2000,650);
        painter.drawEllipse(500,350,1500,600);
        for(int i = 1;i<=1000;i++){
           painter.setPen(Qt::NoPen);
           painter.setBrush(QColor(255,255,255));
           painter.drawEllipse(random(1500),random(2000),3,3);
        }
}

//hàm vẽ cối xây gió
void graphics::coixaygio(QPainter &painter){
    // ve khuon nha
     QPointF body_house_1[4] = {
        QPointF(w+300.0,h+250.0),
        QPointF(w+230.0,h+570.0),
        QPointF(w+290.0,h+570.0),
        QPointF(w+340.0,h+250.0),
     };
     QPointF body_house_3[4] = {
        QPointF(w+360.0,h+250.0),
        QPointF(w+400.0,h+570.0),
        QPointF(w+480.0,h+570.0),
        QPointF(w+400.0,h+250.0),
     };
     painter.setPen(QPen(QBrush("#b35900"), 0));
     painter.setBrush(QColor("#b35900"));
     painter.drawPolygon(body_house_1,4);
     painter.drawPolygon(body_house_3,4);

     QPointF body_house_2[4] = {
        QPointF(w+330.0,h+250.0),
        QPointF(w+280.0,h+570.0),
        QPointF(w+420.0,h+570.0),
        QPointF(w+380.0,h+250.0),
     };
     painter.setPen(QPen(QBrush("#ffcc66"), 1));
     painter.setBrush(QColor("#ffcc66"));
     painter.drawPolygon(body_house_2,4);


     //ve cua so
     QPointF window_1[4]={
        QPointF(w+330.0, h+330.0),
        QPointF(w+330.0, h+380.0),
        QPointF(w+375.0, h+380.0),
        QPointF(w+375.0, h+330.0),
     };
     QPointF window_2[4]={
        QPointF(w+330.0, h+450.0),
        QPointF(w+330.0, h+500.0),
        QPointF(w+375.0, h+500.0),
        QPointF(w+375.0, h+450.0),
     };
     painter.setPen(QPen(QBrush("#800000"), 5));
     painter.setBrush(QColor("#666633"));
     painter.drawPolygon(window_1,4);
     painter.drawPolygon(window_2,4);

// vẽ sàn nhà
     QPointF floor[4]={
        QPointF(w+200.0, h+565.0),
        QPointF(w+200.0, h+575.0),
        QPointF(w+510.0, h+575.0),
        QPointF(w+510.0, h+565.0),
     };
        painter.setPen(QPen(QBrush("#ffdd99"), 1));
        painter.setBrush(QColor("#666633"));
        painter.drawPolygon(floor,4);

// ve mái nhà
     QPointF roof[3]={
        QPointF(w+230.0,h+250.0),
        QPointF(w+480.0,h+250.0),
        QPointF(w+355.0,h+200.0),
     };
      painter.setPen(QPen(QBrush("#f2f2f2"), 1));
      painter.setBrush(QColor("#f2f2f2"));
      painter.drawPolygon(roof,3);
}

//hàm vẽ cánh quạt và truyền chuyển động cho cánh quạt
void graphics::drawEgde(QPainter& painter, QPointF center, int r, int n){
   double w = center.x();
   double h = center.y();

   painter.setPen(Qt::black);

   QPointF a(w-5, h);
   QPointF b(w+5, h);

   QPointF c(w+5, h-r);
   QPointF d(w-35, h-r);

   QPointF e(w-35, h-r+50);
   QPointF f(w-5, h-r+50);

   QPointF g(w-5, h);

   painter.setBrush(Qt::yellow);
   for(int i = 0; i < n; i++){
       QPointF a1 = rotate(a, center, i*(360/n)+edge);
       QPointF b1 = rotate(b, center, i*(360/n)+edge);
       QPointF c1 = rotate(c, center, i*(360/n)+edge);
       QPointF d1 = rotate(d, center, i*(360/n)+edge);
       QPointF e1 = rotate(e, center, i*(360/n)+edge);
       QPointF f1 = rotate(f, center, i*(360/n)+edge);
       QPointF g1 = rotate(g, center, i*(360/n)+edge);
       QPainterPath path;
       path.moveTo(a1);
       path.lineTo(b1);
       path.lineTo(c1);
       path.lineTo(d1);
       path.lineTo(e1);
       path.lineTo(f1);
       path.lineTo(g1);
       painter.drawPath(path);
   }
   painter.drawEllipse(center, r/10, r/10);
}

//hàm insert ông già nôel
void graphics::drawSanta(QPainter &painter) {
    QString filename = "D:/Do_hoa_may_tinh_BAO_CAO/noel.png";
    QPointF a(0+position,550-position+10);  //chuyển động một góc postion để làm hình ảnh chuyển động
    painter.drawPixmap(a,QPixmap(filename));
    QString filename_1 = "D:/Do_hoa_may_tinh_BAO_CAO/snow_man1.png";
    painter.drawPixmap(10,500,170,170,QPixmap(filename_1));    //căng chỉnh vị trí và kích thước của quà
    QString filename_2 = "D:/Do_hoa_may_tinh_BAO_CAO/snow_man2.png";
    painter.drawPixmap(100,550,170,170,QPixmap(filename_2));    //căng chỉnh vị trí và kích thước của quà
    QString filename_3 = "D:/Do_hoa_may_tinh_BAO_CAO/snow_man3.png";
    painter.drawPixmap(5+position,680,120,170,QPixmap(filename_3));


}

//Hàm insert quà trang trí
void graphics::gift(QPainter &painter){
    QString filename = "D:/Do_hoa_may_tinh_BAO_CAO/gift.png";
    painter.drawPixmap(1055,650,80,80,QPixmap(filename));       //căng chỉnh vị trí và kích thước của quà
    QString filename2 = "D:/Do_hoa_may_tinh_BAO_CAO/gift_3.png";
    painter.drawPixmap(1155,680,170,100,QPixmap(filename2));    //căng chỉnh vị trí và kích thước của quà


}

//Hàm vẽ cây
void graphics::drawTree(QPainter &painter){
      // vẽ thân cây
      QPointF trunk_1[4]={
        QPointF(w+1050,h+640),
        QPointF(w+1055,h+640),
        QPointF(w+1050,h+700),
        QPointF(w+1055,h+700),
        };
      QPointF trunk_2[4]={
        QPointF(w+1200,h+670),
        QPointF(w+1205,h+670),
        QPointF(w+1200,h+730),
        QPointF(w+1205,h+730),
        };
        painter.setPen(QPen(QBrush("#996600"), 10));
        painter.setBrush(QColor("#996600"));
        painter.drawPolygon(trunk_1,4);
        painter.drawPolygon(trunk_2,4);

      //vẽ cây
      QPointF tree_3_1[3]={
         QPointF(w+230.0+700+10-20,h+570.0+70),
         QPointF(w+480.0+700-10+20,h+570.0+70),
         QPointF(w+355.0+700,h+400.0),
      };
      QPointF tree_3_2[3]={
         QPointF(w+230.0+700+10-20+150,h+570.0+100),
         QPointF(w+480.0+700-10+20+150,h+570.0+100),
         QPointF(w+355.0+150+700,h+400.0),
      };
      painter.setPen(QPen(QBrush("#008000"), 1));
      painter.setBrush(QColor("#008000"));
      painter.drawPolygon(tree_3_1,3);
      painter.drawPolygon(tree_3_2,3);


      QPointF tree_2_1[3]={
         QPointF(w+940,h+570.0),
         QPointF(w+1170,h+570.0),
         QPointF(w+355.0+700,h+400.0),
      };
      QPointF tree_2_2[3]={
         QPointF(w+940+150,h+600.0),
         QPointF(w+1170+150,h+600.0),
         QPointF(w+355.0+150+700,h+400.0),
      };
      painter.setPen(QPen(QBrush("#adebad"), 1));
      painter.setBrush(QColor("#adebad"));
      painter.drawPolygon(tree_2_1,3);
      painter.drawPolygon(tree_2_2,3);


      QPointF tree_1_1[3]={
         QPointF(w+970,h+500),
         QPointF(w+1140,h+500),
         QPointF(w+1055,h+400.0),
      };
      QPointF tree_1_2[3]={
         QPointF(w+970+150,h+530),
         QPointF(w+1140+150,h+530),
         QPointF(w+1055+150,h+400.0),
      };
       painter.setPen(QPen(QBrush("#e6ffe6"), 1));
       painter.setBrush(QColor("#e6ffe6"));
       painter.drawPolygon(tree_1_1,3);
       painter.drawPolygon(tree_1_2,3);
}

//hàm vẽ chi tiết bông
void graphics::veNhanhBong(QPainter &painter,QPointF diemBD,double BK,double xoay,double sc){
    QPointF diem[12];
    diem[1]=dichuyen(diemBD,BK/40,-30*sc+xoay);
    diem[2]=dichuyen(diem[1],BK*4/10,0*sc+xoay);
    diem[3]=dichuyen(diem[2],BK*3/10,-60*sc+xoay);
    diem[4]=dichuyen(diem[3],BK/40,30*sc+xoay);
    diem[5]=dichuyen(diem[4],BK*3/10-BK/(40*sqrt(3)),120*sc+xoay);
    diem[6]=dichuyen(diem[5],BK*2/10,0*sc+xoay);
    diem[7]=dichuyen(diem[6],BK*2/10,-60*sc+xoay);
    diem[8]=dichuyen(diem[7],BK/40,30*sc+xoay);
    diem[9]=dichuyen(diem[8],BK*2/10-BK/(40*sqrt(3)),120*sc+xoay);
    diem[10]=dichuyen(diem[9],BK*2/10,0*sc+xoay);
    diem[11]=dichuyen(diem[10],BK/40,45*sc+xoay);
    for(int i=1;i<11;i++)
         painter.drawLine(diem[i],diem[i+1]);
}

//hàm insert vị trí bông tuyết
void graphics::veBongTuyet(QPainter& painter){
    painter.setPen(QColor("#80aaff"));
    for(int i=0;i<6;i++){
        veNhanhBong(painter,QPointF(width()/2,height()/2),15,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2,height()/2),15,i*360/6,-1);

        veNhanhBong(painter,QPointF(width()/2+100,height()/2),10,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2+100,height()/2),10,i*360/6,-1);

        veNhanhBong(painter,QPointF(width()/2-100,height()/2-100),10,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-100,height()/2-100),10,i*360/6,-1);

        veNhanhBong(painter,QPointF(width()/2-100,height()/2-200),10,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-100,height()/2-200),10,i*360/6,-1);

        veNhanhBong(painter,QPointF(width()/2-300,height()/2+100),10,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-300,height()/2+100),10,i*360/6,-1);

        veNhanhBong(painter,QPointF(width()/2-200,height()/2-50),15,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-200,height()/2-50),15,i*360/6,-1);

        veNhanhBong(painter,QPointF(width()/2-400,height()/2-30),15,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-400,height()/2-30),15,i*360/6,-1);


        veNhanhBong(painter,QPointF(width()/2-600,height()/2+20),10,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-600,height()/2+20),10,i*360/6,-1);


        veNhanhBong(painter,QPointF(width()/2-650,height()/2+80),20,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-650,height()/2+80),20,i*360/6,-1);

        veNhanhBong(painter,QPointF(width()/2-670,height()/2),20,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-670,height()/2),20,i*360/6,-1);


        veNhanhBong(painter,QPointF(width()/2-500,height()/2+55),12,i*360/6,1);
        veNhanhBong(painter,QPointF(width()/2-500,height()/2+55),12,i*360/6,-1);
    }
}
//hàm sự kiện paint event
void graphics::paintEvent(QPaintEvent *){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    bautroi(painter);
    nentuyet(painter);
    coixaygio(painter);
    drawTree(painter);


    mattrang(painter);
    QPointF a(455, 270);
    drawEgde(painter,a,170,4);
    cloud(painter);
    gift(painter);
    veQua(painter);
    veNhieuSao(painter);
    veBongTuyet(painter);

    drawSanta(painter);
//    QSound::play("D:/Do_hoa_may_tinh_BAO_CAO/123.wav");


}

