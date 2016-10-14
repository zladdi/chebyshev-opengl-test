# Interpolation using Chebyshev polynomials

TL;DR
Given an arbitrary 2D function that we wish to approximate, with y = f(x), we define its parameterized
version with a parameter t, such that x(t) = p1(t), y(t)=p2(t) and y(t) = f(x(t)).

## Build
- Obtain function implementations for the functions in chebyshev.c from the book from the book: *Press, W. H. (2007). Numerical recipes 3rd edition: The art of scientific computing. Cambridge university press.* (http://numerical.recipes/)
- Note: the code in nrutil.h and nrutil.c is the public domain (http://numerical.recipes/public-domain.html)
- Compile with command  
`make` 

## Explanation of procedure

- Sample some points (x,y) from the `test.bmp` image that are on the 2D curve:
x, y  
30,261  
46,218  
93,161  
170,107  
248,82  
347,80  
413,80  
495,112  
560,151  
624,194  
675,250  
705,311  
698,353  
637,382  
540,397  
435,398  
344,398  
244,388  
168,372  
109,351  
70,326  
39,298  
30,274  


- Define a parameterized function, for x and y direction individually. I.e. we use a parameter t in [0..n_samples-1], 
  such that x(t) == x value of sample t, and y(t) == y value of sample t, for integer t.

- Fit for both x and y dimension a Chebyshev polynomial in the range [0..n_samples-1]. For a function evaluation
  at point t, use the nearest integer value. This way, we return x(t) and y(t) at the sampled t, respectively. 

- Now, after fitting, we can evaluate for any t' in [0..n_samples-1], also at non-integer t

- x(t’), y(t’) give us the value of the 2D curve at position at t' (remember, we have a parameterized curve, and t'
  is the parameter)



