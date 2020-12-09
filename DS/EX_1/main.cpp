#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;  //函数返回值状态类型定义
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
    ElemType * elem;
    int length;
    int listsize;
}SqList;

typedef struct{  //线性表的管理表定义
    struct { char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;

using namespace std;

//所要使用的函数声明以供使用
int InitList(SqList &L);
int DestroyList(SqList &L);
int ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L);
int GetElem(SqList L, int i, ElemType &e);
int LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e);
status NextElem(SqList L,ElemType cur_e,ElemType &next_e);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);      //单个线性表的处理
status  SaveList(SqList L,char FileName[]);
status  LoadList(SqList &L,char FileName[]);  //线性表的存储读写操作
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);   //多链表的操作

/*--------------------------------------------*/
int main(void){
    LISTS Lists;
    Lists.length=0;
    int n;
    char name[30], FileName[30];;
    LISTS L_a;
    SqList L;  int op=1; int j;
    int f,e,i,pre,next,p;
    int count=0;
    int flag;
    L.elem=NULL; //表L置为空
    while(op){
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 添加线性表      7. 获取元素的前驱\n");
        printf("    	  2. 清空线性表      8. 获取元素的后继\n");
        printf("    	  3. 线性表判空      9.  插入元素\n");
        printf("    	  4. 线性表长度      10. 删除元素\n");
        printf("    	  5. 获取元素        11. 遍历线性表\n");
        printf("    	  6. 查找元素        12. 保存线性表\n");
        printf("    	  13.加载线性表      14. 删除线性表\n");
        printf("    	  15.查找线性表      16.遍历多线性表\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~16]:");
        scanf("%d",&op);
        switch(op) {
            case 1:
                printf("请输入要添加的线性表的个数");
                scanf("%d", &n);
                while(n--)
                {
                    printf("请输入要添加的线性表的名称\n");
                    scanf("%s",name);
                    AddList(Lists,name);  //增加函数的使用
                    printf("线性表添加成功,请输入线性表的元素，以0结尾\n");
                    scanf("%d",&e);
                    while (e)
                    {
                        ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
                        scanf("%d",&e);
                    }
                }
                for(n=0;n<Lists.length;n++)
                {
                    printf("%s ",Lists.elem[n].name);
                    ListTraverse(Lists.elem[n].L);
                    printf("\n");
                }
                getchar();
                getchar();
                printf("\n");
                break;
            case 2:  // 清空线性表 done
                printf("请输入你想要清空的线性表的名字");
                scanf("%s",name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行删除操作
                        flag=ClearList(Lists.elem[i].L);
                        if(flag==OK) printf("已清空该线性表");
                        if(flag==INFEASIBLE) printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 3: //判断是否为空 done
                printf("请输入线性表的名字");
                scanf("%s",name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行删除操作
                        flag=ListEmpty(Lists.elem[i].L);
                        if(flag==INFEASIBLE) printf("ERROR");
                        if(flag==true) printf("该线性表为空");
                        if(flag== false) printf("该线性表不为空");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 4:  //求表长  done
                printf("请输入线性表的名字");
                scanf("%s",name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行删除操作
                        flag=ListLength(Lists.elem[i].L);
                        printf("此线性表的表长为：%d",flag);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 5:  //获取元素 done
                printf("请输入要进行查找元素线性表的名字");
                scanf("%s", name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行删除操作
                        printf("请输入要查找的元素的位置");
                        scanf("%d", &i);
                        j = GetElem(Lists.elem[i].L, i, e);  //查找函数的使用
                        if (j == OK) printf("获取元素成功!位置%d的元素是%d", i, e);
                        if (j == ERROR) printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 6: //查找元素位置 done
                printf("请输入要进行查找元素线性表的名字");
                scanf("%s", name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行查找操作
                        printf("请输入要查找的元素");
                        scanf("%d", &e);
                        j = LocateElem(Lists.elem[i].L,e);  //查找函数的使用
                        if (j == ERROR) printf("ERROR");
                        printf("查找元素成功!元素%d的位置%d",e,j);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 7: //查找前驱元素 done
                printf("请输入要进行查找元素线性表的名字");
                scanf("%s", name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行查找操作
                        printf("请输入要查找前驱的元素");
                        scanf("%d", &e);
                        j = PriorElem(Lists.elem[i].L,e,pre);  //查找函数的使用
                        if (j == ERROR) printf("ERROR");
                        printf("查找元素成功!元素%d的前驱为%d",e,pre);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 8:  //查找后继元素 done
                printf("请输入要进行查找元素线性表的名字");
                scanf("%s", name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行查找操作
                        printf("请输入要查找后继的元素");
                        scanf("%d", &e);
                        j = NextElem(Lists.elem[i].L,e,next);  //查找函数的使用
                        if (j == ERROR) printf("ERROR");
                        printf("查找元素成功!元素%d的后继为%d",e,next);
                        break;
                    }
                }
                getchar();getchar();
                break;
            case 9:  //插入元素  done
                printf("请输入要进行插入元素线性表的名字");
                scanf("%s", name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行查找操作
                        printf("请输入要插入的位置");
                        scanf("%d",&p);
                        printf("请输入要插入的元素");
                        scanf("%d",&e);
                        j = ListInsert(Lists.elem[i].L,p,e);  //查找函数的使用
                        printf("%s\n", j==OK? "OK" : j==ERROR? "ERROR" : "OVERFLOW");
                        printf("插入后的结果为：");
                        ListTraverse(Lists.elem[i].L);
                        break;
                    }
                }
                getchar();getchar();
                break;
            case 10:  //元素的删除操作 done
                printf("请输入要进行删除元素线性表的名字");
                scanf("%s", name);
                for(i=0;i<Lists.length;i++){
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0){ //匹对陈功执行查找操作
                        printf("请输入要删除的位置");
                        scanf("%d",&p);
                        j=ListDelete(Lists.elem[i].L,p,e);
                        if(j==ERROR) printf("ERROR\n");
                        if(j==OK) printf("OK\n删除的元素为%d\n",e);
                        printf("删除后的结果为：");
                        ListTraverse(Lists.elem[i].L);
                        break;
                    }
                }
                getchar();getchar();
                break;
            case 11:  //线性表的遍历操作 done
                printf("请输入要进行遍历线性表的名字");
                scanf("%s", name);
                for(i=0;i<Lists.length;i++) {
                    int j = strcmp(Lists.elem[i].name, name);
                    if(j==0) {
                        printf("遍历之后的结果为:\n");
                        j = ListTraverse(Lists.elem[i].L);
                        if (j == OK && !Lists.elem[i].L.length) printf("空线性表，没有元素可以展示\n");
                        break;
                    }
                }
                getchar();getchar();
                break;
            case 12:  //文件保存操作 done
                i=0;
                printf("请输入要保存的线性表的名字");
                scanf("%s",name);
                for(i=0;i<Lists.length;i++) {
                    int j = strcmp(Lists.elem[i].name,name);
                    if(j==0) {
                        printf("请输入文件所在地址：");
                        scanf("%s",FileName);
                        j = SaveList(Lists.elem[i].L, FileName);
                        if(j==ERROR) printf("文件打开失败");
                        if(j==OK){
                            printf("保存成功\n");
                            ListTraverse(Lists.elem[i].L);
                        }
                        break;
                    }
                }
                if(i>=Lists.length) printf("没有相应的线性表");
                getchar();getchar();
                break;
            case 13:  //线性表加载操作
                printf("请输入要加载的线性表的名字");
                scanf("%s",name);
                for(i=0;i<Lists.length;i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) {
                        free(Lists.elem[i].L.elem);
                        Lists.elem[i].L.elem = NULL;
                        printf("请输入要读取的文件地址");
                        scanf("%s", FileName);
                        j = LoadList(Lists.elem[i].L, FileName);
                        if (j == ERROR) printf("文件读取失败");
                        if (j == OK) printf("文件读取成功");
                        break;
                    }
                }
                getchar();getchar();
                break;
            case 14:  //删除线性表 done
                printf("请输入要删除的线性表的名字");
                scanf("%s",name);
                if (RemoveList(Lists,name)==OK)
                    for(n=0;n<Lists.length;n++)
                    {
                        printf("%s ",Lists.elem[n].name);
                        ListTraverse(Lists.elem[n].L);
                        putchar('\n');
                    }
                else printf("删除失败");
                printf("\n");
                getchar();
                getchar();
                break;
            case 15:  //查找线性表
                printf("请输入要查找的线性表的名字");
                scanf("%s",name);
                if (n=LocateList(Lists,name))
                {
                    printf("%s ",Lists.elem[n-1].name);
                    ListTraverse(Lists.elem[n-1].L);
                    putchar('\n');
                }
                else printf("查找失败\n");
                getchar();getchar();
                break;
            case 16:  //遍历多线性表
                if(Lists.length==0) printf("线性表的个数为零，展示为空");
                for(i=0;i<Lists.length;i++){
                    printf("%s ",Lists.elem[i].name);
                    ListTraverse(Lists.elem[i].L);
                    printf("\n");
                }
                getchar();
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 1;
}//end of main()

// 初始化线性表,构造一个空线性表
int InitList(SqList &L)  //case 1
{
    if(L.elem)
        return INFEASIBLE;
    else{
        L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(int));
        if (!L.elem)
            return OVERFLOW;
        L.length = 0;
        L.listsize = LIST_INIT_SIZE;
        return OK;
    }
}  //case1

//初始条件：线性表已存在,操作结果：销毁线性表
int DestroyList(SqList &L){
    if(!L.elem)
        return INFEASIBLE;
    else{
        free(L.elem);
        L.elem=NULL;
        L.length=0;
        L.listsize=0;
        return OK;
    }
}

//case 2
/*初始条件：线性表存在;操作结果：清空线性表
（将当前元素个数赋值0，遍历不出任何一个元素，相当于清空线性表）*/
status ClearList(SqList &L){
    if(!L.elem)
        return INFEASIBLE;
    else{
        L.length=0;
        return OK;
    }
}

//case 3
/*初始条件：线性表存在
操作结果：线性表为空返回true，不为空返回false*/
status ListEmpty(SqList L){
    if(!L.elem)
        return INFEASIBLE;
    else{
        return (L.length == 0) ? true : false;
    }
}

//case 4
//获取线性表当前元素个数
//初始条件：线性表已存在
//操作结果：返回线性表当前元素个数
int ListLength(SqList L){
    if(!L.elem)
        return INFEASIBLE;
    else
        return L.length;
}

//case 5
//获得指定位置的数据元素
//初始条件：线性表存在
//操作结果：获得指定位置的数据元素并赋值给e
int GetElem(SqList L, int i, ElemType &e){
    if(!L.elem) return INFEASIBLE;
    else{
        if(i<1||i>L.length)
            return ERROR;
        e=*(L.elem+i-1);//（基址+i-1）即为第i个元素的地址
        return OK;
    }
}

//case 6
//定位元素（获得符合一定条件的数据元素的位序）
//初始条件：线性表已存在
//操作结果：返回L中第一个与e满足关系的元素的位序,若不存在返回0
int LocateElem(SqList L,ElemType e) {
    if(!L.elem) return INFEASIBLE;
    else{
        ElemType *p = L.elem; //P的初值为第一个元素的存储位置
        int i = 1;//i的初值为第一个元素的位序
        while (i <= L.length&&p[i-1]!=e)//越界或已找到满足条件的元素
            ++i;
        //i的最大可能值为L.length+1
        {
            if (i <= L.length)
                return i;
            else
                return 0;
        }
    }
}

//case 7
//返回要查找的位置元素的前驱
status PriorElem(SqList L,ElemType e,ElemType &pre)
{
    if(!L.elem) return INFEASIBLE;
    int i=2;
    ElemType *p=L.elem+1;
    while(i<=L.length&&*p!=e)
    {
        p++;
        i++;
    }
    if(i>L.length)
        return ERROR;
    pre=*--p;
    return OK;
}

//case 8
//初始条件：线性表已存在，数据元素存在后继
//操作结果：查找数据元素，若线性表中有该元素且后继存在，将后继拷贝给一个与数据元素数据类型相同的变量；若后继不存在，上述变量无定义
status NextElem(SqList L,ElemType e,ElemType &next)
{
    if (!L.elem) return INFEASIBLE;
    int i;
    for (i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) { next = L.elem[i + 1]; return OK; }
    }
    return ERROR;
}
//case 9
//插入一个数据元素
//初始条件：线性表存在
//操作结果：在L中第i个元素之前插入新的元素e，L的长度加1
status ListInsert(SqList &L,int i,ElemType e)
{
    if(!L.elem) return INFEASIBLE;
    ElemType *newbase,*q,*p;
    if(i<1||i>L.length+1)//i值不合法，无法执行插入操作
        return ERROR;
    if(L.length>=L.listsize) //当前存储空间已满，增加分配空间
    {
        if(!(newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType))))
            exit(0);//分配存储空间失败
        L.elem=newbase;//新基址
        L.listsize+=LISTINCREMENT;//增加存储容量
    }
    q=L.elem+i-1;//q为插入位置
    for(p=L.elem+L.length-1;p>=q;--p)
    { *(p+1)=*p;} //给插入位置之后的元素赋值达到之后元素后移一位的效果
    *q=e;//插入e
    L.length+=1;
    return OK;
}
//case10
//删除元素
//初始条件：线性表已存在
//操作结构：删除第i个数据元素并返回其值，L的长度减1
status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L.elem) return INFEASIBLE;
    ElemType *p, *q;
    if (i < 1 || i > L.length)//i值不合法
        return ERROR;
    p = L.elem + i - 1;//p为被删除元素的位置
    e = *p;//被删除元素的值赋给e
    q = L.elem + L.length - 1;//表尾元素的位置
    for (++p; p <= q; ++p)
        *(p - 1) = *p;
    L.length--;
    return OK;
}
//case 11

