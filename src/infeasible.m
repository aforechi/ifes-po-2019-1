x = optimvar('x','LowerBound',0,'UpperBound',inf);
y = optimvar('y','LowerBound',0,'UpperBound',inf);
prob = optimproblem('Objective',4*x + 4*y,'ObjectiveSense','min');
prob.Constraints.c1 = x + -y <= 1;
prob.Constraints.c2 = x + 2*y >= 1;
problem = prob2struct(prob);problem = prob2struct(prob);
[sol,fval,exitflag,output] = linprog(problem)