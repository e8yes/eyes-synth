function [notes, forces, ds] = music1(bpm)
% Returns a sample piece of music.
%
% SYNOPSIS: [notes, forces, ds] = music1(bpm).
%
% INPUT bpm: beats per minute.
%
% OUTPUT notes: mxn midi note numbers.
%        forces: mxn forces in newton.
%        ds: mxn note durations in seconds.
%
        notes = [
                noteof("C", 4) noteof("E", 4) noteof("C", 5);
                noteof("C", 4) noteof("E", 4) noteof("C", 5);
                noteof("B", 3) noteof("G", 4) noteof("D", 5);
                noteof("C", 4) noteof("C", 5) noteof("E", 5);
                
                noteof("D", 4) noteof("C", 5) noteof("F", 5);
                noteof("E", 4) noteof("C", 5) noteof("G", 5);
                noteof("C", 4) noteof("C", 5) noteof("E", 5);
                noteof("D", 4) noteof("C", 5) noteof("F", 5);
                noteof("E", 4) noteof("C", 5) noteof("G", 5);
                
                noteof("F", 4) noteof("C", 5) noteof("A", 5);
                
                noteof("E", 4) noteof("C", 5) noteof("G", 5);
                
                noteof("F", 4) noteof("C", 5) noteof("A", 5);
                noteof("D", 4) noteof("G", 4) noteof("B", 5);
                noteof("C", 4) noteof("G", 4) noteof("C", 6);
                noteof("B", 4) noteof("F", 5) noteof("D", 6);
                noteof("C", 5) noteof("E", 5) noteof("E", 6);
                noteof("A", 4) noteof("F", 5) noteof("D", 6);
                
                noteof("G", 3) noteof("E", 5) noteof("C", 6);
                noteof("G", 3) noteof("D", 4) noteof("B", 5);
                noteof("C", 4) noteof("E", 5) noteof("C", 6);
        ];
        
        forces = ones(size(notes));
        
        ds = [
                noteval(1/2, bpm) noteval(1/2, bpm) noteval(1/2, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(3/4, bpm) noteval(3/4, bpm) noteval(3/4, bpm);
                
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                
                noteval(1, bpm) noteval(1, bpm) noteval(1, bpm);
                
                noteval(1/2, bpm) noteval(1/2, bpm) noteval(1/2, bpm);
                
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                noteval(1/4, bpm) noteval(1/4, bpm) noteval(1/4, bpm);
                
                noteval(1/2, bpm) noteval(1/2, bpm) noteval(1/2, bpm);
                noteval(1/2, bpm) noteval(1/2, bpm) noteval(1/2, bpm);
                
                noteval(1, bpm) noteval(1, bpm) noteval(1, bpm);
        ];
end
