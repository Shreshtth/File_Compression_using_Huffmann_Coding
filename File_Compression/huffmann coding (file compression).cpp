#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
typedef long long int li;
typedef long double ld;
using namespace std;

class TreeNode
{
public:
    char c;
    int val;
    TreeNode *left, *right;

    TreeNode(char c, int val, TreeNode *left, TreeNode *right)
    {
        this->c = c;
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

struct comparatorFunc
{
    bool operator()(TreeNode *n1, TreeNode *n2)
    {
        return n1->val > n2->val;
    }
};

void encodeHuffMann(TreeNode *root, string str, map<char, string> &HuffMannCodes)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        HuffMannCodes[root->c] = str;
    }

    encodeHuffMann(root->left, str + '0', HuffMannCodes);
    encodeHuffMann(root->right, str + '1', HuffMannCodes);
}

string decodeString(TreeNode *root, string encodedString)
{
    string ans = "";
    TreeNode *curr = root;
    for (int i = 0; i < encodedString.size(); i++)
    {
        if (encodedString[i] == '0')
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
        if (curr->left == NULL && curr->right == NULL)
        {
            ans += curr->c;
            curr = root;
        }
    }
    return ans;
}

void makingHuffMannCode(string input)
{
    map<char, int> frequencies;
    for (auto i : input)
    {
        frequencies[i]++;
    }

    priority_queue<TreeNode *, vector<TreeNode *>, comparatorFunc> HuffmannTree;

    for (auto x : frequencies)
    {
        TreeNode *newNode = new TreeNode(x.first, x.second, NULL, NULL);
        HuffmannTree.push(newNode);
    }

    while (HuffmannTree.size() != 1)
    {
        TreeNode *left = HuffmannTree.top();
        HuffmannTree.pop();
        TreeNode *right = HuffmannTree.top();
        HuffmannTree.pop();

        TreeNode *newNode = new TreeNode('$', left->val + right->val, left, right);
        HuffmannTree.push(newNode);
    }

    TreeNode *root = HuffmannTree.top();

    map<char, string> HuffMannCodes;
    encodeHuffMann(root, "", HuffMannCodes);

    // printing huffmann codes of each character
    for (auto i : HuffMannCodes)
    {
        cout << i.first << " ->";
        for (auto j : i.second)
        {
            cout << j;
        }
        cout << endl;
    }
    // to get our encoded string
    string encodedString = "";
    for (auto c : input)
    {
        encodedString += HuffMannCodes[c];
    }

    // we have obtained our encoded string, no to decode this string back to the original string, we will make a decode function
    string decodedString = decodeString(root, encodedString);
    cout << endl;
    cout << "The Original String -->>  :" << endl;
    cout << input << endl;
    cout << endl;
    cout << "The Encoded String -->>  :" << endl;
    cout << encodedString << endl;
    cout << endl;
    cout << "The Decoded Strring -->> : " << endl;
    cout << decodedString << endl;

    // to find compression rate
    int lengthOfOriginalString = 8 * (input.length()); // chars take 8 bytes
    int lengthOfReducedString = ceil(encodedString.length() / 8);
    double compression = (double)lengthOfReducedString / lengthOfOriginalString;
    cout << endl;
    cout << "The String has been compressed upto " << compression * 100 << "% of the original string" << endl;
}

int main()
{
   
   
    ifstream in;
    string s;
    in.open("sample.txt");
    while(in.eof()==0){
        string temp;
        getline(in,temp);
        s.append(temp);
    	}
    
   makingHuffMannCode(s);
   return 0;
}