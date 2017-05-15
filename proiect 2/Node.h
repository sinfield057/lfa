#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <algorithm>
#include <string>


class Node {
private:
	// Node value
	int _value;
	// Final node
	bool _final;
	// Start state
	bool _start;
	// One key can relay to one node
	std::map< int, std::string > _relays;

public:
	Node();
	Node( int value );
	~Node();

	// Get node value
	int get_value();
	
	// Get list of relays for "key"
	std::map< int, std::string > get_relays();
	
	// Add a new relay to "node" through "key"
	void add_relay( std::string key, int node );
	
	// Delete relay
	void delete_relay( int node );

	// Switch the state of final/regular node
	void switch_final();

	// Switch the state of start/regular node
	void switch_start();

	// Get final state
	bool is_final();

	// Get start state
	bool is_start();
};

#endif