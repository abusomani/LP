/*    example     <- just give input here only : first line is number of production and then each production
3
E E+E 
E E*E
E id 
T F
F (E) 
F id
3
S AA
A aA
A b 
5
S Aa
S dAb
S dca
S cb
A c
3
E T+E
E T
T a
*/
#include <bits/stdc++.h>
#define MAX 1005
using namespace std;

set <char> NT;
set <char> T;
set < pair<int,pair<char,string> > > StateStart; 
map <int,pair<char,string> > ReduceProd;
map <char,set< pair<char,string> > > Closure;

struct States{
	int stateNo;
	pair<char,string> Start;
	vector <pair <char,string> > Prod;
	vector < pair< pair <char,int> ,string> > Trans;
}st[MAX];

int stateCount = 1;

bool isNonTerminal(char c)
{
    if(c >= 'A' && c <= 'Z')
        return true;
    return false;
}

void printClosure()
{
	cout<<"\n CLOSURE is\n";
	for(map<char,set<pair<char,string> > > ::iterator it = Closure.begin(); it != Closure.end(); it++)
	{
		pair<char,set<pair<char,string> > > p = *it;
		cout<<p.first<<"--> (  ";
		
		for(set< pair<char,string> >  :: iterator j = p.second.begin(); j != p.second.end(); j++)
		{
			pair<char,string> P = *j;
			cout<<P.first <<"->"<<P.second<<"  ";
		}
		cout<<")\n";
	}
}

void printReduceProd()
{
	for(map<int,pair<char,string> > ::iterator it = ReduceProd.begin(); it != ReduceProd.end(); it++)
	{
		pair <int , pair<char,string> > P = *it;
		cout<<P.first<<" ";
		
		pair<char,string> p = P.second;
		
		cout<<p.first<<"-->"<<p.second<<endl;
		
	}
}

void printStates()
{
	for(int i = 0; i <= stateCount; i++)
	{
		cout<<endl<<"State No - "<<st[i].stateNo<<"\n  {\n";
		
		cout<<"\n\tProductions :-\n ";
		for(vector<pair<char,string> > ::iterator it = st[i].Prod.begin(); it != st[i].Prod.end(); it++)
		{
			pair<char,string> p = *it;
			cout<<"\t"<<p.first<<"->"<<p.second<<endl;
		}
		
		cout<<"\n\tTransitions :-\n";
		for(vector<pair<pair<char,int>,string> > ::iterator it = st[i].Trans.begin(); it != st[i].Trans.end(); it++)
		{
			pair<pair<char,int>,string> p = *it;
			if(p.first.second != -1)
			cout<<"\t\t"<<p.first.first<<"->"<<p.first.second<<"  :  "<<p.second<<endl;
			else
			cout<<"\t"<<p.first.first<<"  "<<"   :  "<<p.second<<endl;
		}
		
		cout<<"  }\n";
	}
}

void printNT()
{
	for(set<char> ::iterator it = NT.begin(); it != NT.end(); it++)
	{
		cout << (*it) <<"\t";	
	}	
}

void printT()
{
	for(set<char> ::iterator it = T.begin(); it != T.end(); it++)
	{
		cout << (*it) <<"\t";	
	}
	
}
string isReduce(int i)
{

	for(vector<pair<pair<char,int>,string> >:: iterator it = st[i].Trans.begin(); it != st[i].Trans.end(); it++){
		pair<pair<char,int>,string> p = *it;

		if(p.second[0] == 'r')
			return p.second;
	}

	return "";
}

string alreadyTrans(int i,char c)
{
	vector<pair<pair<char,int>,string> > :: iterator j;
	
	for(vector<pair<pair<char,int>,string> > :: iterator it = st[i].Trans.begin(); it != st[i].Trans.end(); it ++)
	{
		pair<pair<char,int>,string> p = *it;
		
		if(p.first.first == c)
		{
			string s = "|" + p.second;
			st[i].Trans.erase(it);
			return s;
		}
	}

	return "";	
}

void printRed(int i,string red)
{

	for(set<char> :: iterator it = T.begin(); it != T.end(); it++)
		{
			string add = "";
			bool flag = false;
			
			for(vector < pair< pair <char,int> ,string> > ::iterator j = st[i].Trans.begin(); j != st[i].Trans.end(); j++)
			{
				pair<pair<char,int>,string> p = *j;
				
				if(p.first.first == *it)
					{
						add = p.second;
						add += "|" + red;
						flag = true;
						break;
					}
			}
			if(flag)
			cout<<add<<"\t";
			else
			cout<<red<<"\t";
		}
	cout<<endl;
}

