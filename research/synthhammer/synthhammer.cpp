#include <iostream>
#include <math.h>
#include <oct.h>


static bool is_even(int n);


DEFUN_DLD(synthhammer, args, nargout,
          "Synthesize the hammering of a piano string.  "
          "                                             "
          "SYNOPSIS: y = synthhammer(f, fn, d, fs, vol)."
          "						"
          " INPUT f: frequency in Hz, a scalar.		"
          "       fn: forces in newton, a scalar.       "
          "       d: duration in seconds.		"
          "       fs: sampling rate in Hz.		"
          "       vol: loudness factor in [0, 1].	"
          "						"
          " OUTPUT y: the synthesized 1D signal.	")
{
        if (args.length() < 5) {
                print_usage();
                return octave_value();
        }
        double f = args(0).double_value();
        double fn = args(1).double_value();
        double d = args(2).double_value();
        int fs = args(3).int_value();
        float vol = args(4).float_value();
        Matrix y(dim_vector(1, static_cast<int>(std::ceil(fs*d))));
        y.fill(0);
        return octave_value(y);
}

bool
is_even(int n)
{
        return n % 2 == 0;
}

int
main(int argc, char *argv[])
{
        return 0;
}
