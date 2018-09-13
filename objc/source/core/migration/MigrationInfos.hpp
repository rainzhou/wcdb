/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MigrationInfos_hpp
#define MigrationInfos_hpp

#include <WCDB/Lock.hpp>
#include <WCDB/MigrationInfo.hpp>
#include <functional>
#include <list>
#include <map>

namespace WCDB {

class MigrationInfos {
#pragma mark - Initialize
public:
    MigrationInfos();

protected:
    mutable SharedLock m_lock;

#pragma mark - Notification
public:
    // source table -> target table, target database
    typedef std::function<void(const std::string&, std::string&, std::string&)> TableShouldBeMigratedCallback;
    void setNotificaitionWhenTableShouldBeMigrated(const TableShouldBeMigratedCallback& callback);

protected:
    TableShouldBeMigratedCallback m_tableShouldBeMigratedCallback;

#pragma mark - Infos
public:
    // identified? -> Migration Info
    const MigrationInfo* getOrIdentifyInfo(const std::string& tableName);

protected:
    const MigrationInfo* getInfo(const std::string& tableName);
    std::list<const MigrationInfo> m_infos;
    std::map<std::string, const MigrationInfo*> m_tableInfos;
};

} // namespace WCDB

#endif /* MigrationInfos_hpp */