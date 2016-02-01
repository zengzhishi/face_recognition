#ifndef _FACE_CATC_H
#define _FACE_CATC_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"
#include <opencv2\videoio.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\face\facerec.hpp>

#include <string.h>
#include <iostream>
#include <direct.h>
#include <stdlib.h>
#include <memory>

using namespace std;
using namespace cv;
using namespace face;

/*
* author: Zhishi Zeng, Yiwen Yang
*/

class  Face_Catch
{
public:
	 Face_Catch();
	~ Face_Catch();

	//�������

	/*
	*	imgΪ��������faceΪ��ȡ������ͼ
	*/
	void get_Face_Frame(Mat &img, Mat &face, VideoCapture &capture, CascadeClassifier& cascade, double scale);
	vector<Rect> detect_Face(Mat &frame, CascadeClassifier& cascade, double scale);

	//����ʶ��
	static Mat resize_norm(InputArray &_src, CvSize stand_size);
	void face_Reco_Train(Ptr<FaceRecognizer> &model, vector<Mat> &trainFace, vector<int> &trainLabels, CvSize size);
	void face_Reco_Update(Ptr<FaceRecognizer> &model, vector<Mat> &newFaces, vector<int> &newLabels, CvSize size);
	bool save_Reco_Data(Ptr<FaceRecognizer> &model);
	bool Face_Catch::load_Reco_Data(Ptr<FaceRecognizer> &model);

	int CheckDir(char* Dir);
	vector<string> split(string str, string pattern);

	vector<Rect> faces;
	Mat imageROI;
	//�������Ҫ��д�����ݿ��д洢�ĵ�ַ
	string dir_path = "C:/Faces";
	string path = "C:/Faces/faceRecognition.xml";

	CvSize standsize;
};

#endif