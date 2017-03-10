function testplay()
% Test play.
%
        [notes, forces, ds] = music1(25);
        y = play(notes, forces, ds, fs(), 1.0);
        wavplay(y, fs(), 24);
endfunction