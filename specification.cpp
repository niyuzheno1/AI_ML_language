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
Create specification for the object that is defined by the problem (such as cars, traffic) etc.

Specification(Ad)[x(int), y, r, x0, y0, x1, y1, score, ix0, iy0, ix1, iy1, rinv(float)].c(x0, y0, x1, y1){Y}
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
    Y
};
		   
A better and more conscientious approach on getting random number:
		   
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
    synonymous int operator(int b) : next
	
    int next(int a, int b) {
        return next(b - a) + a;
    }
    synonymous int operator(int a, int b) : next
    double nextDouble(double b = 1) {
        return b * next() / 4294967296.0;
    }
    synonymous int operator(double a) : nextDouble
    double nextDouble(double a, double b) {
        return nextDouble(b - a) + a;
    }
    synonymous int operator(double a, double b) : nextDouble
};
"synonymous" keyword allows us to bind operator with function or values.
Example:
Assume that rnd is of type RandomGenerate
		   
rnd(1.0, 3.0) => rnd.nextDouble(1.0, 3.0)

		   
Random Shuffle:
RandomShuffleA(N, A, B);
=> 
C.resize(N, 0);
iota(C.begin(), C.end(), 0);
random_shuffle(C.begin(), C.end());
NA.resize(N, 0);
NB.resize(N, 0);
rep(i, N) NA[i] = A[C[i]], NB[i] = B[C[i]];

		   
Interval Arithemetics:
[a;b] discrete interval a, a+1, a+2, a+3, ... , b 
[a,b] continues interval a, supNotInclude((-infity, a] ), supNotInclude(supNotInclude((-infity, a])) ... b
[a;b] + c => [a+c; b+c]
[a;b] * c => [a * c; b * c] given c >= 0 and [b * c; a * c] given c < 0
[a;b) => {a, a+1, a+2, ... ,b-1}
Underlying transcompilation:
[a;b] =>
//assume that 
struct DiscreteSegment{
	int L;
	int R;
	DiscreteSegment(int x, int y){
		L = x;
		R = y;
		check();
	}
	bool check(){
		sortE(L, R);
	}
	DiscreteSegment operator + (int x){
		return DiscreteSegment(L + x, R + x);
	}
	bool include(int x);
};
//end
DiscreteSegment(a, b);
[a;b) =>
DiscreteSegment(a, b-1);						

 
Some consequences of interval arithematics:
bsearch[ll, x, 0, 1000][X](Condition)
can be equivalent to 
bsearch[ll, x][0; 1000][X](Condition)

Assume that sgt is a Segment Tree
sgt.getSum(0, 1000)
is equivalent to 
sgt.getSum[0;1000)
