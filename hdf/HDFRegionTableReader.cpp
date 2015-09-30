#include <cassert>
#include "HDFRegionTableReader.hpp"

using namespace std;

int HDFRegionTableReader::Initialize(string &regionTableFileName, 
        const H5::FileAccPropList & fileAccPropList) {
    /*
     * Initialize access to the HDF file.
     */
    try {
        regionTableFile.Open(regionTableFileName.c_str(), H5F_ACC_RDONLY, fileAccPropList);
    }
    catch (H5::Exception &e) {
        cout << e.getDetailMsg() << endl;
        return 0;
    }
    if (pulseDataGroup.Initialize(regionTableFile.rootGroup, "PulseData") == 0) {
        return 0;
    }
    if (pulseDataGroup.ContainsObject("Regions") == 0) {
        fileContainsRegionTable = false;
        return 0;
    }
    else {
        fileContainsRegionTable = true;
    }

    if (regions.Initialize(pulseDataGroup, "Regions") == 0) {
        return 0;
    }

    if (columnNames.Initialize(regions, "ColumnNames") == 0) {
        return 0;
    }
    if (regionTypes.Initialize(regions, "RegionTypes") == 0) {
        return 0;
    }
    if (regionDescriptions.Initialize(regions, "RegionDescriptions") == 0) {
        return 0;
    }
    if (regionSources.Initialize(regions,  "RegionSources") == 0) {
        return 0;
    }

    nRows = regions.GetNRows();
    isInitialized_ = true;
    curRow = 0;
    return 1;
}

bool HDFRegionTableReader::IsInitialized(void) const {
    return isInitialized_;
}

bool HDFRegionTableReader::HasRegionTable(void) const {
    assert(IsInitialized() or false == "HDFRegionTable is not initialize!");
    return fileContainsRegionTable;
}

int HDFRegionTableReader::GetNext(RegionAnnotation &annotation) {
    assert(IsInitialized() or false == "HDFRegionTable is not initialize!");
    //
    // Bail with no-op if this is the last row.
    //
    if (fileContainsRegionTable == false) {
        return 0;
    }

    if (curRow == nRows) {
        return 0;
    }

    regions.Read(curRow, curRow+1, annotation.row);
    ++curRow;
    return 1;
}	

void HDFRegionTableReader::RegionTypesToMap(RegionTable &table) {
    size_t i;
    table.regionTypeEnums.resize(table.regionTypes.size());
    for (i = 0;i < table.regionTypes.size(); i++) {
        if (table.regionTypes[i] == "HQRegion") {
            table.regionTypeEnums[i] = HQRegion;
        }
        else if (table.regionTypes[i] == "Adapter") {
            table.regionTypeEnums[i] = Adapter;
        }
        else if (table.regionTypes[i] == "Insert") {
            table.regionTypeEnums[i] = Insert;
        }
        else if (table.regionTypes[i] == "Accuracy") {
            table.regionTypeEnums[i] = Insert;
        }
        else {
            cout << "ERROR! Region Type " << table.regionTypes[i] << " is not supported.  Check Enumerations.h" << endl;
            assert(0);
        }
    }
}

int HDFRegionTableReader::ReadTableAttributes(RegionTable &table) {
    assert(IsInitialized() or false == "HDFRegionTable is not initialize!");
    if (fileContainsRegionTable == false) {
        return 0;
    }
    columnNames.Read(table.columnNames);
    regionTypes.Read(table.regionTypes);
    RegionTypesToMap(table);
    regionDescriptions.Read(table.regionDescriptions);
    regionSources.Read(table.regionSources);
    // All ok.
    return 1;
}

void HDFRegionTableReader::Close() {
    isInitialized_ = false;
    fileContainsRegionTable = false;
    columnNames.Close();
    regionTypes.Close();
    regionDescriptions.Close();
    regionSources.Close();
    pulseDataGroup.Close();
    regions.Close();
    regionTableFile.Close();
}

void HDFRegionTableReader::ReadTable(RegionTable &table) {
    assert(IsInitialized() or false == "HDFRegionTable is not initialize!");
    if (fileContainsRegionTable == false) {
        return;
    }
    ReadTableAttributes(table);
    table.table.resize(nRows);
    int i = 0;
    while(GetNext(table.table[curRow])) {
        i++;
    }
}

void HDFRegionTableReader::GetMinMaxHoleNumber(UInt &minHole,
                                               UInt &maxHole) {
    assert(IsInitialized() or false == "HDFRegionTable is not initialize!");
    // Hole numbers may not be sorted ascendingly, so do not
    // return the first and last hole numbers as the min and max.
    UInt saveCurRow = curRow;
    curRow = 0;
    bool init = false;
    RegionAnnotation annotation;
    while (GetNext(annotation) == 1) {
        UInt curHole = annotation.GetHoleNumber();
        if (not init) {
            minHole = maxHole = curHole;
            init = true;
        } else {
            minHole = (minHole > curHole)?(curHole):(minHole);
            maxHole = (maxHole < curHole)?(curHole):(maxHole);
        }
    }
    curRow = saveCurRow;
}
