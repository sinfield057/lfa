#include "Node.h"

Node::Node() {
	_value = -1;
	_final = false;
}

Node::Node( int value ) {
	_value = value;
	_final = false;
}

Node::~Node() {
	
}

int Node::get_value() {
	return _value;
}

void Node::add_relay( char key, int node, char stack_top, std::vector< char > stack_add ) {
	Node::X x;
	x._top_stack = stack_top;
	x._stack_add = stack_add;
	x._node_relay = node;

	if ( _relays.find( key ) != _relays.end() ) {
		_relays[ key ] = x;
	}
}

std::map< char, Node::X > Node::get_relays() {
	return _relays;
}

void Node::switch_final() {
	_final = !_final;
}

bool Node::is_final() {
	return _final;
}