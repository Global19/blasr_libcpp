/*
 * =====================================================================================
 *
 *       Filename:  CCSIterator_gtest.cpp
 *
 *    Description:  Test alignment/files/CCSIterator.hpp
 *
 *        Version:  1.0
 *        Created:  11/29/2012 04:51:02 PM
 *       Revision:  08/20/2014
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * =====================================================================================
 */

#include <gtest/gtest.h>

#include <pbdata/testdata.h>
#include <alignment/files/CCSIterator.hpp>
#include <hdf/HDFRegionTableReader.hpp>
#include <pbdata/reads/RegionTable.hpp>

class CCSIteratorTestFixture : public testing::Test
{
public:
    CCSIteratorTestFixture() {}

    void SetUp()
    {
        fileName = baxFile2;
        reader = new HDFRegionTableReader();
        ccs = new CCSSequence();
        rgn = new RegionTable();

        int rev = reader->Initialize(fileName);
        EXPECT_TRUE(rev);
        reader->ReadTable(*rgn);
        reader->Close();
    }

    void TearDown()
    {
        if (reader) delete reader;
        if (ccs) delete ccs;
        if (rgn) delete rgn;
    }

    ~CCSIteratorTestFixture() {}

    std::string fileName;
    HDFRegionTableReader* reader;
    CCSSequence* ccs;
    RegionTable* rgn;
    CCSIterator it;
};

TEST_F(CCSIteratorTestFixture, Initialize) {}
