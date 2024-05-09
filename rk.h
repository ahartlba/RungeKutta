/* Implementation of 4th order Runge Kutta
 *
 * Fully templated, and easily expandable.
 * Implemented for curiosity.
 */
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace RungeKutta4
{

    template <typename T>
    T kn(T tn, T yn, std::function<T(T, T)> func)
    {
        return func(tn, yn);
    }

    template <typename T>
    T knp1(T tn, T yn, T h, T kn_, std::function<T(T, T)> func)
    {
        return func(tn + 0.5 * h, yn + 0.5 * h * kn_);
    }

    template <typename T>
    T step(T tn, T yn, T h, std::function<T(T, T)> func)
    {
        T kn1_ = kn<T>(tn, yn, func);
        T kn2_ = knp1<T>(tn, yn, h, kn1_, func);
        T kn3_ = knp1<T>(tn, yn, h, kn2_, func);
        T kn4_ = knp1<T>(tn, yn, h, kn3_, func);
        return yn + (h / 6.0) * (kn1_ + 2 * kn2_ + 2 * kn3_ + kn4_);
    }

    template <typename T>
    void print_vec(const std::vector<T> &v)
    {
        for (T n : v)
            std::cout << n << ' ';
        std::cout << std::endl;
    }

    template <typename T>
    void fill_time_vector(std::vector<T> &v, T start_time, T end_time, T Ts)
    {
        for (T i = start_time; i < end_time; i += Ts)
        {
            v.push_back(i);
        }
    }

    template <typename T>
    void initial_condition(std::vector<T> &v, T ic)
    {
        v[0] = ic;
    }

    template <typename T>
    void create_csv(const std::vector<T> &times, const std::vector<T> &values, const std::string &filename)
    {
        std::ofstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file << "Time,Value" << std::endl;

        for (size_t i = 0; i < times.size(); ++i)
        {
            file << times[i] << "," << values[i] << std::endl;
        }

        file.close();
    }

    template <typename T>
    void solve(const std::vector<T> &times, std::vector<T> &values, std::function<T(T, T)> func)
    {
        for (size_t i = 0; i < times.size() - 1; ++i)
        {
            T t = times[i];
            T Ts = times[i + 1] - times[i];
            values[i + 1] = step<T>(t, values[i], Ts, func);
        }
    }
}