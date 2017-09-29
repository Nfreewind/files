#include "File_Read.h"

int ReadTxt(const char* dir, std::vector<std::string>& outfile){
	FILE *fp;
	char StrLine[100];             //ÿ������ȡ���ַ���
	fp = fopen(dir, "r");
	if (fp == NULL) //�ж��ļ��Ƿ���ڼ��ɶ�
	{
		printf("error!");

	}
	while (!feof(fp))
	{
		fgets(StrLine, 100, fp);  //��ȡһ��
		outfile.push_back(StrLine);
	}
	fclose(fp);  //�ر��ļ�
	printf("file read finish \n");
	return 0;
}

int C_ReadTxt(const char* filename, std::vector<std::string>& outfile){
		FILE *fp;
	char StrLine[1024];             //ÿ������ȡ���ַ���
	if ((fp = fopen(filename, "r")) == NULL) //�ж��ļ��Ƿ���ڼ��ɶ�
	{
		printf("error!");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(StrLine, 1024, fp);  //��ȡһ��
		printf("%s\n", StrLine); //���
		outfile.push_back(UTF8ToGB(StrLine));
	}
	fclose(fp);
	return 0;
}

int CPlus_ReadTxt(const char* filename, std::vector<std::string>& outfile){
	std::string StrLine;             //ÿ������ȡ���ַ���
	std::fstream fp(filename, fstream::in);
	std::string buffer;
	while (!fp.eof())
	{
		fp >> buffer;
		//cout << buffer << endl;
		if (buffer.empty()){
			continue;
		}
		outfile.push_back(buffer);

	}
	fp.close();
	printf("file read finish \n");
	return 0;
}

