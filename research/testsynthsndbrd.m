function testsynthsndbrd()
        fig = figure(1);
        
        for i=0:.00001:.1
                sbrd = synthsndbrd(noteof("A",4),-.0005,i,160000);
                x = linspace(0,1.4,size(sbrd,1));
                y = linspace(0,1.4,size(sbrd,2));
                surf(x,y,sbrd);
                zlim([-.00000003,.00000001]);
                drawnow;
                pause(1/20);
        end
end