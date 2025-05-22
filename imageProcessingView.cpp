// imageProcessingView.cpp: CimageProcessingView 类的实现
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "imageProcessing.h"
#include "imageProcessingDoc.h"
#include "imageProcessingView.h"
#include "_GlobalCommon.h"
#include "CGetRoute.h"
#include "CGetPixel.h"
#include "CGetValue1.h"
#include "CGetValue2.h"
#include "CGetModel.h"
#include "CGetMSE.h"
#include "CGetWindow.h"
#include "CGetBF.h"
#include "CGetK.h"

#define pi 3.1415926

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CimageProcessingView, CView)

BEGIN_MESSAGE_MAP(CimageProcessingView, CView)
	ON_COMMAND(ID_IMAGEPROCESS_OPENBMPFILE, &CimageProcessingView::OnImageprocessOpenbmpfile)
	ON_COMMAND(ID_IMAGEPROCESS_SAVETOFILE, &CimageProcessingView::OnImageprocessSavetofile)
	ON_COMMAND(ID_IMAGEPROCESS_DISPLAYFILEHEADER, &CimageProcessingView::OnImageprocessDisplayfileheader)
	ON_COMMAND(ID_IMAGEPROCESS_DISPLAYPALETTE, &CimageProcessingView::OnImageprocessDisplaypalette)
	ON_COMMAND(ID_IMAGEPROCESS_GETPIXELVALUE, &CimageProcessingView::OnImageprocessGetpixelvalue)
	ON_COMMAND(ID_IMAGEPROCESS_SETPIXELVALUE, &CimageProcessingView::OnImageprocessSetpixelvalue)
	ON_COMMAND(ID_IMAGEPROCESS_INERPOLATION, &CimageProcessingView::OnImageprocessInerpolation)
	ON_COMMAND(ID_IMAGEPROCESS_GAUSSSMOOTH, &CimageProcessingView::OnImageprocessGausssmooth)
	ON_COMMAND(ID_IMAGEPROCESS_MEDIANFILTER, &CimageProcessingView::OnImageprocessMedianfilter)
	ON_COMMAND(ID_IMAGEPROCESS_BILATERALFILTER, &CimageProcessingView::OnImageprocessBilateralfilter)
	ON_COMMAND(ID_IMAGEPROCESS_HISTOEQUALIZATION, &CimageProcessingView::OnImageprocessHistoequalization)
	ON_COMMAND(ID_IMAGEPROCESS_SHARPENGRAD, &CimageProcessingView::OnImageprocessSharpengrad)
	ON_COMMAND(ID_IMAGEPROCESS_CANNYEDGE, &CimageProcessingView::OnImageprocessCannyedge)
	ON_COMMAND(ID_IMAGEPROCESS_OTSUSEGMENT, &CimageProcessingView::OnImageprocessOtsusegment)
END_MESSAGE_MAP()

CimageProcessingView::CimageProcessingView() noexcept
{
	pFileBuf = NULL;
}

CimageProcessingView::~CimageProcessingView()
{
	if( pFileBuf ) 
	{
		delete [] pFileBuf;
		pFileBuf = 0;
	}
}

