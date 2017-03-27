function y = sigmf(x, a, c)
        y = 1./(1 + exp(-a*(x - c)));
end