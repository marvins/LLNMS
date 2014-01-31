/**
 * @file    NetworkPane.cpp
 * @author  Marvin Smith
 * @date    1/28/2014
 */
#include "NetworkPane.hpp"

#include "../llnms/LLNMS_Network.hpp"

#include <QHeaderView>

#include <iostream>
#include <vector>

using namespace std;

/**
 * Constructor
 */
NetworkPane::NetworkPane( QWidget*  parent ) : QWidget( parent ){

    // build main widget
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment( Qt::AlignLeft | Qt::AlignTop );

    // build main label
    mainLabel = new QLabel("LLNMS Network Management Page");
    mainLabel->setFont(QFont(mainLabel->font().family(), 18));
    mainLayout->addWidget( mainLabel );

    // build network list widget
    build_network_list_widget();

    // set layout
    setLayout( mainLayout );

}


/**
 * Create the network list widget
 */
void NetworkPane::build_network_list_widget(){
    
    // create the network list label
    networkListLabel  = new QLabel("Network List");

    // add network list to main widget
    mainLayout->addWidget( networkListLabel );

    // create the widget
    networkListWidget = new QWidget(this);

    // create the layout
    networkListLayout = new QHBoxLayout;

    // create the table
    networkListTable = new QTableWidget(0, 3, networkListWidget);
    networkListTableHeaders.resize(3);
    networkListTableHeaders[0].setText("Name");
    networkListTableHeaders[1].setText("Address-Start");
    networkListTableHeaders[2].setText("Address-End");
    for( int i=0; i<networkListTableHeaders.size(); i++ ){
        networkListTable->setHorizontalHeaderItem( i, &networkListTableHeaders[i] );
    }

    // add table to network list widget
    networkListLayout->addWidget( networkListTable );

    // create the toolbar
    networkListToolbar = new QWidget(networkListWidget);
    
    // create the toolbar layout
    networkListToolbarLayout = new QVBoxLayout;
    networkListToolbarLayout->setAlignment( Qt::AlignTop );

    // create the add network button
    networkListCreateNetworkButton = new QToolButton;
    networkListCreateNetworkButton->setIcon(QIcon("icons/plus.png"));
    networkListCreateNetworkButton->setIconSize(QSize(40,40));
    networkListCreateNetworkButton->setToolTip("Create a Network Definition");
    networkListToolbarLayout->addWidget( networkListCreateNetworkButton );

    // create the remove network button
    networkListRemoveNetworkButton = new QToolButton;
    networkListRemoveNetworkButton->setIcon(QIcon("icons/delete.png"));
    networkListRemoveNetworkButton->setIconSize(QSize(40,40));
    networkListRemoveNetworkButton->setToolTip("Delete a Network Definition");
    networkListToolbarLayout->addWidget( networkListRemoveNetworkButton );
    
    
    // create the modify network button
    networkListModifyNetworkButton = new QToolButton;
    networkListModifyNetworkButton->setIcon(QIcon("icons/gear.png"));
    networkListModifyNetworkButton->setIconSize(QSize(40,40));
    networkListModifyNetworkButton->setToolTip("Modify a Network Definition");
    networkListToolbarLayout->addWidget( networkListModifyNetworkButton );

    // set the layout
    networkListToolbar->setLayout( networkListToolbarLayout );

    // add the toolbar to the main layout
    networkListLayout->addWidget( networkListToolbar );

    // set the main layout
    networkListWidget->setLayout( networkListLayout );

    // add the network list widget to the primary layout
    mainLayout->addWidget( networkListWidget );

    // load the table
    load_network_list_table();

}

/**
 * Load the network list table
 */
void NetworkPane::load_network_list_table(){
    
    // clear the table
    networkListTable->clearContents();
    
    // refresh the LLNMS Network Table
    llnms.network_container.update();

    // get the list of networks
    std::vector<LLNMS_Network> networklist = llnms.network_container.network_list();
    
    // resize the table
    networkListTable->setRowCount( networklist.size()+1 );
    
    // create the all item
    networkListTable->setItem( 0, 0, new QTableWidgetItem("All Networks"));

    // load the table
    for( size_t i=0; i<networklist.size(); i++ ){
        networkListTable->setItem( i+1, 0, new QTableWidgetItem( networklist[i].name().c_str()));
        networkListTable->setItem( i+1, 1, new QTableWidgetItem( networklist[i].address_start().c_str()));
        networkListTable->setItem( i+1, 2, new QTableWidgetItem( networklist[i].address_end().c_str()));
    }

#if QT_VERSION > 0x050000
    networkListTable->horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );
    networkListTable->horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    networkListTable->horizontalHeader()->setSectionResizeMode( 2, QHeaderView::Stretch );
#else
    networkListTable->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    networkListTable->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
    networkListTable->horizontalHeader()->setResizeMode( 2, QHeaderView::Stretch );
#endif
 
}

