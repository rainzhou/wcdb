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

#include <WCDB/Assertion.hpp>
#include <WCDB/Lang.h>

namespace WCDB {

namespace Lang {

AlterTableSTMT::AlterTableSTMT() : switcher(Switch::NotSet)
{
}

CopyOnWriteString AlterTableSTMT::SQL() const
{
    std::string description("ALTER TABLE ");
    description.append(schemaName.isNull() ? mainSchema() : schemaName.get());
    description.append(".");
    LangRemedialAssert(!tableName.empty());
    description.append(tableName.get());
    switch (switcher) {
    case Switch::Rename:
        description.append(" RENAME TO " + newTableName.get());
        break;
    case Switch::AddColumn:
        description.append(" ADD COLUMN " + columnDef.description().get());
        break;
    default:
        LangRemedialFatalError();
        break;
    }
    return description;
}

STMT::Type AlterTableSTMT::getSTMTType() const
{
    return STMT::Type::AlterTable;
}

STMT::Type AlterTableSTMT::getType()
{
    return STMT::Type::AlterTable;
}

} // namespace Lang

} // namespace WCDB