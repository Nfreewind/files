//#include "StdAfx.h"
#include "C_Text_v2.h"
#include <fstream>

//��ȡtxt�ĵ��е�����
std::vector<std::string> C_Text_v2::readTxt(std::string txtFilePath)
{	
	std::vector<std::string> txtContent;
	const int lineLength = 5000;
	std::fstream fsin(txtFilePath, std::ios::in);

	while(fsin) 
	{ 
		char str_buff[lineLength];
		fsin.getline(str_buff, lineLength);//��ȡһ�� 
		if(fsin) 
			txtContent.push_back(str_buff);
	} 
	fsin.close();
	return txtContent;
}

//��������Ϊtxt�ĵ���Ӳ��
void C_Text_v2::saveVtStr(std::vector<std::string> vt_str, std::string filePath)
{
	std::fstream fs;
	fs.open(filePath.c_str(), std::ios::out);

	if (vt_str.size() >= 1)
		fs << vt_str[0].c_str();

	for (int i = 1; i < vt_str.size(); i++)
		fs << std::endl << vt_str[i].c_str();
	//fs << std::endl;
	fs.close();
}

/*--------------------------------------------------------------------
in��			�������룺"1,2,3,4,56"
delimiters:		�������룺"��"
���أ�			"1","2","3","4","56"
--------------------------------------------------------------------*/
std::vector<std::string> C_Text_v2::splitString(std::string in, std::string delimiters)
{
	std::vector<std::string> ret;
	int iLen = in.length();
	if (iLen == 0){
		return ret;
	}	
	char *buffer = new char[iLen + 1];
	strcpy(buffer, in.c_str());

	char * token = strtok( buffer, delimiters.c_str() );
	while( token != NULL ){
		ret.push_back(token);	

		token = strtok( NULL, delimiters.c_str());
	}	
	delete []buffer;
	return ret;
}




////��ȡtxt�ĵ��е�����
//std::vector<std::string> C_Text::readTxt(std::string txtFilePath)
//{
//	std::vector<std::string> txtContent;
//	const int lineLength = 1000;
//	char charLineContent[lineLength];
//	strcpy(charLineContent, txtFilePath.c_str());
//	//��ȡtxt�ļ��е����ݡ�
//	FILE *fp = fopen(txtFilePath.c_str(), "rb");
//	if(fp != NULL)
//	{
//		while(!feof(fp))
//		{
//			sprintf(charLineContent, "%s", "");
//			fscanf(fp,"%s", charLineContent);
//			if(strlen(charLineContent) > 0)
//				txtContent.push_back(charLineContent);
//		}
//	}
//	fclose(fp);
//	return txtContent;
//}