BOOL CimageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CimageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CimageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CimageProcessingDoc *CimageProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CimageProcessingDoc)));
	return (CimageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

// CimageProcessingView 绘图
void CimageProcessingView::OnDraw(CDC *pDC)
{
	CimageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if( pFileBuf != NULL )
	{
		DisplayImage(pDC,pFileBuf,10,10,0,0,0);
	}
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//Here are the functions to be programmed by you!

//Open a BMP file
void CimageProcessingView::OnImageprocessOpenbmpfile()
{
	LPCTSTR lpszFilter = "BMP Files (*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_NOCHANGEDIR,lpszFilter,NULL);
	if( dlg.DoModal() != IDOK ) return;
	if( pFileBuf != NULL )
	{
		delete [] pFileBuf;
	}
	pFileBuf = OpenBMPfile( dlg.GetPathName() );
	Invalidate();
	UpdateWindow();
}

//Save to a new BMP file
void CimageProcessingView::OnImageprocessSavetofile()
{
	if(pFileBuf == NULL) return;
	/**/
	CGetRoute dlg;
	dlg.DoModal();
	//Add your code to choose the new BMP filename
	CString strBmpFile = dlg.out;
	strBmpFile += ".bmp";
	SaveDIB(pFileBuf, strBmpFile);
}

//Display BMP file header
void CimageProcessingView::OnImageprocessDisplayfileheader()
{
	if(pFileBuf == NULL) return;
	/**/
	DisplayHeaderMessage(pFileBuf);
}

//Display Pallete
void CimageProcessingView::OnImageprocessDisplaypalette()
{
	if(pFileBuf == NULL) return;
	/**/
	int num = 0;
	RGBQUAD *pallete = GetDIBPaletteData(pFileBuf,&num);
	if( pallete == NULL )
	{
		AfxMessageBox("No palette");
	}
	else
	{
		//Here are your code
		//char msg[25600];
		for (int i = 0; i < num; i++)
		{
			printf("调色板%d:Reserved=%d,Red=%d,Green=%d,Blue=%d\n", i,
				pallete[i].rgbReserved, pallete[i].rgbRed,
				pallete[i].rgbGreen, pallete[i].rgbBlue);
		}
		//AfxMessageBox(msg);
	}
}

//Get pixel value
void CimageProcessingView::OnImageprocessGetpixelvalue()
{
	if(pFileBuf == NULL) return;
	/**/
	//Add your code to choose the coordinate (x,y)
	CGetPixel dlg;
	dlg.DoModal();
	int x = dlg.X;
	int y = dlg.Y;
	if (x == -1 && y == -1) return;
	if (x >= GetImageWidth(pFileBuf) || y >= GetImageHeight(pFileBuf))
	{
		AfxMessageBox("输入的像素值超出了图片范围!");
		return;
	}
	RGBQUAD rgb;
	bool bGray;
	GetPixel(pFileBuf,x,y,&rgb,&bGray);
	char buf[100];
	if( bGray )
		sprintf(buf, "(%d,%d) = %d",x,y,rgb.rgbReserved);
	else
		sprintf(buf, "(%d,%d) = (%d,%d,%d)",x,y,rgb.rgbRed,rgb.rgbGreen,rgb.rgbBlue);
	AfxMessageBox( buf );
}

//Set pixel value
void CimageProcessingView::OnImageprocessSetpixelvalue()
{
	if(pFileBuf == NULL) return;
	/**/
	//Add your code to choose the coordinate (x,y)
	//获取要处理的像素位置
	CGetPixel dlg;
	dlg.DoModal();
	int x = dlg.X;
	int y = dlg.Y;
	if (x == -1 && y == -1) return;
	if (x >= GetImageWidth(pFileBuf) || y >= GetImageHeight(pFileBuf))
	{
		AfxMessageBox("输入的像素值超出了图片范围!");
		return;
	}
	int BitCount = GetColorBits(pFileBuf);
	RGBQUAD rgb;
	if (BitCount == 8)
	{
		//获取灰度图像的像素设定值
		CGetValue1 dlg;
		dlg.DoModal();
		int value = dlg.out;
		if (value == -1) return;
		if (value >= 256)
		{
			AfxMessageBox("输入的像素值超出了范围!");
			return;
		}
		rgb.rgbReserved = value;
	}
	else if(BitCount == 24)
	{
		//获取24位彩色图像的像素设定值
		CGetValue2 dlg;
		dlg.DoModal();
		if (dlg.Red == -1 && dlg.Green == -1 && dlg.Blue == -1) return;
		if (dlg.Red >= 256 || dlg.Green >= 256 || dlg.Blue >= 256)
		{
			AfxMessageBox("输入的像素值超出了范围!");
			return;
		}
		rgb.rgbRed = dlg.Red;
		rgb.rgbGreen = dlg.Green;
		rgb.rgbBlue = dlg.Blue;
	}
	//打开图像时已进行判断，不存在其他情况
	SetPixel(pFileBuf,x,y,rgb);
	Invalidate();
	UpdateWindow();
	printf("像素设置完毕\n");
}

//Image interpolaion
void CimageProcessingView::OnImageprocessInerpolation()
{
	if(pFileBuf == NULL) return;
	/**/
	//Add your code to choose method (nearest or bilinear) and zoom factors
	CGetModel dlg;
	dlg.DoModal();
	int newWidth  = dlg.Width;
	int newHeight = dlg.Height;
	int model = dlg.model;
	char *pNewImage = ImageInterpolation(pFileBuf,newWidth,newHeight,model);
	delete [] pFileBuf;
	pFileBuf = pNewImage;
	Invalidate();
	UpdateWindow();
}

//Gaussian smoothing
void CimageProcessingView::OnImageprocessGausssmooth()
{
	CGetMSE dlg;
	dlg.DoModal();
	int MSE = dlg.out;//均方差
	if (MSE == -1) return;
	int BitCount = GetColorBits(pFileBuf);
	if (BitCount == 8)
	{
		//处理灰度图像
		int n = 2 * 3 * MSE - 1;//窗口宽度,窗口半径为3sigma
		int mid = (n + 1) / 2;
		//动态分配高斯核数组
		double** Gs;
		Gs = new double* [n];
		for (int i = 0; i < n; i++) Gs[i] = new double[n];
		double sum = 0;//计算和，便于归一化
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				Gs[i - 1][j - 1] = exp(-((mid - i) * (mid - i) + (mid - j) * (mid - j)) / (double)(2 * MSE * MSE));
				sum += Gs[i - 1][j - 1];
			}
		}
		//归一化
		printf("高斯滤波核,均方差为%d,核宽度为%d\n", MSE, n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Gs[i][j] = Gs[i][j] / sum;
				printf("%f ", Gs[i][j]);
			}
			printf("\n");
		}
		int imageWidth = GetImageWidth(pFileBuf);
		int imageHeight = GetImageHeight(pFileBuf);
		//动态分配新的图片像素储存空间,存储计算后数据
		char* NewP = new char[imageHeight * imageWidth];

		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//对每个像素进行处理
				double k = 0;
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						RGBQUAD rgb;
						int x = w + (i - mid);
						int y = h + (j - mid);
						//超出边界的点使用中心值
						if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
							GetPixel(pFileBuf, w, h, &rgb, 0);
						else GetPixel(pFileBuf, x, y, &rgb, 0);
						k += rgb.rgbReserved*Gs[i-1][j-1];
					}
				}
				NewP[h * imageWidth + w] = (int)k;
			}
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				rgb.rgbReserved = NewP[h * imageWidth + w];
				SetPixel(pFileBuf, w, h, rgb);
				//printf("(%d,%d)处像素值已修改为%d\n", w, h, rgb.rgbReserved);
			}
		}

		//释放空间
		for (int i = 0; i < n; i++) delete[] Gs[i];
		delete[] Gs;
		delete[] NewP;
	}
	else if (BitCount == 24)
	{
		//处理彩色图像
		int n = 2 * 3 * MSE - 1;//窗口宽度,窗口半径为3sigma
		int mid = (n + 1) / 2;
		//动态分配高斯核数组
		double** Gs;
		Gs = new double* [n];
		for (int i = 0; i < n; i++) Gs[i] = new double[n];
		double sum = 0;//计算和，便于归一化
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				Gs[i - 1][j - 1] = exp(-((mid - i) * (mid - i) + (mid - j) * (mid - j)) / (double)(2 * MSE * MSE));
				sum += Gs[i - 1][j - 1];
			}
		}
		//归一化
		printf("高斯滤波核,均方差为%d,核宽度为%d\n", MSE, n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Gs[i][j] = Gs[i][j] / sum;
				printf("%f ", Gs[i][j]);
			}
			printf("\n");
		}
		int imageWidth = GetImageWidth(pFileBuf);
		int imageHeight = GetImageHeight(pFileBuf);
		//动态分配新的图片像素储存空间,存储计算后数据
		char* NewPred = new char[imageHeight * imageWidth];
		char* NewPgreen = new char[imageHeight * imageWidth];
		char* NewPblue = new char[imageHeight * imageWidth];

		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//对每个像素进行处理
				double kred = 0, kgreen = 0, kblue = 0;
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						RGBQUAD rgb;
						int x = w + (i - mid);
						int y = h + (j - mid);
						//超出边界的点使用中心值
						if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
							GetPixel(pFileBuf, w, h, &rgb, 0);
						else GetPixel(pFileBuf, x, y, &rgb, 0);
						kred += rgb.rgbRed * Gs[i - 1][j - 1];
						kgreen += rgb.rgbGreen * Gs[i - 1][j - 1];
						kblue += rgb.rgbBlue * Gs[i - 1][j - 1];
					}
				}
				NewPred[h * imageWidth + w] = (int)kred;
				NewPgreen[h * imageWidth + w] = (int)kgreen;
				NewPblue[h * imageWidth + w] = (int)kblue;
			}
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				rgb.rgbRed = NewPred[h * imageWidth + w];
				rgb.rgbGreen = NewPgreen[h * imageWidth + w];
				rgb.rgbBlue = NewPblue[h * imageWidth + w];
				SetPixel(pFileBuf, w, h, rgb);
				/*printf("(%d,%d)处像素值已修改为(%d,%d,%d)\n", w, h,
					rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);*/
			}
		}

		//释放空间
		for (int i = 0; i < n; i++) delete[] Gs[i];
		delete[] Gs;
		delete[] NewPred;
		delete[] NewPgreen;
		delete[] NewPblue;
	}
	Invalidate();
	UpdateWindow();
	printf("高斯平滑处理完毕\n");
}

