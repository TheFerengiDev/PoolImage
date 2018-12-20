#include "fenetre.h"
#include <QtDebug>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

fenetre::fenetre(): QWidget (){

    setFixedSize(400,400);
//Test
    slide1 = new QSlider(Qt::Horizontal,this);
    slide2 = new QSlider(Qt::Horizontal,this);
    slide3 = new QSlider(Qt::Horizontal,this);
    slide4 = new QSlider(Qt::Horizontal,this);
    slide5 = new QSlider(Qt::Horizontal,this);
    slide6 = new QSlider(Qt::Horizontal,this);
    slide7 = new QSlider(Qt::Vertical,this);

    slide8 = new QSlider(Qt::Horizontal,this);
    slide9 = new QSlider(Qt::Horizontal,this);
    slide10 = new QSlider(Qt::Horizontal,this);
    slide11 = new QSlider(Qt::Horizontal,this);
    slide12 = new QSlider(Qt::Horizontal,this);


    slide1->move(50,50 );
    slide2->move(50,100);
    slide3->move(50,150);
    slide4->move(50,200 );
    slide5->move(50,250);
    slide6->move(50,300);

    slide8->move(200,50);
    slide9->move(200,100);
    slide10->move(200,150);
    slide11->move(200,200);
    slide12->move(200,250);

    slide7->move(350,50);


    label8  = new QLabel("Param1",this);
    label9  = new QLabel("Param2",this);
    label10 = new QLabel("minD",this);
    label11 = new QLabel("minR",this);
    label12 = new QLabel("maxR",this);

    label8->move(200,40);
    label9->move(200,90);
    label10->move(200,140);
    label11->move(200,190);
    label12->move(200,240);



    slide1->setRange(0,179);
    slide2->setRange(0,179);
    slide3->setRange(0,255);
    slide4->setRange(0,255);
    slide5->setRange(0,255);
    slide6->setRange(0,255);

    slide8->setRange(1,100);
    slide9->setRange(1,100);
    slide10->setRange(1,100);
    slide11->setRange(1,100);
    slide12->setRange(1,100);

    slide7->setRange(0,4);



    slide1->setValue(40);
    slide2->setValue(80);
    slide3->setValue(50);
    slide4->setValue(255);
    slide5->setValue(0);
    slide6->setValue(255);

    slide8->setValue(20);
    slide9->setValue(100);
    slide10->setValue(10);
    slide11->setValue(0);
    slide12->setValue(100);

    slide7->setValue(0);

    Hmin=40;
    Hmax=80;
    Smin=50;
    Smax=255;
    Vmin=0;
    Vmax=255;
    param_1 = 20;
    param_2 = 100;
    min_dist = 10;
    minR = 0;
    maxR = 100;
    image_size=450;

    lowthreshold_canny=5;

    QObject::connect(slide1,SIGNAL(valueChanged(int)),this,SLOT(setHvalue_min(int)));
    QObject::connect(slide2,SIGNAL(valueChanged(int)),this,SLOT(setHvalue_max(int)));
    QObject::connect(slide3,SIGNAL(valueChanged(int)),this,SLOT(setSvalue_min(int)));
    QObject::connect(slide4,SIGNAL(valueChanged(int)),this,SLOT(setSvalue_max(int)));
    QObject::connect(slide5,SIGNAL(valueChanged(int)),this,SLOT(setVvalue_min(int)));
    QObject::connect(slide6,SIGNAL(valueChanged(int)),this,SLOT(setVvalue_max(int)));

    QObject::connect(slide8,SIGNAL(valueChanged(int)),this,SLOT(setParam1(int)));
    QObject::connect(slide9,SIGNAL(valueChanged(int)),this,SLOT(setParam2(int)));
    QObject::connect(slide10,SIGNAL(valueChanged(int)),this,SLOT(setmindist(int)));
    QObject::connect(slide11,SIGNAL(valueChanged(int)),this,SLOT(setminR(int)));
    QObject::connect(slide12,SIGNAL(valueChanged(int)),this,SLOT(setmaxR(int)));

    QObject::connect(slide7,SIGNAL(valueChanged(int)),this,SLOT(changeImage(int)));


    filename[0]="img1.jpg";
    filename[1]="img2.jpg";
    filename[2]="img3.png";
    filename[3]="img4.png";
    filename[4]="img5.jpg";
    baselink = "C:\\image_for_Cpp\\";
   // link = baselink + filename[0];

   // qDebug() << QString::fromStdString(link);
    //image = cv::imread(link, 1);
   // cv::cvtColor(image, fullImageHSV, cv::COLOR_BGR2HSV);
   // compute();

    changeImage(0);

}

void fenetre::changeImage(int ite){

    link = baselink + filename[ite];
    image = cv::imread(link, 1);


    cv::Size size(image_size,image_size);//the dst image size,e.g.100x100
    cv::resize(image,image,size);//resize image

    image.copyTo(image2);
    cv::cvtColor(image, fullImageHSV, cv::COLOR_BGR2HSV);


   // cv::cvtColor(image2, image2, cv::COLOR_BGR2GRAY);
    compute();
    //link = "C:\\Users\\Administrateur\\Desktop\\C++\\openCVtest\" + filename[0]";
}


