//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# ifdef SIV3D_INCLUDED
#  error <Siv3DAddon/OpenCV.hpp> は <Siv3D.hpp> より前にインクルードしてください
# endif
# include <opencv2/opencv.hpp>
# include <Siv3D.hpp>

namespace s3d
{
	namespace OpenCV
	{
		inline void ToMatVec3b(const Image& image, cv::Mat_<cv::Vec3b>& mat)
		{
			if (image.isEmpty)
			{
				mat.resize(0);

				return;
			}

			const size_t width = image.width, height = image.height;

			if (static_cast<size_t>(mat.cols) != width || static_cast<size_t>(mat.rows) != height)
			{
				mat = cv::Mat_<cv::Vec3b>(height, width);
			}

			if (mat.isContinuous())
			{
				const Color* pSrc = image[0];
				const Color* const pSrcEnd = pSrc + image.num_pixels;
				cv::Vec3b* pDst = mat.ptr<cv::Vec3b>();

				while (pSrc != pSrcEnd)
				{
					pDst->val[0] = pSrc->r;
					pDst->val[1] = pSrc->g;
					pDst->val[2] = pSrc->b;
					++pDst, ++pSrc;
				}
			}
			else
			{
				const Color* pSrc = image[0];

				uint8* pDst = mat.data;
				const size_t dstStep = mat.step.p[0];

				for (size_t y = 0; y < height; ++y)
				{
					size_t index = 0;

					for (size_t x = 0; x < width; ++x)
					{
						pDst[index++] = pSrc->r;
						pDst[index++] = pSrc->g;
						pDst[index++] = pSrc->b;
						++pSrc;
					}

					pDst += dstStep;
				}
			}
		}

		inline void ToMatVec4b(const Image& image, cv::Mat_<cv::Vec4b>& mat)
		{
			if (image.isEmpty)
			{
				mat.resize(0);

				return;
			}

			const size_t width = image.width, height = image.height;

			if (static_cast<size_t>(mat.cols) != width || static_cast<size_t>(mat.rows) != height)
			{
				mat = cv::Mat_<cv::Vec3b>(height, width);
			}

			if (mat.isContinuous())
			{
				const Color* pSrc = image[0];
				const Color* const pSrcEnd = pSrc + image.num_pixels;
				cv::Vec4b* pDst = mat.ptr<cv::Vec4b>();

				while (pSrc != pSrcEnd)
				{
					pDst->val[0] = pSrc->r;
					pDst->val[1] = pSrc->g;
					pDst->val[2] = pSrc->b;
					pDst->val[3] = pSrc->a;
					++pDst, ++pSrc;
				}
			}
			else
			{
				const Color* pSrc = image[0];

				uint8* pDst = mat.data;
				const size_t dstStep = mat.step.p[0];

				for (size_t y = 0; y < height; ++y)
				{
					size_t index = 0;

					for (size_t x = 0; x < width; ++x)
					{
						pDst[index++] = pSrc->r;
						pDst[index++] = pSrc->g;
						pDst[index++] = pSrc->b;
						pDst[index++] = pSrc->a;
						++pSrc;
					}

					pDst += dstStep;
				}
			}
		}

		inline cv::Mat_<cv::Vec3b> ToMatVec3b(const Image& image)
		{
			cv::Mat_<cv::Vec3b> mat;

			ToMatVec3b(image, mat);

			return mat;
		}

		inline cv::Mat_<cv::Vec4b> ToMatVec4b(const Image& image)
		{
			cv::Mat_<cv::Vec4b> mat;

			ToMatVec4b(image, mat);

			return mat;
		}