//Median filtering
void CimageProcessingView::OnImageprocessMedianfilter()
{
	CGetWindow dlg;
	dlg.DoModal();
	int n = dlg.out;//窗口宽度n	
	if (n == -1) return;
	if (n % 2 == 0)
	{
		AfxMessageBox("窗口宽度应为奇数");
		return;
	}
	int BitCount = GetColorBits(pFileBuf);
	if (BitCount == 8)
	{
		//处理灰度图像
		unsigned char* seq = new unsigned char[n * n];
		int mid = (n + 1) / 2;
		int imageWidth = GetImageWidth(pFileBuf);
		int imageHeight = GetImageHeight(pFileBuf);
		//动态分配新的图片像素储存空间,存储计算后数据
		char* NewP = new char[imageHeight * imageWidth];
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//对每个像素进行处理
				memset(seq, 0, n * n);
				int cnt = 0;
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						RGBQUAD rgb;
						int x = w + (i - mid);
						int y = h + (j - mid);
						//超出边界的点使用中心值
						if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
							GetPixel(pFileBuf, w, h, &rgb, 0);
						else GetPixel(pFileBuf, x, y, &rgb, 0);
						seq[cnt++] = rgb.rgbReserved;
					}
				}
				//冒泡排序
				unsigned char temp;
				for (int i = 0; i < n * n - 1; i++)
				{
					for (int j = 0; j < n * n - i - 1; j++)
					{
						if (seq[j] > seq[j + 1])
						{
							temp = seq[j];
							seq[j] = seq[j + 1];
							seq[j + 1] = temp;
						}
					}
				}
				//最终数据存入
				NewP[h * imageWidth + w] = seq[n*n/2];
			}
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				rgb.rgbReserved = NewP[h * imageWidth + w];
				SetPixel(pFileBuf, w, h, rgb);
				//printf("(%d,%d)处像素值已修改为%d\n", w, h, rgb.rgbReserved);
			}
		}
		//释放空间
		delete[] seq;
		delete[] NewP;
	}
	else if (BitCount == 24)
	{
		//处理彩色图像
		AfxMessageBox("彩色图像处理有待实现");
	}
	Invalidate();
	UpdateWindow();
	printf("中值滤波处理完毕\n");
}

