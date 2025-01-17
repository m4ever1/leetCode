/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include "iostream"
#include <stdarg.h>
#include <random>
#include <list>
#include <inttypes.h>
#include <stdio.h>
#include <boost/multiprecision/cpp_int.hpp>

typedef unsigned __int128 uint128_t;

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)

static int print_u128_u(uint128_t u128)
{
    int rc;
    if (u128 > UINT64_MAX)
    {
        uint128_t leading  = u128 / P10_UINT64;
        uint64_t  trailing = u128 % P10_UINT64;
        rc = print_u128_u(leading);
        rc += printf("%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }
    else
    {
        uint64_t u64 = u128;
        rc = printf("%" PRIu64, u64);
    }
    return rc;
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    template<typename... Args>
    ListNode(int val, Args... args) : val(val), next(new ListNode(args...))
    {
        // this->next = new ListNode(args...);
    }
};

class ListNodeWrapper
{
private:
    ListNode* root;
    ListNode* curr;
    int size_p = 1;
public:
    ListNodeWrapper() : root(new ListNode()), curr(root) {}
    ListNodeWrapper(ListNode* root) : root(root), curr(root) {}
    ListNodeWrapper(int val) : root(new ListNode(val)), curr(root) {}
    ListNode peek() const
    {
        return curr->val;
    }
    bool step()
    {
        if(curr->next)
        {
            curr = curr->next;
            return true;
        }
        return false;
    }
    void push(ListNode node)
    {
        curr->next = new ListNode(node);
        size_p++;
    }
    bool check() const
    {
        return curr;
    }
    ListNode* getRoot() const
    {
        return root;
    }
    int size() const
    {
        return size_p;
    }
    std::list<int> getList() const
    {
        ListNode* localCurr = this->root;
        std::list<int> lst;
        while (true)
        {
            if (!localCurr)
            {
                break;
            }
            
            lst.emplace_back(localCurr->val);
            localCurr = localCurr->next;
        }
        return lst;
    }
    std::list<int> reverse() const
    {
        
        std::list<int> reversed = getList();

        reversed.reverse();
        return reversed;
    }
    boost::multiprecision::cpp_int computeInt() const
    {

        std::list<int>lst = getList();
        boost::multiprecision::cpp_int result = 0;
        for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
        {
            // boost::multiprecision::cpp_int 
            boost::multiprecision::cpp_int powerOf10 = 1;
            int exponent = std::distance(lst.begin(), it);
            while (exponent != 0)
            {
                powerOf10 *= 10;
                --exponent;
            }
            powerOf10 *= (*it);
            result += powerOf10;
        }

        return result;
    }
};


void printList(ListNode* curr)
{
    while (curr != nullptr)
    {
        std::cout << curr->val << std::endl;
        curr = curr->next;
    }
    
}

void printList(std::list<int> lst)
{
    std::cout << "REVERSED = " << std::endl;
    for(auto& i : lst)
    {
        std::cout << i << std::endl;
    }
}

class Solution {
public:


    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode* currL1 = l1;
        ListNode* currL2 = l2;

        ListNode* solRoot = new ListNode();
        ListNode* currSol = solRoot;

        bool carry = false;
        while (true)
        {
            int val1 = 0;
            int val2 = 0;
            if (currL1 != nullptr)
            {
                val1 = currL1->val;
                currL1 = currL1->next;
            }
            if (currL2 != nullptr)
            {
                val2 = currL2->val;
                currL2 = currL2->next;
            }
            int sum = val1 + val2 + (int) carry; 
            if(sum < 10)
            {
                currSol->val = sum;
                carry = false;
            }
            else
            {
                currSol->val = sum - 10;
                carry = true;
            }
            if (!currL1 && !currL2)
            {
                break;
            }
            
            currSol->next = new ListNode();
            currSol = currSol->next;
        }
        if(carry)
        {
            currSol->next = new ListNode(1);
        }
        return solRoot;
    }
};

class Test
{
private:

    Solution& sol;
public:
    Test(Solution& sol) : sol(sol) {}
    
    ListNodeWrapper generateList() const
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        
        std::uniform_int_distribution<std::mt19937::result_type> dist9(1,9);
        std::uniform_int_distribution<std::mt19937::result_type> dist100(1,100);

        int numInts = dist100(rng);
        ListNodeWrapper wrapper = ListNodeWrapper(dist9(rng));
        
        for (size_t i = 0; i < numInts - 1; i++)
        {
            ListNode node(dist9(rng));
            wrapper.push(node);
            wrapper.step();
        }
        return wrapper;
    }

    bool solve(ListNodeWrapper tList1, ListNodeWrapper tList2) const
    {

        boost::multiprecision::cpp_int int1 = tList1.computeInt();

        boost::multiprecision::cpp_int int2 = tList2.computeInt();

        boost::multiprecision::cpp_int aritResult = int1 + int2;



        ListNode* algoResultLst = sol.addTwoNumbers(tList1.getRoot(), tList2.getRoot());

        //Wrap result
        ListNodeWrapper algoResultWrapped = ListNodeWrapper(algoResultLst)
        ;
        boost::multiprecision::cpp_int algoResult = algoResultWrapped.computeInt();

        if(algoResult != aritResult)
        {
            std::cout << "MISMATCH:" << std::endl;
            std::cout << "Arithmetic result = " << std::endl;
            std::cout << aritResult << std::endl;
            
            std::cout << "Algo. result = " << std::endl;
            std::cout << algoResult << std::endl;
            return false;
        }

        return true;
    }

    void run(int nTimes) const
    {
        for (size_t i = 0; i < nTimes; i++)
        {
            ListNodeWrapper tList1 = generateList();
            ListNodeWrapper tList2 = generateList();
            solve(tList1, tList2);
        }
    }
};

int main(int argc, const char** argv) {
    Solution sol;

    Test testObj(sol);
    testObj.run(10000000);


    return 0;
}

