#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>

using namespace std;

// ���ַ�ģ��
int binary_search(vector<int> nums, int target) {
    int left = 0, right = nums.size() - 1;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else if (nums[mid] > target)
            right = mid - 1;
        else if(nums[mid] == target)
            return mid;// ֱ�ӷ���
    }
    // ֱ�ӷ���
    return -1;
}

int left_bound(vector<int> nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else if (nums[mid] > target)
            right = mid - 1;
        else if (nums[mid] == target)
            right = mid - 1;   // �𷵻أ��������߽�
    }
    // ���Ҫ��� left Խ������
    if (left >= nums.size() || nums[left] != target)
        return -1;
    return left;
}


int right_bound(vector<int> nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else if (nums[mid] > target)
            right = mid - 1;
        else if (nums[mid] == target)
            left = mid + 1;// �𷵻أ������Ҳ�߽�
    }
    // ���Ҫ��� right Խ������
    if (right < 0 || nums[right] != target)
        return -1;
    return right;
}

#endif // BINARY_SEARCH_H