//Bilateral filtering
void CimageProcessingView::OnImageprocessBilateralfilter()
{
	CGetBF dlg;
	dlg.DoModal();
	int sigma_d = dlg.out_d;
	int sigma_r = dlg.out_r;
	if (sigma_d == -1)return;
	if (sigma_r == -1)return;
	int n = 3 * sigma_d + 3 * sigma_r - 1;//窗口大小暂定为两个参数的均值
	int mid = (n + 1) / 2;
	int BitCount = GetColorBits(pFileBuf);
	if (BitCount == 8)
	{
		//处理灰度图像
		//动态分配双边滤波核数组
		double** Hf;
		Hf = new double* [n];
		for (int i = 0; i < n; i++) Hf[i] = new double[n];
		double sum = 0;//计算和，便于归一化
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
					Hf[i - 1][j - 1] =
					exp(-((mid - i) * (mid - i) + (mid - j) * (mid - j))
						/ (double)(2 * sigma_d * sigma_d));
				sum += Hf[i - 1][j - 1];
			}
		}
		//归一化
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Hf[i][j] = Hf[i][j] / sum;
				printf("%lf ", Hf[i][j]);
			}
			printf("\n");
		}
		int imageWidth = GetImageWidth(pFileBuf);
		int imageHeight = GetImageHeight(pFileBuf);
		//动态分配新的图片像素储存空间,存储计算后数据
		char* NewP = new char[imageHeight * imageWidth];

		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//按照灰度差值重新确定双边滤波核
				double** Hfn;
				Hfn = new double* [n];
				for (int i = 0; i < n; i++) Hfn[i] = new double[n];
				double sum = 0;//计算和，便于归一化
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						RGBQUAD rgb1, rgb2;
						GetPixel(pFileBuf, w, h, &rgb1, 0);
						int x = w + (i - mid);
						int y = h + (j - mid);
						//超出边界的点使用中心值
						if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
							GetPixel(pFileBuf, w, h, &rgb2, 0);
						else GetPixel(pFileBuf, x, y, &rgb2, 0);
						Hfn[i - 1][j - 1] = Hf[i - 1][j - 1] *
							exp(-((rgb1.rgbReserved - rgb2.rgbReserved) * (rgb1.rgbReserved - rgb2.rgbReserved))
								/ (double)(2 * sigma_r * sigma_r));
						sum += Hfn[i - 1][j - 1];
					}
				}
				//修改后继续归一化
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						Hfn[i][j] = Hfn[i][j] / sum;
						//printf("%lf ", Hfn[i][j]);
					}
					//printf("\n");
				}
				//对每个像素进行处理
				double k = 0;
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						RGBQUAD rgb;
						int x = w + (i - mid);
						int y = h + (j - mid);
						//超出边界的点使用中心值
						if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
							GetPixel(pFileBuf, w, h, &rgb, 0);
						else GetPixel(pFileBuf, x, y, &rgb, 0);
						k += rgb.rgbReserved * Hfn[i - 1][j - 1];
					}
				}
				NewP[h * imageWidth + w] = (int)k;
				//释放空间
				for (int i = 0; i < n; i++) delete[] Hfn[i];
				delete[] Hfn;
			}
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				rgb.rgbReserved = NewP[h * imageWidth + w];
				SetPixel(pFileBuf, w, h, rgb);
				//printf("(%d,%d)处像素值已修改为%d\n", w, h, rgb.rgbReserved);
			}
		}

		//释放空间
		for (int i = 0; i < n; i++) delete[] Hf[i];
		delete[] Hf;
		delete[] NewP;

	}
	else if (BitCount == 24)
	{
		//处理彩色图像
		AfxMessageBox("彩色图像处理有待实现");
	}
	Invalidate();
	UpdateWindow();
	printf("双边滤波处理完毕\n");

}

