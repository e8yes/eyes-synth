function y = play(notes, forces, ds, synth, fs, vol)
% Play a piece of music.
%
% SYNOPSIS: y = play(notes, amps, ds, fs, vol).
%
% INPUT notes: an mxn matrix of frequencies in Hz (what are the notes to be played) where m is the length of the music, n is the number of notes played at the same time.
%       forces: an mxn matrix of amplitudes in [0, inf) in newton (how hard each note should be played) with the same definition of m and n as above.
%       ds: a mxn matrix of durations in seconds (how long each note should be played) with the same definition of m and n as above.
%       synth: function name to the synthesizer used.
%       fs: sampling rate in Hz.
%       vol: loudness factor in [0, 1].
%
% OUTPUT y: the synthesized 1D signal.
%
        assert(size(notes) == size(forces) && size(forces) == size(ds));
        
        y = 0;
        for i = 1:size(notes, 1)
                % hit the current notes.
                len = ceil(max(ds(i,:))*fs);
                iy = zeros(1, len);
                for j = 1:size(notes, 2)
                        r = feval(synth, notes(i, j), forces(i, j), ds(i, j), fs);
                        iy += [r zeros(size(iy) - size(r))];
                end
                % stitch the current hit with the previous hit.
                y = stitch(y, iy, 100/44100*fs);
        end
        % normalize the signal.
        y = vol*y/max(y);
end