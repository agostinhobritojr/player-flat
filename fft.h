#ifndef FFT_H
#define FFT_H

#include <complex>
#include <iostream>
#include <valarray>

/**
 * @brief PI is just PI
 */
const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

/**
 * @brief fft calcs forward FFT transform
 * @param x is the array to be transformed. The result is placed directly
 * into x
 */

void fft(CArray& x);

#endif
