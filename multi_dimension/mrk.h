#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <array>
#include <math.h>

namespace ODE45
{
    template <typename T, size_t N>
    std::array<T, N> kn(T tn, const std::array<T, N> &yn, const std::function<std::array<T, N>(T, const std::array<T, N> &)> &func)
    {
        return func(tn, yn);
    }

    template <typename T, size_t N>
    std::array<T, N> knp1(T tn, const std::array<T, N> &yn, T h, const std::array<T, N> &kn_, const std::function<std::array<T, N>(T, const std::array<T, N> &)> &func)
    {
        std::array<T, N> yn_temp;
        for (size_t i = 0; i < N; ++i)
        {
            yn_temp[i] = yn[i] + 0.5 * h * kn_[i];
        }
        return func(tn + 0.5 * h, yn_temp);
    }

    template <typename T, size_t N>
    std::array<T, N> step(T tn, const std::array<T, N> &yn, T h, const std::function<std::array<T, N>(T, const std::array<T, N> &)> &func)
    {
        std::array<T, N> kn1_ = kn<T, N>(tn, yn, func);
        std::array<T, N> kn2_ = knp1<T, N>(tn, yn, h, kn1_, func);
        std::array<T, N> kn3_ = knp1<T, N>(tn, yn, h, kn2_, func);
        std::array<T, N> kn4_ = knp1<T, N>(tn, yn, h, kn3_, func);

        std::array<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = yn[i] + (h / 6.0) * (kn1_[i] + 2 * kn2_[i] + 2 * kn3_[i] + kn4_[i]);
        }
        return result;
    }

    template <typename T>
    void fill_time_vector(std::vector<T> &v, T start_time, T end_time, T Ts)
    {
        for (T i = start_time; i < end_time; i += Ts)
        {
            v.push_back(i);
        }
    }

    template <typename T, size_t N>
    void set_initial_condition(std::array<T, N> &v, const std::array<T, N> &ic)
    {
        v = ic;
    }

    template <typename T, size_t N>
    void create_csv(const std::vector<T> &times, const std::vector<std::array<T, N>> &values, const std::string &filename)
    {
        std::ofstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file << "Time";
        for (size_t i = 0; i < N; ++i)
        {
            file << ",Value_" << i;
        }
        file << std::endl;

        for (size_t i = 0; i < times.size(); ++i)
        {
            file << times[i];
            for (size_t j = 0; j < N; ++j)
            {
                file << "," << values[i][j];
            }
            file << std::endl;
        }

        file.close();
    }

    template <typename T, size_t N>
    void solve(const std::vector<T> &times, std::vector<std::array<T, N>> &values, const std::function<std::array<T, N>(T, const std::array<T, N> &)> &func)
    {
        for (size_t i = 0; i < times.size() - 1; ++i)
        {
            T t = times[i];
            T Ts = times[i + 1] - times[i];
            values[i + 1] = step<T, N>(t, values[i], Ts, func);
        }
    }
}