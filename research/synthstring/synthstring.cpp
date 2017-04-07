#include <iostream>
#include <cmath>
#include <vector>
#include <oct.h>

#define X2(_x)                  ((_x)*(_x))
#define X3(_x)                  ((_x)*(_x)*(_x))
#define X4(_x)                  ((_x)*(_x)*(_x)*(_x))
#define INTERP(_a, _b, _t)      ((_a) + ((_b) - (_a))*(_t))


class String
{
public:
        String(float f, float mass, float d, float l, float e, float alpha1, float alpha2, int ns);

        void            step0(float fx0);
        void            step1(float fx0);
        void            stept(float fx0, float fl);
        float           get_yx0() const;
        float           get_vx0() const;
        float           get_fxl() const;
        const float*    get_y() const;
        unsigned        min_samp() const;
        void		set_fs(unsigned fs);

public:
        float   f;              // Fundamental frequency.
        float   m;              // Total string mass.
        float   d;              // Diameter.
        float   l;              // Length.
        float   e;              // Young's modulus.

        float	rho;		// Density of the string.
        float   c;             	// Wave speed.
        float   epsilon;     	// Dispersion factor
        float   alpha1;         // Velocity-dependent(transverse) damping factor.
        float   alpha2;         // Frequency-dependent damping factor.
        int     ns;             // Number of wrapped strings.

        static const unsigned constexpr nx = 100;
private:
        void		update();

        unsigned        gmin;
        unsigned        gmax;
        unsigned        i0;

        float           y[4][nx];       // displacement at each spatial element for the last 4 time steps.

        unsigned        fs;
        float           ht;
        float           hx;

        unsigned        t = 0;

        float           A0;

        float           A1;
        float           C1;

        float           A;
        float           B;
        float           C;
        float           D;
        float           E;
        float           F;

        float           G;
        float           H;
};

String::String(float f, float mass, float d, float l, float e, float alpha1, float alpha2, int ns):
        f(f), m(mass), d(d), l(l), e(e), alpha1(alpha1), alpha2(alpha2), ns(ns)
{
        // Compute wave speed and dispersion factor based on the fundamental frequency.
        c = 2*f*l;
        rho = mass/(l*static_cast<float>(M_PI)*X2(d/2));
        float eps = X2(d/2)*std::sqrt(e/rho)/c;

        epsilon = X2(c)*eps;

        // Init and rest the string.
        for (unsigned t = 0; t < 4; t ++)
                for (unsigned i = 0; i < nx; i ++)
                        y[t][i] = 0;

        // Init step sizes.
        fs = static_cast<unsigned>(std::ceil(8*f*nx));
        hx = l/nx;
        ht = 1.0f/fs;

        update();
}

void
String::update()
{
        float dm = m/l*hx;

        // Hammer location (5cm from fix point) and force spread (1cm radius).
        i0 = static_cast<unsigned>(std::ceil(.05f/l*nx));
        unsigned n2x0 = static_cast<unsigned>(std::ceil(.01f/l*nx));
        gmin = std::max(0u,i0-n2x0);
        gmax = std::min(nx-1,i0+n2x0);

        // DE factors.
        A0 = X2(ht)/((gmax-gmin+1)*dm);

        A1 = X2(ht)*X2(c)/X2(hx);
        C1 = X2(ht)/((gmax-gmin+1)*dm);

        A = X2(ht)*X2(c)/X2(hx);
        B = -X2(ht)*epsilon/X4(hx);
        C = -alpha1*ht;
        D = alpha2/ht;
        E = X2(ht)/((gmax-gmin+1)*dm);
        F = X2(ht);

        G = fs/dm;
        H = fs;
}

void
String::set_fs(unsigned f)
{
        fs = f;
        ht = 1.0f/fs;
        update();
}

unsigned
String::min_samp() const
{
        return fs;
}

void
String::step0(float fx0)
{
        // Hammer force.
        for (unsigned i = gmin; i <= gmax; i ++)
                y[1][i] += A0*fx0;
        t=0;
}

void
String::step1(float fx0)
{
        // Basic wave equation (without loss and dispersion).
        for (unsigned i = 1; i < nx - 1; i ++)
                y[2][i] = A1*(y[1][i+1] - 2*y[1][i] + y[1][i-1])
                        + 2*y[1][i] - y[0][i];

        // Hammer force.
        for (unsigned i = gmin; i <= gmax; i ++)
                y[2][i] += C1*fx0;
        t=1;
}

void
String::stept(float fx0, float fl)
{
        unsigned t_2 = (t-1)%4;
        unsigned t_1 = (t)%4;
        unsigned t0 = (t+1)%4;
        unsigned t1 = (t+2)%4;

        // Full model.
        for (unsigned i = 2; i < nx - 2; i ++) {
                y[t1][i] = A*(y[t0][i+1] - 2*y[t0][i] + y[t0][i-1])
                         + B*(y[t0][i+2] - 4*y[t0][i+1] + 6*y[t0][i] - 4*y[t0][i-1] + y[t0][i-2])
                         + C*(y[t1][i] - y[t0][i])
                         + D*(y[t1][i] - 3*y[t0][i] + 3*y[t_1][i] - y[t_2][i])
                         + 2*y[t0][i] - y[t_1][i];
        }

        // Hammer force.
        for (unsigned i = gmin; i <= gmax; i ++)
                y[t1][i] += E*fx0;

        // Bridge force.
        y[t1][nx-3] += F*fl;

        t++;
}

