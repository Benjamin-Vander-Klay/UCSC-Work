% BVK ECE167 Lab3 

%% Part 1
% calibration data

%% Z axis acceration data  
Z_acc_pos = importdata("Z_acc1_pos.log");
Z_acc_neg = importdata("Z_acc2_ negative.log");
acc_data = importdata("acc_data3.txt");

x = acc_data(:,1);
y = acc_data(:,2);
z = acc_data(:,3);

close all
figure(1)
scatter3(x,y,z)


new_x = x ./ 1000
new_y = y ./ 1000
new_z = z ./ 1000

figure(2)
scatter3(new_x,new_y,new_z)


Z_acc_pos_avg = mean(Z_acc_pos);
Z_acc_neg_avg = mean(Z_acc_neg);

scale_Zacc =  2.000 / (Z_acc_pos_avg - Z_acc_neg_avg) 



%% Magnitomiter>?
close all

mag_xneg = importdata("magX1_neg.txt");
mag_xpos = importdata("magX2_pos.txt");

mag_ypos = importdata("magY1_pos.txt");
mag_yneg = importdata("magY2_neg.txt");

mag_zpos = importdata("magZ1_pos.txt");
mag_zneg = importdata("magZ2_neg.txt");

mag_data = importdata("mag_data4.txt");

 x = [mag_data(:,1)];
 y = [mag_data(:,2)];
 z = [mag_data(:,3)];


% mag_data_x = mag_data_all(:,1);
% mag_data_y = mag_data_all(:,2);
% mag_data_z = mag_data_all(:,3);

% Clean the data
size_magx_pos = size(mag_xpos);
size_magx_neg = size(mag_xneg);

size_magy_pos = size(mag_ypos);
size_magy_neg = size(mag_yneg);

size_magz_pos = size(mag_zpos);
size_magz_neg = size(mag_zneg);

% for i = 0: size_magx_pos(1)
mag_xpos = mag_xpos(125:606,:);
mag_xneg = mag_xneg(497:978,:);

mag_ypos = mag_ypos(339:820,:);
mag_yneg = mag_yneg(700:1181,:);

mag_zpos = mag_zpos(:,:); % this is our min anyways
mag_zneg = mag_zneg(1104:1585,:);


hold on
figure(1)
xlabel('X axis')
ylabel('Y axis')
zlabel('Z axis')
scatter3(x,y,z, '.'); % X max/min
% scatter3(y(:,1),y(:,2),y(:,3)); % y
% scatter3(z(:,1),z(:,2),z(:,3)); % z
% trim to 482 indicies
hold off


 x_max = max(mag_xpos(:,1)) 
   
 x_min = min(mag_xneg(:,1))
 
 y_max = max(mag_ypos(:,2))

 y_min = min(mag_yneg(:,2))
 
 z_max = max(mag_zpos(:,3))

 z_min = min(mag_zneg(:,3))

% gives the center
 x_bias  = (x_max + x_min) / 2
 y_bias  = (y_max + y_min) / 2
 z_bias  = (z_max + z_min) / 2

 % scale
x_scale =  47332 / (x_max - x_bias); % 22644
% x_scale_neg =  -47332/ (x_min - x_bias) % -22644
 
y_scale =  47332 / (y_max - y_bias); % 5190
% y_scale_neg =  -47332/ (y_min - y_bias) % -5190v

z_scale =  47332 / (z_max - z_bias); % 41234
% z_scale_neg =  -47332/ (z_min - z_bias) % -41234


x_new = (x - x_bias) .* x_scale;
y_new = (y - y_bias) .* y_scale;
z_new = (z - z_bias) .* z_scale;

hold on
figure(2)
scatter3(x_new, y_new, z_new); % X max/min
xlabel('X axis')
ylabel('Y axis')
zlabel('Z axis')
% scatter3(y_new(:,1),y_new(:,2),y_new(:,3)); % Y
% scatter3(z_new(:,1),z_new(:,2),z_new(:,3)); % Z
% trim to 482 indicies
hold off

  x_max = max(x) 
  x_avg = mean(x) 
  x_min = min(x)
 
  y_max = max(y) 
  y_avg = mean(y) 
  y_min = min(y)

  z_max = max(z) 
  z_avg = mean(z) 
  z_min = min(z)
%% Gyro Section 
close all
%C'mon b aby lets get it

%IMPORT DATA (10 second sample)
x_gyro = importdata("gyro_1_x.txt")
y_gyro = importdata("gyro_3_y.txt")
z_gyro = importdata("gyro_5_z.txt")

gyro_hour = importdata("gyro_hour3_total.txt")


% Take only the column we want
x_gyro = x_gyro(:,1)
y_gyro = y_gyro(:,2)
z_gyro = z_gyro(:,3)

% average the 10 second data -simple average
x_avg_bias = mean(x_gyro)
y_avg_bias = mean(y_gyro)
z_avg_bias = mean(z_gyro)

% RESULTS:
% x_avg_bias =
% 
%   -11.5266
% 
% 
% y_avg_bias =
% 
%   -39.9257
% 
% 
% z_avg_bias =
% 
%    16.2556

gyro_hour_biased = [(gyro_hour(:,1) - x_avg_bias), (gyro_hour(:,2) - y_avg_bias), (gyro_hour(:,3) - z_avg_bias)]
sz_gyro = size(gyro_hour_biased);

timeline = .1:.1:3522.5

x_drift_cum = cumtrapz(timeline, gyro_hour_biased(:,1))
y_drift_cum = cumtrapz(timeline, gyro_hour_biased(:,2))
z_drift_cum = cumtrapz(timeline, gyro_hour_biased(:,3))

figure(2)
hold on
title('X drift')
% plot(linspace(0, 60, sz_gyro(1)),  gyro_hour_biased(:,1), '.');
plot(x_drift_cum);
hold off

figure(3)
hold on
title('Y drift')
plot(linspace(0, 60, sz_gyro(1)),  gyro_hour_biased(:,2), '.');
hold off

figure(4)
hold on
plot(linspace(0, 60, sz_gyro(1)),  gyro_hour_biased(:,3), '.');
ylim([-800,800])
title('Z drift')
hold off
% * 1000 to get better value - integer math

given_scale = 131 * 4 % four is a random number that i stole from the whiteboard. just make it work
x_bias_angle = x_avg_bias *1000 / given_scale
y_bias_angle = y_avg_bias *1000 / given_scale
z_bias_angle = z_avg_bias *1000 / given_scale







%% Part 4


[Atilde,Btilde] = CalibrateEllipsoidData3D(x,y,z,20,0)

[Xcorr,Ycorr,Zcorr] = CorrectEllipsoidData3D(Xmeas,Ymeas,Zmeas,Atilde,Btilde)

