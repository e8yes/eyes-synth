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
        yf = [ya(end - sl + 1:end) yb(1:sr)];
        % box filter.
        b = ones(sl + sr)*1/(sl + sr); a = 1;
        yf = filter(b, a, yf);
        % put the parts together.
        ys = [ya(1:end - sl) yf yb(sr + 1:end)];
endfunction