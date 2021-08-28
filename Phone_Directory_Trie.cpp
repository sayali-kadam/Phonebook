#include<bits/stdc++.h>
using namespace std;

struct node{
    bool we;
    node* child[26];
};
node* getNode(){
    node* root = new node();
    if(root){
        root->we = false;
        for(int i=0; i<26; i++)
            root->child[i] = NULL;
    }
    return root;
}
void insert(string w, node* root){
    node* temp = root;
    for(int i=0; i<w.length(); i++){
        int idx = w[i]-'a';
        if(!temp->child[idx])
            temp->child[idx] = getNode();
        temp = temp->child[idx];
    }
    temp->we = true;
}
void dfs(node* temp, vector<string>& res, string w){
    if(temp->we)
        res.push_back(w);
    for(int i=0; i<26; i++){
        if(temp->child[i])
            dfs(temp->child[i], res, w+(char)('a'+i));
    }
}
vector<vector<string> > search(node* root, string w){
    vector<vector<string> > ans;
    node* temp = root;
    string pre;
    for(int i=0; i<w.length(); i++){
        pre += w[i];
        int idx = w[i]-'a';
        if(!temp->child[idx])
            break;
        temp = temp->child[idx];
        vector<string> res;
        dfs(temp, res, pre);
        ans.push_back(res);
    }
    vector<string> zero = {"0"};
    while(ans.size()<w.length())
        ans.push_back(zero);
    return ans;
}
class Solution{
public:
    vector<vector<string> > displayContacts(int n, string contact[], string s)
    {
        // code here
        node* root = getNode();
        for(int i=0; i<n; i++)
            insert(contact[i], root);
        return search(root, s);
    }
};
//Driver code
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string contact[n], s;
        for(int i=0; i<n; i++)
            cin>>contact[i];
        cin>>s;

        Solution ob;
        vector<vector<string> > ans = ob.displayContacts(n, contact, s);
        for(int i=0; i<s.size(); i++){
            for(auto u:ans[i])
                cout<<u<<" ";
            cout<<"\n";
        }
    }
}