void fenetre::setParam1(int P){
    param_1 = P;
    compute();
}

void fenetre::setParam2(int P){
    param_2 = P;
    compute();
}

void fenetre::setminR(int P){
    minR = P;
    compute();
}

void fenetre::setmaxR(int P){
    maxR = P;
    compute();
}

void fenetre::setmindist(int P){
    min_dist = P;
    compute();
}



void fenetre::setHvalue_min(int H){
    Hmin = H;
    compute();
}
void fenetre::setHvalue_max(int H){
    Hmax = H;
    compute();
}
void fenetre::setSvalue_min(int S){
    Smin = S;
    compute();
}
void fenetre::setSvalue_max(int S){
    Smax = S;
    compute();
}
void fenetre::setVvalue_min(int V){
    Vmin = V;
    compute();
}
void fenetre::setVvalue_max(int V){
    Vmax = V;
    compute();
}



double cross(cv::Point v1,cv::Point v2){
    return v1.x*v2.y - v1.y*v2.x;
}

cv::Point getIntersectionPoint(cv::Point a1, cv::Point a2, cv::Point b1, cv::Point b2){
    cv::Point p = a1;
    cv::Point q = b1;
    cv::Point r(a2-a1);
    cv::Point s(b2-b1);
    cv::Point intPnt;

    intPnt.x=0;
    intPnt.y=0;
   if(cross(r,s) == 0) {return intPnt;}

   double t = cross(q-p,s)/cross(r,s);

   return intPnt = p + t*r;
//    return true;
}



void fenetre::compute(){


    qDebug()<< "H:" << Hmin << " - " << Hmax;
    qDebug()<< "S:" << Smin << " - " << Smax;
    qDebug()<< "V:" << Vmin << " - " << Vmax;

    image.copyTo(image2);

    cv::Mat fullImageHSV2;
    cv::imshow("My Image 2",fullImageHSV);
    cv::inRange(fullImageHSV, cv::Scalar(Hmin, Smin, Vmin), cv::Scalar(Hmax, Smax, Vmax), fullImageHSV2);
    cv::imshow("My Image 2",fullImageHSV2);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(fullImageHSV2,circles,cv::HOUGH_GRADIENT, 2, min_dist, param_1, param_2 ,minR,maxR);

     for( size_t i = 0; i < circles.size(); i++ )
     {
         cv::Vec3i c = circles[i];
         cv::Point center = cv::Point(c[0], c[1]);
         // circle center
       //  cv::circle( image2, center, 1, cv::Scalar(0,100,100), 3, cv::LINE_AA);
         // circle outline
         int radius = c[2];
         cv::circle( image2, center, radius, cv::Scalar(255,0,255), 3, cv::LINE_AA);
     }


     cv::Mat border;
     cv::Canny(fullImageHSV2,border,5,15);
     cv::imshow("border",border);

     std::vector<cv::Vec2f> lines;
     cv::HoughLines(border,lines,1, CV_PI/90, 60, 0, 0 );

     std::vector<cv::Vec4f> listpoints;

     for( size_t i = 0; i < lines.size(); i++ )
     {
         float rho = lines[i][0], theta = lines[i][1];
         cv::Point pt1, pt2;
         double a = cos(theta), b = sin(theta);
         double x0 = a*rho, y0 = b*rho;
         pt1.x = cvRound(x0 + 1000*(-b));
         pt1.y = cvRound(y0 + 1000*(a));
         pt2.x = cvRound(x0 - 1000*(-b));
         pt2.y = cvRound(y0 - 1000*(a));
         cv::line( image2, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
         cv::Vec4f l ;
         l[0] = pt1.x;
         l[1] = pt1.y;
         l[2] = pt2.x;
         l[3] = pt2.y;
         listpoints.push_back(l);
            }

     for( size_t i = 0; i < listpoints.size(); i++ ){
         for( size_t i2 = i+1; i2 < listpoints.size(); i2++ ){
            qDebug() << i << " - " << i2;
             cv::Point a1, a2,b1,b2,intPnt;
             a1.x = listpoints[i][0];
             a1.y = listpoints[i][1];
             a2.x = listpoints[i][2];
             a2.y = listpoints[i][3];
             b1.x = listpoints[i2][0];
             b1.y = listpoints[i2][1];
             b2.x = listpoints[i2][2];
             b2.y = listpoints[i2][3];


           intPnt = getIntersectionPoint(a1, a2, b1, b2);
           qDebug()<< "intersection:" <<intPnt.x <<" - " << intPnt.y <<"("<< image.rows <<"|"<< image2.cols<<")";
           if ((intPnt.x<image_size)&(intPnt.y<image_size)&(intPnt.x>0)&(intPnt.y>0)){
               cv::circle( image2, intPnt, 5, cv::Scalar(255,0,255), 3, cv::LINE_AA);
           }


         }

     }

     cv::imshow("My Image", image2);


    // cv::Mat dst;
    // dst= cv::Scalar::all(0);
     //cv::imshow( "bord", dst );


}












