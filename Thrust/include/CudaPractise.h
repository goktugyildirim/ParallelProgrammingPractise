//
// Created by goktug on 14.12.2020.
//
#ifndef CUDA_PRACTISE_CUDAPRACTISE_H
#define CUDA_PRACTISE_CUDAPRACTISE_H

#include <cuda.h>

#include <thrust/for_each.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/iterator/zip_iterator.h>

namespace CUDA_Interface{

    typedef thrust::host_vector<float> inputType;

    void transformInDevice(inputType x, inputType y, inputType z, inputType mat_point_transformer);

}


#endif //CUDA_PRACTISE_CUDAPRACTISE_H
