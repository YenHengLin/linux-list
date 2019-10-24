#include "common.h"

static void list_mergesort(struct list_head *head)
{
    struct list_head list_left, list_right;
    struct listitem *iteml = NULL, *itemr = NULL, *is = NULL;
    struct list_head *halfp;

    if (list_empty(head) || list_is_singular(head))
        return;
    INIT_LIST_HEAD(&list_left);
    INIT_LIST_HEAD(&list_right);
    /* split half*/
    struct list_head *safen = NULL, *safep = NULL;
    struct list_head *next = head->next;
    struct list_head *prev = head->prev;
    bool visit_all = false;
    for (safen = next->next, safep = prev->prev; next != prev;
         next = safen, prev = safep, safen = safen->next, safep = safep->prev) {
        list_move_tail(next, &list_left);
        list_move_tail(prev, &list_right);
        if (next->next == prev) {
            visit_all = true;
        }
    }
    if (!visit_all)
        list_move_tail(prev, &list_right);
    list_mergesort(&list_left);
    list_mergesort(&list_right);
    /* merge*/
    struct list_head *left_next, *right_next;
    struct list_head *safel = NULL, *safer = NULL;
    left_next = list_left.next;
    right_next = list_right.next;
    safel = left_next->next;
    safer = right_next->next;
    while (left_next != &list_left && right_next != &list_right) {
        iteml = list_entry(left_next, struct listitem, list);
        itemr = list_entry(right_next, struct listitem, list);
        if (iteml->i <= itemr->i) {
            list_move_tail(&iteml->list, head);
            left_next = safel;
            safel = safel->next;
        } else {
            list_move_tail(&itemr->list, head);
            right_next = safer;
            safer = safer->next;
        }
    }
    list_splice_tail(&list_left, head);
    list_splice_tail(&list_right, head);
}