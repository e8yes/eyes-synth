function testsynthsndbrd()
        fig = figure(1);
        
        for i=0:.1:10
                sbrd = synthsndbrd(noteof("A",4),-.05,i,4000);
                x = linspace(0,1.4,size(sbrd,1));
                y = linspace(0,1.4,size(sbrd,2));
                surf(x,y,sbrd);
                %zlim([-.003,.001]);
                drawnow;
                pause(1/10);
        end
end