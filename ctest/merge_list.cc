

class Node {
public:
    int data;
    Node* next;
};


Node* merge(Node* head1, Node* head2) {
    if (head1 == NULL) {
        return head2;
    } else if (head2 == NULL) {
        return head1;
    } else if (head1 == head2) {
        return head1;
    }

    Node* head = (head1->data <= head2->data ? head1 : head2)
    Node* p = head;
    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            head1 = head1->next;
            p->next = head1;
        } else if (head1->data > head2->data) {
            head2 = head2->next;
            p->next = head2;
        } else {
            p->next = head1; // always from first list
            head1 = head1.next;
            Node* tmp = head2;
            head2 = head->next;
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
