function testsynthhammer()
        fig = figure(1);
        %set(fig, 'Position', [20 20 1024 1024]);
        hold on;
        for i=0:.0001:.01
                h = synthhammer(88,-5,i);
                plot(i, h);
                xlim([0,.01]);
                %ylim([0,1]);
                drawnow;
                pause(1/10);
        end
        hold off;
end