status ListTraverse(SqList L)  //case 11
{
    if(!L.elem) return INFEASIBLE;
    ElemType *p=L.elem;
    int i;
    for(i=0;i<L.length;i++)
        printf("%d ",p[i]);
    return OK;
}

status  SaveList(SqList L,char FileName[])  //case 12
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(!L.elem) return INFEASIBLE;
    FILE  *fp;
    if ((fp=fopen(FileName,"wb"))==NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    fwrite(L.elem,sizeof(ElemType),L.length,fp);
    fclose(fp);
    return OK;
}

status  LoadList(SqList &L,char FileName[]) //case 13
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L.elem) return INFEASIBLE;
    FILE  *fp;
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(int));
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    if ((fp=fopen(FileName,"rb"))==NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    while(fread(&L.elem[L.length],sizeof(ElemType),1,fp))
        L.length++;
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])  //case 1
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int i=0;
    Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(int));
    Lists.elem[Lists.length].L.length = 0;
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    if (!Lists.elem[Lists.length].L.elem)
        return OVERFLOW;
    while (ListName[i]!='\0'){
        Lists.elem[Lists.length].name[i] = ListName[i];
        i++;
    }
    Lists.elem[Lists.length].name[i]='\0';
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[])  //case 14
// Lists中删除一个名称为ListName的线性表
{
    int i;
    for(i=0;i<Lists.length;i++){
        int j = strcmp(Lists.elem[i].name,ListName);
        if(j==0){ //匹对陈功执行删除操作

            Lists.elem[i]=Lists.elem[i+1];
            Lists.elem[i].L=Lists.elem[i+1].L;
            break;
        }
    }
    if(i==Lists.length) return ERROR;
    Lists.length--;
    return OK;
    /********** End **********/
}

int LocateList(LISTS Lists,char ListName[]) //case 15
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int i;
    for(i=1;i<=Lists.length;i++){
        int j=strcmp(Lists.elem[i-1].name,ListName);
        if (j==0)
            return i;
    }
    return ERROR;
}

