/*
Algorithm: Point Struct
When to use: Use for point struct problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

const double EPS=1e-9;struct Point{double x,y;Point(double x=0,double y=0):x(x),y(y){}Point operator+(Point o)const{return {x+o.x,y+o.y};}Point operator-(Point o)const{return {x-o.x,y-o.y};}};double dot(Point a,Point b){return a.x*b.x+a.y*b.y;}double cross(Point a,Point b){return a.x*b.y-a.y*b.x;}int sgn(double x){return (x>EPS)-(x<-EPS);}
