/**
 * @file    ModifyNetworkDialog.cpp
 * @author  Marvin Smith
 * @date    4/25/2014
*/
#include "ModifyNetworkDialog.hpp"

/**
 * Default Constructor
*/
ModifyNetworkDialog::ModifyNetworkDialog( LLNMS::NETWORK::NetworkDefinition const& network_definition, 
                                          QWidget* parent ) : QDialog(parent){

    // set the network definition
    m_networkDefinition = network_definition;

    // set the window title
    setWindowTitle("Modify Network Information");

    // create the main layout
    mainLayout = new QVBoxLayout();
    mainLayout->setAlignment( Qt::AlignTop | Qt::AlignLeft );

    // create the name widget
    initNameWidget();

    // create the starting address widget
    initStartAddressWidget();

    // create the ending address widget
    initEndAddressWidget();
    
    // create the toolbar
    initToolbar();

    // set the layout
    setLayout( mainLayout );

}

/**
 * Create the name widget
*/
void ModifyNetworkDialog::initNameWidget(){

    // create the widget
    nameWidget = new QWidget(this);

    // create the layout
    nameLayout = new QHBoxLayout();
    
    // set the label
    nameLabel = new QLabel("Network Name:", this);
    nameLayout->addWidget(nameLabel);

    // set the edit
    nameEdit = new QLineEdit(this);
    nameEdit->setText(m_networkDefinition.name().c_str());
    nameEdit->setReadOnly(true);
    nameLayout->addWidget(nameEdit);

    // set the button
    nameLockButton = new QToolButton(this);
    nameLockButton->setIcon(QIcon("icons/unlock.png"));
    nameLayout->addWidget(nameLockButton);
    connect(nameLockButton, SIGNAL(clicked()), this, SLOT(toggleNameEdit()));

    // set the layout
    nameWidget->setLayout(nameLayout);

    // add to main widget
    mainLayout->addWidget(nameWidget);

}

/**
 * Create the start address widget
*/
void ModifyNetworkDialog::initStartAddressWidget(){
    
    // create the widget
    startAddressWidget = new QWidget(this);

    // create the layout
    startAddressLayout = new QHBoxLayout();

    // create the label
    startAddressLabel = new QLabel("Starting Address:");
    startAddressLayout->addWidget(startAddressLabel);

    // create the edit 
    startAddressEdit = new QLineEdit();
    startAddressEdit->setText(m_networkDefinition.address_start().c_str());
    startAddressEdit->setReadOnly(true);
    startAddressLayout->addWidget(startAddressEdit);

    // create the unlock button
    startAddressLockButton = new QToolButton();
    startAddressLockButton->setIcon(QIcon("icons/unlock.png"));
    startAddressLayout->addWidget(startAddressLockButton);
    connect( startAddressLockButton, SIGNAL(clicked()), this, SLOT(toggleStartAddressEdit()));

    // set the layout
    startAddressWidget->setLayout(startAddressLayout);

    // add to main widget
    mainLayout->addWidget(startAddressWidget);


}


/**
 * Create the end address widget
*/
void ModifyNetworkDialog::initEndAddressWidget(){
    
    // create the widget
    endAddressWidget = new QWidget(this);

    // create the layout
    endAddressLayout = new QHBoxLayout();

    // create the label
    endAddressLabel = new QLabel("Ending Address:");
    endAddressLayout->addWidget(endAddressLabel);

    // create the line edit
    endAddressEdit = new QLineEdit();
    endAddressEdit->setText(m_networkDefinition.address_end().c_str());
    endAddressEdit->setReadOnly(true);
    endAddressLayout->addWidget(endAddressEdit);

    // create lock button
    endAddressLockButton = new QToolButton();
    endAddressLockButton->setIcon(QIcon("icons/unlock.png"));
    endAddressLayout->addWidget(endAddressLockButton);
    connect( endAddressLockButton, SIGNAL(clicked()), this, SLOT(toggleEndAddressEdit()));

    // set the layout
    endAddressWidget->setLayout(endAddressLayout);

    // add to main widget
    mainLayout->addWidget(endAddressWidget);


}

/**
 * Create the init toolbar
*/
void ModifyNetworkDialog::initToolbar(){

    // create the widget
    toolbarWidget = new QWidget(this);

    // create the layout
    toolbarLayout = new QHBoxLayout();

    // create the save button
    modifyButton = new QToolButton();
    modifyButton->setText("Save Changes");
    modifyButton->setFixedSize(QSize(110,40));
    toolbarLayout->addWidget(modifyButton);
    connect( modifyButton, SIGNAL(clicked()), this, SLOT(updateNetwork()));

    // create the cancel button
    cancelButton = new QToolButton();
    cancelButton->setText("Cancel");
    cancelButton->setFixedSize(QSize(110,40));
    toolbarLayout->addWidget(cancelButton);
    connect( cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    // set the layout
    toolbarWidget->setLayout(toolbarLayout);

    // add to main layout
    mainLayout->addWidget(toolbarWidget);
}

/**
 * Update the network
*/
void ModifyNetworkDialog::updateNetwork(){

    // grab the settings
    std::string newName  = nameEdit->text().toLocal8Bit().constData();
    std::string newStart = startAddressEdit->text().toLocal8Bit().constData();
    std::string newEnd   = endAddressEdit->text().toLocal8Bit().constData();

    // write to file
    m_networkDefinition.name()          = newName;
    m_networkDefinition.address_start() = newStart;
    m_networkDefinition.address_end()   = newEnd;

    m_networkDefinition.updateFile();

    // close
    close();

}

/**
 * Toggle Name Edit
*/
void ModifyNetworkDialog::toggleNameEdit(){

    if( nameEdit->isReadOnly() == true ){
        nameEdit->setReadOnly(false);
        nameLockButton->setIcon(QIcon("icons/lock.png"));
    } else {
        nameEdit->setReadOnly(true);
        nameLockButton->setIcon(QIcon("icons/unlock.png"));
    }

}

/**
 * Toggle Starting Address
*/
void ModifyNetworkDialog::toggleStartAddressEdit(){

    if( startAddressEdit->isReadOnly() == true ){
        startAddressEdit->setReadOnly(false);
        startAddressLockButton->setIcon(QIcon("icons/lock.png"));
    } else {
        startAddressEdit->setReadOnly(true);
        startAddressLockButton->setIcon(QIcon("icons/unlock.png"));
    }
}

/**
 * Toggle Ending Address
*/
void ModifyNetworkDialog::toggleEndAddressEdit(){

    // if the edit is read only, then change it
    if( endAddressEdit->isReadOnly() == true ){
        endAddressEdit->setReadOnly(false);
        endAddressLockButton->setIcon(QIcon("icons/lock.png"));
    } else {
        endAddressEdit->setReadOnly(true);
        endAddressLockButton->setIcon(QIcon("icons/unlock.png"));
    }

}


