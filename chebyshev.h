#ifndef _CHEBYSHEV_H_
#define _CHEBYSHEV_H_

// Obtain the function implementations from the book: Press, W. H. (2007). Numerical recipes 3rd edition: The art of scientific computing. Cambridge university press.

void chebyshevFit(float a, float b, float c[], int n, float (*func)(float)); 

float chebyshevEv(float a, float b, float c[], int m, float x);

#endif /* _CHEBYSHEV_H_ */
