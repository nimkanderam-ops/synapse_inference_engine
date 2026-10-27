#include "core/tensor.hpp"
#include<cmath>
#include<algorithm>
#include<stdexcept>

Tensor::Tensor(const std::vector<int>& shape): shape(shape)
{
    int totalsize=1;
    for(int dim : shape)
    {
        totalsize *=dim;
    }
    data.resize(totalsize,0.0f);
}

Tensor::Tensor(const std::vector<int>& shape , const std::vector<float>& initialdata) : data(initialdata) , shape(shape)
{
    int totalsize=1;
    for(int dim : shape)
    {
        totalsize*=dim;
    }
    if(totalsize != static_cast<int>(data.size()))
    {
        throw std::invalid_argument("the shape and data do not match");
    }

}

const std::vector<float>& Tensor::getdata() const {return data ;}
const std::vector<int>& Tensor::getshape() const { return shape ;}

Tensor Tensor::add(const Tensor& other) const
{
    if(shape!=other.shape)
    {
        throw std::invalid_argument("...");
    }

    Tensor result(shape);
    for(size_t i=0;i<data.size();++i)
    {
        result.data[i]= data[i] + other.data[i];
    }
    return result;
}

Tensor Tensor::matmul(const Tensor& other ) const
{
    if (shape.size()!=2 || other.shape.size()!=2 )
    {
        throw std::invalid_argument("matrix shall have shape 2 for multiplication");
    } 

    int m=shape[0];
    int K=shape[1];
    int other_K=other.shape[0];
    int n=other.shape[1];

    if(K!=other_K)
    {
        throw std::invalid_argument("inner dimensions must match for matrix multiplication");
    }

    Tensor result({m,n});

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            float sum=0.0f;
            for(int k=0;k<K;++k)
            {
                sum+= data[i*K+k] * other.data[k*n+j];
            }
            result.data[i*n+j]=sum;
        }
    }
    return result;
}

Tensor Tensor::relu() const
{
    Tensor result(shape);
    for(size_t i=0;i<data.size();++i)
    {
        result.data[i]=std::max(0.0f, data[i]);
    }
    return result;
}

Tensor Tensor::softmax() const
{

    Tensor result(shape);

    if(data.empty()) return result;

    float max_value=*std::max_element(data.begin(),data.end());

    float sum=0.0f;

    for(size_t i=0;i<data.size();++i)
    {

        result.data[i]=std::exp(data[i]-max_value);
        sum+=result.data[i];
    }
    
    for(size_t i=0;i<data.size();++i)
    {
        result.data[i]/=sum;
    }

    return result;
}

Tensor Tensor::sigmoid() const
{
    std::vector<float> result(data.size());
    for(size_t i=0;i<data.size();++i)
    {
        result[i]=1.0f/(1.0f + std::exp(-data[i]));
    }
    return Tensor(shape,result);
}

Tensor Tensor::tanh_activation() const
{
    std::vector<float> result(data.size());
    for(size_t i=0;i<data.size();++i)
    {
        result[i]=std::tanh(data[i]);
    }
    return Tensor(shape,result);
}