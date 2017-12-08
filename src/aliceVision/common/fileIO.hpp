// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/structures/mv_structures.hpp>

#include <fstream>

struct multiviewInputParams;

bool FileExists(const std::string& filePath);
bool FolderExists(const std::string& folderPath);

std::string mv_getFileNamePrefixRcTc(multiviewInputParams* mip, int rc, int tc);
std::string mv_getFileNamePrefix(multiviewInputParams* mip, int index);
std::string mv_getFileName(multiviewInputParams* mip, int index, int mv_file_type);
std::string mv_getFileName(multiviewInputParams* mip, int index, int mv_file_type, int scale);
FILE* mv_openFile(multiviewInputParams* mip, int index, int mv_file_type, const char* readWrite);
point3d load3x1MatrixFromFile(FILE* fi);
matrix3x3 load3x3MatrixFromFile(FILE* fi);
matrix3x4 load3x4MatrixFromFile(FILE* fi);
point3d loadPoint3dFromFile(FILE* fi);
int get2dPointsNum(int imgFileId, multiviewInputParams* mip);
int load2dPoints(point2d** _out, int imgFileId, multiviewInputParams* mip);
staticVector<point2d>* load2dPoints(int imgFileId, multiviewInputParams* mip);
void load2dPoints(staticVector<point2d>* out, int imgFileId, multiviewInputParams* mip);
void memcpyRGBImageFromFileToArr(int camId, Color* imgArr, const std::string& fileNameOrigStr, multiviewInputParams* mip,
                                 bool transpose, int scaleFactor, int bandType);
struct seed_io_block            // 80 bytes
{
    orientedPoint op;           // 28 bytes
    point3d xax;                // 12 bytes
    point3d yax;                // 12 bytes
    float pixSize;              // 4 bytes
    uint64_t area;              // 8 bytes
    uint64_t segId;             // 8 bytes
    unsigned short ncams;       // 2 bytes
    unsigned short padding[3];  // 6 bytes
};

void saveSeedsToFile(staticVector<seedPoint>* seeds, const std::string& fileName);
void saveSeedsToFile(staticVector<seedPoint>* seeds, int refImgFileId, multiviewInputParams* mip, int mv_file_type);
bool loadSeedsFromFile(staticVector<seedPoint>** seeds, const std::string& fileName);
bool loadSeedsFromFile(staticVector<seedPoint>** seeds, int refImgFileId, multiviewInputParams* mip, int mv_file_type);
int getSeedsSizeFromFile(int refImgFileId, multiviewInputParams* mip, int mv_file_type);
//int getGrowedSizeFromFile(int refImgFileId, multiviewInputParams* mip);

void saveUniqueIdAliveToFile(std::vector<bool>* uniqueIdAlive, multiviewInputParams* mip);
void loadUniqueIdAliveFromFile(std::vector<bool>* uniqueIdAlive, multiviewInputParams* mip);
void deletePremtachFiles(multiviewInputParams mip, int ncams);
void deleteFilesOfType(multiviewInputParams& mip, int ncams, int mv_file_type);
void saveOrientedPointsToFile(staticVector<orientedPoint>* ops, int refImgFileId, multiviewInputParams* mip);
staticVector<orientedPoint>* loadOrientedPointsFromFile(int refImgFileId, multiviewInputParams* mip);
int getNumOrientedPointsFromFile(int refImgFileId, multiviewInputParams* mip);
bool loadPairConfidenceMatrixFromFileWithAllocation(unsigned char** cm, multiviewInputParams* mip,
                                                    const std::string& name);
void savePairConfidenceMatrixToFile(unsigned char* cm, int32_t size, multiviewInputParams* mip,
                                    const std::string& name);
struct outStruct
{
    orientedPoint op;
    int tarFeatId;

    outStruct()
    {
        op = orientedPoint();
        tarFeatId = -1;
    }

    outStruct& operator=(const outStruct param)
    {
        op = param.op;
        tarFeatId = param.tarFeatId;
        return *this;
    }
};

void savePrematchedToFile(outStruct* outv, int size, int refImgFileId, int tarImgFileId, multiviewInputParams* mip);
outStruct* loadPrematchedFromFile(int* sz, int refImgFileId, int tarImgFileId, multiviewInputParams* mip);

//bool loadAgreedVisMapToFileFromFileWithoutAllocation(idValue* vm, int refImgFileId, multiviewInputParams* mip);
//bool saveAgreedVisMapToFile(idValue* vm, int refImgFileId, multiviewInputParams* mip);
//bool loadDiskSizeMapFromFileWithoutAllocation(int* vm, int refImgFileId, multiviewInputParams* mip);
//bool saveDiskSizeMapToFile(int* vm, int refImgFileId, multiviewInputParams* mip);

void deleteAllFiles(multiviewInputParams* mip);
bool getDepthMapInfo(int refImgFileId, multiviewInputParams* mip, float& mindepth, float& maxdepth,
                     staticVector<int>** tcams);
bool getDepthMapInfoDepthLimits(int refImgFileId, multiviewInputParams* mip, float& mindepth, float& maxdepth);
bool DeleteDirectory(const std::string& sPath);
bool getDirectoryFiles(std::vector<std::string>& out, const std::string& sPath, const std::string& ext);

typedef struct SiftKeypoint
{
    float x, y, s, o; // x, y, scale, orientation.
} SiftKeypoint;

void readSifts(const std::string& fileName, staticVector<float>** descriptors, staticVector<SiftKeypoint>** keys);

void splitString(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens);
