function t = dom(d, fs)
% Generate the discretized domain of synthesis.
%
% SYNOPSIS: t = dom(d, fs).
%
% INPUT d: duration in seconds.
%       fs: sampling rate in Hz.
%
% OUTPUT t: discreted domain values.
%
        t = linspace(0, d, ceil(fs*d));
end