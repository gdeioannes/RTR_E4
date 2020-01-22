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
#include <algorithm>

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
        return (struct1.x < struct2.x);
    }
};

struct sort_by_y
{
    inline bool operator() (const Point2D& struct1, const Point2D& struct2)
    {
        return (struct1.y < struct2.y);
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
		float maxX,maxY,minX,minY;
		if(a.x>b.x){
			maxX=a.x;
			minX=b.x;
		}else{
			maxX=b.x;
			minX=a.x;
		}
		if(a.y>b.y){
			maxY=a.y;
			minY=b.y;
		}else{
			maxY=b.y;
			minY=a.y;
		}

		if(maxX >= point.x && maxY >= point.y && minX <= point.x && minY <= point.y){
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
		if(contains(boundingBox.a) || contains(boundingBox.b) || boundingBox.contains(a) || boundingBox.contains(b)){
			return true;
		}
		return false;
	}

	void printRange(){
		cout << " a:" << " x->"<< a.x << " y->"<< a.y << " b:" << " x->" << b.x << " y->"<< b.y << endl;
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

	//Debug purpose
	void printPoint(){
		cout << " x->"<< point.x << " y->"<< point.y << endl;
	}
};

class KdTree{
private:
	KDNode* node;
	//a private pointer to a kdnode (the root node of the kD-tree)
	//a private method reportSubtree(kdnode* n) that returns the set of all
	//(2D) points which are stored in the leaves of the subtree.
	vector<KDNode> reportSubtree(KDNode * n){
		vector<KDNode> list;
		return list;
	}

	KDNode* build(vector<Point2D> p,int dim){
			KDNode* newNode=new KDNode;
			if(dim==0){
				node=newNode;
			}

			if(newNode->splitDimension % 2 == 0){
				sort(p.begin(),p.end(),sort_by_x());
			}else{
				sort(p.begin(),p.end(),sort_by_y());
			}

			//increase depth for the next node
			newNode->splitDimension=dim;
			cout << "Cr DEPTH->" << newNode->splitDimension << endl;

			//Print Points in each node creation
			for(int i=0;i<p.size();i++){
				cout << " _" << i << "->" << "x:" << p[i].x << " y:" << p[i].y;
			}
			cout << endl;

			if(p.size()==1){
				newNode->leaf=true;
				newNode->point=p[0];
				cout << "Leaf" << endl;
				return newNode;
			}else{
				newNode->leaf=false;
			}

			//AVG to split
			int median=p.size()/2;

			cout << "Arrays median:" << median << endl;

			//https://stackoverflow.com/questions/9811235/best-way-to-split-a-vector-into-two-smaller-arrays
			vector<Point2D> split_lo(p.begin(), p.begin() + median);
			vector<Point2D> split_hi(p.begin() + median, p.end());
			if(p.size()%2!=0){
				split_hi.erase(split_hi.begin());
			}

			//Set Range of the bounding box, by now arranging by x and Y to get min and max on each
			//array, this is n(log n) by quick sort
			sort(p.begin(),p.end(),sort_by_x());
			newNode->range.a.x=p[0].x;
			newNode->range.b.x=p[p.size()-1].x;
			sort(p.begin(),p.end(),sort_by_y());
			newNode->range.a.y=p[p.size()-1].y;
			newNode->range.b.y=p[0].y;
			cout << "KDnode Range ->";
			newNode->range.printRange();
			dim++;
			if(split_lo.size()>0){
				KDNode* lNode=new KDNode;
				newNode->left = build(split_lo,dim);
			}
			if(split_hi.size()>0){
				KDNode* rNode=new KDNode;
				newNode->right = build(split_hi,dim);
			}
			return newNode;
		}

public:
	//a public method build(P) that builds the kD-tree from a set P of (2D) points.
	KDNode build(vector<Point2D> p){
		build(p,0);
	}

	//a public method search(boundingbox range) that performs a range search
	//on the kD-tree and returns a set of (2D) points.
	void search(BoundingBox range,KDNode * sNode){
		KDNode searchNode=*sNode;
		cout << endl;
		cout << "DEPTH->" << searchNode.splitDimension << endl;
		cout << "BEGIN SEARCH RANGE" << endl;
		cout << "SEARCH RANGE->";
		range.printRange();
		cout << "NODE RANGE->";
		node->range.printRange();
		cout << "POINT NODE->";
		node->printPoint();

		if(searchNode.leaf){
			if(range.contains(node->point)){
				cout << "Leaft x->" << searchNode.point.x << " y->"<< searchNode.point.y;
			}
		}else{
			if(range.inside(searchNode.range)){
				//07 ReportSubtree(root.left);
				cout << "inside report sub tree" << endl;
			}else{
				cout << "Left Range->";
				searchNode.left->range.printRange();
				cout << "Right Range->";
				BoundingBox bob=searchNode.right->range;
				bob.printRange();
				if(range.inside(searchNode.left->range)){
					//07 ReportSubtree(root.left);
					cout << "inside report sub tree left" << endl;
				}else if (range.intersect(searchNode.left->range)){
					//root.left.bbox intersects R) then
					//SearchkDTree(root.left, R)
					cout << "intersect Left" << endl;
					search(range,searchNode.left);
				}
				if(range.inside(searchNode.right->range)){
					//07 ReportSubtree(root.left);
					cout << "inside report sub tree right" << endl;
				}else if (range.intersect(searchNode.right->range)){
					//else if (root.right.bbox intersects R) then
					//SearchkDTree(root.right, R)
					cout << "intersect right" << endl;
					search(range,searchNode.right);
				}
			}
		}
	}

	KDNode getNode(){
		return *node;
	}

	void search(BoundingBox range){
		search(range,node);
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
	cout << "Range"<< endl;
	tree.getNode().range.printRange();
	tree.getNode().left->range.printRange();
	tree.getNode().right->range.printRange();
	cout << "Search"<< endl;
	tree.search(bb);
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
