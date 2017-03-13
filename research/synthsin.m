function y = synthsin(f, fn, d, fs)
% Synthesize a sin wave with fixed frequency.
%
% SYNOPSIS: y = synthsin(f, d, fs, vol).
%
% INPUT f: frequency in Hz, a scalar.
%       fn: forces in newton, a scalar.
%       d: duration in seconds.
%       fs: sampling rate in Hz.
%       vol: loudness factor in [0, 1].
%
% OUTPUT y: the synthesized 1D signal.
%
        if fn ~= 0
                t = dom(d, fs);
                y = sin(2*pi*f*t);
        else
                y = zeros(1, fs*d);
        end
end