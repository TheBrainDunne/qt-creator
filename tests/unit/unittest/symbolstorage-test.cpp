/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "googletest.h"

#include "mockfilepathcaching.h"
#include "mocksqlitereadstatement.h"
#include "mocksqlitewritestatement.h"

#include <storagesqlitestatementfactory.h>
#include <symbolstorage.h>
#include <sqlitedatabase.h>

#include <storagesqlitestatementfactory.h>

#include <utils/optional.h>

namespace {

using Utils::PathString;
using ClangBackEnd::FilePathCachingInterface;
using ClangBackEnd::SymbolEntries;
using ClangBackEnd::SymbolEntry;
using ClangBackEnd::SourceLocationEntries;
using ClangBackEnd::SourceLocationEntry;
using ClangBackEnd::StorageSqliteStatementFactory;
using ClangBackEnd::SymbolType;
using Sqlite::Database;
using Sqlite::Table;

using StatementFactory = StorageSqliteStatementFactory<MockSqliteDatabase,
                                                MockSqliteReadStatement,
                                                MockSqliteWriteStatement>;
using Storage = ClangBackEnd::SymbolStorage<StatementFactory>;

class SymbolStorage : public testing::Test
{
protected:
    MockFilePathCaching filePathCache;
    NiceMock<MockSqliteDatabase> mockDatabase;
    StatementFactory statementFactory{mockDatabase};
    MockSqliteWriteStatement &insertSymbolsToNewSymbolsStatement = statementFactory.insertSymbolsToNewSymbolsStatement;
    MockSqliteWriteStatement &insertLocationsToNewLocationsStatement = statementFactory.insertLocationsToNewLocationsStatement;
    MockSqliteReadStatement &selectNewSourceIdsStatement = statementFactory.selectNewSourceIdsStatement;
    MockSqliteWriteStatement &addNewSymbolsToSymbolsStatement = statementFactory.addNewSymbolsToSymbolsStatement;
    MockSqliteWriteStatement &syncNewSymbolsFromSymbolsStatement = statementFactory.syncNewSymbolsFromSymbolsStatement;
    MockSqliteWriteStatement &syncSymbolsIntoNewLocationsStatement = statementFactory.syncSymbolsIntoNewLocationsStatement;
    MockSqliteWriteStatement &deleteAllLocationsFromUpdatedFilesStatement = statementFactory.deleteAllLocationsFromUpdatedFilesStatement;
    MockSqliteWriteStatement &insertNewLocationsInLocationsStatement = statementFactory.insertNewLocationsInLocationsStatement;
    MockSqliteWriteStatement &deleteNewSymbolsTableStatement = statementFactory.deleteNewSymbolsTableStatement;
    MockSqliteWriteStatement &deleteNewLocationsTableStatement = statementFactory.deleteNewLocationsTableStatement;
    MockSqliteWriteStatement &insertProjectPartStatement = statementFactory.insertProjectPartStatement;
    MockSqliteWriteStatement &updateProjectPartStatement = statementFactory.updateProjectPartStatement;
    MockSqliteReadStatement &getProjectPartIdStatement = statementFactory.getProjectPartIdStatement;
    MockSqliteWriteStatement &deleteAllProjectPartsSourcesWithProjectPartIdStatement = statementFactory.deleteAllProjectPartsSourcesWithProjectPartIdStatement;
    MockSqliteWriteStatement &insertProjectPartSourcesStatement = statementFactory.insertProjectPartSourcesStatement;
    MockSqliteWriteStatement &insertIntoNewUsedMacrosStatement = statementFactory.insertIntoNewUsedMacrosStatement;
    MockSqliteWriteStatement &syncNewUsedMacrosStatement = statementFactory.syncNewUsedMacrosStatement;
    MockSqliteWriteStatement &deleteOutdatedUsedMacrosStatement = statementFactory.deleteOutdatedUsedMacrosStatement;
    MockSqliteWriteStatement &deleteNewUsedMacrosTableStatement = statementFactory.deleteNewUsedMacrosTableStatement;
    MockSqliteWriteStatement &insertFileStatuses = statementFactory.insertFileStatuses;
    MockSqliteWriteStatement &insertIntoNewSourceDependenciesStatement = statementFactory.insertIntoNewSourceDependenciesStatement;
    MockSqliteWriteStatement &syncNewSourceDependenciesStatement = statementFactory.syncNewSourceDependenciesStatement;
    MockSqliteWriteStatement &deleteOutdatedSourceDependenciesStatement = statementFactory.deleteOutdatedSourceDependenciesStatement;
    MockSqliteWriteStatement &deleteNewSourceDependenciesStatement = statementFactory.deleteNewSourceDependenciesStatement;
    MockSqliteReadStatement &getProjectPartCompilerArgumentsAndMacroNames = statementFactory.getProjectPartCompilerArgumentsAndMacroNames;
    SymbolEntries symbolEntries{{1, {"functionUSR", "function"}},
                                {2, {"function2USR", "function2"}}};
    SourceLocationEntries sourceLocations{{1, {1, 3}, {42, 23}, SymbolType::Declaration},
                                          {2, {1, 4}, {7, 11}, SymbolType::Declaration}};
    ClangBackEnd::ProjectPartArtefact artefact{{"-DFOO"}, {"FOO"}, 74};
    Storage storage{statementFactory, filePathCache};
};

TEST_F(SymbolStorage, CreateAndFillTemporaryLocationsTable)
{
    InSequence sequence;

    EXPECT_CALL(insertLocationsToNewLocationsStatement, write(1, 42, 23, 3));
    EXPECT_CALL(insertLocationsToNewLocationsStatement, write(2, 7, 11, 4));

    storage.fillTemporaryLocationsTable(sourceLocations);
}

TEST_F(SymbolStorage, AddNewSymbolsToSymbols)
{
    EXPECT_CALL(addNewSymbolsToSymbolsStatement, execute());

    storage.addNewSymbolsToSymbols();
}

TEST_F(SymbolStorage, SyncNewSymbolsFromSymbols)
{
    EXPECT_CALL(syncNewSymbolsFromSymbolsStatement, execute());

    storage.syncNewSymbolsFromSymbols();
}

TEST_F(SymbolStorage, SyncSymbolsIntoNewLocations)
{
    EXPECT_CALL(syncSymbolsIntoNewLocationsStatement, execute());

    storage.syncSymbolsIntoNewLocations();
}

TEST_F(SymbolStorage, DeleteAllLocationsFromUpdatedFiles)
{
    EXPECT_CALL(deleteAllLocationsFromUpdatedFilesStatement, execute());

    storage.deleteAllLocationsFromUpdatedFiles();
}

TEST_F(SymbolStorage, InsertNewLocationsInLocations)
{
    EXPECT_CALL(insertNewLocationsInLocationsStatement, execute());

    storage.insertNewLocationsInLocations();
}

TEST_F(SymbolStorage, DropNewSymbolsTable)
{
    EXPECT_CALL(deleteNewSymbolsTableStatement, execute());

    storage.deleteNewSymbolsTable();
}

TEST_F(SymbolStorage, DropNewLocationsTable)
{
    EXPECT_CALL(deleteNewLocationsTableStatement, execute());

    storage.deleteNewLocationsTable();
}

TEST_F(SymbolStorage, AddSymbolsAndSourceLocationsCallsWrite)
{
    InSequence sequence;

    EXPECT_CALL(insertSymbolsToNewSymbolsStatement, write(An<uint>(), An<Utils::SmallStringView>(), _)).Times(2);
    EXPECT_CALL(insertLocationsToNewLocationsStatement, write(1, 42, 23, 3));
    EXPECT_CALL(insertLocationsToNewLocationsStatement, write(2, 7, 11, 4));
    EXPECT_CALL(addNewSymbolsToSymbolsStatement, execute());
    EXPECT_CALL(syncNewSymbolsFromSymbolsStatement, execute());
    EXPECT_CALL(syncSymbolsIntoNewLocationsStatement, execute());
    EXPECT_CALL(deleteAllLocationsFromUpdatedFilesStatement, execute());
    EXPECT_CALL(insertNewLocationsInLocationsStatement, execute());
    EXPECT_CALL(deleteNewSymbolsTableStatement, execute());
    EXPECT_CALL(deleteNewLocationsTableStatement, execute());

    storage.addSymbolsAndSourceLocations(symbolEntries, sourceLocations);
}

TEST_F(SymbolStorage, ConvertStringsToJson)
{
    Utils::SmallStringVector strings{"foo", "bar", "foo"};

    auto jsonText = storage.toJson(strings);

    ASSERT_THAT(jsonText, Eq("[\"foo\",\"bar\",\"foo\"]"));
}

TEST_F(SymbolStorage, InsertProjectPart)
{
    InSequence sequence;
    ON_CALL(mockDatabase, lastInsertedRowId()).WillByDefault(Return(1));

    EXPECT_CALL(mockDatabase, setLastInsertedRowId(-1));
    EXPECT_CALL(insertProjectPartStatement,
                write(TypedEq<Utils::SmallStringView>("project"),
                      TypedEq<Utils::SmallStringView>("[\"foo\"]"),
                      TypedEq<Utils::SmallStringView>("[\"FOO\"]")));
    EXPECT_CALL(mockDatabase, lastInsertedRowId());

    storage.insertOrUpdateProjectPart("project",  {"foo"}, {"FOO"});
}

TEST_F(SymbolStorage, UpdateProjectPart)
{
    InSequence sequence;
    ON_CALL(mockDatabase, lastInsertedRowId()).WillByDefault(Return(-1));

    EXPECT_CALL(mockDatabase, setLastInsertedRowId(-1));
    EXPECT_CALL(insertProjectPartStatement,
                write(TypedEq<Utils::SmallStringView>("project"),
                      TypedEq<Utils::SmallStringView>("[\"foo\"]"),
                      TypedEq<Utils::SmallStringView>("[\"FOO\"]")));
    EXPECT_CALL(mockDatabase, lastInsertedRowId());
    EXPECT_CALL(updateProjectPartStatement,
                write(TypedEq<Utils::SmallStringView>("[\"foo\"]"),
                      TypedEq<Utils::SmallStringView>("[\"FOO\"]"),
                      TypedEq<Utils::SmallStringView>("project")));

    storage.insertOrUpdateProjectPart("project",  {"foo"}, {"FOO"});
}

TEST_F(SymbolStorage, UpdateProjectPartSources)
{
    InSequence sequence;

    EXPECT_CALL(getProjectPartIdStatement, valueReturnInt32(TypedEq<Utils::SmallStringView>("project"))).WillRepeatedly(Return(42));
    EXPECT_CALL(deleteAllProjectPartsSourcesWithProjectPartIdStatement, write(TypedEq<int>(42)));
    EXPECT_CALL(insertProjectPartSourcesStatement, write(TypedEq<int>(42), TypedEq<int>(1)));
    EXPECT_CALL(insertProjectPartSourcesStatement, write(TypedEq<int>(42), TypedEq<int>(2)));

    storage.updateProjectPartSources("project", {{1, 1}, {1, 2}});
}

TEST_F(SymbolStorage, InsertOrUpdateUsedMacros)
{
    InSequence sequence;

    EXPECT_CALL(insertIntoNewUsedMacrosStatement, write(TypedEq<uint>(42), TypedEq<Utils::SmallStringView>("FOO")));
    EXPECT_CALL(insertIntoNewUsedMacrosStatement, write(TypedEq<uint>(43), TypedEq<Utils::SmallStringView>("BAR")));
    EXPECT_CALL(syncNewUsedMacrosStatement, execute());
    EXPECT_CALL(deleteOutdatedUsedMacrosStatement, execute());
    EXPECT_CALL(deleteNewUsedMacrosTableStatement, execute());

    storage.insertOrUpdateUsedMacros({{"FOO", {1, 42}}, {"BAR", {1, 43}}});
}

TEST_F(SymbolStorage, InsertFileStatuses)
{
    EXPECT_CALL(insertFileStatuses, write(TypedEq<uint>(42), TypedEq<uint>(1), TypedEq<uint>(2)));
    EXPECT_CALL(insertFileStatuses, write(TypedEq<uint>(43), TypedEq<uint>(4), TypedEq<uint>(5)));

    storage.insertFileStatuses({{{1, 42}, 1, 2}, {{1, 43}, 4, 5}});
}

TEST_F(SymbolStorage, InsertOrUpdateSourceDependencies)
{
    InSequence sequence;

    EXPECT_CALL(insertIntoNewSourceDependenciesStatement, write(TypedEq<int>(42), TypedEq<int>(1)));
    EXPECT_CALL(insertIntoNewSourceDependenciesStatement, write(TypedEq<int>(42), TypedEq<int>(2)));
    EXPECT_CALL(syncNewSourceDependenciesStatement, execute());
    EXPECT_CALL(deleteOutdatedSourceDependenciesStatement, execute());
    EXPECT_CALL(deleteNewSourceDependenciesStatement, execute());

    storage.insertOrUpdateSourceDependencies({{{1, 42}, {1, 1}}, {{1, 42}, {1, 2}}});
}

TEST_F(SymbolStorage, FetchProjectPartArtefactCallsValueInStatement)
{
    EXPECT_CALL(getProjectPartCompilerArgumentsAndMacroNames, valueReturnProjectPartArtefact(1))
            .WillRepeatedly(Return(artefact));

    storage.fetchProjectPartArtefact({2, 1});
}

TEST_F(SymbolStorage, FetchProjectPartArtefactReturnArtefact)
{
    EXPECT_CALL(getProjectPartCompilerArgumentsAndMacroNames, valueReturnProjectPartArtefact(1))
            .WillRepeatedly(Return(artefact));

    auto result = storage.fetchProjectPartArtefact({2, 1});

    ASSERT_THAT(result, Eq(artefact));
}
}

