#pragma once
#include<vector>
#include<stdexcept>

class Tensor
{
    private:
        std::vector<float> data;
        std::vector<int> shape;
    public:

        Tensor()= default;
        Tensor(const std::vector<int>& shape);
        Tensor(const std::vector<int>& shape ,const std::vector<float>& intialdata);

        Tensor add(const Tensor& other) const;
        Tensor matmul(const Tensor& other) const;


        const std::vector<int>& getshape() const;
        const std::vector<float>& getdata() const;

        Tensor softmax() const;
        Tensor relu() const;
        Tensor sigmoid() const;
        Tensor tanh_activation() const;
};