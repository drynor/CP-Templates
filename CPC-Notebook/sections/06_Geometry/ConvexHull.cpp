/*
Algorithm: Convex Hull
When to use: Use for convex hull problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct Point{long long x,y;bool operator<(const Point&o)const{return x==o.x?y<o.y:x<o.x;}};long long cross(Point a,Point b,Point c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}vector<Point> convex_hull(vector<Point>p){sort(p.begin(),p.end());p.erase(unique(p.begin(),p.end(),[](Point a,Point b){return a.x==b.x&&a.y==b.y;}),p.end());if(p.size()<=1)return p;vector<Point>h;for(auto pt:p){while(h.size()>=2&&cross(h[h.size()-2],h.back(),pt)<=0)h.pop_back();h.push_back(pt);}int lower=h.size();for(int i=(int)p.size()-2;i>=0;i--){while((int)h.size()>lower&&cross(h[h.size()-2],h.back(),p[i])<=0)h.pop_back();h.push_back(p[i]);}h.pop_back();return h;}
