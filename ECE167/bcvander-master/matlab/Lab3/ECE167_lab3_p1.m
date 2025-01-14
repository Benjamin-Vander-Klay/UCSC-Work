% BVK ECE 167 Lab 3 pt 1 matlab calibration
% 5/2/2023

clear all

%% 

disp("ECE 167 Lab 3 Part: 1")

% bring the data in
EllipseXYData
%vector = ones[]
X = -1.*(Xmeas.^2)
A = [-2.*Xmeas, Ymeas.^2, -2.*Ymeas, ones(size(Ymeas))]

% Z = X \ A
Z = lsqr(A,X)
% Z = mldivide(X,A)

% now solve for the actual internal values
% syms x_o y_o a b
% eqn1 = x_o == Z(1)
% eqn2 = a^2 / b^2 == Z(2)
% eqn3 = (a^2 * y_o) / b^2 == Z(3) % changed y_o from ^2
% eqn4 = (x_o^2) + ((a^2 * y_o^2) / b^2) - (a^2 * R^2) == Z(4)
% 
% sol = solve([eqn1, eqn2, eqn3, eqn4], [x_o y_o a b]);
% xoSol = double(sol.x_o(1))
% yoSol = double(sol.y_o(1))
% aSol  = double(sol.a(1))
% bSol  = double(sol.b(1))

%   xoSol = sol.x_o
%   yoSol = sol.y_o
%   aSol  = sol.a
%   bSol  = sol.b

  % these are all 16 x 1
  % some are all the same, most have variations
  % just going to take the 1st solution of each for now



  % this did not work real well :^(
    % post algebra. coudln't figure the mabtlab out
y_o = Z(3)/Z(2)
x_o = Z(1)
a = sqrt(x_o^2 + y_o^2 * Z(2) - Z(4))
b = a / sqrt(Z(2))

  % deal with this later *************88   


  % try and get new values 
x_new = (Xmeas - x_o) ./ a
y_new = (Ymeas - y_o) ./ b
    
% Norm2_meas_x = sqrt(transpose(Xmeas) * Xmeas)
% Norm2_meas_y = sqrt(transpose(Ymeas) * Ymeas)


norm_meas = sqrt(Xmeas.^2 + Ymeas.^2)
norm_new =  sqrt(x_new.^2 + y_new.^2)
figure(1)
% scatter(linspace(-3,3,size(norm_meas)), )
% norm_meas = zeros(size(Xmeas));
% 
% for index = 1:size(Xmeas, 1)
%     norm_meas(index) = norm(Xmeas(index), Ymeas(index));
% end
% 
% % plot it
close all
figure(1)
hold on
plot(x_new,y_new, '.')
plot(Xmeas,Ymeas, 'o')

axis([-2 2 -3 3])
hold off
figure(2)
hold on
plot(norm_meas, '.');
plot(norm_new, 'o');
  
% Norm2_new_x = sqrt(transpose(X_new) * X_new + transpose(Y_new) * Y_new)
% Norm2_new_y = sqrt(transpose(Y_new) * Y_new)
% figure(2)
% plot()


%% 
disp("ECE 167 Lab 3 Part: 2")