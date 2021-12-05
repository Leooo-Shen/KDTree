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
    std::vector<int> point;
    Node * left;
    Node * right;
    Node(std::vector<int> Tpoint){
        point=Tpoint;
    }
};
Node * insert(std::vector<int> x, Node * parent, int cd) {
    
    if(parent->point.empty()){ 
        Node * parent=new Node(x);}
    else if (x == parent->point)
      {// error! duplicate
      }
    else if (x[cd] < parent->point[cd])
      { 
        parent->left = insert(x, parent->left, (cd+1) % k);
    }else{
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
    Node *root;
    for(int i=0;i<convert_csv.size();i++){
        insert(convert_csv[i],root,0);
    }
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
    //print_array(value_vectors);
    create_csv_Tree(value_vectors);
    //Node root(value_vectors[0]);
    //visualize_tree(root);
    //generate_csv();
    
    
}