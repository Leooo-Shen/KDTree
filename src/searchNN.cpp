#include<iostream>
#include<math.h>
#include "my_kd_tree.h"
#include "searchNN.h"

double distance(std::vector<double> A, std::vector<double> B){
    double dist = 0;
    for (unsigned i=0; i < A.size(); i++)
    {
        dist += pow((A[i] - B[i]),2);
    }
    return sqrt(dist);
}



double max(double a, double b, double c){
    if(a>b){
        if(a>c){return a;}
        else{return c;}
    }
    else{
        if(b>c){return b;}
        else{return c;}
    }
}



double distance(std::vector<double>  Q,Rect* BB){
    auto dx= max(Q[0]-BB->Xmin,0.0,Q[0]-BB->Xmax);
    auto dy = max(Q[1]-BB->Ymin,0.0,Q[1]-BB->Ymax);
    return sqrt(dx*dx+dy*dy); // ONLY DONE FOR K=2 :(((
}
