#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node *slow = head, *fast = head;

    while(fast)
    {
        if(fast->next && fast->next->next)
        {
            fast = fast->next->next;
        }
        else 
        {
            return 0;
        }

        slow = slow->next;

        if(fast == slow) return 1;
    }

    return 0;
}