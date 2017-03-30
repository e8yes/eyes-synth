function testsynthwave()
        fig = figure(1);
        set(fig, 'Position', [20 20 1024 200]);
        
        x = linspace(0,1.5,100);
        for i=0:.0001:1
                plot(x, synthwave(noteof("A",1),-100,i,640000,1));
                xlim([0,1.5]);
                ylim([-0.03 0.03]);
                drawnow;
                pause(1/10);
        end
end