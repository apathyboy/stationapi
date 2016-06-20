CREATE TABLE avatar (id INTEGER PRIMARY KEY,
                     user_id INTEGER,
                     name TEXT,
                     address TEXT,
                     attributes INTEGER);

CREATE TABLE room (id INTEGER PRIMARY KEY,
                   creator_id INTEGER,
                   creator_name TEXT,
                   creator_address TEXT,
                   room_name TEXT,
                   room_topic TEXT,
                   room_password TEXT,
                   room_prefix TEXT,
                   room_address TEXT,
                   room_attributes INTEGER,
                   room_max_size INTEGER,
                   room_message_id INTEGER,
                   created_at INTEGER,
                   node_level INTEGER);

CREATE TABLE persistent_message (id INTEGER PRIMARY KEY,
                                 avatar_id INTEGER,
                                 from_name TEXT,
                                 from_address TEXT,
                                 subject TEXT,
                                 sent_time INTEGER,
                                 status INTEGER,
                                 folder TEXT,
                                 category TEXT,
                                 message TEXT,
                                 oob TEXT);

CREATE TABLE friend (id INTEGER PRIMARY KEY,
                     avatar_id INTEGER,
                     friend_avatar_id INTEGER);

CREATE TABLE ignore (id INTEGER PRIMARY KEY,
                     avatar_id INTEGER,
                     ignore_avatar_id INTEGER);
