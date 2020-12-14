#include "CudaPractise.h"

#include <Eigen/Dense>
#include <chrono>

void transformInHost(thrust::host_vector<float> x,
                     thrust::host_vector<float> y,
                     thrust::host_vector<float> z,
                     Eigen::Matrix4f mat_point_transformer
                     )
{

    auto start = std::chrono::high_resolution_clock::now();

    auto input_begin = thrust::make_zip_iterator(thrust::make_tuple(x.begin(), y.begin(), z.begin()));
    auto input_end = thrust::make_zip_iterator(thrust::make_tuple(x.end(), y.end(), z.end()));

    thrust::host_vector<float> transformed_x(x.size());
    thrust::host_vector<float> transformed_y(x.size());
    thrust::host_vector<float> transformed_z(x.size());

    auto output_begin = thrust::make_zip_iterator(thrust::make_tuple(transformed_x.begin(), transformed_y.begin(), transformed_z.begin()));
    auto output_end = thrust::make_zip_iterator(thrust::make_tuple(transformed_x.end(), transformed_y.end(), transformed_z.end()));

    auto transform = [mat_point_transformer](const auto& input)-> thrust::tuple<float, float, float>
    {
        float x = thrust::get<0>(input);
        float y = thrust::get<0>(input);
        float z = thrust::get<0>(input);

        auto m = mat_point_transformer.matrix();

        float x_t = m.coeff(0,0)*x + m.coeff(0,1)*y + m.coeff(0,2)*z + m.coeff(0,3)*1;
        float y_t = m.coeff(1,0)*x + m.coeff(1,1)*y + m.coeff(1,2)*z + m.coeff(1,3)*1;
        float z_t = m.coeff(2,0)*x + m.coeff(2,1)*y + m.coeff(2,2)*z + m.coeff(2,3)*1;

        return thrust::make_tuple(x_t, y_t, z_t);
    };

    thrust::transform(thrust::tbb::par, input_begin, input_end, output_begin, transform);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Cloud is transformed. Time: " <<  duration.count() << " microseconds." <<  std::endl;
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

    size_t cloud_size = 1000000;

    thrust::host_vector<float> x(cloud_size);
    thrust::host_vector<float> y(cloud_size);
    thrust::host_vector<float> z(cloud_size);

    for(size_t i=0; i<cloud_size; i++)
    {
        x.push_back(mat2.matrix().coeff(0,0));
        y.push_back(mat2.matrix().coeff(0,0));
        z.push_back(mat2.matrix().coeff(0,0));
    }


    transformInHost(x, y, z, mat1);



    //CUDA_Interface::transformInDevice();






return 0;
}
