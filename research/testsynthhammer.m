function testsynthhammer()
        fig = figure(1);
        %set(fig, 'Position', [20 20 1024 1024]);
        hold on;
        for i=0:.00001:.007
                h = synthhammer(33,-5,i,4410000,1);
                plot(i, h);
                xlim([0,.007]);
                %ylim([0,1]);
                drawnow;
                pause(1/10);
        end
        hold off;
end