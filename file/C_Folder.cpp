#include "StdAfx.h"
#include "C_Folder.h"

//#define SameWithMatLab

/*-------------------------------------------------------------------------------------------------
���ܣ�						��ȡ�ļ�����ָ�����ļ���Ϣ������һ���Զ���ṹ��
strFolderPath��				�ļ���·��
strFilter��					��������ֻ�к�׺������".txt"����"mydoc.txt"������strFilter�Ĳ�ɸѡ����
isRecursion:				�Ƿ������ļ���
���أ�						��������������ĵ���·�����ĵ����ơ�ע�⣬����ʹ��deleteFilesInFolder���ͷŷ��ص��ڴ档

-------------------------------------------------------------------------------------------------*/
vector<FilesInFolder>* C_Folder::getFileFromFolder(string* strFolderPath, string* strFilter, bool isRecursion)
{
	vector<FilesInFolder>* vt_fileInfo  = new vector<FilesInFolder>[1];
	vector<FilesInFolder> vt_fileInfoR;
	*vt_fileInfo = scanFolder(*strFolderPath, *strFilter, vt_fileInfoR, isRecursion);
	return vt_fileInfo;
}

/*-------------------------------------------------------------------------------------------------
���ܣ�						��ȡ�ļ�����ָ�����ļ���Ϣ������һ���Զ���ṹ��
strFolderPath��				�ļ���·��
strFilter��					��������ֻ�к�׺������".txt"����"mydoc.txt"������strFilter�Ĳ�ɸѡ����
isRecursion:				�Ƿ������ļ���
vt_FIF:						�������������������ĵ���·�����ĵ����ơ�

-------------------------------------------------------------------------------------------------*/
void C_Folder::getFileFromFolder_faster(string* strFolderPath, string* strFilter, bool isRecursion, vector<FilesInFolder>& vt_FIF)
{
	scanFolder_faster(*strFolderPath, *strFilter, vt_FIF, isRecursion);
}

/*-------------------------------------------------------------------------------------------------
���ܣ�					ɾ���ṹ��FilesInFolder�����õĿռ�
vt_FIF��				��Ҫɾ����FilesInFolder�ڴ�ָ��

-------------------------------------------------------------------------------------------------*/
void C_Folder::deleteFilesInFolder(vector<FilesInFolder>* vt_FIF)
{	

	(*vt_FIF).clear();
	delete[] vt_FIF; 
	vt_FIF = NULL;
}

/*-------------------------------------------------------------------------------------------------
���ܣ�						�����ļ��У���ȡ�ļ����е����ļ��С�
strFolderPath��				��Ҫ�������ļ���·��
isRecursion��				�Ƿ�ݹ��ȡ���ļ����е����ļ���
���أ�						strFolderPath·���е����ļ���

-------------------------------------------------------------------------------------------------*/
vector<string> C_Folder::getFolder(string strFolderPath, bool isRecursion)
{
	vector<string> vt_folder;
	vector<string> vt_folderR;
	vt_folder = scanFolder(strFolderPath, vt_folderR, isRecursion);
	return vt_folder;
}

/*-------------------------------------------------------------------------------------------------
���ܣ�						��ȡ�ļ�����ָ�����ļ���Ϣ������һ���Զ���ṹ�壬�еݹ����
strFolderPath��				�ļ���·��
strFilter��					��������ֻ�к�׺������".txt"����"mydoc.txt"������strFilter�Ĳ�ɸѡ����
vt_FIF��					���λ�ȡ���ļ���Ϣ���ݹ��ã���һ�εݹ����ʱ���Ὣ��ȷ����Ϣ�ŵ��˱�����
isRecursion:				�Ƿ�ݹ鿼�����ļ���
���أ�						��������������ĵ���·�����ĵ�����

-------------------------------------------------------------------------------------------------*/
vector<FilesInFolder> C_Folder::scanFolder(string strFolderPath, string strFilter, vector<FilesInFolder> vt_FIF, bool isRecursion)
{
	vector<FilesInFolder> vt_filePath;
	WIN32_FIND_DATA FindFileData;

	//����һ�εݹ�������ĵ����뷵�صı�����
	for(int i = 0; i < vt_FIF.size(); i++)
		vt_filePath.push_back(vt_FIF[i]);

	string strAllFilePath = strFolderPath + "\\*.*";
	string nextFile = "";

	//��ȡ�ļ����е������ļ�
	HANDLE hFind = FindFirstFile(strAllFilePath.c_str(), &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind) 
		return vt_filePath;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//�����ļ���
		{		
			if(FindFileData.cFileName[0] != '.') 
			{
				nextFile = strFolderPath + "\\" +  FindFileData.cFileName;
				if (isRecursion == true)//�ݹ飬��ȡ���ļ����е��ļ�
					vt_filePath = scanFolder(nextFile, strFilter, vt_filePath, isRecursion);
			}
		}
		else//�����ļ�
		{
			//�ж��Ƿ�����Ҫ���ļ�
			if(compareFilter(FindFileData.cFileName, strFilter) == true)
			{
				//��ȡ·�����ļ�����
				FilesInFolder fif;
				fif.strFilePath = strFolderPath + "\\" + FindFileData.cFileName;
				fif.strFileName = FindFileData.cFileName;
				vt_filePath.push_back(fif);
			}
		}
		if(!FindNextFile(hFind, &FindFileData))    
			break;
	}
	return vt_filePath;
}

