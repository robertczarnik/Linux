t = linspace(0, 2*pi, 81);
p = linspace(0, pi/2, 21);
[tt,pp] = meshgrid(t, p);
r = 2 * cos(pp);
x = r .* sin(pp) .* cos(tt);
y = r .* sin(pp) .* sin(tt);
z = r .* sin(pp);
mesh(x,y,z)
axis off
print -dfig f3.fig