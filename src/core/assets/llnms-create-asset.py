#!/usr/bin/env python
#
#    File:    llnms-create-asset
#    Author:  Marvin Smith
#    Date:    6/15/2015
#
#    Purpose:  Create an LLNMS Asset
#
__author__ = 'Marvin Smith'

#  Python Libraries
import argparse, os, sys, datetime

#  LLNMS Libraries
if os.environ['LLNMS_HOME'] is not None:
    sys.path.append(os.environ['LLNMS_HOME'] + '/lib')
import llnms


# ------------------------------------ #
# -      Parse the Command Line      - #
# ------------------------------------ #
def Parse_Command_Line():

    #  Create parser
    parser = argparse.ArgumentParser(description="Create an LLNMS Asset.")

    #  Version Info
    parser.add_argument('-v', '--version',
                        action='version',
                        version='%(prog)s ' + llnms.info.Get_Version_String(),
                        help='Print the version information.')

    #  Verbose Mode
    parser.add_argument('--verbose',
                        dest='verbose_flag',
                        required=False,
                        default=False,
                        action='store_true',
                        help='Print with verbose output.')

    #  Quiet Mode
    parser.add_argument('--quiet',
                        required=False,
                        default=False,
                        action='store_true',
                        help='Do not print output.')

    #  Interactive
    parser.add_argument('-i', '--interactive',
                        required=False,
                        default=False,
                        dest='interactive_mode',
                        action='store_true',
                        help='Run in interactive mode.',)

    #  Network Name
    parser.add_argument('-host', '--hostname',
                        required=False,
                        dest='asset_hostname',
                        help='Name of the network to scan.')

	#  Description
    parser.add_argument('-d','--description',
                        required=False,
                        dest='asset_description',
                        help='Asset description.')
	
	#  Address
    parser.add_argument('-a','--address',
						required=False,
						dest='asset_addresses',
						action='append',
						help='Address for the particular network.'

    #  Output Pathname
    parser.add_argument('-o','--output-path',
                        required=False,
                        dest='asset_output_path',
                        help='Output pathname.  If not provided on will be generated.')

    #  Return Parser
    return parser.parse_args()

# ------------------------------ #
# -       Process Inputs       - #
# ------------------------------ #
def Process_Inputs( options, asset_list, llnms_home ):

    #  Get the hostname
    asset_hostname = options.asset_hostname
    if options.interactive_mode is True and asset_hostname is None:
        asset_hostname = raw_input('Please enter the desired asset name: ')


    #  Compare the asset list to see if the name is set
    for asset in asset_list:
        if asset.hostname == asset_hostname:
            raise Exception('Asset with hostname (' + asset_hostname + ') already exists.')


    #  Get the description
    asset_description = options.asset_description
    if options.interactive_mode is True and network_description is None:
        network_description = raw_input('Please enter description of network: ')


    #  Get the network path
    network_output_path = options.network_output_path
    if network_output_path is None:
        network_output_path = llnms_home + '/networks/' + datetime.datetime.now().strftime('%Y%M%d_%H%m%s') + '.llnms-network.xml'

    #  Return new network
    return llnms.Network.Network(name          = network_name,
                                 address_start = network_address_start,
                                 address_end   = network_address_end,
                                 description   = network_description,
                                 filename      = network_output_path)

# -------------------------------- #
# -       Validate Options       - #
# -------------------------------- #
def Validate_Options( options ):

    #  Make sure either interactive set or else the variables set
    if  options.interactive_mode is True:
        return

    #  Make sure the name, and other items set
    if options.network_name is None:
        raise Exception('No network name provided.')
    if options.network_address_start is None:
        raise Exception('No address start provided.')
    if options.network_address_end is None:
        raise Exception('No address end provided.')


# ----------------------------- #
# -       Main Function       - #
# ----------------------------- #
def Main():

    #  Look for LLNMS_HOME
    LLNMS_HOME = os.environ['LLNMS_HOME']

    #  Parse the command-line
    options = Parse_Command_Line()

    #  Check for errors
    Validate_Options( options )

    #  Check if name provided or interactive mode enabled
    network_list = llnms.Network.llnms_load_networks(llnms_home=LLNMS_HOME)

    #  Check the input arguments
    new_network = Process_Inputs( options,
                                  network_list,
                                  LLNMS_HOME )

    #  Create the network
    if new_network.Is_Valid():
        new_network.Write_Network_File()
    else:
        raise Exception('Network has an invalid structure.')

if __name__ == '__main__':
    Main()
