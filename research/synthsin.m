function y = synthsin(note, fn, d, fs)
% Synthesize a sin wave with fixed frequency.
%
% SYNOPSIS: y = synthsin(f, d, fs, vol).
%
% INPUT notes: 1xn midi note number.
%       fn: forces in newton, a scalar.
%       d: duration in seconds.
%       fs: sampling rate in Hz.
%       vol: loudness factor in [0, 1].
%
% OUTPUT y: the synthesized 1D signal.
%
        f = notef(note);
        if fn ~= 0
                t = dom(d, fs);
                y = sin(2*pi*f*t);
        else
                y = zeros(1, fs*d);
        end
end