//Histogram equalization
void CimageProcessingView::OnImageprocessHistoequalization()
{
	int BitCount = GetColorBits(pFileBuf);
	if (BitCount == 8)
	{
		//处理灰度图像
		long cnt[256];//累计值数组,256个灰度级
		double cntp[256];//累计百分比数组
		memset(cnt, 0, 256 * sizeof(long));
		memset(cntp, 0, 256 * sizeof(double));
		int imageWidth = GetImageWidth(pFileBuf);
		int imageHeight = GetImageHeight(pFileBuf);
		long pixelNum = imageWidth * imageHeight;
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				RGBQUAD rgb;
				GetPixel(pFileBuf, w, h, &rgb, 0);
				cnt[rgb.rgbReserved]++;
			}
		}
		//计算累计百分比
		for (int i = 0; i < 256; i++)
		{
			if (i >= 1) cnt[i] = cnt[i] + cnt[i - 1];
			cntp[i] = (double)cnt[i] / (double)pixelNum;
			printf("灰度级%d累计百分比为%lf\n", i, cntp[i]);
		}
		int f[256];//灰度级对应数组
		memset(f, 0, 256 * sizeof(int));
		for (int i = 0; i < 256; i++)
		{
			f[i] = (int)(255 * cntp[i] + 0.5);
			printf("灰度级%d对应至灰度级%d\n", i, f[i]);
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				GetPixel(pFileBuf, w, h, &rgb, 0);
				rgb.rgbReserved = f[rgb.rgbReserved];
				SetPixel(pFileBuf, w, h, rgb);
				//printf("(%d,%d)处像素值已修改为%d\n", w, h, rgb.rgbReserved);
			}
		}

	}
	else if (BitCount == 24)
	{
		//处理彩色图像
		AfxMessageBox("彩色图像处理有待实现");
	}
	Invalidate();
	UpdateWindow();
	printf("直方图均衡化处理完毕\n");
}

