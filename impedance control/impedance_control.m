function impedance_control()

    clc
    clear

    global M L Uu
    % System Parameters 
    M=0.1; L=0.3; J=M*L^2/12;                   % plant


    % Controller constants 
    K=2;D=0.2;
    h=0.0005;                                     % sampling period
    T=5;                                        % simualtion time span
    PT=T*100;                                   % half period of the command input


    % Initialization  
    th_ref=10;th_ref_dot=0;th_ref_ddot=0;th_ref0=th_ref/2;th_refv=th_ref0;  % initial values of the reference model and the command input 
    theta=0.0; theta_dot=0.0;xp = [theta;theta_dot];                        % initial plant outputs and state
        
    for i=1: T/h 
       TT(i)=(i-1)*h;                   %time
    % calculate the control input Uu(i) based on xc(i), theta(i), theta_dot(i)
       Uu=J*th_ref_ddot+D*(th_ref_dot-theta_dot)+K*(th_ref-theta);
       
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


    plot(TT,save_th_ref,':',TT,save_u, TT,save_theta)
    xlabel('time (sec)')
    ylabel('Response')
    legend('theta reference','controller output','theta')


    plot(TT,save_th_ref-save_theta)
    xlabel('time (sec)')
    ylabel('trace error')
    legend('trace error')

end


function xdot = plant(t,xy)

    global M L Uu; 
    if(t < 1.5 || t > 4.5)
        tao_e = 0;
    elseif(t < 3)
        tao_e = 10;
    else
        tao_e = -10;
    end
    theta=xy(1); theta_dot=xy(2);
    xdot(1,1)=theta_dot; 
    xdot(2,1)=(Uu+tao_e)/(M*L^2/12);
end

