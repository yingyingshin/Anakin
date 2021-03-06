#include "framework/operators/input.h"

namespace anakin {

namespace ops {

template<>
void Input<NV, AK_FLOAT, Precision::FP32>::operator()(OpContext<NV>& ctx,
        const std::vector<Tensor4dPtr<NV, AK_FLOAT>>& ins,
        std::vector<Tensor4dPtr<NV, AK_FLOAT>>& outs) {
}


/// TODO ... specialization other type of operator


/// set helper
template<typename Ttype, DataType Dtype, Precision Ptype>
InputHelper<Ttype, Dtype, Ptype>::~InputHelper() {
}

template<typename Ttype, DataType Dtype, Precision Ptype>
Status InputHelper<Ttype, Dtype, Ptype>::InitParam() {
    DLOG(WARNING) << "Parsing Input op parameter.";
    input_shape = GET_PARAMETER(PTuple<int>, input_shape);

    for (int i = 0; i < input_shape.size(); i++) {
        LOG(INFO) << " |-- shape [" << i << "]: " << input_shape[i];
    }

    return Status::OK();
}

template<typename Ttype, DataType Dtype, Precision Ptype>
Status InputHelper<Ttype, Dtype, Ptype>::Init(OpContext<Ttype>& ctx,
        const std::vector<Tensor4dPtr<Ttype, Dtype>>& ins,
        std::vector<Tensor4dPtr<Ttype, Dtype>>& outs) {
    return Status::OK();
}

template<typename Ttype, DataType Dtype, Precision Ptype>
Status InputHelper<Ttype, Dtype, Ptype>::InferShape(const std::vector<Tensor4dPtr<Ttype, Dtype> >&
        ins,
        std::vector<Tensor4dPtr<Ttype, Dtype> >& outs) {
    saber::Shape out_shape;

    for (int i = 0; i < input_shape.size(); i++) {
        out_shape.push_back(input_shape[i]);
    }

    for (auto& tensor_p : outs) {
        tensor_p->set_shape(out_shape);
    }

    return Status::OK();
}

template class InputHelper<NV, AK_FLOAT, Precision::FP32>;
template class InputHelper<NV, AK_FLOAT, Precision::FP16>;
template class InputHelper<NV, AK_FLOAT, Precision::INT8>;

template class InputHelper<ARM, AK_FLOAT, Precision::FP32>;
template class InputHelper<ARM, AK_FLOAT, Precision::FP16>;
template class InputHelper<ARM, AK_FLOAT, Precision::INT8>;

// register help
ANAKIN_REGISTER_OP_HELPER(Input, InputHelper, NV, AK_FLOAT, Precision::FP32);
ANAKIN_REGISTER_OP_HELPER(Input, InputHelper, NV, AK_FLOAT, Precision::FP16);
ANAKIN_REGISTER_OP_HELPER(Input, InputHelper, NV, AK_FLOAT, Precision::INT8);

ANAKIN_REGISTER_OP_HELPER(Input, InputHelper, ARM, AK_FLOAT, Precision::FP32);
ANAKIN_REGISTER_OP_HELPER(Input, InputHelper, ARM, AK_FLOAT, Precision::FP16);
ANAKIN_REGISTER_OP_HELPER(Input, InputHelper, ARM, AK_FLOAT, Precision::INT8);

//! register op
ANAKIN_REGISTER_OP(Input)
.Doc("Input operator [ only a input data holder and reshape ] ")
.__alias__<NV, AK_FLOAT, Precision::FP32>("input")
.__alias__<ARM, AK_FLOAT, Precision::FP32>("input")
.Args<PTuple<int>>("input_shape", " shape of graph input.");

} /* namespace ops */

} /* namespace anakin */


