#include<iostream>
#include<vector>
#define K 2

int main()
{
    std::vector<double> v1;
    // v1.push_back(0.);
    v1.push_back(1.);
    // v1.push_back(1.);

    for (std::vector<double>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		std::cout << (*it) << " ";
	}
    
    return 0;

}

