function p = noteof(nam, oct)
% Returns the midi note number of a music note in the specified octave.
%
% SYNOPSIS: p = noteof(nam, oct).
%
% INPUT nam: music note name in string.
%       oct: the number of octave.
%
% OUTPUT p: the midi note number.
%
        switch nam
        case "C"
                p = 12*(oct + 1);
        case "C#"
                p = 1 + 12*(oct + 1);
        case "D"
                p = 2 + 12*(oct + 1);
        case "D#"
                p = 3 + 12*(oct + 1);
        case "E"
                p = 4 + 12*(oct + 1);
        case "F"
                p = 5 + 12*(oct + 1);
        case "F#"
                p = 6 + 12*(oct + 1);
        case "G"
                p = 7 + 12*(oct + 1);
        case "G#"
                p = 8 + 12*(oct + 1);
        case "A"
                p = 9 + 12*(oct + 1);
        case "A#"
                p = 10 + 12*(oct + 1);
        case "B"
                p = 11 + 12*(oct + 1);
        end
end