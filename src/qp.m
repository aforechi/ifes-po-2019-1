c = [15 30];
Q = [4 -4; -4 8];
A = [1 2];
b = [30];
x = quadprog(Q, -c, A, b)
