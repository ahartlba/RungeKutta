#include "mrk.h"

constexpr size_t DIMENSION = 2;

// differential equation y' = f(t, y)
std::array<double, DIMENSION> f(double t, const std::array<double, DIMENSION> &y)
{
    return std::array<double, 2>{-y[1] + 5.0 * std::sin(0.3 * t), 2.3 * y[0]};
}

int main()
{
    double start_time = 0.0;
    double end_time = 5.0;
    double Ts = 0.1;

    std::vector<double> times;
    ODE45::fill_time_vector(times, start_time, end_time, Ts);

    std::vector<std::array<double, DIMENSION>> ys(times.size(), {0.0, 0.0});
    ODE45::set_initial_condition(ys[0], {-3.2, 2.2});

    ODE45::solve<double, DIMENSION>(times, ys, f);

    std::string file = "data.csv";
    ODE45::create_csv(times, ys, file);

    return 0;
}
