/**
 * @file    NetworkManagerUI.cpp
 * @author  Marvin Smith
 * @date    1/14/2014
 */

/// LLNMS CLI Libraries
#include "NetworkManagerUI.hpp"
#include <utilities/CursesUtilities.hpp>
#include <utilities/Table.hpp>


/// NCurses
#include <ncurses.h>

/**
 * Print network manager footer
 */
void print_network_manager_footer( const int& maxX, const int& maxY ){
    
    /// print the horizontal line
    print_single_char_line( '-', maxY-3, 0, maxX );

    // print the first row
    mvprintw( maxY-2, 0, "q/Q: Back to main menu.");
    mvprintw( maxY-1, 0, "s/S: Switch to network list.");

}


/**
 * Print the network list
 */
void print_network_list( const int& minY, const int& maxY ){
    
    // print the header
    mvprintw( minY, 0, "Network Definition List" );
    
    // create a table to print the results on
    Table table;
    table.setHeaderName( 0, "Select" );
    table.setHeaderName( 1, "Network Name" );
    table.setHeaderName( 2, "Starting Address" );
    table.setHeaderName( 3, "Ending Address" );
    
    table.setHeaderRatio( 0, 0.05 );
    table.setHeaderRatio( 1, 0.35 );
    table.setHeaderRatio( 2, 0.30 );
    table.setHeaderRatio( 3, 0.30 );

    // print the table
    table.print( minY+1, options.maxX-1, maxY  ); 

}

/**
 * Print the network scan results
 */
void print_network_scan_results( const int& minY, const int& maxY ){

    // print the header
    mvprintw( minY, 0, "Network Scanning Results" );

}


/**
 * Network Manager UI
 */
void network_manager_ui(){
    
    // list of indeces for managing where stuff is
    int networkListWindowTop=3;
    int networkListWindowBot = (options.maxY / 2)-2;

    int networkScanWindowTop = networkListWindowBot+2;
    int networkScanWindowBot = options.maxY - 4;

    // start a loop
    bool EXIT_LOOP=false;
    while( EXIT_LOOP == false ){


        // clear the screen
        clear();

        // print header
        print_header("LLNMS Network Manager");

        // print the network list
        print_network_list( networkListWindowTop, networkListWindowBot );

        // print the network scanning results
        print_network_scan_results( networkScanWindowTop, networkScanWindowBot );
        
        // print footer
        print_network_manager_footer( options.maxX, options.maxY );

        // refresh the screen
        refresh();

        // grab the character
        int ch = getch();

        switch(ch){

            /// Exit Menu
            case 'q':
                EXIT_LOOP=true;
                break;



        }

    }


}
