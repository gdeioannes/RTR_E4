//============================================================================
// Name        : exercise412.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;



class Point2D{
public :
	float x;
	float y;

	Point2D(float x1,float y1){
		x=x1;
		y=y1;
	}

	Point2D(){
		x=0;
		y=0;
	}
};

struct sort_by_x
{
    inline bool operator() (const Point2D& struct1, const Point2D& struct2)
    {
        return (struct1.x > struct2.x);
    }
};

struct sort_by_y
{
    inline bool operator() (const Point2D& struct1, const Point2D& struct2)
    {
        return (struct1.y > struct2.y);
    }
};

class BoundingBox{
public :

	Point2D a;
	Point2D b;

	BoundingBox(Point2D pa,Point2D pb){
		a=pa;
		b=pb;
	}

	BoundingBox(){

	}

	bool contains(Point2D point){
		//that checks if a point is fully inside this bounding box.

		if(a.x >= point.x && a.y <= point.y && b.x <= point.x && b.y >= point.y){
			return true;
		}
		return false;
	}

	bool inside(BoundingBox boundingBox){
		//that checks if the bounding box itself is fully inside
		//another bounding box.
		if(contains(boundingBox.a) && contains(boundingBox.b)){
			return true;
		}
		return false;
	}

	bool intersect(BoundingBox boundingBox){
		//that checks if the bounding box itself intersects
		//with another bounding box.
		if(contains(boundingBox.a) || contains(boundingBox.b)){
			return true;
		}
		return false;
	}


	void print(string text){
		cout << text << endl;
	}

};

class KDNode{
public:
	//a flag whether it is an internal node or a leaf node.
	bool leaf;
	//two pointers to its left and right children (in case it is an internal node).
	KDNode * left;
	KDNode * right;
	//The dimension of the splitting line (in case it is an internal node).
	int splitDimension;
	//The position of the splitting line (in case it is an internal node).
	int splitPosition;
	//A (2D) point (in case it is a leaf node).
	Point2D point;
	//A range of type boundingbox that stores its corresponding bounds (and
	//implicitly the bounds of its subtree).
	BoundingBox range;
};

class KdTree{
private:
	//a private pointer to a kdnode (the root node of the kD-tree)
	int depth=0;

	//a private method reportSubtree(kdnode* n) that returns the set of all
	//(2D) points which are stored in the leaves of the subtree.
	vector<KDNode> reportSubtree(KDNode * n){
		vector<KDNode> list;
		return list;
	}

public:
	KDNode * node;
	//a public method build(P) that builds the kD-tree from a set P of (2D) points.

	KDNode build(vector<Point2D> p){
		KDNode newNode;
		newNode.splitDimension=depth;
		if(depth % 2 != 0){
			sort(p.begin(),p.end(),sort_by_x());
		}else{
			sort(p.begin(),p.end(),sort_by_y());
		}

		//increase depth for the next node
		depth++;

		//Print Points in each node creation
		for(int i=0;i<p.size();i++){
			cout << " _" << i << "->" << "x:" << p[i].x << " y:" << p[i].y;
		}
		cout << endl;

		if(p.size()==1){
			newNode.leaf=true;
			newNode.point=p[0];
			cout << "Leaf" << endl;
			return newNode;
		}else{
			newNode.leaf=false;
		}

		//Set Range of the bounding bos
		newNode.range.a=p[0];
		newNode.range.b=p[p.size()-1];

		//AVG to split
		int median=p.size()/2;

		cout << "Arrays median:" << median << endl;

		//https://stackoverflow.com/questions/9811235/best-way-to-split-a-vector-into-two-smaller-arrays
		vector<Point2D> split_lo(p.begin(), p.begin() + median);
		vector<Point2D> split_hi(p.begin() + median, p.end());
		if(p.size()%2!=0){
			split_hi.erase(split_hi.begin());
		}

		if(split_lo.size()>0){
			KDNode leftNode=build(split_lo);
			newNode.left = &leftNode;
		}
		if(split_hi.size()>0){
			KDNode rightNode=build(split_hi);
			newNode.left = &rightNode;
		}

		return newNode;
	}

	//a public method search(boundingbox range) that performs a range search
	//on the kD-tree and returns a set of (2D) points.
	vector<Point2D> search(BoundingBox range,KDNode * sNode){
		KDNode searchNode=*sNode;
		vector<Point2D> list;

		if(searchNode.leaf){
			list.push_back(searchNode.point);
			return list;
		}

		if (range.inside(searchNode.left->range)){
			//07 ReportSubtree(root.left);
			cout << "inside left" << endl;
		}

		if (range.intersect(searchNode.left->range)){
			//root.left.bbox intersects R) then
			//SearchkDTree(root.left, R)
			cout << "intersect" << endl;
			search(range,searchNode.left);
		}

		if (range.inside(searchNode.right->range)){
			//(root.right.bbox is fully contained in R) then
			//ReportSubtree(root.right);
			cout << "inside right" << endl;
		}

		if (range.intersect(searchNode.right->range)){
			//else if (root.right.bbox intersects R) then
			//SearchkDTree(root.right, R)
			cout << "intersect right" << endl;
			search(range,searchNode.right);
		}

		return list;
	}

};

void GetPointList(vector<Point2D> &pointList,BoundingBox &bb, string &finalCommand);

int main() {
	vector<Point2D> pointList;
	string finalCommand;
	BoundingBox bb;
	GetPointList(pointList,bb,finalCommand);
	cout << "Debug_1:" << finalCommand << endl;
	KdTree tree;
	tree.build(pointList);
	tree.search(bb,tree.node);
}

void GetPointList(vector<Point2D> &pointList,BoundingBox &bb, string &finalCommand){
	string str;
	int num;
	int count=0;
	getline(cin,str);
	istringstream ss(str);
	//Number of points
	ss >> num;
	while(getline(cin,str)){
		if(count<num){
			istringstream ss(str);
			Point2D point_a;
			ss >>  point_a.x >> point_a.y;
			pointList.push_back(point_a);
		}else{
			istringstream ss(str);
			ss >> bb.a.y >> bb.a.y >> bb.b.x >> bb.b.y >> finalCommand;
			break;
		}
		count++;
	}
}
