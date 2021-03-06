/**
 * @file    MainMenu.cpp
 * @author  Marvin Smith
 * @date    12/31/2013
 */

/// CLI Libraries
#include <ui/AboutUI.hpp>
#include <ui/ConfigurationUI.hpp>
#include <ui/MainMenu.hpp>
#include <ui/NetworkManagerUI.hpp>
#include <utilities/CursesUtilities.hpp>

/// NCurses
#include <ncurses.h>


/**
 * Print the LLNMS Main Menu Footer
*/
void print_main_menu_footer( const int& idx ){
    
    // print bottom header row
    mvprintw( idx+1 , 0, "Press any key to continue: ");

}


/**
 * Print the main menu
*/
void main_menu(){
    
    // add debug message
    logger.add_message( "Entering Main Menu.", LOG_DEBUG );

    // start a loop
    bool EXIT_LOOP=false;
    while( EXIT_LOOP == false ){

        // clear the screen
        clear();    

        // print header
        print_header("LLNMS Main Menu");
        
        // print content
        int i=2;
        mvprintw( i++, 0, "n: Network Management.");
        
        i++;
        mvprintw( i++, 0, "c: Configuration Window.");
        mvprintw( i++, 0, "h: Help/Usage/About.");
        mvprintw( i++, 0, "q: Quit LLNMS Manager.");

        // print footer
        print_main_menu_footer( i );

        // refresh the screen
        refresh();

        // grab the character
        int ch = getch();

        switch(ch){
            
            /**
             * Network Manager
             */
            case 'n':
            case 'N':
                network_manager_ui();
                break;

            /**
             * About Window.
             */
            case 'h':
            case 'H':
                about_ui();
                break;
            
            /**
             * Configuration UI
             */
            case 'c':
            case 'C':
                configuration_ui();
                break;

            /**
             * Quit Program
            */
            case 'q':
            case 'Q':
                EXIT_LOOP=true;
                break;
            
            default:;

        }


    }

    // add exit message
    logger.add_message("Exiting Main Menu.", LOG_DEBUG );
}

