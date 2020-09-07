
% 
% 
% 采用与实际相符的参数进行仿真 


% 添加系统所等效的 弹簧质量块收到相同输入的响应曲线
function impedance_control_real()

    clc
    clear
    wn = 2;yita=0.507;
    global M L Uu T
    % System Parameters 
    M=0.01; L=0.3; J=M*L^2/12;                   % plant
    
    Mm = 0.001;Lm=0.2;Jm=Mm*Lm^2/12;             % controller 


    % Controller constants 
    K=wn^2
    D=2*yita*wn
    h=0.01;                                     % sampling period
    T=10;                                        % simualtion time span
    PT=T*100;                                   % half period of the command input


    % Initialization  
    th_ref=0;th_ref_dot=0;th_ref_ddot=0;th_ref0=th_ref/2;th_refv=th_ref0;  % initial values of the reference model and the command input 
    theta=0.0; theta_dot=0.0;xp = [theta;theta_dot];                        % initial plant outputs and state
        
    for i=1: T/h 
       TT(i)=(i-1)*h;                   %time
    % calculate the control input Uu(i) based on xc(i), theta(i), theta_dot(i)
       Uu=Jm*th_ref_ddot+D*(th_ref_dot-theta_dot)+K*(th_ref-theta);
    
       if(abs(Uu) > 1000) 
           Uu=1000*sign(Uu);
       end
           
    % Control input Uu(i)
       save_u(i)=Uu;                    %save control input for plotting 
       save_theta(i)=theta;             %save output 
       save_th_ref(i)=th_ref;           %save the reference command input 
     
    % Call "ode45" to simulate the response of the plant to obtain theta(i+1)
       ti=TT(i); tf=ti+h;  
       [t,xy]=ode45(@plant,[ti,tf],xp);
       [NN,MM]=size(xy); 
       xp=xy(NN,:); theta=xp(1,1);theta_dot=xp(1,2); % the last output the ode45 is the state at t=(i+1)h
     
       if (mod(i*h, PT)==0) 
           th_refv=-th_refv;                         % generate the command input th_ref(i+1)
       end
       th_ref=th_ref0+th_refv;
    end 

    figure(1)
    plot(TT,save_th_ref,':',TT,save_u, TT,save_theta)
    xlabel('time (sec)')
    ylabel('Response')
    legend('theta reference','controller output','theta')

    figure(2)
    plot(TT,save_th_ref-save_theta)
    xlabel('time (sec)')
    ylabel('trace error')
    legend('trace error')

end

% 实际系统中 输出Uu的单位是mNm，所以有一个系数
function xdot = plant(t,xy)

    global M L Uu T; 
    Kf = 37;
    uncertainty = (-1)^round(t*10)*2;      % uncertainty in System
    mNm2Nm = 1/1000;
    if(t < T/6 || t > T*5/6)
        tao_e = 0;
    elseif(t < T*1/2)
        tao_e = 10;
    else
        tao_e = -10;
    end
    theta=xy(1); theta_dot=xy(2);
    xdot(1,1)=theta_dot; 
    xdot(2,1)=mNm2Nm*(Uu+tao_e-Kf*sign(theta_dot))/(M*L^2/12)+uncertainty;
end

