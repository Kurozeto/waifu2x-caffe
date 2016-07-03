#pragma once

#include <string>
#include "waifu2x.h"


class cNet
{
private:
	boost::shared_ptr<caffe::Net<float>> mNet;

	int mModelScale; // ���f�����ΏۂƂ���g�嗦
	int mInnerScale; // �l�b�g�����Ŋg�傳���{��
	int mNetOffset; // �l�b�g�ɓ��͂���Ƃǂꂭ�炢���邩
	int mInputPlane; // �l�b�g�ւ̓��̓`�����l����

private:
	Waifu2x::eWaifu2xError LoadParameterFromJson(const boost::filesystem::path &model_path, const boost::filesystem::path &param_path
		, const boost::filesystem::path &modelbin_path, const boost::filesystem::path &caffemodel_path, const std::string &process);
	Waifu2x::eWaifu2xError LoadInfoFromJson(const boost::filesystem::path &info_path);
	Waifu2x::eWaifu2xError SetParameter(caffe::NetParameter &param, const std::string &process) const;

public:
	cNet();
	~cNet();

	Waifu2x::eWaifu2xError ConstractNet(const boost::filesystem::path &model_path, const boost::filesystem::path &param_path, const boost::filesystem::path &info_path, const std::string &process);

	int GetInputPlane() const;
	int GetInnerScale() const;
	int GetNetOffset() const;
	int GetScale() const;

	int GetInputMemorySize(const int crop_w, const int crop_h, const int outer_padding, const int batch_size) const;
	int GetOutputMemorySize(const int crop_w, const int crop_h, const int outer_padding, const int batch_size) const;

	Waifu2x::eWaifu2xError ReconstructImage(const bool UseTTA, const int crop_w, const int crop_h, const int outer_padding, const int batch_size, float *inputBlockBuf, float *outputBlockBuf, const cv::Mat &inMat, cv::Mat &outMat);

	static std::string GetModelName(const boost::filesystem::path &info_path);
};