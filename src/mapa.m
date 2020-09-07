map = zeros(100, 100); 
map(40:50,20:80) = 1; 
goal = [50; 30]; 
start = [20; 10]; 

ds = Dstar(map);% os elementos de c serão 1 ou ∞, respectivamente, representando as células livres e ocupadas.
c = ds.costmap();% um plano para mover-se para o objetivo é gerado por
ds.plan(goal); 
% O caminho de um ponto de partida arbitrário para o objetivo
p = ds.query(start);
ds.plot(p)
