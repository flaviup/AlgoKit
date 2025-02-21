
#ifndef __COMMON_H__
#define __COMMON_H__

#include <vector>

typedef std::vector<int> vi; 
typedef std::vector<vi> vvi; 
typedef std::pair<int,int> ii;

#define sz(a) int((a).size()) 
#define pb push_back 
#define all(c) (c).begin(),(c).end() 
#define tr(c, i) for(typeof((c)).begin() i = (c).begin(); i != (c).end(); i++) 
#define present(c, x) ((c).find(x) != (c).end()) 
#define cpresent(c, x) (find(all(c),x) != (c).end()) 

#endif // __COMMON_H__
