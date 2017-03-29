#include <iostream>
#include <math.h>
#include <oct.h>

#define X2(_x)                  ((_x)*(_x))
#define X3(_x)                  ((_x)*(_x)*(_x))
#define X4(_x)                  ((_x)*(_x)*(_x)*(_x))
#define INTERP(_a, _b, _t)      ((_a) + ((_b) - (_a))*(_t))

/////////////////////////////////////////// Entities ///////////////////////////////////////////
struct String
{
        float   m;              // Total string mass.
        float   d;              // Diameter.
        float   l;              // Length.
        float   e;              // Young's modulus.
        float   f;              // Fundamental frequency.

        float   c2;             // Wave speed squred.
        float   epsilon;        // Dispersion factor
        float   alpha1;         // Velocity-dependent(transverse) damping factor.
        float   alpha2;         // Frequency-dependent damping factor.
        int     ns;             // Number of wrapped strings.

        String(float f, float mass, float d, float l, float e, float alpha1, float alpha2, int ns):
                f(f), m(mass), d(d), l(l), e(e), alpha1(alpha1), alpha2(alpha2), ns(ns)
        {
                // Compute wave speed and dispersion factor based on the fundamental frequency.
                float c = 2*f*l;
                float rho = mass/(l*static_cast<float>(M_PI)*X2(d/2));
                float eps = (d/2)*(d/2)*std::sqrt(e/rho)/c;

                c2 = X2(c);
                epsilon = X2(c)*eps;
        }
};

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

struct Soundboard
{
        float   h;              // Thickness of the soundboard.
        float   rho;            // Density of the soundboard.
        float   ex;             // Young's modulus for X direction.
        float   ey;             // Young's modulus for Y direction.
        float   vx;             // Poisson's ratio for X direction.
        float   vy;             // Poisson's ratio for Y direction.
        float   gxy;            // Shear modulus.
        float   a;              // Soundboard width.
        float   b;              // soundboard length.
        float   x;              // Bridge location x.
        float   y;              // Bridge location y.

        Soundboard(float h, float rho,
                   float ex, float ey, float vx, float vy, float gxy,
                   float a, float b, float x, float y):
                h(h), rho(rho),
                ex(ex), ey(ey), vx(vx), vy(vy), gxy(gxy),
                a(a), b(b), x(x), y(y)
        {
        }
};

struct Room
{
        //float   ks;             // Bulk modulus.
        //float   rho;            // Air density.

        float   c;              // Speed of sound.
        float   w;              // Width of the room as a box.
        float   l;              // Length of the room as a box.
        float   h;              // Height of the room as a box.
        float   x;              // Location of the source of the sound.
        float   y;
        float   z;

        Room(float ks, float rho,
             float w, float l, float h,
             float x, float y, float z):
                w(w), l(l), h(h),
                x(x), y(y), z(z)
        {
                c = std::sqrt(ks/rho);
        }
};


/////////////////////////////////////////// Entities generator ///////////////////////////////////////////
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

FeltHammer gen_felt_hammer(int note)
{
        return FeltHammer(note - 8);
}

Soundboard gen_soundboard()
{
        // Spruce wedged plate.
        return Soundboard(.0175f, 433,
                          .686f, 14.9f, .025f, .245f, .552f,
                          1.4f, 1.4f, .7f, 1);
}

Room gen_room()
{
        return Room(1.42e+5, 1.225f,
                    3, 3, 4,
                    1.5f, 1.5f, 1);
}



/////////////////////////////////////////// Synthesis ///////////////////////////////////////////
struct Synthesis
{
        const String            s;
        const FeltHammer        fh;
        const Soundboard        sb;
        const Room              r;

        double                  dt_r;
        unsigned                st_s = 4;
        unsigned                st_sb = 6;

        double                  dx_s;
        unsigned                mx_sb = 2;
        unsigned                mx_r = 4;

        unsigned                nsx;
        unsigned                nrt;

        Synthesis(String s, FeltHammer fh, Soundboard sb, Room r):
                s(s), fh(fh), sb(sb), r(r)
        {
        }

        double tr(unsigned i)
        {
                return i*dt_r;
        }

        double ts(unsigned i)
        {
                return i*dt_r/st_s;
        }

        double tsb(unsigned i)
        {
                return i*dt_r/st_sb;
        }

        double xs(unsigned j)
        {
                return j*dx_s;
        }

        double xr(unsigned j)
        {
                return j*dx_s*mx_r;
        }

        double xsb(unsigned j)
        {
                return j*dx_s*mx_sb;
        }

        double ht(unsigned i, double ht) const
        {
        }

        double svxt(unsigned j, unsigned i, double st, double sx) const
        {
                // Velocity of the string.
        }

        double sbvxyt(unsigned j, unsigned i)
        {
                // Velocity of the sound board
        }

        double rxyzt(unsigned j, unsigned i)
        {
        }

        std::vector<double> hit(float v_hammer, unsigned fs, float d)
        {
                nsx = static_cast<unsigned>(fs/(2*s.f));
                nrt = fs;
                dx_s = s.l/nsx;
                dt_r = d/fs;

                for (unsigned i = 0; i < nrt; i ++) {
                }
        }
};


/////////////////////////////////////////// Octave entrance ///////////////////////////////////////////
DEFUN_DLD(synthhammer, args, ,
          "Synthesize the hammering of a piano string.  "
          "                                             "
          "SYNOPSIS: y = synthhammer(f, fn, d, fs, vol)."
          "						"
          " INPUT note: midi note number.		"
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
        int note = args(0).int_value();
        double fn = args(1).double_value();
        double d = args(2).double_value();
        int fs = args(3).int_value();
        double vol = args(4).double_value();

        Synthesis s(gen_string(note), gen_felt_hammer(note), gen_soundboard(), gen_room());
        const std::vector<double>& ysynth = s.hit(static_cast<float>(fn), static_cast<unsigned>(fs));

        Matrix y(dim_vector(1, static_cast<int>(std::ceil(fs*d))));
        for (unsigned i = 0; i < ysynth.size(); i ++)
                y(static_cast<octave_idx_type>(i + 1)) = ysynth[i];
        return octave_value(vol*y);
}

/////////////////////////////////////////// Tests ///////////////////////////////////////////
int
main(int, char **)
{
        return 0;
}
