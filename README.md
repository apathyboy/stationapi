# swgchat [![Build Status](https://travis-ci.com/apathyboy/swgchat.svg?token=FbjsTwsn9ctKssvZJqCa&branch=master)](https://travis-ci.com/apathyboy/swgchat) #

An open implementation of the chat gateway that SOE based games used to provide various social communication features such as mail, custom chat rooms, friend management, etc.

Like my work and want to support my free and open-source contributions? 

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=8KCAU8HB9J7YU)

## Implementation ##

Uses the SOE libraries to implement chat features in a standalone utility. Ideally, the completed implementation would allow for multiple galaxies to connect and allow players to communicate across them.

## External Dependencies ##

c++14 compatible compiler
boost::iostreams (header only)
boost::optional (header only)
boost::program_options
sqlite3
udplibrary - bundled in the Star Wars Galaxies official source

## Building ##

Copy the udplibrary directory from the Star Wars Galaxies offical source to the top level swgchat directory, then run the following:

    mkdir build; cd build
    cmake ..
    cmake --build .

## Database Initialization ##

Create the database with the following commands:

    sqlite3 chat.db
    sqlite> .read /path/to/init_database.sql

Then update the **database_path** config option with the full path to the database.
