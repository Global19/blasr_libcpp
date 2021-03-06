#ifndef _BLASR_PDFS_HPP_
#define _BLASR_PDFS_HPP_

#include <cassert>
#include <cmath>

#include <alignment/statistics/StatUtils.hpp>

float Binomial(float p, int x, int n);

float Poisson(float lambda, int n);

float Gamma(float lambda, float t, int n);

float Exponential(float lambda, int t);

#endif
