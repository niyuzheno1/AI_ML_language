struct StratifiedKFold{
    //It was supposed to have a self-declared random generator
    int n_fold;
    int shuffle;
    int threshold; //drop out threshold
    StratifiedKFold(int _split, bool _shuffle, int _threshold){
        n_fold = _split;
        shuffle = _shuffle;
        threshold = _threshold;
    }
    //assume that b is sortable 
    VI split(VI a, vector<int> _b){
        assert(a.size() == _b.size());
        
        // b must be discrete and dense
        HashMap<int, int> cnt1, cnt2;
        vector<int> b;        
        int n = a.size();
        vector<int> olda; 
        olda = a;
        olda.resize(n);
        rep(i, n) olda[i] = i;  
        if(shuffle){
            VI cc, aa, bb;
            cc.resize(n);
            aa.resize(n);
            bb.resize(n);
            rep(i, n) cc[i] = i;
            random_shuffle(cc.begin(), cc.end());
            olda = cc;
            rep(i, n){
                aa[i] = a[cc[i]];
                bb[i] = _b[cc[i]];
            }
            a = aa;
            b = bb;
        }

        b.resize(n, 0); 
        int * c = nullptr;
        walloc1d(&c, n);
        rep(i, n) c[i] = _b[i];
        sortA(n, c);
        rep(i, n) {
            b[i] = lower_bound(c, c+n, _b[i]) - c;
        }
        cnt1.init(n);
        cnt2.init(n);
        rep(i, n){
            cnt1[b[i]]++;
        }
        int m = 0;
        rep(i, n){
            if(cnt1[b[i]] * threshold < n) continue;
            cnt2[b[i]]++;
            ++m;
        } 
        HashMap<int, int*> redistributor; 
        HashMap<int, int> redistributor_sz;
        redistributor.init(m);
        redistributor_sz.init(m);
        rep(i, n){
            if(cnt2.exist(b[i]) == 0) continue;
            if(redistributor.exist(b[i]) == 0) {
                redistributor_sz[b[i]] = 0;
                int sz = cnt2[b[i]];
                int * p = nullptr;
                walloc1d(&p, sz);
                rep(j, sz ) p[j] = 0;
                redistributor[b[i]] = p;
            }
            int * p = redistributor[b[i]];
            p[redistributor_sz[b[i]]++] = i;
        }
        VI fold;
        fold.resize(n, -1);
        rep(i, n){
            if(redistributor.exist(b[i]) == 0) continue;
            int * p = redistributor[b[i]];
            int sz = redistributor_sz[b[i]];
            rep(fd, n_fold){
                int base = fd * sz / n_fold;
                int nexty = (fd + 1) * sz / n_fold;
                if(fd == n_fold -1) nexty = sz;
                rep(j, base, nexty){
                    fold[p[j]] = fd;
                }
            }

            redistributor_sz[b[i]] = 0;
        }
        VI foldret; 
        foldret.resize(n, -1);
        rep(i, n)  foldret[olda[i]] = fold[i];
        return foldret;
    }
};