void parseTable()
{

	cout<<"\n\n\n***Parse Table***\n\n\n\t";
	
	printT();cout<<"\t";printNT();cout<<endl;
	
	for(int i = 0; i <= stateCount; i++)
	{
		cout <<i << "\t";
		string red;

		if((red = isReduce(i)) != "")
			{
				printRed(i,red);
				continue;
			}

		for(set<char> :: iterator it = T.begin(); it != T.end(); it++)
		{
			char c = *it;
			bool flag = false;

			for(vector<pair<pair<char,int>,string> > ::iterator k = st[i].Trans.begin(); k != st[i].Trans.end(); k++)
			{
				pair<pair<char,int> ,string> p = *k;

				if(p.first.first == c)
					{
						cout<<p.second<<"\t";
						flag = true;
					}
			}	

			if(!flag)
				cout<<"\t";
		}
		
		cout<<"\t";
		
		for(set<char> :: iterator it = NT.begin(); it != NT.end(); it++)
		{
			char c = *it;
			bool flag = false;
	
			for(vector<pair<pair<char,int>,string> > ::iterator k = st[i].Trans.begin(); k != st[i].Trans.end(); k++)
			{
				pair<pair<char,int> ,string> p = *k;
	
				if(p.first.first == c)
					{
						cout<<p.second<<"\t";
						flag = true;
					}
			}	
	
			if(!flag)
				cout<<"\t";
		}	

		
		
		cout<<endl;	
	}
}

void startString(char SS)
{
	//for state 0
	st[0].Start.first = 'Z';
	string s = ".";
	st[0].Start.second = s.append(1,SS);
	
	
	//for state 1 (ACCEPT STATE)
	st[1].Start.first = 'Z';
	s.clear();
	s.append(1,SS); 
	s = s + ".";
	st[1].Start.second = s;
	
	set<map<char,int> > Unique;
	Unique.insert(map<char,int>());
	
	//rest of the states
	for(map<int,pair<char,string> > ::iterator it = ReduceProd.begin(); it != ReduceProd.end(); it++)
	{
		pair<int, pair<char,string> > p1 = *it;
		pair<char,string> p = p1.second;

		string s = p.second , temp;
	
		for(int i = 1; i < s.size(); i++)
		{
			temp = s.substr(0,i) + "." + s.substr(i,s.size() - i);
			st[++stateCount].Start = make_pair(p.first,temp);
			StateStart.insert(make_pair(stateCount,st[stateCount].Start));
		}

		temp = s + ".";
		st[++stateCount].Start = make_pair(p.first,temp);
		StateStart.insert(make_pair(stateCount,st[stateCount].Start));
	}
	
}


void stateTrans()
{
	int num;
	for(int i = 0;  i <= stateCount; i++)
	{
//		if i is 0 then accept case transition

		if(i == 0)
			st[i].Trans.push_back(make_pair(make_pair('S',1),"1"));
		
		if(i == 1)
		{
			st[i].Trans.push_back(make_pair(make_pair('$',-1),"Acc"));
			continue;			
		}
			
		for(vector<pair<char,string> > ::iterator it = st[i].Prod.begin(); it != st[i].Prod.end(); it++)
		{
			pair <char,string> pii = *it;
			string s = pii.second;
			int posDot = s.find(".");
			string nextString;
			char closureChar = (posDot == s.size()-1) ? '$' : s[posDot + 1];
			
			
			if(posDot == s.size()-1)
			{
				nextString = "";
				s.erase(s.begin() + posDot);
			}
				
				
			else
				{
					s.erase(s.begin() + posDot);
					nextString = s;
					nextString.insert(nextString.begin() + posDot+1, 1,'.');
				}

			pair<char,string> number = make_pair(pii.first,s);

			if(nextString != "")
			{
				pair<char,string> match = make_pair(pii.first,nextString);
				
				for(set<pair<int,pair<char,string> > > ::iterator j = StateStart.begin(); j != StateStart.end(); j++)
				{
					pair<int,pair<char,string> > p  = *j;
					pair<char,string> pp = p.second;

					if(p.second == match and closureChar != '$')
					{
						char shift = 's';
					
						for(map<int,pair<char,string> > ::iterator l = ReduceProd.begin(); l != ReduceProd.end(); l++)
						{
							pair<int,pair<char,string> > pi = *l;
							pair<char,string> item = pi.second;

							if(s == item.second and pi.second.first == item.first)
								num = pi.first;
						}
						
						if(!isNonTerminal(closureChar))
						{
							string type,add;
							type.append(1,shift);
							ostringstream o;
							o << type << num;
							type = o.str();
//							add = alreadyTrans(i,closureChar);
//							type += add;
							st[i].Trans.push_back(make_pair(make_pair(closureChar,p.first),type));
						}
						
						else
						{
							string type,add;
							ostringstream o;
							o << p.first;
							type = o.str();
//							add = alreadyTrans(i,closureChar);
//							type += add;
							st[i].Trans.push_back(make_pair(make_pair(closureChar,p.first),type));
						}
					}
					
				}
			}

			else
			{
				char red = 'r';
				
				for(map<int,pair<char,string> > ::iterator l = ReduceProd.begin(); l != ReduceProd.end(); l++)
					{
						pair<int,pair<char,string> > pi = *l;
						pair<char,string> item = pi.second;

						if(s == item.second and item == number)
							num = pi.first;
					}

				string type,add;
				type.append(1,red);
				ostringstream o;
				o << type << num;
				type = o.str();
//				add = alreadyTrans(i,closureChar);
//				type += add;
				st[i].Trans.push_back(make_pair(make_pair(' ',-1),type));

			}
			
		}
		
	}
}

