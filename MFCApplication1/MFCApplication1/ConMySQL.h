#ifndef _CCSQLACTION_H

#define _CCSQLACTION_H

#include <mysql.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <winsock.h>
#include "opencv2/imgcodecs.hpp"
#include <iostream>

//#pragma comment(lib,"libmySQL.lib") //��������mysql��


using namespace cv;
using namespace std;


struct stu_info//ѧ����Ϣ�Ľṹ��
{
	int num;
	string id;
	string name;
	bool sex;
	string specialty;
	string classname;
	string path[4];
};


class ConMySQL
{
public:
	ConMySQL();
	ConMySQL(char* host_add, char* user, char* pwd, char* database_name, int port);
	~ConMySQL();

	bool chCon(char* host_add, char* user, char* pwd, char* database_name, int port);
	bool insert_Stu_Info(const char* id, const char* name, bool sex, const char* specialty, const char* classname);//�����µ�ѧ����Ϣ
	bool insert_Stu_Pic(int num, const char *path1, const char* path2, const char* path3, const char* path4);//ͼƬ���ݲ���
	bool insert_Stu_Info_full(stu_info stuInfo);
//	bool update_Reco_Data(string &path, int height, int width);
//	string get_Reco_Data();
//	CvSize get_Reco_Data_Size();
	bool get_Stu_Info(stu_info &stuInfo, int num);//��ȡѧ���Ļ�����Ϣ
	int get_all_Info(stu_info stuInfo[]);//��ȡ����ѧ����Ϣ
	bool get_Pic_path(stu_info stuInfo, string &path1, string &path2, string &path3, string &path4);//��ȡ4��ͼƬ��·��

	int update_present_time();//����ѧ���ĵ�������������ʼһ���µĵ���
	bool get_present_time_data(string &present_data);//��ȡѧ���ĵ�����Ϣ
	bool ch_present_time(int num);//�ı������¼������ԭ����ʾΪ���ļ�¼�޸�Ϊ��ǩ��
	

	string ch_CStringToString(CString s);


protected:
	MYSQL my_SQL_Con;//��������Դָ��
	MYSQL_RES *result,*result2;
	MYSQL_ROW row,row2;
	string path;
	const char* RECO_PATH = "C:/Users/FacesData/faceRecognition.xml";
	const char* FACE_DIR = "C:/Users/FacesData/";

};
#endif