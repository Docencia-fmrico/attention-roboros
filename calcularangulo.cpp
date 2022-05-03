#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
bool anglefrom2Vec(vector<int> vector1,vector<int> vector2){
  float cos=(vector1[0]*vector2[0]+vector1[1]*vector2[1])/
  (sqrt(vector1[0]*vector1[0] + vector1[1]*vector1[1])*sqrt(vector2[0]*vector2[0] + vector2[1]*vector2[1]));
  if(cos>=0){
    //in front
    return true;
  }else{
    //in back
    return false;
  }
}

double euclideanDistance(vector<int> vector1,vector<int> vector2)
{
	double x = vector1[0] - vector2[0]; //calculating number to square in next step
	double y = vector1[1] - vector2[1];
	double dist;

	dist = x*x + y*y;       //calculating Euclidean distance
	dist = sqrt(dist);

	return dist;
}

int main(int argc, char const *argv[]) {
  
}
