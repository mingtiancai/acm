#ifndef ANTS_H
#define ANTS_H

#include <vector>

class Ants
{
public:
    Ants(int N, int L, const std::vector<int> &v)
    {
        N_ = N;
        L_ = L;
        v_ = v;
    }

    struct Result
    {
        int max_value;
        int min_value;
    };

    Result Execute();

private:
    int N_;
    std::vector<int> v_;
    int L_;
};

#endif // ANTS_H
