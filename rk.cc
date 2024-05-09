#include "rk.h"

// differential equation y' = f(t, y)
double f(double t, double y)
{
    return (-0.1) * y;
}

int main()
{
    double start_time = 0.0;
    double end_time = 20.0;
    double Ts = 0.01;

    std::vector<double> times;
    RungeKutta4::fill_time_vector(times, start_time, end_time, Ts);

    std::vector<double> ys(times.size(), 0.0);
    RungeKutta4::initial_condition(ys, -3.2);

    RungeKutta4::solve<double>(times, ys, f);

    std::string file = "data.csv";
    RungeKutta4::create_csv(times, ys, file);

    return 0;
}
