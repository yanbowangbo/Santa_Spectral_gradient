#include <vector>

#include "caffe/sgd_solvers.hpp"

namespace caffe {

template <typename Dtype>
void RMSPropSolver<Dtype>::ComputeUpdateValue(int param_id, Dtype rate) {
  /*const vector<Blob<Dtype>*>& net_params = this->net_->learnable_params();
  const vector<float>& net_params_lr = this->net_->params_lr();

  // get the learning rate
  Dtype delta = this->param_.delta();
  Dtype rms_decay = this->param_.rms_decay();
  Dtype local_rate = rate * net_params_lr[param_id];

  switch (Caffe::mode()) {
  case Caffe::CPU:
    // compute square of gradient in update
    caffe_powx(net_params[param_id]->count(),
        net_params[param_id]->cpu_diff(), Dtype(2),
        this->update_[param_id]->mutable_cpu_data());

    // update history
    caffe_cpu_axpby(net_params[param_id] -> count(),
        Dtype(1-rms_decay), this->update_[param_id]->cpu_data(),
        rms_decay, this->history_[param_id]-> mutable_cpu_data());

    // prepare update
    caffe_powx(net_params[param_id]->count(),
        this->history_[param_id]->cpu_data(), Dtype(0.5),
        this->update_[param_id]->mutable_cpu_data());

    caffe_add_scalar(net_params[param_id]->count(),
        delta, this->update_[param_id]->mutable_cpu_data());

    caffe_div(net_params[param_id]->count(),
        net_params[param_id]->cpu_diff(), this->update_[param_id]->cpu_data(),
        this->update_[param_id]->mutable_cpu_data());

    // scale and copy
    caffe_cpu_axpby(net_params[param_id]->count(), local_rate,
        this->update_[param_id]->cpu_data(), Dtype(0),
        net_params[param_id]->mutable_cpu_diff());
    break;
  case Caffe::GPU:
#ifndef CPU_ONLY
    // compute square of gradient in update
    caffe_gpu_powx(net_params[param_id]->count(),
        net_params[param_id]->gpu_diff(), Dtype(2),
        this->update_[param_id]->mutable_gpu_data());

    // update history
    caffe_gpu_axpby(net_params[param_id] -> count(),
        Dtype(1-rms_decay), this->update_[param_id]->gpu_data(),
        rms_decay, this->history_[param_id]-> mutable_gpu_data());

    // prepare update
    caffe_gpu_powx(net_params[param_id]->count(),
        this->history_[param_id]->gpu_data(), Dtype(0.5),
        this->update_[param_id]->mutable_gpu_data());

    caffe_gpu_add_scalar(net_params[param_id]->count(),
        delta, this->update_[param_id]->mutable_gpu_data());

    caffe_gpu_div(net_params[param_id]->count(),
        net_params[param_id]->gpu_diff(), this->update_[param_id]->gpu_data(),
        this->update_[param_id]->mutable_gpu_data());

    caffe_gpu_axpby(net_params[param_id]->count(), local_rate,
        this->update_[param_id]->gpu_data(), Dtype(0),
        net_params[param_id]->mutable_gpu_diff());*/
  const vector<Blob<Dtype>*>& net_params = this->net_->learnable_params();
  const vector<float>& net_params_lr = this->net_->params_lr();

  // get the learning rate
  Dtype delta = this->param_.delta();
  Dtype rms_decay = this->param_.rms_decay();
  Dtype local_rate = rate * net_params_lr[param_id];

  switch (Caffe::mode()) {
  case Caffe::CPU:
    // compute square of gradient in update
    caffe_powx(net_params[param_id]->count(),
        net_params[param_id]->cpu_diff(), Dtype(2),
        this->update_[param_id]->mutable_cpu_data());

    // update history
    caffe_cpu_axpby(net_params[param_id] -> count(),
        Dtype(1-rms_decay), this->update_[param_id]->cpu_data(),
        rms_decay, this->history_[param_id]-> mutable_cpu_data());

    // prepare update
    caffe_powx(net_params[param_id]->count(),
        this->history_[param_id]->cpu_data(), Dtype(0.5),
        this->update_[param_id]->mutable_cpu_data());

    caffe_add_scalar(net_params[param_id]->count(),
        delta, this->update_[param_id]->mutable_cpu_data());

    //gaussian noise
    //caffe_rng_gaussian(net_params[param_id]->count(), Dtype(0), Dtype(1), this->temp_[param_id]->mutable_cpu_data());
    //caffe_powx(net_params[param_id]->count(),
    //		this->temp_[param_id]->cpu_data(), Dtype(2),
    //		this->temp_[param_id]->mutable_cpu_data());
    //caffe_div(net_params[param_id]->count(),
    //		this->temp_[param_id]->cpu_data(), this->update_[param_id]->cpu_data(),
    //		this->temp_[param_id]->mutable_cpu_data());
    //caffe_scal(net_params[param_id]->count(), Dtype(local_rate / 3000000),
    //		this->temp_[param_id]->mutable_cpu_data());
    //caffe_powx(net_params[param_id]->count(),
    //		this->temp_[param_id]->cpu_data(), Dtype(0.5),
    //    	this->temp_[param_id]->mutable_cpu_data());
    //////

    caffe_div(net_params[param_id]->count(),
        net_params[param_id]->cpu_diff(), this->update_[param_id]->cpu_data(),
        this->update_[param_id]->mutable_cpu_data());

    // scale and copy
    caffe_cpu_axpby(net_params[param_id]->count(), local_rate,
        this->update_[param_id]->cpu_data(), Dtype(0),
        net_params[param_id]->mutable_cpu_diff());

    //caffe_cpu_axpby(net_params[param_id]->count(), Dtype(1),
    //    this->temp_[param_id]->cpu_data(), Dtype(1),
    //    net_params[param_id]->mutable_cpu_diff());

    break;
  case Caffe::GPU:
#ifndef CPU_ONLY
    // compute square of gradient in update
    caffe_gpu_powx(net_params[param_id]->count(),
        net_params[param_id]->gpu_diff(), Dtype(2),
        this->update_[param_id]->mutable_gpu_data());

    // update history
    caffe_gpu_axpby(net_params[param_id] -> count(),
        Dtype(1-rms_decay), this->update_[param_id]->gpu_data(),
        rms_decay, this->history_[param_id]-> mutable_gpu_data());

    // prepare update
    caffe_gpu_powx(net_params[param_id]->count(),
        this->history_[param_id]->gpu_data(), Dtype(0.5),
        this->update_[param_id]->mutable_gpu_data());

    caffe_gpu_add_scalar(net_params[param_id]->count(),
        delta, this->update_[param_id]->mutable_gpu_data());

    //gaussian noise
	//LOG(INFO) << "gaussian start";
    //caffe_gpu_rng_gaussian(net_params[param_id]->count(), Dtype(0), Dtype(1), this->temp_[param_id]->mutable_gpu_data());
//LOG(INFO) << "gaussian end";
    //caffe_gpu_powx(net_params[param_id]->count(),
    //		this->temp_[param_id]->gpu_data(), Dtype(2),
    //		this->temp_[param_id]->mutable_gpu_data());
    //caffe_gpu_div(net_params[param_id]->count(),
    //		this->temp_[param_id]->gpu_data(), this->update_[param_id]->gpu_data(),
    //		this->temp_[param_id]->mutable_gpu_data());
    //caffe_gpu_scal(net_params[param_id]->count(), Dtype(local_rate / 3000000),
    //		this->temp_[param_id]->mutable_gpu_data());
    //caffe_gpu_powx(net_params[param_id]->count(),
    //		this->temp_[param_id]->gpu_data(), Dtype(0.5),
    //    	this->temp_[param_id]->mutable_gpu_data());
    /////

    caffe_gpu_div(net_params[param_id]->count(),
        net_params[param_id]->gpu_diff(), this->update_[param_id]->gpu_data(),
        this->update_[param_id]->mutable_gpu_data());

    caffe_gpu_axpby(net_params[param_id]->count(), local_rate,
        this->update_[param_id]->gpu_data(), Dtype(0),
        net_params[param_id]->mutable_gpu_diff());

    //caffe_gpu_axpby(net_params[param_id]->count(), Dtype(1),
    //    this->temp_[param_id]->gpu_data(), Dtype(1),
    //    net_params[param_id]->mutable_gpu_diff());
#else
    NO_GPU;
#endif
    break;
  default:
    LOG(FATAL) << "Unknown caffe mode: " << Caffe::mode();
  }
}

INSTANTIATE_CLASS(RMSPropSolver);
REGISTER_SOLVER_CLASS(RMSProp);

}  // namespace caffe
