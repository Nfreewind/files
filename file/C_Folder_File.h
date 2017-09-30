//���ܣ�		�����ļ��У��ļ����ࡣ

#pragma once
#include <string>
#include <vector>

#ifndef _FilesInFolder_
#define _FilesInFolder_
struct FilesInFolder
{
	std::string strFileName;
	std::string strFilePath;
};
#endif

class C_Folder_File
{
private:

/*-------------------------------------------------------------------------------------
���ܣ�					�����ļ����е����ļ���
input:
	strFolderPath:		�ļ�·��
	isRecursion:		�Ƿ�ݹ��ȡ���ļ���
output
	vt_strFolder_o��	���ļ���·��
-------------------------------------------------------------------------------------*/
	void getFoldersFormDisk(std::string strFolderPath, bool isRecursion, std::vector<std::string>& vt_strFolder_o);

/*-------------------------------------------------------------------------------------
���ܣ�					��ȡ�ָ�������ַ���
input:
	str:				�ַ���
	delimiters:			�ָ���
output
	����:				�ָ���֮����ַ���
-------------------------------------------------------------------------------------*/
	std::vector<std::string> splitString(std::string str, std::string delimiters);

public:
	~C_Folder_File(void){};
	C_Folder_File(){};
	
/*-------------------------------------------------------------------------------------
���ܣ�					�����ļ���������Ҫ���ļ�
input:
	strFolderPath:		�ļ���·��
	strFileFilter:		�ļ�����
	isRecursion:		�Ƿ�ݹ�������ļ���
output
	vt_str_o:			�ļ�����·��
-------------------------------------------------------------------------------------*/
	void getFilesFromFolder(std::string strFolderPath, std::string strFileFilter, bool isRecursion, std::vector<std::string>& vt_str_o);

/*-------------------------------------------------------------------------------------
���ܣ�					�����ļ�����·���е��ļ���
input:
	filePath:			�ļ�·��
	isNeedFilter:		�Ƿ���Ҫ�ļ���׺
output
	����:				�ļ���
-------------------------------------------------------------------------------------*/
	std::string getFileNameFromPath(std::string filePath, bool isNeedFilter);

/*-------------------------------------------------------------------------------------
���ܣ�					�����ļ����ڵ��ļ�������
input:
	filePath:			�ļ�·��
output
	����:				�ļ����ڵ��ļ�������
-------------------------------------------------------------------------------------*/
	std::string getFolderNameFromFilePath(std::string filePath);

/*-------------------------------------------------------------------------------------
���ܣ�					�����ļ����е����ļ���
input:
	strFolderPath:		�ļ�·��
	isRecursion:		�Ƿ�ݹ��ȡ���ļ���
output
	vt_strFolder_o��	���ļ���·��
	����:				������ļ��в���
-------------------------------------------------------------------------------------*/
	int getFolders(std::string strFolderPath, bool isRecursion, std::vector<std::string>& vt_strFolder_o);

/*-------------------------------------------------------------------------------------
���ܣ�					�ж��ļ��Ƿ����
input:
	filePath:			�ļ�·��
output
	����:				�ļ��Ƿ����
-------------------------------------------------------------------------------------*/	
	bool isFileExist(std::string filePath);

/*-------------------------------------------------------------------------------------
���ܣ�					�ж��ļ����Ƿ���ڣ����ҿ��Դ������ļ���
input:
	folderPath:			�ļ���·��
	isCreate��			��������ڣ��Ƿ񴴽����ļ���
output
	����:				�ļ����Ƿ����
-------------------------------------------------------------------------------------*/	
	bool isFolderExist(std::string folderPath, bool isCreate);

/*-------------------------------------------------------------------------------------
���ܣ�					�����ļ�
input:
	src:				Դ�ļ�·��
	dst��				Ŀ���ļ�·��
output
	����:				����״̬��0Ϊ��ȷ�������쳣��
-------------------------------------------------------------------------------------*/	
	int CopyFile(std::string src, std::string dst);

/*-------------------------------------------------------------------------------------
���ܣ�					��ȡһ���ļ���·�����Ĳ���
input:
	vt_strFolder_o��	һ���ļ���·��
output
	����:				���Ĳ���
-------------------------------------------------------------------------------------*/	
	int getMaxFolderLevel(std::vector<std::string>& vt_strFolders);
};
