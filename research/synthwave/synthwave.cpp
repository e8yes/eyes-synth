#include <iostream>
#include <cmath>
#include <vector>
#include <oct.h>

#define SQR(_x)         ((_x)*(_x))
#define T1(_t)          (((_t)+1)&3)
#define T0(_t)          (((_t)+0)&3)
#define T_1(_t)         (((_t)+3)&3)

class Synthesis
{
private:
        float                   l = 1.5;
        float                   x0 = .2;

        unsigned                nx;
        unsigned                nt;
public:
        std::vector<float>     hit(float f, float v, float d, int fs);
};

std::vector<float> 
Synthesis::hit(float f, float v, float d, int fs)
{
        //nx = std::floor(fs/(2.0*f));
        nx = 100;
        fs = 2*f*nx + 100.0f;
        nt = std::ceil(d*fs);

        float ht = static_cast<float>(d)/nt;
        float hx = l/nx;

        float cs = 2*l*f;

        float a = SQR(ht)*SQR(cs)/SQR(hx);
        float b = 2*(1 - a);

        unsigned i0 = x0/l*nx;

        // Initial condition: string is at rest at t=0.
        std::vector<float> y[4];
        for (unsigned t = 0; t < 4; t ++)
                y[t] = std::vector<float>(nx);
        for (unsigned i = 0; i < nx; i ++)
                y[0][i] = 0;

        // y(i0,1) = v*h_t + y(i0,0) at t=1.
        for (unsigned i = 0; i < nx; i ++)
                y[1][i] = 0;
        y[1][i0] = v*ht + y[0][i0];

        // Boundary condition: extremities doesn't move for all t.
        for (unsigned t = 0; t < 4; t ++) {
                y[t][0] = 0;
                y[t][nx-1] = 0;
        }

        for (unsigned t = 1; t < nt; t ++) {
                for (unsigned i = 1; i < nx - 1; i ++) {
                        y[T1(t)][i] = a*y[T0(t)][i+1] + b*y[T0(t)][i] + a*y[T0(t)][i-1] - y[T_1(t)][i];
                }
                //std::cout << T1(t) << ": ";
                //for (unsigned i = 0; i < nx; i ++) {
                //        std::cout << y[T1(t)][i] << " ";
                //}
                //std::cout << std::endl;
        }

        std::cout << T0(nt) << ": ";
        return y[T0(nt)];
}

double fundamental_frequency(int note)
{
        return std::exp2(((note - 57)/12.0)) * 440;
}

/////////////////////////////////////////// Octave entrance ///////////////////////////////////////////
DEFUN_DLD(synthwave, args, ,
          "Generate a wave with initial wave speed.  "
          "                                             "
          "SYNOPSIS: y = wave(note, fn, d, fs, vol)."
          "						"
          " INPUT note: midi note number.		"
          "       v: velocity in m/s, a scalar.       "
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
        int note = args(0).int_value();
        double v = args(1).double_value();
        double d = args(2).double_value();
        int fs = args(3).int_value();
        double vol = args(4).double_value();

        Synthesis s;
        const std::vector<float>& ysynth = s.hit(fundamental_frequency(note), v, d, fs);

        Matrix y(dim_vector(1, static_cast<int>(ysynth.size())));
        for (unsigned i = 0; i < ysynth.size(); i ++)
                y(static_cast<octave_idx_type>(i + 1)) = ysynth[i];
        return octave_value(vol*y);
}

int main()
{
        Synthesis s;
        const std::vector<float>& ysynth = s.hit(44, .01f, .001, 441000);
        for (unsigned i = 0; i < ysynth.size(); i ++)
                std::cout << ysynth[i] << ' ';
        std::cout << std::endl;
        return 0;
}


