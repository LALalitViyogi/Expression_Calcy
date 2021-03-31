#include<iostream>
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
class node
{
public:
    int num;
    string input;
    string data;
    node * next;
    node(int query,string one, string two)
    {
        num=query;
        input=one;
        data=two;
    }
};
node * add(node * head,int query,string one,string two)
{
    node * temp= new node(query,one,two);
    node * curr=head;
    temp->next=NULL;
    if(head==NULL)
    {
        head=temp;
    }
    else
    {
        while(curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next=temp;
    }
    return head;
}

int prec(char c)
{
    if(c=='^')
    {
        return 3;
    }
    else if( c=='*' || c=='/')
    {
        return 2;
    }
    else if(c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
int prefixeval(string exp)
{
    int l=exp.length();
    stack<int> st;
    for(int i=l-1;i>=0;i--)
    {
        if (exp[i] >= '0' && exp[i] <= '9') {
			st.push(exp[i]-'0');
		}
        else
        {
            int x = st.top();
            st.pop();
            int y = st.top();
            st.pop();

            if (exp[i] == '+')
				st.push(y + x);

			else if (exp[i] == '-')
				st.push(y - x);

			else if (exp[i] == '*')
				st.push(y * x);

			else if (exp[i] == '/')
				st.push(y / x);

            else if (exp[i]=='^')
                st.push(pow(y,x));
        }
    }
    return st.top();
}
string inpostfix(string exp)
{
    stack<char> st;
    st.push('N');
    int l = exp.length();
    string ns;
    for(int i=0;i<l;i++)
    {
        if(isdigit(exp[i]))
        {
            ns += exp[i];
        }
        else if(exp[i]=='(')
        {
            st.push('(');
        }
        else if(exp[i]==')')
        {
            while(st.top()!='N' && st.top()!='(')
            {
                char c = st.top();
                st.pop();
                ns +=c;
            }
            if(st.top() =='(')
            {
                char c =st.top();
                st.pop();
            }
        }
        else
        {
            while(st.top()!='N' && prec(exp[i])<=prec(st.top()))
            {
                char c =st.top();
                st.pop();
                ns += c;
            }
            st.push(exp[i]);
        }
    }
    while(st.top()!='N')
    {
        char c = st.top();
        st.pop();
        ns += c;
    }
    return ns;

}
string postinfix(string exp)
{
    stack<string> st;
    int l= exp.length();

    for(int i=0;exp[i]!='\0';i++)
    {
        if(isdigit(exp[i]))
        {
            string op(1,exp[i]);
            st.push(op);
        }
        else if(prec(exp[i])>0)
        {
            string m =st.top();
            st.pop();
            string n=st.top();
            st.pop();
            st.push("("+n+exp[i]+m+")");
        }
    }
    return st.top();
}
int postfixEval(string exp)
{
	stack<int> st;

	for (int i = 0; i < exp.length(); i++)
	{

		if (exp[i] >= '0' && exp[i] <= '9') {
			st.push(exp[i] - '0');
		}

		else
		{
			int x = st.top();
			st.pop();

			int y = st.top();
			st.pop();

			if (exp[i] == '+')
				st.push(y + x);

			else if (exp[i] == '-')
				st.push(y - x);

			else if (exp[i] == '*')
				st.push(y * x);

			else if (exp[i] == '/')
				st.push(y / x);

            else if (exp[i]=='^')
                st.push(pow(y,x));
		}
	}
	return st.top();
}
string infixtoprefix(string exp)
{
    int l=exp.length();
    reverse(exp.begin(),exp.end() );

    for(int i=0;i<l;i++)
    {
        if(exp[i]=='(')
        {
            exp[i]=')';
            i++;
        }
        if (exp[i]==')')
        {
            exp[i]=='(';
            i++;
        }
    }
    string prefix =inpostfix(exp);
    reverse(prefix.begin(),prefix.end());
    return prefix;
}
string prefixtoinfix(string exp)
{
    stack<string> st;
    int l=exp.length();
    for(int i= l-1;i>=0;i--)
    {
        if(prec(exp[i])>0)
        {
            string m =st.top();
            st.pop();
            string n = st.top();
            st.pop();
            string temp= "(" + m + exp[i] + n + ")";
            st.push(temp);
        }
        else
        {
            st.push(string(1,exp[i]));
        }
    }
    return st.top();
}
string pretopost(string exp)
{
    stack<string> st;
    int l=exp.length();
    for(int i= l-1;i>=0;i--)
    {
        if(prec(exp[i])>0)
        {
            string m =st.top();
            st.pop();
            string n = st.top();
            st.pop();
            string temp=  m + n + exp[i] ;
            st.push(temp);
        }
        else
        {
            st.push(string(1,exp[i]));
        }
    }
    return st.top();
}
string posttopre(string exp)
{
    stack<string> st;
    int l=exp.length();
    for(int i=0;i<l;i++)
    {
        if(prec(exp[i])>0)
        {
            string m =st.top();
            st.pop();
            string n = st.top();
            st.pop();
            string temp= exp[i] + n + m;
            st.push(temp);
        }
        else
        {
            st.push(string(1,exp[i]));
        }
    }
    return st.top();
}
int infixeval(string exp)
{
    int value=postfixEval(inpostfix(exp));
    return value;
}
void display(node * head)
{
    node * temp =head;
    if(head==NULL)
    {
        cout<<"No History TO Show"<<endl;
        return;
    }
    cout<<setw(7)<<"SrNo."<<setw(7)<<"Choice "<<setw(15)<<"input string"<<setw(15)<<"Output String"<<endl;
    int i=1;
    while(temp!=NULL)
    {
        cout<<setw(6)<<i<<setw(4)<<temp->num<<" -> "<<setw(10)<<temp->input<<" : "<<setw(10)<<temp->data<<endl;
        temp=temp->next;
        i++;
    }
}
int main()
{
    int t;
    node * head=NULL;
    cout<<"---------------------Viyogi Expression Calcy---------------------"<<endl;
    cout<<"Enter Number 786:";
    cin>>t;
    while(t)
    {
        cout<<"----------------------------------------------"<<endl;
        cout<<"1. INFIX_TO_POSTFIX \t";
        cout<<"6. POSTFIX_TO_INFIX"<<endl;
        cout<<"2. INFIX_TO_PREFIX \t";
        cout<<"7. PREFIX_TO_INFIX"<<endl;
        cout<<"3. PREFIX_TO_POSTFIX \t";
        cout<<"8. POSTFIX_TO_PREFIX"<<endl;
        cout<<"4. INFIX_EVALUATION \t";
        cout<<"9. POSTFIX_EVALUATION"<<endl;
        cout<<"5. PREFIX_EVALUATION \t";
        cout<<"10.HISTORY_NOW"<<endl;
        cout<<"\t\t0. EXIT"<<endl;

        cout<<endl;
        cout<<"Enter Choice :";
        cin>>t;
        switch(t)
        {
        case 0:
            {
                cout<<"--CLOSING PROGRAM--";
                return 0;
            }
        case 1:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two=inpostfix(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,1,one,two);
                break;
            }
        case 6:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two;
                two=postinfix(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,6,one,two);
                break;
            }
        case 2:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two;
                two=infixtoprefix(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,2,one,two);
                break;
            }
        case 7:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two;
                two=prefixtoinfix(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,7,one,two);
                break;
            }
        case 3:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two;
                two=pretopost(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,3,one,two);
                break;
            }
        case 8:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two;
                two=posttopre(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,8,one,two);
                break;
            }
        case 4:
            {
                string one;
                cout<<"enter Expression :";
                cin>>one;
                string two;
                two=infixeval(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,4,one,two);
                break;
            }
        case 9:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two;
                two=postfixEval(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,9,one,two);
                break;
            }
        case 5:
            {
                string one;
                cout<<"Enter Expression :";
                cin>>one;
                string two;
                two=prefixeval(one);
                cout<<"Result :"<<two<<endl;
                head=add(head,5,one,two);
                break;
            }
        case 10:
            {
                display(head);
                break;
            }
        default:
            {
                cout<<" INVALID CHOICE "<<endl;
            }
        }
    }
}
