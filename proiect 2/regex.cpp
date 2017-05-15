#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

#include "Node.h"

#define LAMBDA "L"
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
	for ( std::map< int, Node >::iterator it = node_list.begin(); it != node_list.end(); ++it ) {

		Node current_node = it->second;
		std::map< int, std::string > current_node_relay_list = current_node.get_relays();
		if( current_node.get_value() != START && current_node.get_value() != FINAL ) {
			
			for( std::map< int, Node >::iterator node = node_list.begin(); node != node_list.end(); node++ ) {
				if( node->first != it->first ) {
					std::map< int, std::string > node_relay_list = node->second.get_relays();
					if( node_relay_list.count( current_node.get_value() ) ) {
						for( std::map< int, std::string >::iterator relay = current_node_relay_list.begin(); relay != current_node_relay_list.end(); relay++ ) {
							node->second.add_relay( node_relay_list[ it->first ] + relay->second, relay->first );
						}
					}
				}
			}

		}
	}

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