#ifndef ALGORITHMMOBAN_H
#define ALGORITHMMOBAN_H

#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;

int binary_search(vector<int>& nums, int target)
{
    int left = 0, right = nums.size() - 1;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else if(nums[mid] == target)
        {
            // ֱ�ӷ���
            return mid;
        }
    }
    // ֱ�ӷ���
    return -1;
}

int left_bound(vector<int>&  nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else if (nums[mid] == target)
        {
            // �𷵻أ��������߽�
            right = mid - 1;
        }
    }
    // ���Ҫ��� left Խ������
    if (left >= nums.size() || nums[left] != target)
        return -1;
    return left;
}


int right_bound(vector<int>&  nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else if (nums[mid] == target)
        {
            // �𷵻أ������Ҳ�߽�
            left = mid + 1;
        }
    }
    // ���Ҫ��� right Խ������
    if (right < 0 || nums[right] != target)
        return -1;
    return right;
}


void kmp(int* next, const string& s)
{
    next[0] = -1;
    int j = -1;
    for(int i = 1; i < s.size(); i++)
    {
        while (j >= 0 && s[i] != s[j + 1])
        {
            j = next[j];
        }
        if (s[i] == s[j + 1])
        {
            j++;
        }
        next[i] = j;
    }
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//ǰ������������ң�
void traversal(TreeNode* cur, vector<int>& vec) {
    if (cur == NULL) return;

    vec.push_back(cur->val);    // �� ��ͬʱҲ�Ǵ���ڵ��߼��ĵط�
    traversal(cur->left, vec);  // ��
    traversal(cur->right, vec); // ��
}

//������ǰ�����
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty())
    {
        TreeNode* node = st.top();
        if (node != NULL)
        {
            st.pop();
            if (node->right) st.push(node->right);  // ��
            if (node->left) st.push(node->left);    // ��
            st.push(node);                          // ��
            st.push(nullptr);
        }
        else
        {
            st.pop();
            node = st.top();
            st.pop();
            result.push_back(node->val);            // �ڵ㴦���߼�
        }
    }
    return result;
}

//�������������
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result; // ������������Ԫ��
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        if (node != NULL) {
            st.pop();
            if (node->right) st.push(node->right);  // ��
            st.push(node);                          // ��
            st.push(NULL);
            if (node->left) st.push(node->left);    // ��
        } else {
            st.pop();
            node = st.top();
            st.pop();
            result.push_back(node->val);            // �ڵ㴦���߼�
        }
    }
    return result;
}

//�������������
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        if (node != NULL) {
            st.pop();
            st.push(node);                          // ��
            st.push(NULL);
            if (node->right) st.push(node->right);  // ��
            if (node->left) st.push(node->left);    // ��

        } else {
            st.pop();
            node = st.top();
            st.pop();
            result.push_back(node->val);            // �ڵ㴦���߼�
        }
    }
    return result;
}

//�������
vector<vector<int>> levelOrder(TreeNode* root) {
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<vector<int>> result;
    while (!que.empty()) {
        int size = que.size();
        vector<int> vec;
        for (int i = 0; i < size; i++) {// ����һ��Ҫʹ�ù̶���Сsize����Ҫʹ��que.size()
            TreeNode* node = que.front();
            que.pop();
            vec.push_back(node->val);   // �ڵ㴦����߼�
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        result.push_back(vec);
    }
    return result;
}


//����
//void backtracking(����) {
//    if (��ֹ����) {
//        ��Ž��;
//        return;
//    }

//    for (ѡ�񣺱��㼯����Ԫ�أ����нڵ㺢�ӵ��������Ǽ��ϵĴ�С��) {
//        ����ڵ�;
//        backtracking(·����ѡ���б�); // �ݹ�
//        ���ݣ�����������
//    }
//}



// ���������㷨���
//void slidingWindow(string s, string t)
//{
//    unordered_map<char, int> need, window;
//    for (char c : t) need[c]++;

//    int left = 0, right = 0;
//    int valid = 0;
//    while (right < s.size()) {
//        // c �ǽ����봰�ڵ��ַ�
//        char c = s[right];
//        // ���ƴ���
//        right++;
//        // ���д��������ݵ�һϵ�и���
//        ...


//        // �ж���ര���Ƿ�Ҫ����
//        while (window needs shrink) {
//            // d �ǽ��Ƴ����ڵ��ַ�
//            char d = s[left];
//            // ���ƴ���
//            left++;
//            // ���д��������ݵ�һϵ�и���
//            ...
//        }
//    }
//}

#endif // ALGORITHMMOBAN_H
