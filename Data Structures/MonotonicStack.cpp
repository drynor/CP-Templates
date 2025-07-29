struct MonotonicStack{
    stack<pair<int,int>> st;
    
    int insert(int ind, int val){
        while(!st.empty() and st.top().s >= val){
            st.pop();
        }
        int ans;
        if(st.empty()) ans = -1;
        else           ans = st.top().f;
        
        st.push({ind, val});
        return ans;
    }
};
