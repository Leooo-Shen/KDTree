#ifndef __SearchNN_
#define __SearchNN_
#include <iostream>
#include <string>
#include <vector>
#include<fstream>

#include "node.h"
#include "my_kd_tree.h"

double distance(std::vector<double> A, std::vector<double> B);

double max(double a, double b, double c);

struct Rect
{
    double Xmin,Xmax;
    double Ymin, Ymax;
    Rect(double Xmingiven,double Xmaxgiven, double Ymaxgiven, double Ymingiven){
    Xmin=Xmingiven;
    Xmax=Xmaxgiven;
    Ymin=Ymingiven;
    Ymax=Ymaxgiven;
    }  
    Rect* trimRight(int cd, std::vector<double> T){
        if(cd%2==0){ Rect* newrect=new Rect(Xmin=T[0],Xmax,Ymin,Ymax);
            return  newrect;}
        else{Rect* newrect=new Rect(Xmin,Xmax,Ymin=T[1],Ymax); 
            return newrect;}
    }
    Rect* trimLeft(int cd, std::vector<double> T){
        if(cd%2==0){ Rect* newrect=new Rect(Xmin,Xmax=T[0],Ymin,Ymax); 
            return newrect; }
        else{Rect* newrect=new Rect(Xmin, Xmax, Ymin, Ymax=T[1]); 
            return newrect;}
    }
};

double distance(std::vector<double>  Q,Rect* BB);
#endif