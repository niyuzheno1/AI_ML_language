Dec 18/19/20 2021

Get random number (https://atcoder.jp/contests/ahc001/submissions/20916667)

xor128() 
=> 
unsigned long xor128() {
  static unsigned long x=123456789, y=362436069, z=521288629, w=88675123;
  unsigned long t=(x^(x<<11));
  x=y; y=z; z=w;
  return (w=(w^(w>>19))^(t^(t>>8)));
}

Rectangle Class
struct Rect{
	int x1,y1,x2,y2;
	int area();
  int include(pii x);
  bool intersect(rect r);
};
Storage (Dynamic Array)
struct ArrayD{
  int * content;
  int sz;
  void malloc();
  void add(int x); // content[sz++] = x
  void erase(int x); // sz--, find where content[y] == x and replace with content x
};

Storage (Static Array)
struct ArrayS{
  int content[WSZ];
  int sz;
  void add(int x); // content[sz++] = x
  void erase(int x); // sz--, find where content[y] == x and replace with content x
};
Possible usage (subject to changes):
ArrayS x[1000](1203); 
will be transcompiled into 
ArrayS_1203_Int x[1000]; 
struct ArrayS_1203_Int{
  int content[1203];
  int sz;
  void add(int x); // content[sz++] = x
  void erase(int x); // sz--, find where content[y] == x and replace with content x
};

rd has some extensions
rd(S(x)) where S is a resizable container or a type
S (vector) => rep(y, 0, x) rd(w), S.push_back(w);
S (pii[]) => rep(y,0, x) rd(w.first, w.second);
where we will further analysis what will be possible replacement for rd and rep

group operator:

flag = GI[x, /*in*/ S, n, t, intersect(nr, x)]{Y} //GI = group include
=>
flag = true
rep(i, n) {
	if(i == t) continue;
	x = S[i];
	if(intersect(nr, x)){
		flag = false;
		Y;
		break;
	}
}

flag = GNI[x, /*in*/ S, include(x, p, q)]{
					rect nr=newrect(S[t],X[t],Y[t],p,q);
					if(calc_score(nr,R[t])-calc_score(S[t],R[t])>=-(double)_/C0){
					score+=calc_score(nr,R[t])-calc_score(S[t],R[t]);
					rect_update(S[t],nr,t);}
					};
=>
You can transcompile


Timer for logging time and benchmarking
//https://atcoder.jp/contests/ahc001/submissions/20926292
class timer {
    vector<timer> timers;
    int n = 0;
public:
    double limit = 5;
    double t = 0;
    timer() {}
    timer(int size) : timers(size) {}
    bool elapses() const {
        return time() - t > limit;
    }
    void measure() {
        t = time() - t;
        ++n;
    }
    void measure(char id) {
        timers[id].measure();
    }
    void print() {
        if (n % 2)
            measure();
        for (int i = 0; i < 128; ++i) {
            if (timers[i].n)
                cerr << (char)i << ' ' << timers[i].t << 's' << endl;
        }
        cerr << "  " << t << 's' << endl;
    }
    static double time() {
        using namespace chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / 1000.0;
    }
} timer(128);

Random Class

class rando {
    unsigned y;
public:
    rando(unsigned y) : y(y) {}
    unsigned next() {
        return y ^= (y ^= (y ^= y << 13) >> 17) << 5;
    }
    int next(int b) {
        return next() % b;
    }
    int next(int a, int b) {
        return next(b - a) + a;
    }
    double nextDouble(double b = 1) {
        return b * next() / 4294967296.0;
    }
    double nextDouble(double a, double b) {
        return nextDouble(b - a) + a;
    }
    int operator() (int b) {
        return next(b);
    }
}

Integrate with xor128 =>
		   
class RandomGenerate {
    unsigned long x=123456789, y=362436069, z=521288629, w=88675123;
public:
    unsigned next() {
        unsigned long t=(x^(x<<11));
	x = y; y = z; z = w;
	return (w=(w^(w>>19))^(t^(t>>8)));
    }
    int next(int b) {
        return next() % b;
    }
    int next(int a, int b) {
        return next(b - a) + a;
    }
    double nextDouble(double b = 1) {
        return b * next() / 4294967296.0;
    }
    double nextDouble(double a, double b) {
        return nextDouble(b - a) + a;
    }
    int operator() (int b) {
        return next(b);
    }
};

Specification

Specification(Ad)[x(int), y, r, x0, y0, x1, y1, score, ix0, iy0, ix1, iy1, rinv(float)].c(x0, y0, x1, y1)
=> 
struct Ad {
    int x, y, r, x0, y0, x1, y1, score, ix0, iy0, ix1, iy1;
    float rinv;
    Ad(int x0, int y0, int x1, int y1) {
        this->x0 = x0;
        this->y0 = y0;
        this->x1 = x1;
        this->y1 = y1;
    }
};


