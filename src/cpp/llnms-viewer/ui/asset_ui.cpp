/**
 * @file    asset_ui.cpp
 * @author  Marvin Smith
 * @date    1/2/2014
*/
#include "asset_ui.hpp"
#include "curses_utils.hpp"

#include "Table.hpp"

#include <ncurses.h>

/**
 * Asset Manager User Interface
*/
void asset_ui(){
    
    // start loop
    bool EXIT_LOOP=false;
    while( EXIT_LOOP == false ){
        
        // clear the screen
        clear();

        // print the header
        print_header("Asset Status and Configuration");
    
        /**
         * Create table
        */
        Table table;
        table.setHeaderName( 0, "Asset Name" );
        
        table.print( 2, options.maxX, options.maxY );

        // refresh the screen
        refresh();

        // get the character
        int ch = getch();

        /**
         * Parse Switch
        */
        switch(ch){

            /**
             * Back out of window
            */
            case 'q':
            case 'Q':
                EXIT_LOOP=true;
                break;


        }

    }

}
