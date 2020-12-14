#include "CudaPractise.h"



#include <Eigen/Dense>

void transformInHost()
{

}

int main()
{
    Eigen::Matrix4f mat1;
    mat1 <<
    1, 1, 1, 1,
    1, 0, 1, 1,
    1, 1, 0, 1,
    1, 1, 1, 1;

    Eigen::MatrixXf mat2(4,1);
    mat2 << 1, 1, 1, 1;

    size_t cloud_size(100000);

    thrust::host_vector<Eigen::MatrixXf> points(cloud_size);

    for(size_t i=0; i<cloud_size; i++)
        points.push_back(mat2);

    thrust::host_vector<Eigen::Matrix4f> mat_point_transformers(cloud_size);

    for(size_t i=0; i<cloud_size; i++)
        mat_point_transformers.push_back(mat1);


    CUDA_Interface::transformInDevice();






return 0;
}
