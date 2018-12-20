#ifndef FENETRE_H
#define FENETRE_H

#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QLabel>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class fenetre : public QWidget // On hérite de QWidget (IMPORTANT)

{

    Q_OBJECT

    public:
    fenetre();
    void compute();

public slots:
    void setHvalue_min(int H);
    void setHvalue_max(int H);
    void setSvalue_min(int S);
    void setSvalue_max(int S);
    void setVvalue_min(int V);
    void setVvalue_max(int V);
    void changeImage(int ite);
    void setParam2(int param2);
    void setParam1(int param1);
    void setmindist(int mind);
    void setminR(int x);
    void setmaxR(int x);

    private:
    QSlider *slide1;
    QSlider *slide2;
    QSlider *slide3;
    QSlider *slide4;
    QSlider *slide5;
    QSlider *slide6;

    QSlider *slide7;

    QSlider *slide8;
    QSlider *slide9;
    QSlider *slide10;
    QSlider *slide11;
    QSlider *slide12;

    QLabel  *label8;
    QLabel  *label9;
    QLabel  *label10;
    QLabel  *label11;
    QLabel  *label12;

    cv::Mat image;
    cv::Mat image2;
    cv::Mat fullImageHSV;

    int Hmin;
    int Hmax;
    int Smin;
    int Smax;
    int Vmin;
    int Vmax;
    int param_2;
    int param_1;
    int min_dist;
    int maxR;
    int minR;


    std::string filename[5];
    std::string  link;
    std::string  baselink;
    int lowthreshold_canny;


};

#endif // FENETRE_H
