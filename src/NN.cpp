#include<iostream>
#include<math.h>
#include "my_kd_tree.h"


auto value_vectors = std::vector<std::vector<double>> {{51,75}, {25,40},{70,70},{55,1},{60,80},{10,30},{35,90},{1,10},{50,50}};


double distance(std::vector<double> A, std::vector<double> B){
    double dist = 0;
    for (unsigned i=0; i < A.size(); i++)
    {
        dist += pow((A[i] - B[i]),2);
    }
    return sqrt(dist);
}


double best_dist=-1;



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


double distance(std::vector<double>  Q,Rect* BB){
    auto dx= max(BB->Xmin-Q[0],0.0,BB->Xmax-Q[0]);
    auto dy = max(BB->Ymin-Q[1],0.0,BB->Ymax-Q[1]);
    return sqrt(dx*dx+dy*dy); // ONLY DONE FOR K=2 :(((
}


Node* searchNN(std::vector<double> Q, Node* Root, int cd=0,Rect* BB=new Rect(0,0,100,100))
{
    Node* best=nullptr;
    if(best_dist==-1){
        Node* currentNode= insert(Q,Root,0); 
        //insert point Q into tree
        // print_kd_tree("",currentNode,false);
        //inserted query point to find initial best estimate"
        auto catchv=0;
        best=currentNode;
        while(!currentNode->isLeaf())
        {
            
            if(Q[cd]<currentNode->point[cd]){
                best=currentNode;
                if(!(currentNode->left == nullptr)) currentNode= currentNode->left; //safety
            }
            else{best=currentNode;
                if(!(currentNode->right == nullptr)) currentNode= currentNode->right;} //safety}
            // std::cout<<currentNode->isLeaf();
            cd=(cd+1)%2;
            
        }
        best_dist= distance(Q, best->point);
        std::cout<<"intial best: "<< best_dist<<std::endl;
        print_vector(best->point);
        Root= delete_node(value_vectors, Q);
    }

    //Now we check neighboring nodes :)
    if(Root==nullptr || distance(Q,BB)>best_dist){return nullptr;}  
    double dist=distance(Q,Root->point); 
    if(dist<best_dist){
        best=Root;
        best_dist=dist;
    }
    if(Q[cd]<Root->point[cd]){
        searchNN(Q,Root->left,(cd+1)%2, BB->trimLeft(cd,Root->point));
        searchNN(Q,Root->right,(cd+1)%2, BB->trimRight(cd,Root->point));
    }
    else{
        searchNN(Q,Root->right,(cd+1)%2, BB->trimRight(cd,Root->point));
        searchNN(Q,Root->left,(cd+1)%2, BB->trimLeft(cd,Root->point));

    }
    std::cout<<"final best: "<< best_dist<<std::endl;
    return best;
}


int main()
{   
    //Testing Rect
    
    //  Rect* rect=new Rect(0,0,80,80);
    //  Rect* newrect= rect->trimLeft(0,{52,52});

    //  std::cout << " Xmin: "<< newrect->Xmin<< " Xmax: "<<newrect->Xmax<<" Ymin: "<<newrect->Ymin<<" Ymax: "<<newrect->Ymax;
    // std::cout<<distance(target,rect);
    //---------------------------------------
    Node *root = nullptr;
    
    for (auto &elem : value_vectors)
        {
            root = insert(elem, root);
        }
    Rect* rect=new Rect(0,0,80,80);
    auto target = std::vector<double>{52,52};
    auto NN = searchNN(target, root,0, rect);
    print_vector(NN->point);
}