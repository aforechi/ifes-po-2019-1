desc = readtable('../portfolio_desc.csv');
rets = csvread('../portfolio_med.csv', 1);
covs = csvread('../portfolio_cov.csv', 1);
c = rets(:,1)';
ub = rets(:,2)';
lb = zeros(size(c));
Q = covs;
A = ones(size(c));
b = [1];
x = quadprog(Q, -c, A, b, [], [], lb, ub);
for i= 1:numel(c)
    if x(i) > 0.01
        fprintf('%s = %f\n',desc.TICKER{i}, x(i));
    end
end
