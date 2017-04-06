#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>
#include <oct.h>

#define X2(_x)                  ((_x)*(_x))
#define X3(_x)                  ((_x)*(_x)*(_x))
#define X4(_x)                  ((_x)*(_x)*(_x)*(_x))

#define SQR(_x)         ((_x)*(_x))
#define T1(_t)          (((_t)+1)&3)
#define T0(_t)          (((_t)+0)&3)
#define T_1(_t)         (((_t)+3)&3)


struct FeltHammer
{
        float   m;              // Hammer mass.
        float   f0;             // Initial power pressure (model II).
        float   q0;             // Initial power pressure (model III).
        float   p;              // Power law of compression.
        float   epsilon;        // Time scale fitting parameter (model II).
        float   tao;            // Characteristic time scale in nanosecond (model II).
        float   alpha;          // Characteristic time scale in microsecond (model III).

        FeltHammer(int note)
        {
                m = 11.074f - .074f*note + 1e-4f*X2(note);
                f0 = 15500*std::exp(.059f*note);
                q0 = 183*std::exp(.045f*note);
                p = 3 + .015f*note;
                epsilon = .9894f + 8.8f*10e-5f*note;
                tao = 2.72f - .02f*note + 9e-5f*X2(note);
                alpha = 259.5f - .58f*note + 6.6e-2f*X2(note) - 1.25e-3f*X3(note) + 1.172e-5f*X4(note);
        }
};

FeltHammer gen_felt_hammer(int note)
{
        return FeltHammer(note - 8);
}

std::ostream& operator<<(std::ostream& os, const FeltHammer& fh)
{
        os << "FeltHammer = [" << std::endl;
        os << "mass: " << fh.m << std::endl;
        os << "q0: " << fh.q0 << std::endl;
        os << "p: " << fh.p << std::endl;
        os << "alpha: " << fh.alpha << std::endl;
        os << "]";
        return os;
}

class Synthesis
{
public:
        float   	hit(float v, const FeltHammer& fh, float d);
};

float
Synthesis::hit(float v, const FeltHammer& fh, float d)
{
        unsigned fs = static_cast<unsigned>(std::ceil(1.2f*fh.alpha*fh.q0));
        unsigned nt = static_cast<unsigned>(std::ceil(fs*d));
        float ht = 1.0f/fs;

        float A = ht*fh.p/fh.m*fh.q0*fh.alpha;
        float B = X2(ht)/fh.m*fh.q0;
        float yx0t = 0;

        float h[4];
        for (unsigned i = 0; i < 4; i ++)
                h[i] = yx0t;

        h[0] = yx0t;
        h[1] = h[0] + ht*v;

        for (unsigned t = 1; t < nt; t ++) {
                if (h[T0(t)] > yx0t)
                        return h[T0(t)];

                unsigned t_1 = (t-1)%4;
                unsigned t0 = (t)%4;
                unsigned t1 = (t+1)%4;

                float R = A*std::pow(-(h[t0]-yx0t),fh.p-1);
                h[t1] = 1/(1+R)*(B*std::pow(-(h[t0]-yx0t),fh.p) + A*R*(h[t0] + ht*0) + 2*h[t0] - h[t_1]);
        }
        return h[T0(nt)];
}

/////////////////////////////////////////// Octave entrance ///////////////////////////////////////////
DEFUN_DLD(synthhammer, args, ,
          "Compute the displacement of the hammer when hitting on a static object.      "
          "                                                                             "
          "SYNOPSIS: y = synthhammer(note, fn, d).                              "
          "                                                                             "
          " INPUT note: midi note number.                                               "
          "       v: velocity in m/s, a scalar.                                         "
          "       d: duration in seconds.                                               "
          "       fs: sampling rate in Hz.                                              "
          "                                                                             "
          " OUTPUT y: hammer displacement.	                                        ")
{
        if (args.length() < 3) {
                print_usage();
                return octave_value();
        }
        int note = args(0).int_value();
        double v = args(1).double_value();
        double d = args(2).double_value();

        const FeltHammer& fh = gen_felt_hammer(note);
        Synthesis s;
        float h = s.hit(static_cast<float>(v), fh, static_cast<float>(d));
        return octave_value(h);
}

int main()
{
        const FeltHammer& fh = gen_felt_hammer(10);
        std::cout << fh << std::endl;

        Synthesis s;
        float h = s.hit(-5.0f, fh, .001f);
        std::cout << h << std::endl;
        return 0;
}


