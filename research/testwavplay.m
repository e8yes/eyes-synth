function testwavplay()
% Test wavplay.
%
        y = synthsin(noteof("E", 4), 0.5, 2.5, fs(), 1.0);
        wavplay(y, fs(), 24);
end