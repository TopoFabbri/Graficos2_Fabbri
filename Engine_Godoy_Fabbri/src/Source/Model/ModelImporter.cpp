// #include "ModelImporter.h"
//
// ToToEng::Model* ToToEng::ModelImporter::importModel(Renderer* renderer, std::string modelPath)
// {
//     Model* model = new Model(renderer);
//
//     Assimp::Importer importer;
//     const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
//
//     if (!scene)
//         return nullptr;
//
//     loadNode(model, scene->mRootNode, scene);
//     
//     return model;
// }
//
// ToToEng::Model* ToToEng::ModelImporter::importModel(Renderer* renderer, std::string modelPath, std::string diffusePath,
//     std::string specularPath)
// {
//     Model* model = new Model(renderer);
//
//     Assimp::Importer importer;
//     const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
//
//     if (!scene)
//         return nullptr;
//
//     loadNode(model, scene->mRootNode, scene);
//     loadMaterials(scene, diffusePath, specularPath);
//     
//     return model;
// }