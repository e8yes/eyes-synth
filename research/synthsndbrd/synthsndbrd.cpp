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

Soundboard gen_soundboard()
{
        // Spruce wedged plate.
        return Soundboard(.0175f, 433,
                          .686f, 14.9f, .025f, .245f, .552f,
                          1.4f, 1.4f, .7f, 1);
}

struct Synthesis
{
        Matrix      hit(float v, float f, const Soundboard& sbrd, float d, float fs);
};

Matrix
Synthesis::hit(float v, float f, const Soundboard& sbrd, float d, float fs)
{
        int nx = 30;
        int ny = 30;
        int nt = static_cast<int>(std::ceil(d*fs));

        float hx = sbrd.a/nx;
        float hy = sbrd.b/ny;
        float ht = 1/fs;

        float rx = X3(sbrd.h)*sbrd.ex/(12*(1 - sbrd.vx*sbrd.vy));
        float ry = X3(sbrd.h)*sbrd.ey/(12*(1 - sbrd.vx*sbrd.vy));
        float rxy = X3(sbrd.h)*sbrd.gxy/12;

        float A = sbrd.rho*sbrd.h;
        float B = -rx;
        float C = -(rx*sbrd.vy + ry*sbrd.vx + 4*rxy);
        float D = -ry;

        float K1 = B/A * X2(ht)/X4(hx);
        float K2 = C/A * X2(ht)/(X2(hx)*X2(hy));
        float K3 = D/A * X2(ht)/X4(hy);

        int x0 = static_cast<int>(std::ceil(sbrd.x/sbrd.a * nx));
        int y0 = static_cast<int>(std::ceil(sbrd.y/sbrd.b * ny));

        Matrix m[4];
        for (unsigned t = 0; t < 4; t ++)
                m[t] = Matrix(static_cast<int>(nx), static_cast<int>(ny));

        // Boundary condition: rim is clamped and board is at rest for all time t.
        for (unsigned t = 0; t < 4; t ++)
                m[t].fill(0);

        // Initial condition: the bridge has an initial velocity.
        m[1].fill(0);
        m[1](x0,y0) = v*ht + m[0](x0,y0);

        for (int t = 1; t < nt; t ++) {
                for (int j = 3; j <= ny - 3; j ++) {
                        for (int i = 3; i <= nx - 3; i ++) {
                                m[T1(t)](i,j) = K1*(m[T0(t)](i+2,j) - 4*m[T0(t)](i+1,j) + 6*m[T0(t)](i,j) - 4*m[T0(t)](i-1,j) + m[T0(t)](i-2,j))
                                              + K2*(m[T0(t)](i+1,j+1) -2*m[T0(t)](i,j+1) + m[T0(t)](i-1,j+1)
                                                - 2*(m[T0(t)](i+1,j) -2*m[T0(t)](i,j) + m[T0(t)](i-1,j))
                                                + m[T0(t)](i+1,j-1) -2*m[T0(t)](i,j-1) + m[T0(t)](i-1,j-1))
                                              + K3*(m[T0(t)](i,j+2) - 4*m[T0(t)](i,j+1) + 6*m[T0(t)](i,j) - 4*m[T0(t)](i,j-1) + m[T0(t)](i,j-2))
                                              + 2*m[T0(t)](i,j) - m[T_1(t)](i,j);
                        }
                }
        }
        return m[T0(nt)];
}

float fundamental_frequency(int note)
{
        return std::exp2(((note - 57)/12.0f)) * 440;
}

DEFUN_DLD(synthsndbrd, args, ,
          "Generate a wave on soundboard given the initial speed and frequency  "
          "                                                                     "
          "SYNOPSIS: y = synthsndbrd(note, fn, d, fs).                          "
          "                                                                     "
          " INPUT note: midi note number                                        "
          "       v: velocity in m/s, a scalar.                                 "
          "       d: duration in seconds.                                       "
          "       fs: sampling rate in Hz.                                      "
          "                                                                     "
          " OUTPUT y: soundboard planar displacement.                           ")
{
        if (args.length() < 4) {
                print_usage();
                return octave_value();
        }
        int note = args(0).int_value();
        double v = args(1).double_value();
        double d = args(2).double_value();
        int fs = args(3).int_value();

        const Soundboard& sbrd = ::gen_soundboard();
        Synthesis s;
        const Matrix& m = s.hit(static_cast<float>(v), fundamental_frequency(note), sbrd, static_cast<float>(d), fs);
        return octave_value(m);
}

int main()
{
        const Soundboard& sbrd = ::gen_soundboard();

        Synthesis s;
        const Matrix& m = s.hit(-5.0f, 440, sbrd, 1, 4000);
        std::cout << m << std::endl;
        return 0;
}
