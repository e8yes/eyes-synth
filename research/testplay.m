function testplay()
% Test play.
%
        [notes, forces, ds] = music1(25);
        y = play(notes, forces, ds, "synthsin", fs(), 1.0);
        wavwrite(y, fs(), 24, "testplay.wav");
        wavplay(y, fs(), 24);
end