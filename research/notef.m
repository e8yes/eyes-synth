function f = notef(p)
% Returns the frequency of a note.
%
% SYNOPSIS: f = notef(p).
%
% INPUT p: a midi note number.
%
% OUTPUT f: frequency of p.
%
        f = 2^((p - 57)/12) * 440;
end