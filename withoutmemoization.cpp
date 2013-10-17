#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<utility>
using namespace std;

struct triplet{
	string pre, in, post;
	triplet(string s1, string s2, string s3){
		pre=s1;
		in=s2;
		post=s3;
	}
};


bool isPerm(string s1, string s2){
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	if(s1==s2)
		return true;
	return false;
}

bool comp(triplet t1, triplet t2){
	if(t1.pre<t2.pre)
		return true;
	else if(t1.pre==t2.pre)
		return t1.in<t2.in;
	return false;
}

bool isCorrect(string s){
	for(unsigned int i=0; i<s.length(); i++){
		if(s[i]=='0')
			return false;
	}
	return true;
}


string printHelper(int i){
	if(i==0)
		return "Pre";
	if(i==1)
		return "In";
	if(i==2)
		return "Post";
}
void printState(int arr[6]){
	cout<<printHelper(arr[0])<<" "<<printHelper(arr[1])<<" "<<printHelper(arr[2])<<" "
	<<printHelper(arr[3])<<" "<<printHelper(arr[4])<<" "<<printHelper(arr[5])<<endl;
}


int functionStates[][6]={{0,0,1,1,2,2},{0,0,1,2,1,2},{0,0,1,2,2,1},{0,0,2,1,1,2},{0,0,2,1,2,1},{0,0,2,2,1,1}, {0,1,0,1,2,2},{0,1,0,2,1,2},{0,1,0,2,2,1},{0,1,1,0,2,2},{0,1,1,2,0,2},{0,1,1,2,2,0}, {0,1,2,0,1,2},{0,1,2,0,2,1},{0,1,2,1,0,2},{0,1,2,1,2,0},{0,1,2,2,0,1},{0,1,2,2,1,0}, {0,2,0,1,1,2},{0,2,0,1,2,1},{0,2,0,2,1,1},{0,2,1,0,1,2},{0,2,1,0,2,1},{0,2,1,1,0,2}, {0,2,1,1,2,0},{0,2,1,2,0,1},{0,2,1,2,1,0},{0,2,2,0,1,1},{0,2,2,1,0,1},{0,2,2,1,1,0}, {1,0,0,1,2,2},{1,0,0,2,1,2},{1,0,0,2,2,1},{1,0,1,0,2,2},{1,0,1,2,0,2},{1,0,1,2,2,0}, {1,0,2,0,1,2},{1,0,2,0,2,1},{1,0,2,1,0,2},{1,0,2,1,2,0},{1,0,2,2,0,1},{1,0,2,2,1,0}, {1,1,0,0,2,2},{1,1,0,2,0,2},{1,1,0,2,2,0},{1,1,2,0,0,2},{1,1,2,0,2,0},{1,1,2,2,0,0}, {1,2,0,0,1,2},{1,2,0,0,2,1},{1,2,0,1,0,2},{1,2,0,1,2,0},{1,2,0,2,0,1},{1,2,0,2,1,0}, {1,2,1,0,0,2},{1,2,1,0,2,0},{1,2,1,2,0,0},{1,2,2,0,0,1},{1,2,2,0,1,0},{1,2,2,1,0,0}, {2,0,0,1,1,2},{2,0,0,1,2,1},{2,0,0,2,1,1},{2,0,1,0,1,2},{2,0,1,0,2,1},{2,0,1,1,0,2}, {2,0,1,1,2,0},{2,0,1,2,0,1},{2,0,1,2,1,0},{2,0,2,0,1,1},{2,0,2,1,0,1},{2,0,2,1,1,0}, {2,1,0,0,1,2},{2,1,0,0,2,1},{2,1,0,1,0,2},{2,1,0,1,2,0},{2,1,0,2,0,1},{2,1,0,2,1,0}, {2,1,1,0,0,2},{2,1,1,0,2,0},{2,1,1,2,0,0},{2,1,2,0,0,1},{2,1,2,0,1,0},{2,1,2,1,0,0}, {2,2,0,0,1,1},{2,2,0,1,0,1},{2,2,0,1,1,0},{2,2,1,0,0,1},{2,2,1,0,1,0},{2,2,1,1,0,0}};