void stateProd()
{
	for(int i = 0;  i <= stateCount; i++)
	{
		st[i].stateNo = i;
		st[i].Prod.push_back(st[i].Start);
		
		string s = st[i].Start.second;
		int posDot = s.find(".");
		char closureChar = (posDot == s.size()-1) ? '$' : s[posDot + 1];
		
		if(closureChar != '$')
		{
			for(map<char,set<pair<char,string> > > ::iterator it = Closure.begin(); it != Closure.end(); it++)
			{
				pair<char,set<pair<char,string> > > p = *it;
				if(p.first == closureChar)
				{
					for(set<pair<char,string> > :: iterator j = p.second.begin(); j != p.second.end(); j++)
					{
						pair<char,string> P = *j;
						st[i].Prod.push_back(P);
					}
				}
			}
		}
	}
}

void createClosure()
{
	for(set<char> ::iterator it = NT.begin(); it != NT.end(); it++)
	{
		for(map<int,pair<char,string> > ::iterator j = ReduceProd.begin(); j != ReduceProd.end(); j++)
			{
				pair <int , pair<char,string> > P = *j;
				pair<char,string> p = P.second;
				
				if(p.first == (*it))
					{
						string s ="." + p.second;
						Closure[p.first].insert(make_pair(p.first,s));
					}
			}
	}
	
	map<char,set<pair<char,string> > > C = Closure;
	set<char> closAdd;
	set<char> :: iterator c;
	
	for(map<char,set<pair<char,string> > > ::iterator it = C.begin(); it != C.end(); it++)
	{
		pair<char,set<pair<char,string> > > p = *it;
		
		for(set<pair<char,string> > :: iterator j = p.second.begin(); j != p.second.end(); j++)
		{
			pair<char,string> P = *j;
			char n = P.second[1]; //character 'n' is the first element after .
			
//			cout<<p.first<<"   "<<n<<endl;
			
			if(isNonTerminal(n) and n != p.first)
			{
				closAdd.insert(n);
				
				while(!closAdd.empty())
				{
					
					c = closAdd.begin();
					//p.first is the char in whose closure we will add now
					
					for(set<pair<char,string> > ::iterator j = C[*c].begin(); j != C[*c].end(); j++)
					{
						pair<char,string> p1 = *j;
						
						if(isNonTerminal(p1.second[1]) and  (*c) != p1.second[1])
							closAdd.insert(p1.second[1]);
									
						Closure[p.first].insert(p1);
					}
					closAdd.erase(c);
				}
			}
			
		}
	}
	
	printClosure();
}

int main()
{
    string _temp;
    string _name = __FILE__;        //or use getcwd etc..
    freopen(_name.c_str(), "r", stdin);
    getline(cin, _temp);
    
    int prod,count = 0;
    cin >> prod;
    char A;
    string alpha;
    char SS = '-';
    
    while (prod--)
    {
        cin >> A;
        cin >> alpha;
			if(SS == '-')	SS = A;	
        count++;
	    ReduceProd.insert(make_pair(count,make_pair(A,alpha)));
	    for(int i = 0; i < alpha.size(); i++)
	    {
	    	if(isNonTerminal(alpha[i]))
	    		NT.insert(alpha[i]);
	    	else
	    		T.insert(alpha[i]);
	    }

	    NT.insert(A);
    }
	T.insert('$'); //treating as non-terminal
	printReduceProd();
//	printNT();
	createClosure();
//	DFA(SS,0);
	startString(SS);
	stateProd();
	stateTrans();
	printStates();
	parseTable();
	
	return 0;
}

//set<char> addProd(int stNo,pair<char,string> start)
//{
//	set<char> S;
//	
//	st[stNo].Prod.push_back(st[stNo].Start);
//		
//	string s = st[stNo].Start.second;
//	int posDot = s.find(".");
//	char closureChar = (posDot == s.size()-1) ? '$' : s[posDot + 1];
//	
//	if(closureChar != '$')
//	{
//		for(map<char,set<pair<char,string> > > ::iterator it = Closure.begin(); it != Closure.end(); it++)
//		{
//			pair<char,set<pair<char,string> > > p = *it;
//			if(p.first == closureChar)
//			{
//				for(set<pair<char,string> > :: iterator j = p.second.begin(); j != p.second.end(); j++)
//				{
//					pair<char,string> P = *j;
//					st[stNo].Prod.push_back(P);
//					S.insert(P.second[1]);
//				}
//			}
//		}
//	}
//
//	return S;
//}
//
//void newState(int i, char first)
//{
//	for()
//}
//
//
//void DFA(char SS,int stNo)
//{
//	if(stateCount < stNo)
//		return;
//		
//	set<char> first;
//		
//	if(stNo == 0 and SS == 'S' )
//	{
//		st[0].Start.first = 'Z';
//		string s = ".";
//		st[0].Start.second = s.append(1,SS);
//		first = addProd(stNo,st[0].Start);
//	}
//	
//	for(set<char> :: iterator it = first.begin(); it != first.end(); it++)
//	{
//		newState();
//	}
//	
//}
