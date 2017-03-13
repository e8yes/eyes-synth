% frequency of note of C4.
fc4 = notef(noteof("C", 4));

% duration of synthesis.
d = 1;

% force in hitting the string.
force = 15;

% wave of sin wave.
ysin = synthsin(fc4, force, d, fs(), 1.0);

% wave of hammered wave.
yham = synthhammer(fc4, force, d, fs(), 1.0);



figure(1);
domt = dom(d, fs());

% plot of sin wave.
subplot(2,1,1);
plot(domt(1:1000), ysin(1: 1000));

title("synthesis");
xlabel("t (seconds)");
ylabel("amplitude");


% plot of hammered wave.
subplot(2,1,2);
plot(domt(1:1000), yham(1: 1000));

title("synthesis");
xlabel("t (seconds)");
ylabel("amplitude");



figure(2);

% plot of sin wave.
domf = linspace(0, size(domt, 2)/2, size(domt, 2));
subplot(2,1,1);
plot(abs(fft(ysin))(1:1000));

title("frequency distribution");
xlabel("frequency (Hz)");
ylabel("proportion");


% plot of hammered wave.
subplot(2,1,2);
plot(abs(fft(yham))(1:1000));

title("frequency distribution");
xlabel("frequency (Hz)");
ylabel("proportion");
