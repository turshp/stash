<<<<<<< HEAD
#include <cstdio>

=======
>>>>>>> f2aef8356e6059ea209c57b359af604ed93ff863
class Node {
public:
    int data;
    Node* next;
};

<<<<<<< HEAD
// remove nodes with identical data
void remove_repetition(Node* head) {
    while (head && head->next) {
        if (head->data == head->next->data) {
            // do not change the head element
            Node* tmp = head->next;
            head->next = tmp->next;
            delete tmp;
        } else {
            head = head->next;
        }
    }
}


=======
>>>>>>> f2aef8356e6059ea209c57b359af604ed93ff863
Node* merge(Node* head1, Node* head2) {
    static Node snode;

    remove_repetition(head1);
    remove_repetition(head2);

    if (head1 == NULL) {
        return head2;
    } else if (head2 == NULL) {
        return head1;
    } else if (head1 == head2) {
        return head1;
    }

    Node* head = (head1->data <= head2->data ? head1 : head2);
    Node* p = &snode;
    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            p->next = head1;
            p = p->next;
            head1 = head1->next;
        } else if (head1->data > head2->data) {
            p->next = head2;
            p = p->next;
            head2 = head2->next;
        } else {
            p->next = head1; // always take from first list
            p = p->next;
            head1 = head1->next;
            Node* tmp = head2;
            head2 = head2->next;
            delete tmp;
        }
    }

    if (head1) {
        p->next = head1;
    } else {
        p->next = head2;
    }

    return head;
}



/*
 * test
 */
Node* list_append(int data, Node* node = NULL) {
    Node* n = new Node;
    n->data = data;
    n->next = NULL;
    if (node) {
        node->next = n;
    }
    return n;
}

void test1() {
    // 1,2,5
    // 3,4
    Node* head1 = list_append(1, NULL);
    Node* tmp = head1;
    tmp = list_append(2, tmp);
    tmp = list_append(5, tmp);

    Node* head2 = list_append(3, NULL);
    tmp = head2;
    tmp = list_append(4, tmp);

    Node* head = merge(head1, head2);

    printf("test1:\n");
    for (Node* n = head; n != NULL; n = n->next) {
        printf("%d-->", n->data);
    }

    printf("\n");

}

void test2() {
    // 1,2,5
    // 1,3,4,4,4,6
    Node* head1 = list_append(1, NULL);
    Node* tmp = head1;
    tmp = list_append(2, tmp);
    tmp = list_append(5, tmp);

    Node* head2 = list_append(1, NULL);
    tmp = head2;
    tmp = list_append(3, tmp);
    tmp = list_append(4, tmp);
    tmp = list_append(4, tmp);
    tmp = list_append(4, tmp);
    tmp = list_append(6, tmp);

    Node* head = merge(head1, head2);

    printf("test2:\n");
    for (Node* n = head; n != NULL; n = n->next) {
        printf("%d-->", n->data);
    }

    printf("\n");

}

void test3() {
    // 1,2,3,5
    // 1,3,4,4,4,6
    Node* head1 = list_append(1, NULL);
    Node* tmp = head1;
    tmp = list_append(2, tmp);
    tmp = list_append(3, tmp);
    tmp = list_append(5, tmp);

    Node* head2 = list_append(1, NULL);
    tmp = head2;
    tmp = list_append(3, tmp);
    tmp = list_append(4, tmp);
    tmp = list_append(4, tmp);
    tmp = list_append(4, tmp);
    tmp = list_append(6, tmp);

    Node* head = merge(head1, head2);

    printf("test3:\n");
    for (Node* n = head; n != NULL; n = n->next) {
        printf("%d-->", n->data);
    }

    printf("\n");

}

int main() {
    test1();
    test2();
    test3();
}
