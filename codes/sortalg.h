#ifndef SORTALG_H
#define SORTALG_H

#include <vector>
#include <iostream>
#include <algorithm>

using namespace  std;

//ð������
void bibleSort(vector<int>& arr, int n)
{
    for(int i=0; i<n; i++)
    {
        bool bSorted = false; //�Ż�����ǰһ��û�н��н���ʱ��˵�������Ѿ�����û�б�Ҫ�ٽ�����һ�ֵ�ѭ����
        for(int j = 1; j<n-i; j++)  //һ�ΰ�һ��Ԫ�طŵ�����
        {
            if(arr[j] < arr[j-1])
            {
                bSorted = true;
                swap(arr[j], arr[j-1]);
            }
        }
        if(!bSorted) break;
    }
}

// ��������
void quickSort(vector<int>& arr, int l, int r)
{
    if(l >= r) return;

    int temp = arr[l];
    int left = l;
    int right = r;

    // ��lΪ��׼����lС�ķ���ߣ���l��ķ��ұ�
    while(l < r)
    {
        while(l<r && arr[r]>=temp) r--;  //ע��r�ȼ�
        while(l<r && arr[l]<=temp) l++;
        swap(arr[l], arr[r]); //С�ķ���ߣ���ķ��ұ�
    }
    swap(arr[left], arr[r]); //�ѻ�׼�ƶ����м䣬����ѭ����arr[r]һ���ǱȻ�׼С�ģ���˿��Խ���

    quickSort(arr, left, r-1);  //����ұ�
    quickSort(arr, r+1, right);
}

// ֱ�Ӳ�������
void insertSort(vector<int>& arr, int n)
{
    for(int i=1; i<n; i++)
    {
        int pos = i;
        int val = arr[i];
        while(pos>0 && arr[pos-1] > val)
        {
            arr[pos] = arr[pos-1];
            pos--;
        }
        arr[pos] = val;
    }
}

// ϣ������
void shellSort(vector<int>& arr, int n)
{
    int d = n/2; //����d��ÿ�μ��룬�𽥼��ٵ�1�����һ��һ��ҪΪ1��
    for(; d>=1; d/=2)
    {
        for(int i=d; i<n; i++)
        {
            int pos = i;
            int val = arr[pos];
            while(pos-d>=0 && arr[pos-d] > val)
            {
                arr[pos] = arr[pos-d];
                pos -= d;
            }
            arr[pos] = val;
        }
    }
}

// �鲢����
void mergeSort(vector<int>& arr, int l, int r)
{
    if(l == r) return; //ֻ��һ���� ��������

    int mid = l + (r-l)/2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid+1, r);

    vector<int> temp(r-l+1, 0);

    int ptrL = l, ptrR = mid+1;
    int ptrRes = 0;
    while(ptrL <= mid && ptrR <= r)
    {
        if(arr[ptrL] <= arr[ptrR])
            temp[ptrRes++] = arr[ptrL++];
        else
            temp[ptrRes++] = arr[ptrR++];
    }
    while(ptrL <= mid)
        temp[ptrRes++] = arr[ptrL++];
    while(ptrR <= r)
        temp[ptrRes++] = arr[ptrR++];

    for(int i=l,j=0; i<=r; i++,j++) //���źõĶθ��ƻ�arr
        arr[i] = temp[j];
}

