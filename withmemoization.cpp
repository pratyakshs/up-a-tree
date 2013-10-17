#include <string>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct tree
{
	string tr[3];
};

bool operator<(tree const &t1,tree const &t2)
{
	if (t1.tr[0] < t2.tr[0]) return true;
	if (t2.tr[0] < t1.tr[0]) return false;
	if (t1.tr[1] < t2.tr[1]) return true;
	if (t2.tr[1] < t1.tr[1]) return false;
	if (t1.tr[2] < t2.tr[2]) return true;
	return false;
};

map<tree,tree> M;

string srt(string);
tree makeTree(tree);

int comb[] = {0,0,1,1,2,2};



int main ()
{
	tree T;
	cin >> T.tr[0] >> T.tr[1] >> T.tr[2];
	bool done = false;
	while (!done)
	{
		tree temp;
		M.clear();
		temp = makeTree(T);
		if (temp.tr[0] != "-")
		{
			for (int i = 0; i < 5; i++)
			{
				if (comb[i] == 0) cout << "Pre ";
				if (comb[i] == 1) cout << "In ";
				if (comb[i] == 2) cout << "Post ";
			}
			if (comb[5] == 0) cout << "Pre";
			if (comb[5] == 1) cout << "In";
			if (comb[5] == 2) cout << "Post";
			cout << endl;
			cout << temp.tr[0] << endl;
			cout << temp.tr[1] << endl;
			cout << temp.tr[2] << endl;
		}
		int i = 5;
		while ((i >= 1) && (comb[i] <= comb[i-1])) i--;
		if (i == 0) done = true;
		else
		{
			int j = i;
			while ((j < 6) && (comb[j] > comb[i-1])) j++;
			int tmp = comb[i-1];
			comb[i-1] = comb[j-1];
			comb[j-1] = tmp;
			sort(comb+i, comb+6);
		}
	}
	return 0;
}

