struct MonotonicStack{
    stack<pair<int,int>> st;
    int insert(int ind, int val){
        while(!st.empty() and st.top().s >= val) st.pop();
        int ans;
        if(st.empty()) ans = -1;
        else           ans = st.top().f;
        
        st.push({ind, val});
        return ans;
    }
};

struct S{
    vector< pair< int , int > > v;
    vector< pair< int , pair< int , int> > > op;
    int idx = 0;
 
    S(){
        v.clear();
        v.push_back({1, -1});
        idx = 1;
    }
 
    void push(int x,int y){
        int before = idx;
        while(idx > 1 && y >= v[idx - 1].second) idx--;
        if(idx == (int)v.size()){
            v.push_back({-1, -1});
        }
        op.push_back({before, v[idx]});
        v[idx++] = {x, y};
    }
 
    void pop(){
        idx--;
        v[idx] = op.back().second;
        idx = op.back().first;
        op.pop_back();
    }
 
    int get(int val){
        // cout << "get " << val << endl;
        // for(int i = 0 ;i < idx;i++) cout << v[i].first << " " << v[i].second << endl;
 
        int id = upper_bound(v.begin(),v.begin() + idx,make_pair(val, oo)) - v.begin();
        if(id == idx) return -1;
        return v[id].second;
    }
};
