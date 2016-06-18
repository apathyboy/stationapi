#include "ContactService.hpp"

#include <sqlite3.h>

ContactService::ContactService(sqlite3 * db)
    : db_{db} {}

ContactService::~ContactService() {}
