#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "glm/glm.hpp"
#include "utilities.h"
#include "sceneStructs.h"

#include "bounds.h"
#include "bvh.h"

using namespace std;

// ----------------------------------------------------------------
//----------------------- Toggle Here -----------------------------
// ----------------------------------------------------------------

// Uncomment to enable mesh world bound
#define ENABLE_MESHWORLDBOUND

// Should first enable mesh world bound to enable BVH
// So far, since our scene is relatively simple
// all mesh(S) / all triangles -> one BVH tree
#define ENABLE_BVH

// ----------------------------------------------------------------
// ----------------------------------------------------------------

class Scene {
private:
    ifstream fp_in;
    int loadMaterial(string materialid);
    int loadGeom(string objectid);
    int loadCamera();

	int loadEnvironment();

	void loadObj(string objPath, Geom& newGeom, const glm::mat4& transform, const glm::mat4& invTranspose);

public:
    Scene(string filename);
    ~Scene();


	std::vector<Light> lights;
	std::vector<int> emitMaterialId;

    std::vector<Geom> geoms;
    std::vector<Material> materials;
    RenderState state;
	
	// used ONLY in mesh cases
	std::vector<Triangle> tris;
	std::vector<Bounds3f> worldBounds;

	// Texture part
	std::vector<Texture> textureMap;
	std::vector<Texture> normalMap;
	std::vector<Texture> EnvironmentMap;


#ifdef ENABLE_BVH
	LinearBVHNode *bvh_nodes; //Output
	int bvh_totalNodes;

#endif // ENABLE_BVH

};
