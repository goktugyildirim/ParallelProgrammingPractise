#include "CudaPractise.h"


namespace CUDA_Interface{

    struct Transform
    {
        Transform(thrust::device_vector<float> mat_d)
        {

        }

        __host__ __device__
        thrust::tuple<float, float, float>  operator()(const thrust::tuple<float, float, float>& input)
        {
            const float& x = thrust::get<0>(input);
            const float& y = thrust::get<0>(input);
            const float& z = thrust::get<0>(input);

            /*
            float x_t = mat_point_transformer[0]*x + mat_point_transformer[1]*y + mat_point_transformer[2]*z + mat_point_transformer[3]*1;
            float y_t = mat_point_transformer[4]*x + mat_point_transformer[5]*y + mat_point_transformer[6]*z + mat_point_transformer[7]*1;
            float z_t = mat_point_transformer[8]*x + mat_point_transformer[9]*y + mat_point_transformer[10]*z + mat_point_transformer[11]*1;
            */
            return thrust::make_tuple(x,y,z);
        }


    };


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

        thrust::transform(input_begin, input_end, output_begin, Transform(mat_d));
    }

}