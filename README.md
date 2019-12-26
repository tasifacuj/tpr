# Intro
```
min(f(x))
with contraints
	  
gi(x) <= 0
	  
alpha(x) = sum( R1( gi(x) ) ) + sum( R2( hj(x) ) )
R1(gi(x)) = max( 0, gi(x) )^P
R2(gj(x)) = hj(x)^ 2 * P
penalty function itself: F(x,rk) = f(x) + rk * alpha(x) --> min
min(F(x, rk)) may be found by gradient descent, for example.
	 
while true
do
	F(x, r[k]) = f(x_opt) + r[k] * alpha(x_opt)
	x_opt = min( F(x, r[k]) )
	 	   
	eps = F( x[rk] ) - F(x[rk-1])
	if eps <= Epsilon
	then
	    return x_opt
	else
	    r[k+1] = Beta * r[k]
	end
done
```
# Penalty function algorithm implementation.
In order to use this stuff one must provide:
1. implemenation of the target function 
```
struct Fx{
	static ValueType apply(){...}
	static VectorT gradient(){...}
};
```
2. implemenation for all contraints
```
struct G1{
	static ValueType apply(){...}
	static VectorT gradient(){...}
};

struct G2{
	static ValueType apply(){...}
	static VectorT gradient(){...}
};
...
struct GN{
	static ValueType apply(){...}
	static VectorT gradient(){...}
};
```

Example can be found in TrainingModel.hpp