//Sharpening by gradient
void CimageProcessingView::OnImageprocessSharpengrad()
{
	CGetK dlg;
	dlg.DoModal();
	float k = dlg.out;
	if (k == -1) return;
	if (k == 0 || k >= 1)
	{
		AfxMessageBox("增强因子范围为0-1!");
		return;
	}
	int BitCount = GetColorBits(pFileBuf);
	int imageWidth = GetImageWidth(pFileBuf);
	int imageHeight = GetImageHeight(pFileBuf);
	if (BitCount == 8)
	{
		//处理灰度图像
		//动态分配新的图片像素储存空间,存储计算后数据
		char* NewP = new char[imageHeight * imageWidth];
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//顶侧和右侧两条边的临界值不处理
				if (w + 1 < imageWidth && h + 1 < imageHeight)
				{
					//一阶微分方案
					/*
					RGBQUAD rgb, rgbw, rgbh;
					GetPixel(pFileBuf, w, h, &rgb, 0);
					GetPixel(pFileBuf, w + 1, h, &rgbw, 0);
					GetPixel(pFileBuf, w, h + 1, &rgbh, 0);
					int deltaw = rgb.rgbReserved - rgbw.rgbReserved;
					int deltah = rgb.rgbReserved - rgbh.rgbReserved;
					*/
					//二阶微分方案
					RGBQUAD rgb, rgbh1, rgbh2, rgbw1, rgbw2;
					GetPixel(pFileBuf, w, h, &rgb, 0);
					GetPixel(pFileBuf, w + 1, h, &rgbw1, 0);
					GetPixel(pFileBuf, w - 1, h, &rgbw2, 0);
					GetPixel(pFileBuf, w, h + 1, &rgbh1, 0);
					GetPixel(pFileBuf, w, h - 1, &rgbh2, 0);
					int deltaw = rgbw1.rgbReserved + rgbw2.rgbReserved - 2 * rgb.rgbReserved;
					int deltah = rgbh1.rgbReserved + rgbh2.rgbReserved - 2 * rgb.rgbReserved;

					double newpixel = sqrt((double)(deltah * deltah + deltaw * deltaw)) * k
						+ (double)rgb.rgbReserved * (1 - k);
					if (newpixel > 255) newpixel = 255;//上式计算的newpixel可能溢出
					NewP[h * imageWidth + w] = (int)newpixel;
				}
			}
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				rgb.rgbReserved = NewP[h * imageWidth + w];
				SetPixel(pFileBuf, w, h, rgb);
				//printf("(%d,%d)处像素值已修改为%d\n", w, h, rgb.rgbReserved);
			}
		}
		//释放空间
		delete[] NewP;
	}
	else if (BitCount == 24)
	{
		//处理彩色图像
		AfxMessageBox("彩色图像处理有待实现");
	}
	Invalidate();
	UpdateWindow();
	printf("图像锐化处理完毕\n");

}

