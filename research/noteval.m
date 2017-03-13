function s = noteval(n, bpm)
% Returns the duration of note value according to bpm rate.
%
% SYNOPSIS: s = noteval(n, bpm).
%
% INPUT n: note value.
%       bpm: beats per minute.
%
% OUTPUT duration in second.
%
        s = 60/bpm*n;
end