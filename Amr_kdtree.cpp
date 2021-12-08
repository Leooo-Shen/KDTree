#include<iostream>
#include<fstream>
#include<vector>
int k{3};

std::vector<std::vector<int>> generate_numbers(int n){
    std::vector<std::vector<int>> generated_int(n,std::vector<int>(k,0));
    for(int i=0; i<n;i++)
        {
        for(int j=0;j<k;j++){generated_int[i][j]=(rand()%100);}
        }
    return generated_int;
}

void print_array(std::vector<std::vector<int>> generate_numbers)
    {
    for(auto vectors: generate_numbers)
        {
        for(auto element: vectors){std::cout<< element<<", ";}
        std::cout<<"\n";}
    }

struct Node{
    std::vector<int> point{0,0,0};
    Node * left=NULL;
    Node * right=NULL;
    Node(std::vector<int> Tpoint){
        // point=Tpoint;
        for(int i=0;i<k;i++){
            point[i]=Tpoint[i];    
        }
        left=right=NULL;
    }
};

Node * insert(std::vector<int> x, Node * parent, int cd) {
    
    if(parent ==NULL){ 
        Node * parent=new Node(x);
        std::cout<<"Successfully created a Node\n ";
        return parent;}
    else if (x == parent->point)
      {// error! duplicate
      }
    else if (x[cd] < parent->point[cd])
      { std::cout<<"Successfully created a Left pointer\n ";
        parent->left = insert(x, parent->left, (cd+1) % k);
    }else{
        std::cout<<"Successfully created a Right pointer\n ";
        parent->right = insert(x, parent->right, (cd+1) % k);
   }
   return parent;
}

void generate_csv(){
    std::ofstream write_csv_file("./test_numbers1.csv");
    write_csv_file << "x,y,z\n";
    for(int i=0; i<100;i++){
        std::string n1= std::to_string(rand()%100)+ ",";
        std::string n2= std::to_string(rand()%100)+ ",";
        std::string n3= std::to_string(rand()%100)+ "\n";
        write_csv_file << n1+n2+n3;
    }
    write_csv_file.close();
}

std::vector<std::vector<int>> delete_number(std::vector<std::vector<int>> generated_numbers, int index){
    std::vector<std::vector<int>> changed_array(generated_numbers.size()-1,std::vector<int>(k,0));
    int a=0;
    for(int i=0;i<generated_numbers.size();i++){
        
        if(i==index){}
        else{
            for(int j=0;j<k;j++){
            changed_array[a][j]=generated_numbers[i][j];
                }
                a++;
            }
            
    }
    return changed_array;
}

std::vector<std::vector<int>> convert_csv(std::string filename){
    std::ifstream read_csv_file;
    read_csv_file.open(filename);
    std::vector<std::vector<std::string>> converted_array;
    std::vector<std::vector<int>> converted_int_array;
    for(int i=0;read_csv_file.good();i++){
        std::getline(read_csv_file,converted_array[i][0],',');
        converted_int_array[i][0]=std::stoi(converted_array[i][0]);
        std::getline(read_csv_file,converted_array[i][1],',');
        converted_int_array[i][0]=std::stoi(converted_array[i][1]);
        std::getline(read_csv_file,converted_array[i][2],',');
        converted_int_array[i][0]=std::stoi(converted_array[i][2]);
    }
    read_csv_file.close();
    
    return converted_int_array;
}

void create_csv_Tree(std::vector<std::vector<int>> convert_csv){
    Node* root{NULL};
    std::vector<std::vector<Node*>> Tree{};
    std::vector<Node*> Nodes(100);
    std::cout<<convert_csv.size();
    for(int i=0;i<convert_csv.size();i++){
        root=insert(convert_csv[i],root,0);
    }
    // std::cout<< convert_csv[0][0]<<Nodes[0]->point[0];
    // std::cout<<"----------\n";
    // std::cout<<Nodes[1]->point[0]<<"\n";
    // std::cout<<"----------\n";
    // for(int i=0;i<convert_csv.size()-1;i++){
    //     insert(convert_csv[i+1],Nodes[i],0);
    // }
    // std::vector<int> tester=Tree[6]->left->point;
    // for(int element:tester){
    //     std::cout<< element<<",";
    // }
    //we want to read from test_numbers and add nodes iteratively 

};

void visualize_tree(Node parent){
    //can make a local function here
    
        std::cout<<"[";
        for(int i=0;i<parent.point.size();i++){
            std::cout<< parent.point[i] +",";
        }
        std::cout<<"]\n";
        if(parent.left!=NULL){
            
            visualize_tree(*parent.left); }
        if(parent.right!=NULL){
            std::cout<<"             ";
            visualize_tree(*parent.right);
        }
    

}

int main(){
    
    auto value_vectors=generate_numbers(100);
    auto deleted_vectors=delete_number(value_vectors,4);
     print_array(deleted_vectors);
     std::cout<<"--------------\n";
     print_array(value_vectors);
    //  create_csv_Tree(value_vectors);
    //Node root(value_vectors[0]);
    //visualize_tree(root);
    //generate_csv();
    
    
}