/*-------------------------------------------------------------------------------------------------
�ر�ע�⣺					�˺������ڴ����������50w�����ݣ���Լ��50M���ڴ�û���ͷ�
���ܣ�						��ȡ�ļ�����ָ�����ļ���Ϣ������һ���Զ���ṹ�壬�еݹ��������scanFolder��ȣ��˺�������
strFolderPath��				�ļ���·��
strFilter��					��������ֻ�к�׺������".txt"����"mydoc.txt"������strFilter�Ĳ�ɸѡ����
vt_FIF��					���λ�ȡ���ļ���Ϣ���ݹ��ã���һ�εݹ����ʱ���Ὣ��ȷ����Ϣ�ŵ��˱�����
isRecursion:				�Ƿ�ݹ鿼�����ļ���
���أ�						��������������ĵ���·�����ĵ�����

-------------------------------------------------------------------------------------------------*/
void C_Folder::scanFolder_faster(string strFolderPath, string strFilter, vector<FilesInFolder>& vt_FIF, bool isRecursion)
{
	WIN32_FIND_DATA FindFileData;

	string strAllFilePath = strFolderPath + "\\*.*";
	string nextFile = "";

	//��ȡ�ļ����е������ļ�
	HANDLE hFind = FindFirstFile(strAllFilePath.c_str(), &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind) 
		return;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//�����ļ���
		{		
			if(FindFileData.cFileName[0] != '.') 
			{
				nextFile = strFolderPath + "\\" +  FindFileData.cFileName;
				if (isRecursion == true)//�ݹ飬��ȡ���ļ����е��ļ�					
					scanFolder_faster(nextFile, strFilter, vt_FIF, isRecursion);
			}
		}
		else//�����ļ�
		{
			//�ж��Ƿ�����Ҫ���ļ�
			if(compareFilter(FindFileData.cFileName, strFilter) == true)
			{
				//��ȡ·�����ļ�����
				FilesInFolder fif;
				fif.strFilePath = strFolderPath + "\\" + FindFileData.cFileName;
				fif.strFileName = FindFileData.cFileName;
				vt_FIF.push_back(fif);
			}
		}
		if(!FindNextFile(hFind, &FindFileData))    
			break;
	}
}

/*-------------------------------------------------------------------------------------------------
���ܣ�						��ȡ�ļ������ļ��У�����һ���Զ���ṹ�壬�еݹ����
strFolderPath��				�ļ���·��
vt_folderName��				���λ�ȡ���ļ�����Ϣ���ݹ��ã���һ�εݹ����ʱ���Ὣ��ȷ����Ϣ�ŵ��˱�����	
isRecursion��				�Ƿ�ݹ鿼�����ļ���
���أ�						��������������ļ���

-------------------------------------------------------------------------------------------------*/
vector<string> C_Folder::scanFolder(string strFolderPath, vector<string> vt_folderName, bool isRecursion)
{
	vector<string> vt_folder;
	WIN32_FIND_DATA FindFileData;

	//����һ�εݹ�������ļ��з��뷵�صı�����
	for(int i = 0; i < vt_folderName.size(); i++)
		vt_folder.push_back(vt_folderName[i]);

	string strAllFilePath = strFolderPath + "\\*.*";
	string nextFile = "";

	//��ȡ�ļ����е������ļ�
	HANDLE hFind = FindFirstFile(strAllFilePath.c_str(), &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind) 
		return vt_folder;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//�����ļ���
		{		
			if(FindFileData.cFileName[0] != '.')
			{
				nextFile = strFolderPath + "\\" +  FindFileData.cFileName;
				vt_folder.push_back(nextFile);
				if (isRecursion == true)//�ݹ飬��ȡ���ļ����е��ļ���
					vt_folder = scanFolder(nextFile, vt_folder, isRecursion);
			}
		}

		if(!FindNextFile(hFind, &FindFileData))    
			break;
	}
	return vt_folder;
}