triplet checkState(string s1, string s2, string s3, int i1, int i2, int i3, int func[6]){
	
//	cout<<s1<<"("<<s1.length()<<")"<<" "<<s2<<"("<<s2.length()<<")"<<" "<<s3<<"("<<s3.length()<<")"<<" "<<i1<<" "<<i2<<" "<<i3<<endl<<endl;
	
	if(!(isPerm(s1, s2) && isPerm(s2, s3) && isPerm(s1, s3)))
		return triplet("0", "0", "0");

	if(s1.length()==0)
	{
		return triplet("", "", "");
	}

	if(s1.length()==1)
	{
		if(s1==s2 && s2==s3)
		{
			return triplet(s1, s1, s1);
		}
		else
			return triplet("0", "0", "0");
	}
	
	if(i1==0 && i2==0 && i3==1){
		if(s1!=s2){
			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s3.find(s1[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");
		
		string left1=s1.substr(1, rootIndex), left2=s2.substr(1, rootIndex), left3=s3.substr(0, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[0], func[0], func[2], func);
		
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		
		triplet right=checkState(right1, right2, right3, func[1], func[1], func[3], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");

		return triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]);
		
	}
	else if(i1==0 && i2==1 && i3==0){
		if(s1!=s3){

			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s2.find(s1[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(1, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(1, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);

		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]);
		
	}
	
	else if(i1==1 && i2==0 && i3==0){
		if(s2!=s3){

			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s1.find(s2[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(0, rootIndex), left2=s2.substr(1, rootIndex), left3=s3.substr(1, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s2[0]+left.pre+right.pre, left.in+s2[0]+right.in, left.post+right.post+s2[0]);
		
	}

	else if(i1==0 && i2==2 && i3==0){
		if(s1!=s3){

			return triplet("0", "0", "0");
		}
		
		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{

			string left1=s1.substr(1, k), left2=s2.substr(0, k), left3=s3.substr(1, k);
			string right1=s1.substr(k+1), right2=s2.substr(k, s1.length()-1-k), right3=s3.substr(k+1);
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);

			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

			if(isCorrect(right.pre))
				v.push_back(triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]));

		}
		if(v.size()==0){
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];
	}
	
	else if(i1==0 && i2==0 && i3==2){
		if(s1!=s2){

			return triplet("0", "0", "0");
		}
		
		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{
			string left1=s1.substr(1, k), left2=s2.substr(1, k), left3=s3.substr(0, k);
			string right1=s1.substr(k+1), right2=s2.substr(k+1), right3=s3.substr(k, s1.length()-1-k);
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
			
			if(isCorrect(right.pre))
				v.push_back(triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]));
		}
		
		if(v.size()==0){
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];
		//check all
	}
	
	else if(i1==2 && i2==0 && i3==0){
		if(s3!=s2){

			return triplet("0", "0", "0");
		}
		
		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{
			//cout<<"i="<<k<<endl;
			string left1=s1.substr(0, k), left2=s2.substr(1, k), left3=s3.substr(1, k);
			string right1=s1.substr(k, s1.length()-1-k), right2=s2.substr(k+1), right3=s3.substr(k+1);
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
			
			if(isCorrect(right.pre))
				v.push_back(triplet(s2[0]+left.pre+right.pre, left.in+s2[0]+right.in, left.post+right.post+s2[0]));
		}
		
		if(v.size()==0){
			//cout<<"vector size is zero"<<endl;
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];
	}
	
	else if(i1==0 && i2==1 && i3==2){
		if(s3[s1.length()-1]!=s1[0])
		{
			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s2.find(s1[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(1, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex, s1.length()-1-rootIndex);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]);
		
	}
	
	else if(i1==0 && i2==2 && i3==1){
		if(s2[s1.length()-1]!=s1[0])
		{
			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s3.find(s1[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(1, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex, s1.length()-1-rootIndex), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]);
		
	}
	
	else if(i1==1 && i2==2 && i3==0){

		if(s2[s1.length()-1]!=s3[0])
		{
			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s1.find(s3[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(1, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex, s1.length()-1-rootIndex), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s3[0]+left.pre+right.pre, left.in+s3[0]+right.in, left.post+right.post+s3[0]);
		
	}
	
	else if(i1==1 && i2==0 && i3==2){

		if(s3[s1.length()-1]!=s2[0])
		{
			return triplet("0", "0", "0");
		}

		unsigned int rootIndex=s1.find(s2[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(0, rootIndex), left2=s2.substr(1, rootIndex), left3=s3.substr(0, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex, s1.length()-1-rootIndex);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s2[0]+left.pre+right.pre, left.in+s2[0]+right.in, left.post+right.post+s2[0]);
		
	}
	
	else if(i1==2 && i2==1 && i3==0){

		if(s1[s1.length()-1]!=s3[0])
		{
			return triplet("0", "0", "0");
		}

		unsigned int rootIndex=s2.find(s3[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(1, rootIndex);
		
		string right1=s1.substr(rootIndex, s1.length()-1-rootIndex), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s3[0]+left.pre+right.pre, left.in+s3[0]+right.in, left.post+right.post+s3[0]);
		
	}
	
	else if(i1==2 && i2==0 && i3==1){
		if(s1[s1.length()-1]!=s2[0])
		{
			return triplet("0", "0", "0");
		}

		unsigned int rootIndex=s3.find(s2[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(0, rootIndex), left2=s2.substr(1, rootIndex), left3=s3.substr(0, rootIndex);
		
		string right1=s1.substr(rootIndex, s1.length()-1-rootIndex), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s2[0]+left.pre+right.pre, left.in+s2[0]+right.in, left.post+right.post+s2[0]);
		
	}
	
	else if(i1==1 && i2==1 && i3==0){
		if(s1!=s2){

			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s1.find(s3[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(1, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s3[0]+left.pre+right.pre, left.in+s3[0]+right.in, left.post+right.post+s3[0]);
		
	}
	
	else if(i1==0 && i2==1 && i3==1){
		if(s3!=s2){

			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s3.find(s1[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(1, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]);
		
	}
	
	else if(i1==1 && i2==0 && i3==1){
		if(s1!=s3){

			return triplet("0", "0", "0");
		}
		unsigned int rootIndex=s3.find(s2[0]);
		
		if(rootIndex<0 || rootIndex >= s1.length())
			return triplet("0", "0", "0");

		string left1=s1.substr(0, rootIndex), left2=s2.substr(1, rootIndex), left3=s3.substr(0, rootIndex);
		
		string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);
		
		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		
		if(!isCorrect(right.pre))
			return triplet("0", "0", "0");
		return triplet(s2[0]+left.pre+right.pre, left.in+s2[0]+right.in, left.post+right.post+s2[0]);
		
	}
	
	else if(i1==0 && i2==2 && i3==2){
		if(s3!=s2){

			return triplet("0", "0", "0");
		}
		
		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{
			
			string left1=s1.substr(1, k), left2=s2.substr(0, k), left3=s3.substr(0, k);
			string right1=s1.substr(k+1), right2=s2.substr(k, s1.length()-1-k), right3=s3.substr(k, s1.length()-1-k);
			
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
			

			if(isCorrect(right.pre))
				v.push_back(triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]));
		}
		//cout<<"hello"<<v.size()<<endl;
		
		if(v.size()==0){
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];
	}
	
	else if(i1==2 && i2==0 && i3==2){
		if(s1!=s3){

			return triplet("0", "0", "0");
		}
		
		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{
			//cout<<"i="<<k<<endl;
			string left1=s1.substr(0, k), left2=s2.substr(1, k), left3=s3.substr(0, k);
			string right1=s1.substr(k, s1.length()-1-k), right2=s2.substr(k+1), right3=s3.substr(k, s1.length()-1-k);
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
			//cout<<"leftdone"<<endl;
			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
			
			//cout<<"i="<<k<<" "<<left.pre<<" "<<right.pre<<endl;

			if(isCorrect(right.pre))
				v.push_back(triplet(s2[0]+left.pre+right.pre, left.in+s2[0]+right.in, left.post+right.post+s2[0]));
		}
		
		if(v.size()==0){
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];
	}
	
	else if(i1==2 && i2==2 && i3==0){
		if(s1!=s2){

			return triplet("0", "0", "0");
		}
		
		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{
			string left1=s1.substr(0, k), left2=s2.substr(0, k), left3=s3.substr(1, k);
			string right1=s1.substr(k, s1.length()-1-k), right2=s2.substr(k, s1.length()-1-k), right3=s3.substr(k+1);
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
			
			if(isCorrect(right.pre))
				v.push_back(triplet(s3[0]+left.pre+right.pre, left.in+s3[0]+right.in, left.post+right.post+s3[0]));
		}
		if(v.size()==0){
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];
	}

	else if(i1==0 && i2==0 && i3==0)
	{
		if(s1!=s2 || s2!=s3 || s1!=s3)
			return triplet("0", "0", "0");

		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{
			string left1=s1.substr(1, k), left2=s2.substr(1, k), left3=s3.substr(1, k);
			string right1=s1.substr(k+1), right2=s2.substr(k+1), right3=s3.substr(k+1);
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
			
			if(isCorrect(right.pre))
				v.push_back(triplet(s1[0]+left.pre+right.pre, left.in+s1[0]+right.in, left.post+right.post+s1[0]));
		}
		
		if(v.size()==0){
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];
	}
	
	else if(i1==1 && i2==1 && i3==1)
	{
		if(s1!=s2 || s2!=s3 || s1!=s3)
			return triplet("0", "0", "0");
/*
		vector<triplet > v;
		for(unsigned int k=0; k<=s1.length()-1; k++)
		{
			string left1=s1.substr(0, k), left2=s2.substr(0, k), left3=s3.substr(0, k);
			string right1=s1.substr(k+1), right2=s2.substr(k+1), right3=s3.substr(k+1);
			
			triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
			if(!isCorrect(left.pre))
				continue;
			triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
			
			if(isCorrect(right.pre))
				v.push_back(triplet(s1[k]+left.pre+right.pre, left.in+s1[k]+right.in, left.post+right.post+s1[k]));
		}
		
		if(v.size()==0){
			return triplet("0", "0", "0");
		}
		sort(v.begin(), v.end(), comp);
		return v[0];*/
		pair<int, char> p=make_pair(0, 'Z');
		for(int k=0; k<s1.length(); k++){
			if(s1[k]<=p.second)
				p=make_pair(k, s1[k]);
		}
		int k=p.first;
		string left1=s1.substr(0, k), left2=s2.substr(0, k), left3=s3.substr(0, k);
		string right1=s1.substr(k+1), right2=s2.substr(k+1), right3=s3.substr(k+1);

		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			return triplet("0", "0", "0");
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);
		if(!isCorrect(right.pre))
			return(triplet("0", "0", "0"));
		return triplet(s1[k]+left.pre+right.pre, left.in+s1[k]+right.in, left.post+right.post+s1[k]);
			
	}

else if(i1==2 && i2==2 && i3==2)
{
	if(s1!=s2 || s2!=s3 || s1!=s3)
		return triplet("0", "0", "0");

	vector<triplet > v;
	for(unsigned int k=0; k<=s1.length()-1; k++)
	{
		string left1=s1.substr(0, k), left2=s2.substr(0, k), left3=s3.substr(0, k);
		string right1=s1.substr(k, s1.length()-1-k), right2=s2.substr(k, s1.length()-1-k), right3=s3.substr(k, s1.length()-1-k);

		triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
		if(!isCorrect(left.pre))
			continue;
		triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

		if(isCorrect(right.pre))
			v.push_back(triplet(s1[s1.length()-1]+left.pre+right.pre, left.in+s1[s1.length()-1]+right.in, left.post+right.post+s1[s1.length()-1]));
	}

	if(v.size()==0){
		return triplet("0", "0", "0");
	}
	sort(v.begin(), v.end(), comp);
	return v[0];
}

else if(i1==1 && i2==1 && i3==2){
	if(s1!=s2){

		return triplet("0", "0", "0");
	}
	unsigned int rootIndex=s1.find(s3[s3.length()-1]);

	if(rootIndex<0 || rootIndex >= s1.length())
		return triplet("0", "0", "0");

	string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);

	string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex, s1.length()-1-rootIndex);

	triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
	if(!isCorrect(left.pre))
		return triplet("0", "0", "0");
	triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

	if(!isCorrect(right.pre))
		return triplet("0", "0", "0");
	return triplet(s3[s3.length()-1]+left.pre+right.pre, left.in+s3[s3.length()-1]+right.in, left.post+right.post+s3[s3.length()-1]);

}

else if(i1==1 && i2==2 && i3==1){
	if(s1!=s3){

		return triplet("0", "0", "0");
	}
	unsigned int rootIndex=s3.find(s2[s1.length()-1]);

	if(rootIndex<0 || rootIndex >= s1.length())
		return triplet("0", "0", "0");

	string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);

	string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex, s1.length()-1-rootIndex), right3=s3.substr(rootIndex+1);

	triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
	if(!isCorrect(left.pre))
		return triplet("0", "0", "0");
	triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

	if(!isCorrect(right.pre))
		return triplet("0", "0", "0");
	return triplet(s2[s3.length()-1]+left.pre+right.pre, left.in+ s2[s3.length()-1]+right.in, left.post+right.post+s2[s3.length()-1]);
}

else if(i1==2 && i2==1 && i3==1){
	if(s3!=s2){

		return triplet("0", "0", "0");
	}
	unsigned int rootIndex=s3.find(s1[s1.length()-1]);

	if(rootIndex<0 || rootIndex >= s1.length())
		return triplet("0", "0", "0");

	string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);

	string right1=s1.substr(rootIndex, s1.length()-1-rootIndex), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex+1);

	triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);

		//cout<<"left is "<<left.pre<<endl;

	if(!isCorrect(left.pre))
		return triplet("0", "0", "0");
	triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

		//cout<<"right is"<<right.pre<<endl;

	if(!isCorrect(right.pre))
		return triplet("0", "0", "0");
	return triplet(s1[s3.length()-1]+left.pre+right.pre, left.in+s1[s3.length()-1]+right.in, left.post+right.post+s1[s3.length()-1]);
}

else if(i1==2 && i2==2 && i3==1){
	if(s1!=s2){

		return triplet("0", "0", "0");
	}
	unsigned int rootIndex=s3.find(s1[s1.length()-1]);

	if(rootIndex<0 || rootIndex >= s1.length())
		return triplet("0", "0", "0");

	string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);

	string right1=s1.substr(rootIndex, s1.length()-1-rootIndex), right2=s2.substr(rootIndex, s1.length()-1-rootIndex), right3=s3.substr(rootIndex+1);

	triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
	if(!isCorrect(left.pre))
		return triplet("0", "0", "0");
	triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

	if(!isCorrect(right.pre))
		return triplet("0", "0", "0");
	return triplet(s1[s3.length()-1]+left.pre+right.pre, left.in+s1[s3.length()-1]+right.in, left.post+right.post+s1[s3.length()-1]);

}

else if(i1==2 && i2==1 && i3==2){
	if(s1!=s3){

		return triplet("0", "0", "0");
	}
	unsigned int rootIndex=s2.find(s1[s1.length()-1]);

	if(rootIndex<0 || rootIndex >= s1.length())
		return triplet("0", "0", "0");

	string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);

	string right1=s1.substr(rootIndex, s1.length()-1-rootIndex), right2=s2.substr(rootIndex+1), right3=s3.substr(rootIndex, s1.length()-1-rootIndex);\

	triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
	if(!isCorrect(left.pre))
		return triplet("0", "0", "0");
	triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

	if(!isCorrect(right.pre))
		return triplet("0", "0", "0");
	return triplet(s1[s3.length()-1]+left.pre+right.pre, left.in+s1[s3.length()-1]+right.in, left.post+right.post+s1[s1.length()-1]);
}

else if(i1==1 && i2==2 && i3==2){
	if(s3!=s2){
		return triplet("0", "0", "0");
	}
	unsigned int rootIndex=s1.find(s2[s2.length()-1]);

	if(rootIndex<0 || rootIndex >= s1.length())
		return triplet("0", "0", "0");

	string left1=s1.substr(0, rootIndex), left2=s2.substr(0, rootIndex), left3=s3.substr(0, rootIndex);

	string right1=s1.substr(rootIndex+1), right2=s2.substr(rootIndex, s1.length()-1-rootIndex), right3=s3.substr(rootIndex, s1.length()-1-rootIndex);

	triplet left=checkState(left1, left2, left3, func[i1*2], func[i2*2], func[i3*2], func);
	if(!isCorrect(left.pre))
		return triplet("0", "0", "0");
	triplet right=checkState(right1, right2, right3, func[i1*2+1], func[i2*2+1], func[i3*2+1], func);

	if(!isCorrect(right.pre))
		return triplet("0", "0", "0");
	return triplet(s2[s3.length()-1]+left.pre+right.pre, left.in+s2[s3.length()-1]+right.in, left.post+right.post+s2[s3.length()-1]);
}


}

int main(){
	

	string pre, in, post;

	while(cin>>pre){
		cin>>in;
		cin>>post;

		unsigned int rootIndex=in.find(pre[0]);

		string leftIn=in.substr(0, rootIndex), rightIn=in.substr(rootIndex+1);
		string leftPre=pre.substr(1, rootIndex), rightPre=pre.substr(rootIndex+1);
		string leftPost=post.substr(0, rootIndex), rightPost=post.substr(rootIndex, post.length()-rootIndex-1);

		char root=pre[0];

		for(int i=0; i<90; i++){
		//	printState(functionStates[i]);
		//	cout<<"here we start"<<endl;
		//	if(functionStates[i][0]==0 && functionStates[i][1]==2 && functionStates[i][2]==1 && functionStates[i][3]==2 && functionStates[i][4]==0 && functionStates[i][5]==1){
		//	cout<<leftPre<<" "<<leftIn<<" "<<leftPost<<" "<<rightPre<<" "<<rightIn<<" "<<rightPost<<endl;

			triplet left=checkState(leftPre, leftIn, leftPost, functionStates[i][0], functionStates[i][2], functionStates[i][4], functionStates[i]);
			//	cout<<left.pre<<endl;
			//	cout<<"leftdone"<<endl;


			triplet right=checkState(rightPre, rightIn, rightPost, functionStates[i][1], functionStates[i][3], functionStates[i][5], functionStates[i]);

			//	cout<<right.pre<<endl;
			//	cout<<"rightdone"<<endl;

			if(!(isCorrect(left.pre) && isCorrect(right.pre)))
				continue;
			printState(functionStates[i]);
			cout<<root+left.pre+right.pre<<endl;
			cout<<left.in+root+right.in<<endl;
			cout<<left.post+right.post+root<<endl;

		//	cout<<endl<<endl;
		//	}

		}
	}
}