// ѡ������
void selectSort(vector<int>& arr)
{
    for(int i=0; i<arr.size(); i++)
    {
        int minIdx = i;
        for(int j=i+1; j<arr.size(); j++)
        {
            if(arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}


// ������
//�����ѣ���startλ��Ϊ���ڵ㣬������end
void adjustHeap(vector<int>& arr, int start, int end)
{
    int root = start;
    int child = 2*start + 1; //������0��ʼ������������1��ʼ����Ϊ2*start
    while(child <= end)
    {
        if(child < end && arr[child] < arr[child+1]) //�����ҽ�������Ǹ�
            child++;  //�л����ҽڵ�

        if(arr[root] >= arr[child]) return; //���ڵ�������ӽڵ��˵��������λ
        else
        {
            swap(arr[root], arr[child]);
            root = child;
            child = 2*root + 1;
        }
    }
}

// ��С���󣬴����
void heapSort(vector<int>& arr, int n)
{
    for(int i=n/2; i>=0; i--)
    {
        adjustHeap(arr, i, n);  //ɸѡ�㷨����������ķ�Ҷ�ӽ������ڵ����������ϸ���С���³�
    }

    for(int i=0; i<=n; i++) //ע�⣺�������n����ֵ����ֻ�ҳ�topK�����/��С��
    {
        swap(arr[0], arr[n-i]);   //�Ѵ���Ѹ��ڵ�����һ���������������ֵ�Ƶ������
        adjustHeap(arr, 0, n-i-1);  //�������ڵ㣬ע�⣺���ź�Ԫ�ز���������
    }
}



// Ͱ����
void bucketSort(vector<int>& arr)
{
    int minVal = INT_MAX, maxVal = INT_MIN;
    for(int i: arr)
    {
        minVal = min(minVal, i);
        maxVal = max(maxVal, i);
    }

    int bucketNum = (maxVal-minVal) / arr.size() + 1;  //ÿ��Ͱ�ķ�Χ��СΪarr.size
    vector<vector<int>> buckets(bucketNum, vector<int>());
    for(int i: arr)
    {
        int idx = (i-minVal) / arr.size();
        buckets[idx].push_back(i);
    }

    for(auto &bucket: buckets)    // ע������������
        sort(bucket.begin(), bucket.end());

    int idx = 0;
    for(auto bucket: buckets)
    {
        for(int i: bucket)
        {
            arr[idx++] = i;
        }
    }
}

// ��������
void countSort(vector<int>& arr)
{
    int minVal = INT_MAX, maxVal = INT_MIN;
    for(int i: arr)
    {
        minVal = min(minVal, i);
        maxVal = max(maxVal, i);
    }
    vector<int> temp(maxVal-minVal+1, 0);
    for(int i: arr)
        temp[i-minVal]++;

    int i = 0, j = 0;
    for(int j=0; j<temp.size(); j++)
    {
        while(temp[j]--)
            arr[i++] = j + minVal;
    }
}

// ��������
void radixSort(vector<int>& arr)
{
    int idx = 1, maxVal = INT_MIN;
    for(int i: arr)
    {
        maxVal = max(maxVal, i);
    }

    vector<vector<int>> radix(10, vector<int>());  // 0~9
    while(idx < maxVal)
    {
        for(int i: arr)
        {
            int rest = i / idx;
            radix[rest % 10].push_back(i);   // ����ÿһλ���ŵ�0~9��Ͱ�У�������Ͱ������
        }

        // ÿһλ�������������ݺϲ�
        int j = 0;
        for(auto vec: radix)
        {
            for(int i: vec)
                arr[j++] = i;
        }
        radix.clear();
        idx *= 10;
    }
}


void sortTest()
{
    vector<int> temp;
//    vector<int> arr{9,8,7,6,5,4,3,2,1,0};
    vector<int> arr{1,3,5,7,2,6,4,8,9,2,8,7,6,0,3,5,9,4,1,0};
//    vector<int> arr{63,157,189,51,101,47,141,121,157,156,194,117,98,139,67,133,181,13,28,109};

//    bibleSort(arr, arr.size());
//    quickSort(arr, 0, arr.size()-1);
//    insertSort(arr, arr.size());
//    shellSort(arr, arr.size());
//    mergeSort(arr, 0, arr.size()-1);
//    selectSort(arr);
//    heapSort(arr, arr.size()-1);
//    bucketSort(arr);
//    countSort(arr);
    radixSort(arr);

    for(auto i: arr)
       cout<<i<<",";
}


// ///////////////////////////////////////
// ��������  k-th Element ����
//int quickSort(vector<int>& nums, int l, int r, int k)
//{
//    if(l >= r)
//    {
//        if(r == nums.size()-k)
//            return nums[r];
//        else
//            return -1;
//    }

//    int left = l;
//    int right = r;
//    int val = nums[l];
//    while(l < r)
//    {
//        while(l<r && nums[r] >= val) r--;
//        while(l<r && nums[l] <= val) l++;
//        swap(nums[l], nums[r]);
//    }
//    swap(nums[left], nums[r]);
//    if(r == nums.size()-k)
//        return val;
//    else if(r > nums.size()-k)
//        return quickSort(nums, left, r-1, k);
//    else if(r < nums.size()-k)
//        return quickSort(nums, r+1, right, k);
//}

//int findKthLargest(vector<int>& nums, int k) {
//    return quickSort(nums, 0, nums.size()-1, k);
//}

int helper(vector<int>& nums, int l, int r)
{
    int left = l;
    int right = r;
    int val = nums[l];
    while(l < r)
    {
        while(l<r && nums[r] >= val) r--;
        while(l<r && nums[l] <= val) l++;
        swap(nums[l], nums[r]);
    }
    swap(nums[left], nums[r]);
    return r;
}

int findKthLargest(vector<int>& nums, int k) {
    int l = 0, r = nums.size()-1;
    while(l < r)
    {
        int res = helper(nums, l, r);
        if(res == nums.size()-k) return nums[res];
        else if(res > nums.size()-k)
            r = res - 1;
        else
            l = res + 1;
    }
    return nums[l];
}




#endif // SORTALG_H
