% this function is instead implemented in c++.

%function y = synthhammer(notes, fn, d, fs)
% Synthesize the hammering of a piano string.
%
% SYNOPSIS: y = synthhammer(f, fn, d, fs, vol).
%
% INPUT notes: 1xn midi note number.
%       fn: forces in newton, a scalar.
%       d: duration in seconds.
%       fs: sampling rate in Hz.
%       vol: loudness factor in [0, 1].
%
% OUTPUT y: the synthesized 1D signal.
%
%        y = zeros(1, fs*d);
%end