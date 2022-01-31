#include<iostream>
#include<math.h>
#include "my_kd_tree.h"
#include "searchNN.h"

// Helper functions for the Nearest Neighbour search (https://en.wikipedia.org/wiki/K-d_tree#Nearest_neighbour_search)


double distance(std::vector<double> A, std::vector<double> B){
    /*
    Find the distance between two vector A and vector B;
    param:
        inputs: 
            A,B: double vector  
        returns:
            L2 distance between A and B

    */
    double dist = 0;
    for (unsigned i=0; i < A.size(); i++)
    {
        dist += pow((A[i] - B[i]),2);
    }
    return sqrt(dist);
}



double max(double a, double b, double c){
    /*
    Find the maximum between three doubles
    param:
        inputs: 
            a,b,c: doubles 
        returns:
            max(a,b,c)
    */
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
    /*
    Find the distance between vector Q and rectangle BB, if vector Q is in rectangle BB the distance is 0
    param:
        inputs: 
            Q: vector of doubles
            BB: Rectangle struct with 4 vertices, defined and initialized in searchNN.h
        returns:
            L2 distance between Q and BB given that Q is outside of Rect BB

    */
    auto dx= max(Q[0]-BB->Xmin,0.0,Q[0]-BB->Xmax);
    auto dy = max(Q[1]-BB->Ymin,0.0,Q[1]-BB->Ymax);
    return sqrt(dx*dx+dy*dy); // ONLY DONE FOR K=2 :(((
}
