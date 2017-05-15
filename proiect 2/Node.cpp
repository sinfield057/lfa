#include "Node.h"

Node::Node() {
	_value = -1;
	_final = false;
	_start = false;
}

Node::Node( int value ) {
	_value = value;
	_final = false;
	_start = false;
}

Node::~Node() {
	
}

int Node::get_value() {
	return _value;
}

void Node::add_relay( std::string key, int node ) {
	if( _relays.find( node ) != _relays.end() ) {
		_relays[ node ] = _relays[ node ] + "+" + key;
	} else {
		_relays[ node ] = key;
	}
}

void Node::reset_relay( std::string key, int node ) {
	_relays[ node ] = key;
}

std::string Node::get_relay( int node ) {
	return _relays.find( node ) != _relays.end() ? _relays[ node ] : "";
}


void Node::delete_relay( int node ) {
		_relays.erase( node );
}

std::map< int, std::string > Node::get_relays() {
	return _relays;
}

void Node::switch_final() {
	_final = !_final;
}

bool Node::is_final() {
	return _final;
}

void Node::switch_start() {
	_start = !_start;
}

bool Node::is_start() {
	return _start;
}