		inline void ToImage(const cv::Mat_<cv::Vec3b>& mat, Image& image)
		{
			if (mat.empty())
			{
				image.clear();

				return;
			}

			const size_t width = mat.cols, height = mat.rows;

			image.resize(width, height);

			if (mat.isContinuous())
			{
				Color* pDst = image[0];
				Color* const pDstEnd = pDst + image.num_pixels;
				const cv::Vec3b* pSrc = mat.ptr<cv::Vec3b>();

				while (pDst != pDstEnd)
				{
					pDst->r = pSrc->val[0];
					pDst->g = pSrc->val[1];
					pDst->b = pSrc->val[2];
					pDst->a = 255;
					++pDst, ++pSrc;
				}
			}
			else
			{
				Color* pDst = image[0];

				uint8* pSrc = mat.data;
				const size_t srcStep = mat.step.p[0];

				for (size_t y = 0; y < height; ++y)
				{
					size_t index = 0;

					for (size_t x = 0; x < width; ++x)
					{
						pDst->r = pSrc[index++];
						pDst->g = pSrc[index++];
						pDst->b = pSrc[index++];
						pDst->a = 255;
						++pDst;
					}

					pSrc += srcStep;
				}
			}
		}

		inline void ToImage(const cv::Mat_<cv::Vec4b>& mat, Image& image)
		{
			if (mat.empty())
			{
				image.clear();

				return;
			}

			const size_t width = mat.cols, height = mat.rows;

			image.resize(width, height);

			if (mat.isContinuous())
			{
				Color* pDst = image[0];
				Color* const pDstEnd = pDst + image.num_pixels;
				const cv::Vec4b* pSrc = mat.ptr<cv::Vec4b>();

				while (pDst != pDstEnd)
				{
					pDst->r = pSrc->val[0];
					pDst->g = pSrc->val[1];
					pDst->b = pSrc->val[2];
					pDst->a = pSrc->val[3];
					++pDst, ++pSrc;
				}
			}
			else
			{
				Color* pDst = image[0];

				uint8* pSrc = mat.data;
				const size_t srcStep = mat.step.p[0];

				for (size_t y = 0; y < height; ++y)
				{
					size_t index = 0;

					for (size_t x = 0; x < width; ++x)
					{
						pDst->r = pSrc[index++];
						pDst->g = pSrc[index++];
						pDst->b = pSrc[index++];
						pDst->a = pSrc[index++];
						++pDst;
					}

					pSrc += srcStep;
				}
			}
		}

		inline void ToImage(const cv::Mat_<cv::Vec4b>& mat, Image& image, uint8 alpha)
		{
			if (mat.empty())
			{
				image.clear();

				return;
			}

			const size_t width = mat.cols, height = mat.rows;

			image.resize(width, height);

			if (mat.isContinuous())
			{
				Color* pDst = image[0];
				Color* const pDstEnd = pDst + image.num_pixels;
				const cv::Vec4b* pSrc = mat.ptr<cv::Vec4b>();

				while (pDst != pDstEnd)
				{
					pDst->r = pSrc->val[0];
					pDst->g = pSrc->val[1];
					pDst->b = pSrc->val[2];
					pDst->a = alpha;
					++pDst, ++pSrc;
				}
			}
			else
			{
				Color* pDst = image[0];

				uint8* pSrc = mat.data;
				const size_t srcStep = mat.step.p[0];

				for (size_t y = 0; y < height; ++y)
				{
					size_t index = 0;

					for (size_t x = 0; x < width; ++x)
					{
						pDst->r = pSrc[index++];
						pDst->g = pSrc[index++];
						pDst->b = pSrc[index++];
						pDst->a = alpha; ++index;
						++pDst;
					}

					pSrc += srcStep;
				}
			}
		}

		inline Image ToImage(const cv::Mat_<cv::Vec3b>& mat)
		{
			Image image;

			ToImage(mat, image);

			return image;
		}

		inline Image ToImage(const cv::Mat_<cv::Vec4b>& mat)
		{
			Image image;

			ToImage(mat, image);

			return image;
		}

		inline Image ToImage(const cv::Mat_<cv::Vec4b>& mat, uint8 alpha)
		{
			Image image;

			ToImage(mat, image, alpha);

			return image;
		}
	}
}
