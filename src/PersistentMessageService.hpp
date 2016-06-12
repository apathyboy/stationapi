
#pragma once

struct sqlite3;

class PersistentMessageService {
public:
    explicit PersistentMessageService(sqlite3* db);
    ~PersistentMessageService();

private:
    sqlite3* db_;
};