/*-------------------------------------------------------------------------------------------------
���ܣ�						�ж�str1�Ƿ��str2��ĩβ���ַ���ͬ�������ж�str2�Ƿ��str1��ĩβ���ַ���ͬ
str1��						�ַ���1
str2��						�ַ���2	
���أ�						�Ƿ���ͬ

-------------------------------------------------------------------------------------------------*/
bool C_Folder::compareFilter(string str1, string str2)
{
	int minLen = str1.length() < str2.length() ? str1.length() : str2.length();
	bool isMatch;
	string str1Sub = str1.substr(str1.length() - minLen, minLen);
	string str2Sub = str2.substr(str2.length() - minLen, minLen);
	if(str1Sub == str2Sub) 
		isMatch = true;
	else
		isMatch = false;
	return isMatch;
}

//����ͼƬ·��"D:\Test\2012-04-23_09-02-08_002_DO.jpg"������"2012-04-23_09-02-08_002_DO"

string C_Folder::getFileNameFromPath(string filePath, bool isNeedFormat)
{
	int i1 = filePath.rfind("\\");
	string str;
	str = filePath.substr(i1 + 1, filePath.length() - i1);
	if(isNeedFormat == false);
	{
		i1 = str.rfind(".");
		str = str.substr(0, i1);
	}	
	return str;
}

//�����ļ�·��"D:\Test\2012-04-23_09-02-08_002_DO.jpg"������"Test"

string C_Folder::getFolderNameFromPath(string filePath)
{	
	string str = filePath.substr(0, filePath.rfind("\\"));
	str = str.substr(str.rfind("\\") + 1, str.length() - str.rfind("\\"));
	return str;
}

//�ж��ļ��Ƿ����

bool C_Folder::isFileExist(string path)
{
	bool isExist = false;
	WIN32_FIND_DATA FindFolderData;
	HANDLE hFind_folder = FindFirstFile(path.c_str(), &FindFolderData);
	if(INVALID_HANDLE_VALUE == hFind_folder)   
	{				
	}
	else
	{
		isExist = true;
	}
	return isExist;
}

//�ж��ļ����Ƿ���ڣ����������½���

bool C_Folder::isFoldeExist(char* folderPath, bool isCreate)
{
	bool isExist = false;
	//�ж��ļ����Ƿ���ڣ����������½���
	WIN32_FIND_DATA FindFolderData;
	HANDLE hFind_folder = FindFirstFile(folderPath, &FindFolderData);
	if(INVALID_HANDLE_VALUE == hFind_folder)
	{
		//�����ļ���
		if(isCreate)
			CreateDirectory(folderPath, NULL);
	}
	else
	{
		isExist = true;
	}
	return isExist;
}

/*-------------------------------------------------------------------------------------------------
���ܣ�						��str_src�е��ļ��и��Ƶ�str_dst�У�ֻ�����ļ��нṹ���������ļ����е��ļ���
str_src��					Դ�ļ���·��
str_dst��					Ŀ���ļ���·��
isRecursion��				�Ƿ�ݹ�
���أ�						���Ƶ��ļ�������

-------------------------------------------------------------------------------------------------*/
int C_Folder::creatFolder(string str_src, string str_dst, bool isRecursion)
{
	C_Folder OF;
	vector<string> vt_folder = OF.getFolder(str_src, false);
	if(vt_folder.size() == 0)
		return 0;
	for(int i = 0; i < vt_folder.size(); i++)
	{
		string strFolderName = vt_folder[i].substr(vt_folder[i].rfind("\\") + 1, vt_folder[i].length() - vt_folder[i].rfind("\\"));
		string str_dstFolderPath = str_dst + "\\" + strFolderName;
		char dstFolderPath[300];
		sprintf(dstFolderPath, "%s", str_dstFolderPath.c_str());
		OF.isFoldeExist(dstFolderPath, true);//�ж��ļ����Ƿ���ڣ��������򴴽�
		if(isRecursion == true)
			creatFolder(vt_folder[i].c_str(), dstFolderPath, isRecursion);
	}
	return vt_folder.size();
}

//�����ļ���source�е����з���searchChars�����ݵ��ļ���dis��
void C_Folder::copyFolderTo(string source, string dis, string searchChars)
{
	vector<FilesInFolder>* vt_FIF = getFileFromFolder(&source, &searchChars, false);
	for(int i = 0; i < vt_FIF->size() && i < 30; i++)
	{
		string newfilePath = dis + "\\" + (*vt_FIF)[i].strFileName;
		CopyFile((*vt_FIF)[i].strFilePath.c_str(), newfilePath.c_str(), false);
	}
	deleteFilesInFolder(vt_FIF);
}
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