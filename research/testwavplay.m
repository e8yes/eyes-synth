function testwavplay()
% Test wavplay.
%
        f = notef(noteof("E", 4));
        y = synthsin(f, 0.5, 2.5, fs(), 1.0);
        wavplay(y, fs(), 24);
end