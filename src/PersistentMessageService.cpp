#include "PersistentMessageService.hpp"

#include <sqlite3.h>

PersistentMessageService::PersistentMessageService(sqlite3* db)
    : db_{db} {}

PersistentMessageService::~PersistentMessageService() {}
