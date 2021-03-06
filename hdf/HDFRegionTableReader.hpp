#ifndef _BLASR_HDF_REGION_TABLE_READER_HPP_
#define _BLASR_HDF_REGION_TABLE_READER_HPP_

#include <string>
#include <vector>

#include <H5Cpp.h>

#include <hdf/HDF2DArray.hpp>
#include <hdf/HDFArray.hpp>
#include <hdf/HDFAtom.hpp>
#include <hdf/HDFFile.hpp>
#include <pbdata/reads/RegionTable.hpp>

class HDFRegionTableReader
{
private:
    HDFFile regionTableFile;
    HDFGroup pulseDataGroup;
    HDF2DArray<int> regions;

    HDFAtom<std::vector<std::string> > regionTypes;
    HDFAtom<std::vector<std::string> > regionDescriptions;
    HDFAtom<std::vector<std::string> > regionSources;
    HDFAtom<std::vector<std::string> > columnNames;

    int curRow;

    bool isInitialized_;  // whether or not this reader is initialized.

    int nRows;

    bool fileContainsRegionTable;

public:
    HDFRegionTableReader(void)
        : curRow(0), isInitialized_(false), nRows(0), fileContainsRegionTable(false)
    {
    }

    int Initialize(std::string &regionTableFileName,
                   const H5::FileAccPropList &fileAccPropList = H5::FileAccPropList::DEFAULT);

    bool IsInitialized(void) const;

    bool HasRegionTable(void) const;

    void GetMinMaxHoleNumber(UInt &minHole, UInt &maxHole);

    void ReadTable(RegionTable &table);

    void Close();

private:
    int GetNext(RegionAnnotation &annotation);
};

#endif
