# SWGChat [![Build Status](https://travis-ci.com/apathyboy/swgchat.svg?token=FbjsTwsn9ctKssvZJqCa&branch=master)](https://travis-ci.com/apathyboy/swgchat) #

An open implementation of the chat gateway that SOE based games used to provide various social communication features such as mail, custom chat rooms, friend management, etc.

## Implementation ##

Uses the SOE libraries to implement chat features in a standalone utility. Ideally, the completed implementation would allow for multiple galaxies to connect and allow players to communicate across them.

## Database Initialization ##

Create the database with the following commands:

    sqlite3 chat.db
    sqlite> .read /path/to/init_database.sql

Then update the **chatDatabasePath** config option with the full path to the database.
