#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <algorithm>


class Node {
public:
	struct X {
		// Entry values
		char _top_stack;
		// Remove values
		std::vector< char > _stack_add;
		// Node relay
		int _node_relay;
	};
private:
	// Node value
	int _value;
	// Final node
	bool _final;

public:
	// Relay list
	std::map< char, X > _relays;
	Node();
	Node( int value );
	~Node();

	// Get node value
	int get_value();

	// Get list of relays for "key"
	std::map< char, X > get_relays();

	// Add a new relay to "node" through "key"
	void add_relay( char key, int node, char stack_top, std::vector< char > stack_add );

	// Switch the state of final/regular node
	void switch_final();

	// Get state
	bool is_final();
};

#endif