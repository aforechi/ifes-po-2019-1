x = optimvar('x','LowerBound',0,'UpperBound',inf);
y = optimvar('y','LowerBound',0,'UpperBound',inf);
prob = optimproblem('Objective',x + y,'ObjectiveSense','max');
prob.Constraints.c1 = x + y >= 4;
prob.Constraints.c2 = -x + 2*y <= 4;
problem = prob2struct(prob);problem = prob2struct(prob);
[sol,fval,exitflag,output] = linprog(problem)