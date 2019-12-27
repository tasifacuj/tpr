import math

x1 = x2 = x3 = 30.0
c = 0.5
f = 3 * x1 + 9 * x2 + 5 * x3

print( "fx = {0}".format( f ) )
g1 = 1.5 * x1 + 0.75 * x2 + 2.5 * x3 - 250
g2 = 30 - x1
g3 = 70 - x2
g4 = 50 - x3
print( "g1={0}, g2 = {1}, g3 = {2}, g4 = {3}".format(g1, g2, g3, g4) )

R1 = max( 0, g1 ) ** 2
R2 = max( 0, g2 ) ** 2
R3 = max( 0, g3 ) ** 2
R4 = max(0, g4 ) ** 2

print( "R1 = {0} \nR2 = {1} \nR3 = {2} \nR4 = {3}".format( R1, R2, R3, R4 ) )

Theta =  3 * x1 + 9 * x2 + 5 * x3 + c * ( R1 + R2 + R3 + R4 )

print( "theta = {0}".format( Theta ) )

dg1dx1 = 2 * g1 * 1.5 if g1 > 0 else 0
dg1dx2 = 2 * g1* 0.75 if g1 > 0 else 0
dg1dx3 = 2 * g1 * 2.5 if g1 > 0 else 0

dg2dx1 = 2.0 * g2 * -1.0 if g2 > 0 else 0
dg2dx2 = 0
dg2dx3 = 0

dg3dx1 = 0
dg3dx2 = 2.0 * g3 * -1.0 if g3 > 0 else 0
dg3dx3 = 0

dg4dx1 = 0
dg4dx2 = 0
dg4dx3 = 2.0 * g4 * -1.0 if g4 > 0 else 0

print( "\ndg1dx1 = {0} \ndg1dx2 = {1} \ndg1dx3 = {2}".format( dg1dx1, dg1dx2, dg1dx3 ) )
print( "\ndg2dx1 = {0} \ndg2dx2 = {1} \ndg2dx3 = {2}".format( dg2dx1, dg2dx2, dg2dx3 ) )
print( "\ndg3dx1 = {0} \ndg3dx2 = {1} \ndg3dx3 = {2}".format( dg3dx1, dg3dx2, dg3dx3 ) )
print( "\ndg4dx1 = {0} \ndg4dx2 = {1} \ndg4dx3 = {2}".format( dg4dx1, dg4dx2, dg4dx3 ) )

drdx1 = dg1dx1 + dg2dx1 + dg3dx1 + dg4dx1
drdx2 = dg1dx2 + dg2dx2 + dg3dx2 + dg4dx2
drdx3 = dg1dx3 + dg2dx3 + dg3dx3 + dg4dx3

print( "\ndrdx1 = {0} \ndrdx2 = {1} \ndrdx3 = {2}".format( drdx1, drdx2, drdx3 ) )

dtdx1 = 3 + c * drdx1
dtdx2 = 9 + c * drdx2
dtdx3 = 5 + c * drdx3

print( "\ndtdx1 = {0}\ndtdx2 = {1}\ndtdx3 = {2}\n".format( dtdx1, dtdx2, dtdx3 ) )