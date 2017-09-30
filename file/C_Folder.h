//���������ļ��У��ļ����ࡣ

#pragma once
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

#ifndef _FilesInFolder_
#define _FilesInFolder_
struct FilesInFolder
{
	string strFileName;
	string strFilePath;
};
#endif

class __declspec(dllexport) C_Folder
{
private:
	//��ȡ�ļ�����ָ�����ļ���Ϣ���ݹ�
	vector<FilesInFolder> scanFolder(string strFolderPath, string strFilter, vector<FilesInFolder> vt_FIF ,bool isRecursion);
	void scanFolder_faster(string strFolderPath, string strFilter, vector<FilesInFolder>& vt_FIF ,bool isRecursion);
	vector<string> scanFolder(string strFolderPath, vector<string> vt_folderName, bool isRecursion);
	//�ַ����Ƚ�
	bool compareFilter(string str1, string str2);
public:
	~C_Folder(void){};
	C_Folder(){};
	
	//��ȡ�ļ�����ָ�����ļ���Ϣ������һ���Զ���ṹ�壬ע�⣬����ʹ��deleteFilesInFolder�ͷŷ���ֵ���ڴ�
	vector<FilesInFolder>* getFileFromFolder(string* strFolderPath, string* strFilter, bool isRecursion);
	void getFileFromFolder_faster(string* strFolderPath, string* strFilter, bool isRecursion, vector<FilesInFolder>& vt_FIF);
	//�ͷ����溯������Ľṹ���ڴ�
	void deleteFilesInFolder(vector<FilesInFolder>* vt_FIF);	
	//��ȡ�ļ����е����ļ���
	vector<string> getFolder(string strFolderPath, bool isRecursion);
	//���ļ�·���л�ȡ�ļ��� C:/f1/f2/3.bmp -> 3.bmp
	string getFileNameFromPath(string filePath, bool isNeedFormat);
	//���ļ�·���л�ȡ�ļ����ڵ��ļ����� C:/f1/f2/3.bmp -> f2
	string getFolderNameFromPath(string filePath);
	//�ж��ļ��Ƿ����
	bool isFileExist(string path);
	//�ж��ļ����Ƿ����
	bool isFoldeExist(char* folderPath, bool isCreate);
	//�����ļ���
	int creatFolder(string str_src, string str_dst, bool isRecursion);
	//�����ļ���
	void copyFolderTo(string source, string dis, string searchChars);
	//{   
	//	vector<FilesInFolder>* vt_FIF = getFileFromFolder()

	//	/*		struct _finddata_t   ffblk;  
	//	char path[256], SourcePath[256], DisPath[256];  
	//	sprintf(path,"%sq_*",source);  
	//	long done = _findfirst(path,&ffblk);  
	//	int find=0;  
	//	while (find==0)    
	//	{    
	//	if(strcmp(ffblk.name, "q_"))
	//	{
	//	sprintf(SourcePath, "%s\%s",source, ffblk.name);
	//	sprintf(DisPath, "%s\%s",dis, ffblk.name);
	//	CopyFile(SourcePath, DisPath, bcover);
	//	}
	//	find=_findnext(done,&ffblk);    
	//	}  
	//	_findclose(done); */ 
	//}
};
