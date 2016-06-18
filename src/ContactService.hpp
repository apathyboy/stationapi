
#pragma once

struct sqlite3;

class ContactService {
public:
    explicit ContactService(sqlite3* db);
    ~ContactService();

private:
    sqlite3* db_;
};