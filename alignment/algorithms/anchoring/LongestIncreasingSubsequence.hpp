#ifndef _BLASR_LONGEST_INCREASING_SUBSEQUENCE_HPP_
#define _BLASR_LONGEST_INCREASING_SUBSEQUENCE_HPP_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
class RawValue
{
    int operator()(T &t) { return t; }
};

template <typename T, typename F_IntValue>
int BinarySearch(T *x, std::vector<int> &m, int i, int lenM, F_IntValue IntValue);

template <typename T, typename F_IntValue>
int LongestIncreasingSubset(T *x, int xLength, std::vector<int> &subsetIndices, std::vector<int> &m,
                            std::vector<int> &p, F_IntValue IntValue, int start = 0, int end = -1);

template <typename T, typename F_IntValue>
int LongestIncreasingSubset(T *x, int &xLength, std::vector<int> &subsetIndices);

#include "LongestIncreasingSubsequenceImpl.hpp"

#endif
