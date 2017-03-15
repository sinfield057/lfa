#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <algorithm>


class Node {
private:
	// Node value
	int _value;
	// Final node
	bool _final;
	// Lambda closures
	std::vector< int > _closures;
	// One key can relay to multiple nodes
	std::map< char, std::vector< int > > _relays;

public:
	Node();
	Node( int value );
	~Node();

	// Get node value
	int get_value();
	
	// Get list of relays for "key"
	std::map< char, std::vector< int > > get_relays();
	
	// Add a new relay to "node" through "key"
	void add_relay( char key, int node );
	
	// Add closure
	void add_closure( int node );
	
	// Get closure list
	std::vector< int > get_closures(); 

	// Switch the state of final/regular node
	void switch_final();

	// Get state
	bool is_final();
};

#endif