#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

#include "Node.h"

#define LAMBDA "*"
#define START 999
#define FINAL 1000

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
		std::string relay;

		f >> node >> relay >> dest_node;

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
	}

	// Reading the number of final states
	f >> n;
	
	Node final_node( FINAL );
	node_list[ FINAL ] = final_node;
	node_list[ FINAL ].switch_final();

	for ( int i = 0; i < n; ++i ) {
		
		int node;

		f >> node;

		node_list[ node ].add_relay( LAMBDA, FINAL );

	}

	// Reading the start state
	f >> n;
	f.close();
	
	Node start_node( START );
	node_list[ START ] = start_node;
	node_list[ START ].switch_start();
	node_list[ START ].add_relay( LAMBDA, n );

	// Creating the RE
	// for ( std::map< int, Node >::iterator it = node_list.begin(); it != node_list.end(); ++it ) {

	// 	Node current_node = it->second;
	// 	if( current_node.get_value() != START && current_node.get_value() != FINAL ) {

	// 		std::string new_relay = "";
	// 		std::map< std::string, int > relays_list = current_node.get_relays();
	// 		for ( std::map< std::string, int >::iterator it2 = relays_list.begin(); it2 != relays_list.end(); it2++ ) {
	// 			if ( it->first == it2->second ) {
	// 				new_relay = new_relay + it2->first;
	// 				new_relay = new_relay + "+";
	// 				it->second.delete_relay( it2->first );
	// 			}
	// 		}
	// 		new_relay = new_relay.size() ? new_relay.substr( 0, new_relay.size() - 1 ) : "";

	// 		if( new_relay.size() ) {
	// 			it->second.add_relay( new_relay, it->first );
	// 		}
	// 	}
	// }

	// Testing the list
	for ( std::map< int, Node >::iterator it = node_list.begin(); it != node_list.end(); ++it ) {
		
		Node current_node = it->second;
		std::cout << "\nNod: " << current_node.get_value() << '\n';
		
		if ( current_node.is_start() ) {
			std::cout << "Este de inceput\n";
		}

		if ( current_node.is_final() ) {
			std::cout << "Este final\n";
		}

		std::cout << "Relay list:\n";
		std::map< int, std::string > relays_list = current_node.get_relays();
		for ( std::map< int, std::string >::iterator it2 = relays_list.begin(); it2 != relays_list.end(); it2++ ) {
			std::cout << it2->second << ": ";
			std::cout << it2->first << '\n';
		}
	}

	return 0;
}