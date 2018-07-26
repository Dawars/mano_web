#include <iostream>
#include <array>
#include <emscripten/emscripten.h>
//#include "mano/joints.h"
//#include "mano/weights.h"
#include "mano/indices.h"
#include "mano/mean.h"
#include "mano/shapes.h"
//#include "mano/poses.h"
//#include "mano/jreg.h"

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

const int numShapeParams = 10;
const int numPoseParams = 135; // 15*3*3

using MatMap = Eigen::Map<Eigen::Matrix<float, numVertices, 3, Eigen::RowMajor> >;
using JregMatMap = Eigen::Map<Eigen::Matrix<float, 16, 10, Eigen::RowMajor>>;

Eigen::MatrixXf manoVertices = MatMap(&meanShape[0][0]);
Eigen::MatrixXf shapeBS[numShapeParams] = {
        MatMap(&sBlendshapes[0][0][0]),
        MatMap(&sBlendshapes[1][0][0]),
        MatMap(&sBlendshapes[2][0][0]),
        MatMap(&sBlendshapes[3][0][0]),
        MatMap(&sBlendshapes[4][0][0]),
        MatMap(&sBlendshapes[5][0][0]),
        MatMap(&sBlendshapes[6][0][0]),
        MatMap(&sBlendshapes[7][0][0]),
        MatMap(&sBlendshapes[8][0][0]),
        MatMap(&sBlendshapes[9][0][0]),
};

/*
Eigen::MatrixXf jregMatrices[3] = {
    JregMatMap(&jreg[0][0][0]),
    JregMatMap(&jreg[1][0][0]),
    JregMatMap(&jreg[2][0][0])
};

Eigen::MatrixXf poseBS[numPoseParams];
Eigen::VectorXf zeroPoseRot;*/


int main() {

#ifdef EIGEN_VECTORIZE
    std::cout << "Vectorization enabled" << std::endl;
#endif

    EM_ASM(
            console.log("HandVR");
    );

    return 0;
}


extern "C" {
void debugBuffer(float *buff) {
    std::cout << buff[0] << "\t" << buff[1] << "\t" << buff[2] << "\n";
    std::cout << buff[1 * 3 + 0] << "\t" << buff[1 * 3 + 1] << "\t" << buff[1 * 3 + 2] << "\n";
    std::cout << buff[2 * 3 + 0] << "\t" << buff[2 * 3 + 1] << "\t" << buff[2 * 3 + 2] << "\n";
    std::cout << "---------------\n";
}
}


void calcShape(MatMap &geometry, float *shapeParams) {
    for (size_t j = 0; j < numShapeParams; ++j) {
        geometry += shapeParams[j] * shapeBS[j];
    }
}


//WASM can't handle C++ name mangling, so it can only call functions from extern "C" blocks form where we can call C++ code (I just assume this is true but I never tried)
void manoDummy(float *geometry, float *shapeParams, float *poseParams) {
    //template
    MatMap geom = MatMap{geometry}; // wrap buffer in Eigen Matrix, doesn't copy data

    geom = manoVertices; // init with mano template verts

    // shape
    calcShape(geom, shapeParams);
}

extern "C" {

void EMSCRIPTEN_KEEPALIVE calcHandVertices(float *geometry, float *shapeParams, float *poseParams) {
    manoDummy(geometry, shapeParams, poseParams);
}

// todo blend weights

int EMSCRIPTEN_KEEPALIVE getNumVertices() {
    return numVertices;
}

const size_t EMSCRIPTEN_KEEPALIVE getNumPoseParams() {
    return numPoseParams;
}

// todo combine these two:
unsigned short *EMSCRIPTEN_KEEPALIVE getIndexBuffer() {
    return faces;
}
size_t EMSCRIPTEN_KEEPALIVE getIndexBufferSize() {
    return facesSize;
}
}
