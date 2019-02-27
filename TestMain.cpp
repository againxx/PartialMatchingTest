#include <iostream>
#include "SingleModeDatasetGenerator.h"
#include "ModelDataset.h"
#include "PartialMatchingFacada.h"
#include "SegmentedPatch.h"
#include "MatchingResultParser.h"

int main(int argc, char *argv[])
{
    SingleModeDatasetGenerator datasetGenerator;
    // TODO: Replace these two paths with your own /path/to/point_cloud.ply and /path/to/generated_dataset
    std::string pointCloudDir = "/home/ustc-1314/ProjectData/testRoom6/";
    std::string datasetDir = "/home/ustc-1314/ProjectData/testRoom6_Dataset/";
    datasetGenerator.generate(pointCloudDir, datasetDir);

    // TODO: Replace this .ply file with your test model
    SegmentedPatch patch("/home/ustc-1314/ProjectData/testRoom6/chair_0003_del.ply");

    PartialMatchingFacada partialMatching(datasetDir);
    partialMatching.setPartialMatchingAlgorithm(PartialMatchingFacada::BOW_ALGORITHM); // using bag of words method
    MatchingResultParser matchingResult = partialMatching.getMatchingResult(patch);

    // TODO: Use setCandidateCount to adjust output model number, default 5
    // partialMatching.setCandidateCount(5);

    for (int i = 0; i < matchingResult.matchNum; ++i)
    {
        std::cout << matchingResult.modelNames[i] << std::endl;
        std::cout << matchingResult.transformationMatrixs[i] << std::endl;
        std::cout << matchingResult.errors[i] << std::endl;
    }
    return 0;
}