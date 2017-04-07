function testsynthstring()
        fig = figure(1);
        set(fig, 'Position', [20 20 1024 200]);
        
        x = linspace(0,1.5,100);
        for i=0:.001:1
                plot(x, synthstring(noteof("A",3),-10,i,441000));
                xlim([0,1.5]);
                ylim([-0.000003 0.000003]);
                drawnow;
                pause(1/10);
        end
end
