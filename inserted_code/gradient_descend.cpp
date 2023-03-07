// gradient_descend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>


#define eps 10e-5

const double eps2 = 1 / (2 * eps);

using std::cout;


struct Descend {
    double learning_rate;
    double (*funct)(std::vector<double>);
    int size;
    std::vector<double> current_position;

    Descend(std::vector<double> start_position, double learning_rate, double(*funct)(std::vector<double>))
    {
        this->learning_rate = learning_rate;
        this->funct = funct;
        this->current_position = start_position;
        this->size = start_position.size();
    }

    void step()
    {
        std::vector<double> grad = this->current_grad();
        for (int i = 0; i < size; i++) {
            double x = current_position[i] - grad[i] * learning_rate;
            current_position[i] = x;
        }
    }

    std::vector<double> current_grad()
    {
        std::vector<double> grad(size);
        for (int i = 0; i < size; i++) {
            double temp_pose = current_position[i];

            current_position[i] = temp_pose + eps;
            double left_value = (this->funct)(current_position);

            current_position[i] = temp_pose - eps;
            double right_value = (this->funct)(current_position);
	    asm(
	    	"fldl %[R]\n\t"
	    	"fldl %[L]\n\t"
	    	"fsubp\n\t"
	    	"fldl %[EPS]\n\t"
	    	"fmulp %%st(0), %%st(1)\n\t"
		"fstpl %[DST]\n\t"
		
		:[DST]"=m"(grad[i])
		:[L]"m"(left_value), [R]"m"(right_value), [EPS]"m"(eps2)
		:"cc"
	    );
            current_position[i] = temp_pose;
        }
        return grad;
    }
};

double my_function(std::vector<double> x)
{
    return abs(x[0]) + abs(x[1]) + abs(x[2]) + abs(x[3]) + abs(x[4]) + 10 * cos( 0.5 * x[1] + 0.2 * x[2] - 0.3 * x[4]);
}


std::vector<double> test1() 
{
    const int size = 5;
    double (*foo)(std::vector<double>) = my_function;
    std::vector<double> arr = { 1.0, 1.0, 1.0, 10.0, 1.0 };

    double learning_rate = 0.01;
    Descend model = Descend(arr, learning_rate, foo);
    for (int i = 0; i < 20000; ++i)
    {
        model.step();
    }

    return model.current_position;
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::vector<double> result;
    for(int i=0; i < 10; i++)
    {
        result = test1();
        result = test1();
        result = test1();
        result = test1();
        result = test1();
        result = test1();
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    std::cout << "\nelapsed time: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << std::endl;
     
    int size = 5;

    std::ofstream myfile("inserted_result.txt");
    if (myfile.is_open())
    {
        myfile << "result:\n";
        for(int count = 0; count < size; count ++){
            myfile << result[count] << " " ;
        }
        myfile << "\n\nelapsed time:\n";
        myfile << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
        myfile.close();
    }
}
