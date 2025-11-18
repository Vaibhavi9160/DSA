#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node *next;
} Node;

// Helper: create a new node
Node* new_node(int v) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) { perror("malloc"); exit(1); }
	p->val = v;
	p->next = NULL;
	return p;
}

// Reverse the sublist from position m to n (1-based). Return new head.
Node* reversePlaylistSegment(Node* head, int m, int n) {
	if (!head || m == n) return head;

	Node dummy;
	dummy.next = head;
	Node* prev = &dummy;

	// Move prev to the node before position m
	for (int i = 1; i < m; ++i) {
		if (!prev->next) return head; //m out of range
		prev = prev->next;
	}

	Node* const sublist_head_prev = prev;
	Node* sublist_iter = prev->next; // will become the tail of reversed sublist

	// Reverse nodes between m and n
	Node* curr = sublist_iter;
	Node* prev_rev = NULL;
	for (int i = m; i <= n; ++i) {
		if (!curr) break; // n out of range
		Node* next = curr->next;
		curr->next = prev_rev;
		prev_rev = curr;
		curr = next;
	}

	// Connect reversed sublist back into list
	sublist_head_prev->next = prev_rev;      // prev_rev is new head of reversed segment
	sublist_iter->next = curr;               // sublist_iter is original m-th node, now tail

	return dummy.next;
}

// Utility: print list
void print_list(Node* head) {
	Node* p = head;
	while (p) {
		printf("%d", p->val);
		if (p->next) printf(" -> ");
		p = p->next;
	}
	printf("\n");
}

// Free list
void free_list(Node* head) {
	Node* p = head;
	while (p) {
		Node* nxt = p->next;
		free(p);
		p = nxt;
	}
}

int main(void) {
	// Build sample list: 101 -> 102 -> 103 -> 104 -> 105 -> 106 -> 107
	int vals[] = {101,102,103,104,105,106,107};
	size_t nvals = sizeof(vals)/sizeof(vals[0]);

	Node* head = NULL;
	Node* tail = NULL;
	for (size_t i = 0; i < nvals; ++i) {
		Node* node = new_node(vals[i]);
		if (!head) head = tail = node;
		else { tail->next = node; tail = node; }
	}

	printf("Sample input playlist:\n");
	print_list(head);

	int m = 2, nn = 5;
	Node* modified = reversePlaylistSegment(head, m, nn);

	printf("Modified playlist (reverse positions %d..%d):\n", m, nn);
	print_list(modified);

	free_list(modified);
	return 0;
}
