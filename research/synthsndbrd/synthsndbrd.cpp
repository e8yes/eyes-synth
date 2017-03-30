#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>
#include <oct.h>


DEFUN_DLD(synthsndbrd, args, ,
          "Generate a wave on soundboard given the initial speed.       "
          "                                                             "
          "SYNOPSIS: y = synthsndbrd(note, fn, d, fs, vol).             "
          "                                                             "
          " INPUT note: midi note number.                               "
          "       v: velocity in m/s, a scalar.                         "
          "       d: duration in seconds.                               "
          "       fs: sampling rate in Hz.                              "
          "       vol: loudness factor in [0, 1].                       "
          "                                                             "
          " OUTPUT y: soundboard planar displacement.                   ")
{
        if (args.length() < 5) {
                print_usage();
                return octave_value();
        }
        int note = args(0).int_value();
        double v = args(1).double_value();
        double d = args(2).double_value();
        int fs = args(3).int_value();
        double vol = args(4).double_value();

//        return octave_value(h);
}

int main()
{
        return 0;
}
