#include "rk.h"

// differential equation y' = f(t, y)
double f(double t, double y)
{
    return (-15.0) * y;
}

int main()
{
    double start_time = 0.0;
    double end_time = 1.0;
    double Ts = 0.1;

    std::vector<double> times;
    ODE45::fill_time_vector(times, start_time, end_time, Ts);

    std::vector<double> ys(times.size(), 0.0);
    ODE45::initial_condition(ys, -3.2);

    ODE45::solve<double>(times, ys, f);

    std::string file = "data.csv";
    ODE45::create_csv(times, ys, file);

    return 0;
}
