// gradient_descend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <math.h>
#include <iostream>
#include <vector>
#define eps 10e-5

using std::cout;


struct Descend {
    double learning_rate;
    double (*funct)(std::vector<double>);
    std::vector<double> current_position;

    Descend(std::vector<double> start_position, double learning_rate, double(*funct)(std::vector<double>))
    {
        this->learning_rate = learning_rate;
        this->funct = funct;
        this->current_position = start_position;
    }

    void step()
    {
        std::vector<double> grad = this->current_grad();
        for (int i = 0; i < current_position.size(); i++) {
            double x = current_position[i] - grad[i] * learning_rate;
            current_position[i] = x;
        }
    }

    std::vector<double> current_grad()
    {
        std::vector<double> grad(current_position.size());

        for (int i = 0; i < current_position.size(); i++) {
            long double temp_pose = current_position[i];

            current_position[i] = temp_pose + eps;
            long double left_value = (this->funct)(current_position);

            current_position[i] = temp_pose - eps;
            long double right_value = (this->funct)(current_position);

            grad[i] =  (left_value - right_value) / (2 * eps);

            current_position[i] = temp_pose;
        }
        return grad;
    }

    void to_string() 
    {
        for (int i = 0; i < current_position.size(); i++)
        {
            std::cout << current_position[i] << std::endl;
        }
    }
};

double my_function(std::vector<double> x)
{
    return abs(x[0]) + abs(x[1]) + abs(x[2]) + abs(x[3]) + abs(x[4]) + 5 * cos(x[1]);
}


void test1() 
{
    const int size = 5;
    double (*foo)(std::vector<double>) = my_function;
    std::vector<double> arr = { 1.0, 1.0, 1.0, 10.0, 1.0 };

    double learning_rate = 0.5;
    Descend booba = Descend(arr, learning_rate, foo);
    for (int i = 0; i < 20; ++i)
    {
        booba.step();
        booba.to_string();
        std::cout << std::endl;
    }

    booba.to_string();
}

int main()
{
    test1();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
