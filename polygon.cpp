#include <iostream> 
using namespace std; 
  #define INF 10000 
  
struct Point 
{ 
    int x; 
    int y; 
}; 
  
//to check if point lies on line pr
bool onLine(Point a, Point b, Point r) 
{ 
    if (b.x <= max(a.x, r.x) && b.x >= min(a.x, r.x) && 
            b.y <= max(a.y, r.y) && b.y >= min(a.y, r.y)) 
        return true; 
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point a, Point b, Point r) 
{ 
    int val = (b.y - a.y) * (r.x - b.x) - 
              (b.x - a.x) * (r.y - b.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The function that returns true if lines 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point a1, Point b1, Point a2, Point b2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(a1, b1, a2); 
    int o2 = orientation(a1, b1, b2); 
    int o3 = orientation(a2, b2, a1); 
    int o4 = orientation(a2, b2, a1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onLine(a1, a2, b1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onLine(a1, b2, b1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onLine(a2, a1, b2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onLine(a2, b1, b2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(Point polygon[], int n, Point a) 
{ 
    // There must be at least 3 vertices in polygon[] 
    if (n < 3)  return false; 
  
    // Create a point for line segment from p to infinite 
    Point extreme = {INF, a.y}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 
  
        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon[i], polygon[next], a, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], a, polygon[next]) == 0) 
               return onLine(polygon[i], a, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    return count&1;  // Same as (count%2 == 1) 
} 
  
// Driver program to test above functions 
int main() 
{ 
    Point polygon1[] = {{0, 0}, {10, 0}, {10, 10}, {0, 10}}; 
    int n = sizeof(polygon1)/sizeof(polygon1[0]); 
    Point a = {20, 20}; 
    isInside(polygon1, n, a)? cout << "Yes \n": cout << "No \n"; 
  
    a = {5, 5}; 
    isInside(polygon1, n, a)? cout << "Yes \n": cout << "No \n"; 
  
    Point polygon2[] = {{0, 0}, {5, 5}, {5, 0}}; 
    a = {3, 3}; 
    n = sizeof(polygon2)/sizeof(polygon2[0]); 
    isInside(polygon2, n, a)? cout << "Yes \n": cout << "No \n"; 
  
//    p = {5, 1}; 
//    isInside(polygon2, n, p)? cout << "Yes \n": cout << "No \n"; 
//  
//    p = {8, 1}; 
//    isInside(polygon2, n, p)? cout << "Yes \n": cout << "No \n"; 
//  
//    Point polygon3[] =  {{0, 0}, {10, 0}, {10, 10}, {0, 10}}; 
//    p = {-1,10}; 
//    n = sizeof(polygon3)/sizeof(polygon3[0]); 
//    isInside(polygon3, n, p)? cout << "Yes \n": cout << "No \n"; 
  
    return 0; 
}
