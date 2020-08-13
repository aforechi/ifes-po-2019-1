x = pi*[0:.5:2]; 
y = [0  1  0 -1  0  1  0; 
     1  0  1  0 -1  0  1];
y2 = y/2;
y3 = (y+y2)/2;
pp = spline(x,y);
pp2 = spline(x,y2);
yy = ppval(pp, linspace(0,2*pi,101));
yy2 = ppval(pp2, linspace(0,2*pi,101));
plot(yy(1,:),yy(2,:),'-b',y(1,2:5),y(2,2:5),'or')
hold on
plot(yy2(1,:),yy2(2,:),'-r',y2(1,2:5),y2(2,2:5),'or')
plot( (yy(1,:)+yy2(1,:))/2 , (yy(2,:)+yy2(2,:))/2,'-g',y3(1,2:5),y3(2,2:5),'or')
axis equal