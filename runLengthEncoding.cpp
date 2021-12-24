vector<string> split(string & x, char c) {
    vector<string> res;
    string tmp = "";
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == c) {
            res.push_back(tmp);
            tmp = "";
        } else {
            tmp += x[i];
        }
    }
    res.push_back(tmp);
    return res;
}

#define rep2(i,a,b, c) for(int i=(a);i<(b);i+=(c))
#define rep(i, a, b) rep2(i, a, b, 1)
//https://www.kaggle.com/slawekbiel/positive-score-with-detectron-1-3-input-data/
vector<vector<int>> rleDecode(string & maskRle, int * shape){
    //s = mask_rle.split()
    vector<string> s = split(maskRle, ' ');
    //starts, lengths = [np.asarray(x, dtype=int) for x in (s[0:][::2], s[1:][::2])]
    vector<int> starts, lengths;
    rep2(i, 0, s.size(), 2){
        starts.push_back(stoi(s[i]));
        lengths.push_back(stoi(s[i + 1]));
    }
    //starts -= 1
    rep(i, 0, starts.size()){
        starts[i] -= 1;
    }
    //ends = starts + lengths
    vector<int> ends;
    rep(i, 0, starts.size()){
        ends.push_back(starts[i] + lengths[i]);
    }
    //img = np.zeros(shape[0]*shape[1], dtype=np.uint8)
    int imgSize = shape[0] * shape[1];
    vector<int> img(imgSize, 0);
    // for lo, hi in zip(starts, ends):
    //     img[lo:hi] = 1
    rep(i, 0, starts.size()){
        rep(j, starts[i], ends[i]){
            img[j] = 1;
        }
    }
    // img.reshape(shape)
    // return img

    vector<vector<int>> res;
    rep(i, 0, shape[0]){
        vector<int> tmp;
        rep(j, 0, shape[1]){
            tmp.push_back(img[i * shape[1] + j]);
        }
        res.push_back(tmp);
    }
    return res;
}
