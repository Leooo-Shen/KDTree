#include "my_kd_tree.h"
#include <math.h>

double distance(std::vector<double> a, std::vector<double> b)
{
    double dist = 0;
    for (unsigned i=0; i < a.size(); i++)
    {
        dist += pow((a[i] - b[i]),2);
    }
    return sqrt(dist);
}



