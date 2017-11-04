#include<bits/stdc++.h>
using namespace std;
string to_binary(int n,int m)			
{
string a;
 for(int i=0;i<m;i++)
  {
  if(n%2==0)
  	a.push_back('0');
   else 
  	a.push_back('1');
   n=n/2;
  }
  reverse(a.begin(),a.end());
  return a;
}

int compare(string a,string b)
{
int n=a.length();
int c=0,d=0,k;
  for(int i=0;i<n;i++)
  	{
  	if(a[i]!=b[i])
  	{
  	c++;
  	k=i;
  	}
      else if(a[i]==b[i])
      d++;
      }
if(c==1) return k;
else if(d==n) return -2;
else return -1;
} 
string change(string a,int l)
{ 
a[l]='_';
return a;
}
void check_like(string a,vector<string>&b)
{
int flag=0,n=b.size();
 for(int i=0;i<n;i++)
  {
  if(compare(a,b[i])==-2)return;
  else flag++;
  }
 if(flag==n)
 b.push_back(a);
 return;
}

int main() 
{
int in,jn,kn;
vector<vector<string> >fn;	//vector having functions
int nf,no;
cout<<"Enter the no. of function: ";
cin>>nf;
cout<<"Enter the no .of variables: ";
cin>>no;
vector<vector<int> >mn;
for(in=0;in<nf;in++)
{
vector<int >tempo;
int m1;

cout<<"Enter the no. of minterms of "<<in+1<<" Function: ";
cin>>m1;
cout<<"Enter their decimal representaton: ";
	for(jn=0;jn<m1;jn++)
	{
	int a;
	cin>>a;
	tempo.push_back(a);
	}
	
mn.push_back(tempo);
}
for(in=0;in<nf;in++)
{
int c=0;
vector<int >tempo1;
	for(jn=0;jn<pow(2,no);jn++)
	{
	if(mn[in][c]!=jn)
		tempo1.push_back(jn);
	else
	c++;
	}
mn.push_back(tempo1);
}
/*for(in=0;in<mn.size();in++)
	{
		for(jn=0;jn<mn[in].size();jn++)
		cout<<mn[in][jn]<<" ";
	cout<<"\n";
	}*/
	
for(int i1=0;i1<(2*nf);i1++)		//tabulation to find the minimized 
{

	 int i,j,k,n,m,l,row,col,count;
	 n=mn[i1].size();
	 vector<string>temps;
	 vector<string>terms;
	 vector<string>vect;
	 vector<string>prime;
	 vector<string>temp1;
	 vector<string>ep;
	 vector<int>temp2;
	 vector<pair<int,int> >temp3;
	 
	 int a[n];
	 
	 for(int r1=0;r1<n;r1++)
	 a[r1]=mn[i1][r1];
     	for(int i=0;i<n;i++)
	vect.push_back(to_binary(a[i],no));
	for(int i=0;i<vect.size();i++)
	terms.push_back(vect[i]);

	while(!vect.empty())
		{
		 for(i=0;i<vect.size()-1;i++)
		  {
		  int c=0;
		    for(j=i+1;j<vect.size();j++)
		     {
		     l=compare(vect[i],vect[j]);
			 if(l!=-1 && l!=-2)
			  {
			  temp1.push_back(change(vect[i],l));
			  temp2.push_back(j);
			  }
			 else c++;
		     }
		     if(c==j-i-1)
		     	{ int d=0;for(int k=0;k<temp2.size();k++)
		     		{
		     		if(i==(temp2[k]))
		     			{d=1;break;}
		     		}
		     		 if(d==0) check_like(vect[i],prime);
			  }
		  }
		  int d=0;
		  for(int k=0;k<temp2.size();k++)
		  {
		  	if(i==(temp2[k]))
		  		{d=1;break;}
		  }
		  if(d==0)check_like(vect[i],prime);
		  vect.clear();
		  for(int i=0;i<temp1.size();i++)
		   	{
		   		vect.push_back(temp1[i]);
		   	}
		   temp1.clear();
		   temp2.clear();
		}
	vector<string>().swap(temp1);
	vector<int>().swap(temp2);
	vector<string>().swap(vect);
	//cout<<"PI"<<endl;
	//for(int i=0;i<prime.size();i++)
	//	{cout<<prime[i]<<endl;}


	row=prime.size();
	col=n;
	int**t = new int*[row+1];
	for(int i=0;i<row+1;i++)
	{  t[i]=new int[col];
	}

	for(int i=0;i<row+1;i++)
	{for(int j=0;j<col;j++)
	  t[i][j]=0;
	}
	for(int i=0;i<row;i++)
	 { int c;
	 int n1=terms.size();
	 int m1=prime[i].length();
	 for(int j=0;j<n1;j++)
	 { c=1;
	   for(int k=0;k<m1;k++)
	   { if(prime[i][k]!='_'){if(prime[i][k]!=terms[j][k]){c=0;break;}}}
	   if(c==1)t[i][j]=1;
	 }
	 }
	for(j=0;j<col;j++)
	 {count=0;
	   for(i=0;i<row;i++)
	    { if(t[i][j]==1) {count++;k=i;}}
	   if(count==1){temp3.push_back(make_pair(j,k));}
	 }

	for(i=0;i<temp3.size();i++)
	{ if(t[row][temp3[i].first]!=1)
	   { ep.push_back(prime[temp3[i].second]);
	     t[temp3[i].second][temp3[i].first]=-1;
	     t[row][temp3[i].first]=1;
	     for(j=0;j<col;j++)
		{ if(t[temp3[i].second][j]==1)
		    {for(k=0;k<row;k++)
		      { if(t[k][j]==1)
		         t[k][j]=-1;
		      }
		     t[row][j]=1;
		    }
		 }
	     }
	}
	temp3.clear();

	for(i=0;i<row;i++)
	{ count=0;
	  for(j=0;j<col;j++)
	  { if(t[i][j]==1)
	    count++;
	  }
	  if(count>0){temp3.push_back(make_pair(count,i));}
	}
	sort(temp3.begin(),temp3.end());

	if(!temp3.empty())
	{i=temp3.size()-1;
	{ ep.push_back(prime[temp3[i].second]);
	  for(j=0;j<col;j++)
	    { if(t[temp3[i].second][j]==1)
		{ for(k=0;k<row;k++)
		  { if(t[k][j]==1)
		     {t[k][j]=-1;}
		  }
		}
	    }
	}

	while(1)
	{k=1;
	 for(i=0;(i<temp3.size()-k && i>=0);i++)
	 {count=0;
	  for(j=0;j<col;j++)
	  { if(t[temp3[i].second][j]==1)
	     count++;
	  }
	  if(count>0)
	  {temp3[i].first=count;}else temp3[i].first=0;
	  }
	 sort(temp3.begin(),temp3.end()-k);
	 i=temp3.size()-1-k;
	 if(temp3[i].first>0)
	 {ep.push_back(prime[temp3[i].second]);
	  for(j=0;j<col;j++)
	    { if(t[temp3[i].second][j]==1)
		{ for(k=0;k<row;k++)
		  { if(t[k][j]==1)
		     {t[k][j]=-1;}
		  }
		}
	    }
	}
	else 
	break;
	k++;
	}
	//cout<<"Essential Prime Implicants are: "<<endl;
	for(int i=0;i<ep.size();i++)
	{
	//cout<<ep[i]<<" ";
	temps.push_back(ep[i]);
	}
	}
	else
	{
	//cout<<"Essential Prime Implicants are: "<<endl;
	for(int i=0;i<prime.size();i++)
	{
	//cout<<prime[i]<<" ";
	temps.push_back(prime[i]);				//pushing the essential prime implicants in the Vector
	}
	}
fn.push_back(temps);
//cout<<"\n\n";
}

/*for(int i=0;i<fn.size();i++)
	{
	for(int j=0;j<fn[i].size();j++)
	cout<<fn[i][j]<<" ";
	cout<<"\n";
	}*/
	
vector<string >w;

for(int i=0;i<pow(2,nf);i++)					//converting decimal to binary for furthur uses
w.push_back(to_binary(i,nf));


/*for(int i=0;i<w.size();i++)
	{
	for(int j=0;j<w[i].size();j++)
	cout<<w[i][j]<<" ";
	cout<<"\n";
	}*/
vector<set<string> > fnc;




for(int i=0;i<w.size();i++)				//making the group of all the possible arrangements
	{
	set<string> tempse;
	for(int j=0;j<w[i].size();j++)
	{
	
		if(w[i][j]=='0')
		{
		for(int k=0;k<fn[j+nf].size();k++)
		tempse.insert(fn[j+nf][k]);
		}
	
		else
		{
		for(int k=0;k<fn[j].size();k++)
		tempse.insert(fn[j][k]);
		}
	
	}
	fnc.push_back(tempse);
	}

int min=fnc[0].size();
int res=0;
for(int i=1;i<pow(2,nf);i++)			//check that which set of function have minimum no. of terms
{
	if(min>fnc[i].size())
	{
	res=i;min=fnc.size();
	}
}

//cout<<min<<""<<res;


string s=(to_binary(res,nf));    	//Finally prints the result 
cout<<"Functions are: ";
for(int i=0;i<s.size();i++)
{
if(s[i]=='0')
cout<<"f["<<i+1<<"]' ";
else
cout<<"f["<<i+1<<"] ";
}

return 0;
}





