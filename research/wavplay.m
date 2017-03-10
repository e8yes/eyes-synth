function wavplay(y, fs, bits)
% Play a 1D signal as sound.
%
% SYNOPSIS: wavplay(y,fs,bits).
%
% INPUT y: a vector of values representing the signal.
%       fs: sampling rate, in Hz.
%       bits: bit resolution.
%
        if (nargin != 3)
                usage("wavplay(y, fs, bits)");
        endif

        file = strcat(tmpnam(), ".wav");
        wavwrite(y, fs, bits, file); 
        system(sprintf("/usr/bin/paplay %s ; rm -f %s", file, file));
end