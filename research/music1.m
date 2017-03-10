function [notes, forces, ds] = music1(bpm)
% Returns a sample piece of music.
%
% SYNOPSIS: [notes, forces, ds] = music1(bpm).
%
% INPUT bpm: beats per minute.
%
% OUTPUT notes: mxn frequencies in Hz.
%        forces: mxn forces in newton.
%        ds: mxn note durations in seconds.
%
        notes = [
                notef(noteof("C", 4)) notef(noteof("E", 4)) notef(noteof("C", 5));
                notef(noteof("C", 4)) notef(noteof("E", 4)) notef(noteof("C", 5));
                notef(noteof("B", 3)) notef(noteof("G", 4)) notef(noteof("D", 5));
                notef(noteof("C", 4)) notef(noteof("G", 4)) notef(noteof("E", 5));
                
                notef(noteof("D", 4)) notef(noteof("G", 4)) notef(noteof("F", 5));
                notef(noteof("E", 4)) notef(noteof("G", 4)) notef(noteof("G", 5));
                notef(noteof("C", 4)) notef(noteof("G", 4)) notef(noteof("E", 5));
                notef(noteof("D", 4)) notef(noteof("G", 4)) notef(noteof("F", 5));
                notef(noteof("E", 4)) notef(noteof("G", 4)) notef(noteof("G", 5));
                notef(noteof("F", 4)) notef(noteof("G", 4)) notef(noteof("A", 5));
        ];
        
        forces = [
                1 1 1;
                1 1 1;
                1 1 1;
                1 1 1;
                
                1 1 1;
                1 1 1;
                1 1 1;
                1 1 1;
                1 1 1;
                1 1 1;
        ];
        
        ds = [
                noteval(1/2, bpm) noteval(1/2, bpm) noteval(1/2, bpm);
                noteval(1/2, bpm) noteval(1/2, bpm) noteval(1/2, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(3/4, bpm) noteval(3/4, bpm) noteval(3/4, bpm);
                
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1, bpm) noteval(1, bpm) noteval(1, bpm);
        ];
endfunction