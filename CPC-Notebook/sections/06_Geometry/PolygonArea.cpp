/*
Algorithm: Polygon Area
When to use: Use for polygon area problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct Point{long long x,y;};long long twice_signed_area(const vector<Point>&p){long long s=0;int n=p.size();for(int i=0;i<n;i++){int j=(i+1)%n;s+=p[i].x*p[j].y-p[i].y*p[j].x;}return s;}double polygon_area(const vector<Point>&p){return fabs((double)twice_signed_area(p))/2.0;}
