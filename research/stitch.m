function ys = stitch(ya, yb, win)
% Stitches the end of one signal to the beginning of the other.
%
% SYNOPSIS: ys = stitch(ya, yb, win).
%
% INPUT ya: signal to prepend.
%       yb: signal to append.
%       win: smoothing window, the larger the more smoothing will be applied.
%
% OUTPUT ys: the stitched signal.
%
        % crop the part of signal within the window.
        sl = min(size(ya, 2), win); sr = min(size(yb, 2), win);
        
        part_left = ya(end - sl + 1:end);
        part_right = yb(1:sr);
        total_len = size(part_left,2) + size(part_right,2);
        
        % find the mean.
        miu = size(part_left,2)/total_len*mean(part_left) + size(part_right,2)/total_len*mean(part_right);
        
        % alpha blending in 1D.
        t_left = linspace(0,10,size(part_left,2));
        t_right = linspace(0,10,size(part_right,2));
        alpha_left = sigmf(t_left, 1, 5);
        alpha_right = sigmf(t_right, 1, 5);

        yf = [(1 - alpha_left).*part_left + alpha_left.*miu       (1 - alpha_right).*miu + alpha_right.*part_right];
        
        % put the parts together.
        ys = [ya(1:end - sl) yf yb(sr + 1:end)];
end