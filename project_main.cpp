#include <iostream>
#include <stdio.h>
#include <string.h>


#include "../data_DLL/pch.h"
#pragma comment(lib,"data_DLL.lib")
typedef struct student
{
	int stuID;//序号
	char name[12];//姓名
	int score[4];//各科成绩，依次为语文、数学、外语、综合
	int totalScore; //总分
	double submittedScore;//投档分
	int level;//过线级别
	int status;//档案状态
	int schoolID; //投档学校
} STUDENT;
typedef struct stuLink
{
	int stuID;//学生证号
	int totalScore;//总分
	double submittedScore;//投档分
	struct stuLink* next;//
}STULINK;
typedef struct cp
{
	STULINK* pd;
	int stuID;
}CP;
typedef struct enrollment_plan
{
	int collegeID;//学校代码
	char collegeName[24];//学校名称
	int numberOfEnrollment;//招生人数
	int numberOfReceived;//已投档人数
	STULINK* stuInfo;//已投档学生信息
}ENROLLMENT_PLAN;
typedef struct aspiration
{
	int stuID;
	int wish[6];

}ASPIRATION;
typedef struct success
{
	int stuID;
	int totalScore1;
	double submittedScore;
	char name[12];
	char collegeName[24];
	int collegeID;
}SUCCESS;
typedef struct fail
{
	int stuID;
	int totalScore1;
	double submittedScore;
	char name[12];
	char collegeName[24];
	char reason[24];
}FAIL;
void sort(int a[],int b)
{
	int i,j,t;
	for (i = 0; i < b; i++)
	{
		for (j = i + 1; j < b; j++)
		{
			if (a[i] < a[j])
			{
				t = a[i];
				a[i] = a[j]; a[j] = t;
			}
		}
	}
}
int main()
{
	int i, c, schid, n, j, t, m, count[751] = { 0 }, KU_plan = 0, SU_plan = 0, k = 0, s = 0, f, r, id, count1[751][3];
	int * Max,*Min; float* ave, * Sum, * sd,* sum;
	printf("请输入模拟人数n:");
	scanf_s("%d", &n);
	struct student* STUDENT;
	struct enrollment_plan* ENROLLMENT_PLAN;
	struct aspiration* ASPIRATION;
	int* Chinese, * Math, * English, * Synthesis, * totalScore, * b;
	double* submittedScore;
	STULINK* theslink;//链表
	theslink = (STULINK*)calloc(n, sizeof(STULINK));
	FILE* fp;
	fopen_s(&fp, "高考成绩_模拟.txt", "r");//打开文件
	fscanf_s(fp, "%d", &n);
	//printf("%d\n", n);
	STUDENT = (student*)calloc(n, sizeof(student));
	Chinese = (int*)calloc(n, sizeof(int));
	Math = (int*)calloc(n, sizeof(int));
	English = (int*)calloc(n, sizeof(int));
	Synthesis = (int*)calloc(n, sizeof(int));
	totalScore = (int*)calloc(n, sizeof(int));
	submittedScore = (double*)calloc(n, sizeof(double));
	b = (int*)calloc(n, sizeof(int));
	//读取学生信息到结构体数组中
	for (i = 0; i < n; i++)
	{

		fscanf_s(fp, "%d", &STUDENT[i].stuID);
		fscanf_s(fp, "%s", &STUDENT[i].name, 11);
		fscanf_s(fp, "%d", &STUDENT[i].score[0]);
		fscanf_s(fp, "%d", &STUDENT[i].score[1]);
		fscanf_s(fp, "%d", &STUDENT[i].score[2]);
		fscanf_s(fp, "%d", &STUDENT[i].score[3]);
		Chinese[i] = STUDENT[i].score[0]; Math[i] = STUDENT[i].score[1]; English[i] = STUDENT[i].score[2]; Synthesis[i] = STUDENT[i].score[3]; totalScore[i] = STUDENT[i].score[0] + STUDENT[i].score[1] + STUDENT[i].score[2] + STUDENT[i].score[3];
		submittedScore[i] = totalScore[i] + 0.001 * STUDENT[i].score[0] + 0.000001 * STUDENT[i].score[1] + 0.000000001 * STUDENT[i].score[2];
		STUDENT[i].totalScore = STUDENT[i].score[0] + STUDENT[i].score[1] + STUDENT[i].score[2] + STUDENT[i].score[3];
		STUDENT[i].submittedScore = totalScore[i] + 0.001 * STUDENT[i].score[0] + 0.000001 * STUDENT[i].score[1] + 0.000000001 * STUDENT[i].score[2];
		//对链表赋值，为排序做准备
		theslink[i].stuID = STUDENT[i].stuID;
		theslink[i].totalScore = STUDENT[i].totalScore;
		theslink[i].submittedScore = STUDENT[i].submittedScore;
		theslink[i].next = NULL;		

	}
     //fclose(fp);

	//调用函数计算每门课程的统计量
	FILE* par;
	fopen_s(&par, "成绩分析报告.txt", "w");
	fprintf_s(par, "      最高分  最低分  平均分             方差\n");
	fprintf_s(par, "语文：%d      %d      %f       %f\n", maxs(Chinese, n), mins(Chinese, n), Ave(Chinese, n), SD(Chinese, n));
	fprintf_s(par, "数学：%d      %d      %f       %f\n", maxs(Math, n), mins(Math, n), Ave(Math, n), SD(Math, n));
	fprintf_s(par, "英语：%d      %d      %f       %f\n", maxs(English, n), mins(English, n), Ave(English, n), SD(English, n));
	fprintf_s(par, "综合：%d      %d      %f       %f\n", maxs(Synthesis, n), mins(Synthesis, n), Ave(Synthesis, n), SD(Synthesis, n));
	fclose(par);
	FILE* fp2;
	fopen_s(&fp2, "招生计划.txt", "r");
	fscanf_s(fp2, "%d", &t);
	ENROLLMENT_PLAN = (enrollment_plan*)calloc(n, sizeof(enrollment_plan));
	for (i = 0; i < t; i++)
	{
		fscanf_s(fp2, "%d", &ENROLLMENT_PLAN[i].collegeID);
		fscanf_s(fp2, "%s", &ENROLLMENT_PLAN[i].collegeName, 24);
		fscanf_s(fp2, "%d", &ENROLLMENT_PLAN[i].numberOfEnrollment);
		ENROLLMENT_PLAN[i].numberOfReceived = 0;
		ENROLLMENT_PLAN[i].stuInfo = NULL;
	}
	fclose(fp2);

		//读取学生志愿文件
		FILE* fp3;
		fopen_s(&fp3, "学生志愿.txt", "r");
		fscanf_s(fp3, "%d", &m);
		ASPIRATION = (aspiration*)calloc(n, sizeof(aspiration));
		for (i = 0; i < m; i++)
		{
			fscanf_s(fp3, "%d", &ASPIRATION[i].stuID);
			fscanf_s(fp3, "%d", &ASPIRATION[i].wish[0]);
			fscanf_s(fp3, "%d", &ASPIRATION[i].wish[1]);
			fscanf_s(fp3, "%d", &ASPIRATION[i].wish[2]);
			fscanf_s(fp3, "%d", &ASPIRATION[i].wish[3]);
			fscanf_s(fp3, "%d", &ASPIRATION[i].wish[4]);
			fscanf_s(fp3, "%d", &ASPIRATION[i].wish[5]);


		}
		fclose(fp3);
		
		//一分一段表
		FILE* sgt;
		fopen_s(&sgt, "一分一段表.txt", "w");
		fprintf_s(sgt, "一分一段表：\n");
		int a = 750, g = 0, totalcount = 0;
		for (j = 0; j < 751; j++)
		{
			while (a >= 0)
			{
				for (int i = 1; i <= n; i++)
				{
					if (totalScore[i] == a)
						g++;
				}
				totalcount += g;
				count1[j][0] = a, count1[j][1] = g, count1[j][2] = totalcount;
				g = 0, a--;
				break;
			}
			fprintf_s(sgt, "%d %d %d\n", count1[j][0], count1[j][1], count1[j][2]);
		}
		fclose(sgt);
		//确定批次线
		//统计各批次招生人数
		for (i = 0; i < t; i++)
		{
			if (ENROLLMENT_PLAN[i].collegeID < 200)
			{
				KU_plan = ENROLLMENT_PLAN[i].numberOfEnrollment + KU_plan;
				f = KU_plan * 1.1;
			}
			if (ENROLLMENT_PLAN[i].collegeID >= 200)
			{
				SU_plan = ENROLLMENT_PLAN[i].numberOfEnrollment + SU_plan; r = SU_plan * 1.1;
			}
		}

		int OneLine = 0, TwoLine = 0;
		for (int i = 0; i < 751; i++)
		{
			if (count1[i][2] >= f)
			{
				OneLine = count1[i][0];
				break;
			}
		}
		for (int i = 0; i < 751; i++)
		{
			if (count1[i][2] >= (f + r))
			{
				TwoLine = count1[i][0];

				break;
			}
		}
		STULINK change1;//按投档分从高到低排序链表
		for (i = 0; i < n; i++)
		{
			for (j = i + 1; j < n + 1; j++)
			{
				if (theslink[i].submittedScore < theslink[j].submittedScore)
				{
					change1 = theslink[i];
					theslink[i] = theslink[j];
					theslink[j] = change1;
				}
			}
		}
		//学生投档文件
		FILE* stu = NULL;
		fopen_s(&stu, "学生投档情况.txt", "w");
		fprintf_s(stu, "             ********************学生投档情况*********************\n");
		fprintf_s(stu, "一本线：%d 二本线：%d 一本计划人数：%d 二本计划人数：%d\n", OneLine, TwoLine, f, r);
		fprintf_s(stu, "成功投档学生信息如下：\n");
		CP* q;
		q = (CP*)calloc(m, sizeof(CP));
		int  u, v = 0;
		for (k = 1; k < n; k++)//通过降序链表的循环筛选
		{
			v = 0;
			for (s = 0; s < m; s++)//依次查找志愿
			{
				if (ASPIRATION[s].stuID == theslink[k].stuID)
				{

					for (u = 0; u < 6; u++)
					{
						for (j = 0; j < t; j++)//循环查找学校
						{
							if (ENROLLMENT_PLAN[j].collegeID == ASPIRATION[s].wish[u])//确定志愿的学校
							{
								if (ENROLLMENT_PLAN[j].numberOfReceived == 0)
								{
									ENROLLMENT_PLAN[j].stuInfo = &theslink[k];
									q[j].pd = &theslink[k];
									v = 1;
									ENROLLMENT_PLAN[j].numberOfReceived++;
									for (int i = 0; i < n; i++)
									{
										if (STUDENT[i].stuID == theslink[k].stuID)
										{
											STUDENT[i].schoolID = ENROLLMENT_PLAN[j].collegeID;
											fprintf_s(stu, "%d %s %d %s\n", STUDENT[i].stuID, STUDENT[i].name, totalScore[i], ENROLLMENT_PLAN[j].collegeName);
										}
									}
								}
								else if (ENROLLMENT_PLAN[j].numberOfReceived == (ENROLLMENT_PLAN[j].numberOfEnrollment - 1))
								{	//录取此人且该学生是该学校最后一位学生
									q[j].pd->next = &theslink[k];
									v = 1;
									for (int i = 0; i < n; i++)
									{
										if (STUDENT[i].stuID == theslink[k].stuID)
										{
											STUDENT[i].schoolID = ENROLLMENT_PLAN[j].collegeID; fprintf_s(stu, "%d %s %d %s\n", STUDENT[i].stuID, STUDENT[i].name, totalScore[i], ENROLLMENT_PLAN[j].collegeName);
										}
									}
									ENROLLMENT_PLAN[j].numberOfReceived++;
								}
								else if (ENROLLMENT_PLAN[j].numberOfReceived < ENROLLMENT_PLAN[j].numberOfEnrollment)
								{	//已录取学生且未满,录取此人
									q[j].pd->next = &theslink[i];
									q[j].pd = &theslink[i];
									v = 1;
									for (int i = 0; i < n; i++)
									{
										if (STUDENT[i].stuID == theslink[k].stuID)
										{
											STUDENT[i].schoolID = ENROLLMENT_PLAN[j].collegeID; fprintf_s(stu, "%d %s %d %s\n", STUDENT[i].stuID, STUDENT[i].name, totalScore[i], ENROLLMENT_PLAN[j].collegeName);
										}
									}
									ENROLLMENT_PLAN[j].numberOfReceived++;
								}//学校已经录满,不录取
								if (v == 1)
									goto zloop;
							}
						}
					}
				}//没匹配到的都是二本以下的

			}
		zloop:;
		}

		int x = 0, y = 0;
		for (i = 0; i < m; i++)
		{
			if (ENROLLMENT_PLAN[i].collegeID <= 199)
				x += ENROLLMENT_PLAN[i].numberOfReceived;
			else
				y += ENROLLMENT_PLAN[i].numberOfReceived;
		}
		fprintf_s(stu, "一批成功投档人数为：%d\n", x);
		fprintf_s(stu, "二批成功投档人数为：%d\n", y);

		int susss = 0;
		for (i = 0; i < t; i++)
		{
			susss += ENROLLMENT_PLAN[i].numberOfReceived;
		}

		SUCCESS* thesuccess;//投档学生结构体
		thesuccess = (SUCCESS*)calloc(n, sizeof(SUCCESS));
		FAIL* thefail;//未投档学生结构体
		thefail = (FAIL*)calloc(n, sizeof(FAIL));
		int bs, bf;
		for (i = 0, bs = 0, bf = 0; i < n; i++)
		{

			if (STUDENT[i].schoolID != 0)
			{
				thesuccess[bs].stuID = STUDENT[i].stuID;
				thesuccess[bs].submittedScore = STUDENT[i].submittedScore;
				thesuccess[bs].totalScore1 = STUDENT[i].totalScore;
				strcpy_s(thesuccess[bs].name, 11, STUDENT[i].name);
				for (j = 0; j < t; j++)
				{
					if (STUDENT[i].schoolID == ENROLLMENT_PLAN[j].collegeID)
					{
						thesuccess[bs].collegeID = ENROLLMENT_PLAN[j].collegeID;
						strcpy_s(thesuccess[bs].collegeName, 23, ENROLLMENT_PLAN[j].collegeName);
					}
				}
				bs++;
			}
			else
			{
				thefail[bf].stuID = STUDENT[i].stuID;
				thefail[bf].totalScore1 = STUDENT[i].totalScore;
				strcpy_s(thefail[bf].name, 11, STUDENT[i].name);
				if (thefail[bf].totalScore1 > TwoLine)
				{
					strcpy_s(thefail[bf].reason, 23, "滑档");
				}
				else
					strcpy_s(thefail[bf].reason, 23, "未过二本线");
				bf++;
			}
		}
		fprintf_s(stu, "未成功投档学生信息及其原因：\n");
		for (i = 0; i < n - susss; i++)
		{
			fprintf_s(stu, "%d %s %d %s\n", thefail[i].stuID, thefail[i].name, thefail[i].totalScore1, thefail[i].reason);
		}
		fclose(stu);
		//学校投档文件
		sum = (float*)calloc(susss, sizeof(int)); ave = (float*)calloc(susss, sizeof(float));
		Max = (int*)calloc(susss, sizeof(int)); Min = (int*)calloc(susss, sizeof(int));
		sd= (float*)calloc(susss, sizeof(float));Sum= (float*)calloc(susss, sizeof(float));
		FILE* sch = NULL;
		fopen_s(&sch, "学校投档情况.txt", "w");//输出学校投档文件	
		for (i = 0; i < t; i++)
		{
			fprintf_s(sch, "%s(%d)\n", ENROLLMENT_PLAN[i].collegeName, ENROLLMENT_PLAN[i].collegeID);
			for (s = 0; s < susss; s++)
			{
				if (thesuccess[s].collegeID == ENROLLMENT_PLAN[i].collegeID)
				{
					if (Max[i] < thesuccess[s].totalScore1)
						Max[i] = thesuccess[s].totalScore1;
					if (750 > thesuccess[s].totalScore1)
						Min[i] = thesuccess[s].totalScore1;
					sum[i] = thesuccess[s].totalScore1+sum[i];
					ave[i] = sum[i] / ENROLLMENT_PLAN[i].numberOfReceived;
					fprintf_s(sch,"%d %s %d\n", thesuccess[s].stuID, thesuccess[s].name, thesuccess[s].totalScore1);
				}

			}fprintf_s(sch,"已录取人数：%d 最高分：%d 最低分：%d 平均分：%f   ", ENROLLMENT_PLAN[i].numberOfReceived,Max[i],Min[i],ave[i]);
			for (s = 0; s < susss; s++)
			{
				if (thesuccess[s].collegeID == ENROLLMENT_PLAN[i].collegeID)
				{
					Sum[i] = (thesuccess[s].totalScore1 - ave[i]) * (thesuccess[s].totalScore1 - ave[i]) + Sum[i];
					sd[i] = sqrt((Sum[i] / ENROLLMENT_PLAN[i].numberOfReceived));
				}

			}fprintf_s(sch,"方差：%f\n",sd[i]);

		}
		fclose(sch);
		int flag=1;

		//查询菜单
		while (flag)
		{
			printf("          查询学生投档情况输入1:\n");
			printf("          查询学校投档情况输入2:\n");
			printf("          退出查询请输入0:\n");
			scanf_s("%d", &c);
			switch (c)
			{
			case 1:
				printf("请输入您的准考证号：");
				scanf_s("%d", &id);
				for (i = 0; i < susss; i++)
				{
					if (thesuccess[i].stuID == id)
					{
						printf("%s  ", thesuccess[i].name);
						printf("%s\n", thesuccess[i].collegeName);
						break;
					}
				}
				for (j = 0; j < n - susss; j++)
				{
					if (thefail[j].stuID == id)
					{
						printf("%s  ", thefail[j].name);
						printf("%s\n", thefail[j].reason);
						break;
					}
				}break;
			case 2:	printf("请输入您的查询学校：");
				scanf_s("%d", &schid);

				for (i = 0; i < t; i++)
				{
					printf("%d\n", schid);
					for (s = 0; s < susss; s++)
					{
						if (thesuccess[s].collegeID == schid)
						{

							printf("%d %s %d %s\n", thesuccess[s].stuID, thesuccess[s].name, thesuccess[s].totalScore1, thesuccess[s].collegeName);
						}


					}break;
				}break;
			}
			if (c == 0)
				flag = 0;
		}

free(STUDENT); free(ENROLLMENT_PLAN); free(ASPIRATION);
free(Chinese); free(Math); free(English); free(Synthesis); free(submittedScore);free(totalScore);
free(q); free(thesuccess); free(thefail);
free(Max); free(Min); free(ave); free(Sum); free(sd); free(sum);		
		return 1;
		}		
