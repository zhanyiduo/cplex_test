\ENCODING=ISO-8859-1
\Problem name: IloCplex

Minimize
 obj: x1 + x2 + x3 + x4 + x5
Subject To
 contraint_1#0: 5 x1 + 6 x2 >= 20
 contraint_2#1: x2 + x3 >= 4
 contraint_3#2: x1 + 3 x3 >= 9
Bounds
 0 <= x4 <= 1
      x5 = 0
Binaries
 x4 
End
