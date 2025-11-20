vector<int> build_fail(string a) {
    int n = a.size(), ln = 0;
    vector<int> fail(n, 0);
    for(int i = 1; i < n; i++){
        while(ln > 0 and a[ln] != a[i]) ln = fail[ln-1];
        if(a[ln] == a[i]) ln++;
        fail[i] = ln;
    }
    return fail;
}
void kmp(string a, string b, vector<int> fail){
    int n = a.size(), m = b.size(), ln = 0;
    for(int i = 0;i<n;i++){
        while(ln > 0 and b[ln] != a[i]) ln = fail[ln-1];
        if(b[ln] == a[i]) ln++;
        if(ln == m){
            cout << i - ln + 1 << endl;
            ln = fail[ln-1];
        }
    }
}
