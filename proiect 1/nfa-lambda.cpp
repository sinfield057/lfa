#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

#include "Node.h"

#define LAMBDA '*'

bool check_word( int current_value, std::map< int, Node > node_list, std::string input, int input_char ) {
	
	Node current_node = node_list[ current_value ];
	
	if( current_node.is_final() && input_char == input.size() ) {
		return true;
	}


	std::map< char, std::vector< int > > relay_list = current_node.get_relays();
	if( relay_list.count( input[ input_char ] ) ) {
		std::vector< int > relays = relay_list[ input[ input_char ] ];
		for ( std::vector< int >::iterator it = relays.begin(); it != relays.end(); it++ ) {
			if( check_word( *it, node_list, input, input_char + 1 ) ) {
				return true;
			}
		}
	} else {
		std::vector< int > closures = current_node.get_closures();
		for ( std::vector< int >::iterator it = closures.begin(); it != closures.end(); it++ ) {
			if( check_word( *it, node_list, input, input_char ) ) {
				return true;
			}
		} 
	}

	return false;
}

int main(int argc, char const *argv[]) {
	
    std::ifstream f( "date.in", std::ios_base::in );	
	
	// Number of relays
	int n;
	f >> n;

	// List of nodes 
	std::map< int, Node > node_list;

	// Setting the list
	for ( int i = 0; i < n; i++ ) {
		
		int node, dest_node;
		char relay;

		f >> node >> relay >> dest_node;
		
		switch( relay ) {
			case LAMBDA:
				if ( node_list.count( node ) ) {
					node_list[ node ].add_closure( dest_node );
				} else {
					Node new_node( node );
					node_list[ node ] = new_node;
					node_list[ node ].add_closure( dest_node );
				}

				if ( !node_list.count( dest_node ) ) {
					Node new_dest_node( dest_node );
					node_list[ dest_node ] = new_dest_node;
				}
				break;
			default:
				if ( node_list.count( node ) ) {
					node_list[ node ].add_relay( relay, dest_node );
				} else {
					Node new_node( node );
					node_list[ node ] = new_node;
					node_list[ node ].add_relay( relay, dest_node );
				}
				if ( !node_list.count( dest_node ) ) {
					Node new_dest_node( dest_node );
					node_list[ dest_node ] = new_dest_node;
				}
				break;
		}
	}

	// Reading the number of final states
	f >> n;

	for ( int i = 0; i < n; ++i ) {
		
		int node;

		f >> node;

		node_list[ node ].switch_final();

	}

	// Testing the list
	for ( std::map< int, Node >::iterator it = node_list.begin(); it != node_list.end(); ++it ) {
		
		Node current_node = it->second;
		std::cout << "Nod: " << current_node.get_value() << '\n';
		
		if ( current_node.is_final() ) {
			std::cout << "Este final\n";
		}

		std::cout << "Relay list:\n";
		std::map< char, std::vector< int > > relays_list = current_node.get_relays();
		for ( std::map< char, std::vector< int > >::iterator it2 = relays_list.begin(); it2 != relays_list.end(); it2++ ) {
			std::cout << it2->first << ": ";
			std::vector< int > copy = it2->second;	
			for ( std::vector< int >::iterator it3 = copy.begin(); it3 < copy.end(); it3++ ) {
				std::cout << *it3 << ' ';
			}
			std::cout << '\n';
		}

		std::cout << "Closure list:\n";
		std::vector< int > closure_copy = it->second.get_closures();
		for ( std::vector< int >::iterator it2 = closure_copy.begin(); it2 != closure_copy.end(); it2++ ) {
			std::cout << *it2 << ' ';
		}
		std::cout << "\n\n";

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