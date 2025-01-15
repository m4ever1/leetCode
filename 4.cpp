#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef vector<int>::iterator iter;

inline bool isOdd(const size_t& size)
{
    return size%2;
}

bool getMedianIndex(const size_t& size, int& idx)
{
    if (size <= 1)
    {
        idx = 0;
        return true;
    }
    
    idx = size/2 - 1; // 2/2 
    return isOdd(size);
}

float getAverage(const float& lhs, const float& rhs)
{
    return (lhs+rhs)/2;
}

int getMedianFloor(const vector<int>& vec, int& idx)
{
    if(getMedianIndex(vec.size(), idx))
    {
        return vec[idx];
    }
    
    return ((vec[idx] + vec[idx + 1])/2);
}

class VectorState
{
private:
    vector<int>& vec; // x is always smaller than or equals to y in median

    int cutSide(int& side, const int& toCut)
    {
        side = side - toCut;
        if (side < 0)
        {
            side = 0;
        }
        return side;
    }

    inline int addSide(int& side, const int& toAdd)
    {
        side += toAdd;
    }


public:
    int medianFloor = 0;
    int lSide = 0;
    int rSide = 0;
    int medianIndex = 0;
    VectorState(vector<int>& vecIn): vec(vecIn)
    {
        medianFloor = getMedianFloor(vec, medianIndex);
        lSide = isOdd(vec.size()) ? vec.size()/2 : vec.size()/2 -1;
        rSide = lSide;
    }

    VectorState(VectorState&& other) : vec(other.vec)
    {
        medianFloor = other.medianFloor;
        lSide = other.lSide;
        rSide = other.rSide;
        medianIndex = other.medianIndex;
        vec = move(other.vec);
        other.medianFloor = 0;
        other.lSide = 0;
        other.rSide = 0;
        other.medianIndex = 0;
    }

    int searchLeft(const int& value, const int& startIndex = 0, const int& endIndex = -1)
    {
        vector<int>::const_iterator beginIt = vec.begin() + startIndex;
        vector<int>::const_iterator endIt = endIndex == -1 ? vec.end() : vec.begin() + endIndex;

        return distance(beginIt, lower_bound(beginIt, endIt, value));
    }

    int searchRight(const int& value, const int& startIndex = 0, const int& endIndex = -1)
    {
        vector<int>::const_iterator beginIt = vec.begin() + startIndex;
        vector<int>::const_iterator endIt = endIndex == -1 ? vec.end() : vec.begin() + endIndex;

        return distance(lower_bound(beginIt, endIt, value), endIt);
    }

    int cutLeft(const int& toCut)
    {
        return cutSide(lSide, toCut);
    }
    int cutRight(const int& toCut)
    {
        return cutSide(rSide, toCut);
    }

    int addLeft(const int& toAdd)
    {
        return addSide(lSide, toAdd);
    }
    int addRight(const int& toAdd)
    {
        return addSide(rSide, toAdd);
    }

};

class State
{
private:
    VectorState leftVec;
    VectorState rightVec;
public:
    int mergedSize = 0;
    bool mergedOdd = false;
    int mergedSides = 0;

    State(vector<int>& n1, vector<int>& n2): leftVec(n1.size() <= n2.size() ? n1 : n2), 
                                             rightVec(n1.size() > n2.size() ? n2 : n1)
    {
        mergedSize = n1.size() + n2.size();
        mergedOdd = isOdd(mergedSize);
        mergedSides = mergedOdd ? mergedSize/2 : mergedSides/2 - 1;

    }
};

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int dummy;

        State state(nums1, nums2);
        


        vector<int>& x = nums1;

        vector<int>& y = nums2;
        
        return 0;
    }
};

int main()
{
    Solution sol;
    vector<int> x = {3,7,16,17};
    vector<int> y = {2,5,6,9,12,15};
    sol.findMedianSortedArrays(x, y);
}