#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <ctime>

#include "../include/utils.h"

extern const int k;

/*
    General utility functions/ helper functions for testing, printing, and generating data for KD trees
*/

std::ostream &operator<<(std::ostream &os, std::vector<double> vec)
{
    // Reload the << to ouput vectors more conviently
    for (const auto &elem : vec)
    {
        os << elem << " ";
    }
    os << '\n';
    return os;
}

std::vector<std::vector<double>> generate_numbers(int n, unsigned k)
{
    /*
    Generate fake data of k-dimensions;
    param:
        inputs:
            n: total numbers of vectors want to generate (int)
        returns:
            generated_int: a general vector of generated value vectors (std::vector<std::vector<double>>)

    */
    srand(time(0));
    std::vector<std::vector<double>> generated_values(n, std::vector<double>(k, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            generated_values[i][j] = (double)rand() / RAND_MAX * 300 - 150;
        }
    }
    return generated_values;
}

void print_vector(const std::vector<double> &Vector)
{
    // print vector
    std::cout << "[";
    std::string messy{""};
    for (auto elements : Vector)
    {
        messy = messy + std::to_string(elements) + ",";
    }
    messy.pop_back();
    std::cout << messy;
    std::cout << "]";
    std::cout << std::endl;
}

void write_to_csv(const std::vector<std::vector<double>> &generated_numbers,
                  const std::string &filename)
{

    /*
    Create csv file from vector of vectors;
    param:
        inputs:
            generated_numbers: vector of vectors containing all data inputs (could've been generated from generated numbers for example)
            filename: filepath of csv file to be filled in with from generated_numbers

    */

    // open file stream for output
    std::ofstream csv_file(filename);

    // csv column headers
    csv_file << "generated k-dimension data, k = " << k << "\n";

    for (size_t i = 0; i < generated_numbers.size(); i++)
    {
        csv_file << generated_numbers[i];
    }
    csv_file.close();

    std::cout << "File saved at: " << filename << std::endl;
}

std::vector<std::vector<double>> read_from_csv(const std::string &filename)
{
    /*
    Create vector of vectors from csv file (the opposite of write_to_csv);
    param:
        inputs:
            filename: filepath of csv to be read from
        returns:
            vector of vectors based on the csv file

    */

    clock_t startTime = clock();

    std::ifstream ifs(filename);
    std::vector<std::vector<double>> value_vectors;
    std::vector<double> point;
    double single_value;

    if (ifs.is_open())
    {
        std::cout << "Opening the file: " << filename << std::endl;
        std::string line;
        // throw away first line: contains csv header
        std::getline(ifs, line);

        // while lines in csv
        while (std::getline(ifs, line))
        {
            std::stringstream line_stream(line);
            while (line_stream >> single_value)
            {
                point.push_back(single_value);
            }
            value_vectors.push_back(point);
            point.clear();
        }
        ifs.close();
        clock_t endTime = clock();
        std::cout << "[Time cost in read_from_csv: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s]" << std::endl;
    }

    else
    {
        std::cout << "Cannot open the file" << std::endl;
    }
    return value_vectors;
}

// Helper functions for the Nearest Neighbour search
// (https://en.wikipedia.org/wiki/K-d_tree#Nearest_neighbour_search)
double distance(std::vector<double> A, std::vector<double> B)
{
    /*
    Find the distance between two vector A and vector B;
    param:
        inputs:
            A,B: double vector
        returns:
            L2 distance between A and B

    */
    double dist = 0;
    for (unsigned i = 0; i < A.size(); i++)
    {
        dist += pow((A[i] - B[i]), 2);
    }
    return sqrt(dist);
}

double max(double a, double b, double c)
{
    /*
    Find the maximum between three doubles
    param:
        inputs:
            a,b,c: doubles
        returns:
            max(a,b,c)
    */
    if (a > b)
    {
        if (a > c)
        {
            return a;
        }
        else
        {
            return c;
        }
    }
    else
    {
        if (b > c)
        {
            return b;
        }
        else
        {
            return c;
        }
    }
}

double distance(std::vector<double> Q, std::shared_ptr<Rect> BB)
{
    /*
    Find the distance between vector Q and rectangle BB, if vector Q is in rectangle BB the distance is 0
    param:
        inputs:
            Q: vector of doubles
            BB: Rectangle struct with 4 vertices, defined and initialized in rect.h
        returns:
            L2 distance between Q and BB given that Q is outside of Rect BB

    */
    auto dx = max(Q[0] - BB->Xmin, 0.0, Q[0] - BB->Xmax);
    auto dy = max(Q[1] - BB->Ymin, 0.0, Q[1] - BB->Ymax);
    return sqrt(dx * dx + dy * dy); // ONLY DONE FOR K=2 :(((
}
