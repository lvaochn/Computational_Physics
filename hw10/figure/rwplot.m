clear;
clc;
t = readtable("E:\Computational_Physics\hw16\Rg_data.txt");
%t2 = readtable("E:\Computational_Physics\hw10\2D_data_10000.txt");
m = table2array(t);

x = log(m(1:51,1));

y = log(m(1:51,2));
cftool;
% scatter(x,y,3,'Filled');
% xlabel({'$$x$$'},'Interpreter','latex');
% ylabel({'$$y$$'},'Interpreter','latex');
% title('3784 particles');

