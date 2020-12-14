#include "CudaPractise.h"



namespace CUDA_Interface{

    void transformInDevice(inputType x, inputType y, inputType z, inputType mat_point_transformer)
    {
        thrust::device_vector<float> x_d = x;
        thrust::device_vector<float> y_d = y;
        thrust::device_vector<float> z_d = z;
        thrust::device_vector<float> mat_d = mat_point_transformer;

        auto input_begin = thrust::make_zip_iterator(thrust::make_tuple(x_d.begin(), y_d.begin(), z_d.begin()));
        auto input_end = thrust::make_zip_iterator(thrust::make_tuple(x_d.end(), y_d.end(), z_d.end()));

        thrust::device_vector<float> x_d_transformed = x;
        thrust::device_vector<float> y_d_transformed = y;
        thrust::device_vector<float> z_d_transformed = z;

        auto output_begin = thrust::make_zip_iterator(thrust::make_tuple(x_d_transformed.begin(),
                            y_d_transformed.begin(), z_d_transformed.begin()));
        auto output_end = thrust::make_zip_iterator(thrust::make_tuple(x_d_transformed.end(),
                            y_d_transformed.end(), z_d_transformed.end()));

        auto transform = []()
        {

        };


    }

}