float
String::get_yx0() const
{
        unsigned t0 = (t)%4;
        return y[t0][i0];
}

float
String::get_vx0() const
{
        unsigned t0 = (t)%4;
        unsigned t1 = (t+1)%4;
        return (y[t1][i0] - y[t0][i0])*H;
}

float
String::get_fxl() const
{
        unsigned t_1 = (t-1)%4;
        unsigned t0 = (t)%4;
        unsigned t1 = (t+1)%4;
        return (y[t1][nx-3] - 2*y[t0][nx-3] + y[t_1][nx-3])*G;
}

const float*
String::get_y() const
{
        unsigned t0 = (t)%4;
        return y[t0];
}

// Helpers.
float fundamental_frequency(int note)
{
        return std::exp2(((note - 57)/12.0f)) * 440;
}

String gen_string(const String& a, const String& b, int p0, int p1, int note)
{
        float f = fundamental_frequency(note);
        float t;
        if (p0 != p1)   t = static_cast<float>(note - p0)/static_cast<float>(p1 - p0);
        else            t = 0;

        return String(f,
                      INTERP(a.m, b.m, t),
                      INTERP(a.d, b.d, t),
                      INTERP(a.l, b.l, t),
                      INTERP(a.e, b.e, t),
                      INTERP(a.alpha1, b.alpha1, t),
                      INTERP(a.alpha2, b.alpha2, t),
                      static_cast<int>(INTERP(a.ns, b.ns, t)));

}

String gen_string(int note)
{
        String s_a0(fundamental_frequency(0), 360.11152e-3f, 1.5e-3f, 1.2392f, 2e+11f, .5f, 6.25e-9f, 1);
        String s_a2(fundamental_frequency(33), 13.88104e-3f, .95e-3f, .8312f, 2e+11f, .5f, 6.25e-9f, 2);
        String s_d3(fundamental_frequency(38), 7.51998e-3f, 1.125e-3f, .9641f, 2e+11f, .5f, 6.25e-9f, 3);
        String s_a4(fundamental_frequency(57), 2.23608e-3f, .95e-3f, .399f, 2e+11f, .5f, 6.25e-9f, 3);
        String s_a5(fundamental_frequency(69), 1.0415e-3f, .95e-3f, .208f, 2e+11f, .5f, 6.25e-9f, 3);
        String s_c7(fundamental_frequency(84), .460e-3f, .95e-3f, .09f, 2e+11f, .5f, 2.6e-10f, 3);

        if (note < 33)
                return gen_string(s_a0, s_a2, 0, 33, note);
        else if (note >= 33 && note < 38)
                return gen_string(s_a2, s_d3, 33, 38, note);
        else if (note >= 38 && note < 57)
                return gen_string(s_d3, s_a4, 38, 57, note);
        else if (note >= 57 && note < 69)
                return gen_string(s_a4, s_a5, 57, 69, note);
        else if (note >= 69 && note < 84)
                return gen_string(s_a5, s_c7, 69, 84, note);
        else
                return gen_string(s_c7, s_c7, 84, 84, note);
}

// main.
static RowVector synth(String& s, float f, float d, unsigned fs)
{
        unsigned nt = static_cast<unsigned>(std::ceil(s.min_samp()*d));
        s.step0(f/2);
        s.step1(f);

        for (unsigned t = 2; t < nt; t ++) {
                s.stept(0, 0);
        }

        const float* y = s.get_y();
        RowVector rvy(String::nx);
        for (unsigned i = 0; i < String::nx; i ++)
                rvy(static_cast<int>(i)) = y[i];
        return rvy;
}

/////////////////////////////////////////// Octave entrance ///////////////////////////////////////////
DEFUN_DLD(synthstring, args, ,
          "Generate a string wave with initial wave speed.      "
          "                                                     "
          "SYNOPSIS: y = wave(note, v, d).                      "
          "                                                     "
          " INPUT note: midi note number.                       "
          "       a: force in Newton, a scalar.                 "
          "       d: duration in seconds.                       "
          "       fs: sampling rate in Hz.                      "
          "                                                     "
          " OUTPUT y: the synthesized 1D signal.                ")
{
        if (args.length() < 4) {
                print_usage();
                return octave_value();
        }
        int note = args(0).int_value();
        double f = args(1).double_value();
        double d = args(2).double_value();
        double fs = args(3).double_value();

        String s = ::gen_string(note);
        const RowVector& y = ::synth(s, static_cast<float>(f), static_cast<float>(d), static_cast<unsigned>(fs));
        return octave_value(y);
}

int main()
{
        String s = ::gen_string(33);
        const RowVector& y = ::synth(s, -10, 5.2f, 441000);
        std::cout << y << std::endl;
        return 0;
}


