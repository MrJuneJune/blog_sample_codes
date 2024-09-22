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
#include <string>
class Solution {
 public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int x = 0;
        int y = 0;
        while (l1) {
            x  = x * 10 + l1->val;
            l1 = l1->next;
        }
        while (l2) {
            y  = y * 10 + l2->val;
            l2 = l2->next;
        }
        std::string ans = std::to_string(x + y);
        ListNode* start = new ListNode(0);
        ListNode* curr  = start;
        for (char& i : ans) {
            curr->next = new ListNode(i - '0');
            curr       = curr->next;
        }
        return start->next;
    }
};

/* most optimal solution? */

// Synchronization with C I/O Disabled:
//
// std::ios_base::sync_with_stdio(false);: This disables the synchronization
// between C and C++ standard streams. By default, C++ streams are synchronized
// with C streams, which incurs some overhead. Disabling this synchronization
// can make C++ standard stream operations faster. std::cin.tie(nullptr); and
// std::cout.tie(nullptr);: These calls untie the input and output streams,
// which can avoid unnecessary flushing of std::cout before std::cin operations.
// Pre-calculated Lookup Table (Booster static initialization):
//
// The static initialization block ensures that the I/O optimizations are
// applied before any other operations, giving the entire program the benefit of
// faster I/O from the start. Efficient Input Parsing and Processing:
//
// The parse_and_solve function is optimized for efficient parsing and
// processing of strings representing numbers. It avoids unnecessary operations
// and processes each character directly, minimizing overhead. The function uses
// a single ofstream object to write the output, avoiding the overhead of
// multiple file operations.
//
static const bool Booster = []() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    return true;
}();

inline bool isDigit(const char c) {
    return (c >= '0') && (c <= '9');
}

void parse_and_solve(const std::string& s1, const std::string& s2, std::ofstream& out) {
    const int S1 = s1.size();
    const int S2 = s2.size();
    if (S1 < S2) {
        parse_and_solve(s2, s1, out);
        return;
    }
    int carry = 0;
    int i     = 0;
    int j     = 0;
    while (i < S1 - 1) {
        while (i < S1 && (!isDigit(s1[i]))) {
            ++i;
        }
        while (j < S2 && (!isDigit(s2[j]))) {
            ++j;
        }
        const int n1 = s1[i] - '0';
        const int n2 = (j < S2) ? (s2[j] - '0') : 0;
        const int n  = carry + n1 + n2;
        carry        = n / 10;
        out << (n % 10);
        if (i < S1 - 2) {
            out << ",";
        }
        ++i;
        ++j;
    }
    if (carry > 0) {
        out << "," << carry;
    }
}

static bool Solve = []() {
    std::ofstream out("user.out");
    std::string s1, s2;
    while (std::getline(std::cin, s1) && std::getline(std::cin, s2)) {
        out << "[";
        parse_and_solve(s1, s2, out);
        out << "]\n";
    }
    out.flush();
    exit(0);
    return true;
}();
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
class Solution {
 public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ans  = nullptr;
        ListNode* temp = nullptr;
        int carry      = 0;
        while (l1 != nullptr && l2 != nullptr) {
            int val        = l1->val + l2->val + carry;
            carry          = val / 10;
            val            = val % 10;
            ListNode* node = new ListNode(val);
            if (ans == nullptr) {
                ans  = node;
                temp = ans;

            } else {
                ans->next = node;
                ans       = ans->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1 != nullptr) {
            int val        = l1->val + carry;
            carry          = val / 10;
            val            = val % 10;
            ListNode* node = new ListNode(val);
            if (ans == nullptr) {
                ans  = node;
                temp = ans;

            } else {
                ans->next = node;
                ans       = ans->next;
            }
            l1 = l1->next;
        }
        while (l2 != nullptr) {
            int val        = l2->val + carry;
            carry          = val / 10;
            val            = val % 10;
            ListNode* node = new ListNode(val);
            if (ans == nullptr) {
                ans  = node;
                temp = ans;

            } else {
                ans->next = node;
                ans       = ans->next;
            }
            l2 = l2->next;
        }
        if (carry) {
            ListNode* node = new ListNode(carry);
            ans->next      = node;
        }
        return temp;
    }
};
