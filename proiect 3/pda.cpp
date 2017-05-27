#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <map>
#include <vector>
#include <stack>

std::stack< char > pda_stack;

struct X {
	// Entry values
	char _top_stack;
	// Remove values
	std::vector< char > _stack_add;
	// Node relay
	int _node_relay;
};

class Node {

private:
	// Node value
	int _value;
	// Final node
	bool _final;
	// Relay list
	std::map< char, X > _relays;

public:
	Node() {
		_value = -1;
		_final = false;
	};

	Node( int value ){
		_value = value;
		_final = false;
	};
	
	~Node() {

	};

	// Get node value
	int get_value(){
		return _value;
	};

	// Get list of relays for "key"
	std::map< char, X > get_relays(){
		return _relays;
	};

	// Add a new relay to "node" through "key"
	void add_relay( char key, int node, char stack_top, std::vector< char > stack_add ){
		X x;
		x._top_stack = stack_top;
		x._stack_add = stack_add;
		x._node_relay = node;
		
		_relays[ key ] = x;
	};

	// Switch the state of final/regular node
	void switch_final(){
		_final = !_final;
	};

	// Get state
	bool is_final(){
		return _final;
	};
};



#define LAMBDA '*'
#define Z0 '$'

bool check_word( int current_value, std::map< int, Node > node_list, std::string input, int input_char ) {
	
	Node current_node = node_list[ current_value ];
	
	if( current_node.is_final() && input_char == input.size() && pda_stack.top() == Z0 ) {
		return true;
	}


	std::map< char, X > relay_list = current_node.get_relays();
	if( relay_list.count( input[ input_char ] ) ) {
		std::cout << pda_stack.top() << ' ' << relay_list[ input [ input_char ] ]._top_stack << '\n';
		if( pda_stack.top() != relay_list[ input[ input_char ] ]._top_stack ) {
			return false;
		}

		pda_stack.pop();

		for( std::vector< char >::reverse_iterator char_to_add = relay_list[ input[ input_char ] ]._stack_add.rbegin(); char_to_add != relay_list[ input[ input_char ] ]._stack_add.rend(); char_to_add++ ) {
			if( *char_to_add != LAMBDA ) {
				pda_stack.push( *char_to_add );
			}
		}
		
		if( check_word( relay_list[ input[ input_char ] ]._node_relay, node_list, input, input_char + 1 ) ) {
			return true;
		}
	} 

	if ( relay_list.count( LAMBDA ) ) {
		std::cout << pda_stack.top() << ' ' << relay_list[ input [ LAMBDA ] ]._top_stack << '\n';
		if( pda_stack.top() != relay_list[ LAMBDA ]._top_stack ) {
			return false;
		}

		pda_stack.pop();

		for( std::vector< char >::reverse_iterator char_to_add = relay_list[ LAMBDA ]._stack_add.rbegin(); char_to_add != relay_list[ LAMBDA ]._stack_add.rend(); char_to_add++ ) {
			if( *char_to_add != LAMBDA ) {
				pda_stack.push( *char_to_add );
			}
		}
		
		if( check_word( relay_list[ LAMBDA ]._node_relay, node_list, input, input_char + 1 ) ) {
			return true;
		}
	}

	return false;
}

int main(int argc, char const *argv[]) {

	pda_stack.push( Z0 );
	
    std::ifstream f( "date.in", std::ios_base::in );	
	
	// Number of relays
	int n;
	f >> n;

	// List of nodes 
	std::map< int, Node > node_list;

	// Setting the list
	for ( int i = 0; i < n; i++ ) {
		
		int node, dest_node;
		char relay, stack_top;
		std::string stack_add;

		f >> node >> relay >> stack_top >> stack_add >> dest_node;
		std::vector< char > stack_add_vector( stack_add.begin(), stack_add.end() );
		
		if ( node_list.count( node ) ) {
			node_list[ node ].add_relay( relay, dest_node, stack_top, stack_add_vector );
		} else {
			Node new_node( node );
			node_list[ node ] = new_node;
			node_list[ node ].add_relay( relay, dest_node, stack_top, stack_add_vector );
		}
		
		if ( !node_list.count( dest_node ) ) {
			Node new_dest_node( dest_node );
			node_list[ dest_node ] = new_dest_node;
		}
	}

	// Reading the number of final states
	f >> n;
	for ( int i = 0; i < n; i++ ) {
		int node_to_switch;
		f >> node_to_switch;
		node_list[ node_to_switch ].switch_final();
	}

	// Testing the list
	for ( std::map< int, Node >::iterator it = node_list.begin(); it != node_list.end(); ++it ) {
		
		Node current_node = it->second;
		std::cout << "Nod: " << current_node.get_value() << '\n';
		
		if ( current_node.is_final() ) {
			std::cout << "Este final\n";
		}

		std::cout << "Relay list:\n";
		std::map< char, X > relays_list = current_node.get_relays();
		for ( std::map< char, X >::iterator it2 = relays_list.begin(); it2 != relays_list.end(); it2++ ) {
			std::cout << it2->first << ": ";
			std::cout << it2->second._node_relay;
			std::cout << "\nStack add: \n";
			for( std::vector<char>::iterator charCheck = it2->second._stack_add.begin(); charCheck != it2->second._stack_add.end(); charCheck++ ) {
				std::cout << *charCheck << " ";
			}
			std::cout << "\n\n";
		}

	}

	std::string input;
	f >> input;
	f.close();
	std::cout << "\nReading string: " << input << "\nChoose the start node: ";
	int current_value;
	std::cin >> current_value;

	// String iterator
	if( check_word( current_value, node_list, input, 0 ) ) {
		std::cout << "\nThe input is accepted";
	} else {
		std::cout << "\nThe word is rejected";
	}

	return 0;
}