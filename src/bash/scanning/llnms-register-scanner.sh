#!/bin/sh
#
#   File:    llnms-register-scanner.sh
#   Author:  Marvin Smith
#   Date:    12/13/2013
#


#---------------------------------------#
#-          Usage Instructions         -#
#---------------------------------------#
usage(){

    echo "$0 [options]"
    echo ''
    echo '    options:'
    echo '        -h, --help    : Print usage instructions'
    echo '        -v, --version : Print version information'
    echo '' 
    echo '        -s, --scanner [llnms-scanner.xml file] : Set the scanner filename (Mandatory)'
    echo ''
}


#-------------------------------------#
#             Error Function          #
#-------------------------------------#
error(){
    echo "error $1"
}


#-------------------------------------#
#           Version Function          #
#-------------------------------------#
version(){

    echo "$0 Information"
    echo ''
    echo "   LLNMS Version ${LLNMS_MAJOR}.${LLNMS_MINOR}.${LLNMS_SUBMINOR}"

}


#-------------------------------------#
#-           Main Function           -#
#-------------------------------------#

#  Source llnms home
if [ "$LLNMS_HOME" = "" ]; then
    LLNMS_HOME="/var/tmp/llnms"
fi


#  Import the version info
source $LLNMS_HOME/config/llnms-info.sh


#  Scanner flags
SCANNER_FLAG=0
SCANNER_FILE=''

#   Parse Command-Line Options
for OPTION in "$@"; do

    case $OPTION in

        #  Print usage instructions
        '-h' | '--help' )
            usage
            exit 1
            ;;


        #  Print version information
        '-v' | '--version' )
            version
            exit 1
            ;;
        
        #  Set the scanner flag
        '-s' | '--scanner' )
            SCANNER_FLAG=1
            ;;

        #  Otherwise there is an error or we are pulling values
        *)

            #  Set the scanner filename
            if [ $SCANNER_FLAG -eq 1 ]; then
                SCANNER_FLAG=0
                SCANNER_FILE=$OPTION

            #  Otherwise, there is an error
            else
                error "unknown option $OPTION"
                exit 1
            fi

            ;;
        
    esac
done

