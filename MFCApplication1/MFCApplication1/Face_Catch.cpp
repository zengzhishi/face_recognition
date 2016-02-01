
#include "stdafx.h"
#include "Face_Catch.h"


Face_Catch::Face_Catch()
{
	standsize.height = 200;
	standsize.width = 200;
}

Face_Catch::~Face_Catch()
{

}


void Face_Catch::get_Face_Frame(Mat &img, Mat &face, VideoCapture &capture, CascadeClassifier& cascade, double scale)
{//����Ƶ���л�ȡͼ�񲢻�����������
	Mat frame,gray;
	vector<Rect> faces;

	if (capture.isOpened())
	{
		int times = 0;
		while(!capture.read(frame) && times == 2)
		{
			waitKey(100);
			times++;
		}


		faces = detect_Face(frame, cascade, scale);
		//cvtColor(frame, gray, COLOR_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ��
		//�����������
		//cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		int i, maxxsize = 0, id = -1, area;
		for (i = 0; i < faces.size(); i++)//Ѱ��������������������������������
		{	
			area = faces[i].width*faces[i].height; 
			if (maxxsize < area)
			{
				maxxsize = area;
				id = i;
			}
		}
		if (id != -1)
		{
			//double aspect_ratio = (double)faces[id].width / faces[id].height;
			frame.copyTo(img);
			rectangle(img, cvPoint(cvRound(faces[id].x*scale), cvRound(faces[id].y*scale)),
				cvPoint(cvRound((faces[id].x + faces[id].width - 1)*scale), cvRound((faces[id].y + faces[id].height - 1)*scale)),
				CV_RGB(255, 0, 0), 3, 8, 0);
			Rect faceRect;//��ԭ����С��ͼ�񰴱����Ŵ�
			faceRect.x = cvRound(faces[id].x*scale);
			faceRect.y = cvRound(faces[id].y*scale);
			faceRect.height = cvRound((faces[id].width - 1)*scale);
			faceRect.width = cvRound((faces[id].height - 1)*scale);
			face = frame(faceRect);
			cvtColor(face, face, CV_BGR2GRAY);
		}
	}
}


vector<Rect> Face_Catch::detect_Face(Mat &frame, CascadeClassifier& cascade, double scale)
{
	Mat gray, smallImg(cvRound(frame.rows / scale), cvRound(frame.cols / scale), CV_8UC1);
	double t = 0;

	cvtColor(frame, gray, CV_BGR2GRAY);//�ڽ����������֮ǰҪ�Ƚ�ͼ��ת��Ϊ�Ҷ�ͼ
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);//ͨ����СͼƬ�ӿ����������ٶ�
	equalizeHist(smallImg, smallImg);//ֱ��ͼ���⻯

	//t = (double)cvGetTickCount();//��ʱ��ͳ���������ʱ��
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		| CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		//|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));
	//t = (double)cvGetTickCount() - t;
	//printf("detection time = %g ms\n", t / ((double)cvGetTickFrequency()*1000.));
	return faces;
}


void Face_Catch::face_Reco_Train(Ptr<FaceRecognizer> &model, vector<Mat> &trainFace, vector<int> &trainLabels, CvSize size)
{
	int i;
	for (i = 0; i < trainFace.size(); ++i)
	{
		resize_norm(trainFace[i], size);//����ͼƬ����͹�һ��
	}
//	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();//��������ʼ��һ��������ģ��
	model->train(trainFace, trainLabels);//��ͼ��ͱ�ǩ����ѵ��

}


void Face_Catch::face_Reco_Update(Ptr<FaceRecognizer> &model, vector<Mat> &newFaces, vector<int> &newLabels, CvSize size)
{
	int i;
	for (i = 0; i < newFaces.size(); ++i)
	{
		resize_norm(newFaces[i], size);
	}
	model->update(newFaces, newLabels);//���·�����
}


bool Face_Catch::save_Reco_Data(Ptr<FaceRecognizer> &model)
{//��������ʶ���������������Ϣ
	char path_dir_c[200];
	strcpy_s(path_dir_c, dir_path.c_str());

	if (CheckDir(path_dir_c) == 0 || CheckDir(path_dir_c) == 1)//����ļ����Ƿ����
	{
		model->save(path);
		return true;
	}
	else
		return false;
}


bool Face_Catch::load_Reco_Data(Ptr<FaceRecognizer> &model)
{//��ȡ����ʶ���������������Ϣ
//	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	FILE *fp = NULL;
	char path_c[100];
	strcpy_s(path_c, path.c_str());
	fopen_s(&fp, path_c, "r");
	if (fp)
	{
		fclose(fp);
		model->load(path);
		return true;
	}
	return false;
}


//����ļ����Ƿ���ڣ��������򴴽�֮
//�ļ��д��ڷ��� 0
//�ļ��д���ʧ�ܷ���-1
//�ļ��д���ʧ�ܷ���1
int Face_Catch::CheckDir(char* Dir)
{
	FILE *fp = NULL;
	char TempDir[200];
	memset(TempDir, '\0', sizeof(TempDir));
	sprintf_s(TempDir, Dir);
	strcat_s(TempDir, "\\");
	strcat_s(TempDir, ".temp.fortest");
	fopen_s(&fp, TempDir, "w");
	if (!fp)
	{
		if (_mkdir(Dir) == 0)
		{
			return 1;//�ļ��д����ɹ�
		}
		else
		{
			return -1;//can not make a dir;
		}
	}
	else
	{
		fclose(fp);
	}
	return 0;
}


Mat Face_Catch::resize_norm(InputArray &_src, CvSize stand_size) 
{
	Mat dst;
	Mat src = _src.getMat();
	resize(_src, dst,stand_size);//�ߴ����
	// �����ͷ��ع�һ����ͼ��:
	switch (src.channels()) {
	case 1:
		normalize(dst, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		normalize(dst, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}



//�ַ����ָ��,strΪԴ�ַ�����patternΪ�ָ���
vector< string> Face_Catch::split(string str, string pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())//ʣ�µĲ�Ϊ�գ��⽫ʣ�µ���Ϊ���һ���ֶη���
		ret.push_back(str.substr(start));
	return ret;
}
