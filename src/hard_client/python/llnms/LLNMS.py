#!/usr/bin/env python
import network
from utils import Logger

#------------------------------------------------------------------------------#
#-   Global class which contains most if not all relevant LLNMS information   -#
#------------------------------------------------------------------------------#
class LLNMS:
	''' LLNMS State Class'''
	
	#-    Constructor   -#
	def __init__(self):
		
		# set the home
		self.LLNMS_HOME="/var/tmp/llnms";

		# set the log file
		self.logger = Logger.Logger('/var/tmp/llnms/log/llnms-viewer.log')

		# load the network list
		network_path = self.LLNMS_HOME + "/networks";
		self.networks = network.llnms_load_networks( network_path, self.logger );
		self.logger.addMessage('Networks loaded from ' + network_path, Logger.INFO );

		