//Canny edge detection
void CimageProcessingView::OnImageprocessCannyedge()
{
	
	int BitCount = GetColorBits(pFileBuf);
	int imageWidth = GetImageWidth(pFileBuf);
	int imageHeight = GetImageHeight(pFileBuf);
	if (BitCount == 8)
	{
		//处理灰度图像
		//soble算子
		int soble_x[3][3] = { -1,0,1,-2,0,2,-1,0,1 };
		int soble_y[3][3] = { 1,2,1,0,0,0,-1,-2,-1 };
		//动态分配梯度储存数组
		int* Grad_x = new int[imageHeight * imageWidth];
		int* Grad_y = new int[imageHeight * imageWidth];
		double* G = new double[imageWidth * imageHeight];
		//梯度方向数组，1,2,3,4分别代表—,|,/,\四个方向
		int* D = new int[imageWidth * imageHeight];
		//动态分配新的图片像素储存空间,存储计算后数据
		char* NewP = new char[imageHeight * imageWidth];
		//计算梯度
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//对每个像素进行处理
				int Gx = 0;
				int Gy = 0;
				for (int i = 1; i <= 3; i++)
				{
					for (int j = 1; j <= 3; j++)
					{
						RGBQUAD rgb;
						int x = w + (i - 2);
						int y = h + (j - 2);
						//超出边界的点使用中心值
						if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
							GetPixel(pFileBuf, w, h, &rgb, 0);
						else GetPixel(pFileBuf, x, y, &rgb, 0);
						Gx += rgb.rgbReserved * soble_x[i - 1][j - 1];
						Gy += rgb.rgbReserved * soble_y[i - 1][j - 1];
					}
				}
				//printf("x，y方向梯度为%d，%d\n", Gx, Gy);
				Grad_x[h * imageWidth + w] = Gx;
				Grad_y[h * imageWidth + w] = Gy;
				G[h * imageWidth + w] = sqrt(Gx * Gx + Gy * Gy);
				double t = atan2(Gy, Gx);
				//printf("角度为%lf\n", t);
				if ((t >= -pi / 8 && t < pi / 8) || (t < -pi * 7 / 8) || (t >= pi * 7 / 8))
					D[h * imageWidth + w] = 1;
				if ((t >= pi * 3 / 8 && t < pi * 5 / 8) || (t >= -pi * 5 / 8 && t < -pi * 3 / 8))
					D[h * imageWidth + w] = 2;
				if ((t >= pi / 8 && t < pi * 3 / 8) || (t >= -pi * 7 / 8 && t < -pi * 5 / 8))
					D[h * imageWidth + w] = 3;
				if ((t >= pi * 5 / 8 && t < pi * 7 / 8) || (t >= -pi * 3 / 8 && t < -pi / 8))
					D[h * imageWidth + w] = 4;
			}
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//进行非极大抑制		
				switch (D[h * imageWidth + w])
				{
				case 1:
					//若超出边界不予处理
					if (w - 1 < 0 || w + 1 >= imageWidth) break;
					//若为极大值则保留，否则置为0
					if (G[h * imageWidth + w - 1] <= G[h * imageWidth + w] &&
						G[h * imageWidth + w + 1] <= G[h * imageWidth + w])
						NewP[h * imageWidth + w] = G[h * imageWidth + w];
					else NewP[h * imageWidth + w] = 0;
					break;
				case 2:
					if (h - 1 < 0 || h + 1 >= imageWidth) break;
					if (G[(h - 1) * imageWidth + w] <= G[h * imageWidth + w] &&
						G[(h + 1) * imageWidth + w] <= G[h * imageWidth + w])
						NewP[h * imageWidth + w] = G[h * imageWidth + w];
					else NewP[h * imageWidth + w] = 0;
					break;
				case 3:
					if (w - 1 < 0 || w + 1 >= imageWidth) break;
					if (h - 1 < 0 || h + 1 >= imageWidth) break;
					if (G[(h + 1) * imageWidth + w - 1] <= G[h * imageWidth + w] &&
						G[(h - 1) * imageWidth + w + 1] <= G[h * imageWidth + w])
						NewP[h * imageWidth + w] = G[h * imageWidth + w];
					else NewP[h * imageWidth + w] = 0;
					break;
				case 4:
					if (w - 1 < 0 || w + 1 >= imageWidth) break;
					if (h - 1 < 0 || h + 1 >= imageWidth) break;
					if (G[(h - 1) * imageWidth + w - 1] <= G[h * imageWidth + w] &&
						G[(h + 1) * imageWidth + w + 1] <= G[h * imageWidth + w])
						NewP[h * imageWidth + w] = G[h * imageWidth + w];
					else NewP[h * imageWidth + w] = 0;
					break;
				}
			}
		}
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				if (NewP[h * imageWidth + w] > 255) rgb.rgbReserved = 255;
				else rgb.rgbReserved = NewP[h * imageWidth + w];
				SetPixel(pFileBuf, w, h, rgb);
				//printf("(%d,%d)处像素值已修改为%d\n", w, h, rgb.rgbReserved);
			}
		}

		//释放空间
		delete[] Grad_x;
		delete[] Grad_y;
		delete[] G;
		delete[] D;
		delete[] NewP;
	}
	else if (BitCount == 24)
	{
		//处理彩色图像
		AfxMessageBox("彩色图像处理有待实现");
	}
	Invalidate();
	UpdateWindow();
	printf("边缘检测处理完毕\n");
}

