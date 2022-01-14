// Basic Plan:
// 1- We want to make methods first:
//      i- Define a rectangle class - done
//      ii- Define a distance function from point to point and point to rectangle - done
//      iii- Find initial d(Q,C), here Q is the query point, C is the node which our Q would've been under if we traversed the tree for and d is our 
//          squared distance function - done
//      iv- Method to define the bounding box: simply >< immediate parent node[cd] - done
//      v- We recursively now check the parent nodes:
//                  if bounding box of node < d(Q,C) we recursively check the left and right children of our node
//                  else we prune the node from our search
//      
// 2- Turn our method into a class
// 3- Create a test case (we can try to use the test case in the slides)
// 4- Not done for k>2 points

#include<iostream>
#include "my_kd_tree.h"

std::vector<double> Q;
struct Rect
{
    int Xmin, Xmax;
    int Ymin, Ymax;
    Rect(Xmin,Xmax,Ymin,Ymax){
    Xmin=Xmin;
    Ymin=Ymin;
    Ymax=Ymax;
    Xmax=Xmax;
    }  
    trimRight(int cd, std::vector<double> X){
        if(cd%2==0){ Xmin=X[0]; }
        else{Ymin=X[1];}
    }
    trimLeft(int cd, std::vector<double> X){
        if(cd%2==0){ Xmax=X[0]; }
        else{Ymax=X[1];}
    }
};

int distance(std::vector<double>  Q,Rect BB, int k=2){
    dx=std::max(BB.Xmin-Q[0],0,BB.Xmax-Q[0]);   
    dy=std::min(BB.Ymin-Q[1],0,BB.Ymax-Q[1]);
    return dx*dx+dy*dy;
}

int distance(std::vector<double>  Q,std::vector<double> point, int k=2){
    return (Q[0]-point[0])^2 +(Q[1]-point[1])^2;
}
Node* parentNode= insert(Q,root,0);

best_dist=distance(Q, parentNode.point);


Node* getNN(std::vector<double> Q, Node* T, int cd=0, Rect BB)
    {
// if this bounding box is too far, do nothing
    if (T == NULL || distance(Q, BB) > best_dist) return;
// if this point is better than the best:
    dist = distance(Q, T.point)
    if (dist < best_dist)
        {best = return T;
        best_dist = dist;
        }
// visit subtrees in most promising order:
    if (Q[cd] < T.point[cd]){
        NN(Q, T.right, (cd+1)%k, BB.trimRight(cd, T.point));
        NN(Q, T.left, (cd+1)%k, BB.trimLeft(cd, T.point));
        }
    else{
        NN(Q, T.right, (cd+1)%k, BB.trimRight(cd, T.point));
        NN(Q, T.left, (cd+1)%k, BB.trimLeft(cd, T.point));
        }
    }