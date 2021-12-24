//https://www.kaggle.com/slawekbiel/positive-score-with-detectron-1-3-input-data/
#define rep2(i,a,b, c) for(int i=(a);i<(b);i+=(c))
#define rep(i, a, b) rep2(i, a, b, 1)

void binaryMaskToRLE(vector<vector<int>> binaryMask){
    //rle = {'counts': [], 'size': list(binary_mask.shape)}
    map<string, vector<int>> rle;
    rle["counts"] = vector<int>();
    rle["size"] = vector<int>();
    rle["size"].push_back(binaryMask.size());
    rle["size"].push_back(binaryMask[0].size());
    //counts = rle.get('counts')
    vector<int> & counts = rle["counts"];
    //K = itertools.groupby(binary_mask.ravel(order='F'))
    vector<int> tmp;
    rep(i, 0, binaryMask.size()){
        rep(j, 0, binaryMask[0].size()){
            tmp.push_back(binaryMask[i][j]);
        }
    }
    struct temp{
        int val;
        vector<int> elements;
    };
    vector<temp> K;
    rep(i, 0, tmp.size()){
        temp t;
        if(K.size() == 0 || K[K.size() - 1].val != tmp[i]){
            t.val = tmp[i];
            t.elements = vector<int>();
            t.elements.push_back(tmp[i]);
            K.push_back(t);
        } else {
            K[K.size() - 1].elements.push_back(tmp[i]);
        }
    }


    // for i, (value, elements) in enumerate(K):
    rep(i, 0, K.size()){
        int value = K[i].val;
        vector<int> & elements = K[i].elements;
        //if i == 0 and value == 1:
        if(i == 0 && value == 1){
            //counts.append(0)
            counts.push_back(0);
        }
        //counts.append(len(list(elements)))
        counts.push_back(elements.size());

    }
}
