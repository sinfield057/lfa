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

void Node::add_relay( char key, int node ) {
	if ( std::find( _relays[ key ].begin(), _relays[ key ].end(), node ) == _relays[ key ].end() ) {
		_relays[ key ].push_back( node );
	}
}

std::map< char, std::vector< int > > Node::get_relays() {
	return _relays;
}

void Node::add_closure( int node ) {
	if ( std::find( _closures.begin(), _closures.end(), node ) == _closures.end() ) {
		_closures.push_back( node );
	}
}

std::vector< int > Node::get_closures() {
	return _closures;
}

void Node::switch_final() {
	_final = !_final;
}

bool Node::is_final() {
	return _final;
}