//Otsu segmentation
void CimageProcessingView::OnImageprocessOtsusegment()
{
	int BitCount = GetColorBits(pFileBuf);
	int imageWidth = GetImageWidth(pFileBuf);
	int imageHeight = GetImageHeight(pFileBuf);
	if (BitCount == 8)
	{
		//处理灰度图像
		long cnt[256];//累计值数组,256个灰度级
		double cntp[256];//百分比数组
		memset(cnt, 0, 256 * sizeof(long));
		memset(cntp, 0, 256 * sizeof(double));
		long pixelNum = imageWidth * imageHeight;
		//统计像素数
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				RGBQUAD rgb;
				GetPixel(pFileBuf, w, h, &rgb, 0);
				cnt[rgb.rgbReserved]++;
			}
		}
		//计算百分比及平均灰度级
		double sum = 0;
		for (int i = 0; i < 256; i++)
		{
			cntp[i] = (double)cnt[i] / (double)pixelNum;
			sum = sum + cntp[i] * i;
			//printf("灰度级%d所占百分比为%lf\n", i, cntp[i]);
		}
		int argu = (int)(sum + 0.5);
		printf("平均灰度级为%d\n", argu);
		// 
		//遍历所有灰度级，找出类间方差最大的k
		int final_k = 255;
		double Ob = 0;
		for (int k = 0; k < 256; k++)
		{
			//计算w1,w2
			double w1 = 0, w2 = 0;
			for (int i = 0; i < 256; i++)
			{
				if (i <= k) w1 = w1 + cntp[i];
				else if (i > k) w2 = w2 + cntp[i];
			}
			//printf("阈值为%d时,w1=%lf,w2=%lf\n", k, w1, w2);
			
			//计算u1,u2
			double u1 = 0, u2 = 0;
			for (int i = 0; i < 256; i++)
			{
				if (i <= k && w1 != 0) u1 = u1 + cntp[i] / w1;
				else if (i > k && w2 != 0) u2 = u2 + cntp[i] / w2;
			}
			//printf("阈值为%d时,u1=%lf,u2=%lf\n", k, u1, u2);

			//计算当前阈值类间方差Ob_k
			double Ob_k = w1 * w2 * (u2 - u1) * (u2 - u1);
			if (Ob_k > Ob)
			{
				Ob = Ob_k;
				final_k = k;
			}
		}
		//printf("计算出的阈值为%d\n", final_k);
		
		//按照计算出的阈值对图像进行分割
		for (int w = 0; w < imageWidth; w++)
		{
			for (int h = 0; h < imageHeight; h++)
			{
				//将所有像素的计算值写回原处		
				RGBQUAD rgb;
				GetPixel(pFileBuf, w, h, &rgb, 0);
				if (rgb.rgbReserved <= final_k) rgb.rgbReserved = 0;
				else rgb.rgbReserved = 255;
				SetPixel(pFileBuf, w, h, rgb);
				//printf("(%d,%d)处像素值已修改为%d\n", w, h, rgb.rgbReserved);
			}
		}
		char msg[50];
		sprintf(msg, "Otsu阈值计算为为%d", final_k);
		AfxMessageBox(msg);

	}
	else if (BitCount == 24)
	{
		//处理彩色图像
		AfxMessageBox("彩色图像处理有待实现");
	}
	Invalidate();
	UpdateWindow();
	printf("Otsu阈值分割处理完毕\n");
}