tree makeTree(tree T)
{
	map<tree,tree>::iterator p = M.find(T);
	if (p != M.end()) return p->second;
	tree temp, temp1;
	if (T.tr[1].length() > 0)
	{
		if ((T.tr[0].length() > 0) && (T.tr[2].length() > 0))
		{
			int i = 0;
			while (T.tr[1][i] != T.tr[0][0]) i++;
			string s1, s2, s3, s4, s5, s6;
			s1.insert(s1.begin(), T.tr[1].begin(), T.tr[1].begin()+i);
			s2.insert(s2.begin(), T.tr[0].begin()+1, T.tr[0].begin()+i+1);
			s3.insert(s3.begin(), T.tr[1].begin()+i+1,T.tr[1].end());
			s4.insert(s4.begin(), T.tr[0].begin()+i+1,T.tr[0].end());
			s5.insert(s5.begin(), T.tr[2].begin(), T.tr[2].begin()+i);
			s6.insert(s6.begin(),T.tr[2].begin()+i, T.tr[2].end()-1);
			if (((comb[2]==comb[0]) && (s1 != s2)) ||
			    ((comb[2]==comb[4]) && (s1 != s5)) ||
			    ((comb[0]==comb[4]) && (s2 != s5)) ||
			    ((comb[3]==comb[1]) && (s4 != s3)) ||
			    ((comb[3]==comb[5]) && (s3 != s6)) ||
			    ((comb[1]==comb[5]) && (s4 != s6)) ||
			    (srt(s1) != srt(s2)) ||
			    (srt(s1) != srt(s5)) ||
			    (srt(s3) != srt(s4)) ||
			    (srt(s3) != srt(s6)))
			{
				temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
				M[T] = temp;
				return temp;
			}
			else
			{
				tree left, right;
				left.tr[0] = left.tr[1] = left.tr[2] = "";
				left.tr[comb[2]] = s1;
				left.tr[comb[0]] = s2;
				left.tr[comb[4]] = s5;
				left = makeTree(left);
				right.tr[0] = right.tr[1] = right.tr[2] = "";
				right.tr[comb[1]] = s4;
				right.tr[comb[3]] = s3;
				right.tr[comb[5]] = s6;
				right = makeTree(right);
				if ((left.tr[0] != "-") && (right.tr[0] != "-"))
				{
					temp.tr[0] = T.tr[0][0] + left.tr[0] + right.tr[0];
					temp.tr[1] = left.tr[1] + T.tr[0][0] + right.tr[1];
				 	temp.tr[2] = left.tr[2] + right.tr[2] + T.tr[0][0];
				}
				else
				{
					temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
				}
				M[T] = temp;
				return temp;
			}
		}
		else if (T.tr[0].length() > 0)
		{
			int i = 0;
			while (T.tr[1][i] != T.tr[0][0]) i++;
			string s1, s2, s3, s4;
			s1.insert(s1.begin(), T.tr[1].begin(), T.tr[1].begin()+i);
			s2.insert(s2.begin(), T.tr[0].begin()+1, T.tr[0].begin()+i+1);
			s3.insert(s3.begin(), T.tr[1].begin()+i+1,T.tr[1].end());
			s4.insert(s4.begin(), T.tr[0].begin()+i+1,T.tr[0].end());
			if (((comb[2]==comb[0]) && (s1 != s2)) ||
			    ((comb[3]==comb[1]) && (s4 != s3)) ||
			    (srt(s1) != srt(s2)) ||
			    (srt(s3) != srt(s4))) 
			{
				temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
				M[T] = temp;
				return temp;
			}
			else
			{
				tree left, right;
				left.tr[0] = left.tr[1] = left.tr[2] = "";
				left.tr[comb[2]] = s1;
				left.tr[comb[0]] = s2;
				left = makeTree(left);
				right.tr[0] = right.tr[1] = right.tr[2] = "";
				right.tr[comb[1]] = s4;
				right.tr[comb[3]] = s3;
				right = makeTree(right);
				if ((left.tr[0] != "-") && (right.tr[0] != "-"))
				{
					temp.tr[0] = T.tr[0][0] + left.tr[0] + right.tr[0] ;
					temp.tr[1] = left.tr[1] + T.tr[0][0] + right.tr[1] ;
				 	temp.tr[2] = left.tr[2] + right.tr[2] + T.tr[0][0] ;
				}
				else
				{
					temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
				}
				M[T] = temp;
				return temp;
			}
		}
		else if (T.tr[2].length() > 0)
		{
			int i = 0;
			while (T.tr[1][i] != T.tr[2][T.tr[2].length()-1]) i++;
			string s1, s3, s5, s6;
			s1.insert(s1.begin(), T.tr[1].begin(), T.tr[1].begin()+i);
			s3.insert(s3.begin(), T.tr[1].begin()+i+1,T.tr[1].end());
			s5.insert(s5.begin(), T.tr[2].begin(), T.tr[2].begin()+i);
			s6.insert(s6.begin(),T.tr[2].begin()+i, T.tr[2].end()-1);
			if (((comb[2]==comb[4]) && (s1 != s5)) ||
			    ((comb[3]==comb[5]) && (s3 != s6)) ||
			    (srt(s1) != srt(s5)) ||
			    (srt(s3) != srt(s6)))
			{
				temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
				M[T] = temp;
				return temp;
			}
			else
			{
				tree left, right;
				left.tr[0] = left.tr[1] = left.tr[2] = "";
				left.tr[comb[2]] = s1;
				left.tr[comb[4]] = s5;
				left = makeTree(left);
				right.tr[0] = right.tr[1] = right.tr[2] = "";
				right.tr[comb[3]] = s3;
				right.tr[comb[5]] = s6;
				right = makeTree(right);
				if ((left.tr[0] != "-") && (right.tr[0] != "-"))
				{
					temp.tr[0] = T.tr[2][T.tr[2].length()-1]+ left.tr[0] + right.tr[0];
					temp.tr[1] = left.tr[1] + T.tr[2][T.tr[2].length()-1] + right.tr[1];
				 	temp.tr[2] = left.tr[2] + right.tr[2] + T.tr[2][T.tr[2].length()-1];
				}
				else
				{
					temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
				}
				M[T] = temp;
				return temp;
			}
		}
		else
		{
			int i = 0;
			for (int j = 1; j < T.tr[1].length(); j++)
				if (T.tr[1][j] < T.tr[1][i]) i = j;
			string s1, s3;
			s1.insert(s1.begin(), T.tr[1].begin(), T.tr[1].begin()+i);
			s3.insert(s3.begin(), T.tr[1].begin()+i+1,T.tr[1].end());
			tree left, right;
			left.tr[0] = left.tr[1] = left.tr[2] = "";
			left.tr[comb[2]] = s1;
			left = makeTree(left);
			right.tr[0] = right.tr[1] = right.tr[2] = "";
			right.tr[comb[3]] = s3;
			right = makeTree(right);
			if ((left.tr[0] != "-") && (right.tr[0] != "-"))
			{
				temp.tr[0] = T.tr[1][i]+ left.tr[0] + right.tr[0];
				temp.tr[1] = left.tr[1] + T.tr[1][i] + right.tr[1];
			 	temp.tr[2] = left.tr[2] + right.tr[2] + T.tr[1][i];
			}
			else
			{
				temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
			}
			M[T] = temp;
			return temp;
		}
	}
	else if ((T.tr[0].length() > 0) && (T.tr[2].length() > 0))
	{
		if (T.tr[0][0] != T.tr[2][T.tr[2].length()-1])
		{
			temp.tr[0] = temp.tr[1] = temp.tr[2] = "-";
			M[T] = temp;
			return temp;
		}
		else
		{
			temp1.tr[0] = temp1.tr[1] = temp1.tr[2] = "-"; 
			for (int i = 0; i < T.tr[0].length(); i++)
			{
				string s1,s2,s3,s4;
				s1.insert(s1.begin(),T.tr[0].begin()+1,T.tr[0].begin()+i+1);
				s2.insert(s2.begin(),T.tr[0].begin()+i+1,T.tr[0].end());
				s3.insert(s3.begin(),T.tr[2].begin(),T.tr[2].begin()+i);
				s4.insert(s4.begin(),T.tr[2].begin()+i, T.tr[2].end()-1);
				if (((comb[0] == comb[4]) && (s1 != s3)) ||
				    ((comb[1] == comb[5]) && (s2 != s4)) ||
				    (srt(s1) != srt(s3)) ||
				    (srt(s2) != srt(s4))) continue;
				else
				{
					tree left, right;
					left.tr[0] = left.tr[1] = left.tr[2] = "";
					left.tr[comb[0]] = s1;
					left.tr[comb[4]] = s3;
					left = makeTree(left);
					right.tr[0] = right.tr[1] = right.tr[2] = "";
					right.tr[comb[1]] = s2;
					right.tr[comb[5]] = s4;
					right = makeTree(right);
					if ((left.tr[0] != "-") && (right.tr[0] != "-"))
					{
						temp.tr[0] = T.tr[0][0] + left.tr[0] + right.tr[0];
						temp.tr[1] = left.tr[1] + T.tr[0][0] + right.tr[1];
				 		temp.tr[2] = left.tr[2] + right.tr[2] + T.tr[0][0];
						if ((temp1.tr[0] == "-") || (temp < temp1)) temp1 = temp;
					}
				}
			}
			M[T] = temp1;
			return temp1;
		}
	}
	else if (T.tr[0].length() > 0)
	{
		temp1.tr[0] = temp1.tr[1] = temp1.tr[2] = "-"; 
		for (int i = 0; i < T.tr[0].length(); i++)
		{
			string s1,s2;
			s1.insert(s1.begin(),T.tr[0].begin()+1,T.tr[0].begin()+i+1);
			s2.insert(s2.begin(),T.tr[0].begin()+i+1,T.tr[0].end());
			tree left, right;
			left.tr[0] = left.tr[1] = left.tr[2] = "";
			left.tr[comb[0]] = s1;
			left = makeTree(left);
			right.tr[0] = right.tr[1] = right.tr[2] = "";
			right.tr[comb[1]] = s2;
			right = makeTree(right);
			if ((left.tr[0] != "-") && (right.tr[0] != "-"))
			{
				temp.tr[0] = T.tr[0][0] + left.tr[0] + right.tr[0];
				temp.tr[1] = left.tr[1] + T.tr[0][0] + right.tr[1];
				temp.tr[2] = left.tr[2] + right.tr[2] + T.tr[0][0];
				if ((temp1.tr[0] == "-") || (temp < temp1)) temp1 = temp;
			}
		}
		M[T] = temp1;
		return temp1;
	}
	else if (T.tr[2].length() > 0)
	{
		temp1.tr[0] = temp1.tr[1] = temp1.tr[2] = "-"; 
		for (int i = 0; i < T.tr[2].length(); i++)
		{
			string s3,s4;
			s3.insert(s3.begin(),T.tr[2].begin(),T.tr[2].begin()+i);
			s4.insert(s4.begin(),T.tr[2].begin()+i, T.tr[2].end()-1);
			tree left, right;
			left.tr[0] = left.tr[1] = left.tr[2] = "";
			left.tr[comb[4]] = s3;
			left = makeTree(left);
			right.tr[0] = right.tr[1] = right.tr[2] = "";
			right.tr[comb[5]] = s4;
			right = makeTree(right);
			if ((left.tr[0] != "-") && (right.tr[0] != "-"))
			{
				temp.tr[0] = T.tr[2][T.tr[2].length()-1] + left.tr[0] + right.tr[0];
				temp.tr[1] = left.tr[1] + T.tr[2][T.tr[2].length()-1] + right.tr[1];
			 	temp.tr[2] = left.tr[2] + right.tr[2] + T.tr[2][T.tr[2].length()-1];
				if ((temp1.tr[0] == "-") || (temp < temp1)) temp1 = temp;
			}
		}
		M[T] = temp1;
		return temp1;
	}
	else
	{
		temp.tr[0] = temp.tr[1] = temp.tr[2] = "";
		M[T] = temp;
		return temp;
	}
}


string srt(string s)
{
	sort(s.begin(),s.end());
	return s;
}