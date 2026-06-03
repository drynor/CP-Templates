/*
Algorithm: Segment Intersection
When to use: Use for segment intersection problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct Point{long long x,y;};long long cross(Point a,Point b,Point c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}bool between(long long a,long long b,long long x){return min(a,b)<=x&&x<=max(a,b);}bool on_segment(Point a,Point b,Point p){return cross(a,b,p)==0&&between(a.x,b.x,p.x)&&between(a.y,b.y,p.y);}bool segments_intersect(Point a,Point b,Point c,Point d){long long c1=cross(a,b,c),c2=cross(a,b,d),c3=cross(c,d,a),c4=cross(c,d,b);if(c1==0&&on_segment(a,b,c))return true;if(c2==0&&on_segment(a,b,d))return true;if(c3==0&&on_segment(c,d,a))return true;if(c4==0&&on_segment(c,d,b))return true;return (c1>0)!=(c2>0)&&(c3>0)!=(c4>0);}
